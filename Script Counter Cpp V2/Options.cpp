#include "Options.h"

bool Options::IsEmpty()
{
	if (FileTypes.empty()) 
	{
		return true;
	}
	return false;
}

bool Options::Load() 
{
	if (std::filesystem::exists(FilePath))
	{
		std::ifstream file;
		file.open(FilePath);
		bool state = file.is_open();
		if (state)
		{
			nlohmann::json j = nlohmann::json::parse(file);
			FileTypes = j["file types"];
			PathFilters = j["path filters"];
		}
		file.close();
		return state;
	}
	return false;
}

void Options::Save()
{
	nlohmann::json j;
	j["file types"] = FileTypes;
	j["path filters"] = PathFilters;

	std::ofstream file(FilePath);
	file << j.dump(4) << std::endl;
	file.close();
}