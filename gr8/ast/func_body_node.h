#ifndef __GR8_FUNCBODYNODE_H__
#define __GR8_FUNCBODYNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing function body nodes.
   */
  class func_body_node: public cdk::typed_node {
      bool _publics;
      std::string _idstr;
      cdk::sequence_node *_parms;
      cdk::expression_node *_def_ret;
      block_node *_body;

  public:
    inline func_body_node(int lineno, bool publics, basic_type *type, std::string* idstr, cdk::sequence_node *parms, cdk::expression_node *def_ret, block_node *body):
    cdk::typed_node(lineno), _publics(publics), _idstr(*idstr), _parms(parms), _def_ret(def_ret), _body(body) {
        cdk::typed_node::type(type);
    }
    
    inline bool publics() {
        return _publics;
    }
    
    inline std::string idstr() {
        return _idstr;
    }
    
    inline cdk::sequence_node *parms() {
        return _parms;
    }
    
    inline cdk::expression_node  *def_ret() {
        return _def_ret;
    }
    
    inline block_node *body() {
        return _body;
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_body_node(this, level);
    }

  };

} // gr8

#endif
