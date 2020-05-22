#include "../IRTBuilder.h"

using namespace IRT;
using std::make_shared;
using std::shared_ptr;

static constexpr int kWordSize = 4;

std::unordered_map<std::string, std::shared_ptr<IRT::Statement>>
BuildIRT(std::shared_ptr<ProgramTable>  program_table_,
         std::shared_ptr<node::Program> program) {
  IRTBuilder builder(std::move(program_table_));
  builder.Accept(*program);
  return std::move(builder.method_trees_);
}

IRTBuilder::IRTBuilder(std::shared_ptr<ProgramTable> program_table)
    : program_table_(std::move(program_table)) {
}

void IRTBuilder::Visit(node::Node&) {
  // pass
}

void IRTBuilder::Visit(node::Class& node) {
  current_class_ = program_table_->GetClass(node.identifier);
  current_class_node_ =
    std::dynamic_pointer_cast<node::Class>(node.shared_from_this());

  for (auto&& method: node.methods) {
    method->Accept(*this);
  }
}

void IRTBuilder::Visit(node::Formal& node) {
  // pass
}

void IRTBuilder::Visit(node::MethodDeclaration& node) {
  current_method_node_ =
    std::dynamic_pointer_cast<node::MethodDeclaration>(node.shared_from_this());

  auto method_label =
    current_class_node_->identifier + "." + current_method_node_->identifier;

  current_frame_ =
    make_shared<FrameTranslator>(current_class_, node.identifier);

  auto statements_ir = Accept(*node.scope);

  if (statements_ir) {
    tos_value_ = make_shared<IRT::StatementWrapper>(
      make_shared<IRT::SeqStatement>(
        make_shared<IRT::LabelStatement>(IRT::Label(method_label)),
        statements_ir->ToStatement()
      )
    );
  } else {
    // generating return 0
    tos_value_ = make_shared<IRT::StatementWrapper>(
      make_shared<IRT::SeqStatement>(
        make_shared<IRT::LabelStatement>(IRT::Label(method_label)),
        make_shared<IRT::MoveStatement>(
          current_frame_->GetReturnValueAddress()->ToExpression(),
          make_shared<IRT::ConstExpression>(0)
        )
      )
    );
  }

  method_trees_[method_label] = tos_value_->ToStatement();
}

void IRTBuilder::Visit(node::Type& node) {
  throw;
}

void IRTBuilder::Visit(node::VarDeclaration& node) {
  tos_value_ = nullptr;
}

void IRTBuilder::Visit(node::Add& node) {
  Visit(node, BinaryOperatorType::PLUS);
}

void IRTBuilder::Visit(node::And& node) {
  Visit(node, BinaryOperatorType::AND);
}

void IRTBuilder::Visit(node::At& node) {
  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<MemExpression>(
      make_shared<BinopExpression>(
        BinaryOperatorType::PLUS,
        Accept(*node.array)->ToExpression(),
        make_shared<BinopExpression>(
          BinaryOperatorType::MUL,
          Accept(*node.index)->ToExpression(),
          make_shared<ConstExpression>(kWordSize)
        )
      )
    )
  );
}

void IRTBuilder::Visit(node::Div& node) {
  Visit(node, BinaryOperatorType::DIV);
}

void IRTBuilder::Visit(node::Equals& node) {
  Visit(node, LogicOperatorType::EQ);
}

void IRTBuilder::Visit(node::Identifier& node) {
  auto address = current_frame_->GetAddress(node.identifier);
  tos_value_ = make_shared<ExpressionWrapper>(address->ToExpression());
}

void IRTBuilder::Visit(node::Length& node) {
  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<MemExpression>(
      make_shared<BinopExpression>(
        BinaryOperatorType::MINUS,
        Accept(*node.array_expression)->ToExpression(),
        make_shared<ConstExpression>(kWordSize)
      )
    )
  );
}

void IRTBuilder::Visit(node::Less& node) {
  Visit(node, LogicOperatorType::LT);
}

void IRTBuilder::Visit(node::MethodInvocation& node) {
  auto irt_expressions = make_shared<IRT::ExpressionList>();

  irt_expressions->Add(current_frame_->GetThis()->ToExpression());
  for (auto&& arg: node.arguments) {
    irt_expressions->Add(Accept(*arg)->ToExpression());
  }

  auto method_label =
    node.class_expression->type->identifier + "." + node.method_identifier;

  tos_value_ = make_shared<IRT::ExpressionWrapper>(
    make_shared<IRT::CallExpression>(
      make_shared<IRT::NameExpression>(IRT::Label(method_label)),
      irt_expressions
    )
  );
}

void IRTBuilder::Visit(node::More& node) {
  Visit(node, LogicOperatorType::GT);
}

void IRTBuilder::Visit(node::Mul& node) {
  Visit(node, BinaryOperatorType::MUL);
}

void IRTBuilder::Visit(node::New& node) {
  int class_size = program_table_->GetClass(node.type->identifier)->SizeOf();

  auto irt_expressions = make_shared<IRT::ExpressionList>();

  irt_expressions->Add(make_shared<ConstExpression>(class_size));

  tos_value_ = make_shared<IRT::ExpressionWrapper>(
    make_shared<IRT::CallExpression>(
      make_shared<IRT::NameExpression>(IRT::Label("malloc")),
      irt_expressions
    )
  );
}

void IRTBuilder::Visit(node::NewArray& node) {
  auto irt_expressions = make_shared<IRT::ExpressionList>();

  auto size_expression = Accept(*node.size_expression)->ToExpression();
  auto size = make_shared<BinopExpression>(
    BinaryOperatorType::MUL,
    size_expression,
    make_shared<ConstExpression>(kWordSize)
  );

  irt_expressions->Add(size);

  // malloc is abstract function here,
  // need to be implemented as library function
  tos_value_ = make_shared<IRT::ExpressionWrapper>(
    make_shared<BinopExpression>(
      BinaryOperatorType::PLUS,
      make_shared<IRT::CallExpression>(
        make_shared<IRT::NameExpression>(IRT::Label("malloc")),
        irt_expressions
      ),
      make_shared<ConstExpression>(kWordSize)
    )
  );
}

void IRTBuilder::Visit(node::Not& node) {
  auto wrapper = Accept(*node.argument);

  tos_value_ = make_shared<NegateConditionalWrapper>(
    wrapper
  );
}

void IRTBuilder::Visit(node::Number& node) {
  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<IRT::ConstExpression>(node.number)
  );
}

void IRTBuilder::Visit(node::Percent& node) {
  Visit(node, BinaryOperatorType::PERC);
}

void IRTBuilder::Visit(node::Subtract& node) {
  Visit(node, BinaryOperatorType::MINUS);
}

void IRTBuilder::Visit(node::This& node) {
  tos_value_ = make_shared<ExpressionWrapper>(
    current_frame_->GetThis()->ToExpression()
  );
}

void IRTBuilder::Visit(node::Assert& node) {
  tos_value_ = make_shared<IRT::ExpressionWrapper>(
    make_shared<IRT::CallExpression>(
      make_shared<IRT::NameExpression>(IRT::Label("terminate")),
      nullptr
    )
  );
}

void IRTBuilder::Visit(node::Assign& node) {
  auto var_expression =
    current_frame_->GetAddress(node.lvalue->identifier)->ToExpression();

  auto rvalue = Accept(*node.expression);

  if (node.lvalue->index_expression) {
    auto index_expression =
      Accept(*node.lvalue->index_expression)->ToExpression();
    var_expression = make_shared<BinopExpression>(
      BinaryOperatorType::PLUS,
      make_shared<MemExpression>(var_expression),
      index_expression
    );
  }

  tos_value_ = make_shared<StatementWrapper>(
    make_shared<MoveStatement>(
      var_expression,
      rvalue->ToExpression()
    )
  );
}

void IRTBuilder::Visit(node::If& node) {
  auto if_cond_expression = Accept(*node.condition);
  auto true_stmt = Accept(*node.then_statement);
  auto false_stmt = Accept(*node.else_statement);

  Label label_true;
  Label label_false;
  Label label_join;

  shared_ptr<Statement> suffix = make_shared<LabelStatement>(label_join);

  Label* result_true = &label_join;
  Label* result_false = &label_join;

  if (false_stmt) {
    result_false = &label_false;
    suffix = make_shared<SeqStatement>(
      make_shared<LabelStatement>(label_false),
      make_shared<SeqStatement>(false_stmt->ToStatement(), suffix)
    );

    if (true_stmt) {
      suffix = make_shared<SeqStatement>(
        make_shared<JumpStatement>(label_join),
        suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = make_shared<SeqStatement>(
      make_shared<LabelStatement>(label_true),
      make_shared<SeqStatement>(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = make_shared<StatementWrapper>(
    make_shared<SeqStatement>(
      if_cond_expression->ToConditional(*result_true, *result_false),
      suffix
    )
  );
}

void IRTBuilder::Visit(node::Lvalue& node) {
  // pass
  // not visited
}

void IRTBuilder::Visit(node::Print& node) {
  auto irt_expressions = make_shared<ExpressionList>();
  irt_expressions->Add(Accept(*node.print_expression)->ToExpression());

  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<CallExpression>(
      make_shared<IRT::NameExpression>(IRT::Label("print")),
      irt_expressions
    )
  );
}

void IRTBuilder::Visit(node::Return& node) {
  auto return_expr = Accept(*node.return_expression);
  tos_value_ = make_shared<StatementWrapper>(
    make_shared<MoveStatement>(
      current_frame_->GetReturnValueAddress()->ToExpression(),
      return_expr->ToExpression()
    )
  );
}

void IRTBuilder::Visit(node::Scope& node) {
  auto guard = current_frame_->GetGuard();

  if (node.statements.empty()) {
    tos_value_ = nullptr;
  } else if (node.statements.size() == 1) {
    tos_value_ = Accept(*node.statements[0]);
  } else {
    std::vector<std::shared_ptr<IRT::Statement>> statements;
    statements.reserve(node.statements.size());

    for (auto&& stmt_v: node.statements) {
      auto stmt = Accept(*stmt_v);
      if (stmt) {
        statements.push_back(stmt->ToStatement());
      }
    }

    std::shared_ptr<IRT::Statement> suffix = statements.back();

    for (int index = static_cast<int>(statements.size()) - 2; index >= 0; --index) {
      suffix = make_shared<IRT::SeqStatement>(
        statements[index],
        suffix
      );
    }

    tos_value_ = make_shared<StatementWrapper>(suffix);
  }
}

void IRTBuilder::Visit(node::While& node) {
  auto if_cond_expression = Accept(*node.condition);
  auto true_stmt = Accept(*node.then_statement);

  Label label_while;
  Label label_true;
  Label label_join;

  shared_ptr<Statement> suffix = make_shared<SeqStatement>(
    make_shared<JumpStatement>(label_while),
    make_shared<LabelStatement>(label_join)
  );

  if (true_stmt) {
    suffix = make_shared<SeqStatement>(
      true_stmt->ToStatement(),
      suffix
    );
  }

  tos_value_ = make_shared<StatementWrapper>(
    make_shared<SeqStatement>(
      make_shared<LabelStatement>(label_while),
      make_shared<SeqStatement>(
        if_cond_expression->ToConditional(label_true, label_join),
        make_shared<SeqStatement>(
          make_shared<LabelStatement>(label_true),
          suffix
        )
      )
    )
  );
}

void IRTBuilder::Visit(node::Program& node) {
  for (auto&& class_v: node.classes) {
    class_v->Accept(*this);
  }
}

void IRTBuilder::Visit(node::Or& node) {
  Visit(node, BinaryOperatorType::OR);
}

void IRTBuilder::Visit(node::BooleanLiteral& node) {
  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<IRT::ConstExpression>(node.is_true)
  );
}

void IRTBuilder::Visit(node::BinaryOp& node, BinaryOperatorType type) {
  auto lhs = Accept(*node.lhvalue);
  auto rhs = Accept(*node.rhvalue);

  tos_value_ = make_shared<ExpressionWrapper>(
    make_shared<BinopExpression>(
      type,
      lhs->ToExpression(),
      rhs->ToExpression()
    )
  );
}

void IRTBuilder::Visit(node::BinaryOp& node, LogicOperatorType type) {
  auto lhs = Accept(*node.lhvalue);
  auto rhs = Accept(*node.rhvalue);

  tos_value_ = make_shared<RelativeConditionalWrapper>(
    type,
    lhs->ToExpression(),
    rhs->ToExpression()
  );
}
