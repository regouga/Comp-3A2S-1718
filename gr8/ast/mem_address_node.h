#ifndef __GR8_MEMADDRESSNODE_H__
#define __GR8_MEMADDRESSNODE_H__

#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing memory adress nodes.
   */
  class mem_address_node: public cdk::expression_node {
      cdk::lvalue_node *_lvalue;

  public:
    inline mem_address_node(int lineno, cdk::lvalue_node *arg) :
        cdk::expression_node(lineno), _lvalue(arg) {} 
        
  public:
    inline cdk::lvalue_node *lvalue() {
        return _lvalue;
    }
    
  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_mem_address_node(this, level);
    }

  };

} // gr8

#endif
