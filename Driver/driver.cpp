#include "driver.hh"
#include <Parser/parser.hh>
#include <Visitors/Dumper.h>
#include <Visitors/Interpreter.h>
#include <SymbolTables/SymbolTableBuilder.h>
#include <Visitors/Typer.h>

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

Driver::Driver()
    : trace_parsing(false)
    , trace_scanning(false)
    , scanner(*this)
    , parser(scanner, *this) {
}

void Driver::SetTraceParsing(bool flag) {
  trace_parsing = flag;
}

void Driver::SetDump(bool flag) {
  dump = flag;
}

int Driver::Drive(const std::string& f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  scan_end();

  if (program) {
    if (dump) {
      PrintDump();
    }

    auto table = MakeProgramTable(*program);
    SetTypes(program, table);
    //Interpret(*program);
  }

  return res;
}

void Driver::scan_begin() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    if (!stream.is_open()) {
      std::cout << "failure while opening file " + file << std::endl;
      std::exit(1);
    }
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end() {
  stream.close();
}

void Driver::PrintDump() {
  Dumper dumper(program, file + ".gv");
  dumper.Dump();
  pid_t pid = fork();
  if (pid == 0) {
    execlp("dot", "dot", "-Tpng",
           (file + ".gv").c_str(), "-o", (file + ".png").c_str(), nullptr);
  }
  wait(NULL);
}
