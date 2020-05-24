#include "driver.hh"
#include <Parser/parser.hh>
#include <Visitors/Dumper.h>
#include <Visitors/Interpreter.h>
#include <Visitors/SymbolTableBuilder.h>
#include <Visitors/Typer.h>
#include <Visitors/IRTBuilder.h>
#include <IR/include.h>

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <IR/visitors/DoubleCallEliminateVisitor.h>
#include <IR/visitors/EseqEliminationVisitor.h>

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

void Driver::SetBuildIRT(bool flag) {
  build_irt = flag;
}

int Driver::Drive(const std::string& f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  parser();
  scan_end();

  if (program) {
    if (dump) {
      PrintDump();
    } else if (build_irt) {


      auto table = MakeProgramTable(*program);
      SetTypes(*program, table);

      auto irt_tree = BuildIRT(table, program);

      if (call_elim) {
        IRT::DoubleCallEliminateVisitor dce_visitor;
        for (auto& [funcname, func]: irt_tree) {
          func = dce_visitor.GetTree(func);
        }
      }

      if (eseq_elim) {
        IRT::EseqEliminationVisitor ee_visitor;
        for (auto& [funcname, func]: irt_tree) {
          func = ee_visitor.GetTree(func);
        }
      }

      if (linear) {
        IRT::LinearizationVisitor l_visitor;
        for (auto& [funcname, func]: irt_tree) {
          func = l_visitor.GetTree(func);
        }
      }

      IRT::PrintVisitor print_visitor(file + ".ir.txt");
      for (auto&& [funcname, func]: irt_tree) {
        func->Accept(print_visitor);
      }

    } else {
      Interpret(*program);
    }

    return 0;
  }

  return 1;
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

void Driver::SetCallElim(bool flag) {
  call_elim = flag;
}

void Driver::SetEseqElim(bool flag) {
  eseq_elim = flag;
}

void Driver::SetLinear(bool flag) {
  linear = flag;
}
