#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <ctime>
#include "Options.h"

int main()
{
	Options options;
	if (options.IsEmpty())
	{
		options.FileTypes.push_back(".cpp");
		options.FileTypes.push_back(".hpp");
		options.FileTypes.push_back(".h");
		options.Save();
	}
	std::cout << "Please input the root directory of the script folder" << std::endl;
	std::filesystem::path p;
	std::cin >> p;
	if (p.is_absolute())
	{
		options.Load();
		std::list<std::filesystem::path> files;

		for (const auto& file : std::filesystem::recursive_directory_iterator(p))
		{
			for (const auto& type : options.FileTypes)
			{
				if (file.path().extension() == type)
				{
					files.push_back(file.path());
					break;
				}
			}
		}

		std::list<std::filesystem::path> filteredFiles;

		for (const auto& fileP : files)
		{
			if (options.PathFilters.empty()) 
			{
				filteredFiles.push_back(fileP);
			}
			else
			{
				bool validPath = true;

				for (const auto& filter : options.PathFilters)
				{
					if (fileP.string().find(filter) != std::string::npos)
					{
						validPath = false;
						break;
					}
				}

				if (validPath)
				{
					filteredFiles.push_back(fileP);
				}
			}
		}

		std::cout << "Found " << filteredFiles.size() << " script files" << std::endl;

		auto start = std::chrono::system_clock::now();

		long lines = 0;
		long characters = 0;

		for (const auto& file : filteredFiles)
		{
			std::fstream fileRead;
			fileRead.open(file, std::ios::in);
			if (fileRead.is_open()) {
				std::string tp;
				while (getline(fileRead, tp)) {
					lines++;
					characters += tp.length();
				}
			}
		}

		std::cout << "Total line count " << lines << std::endl;
		std::cout << "Total character count " << characters << std::endl;

		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsedTime = end - start;

		std::cout << "Elapsed time: " << elapsedTime << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(10));

		return 0;
	}
	return 1;
}