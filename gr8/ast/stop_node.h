#ifndef __GR8_STOPNODE_H__
#define __GR8_STOPNODE_H__

#include <cdk/ast/integer_node.h>

namespace gr8 {

  /**
   * Class for describing stop nodes.
   */
  class stop_node: public cdk::basic_node {
    cdk::integer_node *_expression;

  public:
    inline stop_node(int lineno, cdk::integer_node *expression) :
        cdk::basic_node(lineno), _expression(expression) {
    }

  public:
    inline cdk::integer_node *expression() {
      return _expression;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_stop_node(this, level);
    }

  };

} // gr8

#endif
