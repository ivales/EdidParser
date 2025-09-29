#ifndef __WRITE_MAP_TO_FILE_H_
#define __WRITE_MAP_TO_FILE_H_

#include <map>
#include <string>

std::string parse_filename_to_model(const std::string& filename, const char& splitter);
void write_map_to_csv(
    const std::string& filename,
    const std::map<std::string, std::map<std::string, std::string>>& data);

#endif
