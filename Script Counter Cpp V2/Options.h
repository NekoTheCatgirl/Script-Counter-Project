#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

class Options
{
public:
	std::vector<std::string> FileTypes;
	std::vector<std::string> PathFilters;

	bool IsEmpty();
	bool Load();
	void Save();

private:
	const char* FilePath = "Options.json";
};

