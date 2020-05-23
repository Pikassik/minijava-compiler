#include "DoubleCallEliminateVisitor.h"
#include "BaseElements.h"

namespace IRT {

using std::shared_ptr;
using std::make_shared;

void DoubleCallEliminateVisitor::Visit(ExpStatement& stmt) {
  IrtStorage elements = Accept(*stmt.GetExpression());
  tos_value_.statement_ = make_shared<ExpStatement>(elements.expression_);
}

void DoubleCallEliminateVisitor::Visit(ConstExpression& const_expression) {
  tos_value_.expression_ = make_shared<ConstExpression>(const_expression.Value());
}

void DoubleCallEliminateVisitor::Visit(JumpConditionalStatement& jump_conditional_statement) {
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
void DoubleCallEliminateVisitor::Visit(MoveStatement& move_statement) {
  auto source = Accept(*move_statement.source_).expression_;
  auto target = Accept(*move_statement.target_).expression_;

  tos_value_.statement_ = make_shared<MoveStatement>(source, target);
}

void DoubleCallEliminateVisitor::Visit(SeqStatement& seq_statement) {
  auto first = Accept(*seq_statement.first_statement_).statement_;
  auto second = Accept(*seq_statement.second_statement_).statement_;

  tos_value_.statement_ = make_shared<SeqStatement>(
    first,
    second
  );
}


void DoubleCallEliminateVisitor::Visit(LabelStatement& label_statement) {
  tos_value_.statement_ = make_shared<LabelStatement>(label_statement.label_);
}

void DoubleCallEliminateVisitor::Visit(BinopExpression& binop_statement) {
  tos_value_.expression_ = make_shared<BinopExpression>(
    binop_statement.operator_type_,
    Accept(*binop_statement.first_).expression_,
    Accept(*binop_statement.second_).expression_
  );
}
void DoubleCallEliminateVisitor::Visit(TempExpression& temp_exression) {
  tos_value_.expression_ = make_shared<TempExpression>(temp_exression.temporary_);
}

void DoubleCallEliminateVisitor::Visit(MemExpression& mem_expression) {
  tos_value_.expression_ = make_shared<MemExpression>(
      Accept(*mem_expression.expression_).expression_
  );
}

void DoubleCallEliminateVisitor::Visit(JumpStatement& jump_statement) {
  tos_value_.statement_ = make_shared<JumpStatement>(
    jump_statement.label_
  );
}
void DoubleCallEliminateVisitor::Visit(CallExpression& call_expression) {
  auto func = Accept(*call_expression.function_name_).expression_;
  auto args = Accept(*call_expression.args_).expression_list_;

  Temporary temp;

  tos_value_.expression_ = make_shared<EseqExpression>(
    make_shared<MoveStatement>(
      make_shared<TempExpression>(temp),
      make_shared<CallExpression>(
        func,
        args
      )
    ),
    make_shared<TempExpression>(temp)
  );
}
void DoubleCallEliminateVisitor::Visit(ExpressionList& expression_list) {
  auto expression_list_ = make_shared<ExpressionList>();

  for (auto&& expression: expression_list.expressions_) {
    expression_list_->Add(Accept(*expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;

}

void DoubleCallEliminateVisitor::Visit(NameExpression& name_expression) {
  tos_value_.expression_ = make_shared<NameExpression>(name_expression.label_);
}

void DoubleCallEliminateVisitor::Visit(EseqExpression& eseq_expression) {
  auto stmt = Accept(*(eseq_expression.statement_)).statement_;
  auto expr = Accept(*eseq_expression.expression_).expression_;

  tos_value_.expression_ = make_shared<EseqExpression>(stmt, expr);
}

std::shared_ptr<Statement>
DoubleCallEliminateVisitor::GetTree(std::shared_ptr<Statement> func) {
  return Accept(*func).statement_;
}

}