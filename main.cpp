#include <Driver/driver.hh>

#include <iostream>
#include <string_view>
#include <cassert>

int main(int argc, char** argv) {
  using namespace std::string_view_literals;
  Driver driver;

  for (int i = 1; i < argc; ++i) {
    if (argv[i] == "-t"sv) {
      driver.SetTraceParsing(true);
    }

    if (argv[i] == "-d"sv) {
      driver.SetDump(true);
    }

    if (argv[i] == "-irt"sv) {
      driver.SetBuildIRT(true);
    }
  }

  for (int i = 1; i < argc; ++i) {
    if (!(argv[i] == "-t"sv ||
          argv[i] == "-d"sv ||
          argv[i] == "-irt"sv)) {
      return driver.Drive(argv[i]);
    }
  }

  return 1;
}