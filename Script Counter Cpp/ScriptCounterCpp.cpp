#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <filesystem>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std; using namespace std::chrono; using namespace std::this_thread; using namespace std::filesystem;

int main() {
	cout << "Please input the root directory of the script folder" << endl;
	path p;
	cin >> p;
	if (p.is_absolute()) {
		auto start = system_clock::now();
		list<path> files;

		for (const auto& file : recursive_directory_iterator(p)) {
			if (file.path().extension() == ".cpp" || file.path().extension() == ".hpp" || file.path().extension() == ".h") {
				files.push_back(file.path());
			}
		}

		cout << "Found " << files.size() << " script files" << endl;

		long lines = 0;
		long characters = 0;

		for (auto& file : files) {
			fstream fileRead;
			fileRead.open(file, ios::in);
			if (fileRead.is_open()) {
				string tp;
				while (getline(fileRead, tp)) {
					lines++;
					characters += tp.length();
				}
			}
		}

		cout << "Total line count " << lines << endl;
		cout << "Total character count " << characters << endl;

		auto end = system_clock::now();

		duration<double> elapsed_seconds = end - start;
		
		cout << "Elapsed time: " << elapsed_seconds << endl;
		
		sleep_for(seconds(10));
		return 0;
	}
	cout << "The path is not rooted" << endl;
	sleep_for(seconds(10));
	return 1;
}