#pragma once

#include "Parser/scanner.h"
#include "Parser/parser.hh"
#include <Nodes/Nodes.h>

#include <map>
#include <string>
#include <fstream>


class Driver {
 public:
    Driver();
    std::map<std::string, int> variables;
    std::shared_ptr<node::Program> program;
    int parse(const std::string& f);
    std::string file;
    bool trace_parsing;
    bool dump;

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
