#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------


std::string isTrueOrFalse(bool boolean) {
    if (boolean) return "true";
    return "false";
}

std::string typePicker(basic_type *type) {
    if(type->name() == basic_type::TYPE_INT) return "small";
    if(type->name() == basic_type::TYPE_STRING) return "news";
    if(type->name() == basic_type::TYPE_POINTER) return (typePicker(type->subtype()) + "fake");
    if(type->name() == basic_type::TYPE_DOUBLE) return "huge";
    if(type->name() == basic_type::TYPE_VOID) return "void";
    return "invalid";
}

void gr8::xml_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
void gr8::xml_writer::do_data_node(cdk::data_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
void gr8::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  process_literal(node, lvl);
}
void gr8::xml_writer::do_not_node(cdk::not_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}
void gr8::xml_writer::do_and_node(cdk::and_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_or_node(cdk::or_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

void gr8::xml_writer::do_sweeping_node(gr8::sweeping_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("from", lvl + 2);
  node->from()->accept(this, lvl + 4);
  closeTag("from", lvl + 2);
  openTag("to", lvl + 2);
  node->to()->accept(this, lvl + 4);
  closeTag("to", lvl + 2);
  openTag("by", lvl + 2);
  node->by()->accept(this, lvl + 4);
  closeTag("by", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_return_node(gr8::return_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("arg", lvl+2);
  if(node->arg() != nullptr) { node->arg()->accept(this, lvl + 4); }
  closeTag("arg", lvl+2);
  closeTag(node, lvl);
}
void gr8::xml_writer::do_block_node(gr8::block_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("declarations", lvl + 2);
  if(node->declarations() != nullptr) { node->declarations()->accept(this, lvl + 4); }
  closeTag("declarations", lvl + 2);
  openTag("instructions", lvl + 2);
  if(node->instructions() != nullptr) { node->instructions()->accept(this, lvl + 4); }
  closeTag("instructions", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_var_declaration_node(gr8::var_declaration_node *const node, int lvl) {
  os() << std::string(lvl, ' ') << "< " << node->label() << "public: " << isTrueOrFalse(node->publics()) << "use: " << isTrueOrFalse(node->use()) << typePicker(node->type()) << "id: " << node->idstr() << ">" << std::endl;
  openTag("initial_value", lvl+2);
  if(node->initial_value() != nullptr) { node->initial_value()->accept(this, lvl + 4); }
  closeTag("initial_value", lvl+2);
  closeTag(node, lvl);
  
}

void gr8::xml_writer::do_again_node(gr8::again_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("expression", lvl+2);
  if(node->expression() != nullptr) { node->expression()->accept(this, lvl + 4); }
  closeTag("expression", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_stop_node(gr8::stop_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("expression", lvl+2);
  if(node->expression() != nullptr) { node->expression()->accept(this, lvl + 4); }
  closeTag("expression", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_func_declaration_node(gr8::func_declaration_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "< " << node->label() << "public: " << isTrueOrFalse(node->publics()) << "use: " << isTrueOrFalse(node->use()) << typePicker(node->type()) << "id: " << node->idstr() << ">" << std::endl;
  openTag("parameters", lvl+2);
  if(node->parms() != nullptr) { node->parms()->accept(this, lvl + 4); }
  closeTag("parameters", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_func_invocation_node(gr8::func_invocation_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << node->label() << "id: " << node->idstr() << ">" << std::endl;
  openTag("parameters", lvl+2);
  if(node->parms() != nullptr) { node->parms()->accept(this, lvl + 4); }
  closeTag("parameters", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_func_body_node(gr8::func_body_node *const node, int lvl) {
   //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "< " << node->label() << "public: " << isTrueOrFalse(node->publics()) << typePicker(node->type()) << "id: " << node->idstr() << ">" << std::endl;
  openTag("parameters", lvl+2);
  if(node->parms() != nullptr) { node->parms()->accept(this, lvl + 4); }
  closeTag("parameters", lvl+2);
  openTag("value", lvl+2);
  if(node->parms() != nullptr) { node->def_ret()->accept(this, lvl + 4); }
  closeTag("value", lvl+2);
  openTag("block", lvl+2);
  node->body()->accept(this, lvl + 4);
  closeTag("block", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_null_node(gr8::null_node *const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_mem_alloc_node(gr8::mem_alloc_node *const node, int lvl) {
  do_unary_expression(node, lvl);
}

void gr8::xml_writer::do_mem_address_node(gr8::mem_address_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("lvalue", lvl+2);
  if(node->lvalue() != nullptr) { node->lvalue()->accept(this, lvl + 4); }
  closeTag("lvalue", lvl+2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_identity_node(gr8::identity_node *const node, int lvl) {
  do_unary_expression(node, lvl);
}

void gr8::xml_writer::do_indexing_node(gr8::indexing_node *const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("ptr", lvl+2);
  if(node->ptr() != nullptr) { node->ptr()->accept(this, lvl + 4); }
  closeTag("ptr", lvl+2);
  openTag("index", lvl+2);
  if(node->index() != nullptr) { node->index()->accept(this, lvl + 4); }
  closeTag("index", lvl+2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  process_literal(node, lvl);
}

void gr8::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  process_literal(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_unary_expression(cdk::unary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  do_unary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_binary_expression(cdk::binary_expression_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}
void gr8::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  os() << std::string(lvl, ' ') << "<" << node->label() << ">" << node->name() << "</" << node->label() << ">" << std::endl;
}

void gr8::xml_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);

  node->lvalue()->accept(this, lvl);
  reset_new_symbol();

  node->rvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}


//---------------------------------------------------------------------------

void gr8::xml_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_print_node(gr8::print_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_read_node(gr8::read_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::xml_writer::do_if_node(gr8::if_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);
}

void gr8::xml_writer::do_apply_else_node(gr8::apply_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  openTag(node, lvl);
  closeTag(node, lvl);
}
