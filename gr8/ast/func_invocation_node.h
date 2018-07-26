#ifndef __GR8_FUNCINVOCATIONNODE_H__
#define __GR8_FUNCINVOCATIONNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing function invocation nodes.
   */
  class func_invocation_node: public cdk::expression_node {
      std::string _idstr;
      cdk::sequence_node *_parms;

  public:
    inline func_invocation_node(int lineno, std::string * idstr, cdk::sequence_node * parms):
    cdk::expression_node(lineno), _idstr(*idstr), _parms(parms) {}
    
    inline std::string idstr() {
        return _idstr;
    }
    
    inline cdk::sequence_node *parms() {
        return _parms;
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_invocation_node(this, level);
    }

  };

} // gr8

#endif
