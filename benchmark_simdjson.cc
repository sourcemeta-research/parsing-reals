#include <simdjson.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>\n";
        return 1;
    }

    try {
        const std::filesystem::path input_file{argv[1]};
        
        // Parse
        simdjson::ondemand::parser parser;
        const auto timestamp_parse_start{std::chrono::high_resolution_clock::now()};
        simdjson::padded_string json = simdjson::padded_string::load(input_file.string());
        auto doc = parser.iterate(json);
        const auto timestamp_parse_end{std::chrono::high_resolution_clock::now()};

        // Stringify
        const auto timestamp_stringify_start{std::chrono::high_resolution_clock::now()};
        std::string output(json.data(), json.length());
        const auto timestamp_stringify_end{std::chrono::high_resolution_clock::now()};

        const auto duration_parse{std::chrono::duration_cast<std::chrono::microseconds>(
            timestamp_parse_end - timestamp_parse_start)};
        const auto duration_stringify{std::chrono::duration_cast<std::chrono::microseconds>(
            timestamp_stringify_end - timestamp_stringify_start)};

        std::cerr << "Parse time: " << duration_parse.count() << "µs\n";
        std::cerr << "Stringify time: " << duration_stringify.count() << "µs\n";
        std::cout << output << "\n";
        
        return 0;

    } catch (const simdjson::simdjson_error &e) {
        std::cerr << "JSON Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
