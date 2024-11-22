#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

class YamlParser {
private:
    std::unordered_map<std::string, std::variant<std::string, std::vector<std::string>>> data;

    // Hjälpmetod för att trimma whitespace
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

public:
    YamlParser(const std::string& filename);
    std::string getString(const std::string& key) const;
    int getInt(const std::string& key) const;
    std::vector<std::string> getStringList(const std::string& key) const;
};

#endif // YAML_PARSER_H