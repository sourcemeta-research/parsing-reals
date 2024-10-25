#include <sourcemeta/jsontoolkit/json.h>

#include <sstream>
#include <iostream>
#include <chrono>

int main(int, char **argv) {
  const std::filesystem::path input_file{argv[1]};
  auto stream{sourcemeta::jsontoolkit::read_file(input_file)};

  // Parse
  const auto timestamp_parse_start{std::chrono::high_resolution_clock::now()};
  const auto schema{sourcemeta::jsontoolkit::parse(stream)};
  const auto timestamp_parse_end{std::chrono::high_resolution_clock::now()};

  std::ostringstream output;

  // Stringify
  const auto timestamp_stringify_start{std::chrono::high_resolution_clock::now()};
  sourcemeta::jsontoolkit::stringify(schema, output);
  const auto timestamp_stringify_end{std::chrono::high_resolution_clock::now()};

  const auto duration_parse{std::chrono::duration_cast<std::chrono::milliseconds>(
      timestamp_parse_end - timestamp_parse_start)};
  const auto duration_stringify{std::chrono::duration_cast<std::chrono::milliseconds>(
      timestamp_stringify_end - timestamp_stringify_start)};

  std::cerr << "Parse time: " << duration_parse << "\n";
  std::cerr << "Stringify time: " << duration_stringify << "\n";

  std::cout << output.str() << "\n";
  return 0;
}
