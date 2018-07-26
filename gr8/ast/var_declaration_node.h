#ifndef __GR8_VARDECLARATIONNODE_H__
#define __GR8_VARDECLARATIONNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing variable declaration nodes.
   */
  class var_declaration_node: public cdk::typed_node {
      bool _publics;
      bool _use;
      basic_type *_type;
      std::string _idstr;
      cdk::expression_node *_initial_value;

  public:
    inline var_declaration_node(int lineno, basic_type * type, bool publics, bool use, std::string * idstr, cdk::expression_node * initial_value):
    cdk::typed_node(lineno), _publics(publics), _use(use), _type(type), _idstr(*idstr), _initial_value(initial_value) {}
    
  public:
    inline bool publics() {
        return _publics;
    }
    
    inline bool use() {
        return _use;
    }
    
    inline basic_type *type() {
        return _type;
    }
    
    inline std::string idstr() {
        return _idstr;
    }
    
    inline cdk::expression_node *initial_value() {
        return _initial_value;
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_var_declaration_node(this, level);
    }

  };

} // gr8

#endif
