#include "EseqEliminationVisitor.h"
#include "BaseElements.h"

#include <unordered_set>
#include <algorithm>

namespace IRT {

using std::shared_ptr;
using std::make_shared;

bool IsExpression(BaseElement& elem) {
  return dynamic_cast<Expression*>(&elem) != nullptr;
}

bool IsConst(BaseElement& elem) {
  return dynamic_cast<ConstExpression*>(&elem) != nullptr;
}

bool IsName(BaseElement& elem) {
  return dynamic_cast<NameExpression*>(&elem) != nullptr;
}

bool IsSeqStatement(Statement& stmt) {
  return dynamic_cast<SeqStatement*>(&stmt) != nullptr;
}

bool IsEseqExpression(BaseElement& elem) {
  return dynamic_cast<EseqExpression*>(&elem) != nullptr;
}

bool AreCommute(Statement& stmt, Expression& expr) {
  return
    (IsExpression(stmt) &&
     IsConst(*dynamic_cast<ExpStatement*>(&stmt)->GetExpression())) ||
    IsConst(expr) ||
    IsName(expr);
}


void EseqEliminationVisitor::Visit(ExpStatement& stmt) {
  auto expr = Accept(*stmt.GetExpression()).expression_;
  if (IsEseqExpression(*expr)) {
    tos_value_.statement_ =
      std::dynamic_pointer_cast<EseqExpression>(expr)->statement_;
  } else {
    tos_value_.statement_ = make_shared<ExpStatement>(expr);
  }
}

void EseqEliminationVisitor::Visit(ConstExpression& const_expression) {
  tos_value_.expression_ = make_shared<ConstExpression>(const_expression.Value());
}

void EseqEliminationVisitor::Visit(JumpConditionalStatement& jump_conditional_statement) {
  auto lhs = Accept(*jump_conditional_statement.left_operand_).expression_;
  auto rhs = Accept(*jump_conditional_statement.right_operand_).expression_;

  tos_value_.statement_ = make_shared<JumpConditionalStatement>(
      jump_conditional_statement.operator_type_,
      lhs,
      rhs,
      jump_conditional_statement.label_true_,
      jump_conditional_statement.label_false_
  );
}
void EseqEliminationVisitor::Visit(MoveStatement& move_statement) {
  auto source = Accept(*move_statement.source_).expression_;
  auto target = Accept(*move_statement.target_).expression_;

  tos_value_.statement_ = make_shared<MoveStatement>(source, target);
}

void EseqEliminationVisitor::Visit(SeqStatement& seq_statement) {
  tos_value_.statement_ = make_shared<SeqStatement>(
    Accept(*seq_statement.first_statement_).statement_,
    Accept(*seq_statement.second_statement_).statement_
  );
}

void EseqEliminationVisitor::Visit(LabelStatement& label_statement) {
  tos_value_.statement_ = make_shared<LabelStatement>(label_statement.label_);
}

void EseqEliminationVisitor::Visit(BinopExpression& binop_statement) {
  auto op = binop_statement.operator_type_;
  auto lhs = Accept(*binop_statement.first_).expression_;
  auto rhs = Accept(*binop_statement.second_).expression_;
  if (IsEseqExpression(*lhs) && IsEseqExpression(*rhs)) {
    auto left_eseq = std::dynamic_pointer_cast<EseqExpression>(lhs);
    auto right_eseq = std::dynamic_pointer_cast<EseqExpression>(rhs);
    if (AreCommute(*right_eseq->statement_, *lhs)) {
      tos_value_.expression_ =
        make_shared<EseqExpression>(
          left_eseq->statement_,
          make_shared<EseqExpression>(
            right_eseq->statement_,
            make_shared<BinopExpression>(
              op,
              left_eseq->expression_,
              right_eseq->expression_)
          )
        );
    } else {
      Temporary t;
      tos_value_.expression_ =
        make_shared<EseqExpression>(
          left_eseq->statement_,
          make_shared<EseqExpression>(
            make_shared<MoveStatement>(
              make_shared<TempExpression>(t),
              left_eseq->expression_
            ),
            make_shared<EseqExpression>(
              right_eseq->statement_,
              make_shared<BinopExpression>(
                op,
                make_shared<TempExpression>(t),
                right_eseq->expression_
              )
            )
          )
        );
    }
  } else if (IsEseqExpression(*lhs)) {
    auto eseq = std::dynamic_pointer_cast<EseqExpression>(lhs);
    tos_value_.expression_ =
      make_shared<EseqExpression>(
        eseq->statement_,
        make_shared<BinopExpression>(
          op,
          eseq->expression_,
          rhs
        )
      );
  } else if (IsEseqExpression(*rhs)) {
    auto eseq = std::dynamic_pointer_cast<EseqExpression>(rhs);
    if (AreCommute(*eseq->statement_, *lhs)) {
      tos_value_.expression_ =
        make_shared<EseqExpression>(
          eseq->statement_,
          make_shared<BinopExpression>(op, lhs, eseq->expression_)
        );
    } else {
      Temporary t;
      tos_value_.expression_ =
        make_shared<EseqExpression>(
          make_shared<MoveStatement>(
            make_shared<TempExpression>(t),
            lhs
          ),
          make_shared<EseqExpression>(
            eseq->statement_,
            make_shared<BinopExpression>(
              op,
              make_shared<TempExpression>(t),
              eseq->expression_
            )
          )
        );
    }
  } else {
    tos_value_.expression_ = make_shared<BinopExpression>(op, lhs, rhs);
  }
}

void EseqEliminationVisitor::Visit(TempExpression& temp_exression) {
  tos_value_.expression_ = make_shared<TempExpression>(temp_exression.temporary_);
}

void EseqEliminationVisitor::Visit(MemExpression& mem_expression) {
  auto expr = Accept(*mem_expression.expression_).expression_;

  if (IsEseqExpression(*expr)) {
    auto eseq = std::dynamic_pointer_cast<EseqExpression>(expr);
    tos_value_.expression_ =
      std::make_shared<EseqExpression>(
        eseq->statement_,
        make_shared<MemExpression>(eseq->expression_)
      );
  } else {
    tos_value_.expression_ = make_shared<MemExpression>(expr);
  }
}

void EseqEliminationVisitor::Visit(JumpStatement& jump_statement) {
  tos_value_.statement_ = make_shared<JumpStatement>(
    jump_statement.label_
  );
}

void EseqEliminationVisitor::Visit(CallExpression& call_expression) {
  auto func = Accept(*call_expression.function_name_).expression_;
  auto expression_list = Accept(*call_expression.args_).expression_list_;

  using T = decltype(expression_list->expressions_[0]);
  auto eseq_it = std::find_if(expression_list->expressions_.begin(),
                              expression_list->expressions_.end(),
                              [&] (const std::shared_ptr<Expression>& ptr){
    return IsEseqExpression(*ptr);
  });

  int eseq_index =
    eseq_it == expression_list->expressions_.end() ?
    - 1 :
    eseq_it - expression_list->expressions_.begin();

  if (eseq_index == -1) {

    if (IsEseqExpression(*call_expression.function_name_)) {
      auto func_eseq = std::dynamic_pointer_cast<EseqExpression>(func);

      tos_value_.expression_ =
        make_shared<EseqExpression>(
          func_eseq->statement_,
          make_shared<CallExpression>(func_eseq->expression_, expression_list)
        );

    } else {
      tos_value_.expression_ =
        make_shared<CallExpression>(func, expression_list);
    }
    return;
  }

  auto eseq =
    std::dynamic_pointer_cast<EseqExpression>(
      expression_list->expressions_[eseq_index]
    );

  std::unordered_set<size_t> noncommute;

  for (int i = 0; i < eseq_index - 1; ++i) {
    if (!AreCommute(*eseq->statement_, *expression_list->expressions_[i])) {
      noncommute.insert(i);
    }
  }

  auto temporary_statements = eseq->statement_;

  int size = (int)noncommute.size() - 1;

  std::vector<Temporary> temporaries(size >= 0 ? size : 0);

  for (int i = eseq_index; i >= 0; --i) {
    if (noncommute.find(i) != noncommute.end()) {
      temporary_statements =
        make_shared<SeqStatement>(
          make_shared<MoveStatement>(
            make_shared<TempExpression>(temporaries[size--]),
            expression_list->expressions_[i]),
          temporary_statements
        );
    }
  }

  size = 0;

  auto new_expression_list = make_shared<ExpressionList>();

  for (size_t i = 0; i < expression_list->expressions_.size(); ++i) {
    if (i == eseq_index) {
      new_expression_list->Add(eseq->expression_);
    } else {
      if (noncommute.find(i) != noncommute.end()) {
        new_expression_list->Add(make_shared<TempExpression>(temporaries[size++]));
      } else {
        new_expression_list->Add(expression_list->expressions_[i]);
      }
    }
  }

  if (IsEseqExpression(*call_expression.function_name_)) {
    auto func_eseq = std::dynamic_pointer_cast<EseqExpression>(func);
    tos_value_.expression_ =
      make_shared<EseqExpression>(
        func_eseq->statement_,
        make_shared<EseqExpression>(
          temporary_statements,
          make_shared<CallExpression>(
            func_eseq->expression_,
            new_expression_list
          )
        )
      );
  } else {
    tos_value_.expression_ =
      make_shared<EseqExpression>(
        temporary_statements,
        make_shared<CallExpression>(
          func,
          new_expression_list
        )
      );
  }
}
void EseqEliminationVisitor::Visit(ExpressionList& expression_list) {
  auto expression_list_ = make_shared<ExpressionList>();

  for (auto&& expression: expression_list.expressions_) {
    expression_list_->Add(Accept(*expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;
}

void EseqEliminationVisitor::Visit(NameExpression& name_expression) {
  tos_value_.expression_ = make_shared<NameExpression>(name_expression.label_);
}

void EseqEliminationVisitor::Visit(EseqExpression& eseq_expression) {
  // eseq union

  auto stmt = Accept(*eseq_expression.statement_).statement_;
  auto expr = Accept(*eseq_expression.expression_).expression_;

  if (IsEseqExpression(*expr)) {
    auto eseq = std::dynamic_pointer_cast<EseqExpression>(expr);
    tos_value_.expression_ =
      make_shared<EseqExpression>(
        make_shared<SeqStatement>(
          stmt,
          eseq->statement_
        ),
        eseq->expression_
      );
  } else {
    tos_value_.expression_ = make_shared<EseqExpression>(stmt, expr);
  }

}

std::shared_ptr<Statement>
EseqEliminationVisitor::GetTree(std::shared_ptr<Statement> func) {
  return Accept(*func).statement_;
}

}