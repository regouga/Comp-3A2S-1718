#ifndef __GR8_INDEXINGNODE_H__
#define __GR8_INDEXINGNODE_H__

#include "cdk/ast/lvalue_node.h"

namespace gr8 {

  /**
   * Class for describing indexing nodes.
   */
  class indexing_node: public cdk::lvalue_node {
    cdk::expression_node *_ptr, *_index;
  public:
    inline indexing_node(int lineno, cdk::expression_node *ptr, cdk::expression_node *index): 
        cdk::lvalue_node(lineno), _ptr(ptr), _index(index){}
        
  public:
    inline cdk::expression_node *ptr() {
        return _ptr;
    }
    
    inline cdk::expression_node *index() {
        return _index;
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_indexing_node(this, level);
    }

  };

} // gr8

#endif
