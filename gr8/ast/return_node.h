#ifndef __GR8_RETURNNODE_H__
#define __GR8_RETURNNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing return nodes.
   */
  class return_node: public cdk::basic_node {
      cdk::expression_node *_arg;

  public:
    inline return_node(int lineno): cdk::basic_node(lineno){}
    
  public:
    inline return_node(int lineno, cdk::expression_node *arg): cdk::basic_node(lineno), _arg(arg){}
    
  public:
    inline cdk::expression_node *arg() {
        return _arg;
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // gr8

#endif
