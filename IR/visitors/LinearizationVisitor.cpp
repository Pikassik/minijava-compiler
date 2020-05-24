#include "LinearizationVisitor.h"
#include "BaseElements.h"

namespace IRT {

using std::shared_ptr;
using std::make_shared;

static bool IsSeqStatement(Statement& stmt) {
  return dynamic_cast<SeqStatement*>(&stmt) != nullptr;
}

void LinearizationVisitor::Visit(ExpStatement& stmt) {
  IrtStorage elements = Accept(*stmt.GetExpression());
  tos_value_.statement_ = make_shared<ExpStatement>(elements.expression_);
}

void LinearizationVisitor::Visit(ConstExpression& const_expression) {
  tos_value_.expression_ = make_shared<ConstExpression>(const_expression.Value());
}

void LinearizationVisitor::Visit(JumpConditionalStatement& jump_conditional_statement) {
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
void LinearizationVisitor::Visit(MoveStatement& move_statement) {
  auto source = Accept(*move_statement.source_).expression_;
  auto target = Accept(*move_statement.target_).expression_;

  tos_value_.statement_ = make_shared<MoveStatement>(source, target);
}

void LinearizationVisitor::Visit(SeqStatement& seq_statement) {
  // SEQ(SEQ(a, b), c) -> SEQ(a, SEQ(b, c))

  auto first = Accept(*seq_statement.first_statement_).statement_;

  if (IsSeqStatement(*first)) {
    auto left_seq = std::dynamic_pointer_cast<SeqStatement>(first);
    auto b = left_seq->second_statement_;
    seq_statement.first_statement_ = b;
    left_seq->second_statement_ = Accept(seq_statement).statement_;
    tos_value_.statement_ = left_seq;
  } else {
    auto second = Accept(*seq_statement.second_statement_).statement_;
    tos_value_.statement_ = make_shared<SeqStatement>(
      first,
      second
    );
  }
}

void LinearizationVisitor::Visit(LabelStatement& label_statement) {
  tos_value_.statement_ = make_shared<LabelStatement>(label_statement.label_);
}

void LinearizationVisitor::Visit(BinopExpression& binop_statement) {
  tos_value_.expression_ = make_shared<BinopExpression>(
    binop_statement.operator_type_,
    Accept(*binop_statement.first_).expression_,
    Accept(*binop_statement.second_).expression_
  );
}
void LinearizationVisitor::Visit(TempExpression& temp_exression) {
  tos_value_.expression_ = make_shared<TempExpression>(temp_exression.temporary_);
}

void LinearizationVisitor::Visit(MemExpression& mem_expression) {
  tos_value_.expression_ = make_shared<MemExpression>(
      Accept(*mem_expression.expression_).expression_
  );
}

void LinearizationVisitor::Visit(JumpStatement& jump_statement) {
  tos_value_.statement_ = make_shared<JumpStatement>(
    jump_statement.label_
  );
}
void LinearizationVisitor::Visit(CallExpression& call_expression) {
  auto func = Accept(*call_expression.function_name_).expression_;
  auto args = Accept(*call_expression.args_).expression_list_;

  tos_value_.expression_ = make_shared<CallExpression>(
    func,
    args
  );
}
void LinearizationVisitor::Visit(ExpressionList& expression_list) {
  auto expression_list_ = make_shared<ExpressionList>();

  for (auto&& expression: expression_list.expressions_) {
    expression_list_->Add(Accept(*expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;

}

void LinearizationVisitor::Visit(NameExpression& name_expression) {
  tos_value_.expression_ = make_shared<NameExpression>(name_expression.label_);
}

void LinearizationVisitor::Visit(EseqExpression& eseq_expression) {
  auto stmt = Accept(*(eseq_expression.statement_)).statement_;
  auto expr = Accept(*eseq_expression.expression_).expression_;

  tos_value_.expression_ = make_shared<EseqExpression>(stmt, expr);
}

std::shared_ptr<Statement>
LinearizationVisitor::GetTree(std::shared_ptr<Statement> func) {
  return Accept(*func).statement_;
}

}