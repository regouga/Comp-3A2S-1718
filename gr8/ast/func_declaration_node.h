#ifndef __GR8_FUNCDECLARATIONNODE_H__
#define __GR8_FUNCDECLARATIONNODE_H__

#include <cdk/ast/sequence_node.h>

namespace gr8 {

  /**
   * Class for describing variable declaration nodes.
   */
  class func_declaration_node: public cdk::typed_node {
      bool _publics;
      bool _use;
      std::string _idstr;
      cdk::sequence_node *_parms;

  public:
    inline func_declaration_node(int lineno, basic_type * type, bool publics, bool use, std::string * idstr, cdk::sequence_node * parms):
    cdk::typed_node(lineno), _publics(publics), _use(use), _idstr(*idstr), _parms(parms) {
        cdk::typed_node::type(type);
    }
    
  public:
      inline bool publics() {
          return _publics;
      }
      
      inline bool use() {
          return _use;
      }
      
      inline std::string idstr() {
          return _idstr;
      }
      
      inline cdk::sequence_node *parms() {
          return _parms;
      }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_func_declaration_node(this, level);
    }

  };

} // gr8

#endif
