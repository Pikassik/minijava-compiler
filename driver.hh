#pragma once

#include "scanner.h"
#include "parser.hh"

#include <map>
#include <string>
#include <fstream>


class Driver {
 public:
    Driver();
    std::map<std::string, int> variables;
    std::map<std::string, std::vector<int>> arrays;
    int parse(const std::string& f);
    std::string file;
    bool trace_parsing;

    void scan_begin();
    void scan_end();

    bool trace_scanning;
    yy::location location;

    friend class Scanner;
    Scanner scanner;
    yy::parser parser;
 private:
    std::ifstream stream;

};
