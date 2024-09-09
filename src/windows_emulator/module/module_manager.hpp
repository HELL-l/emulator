#pragma once
#include "mapped_module.hpp"
#include <emulator.hpp>

class module_manager
{
public:
	module_manager() = default; // TODO: Get rid of that
	module_manager(emulator& emu);

	mapped_module* map_module(std::filesystem::path file);

	mapped_module* find_by_address(const uint64_t address)
	{
		const auto entry = this->get_module(address);
		if(entry != this->modules_.end())
		{
			return &entry->second;
		}

		return nullptr;
	}

private:
	emulator* emu_{};

	using module_map = std::map<uint64_t, mapped_module>;
	module_map modules_{};

	module_map::iterator get_module(const uint64_t address)
	{
		if (this->modules_.empty())
		{
			return this->modules_.end();
		}

		auto upper_bound = this->modules_.upper_bound(address);
		if (upper_bound == this->modules_.begin())
		{
			return this->modules_.end();
		}

		std::advance(upper_bound, -1);
		return upper_bound;
	}
};