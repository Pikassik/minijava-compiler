#include <Driver/driver.hh>

#include <iostream>
#include <cassert>

int main(int argc, char** argv) {
  Driver driver;

  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string_view("-t")) {
      driver.SetTraceParsing(true);
    }

    if (argv[i] == std::string_view("-d")) {
      driver.SetDump(true);
    }
  }

  for (int i = 1; i < argc; ++i) {
    if (!(std::string_view(argv[i]) == std::string_view("-t") ||
          std::string_view(argv[i]) == std::string("-d"))) {
      return driver.Drive(argv[i]);
    }
  }

  return 1;
}