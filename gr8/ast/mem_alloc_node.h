#ifndef __GR8_MEMALLOCNODE_H__
#define __GR8_MEMALLOCNODE_H__

#include <cdk/ast/sequence_node.h>

namespace gr8 {

  /**
   * Class for describing memory allocation nodes.
   */
  class mem_alloc_node: public cdk::unary_expression_node {

  public:
    inline mem_alloc_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {} 

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_mem_alloc_node(this, level);
    }

  };

} // gr8

#endif
