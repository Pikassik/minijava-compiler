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
  void SetTraceParsing(bool flag);
  void SetDump(bool flag);
  void SetBuildIRT(bool flag);
  void SetCallElim(bool flag);
  void SetEseqElim(bool flag);
  void SetLinear(bool flag);
  void scan_begin();
  void scan_end();

  bool trace_scanning;
  yy::location location;
  yy::parser::symbol_type symbol;

  friend class Scanner;
  Scanner scanner;
  yy::parser parser;
 private:
  void PrintDump();
  //todo switch to enum
  bool trace_parsing = false;
  bool dump = false;
  bool build_irt = false;
  bool call_elim = false;
  bool eseq_elim = false;
  bool linear = false;

  std::ifstream stream;
};
