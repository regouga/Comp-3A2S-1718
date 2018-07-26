#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void gr8::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  // EMPTY
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::type_checker::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
void gr8::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  // EMPTY
}
void gr8::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  // EMPTY
}
void gr8::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  // EMPTY
}
void gr8::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_return_node(gr8::return_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_block_node(gr8::block_node *const node, int lvl) {
  // EMPTY
}


void gr8::type_checker::do_var_declaration_node(gr8::var_declaration_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_again_node(gr8::again_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_stop_node(gr8::stop_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_func_declaration_node(gr8::func_declaration_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_func_invocation_node(gr8::func_invocation_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_func_body_node(gr8::func_body_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_null_node(gr8::null_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_mem_alloc_node(gr8::mem_alloc_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_mem_address_node(gr8::mem_address_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_identity_node(gr8::identity_node *const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_indexing_node(gr8::indexing_node *const node, int lvl) {
  // EMPTY
}


//---------------------------------------------------------------------------

void gr8::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

void gr8::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in argument of unary expression");

  // in Simple, expressions were always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in right argument of binary expression");

  // in Simple, expressions were always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void gr8::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  } else {
    throw id;
  }
}

void gr8::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void gr8::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;

  try {
    node->lvalue()->accept(this, lvl);
  } catch (const std::string &id) {
    std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(new basic_type(4, basic_type::TYPE_INT), id, 0);
    _symtab.insert(id, symbol);
    _parent->set_new_symbol(symbol);  // advise parent that a symbol has been inserted
    node->lvalue()->accept(this, lvl);  //DAVID: bah!
  }

  if (node->lvalue()->type()->name() != basic_type::TYPE_INT) throw std::string(
      "wrong type in left argument of assignment expression");

  node->rvalue()->accept(this, lvl + 2);
  if (node->rvalue()->type()->name() != basic_type::TYPE_INT) throw std::string(
      "wrong type in right argument of assignment expression");

  // in Simple, expressions were always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void gr8::type_checker::do_print_node(gr8::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_read_node(gr8::read_node * const node, int lvl) {
  try {

  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}


//---------------------------------------------------------------------------

void gr8::type_checker::do_if_node(gr8::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void gr8::type_checker::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void gr8::type_checker::do_apply_node(gr8::apply_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
   node->vector()->accept(this, lvl + 4);
   node->from()->accept(this, lvl + 4);
   node->to()->accept(this, lvl + 4);

}
