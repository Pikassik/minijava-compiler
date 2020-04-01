#include <iostream>
#include <Driver/driver.hh>

int main(int argc, char** argv) {
    int result = 0;
    Driver driver;

    for (int i = 1; i < argc; ++i) {
        if (argv[i] == std::string_view("-t")) {
            // trace
            driver.trace_parsing = true;
        } else if (argv[i] == std::string_view("-d")) {
            // dump
            driver.dump = true;
        } else {
            driver.parse(argv[i]);
            break;
        }
    }

    return result;
}