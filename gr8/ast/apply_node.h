#ifndef __GR8_APPLYNODE_H__
#define __GR8_APPLYNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing sweeping-cycle nodes.
   */
  class apply_node: public cdk::basic_node {
    cdk::expression_node *_vector;
    cdk::expression_node *_from;
    cdk::expression_node *_to;
    std::string *_idstr;
    
  public:
    inline apply_node(int lineno, std::string *idstr, cdk::expression_node *vector, cdk::expression_node *from, cdk::expression_node *to) :
        basic_node(lineno), _idstr(idstr), _vector(vector), _from(from), _to(to) {
    }

  public:
    inline cdk::expression_node *vector() {
      return _from;
    }
    inline cdk::expression_node *from() {
      return _from;
    }
    inline cdk::expression_node *to() {
      return _to;
    }
    inline std::string *idstr() {
      return _idstr;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweeping_node(this, level);
    }

  };

} // gr8

#endif
