#include "YamlParser.h"

YamlParser::YamlParser(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open YAML file: " + filename);
    }

    std::string line;
    std::string currentKey;
    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line[0] == '#') {
            continue; // Ignorera tomma rader och kommentarer
        }

        // Kontrollera om raden innehåller en nyckel-värde-par
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            currentKey = trim(line.substr(0, colonPos));
            std::string value = trim(line.substr(colonPos + 1));

            if (value.empty()) {
                // Nästa rader innehåller en lista
                std::vector<std::string> listValues;
                while (std::getline(file, line) && (line = trim(line))[0] == '-') {
                    listValues.push_back(trim(line.substr(1)));
                }
                data[currentKey] = listValues;
            } else {
                data[currentKey] = value;
            }
        }
    }
}

std::string YamlParser::getString(const std::string& key) const {
    if (data.find(key) != data.end() && std::holds_alternative<std::string>(data.at(key))) {
        return std::get<std::string>(data.at(key));
    }
    throw std::runtime_error("Key not found or not a string: " + key);
}

int YamlParser::getInt(const std::string& key) const {
    std::string value = getString(key);
    try {
        return std::stoi(value);
    } catch (...) {
        throw std::runtime_error("Value is not an integer: " + key);
    }
}

std::vector<std::string> YamlParser::getStringList(const std::string& key) const {
    if (data.find(key) != data.end() && std::holds_alternative<std::vector<std::string>>(data.at(key))) {
        return std::get<std::vector<std::string>>(data.at(key));
    }
    throw std::runtime_error("Key not found or not a list: " + key);
}