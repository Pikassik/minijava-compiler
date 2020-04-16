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
  std::shared_ptr<node::Program> program;
  int Drive(const std::string& f);
  std::string file;
  bool trace_parsing = false;
  bool dump = false;

  void SetTraceParsing(bool flag);
  void SetDump(bool flag);
  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
 private:
  void PrintDump();

  std::ifstream stream;
};
