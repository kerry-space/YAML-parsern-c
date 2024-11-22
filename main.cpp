#include "YamlParser.h"

int main() {
    try {
        YamlParser parser("example.yaml");

        std::string title = parser.getString("title");
        int year = parser.getInt("year");
        std::vector<std::string> authors = parser.getStringList("authors");

        std::cout << "Title: " << title << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "Authors:" << std::endl;
        for (const auto& author : authors) {
            std::cout << "- " << author << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}