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

    if (argv[i] == "-call"sv) {
      driver.SetCallElim(true);
    }

    if (argv[i] == "-eseq"sv) {
      driver.SetEseqElim(true);
    }

    if (argv[i] == "-lin"sv) {
      driver.SetLinear(true);
    }
  }

  for (int i = 1; i < argc; ++i) {
    if (!(argv[i] == "-t"sv ||
          argv[i] == "-d"sv ||
          argv[i] == "-irt"sv ||
          argv[i] == "-call"sv ||
          argv[i] == "-eseq"sv ||
          argv[i] == "-lin"sv)) {
      return driver.Drive(argv[i]);
    }
  }

  return 1;
}