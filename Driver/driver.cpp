#include "driver.hh"
#include "Parser/parser.hh"
#include <Visitors/Dumper.h>
#include <Visitors/Interpreter.h>

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

#include <chrono>

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}


int Driver::parse(const std::string& f) {
    file = f;
    location.initialize(&file);
    scan_begin();
    parser.set_debug_level(trace_parsing);
    int res = parser();
    scan_end();

    if (program) {
      if (dump) {
        Dumper dumper(program, f + ".gv");
        dumper.Dump();
        pid_t pid = fork();
        if (pid == 0) {
          execlp("dot", "dot", "-Tpng",
                 (f + ".gv").c_str(), "-o", (f + ".png").c_str(), nullptr);
        }
        wait(NULL);
      }

      Interpret(*program);
    }

    return res;
}

void Driver::scan_begin() {
    scanner.set_debug(trace_scanning);
  if (file.empty () || file == "-") {
  } else {
    stream.open(file);
    if (!stream.is_open()) {
      std::cout << "failure while opening file " + file << std::endl;
      std::exit(1);
    }
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end()
{
    stream.close();
}

