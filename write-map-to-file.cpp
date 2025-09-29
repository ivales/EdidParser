#include <iostream>
#include <fstream>
#include <set>

#include "write-map-to-file.h"

std::string parse_filename_to_model(const std::string& filename, const char& splitter) {
	size_t firstPos = filename.find(splitter);

    if (firstPos != std::string::npos) {
        size_t secondPos = filename.find(splitter, firstPos + 1);

        if (secondPos != std::string::npos) {
            size_t thirdPos = filename.find(splitter, secondPos+1);
            if (thirdPos != std::string::npos) {
                return filename.substr(0, thirdPos);
            } else {
                return filename.substr(0, secondPos) + "_UnknownInput";
            }
        } else {
            return filename.substr(0, firstPos) + "_UnknownModel_UnknownInput";
        }
    } else {
        return "UnknownBrand_UnknownModel_UnknownInput";
    }
}

void write_map_to_csv(
    const std::string& filename,
    const std::map<std::string, std::map<std::string, std::string>>& data)
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing\n";
        return;
    }

    std::set<std::string> columns;
    for (const auto& row_pair : data) {
        for (const auto& col_pair : row_pair.second) {
            columns.insert(col_pair.first);
        }
    }

    file << "Модель ТВ";
    for (const auto& col_name : columns) {
        file << "," << col_name;
    }
    file << "\n";

    for (const auto& row_pair : data) {
        file << row_pair.first;

        for (const auto& col_name : columns) {
            file << ",";
            auto it = row_pair.second.find(col_name);
            if (it != row_pair.second.end()) {
                file << it->second;
            }
        }
        file << "\n";
    }

    file.close();
}
