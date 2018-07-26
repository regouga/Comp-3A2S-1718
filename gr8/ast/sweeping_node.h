#ifndef __GR8_SWEEPINGNODE_H__
#define __GR8_SWEEPINGNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing sweeping-cycle nodes.
   */
  class sweeping_node: public cdk::basic_node {
    cdk::expression_node *_from, *_to, *_by;
    cdk::basic_node *_block;
    cdk::lvalue_node *_lvalue;
    
  public:
    inline sweeping_node(int lineno, cdk::expression_node *from, cdk::expression_node *to, cdk::expression_node *by, cdk::basic_node *block, cdk::lvalue_node *lvalue) :
        basic_node(lineno), _from(from), _to(to), _by(by), _block(block), _lvalue(lvalue) {
    }

  public:
    inline cdk::expression_node *from() {
      return _from;
    }
    inline cdk::expression_node *to() {
      return _to;
    }
    inline cdk::expression_node *by() {
      return _by;
    }
    inline cdk::basic_node *block() {
      return _block;
    }
    inline cdk::lvalue_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweeping_node(this, level);
    }

  };

} // gr8

#endif
