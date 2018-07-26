#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_block_node(gr8::block_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_var_declaration_node(gr8::var_declaration_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_again_node(gr8::again_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_stop_node(gr8::stop_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_func_declaration_node(gr8::func_declaration_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_func_invocation_node(gr8::func_invocation_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_func_body_node(gr8::func_body_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_null_node(gr8::null_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_mem_alloc_node(gr8::mem_alloc_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_mem_address_node(gr8::mem_address_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_identity_node(gr8::identity_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_indexing_node(gr8::indexing_node *const node, int lvl) {
  // EMPTY
}


//---------------------------------------------------------------------------

void gr8::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
}

void gr8::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void gr8::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void gr8::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void gr8::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void gr8::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void gr8::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void gr8::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void gr8::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void gr8::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void gr8::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void gr8::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // simplified generation: all variables are global
  _pf.ADDR(node->name());
}

void gr8::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  _pf.LDINT(); // depends on type size
}

void gr8::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  _pf.DUP32();
  if (new_symbol() == nullptr) {
    node->lvalue()->accept(this, lvl); // where to store the value
  } else {
    _pf.DATA(); // variables are all global and live in DATA
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(new_symbol()->name()); // name variable location
    reset_new_symbol();
    _pf.SINT(0); // initialize it to 0 (zero)
    _pf.TEXT(); // return to the TEXT segment
    node->lvalue()->accept(this, lvl);  //DAVID: bah!
  }
  _pf.STINT(); // store the value at address
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.TRASH(4); // delete the evaluated value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.TRASH(4); // delete the evaluated value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void gr8::postfix_writer::do_print_node(gr8::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_read_node(gr8::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.CALL("readi");
  _pf.LDFVAL32();
  _pf.STINT();
}


//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_node(gr8::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

void gr8::postfix_writer::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_return_node(gr8::return_node *const node, int lvl) {
  // EMPTY
}


void gr8::postfix_writer::do_apply_node(gr8::apply_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  std::string condition = mklbl(++_lbl);
  std::string end = mklbl(++_lbl);
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->idsrt());

  // i = from
  node->from()->accept(this, lvl);

  // i <= to
  _pf.DUP32();
  _pf.ALIGN();
  _pf.LABEL(condition);
  node->to()->accept(this, lvl);
  _pf.LE();
  _pf.JZ(end);

  _pf.DUP32();
  _pf.INT(node->vector()->type()->subtype()->size());
  _pf.MUL;
  node->vector()->accept(this, lvl);
  _pf.ADD();

  if (node->vector()->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.LDDOUBLE();
  else
    _pf.LDINT();

  _pf.CALL(node->idstr());

  //increment

  _pf.INT(0);
  _pf.ADD();
  _pf.JMP(condition);
  _pf.ALIGN();
  _pf.LABEL(end);
  _pf.TRASH(4);
}
