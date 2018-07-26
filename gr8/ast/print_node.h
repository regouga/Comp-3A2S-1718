// $Id: print_node.h,v 1.3 2018/04/18 21:23:16 ist424833 Exp $ -*- c++ -*-
#ifndef __GR8_PRINTNODE_H__
#define __GR8_PRINTNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node *_argument;
    bool _isTweetOrPost;

  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool isTweetOrPost) :
        cdk::basic_node(lineno), _argument(argument), _isTweetOrPost(isTweetOrPost) {
            // True: tweet 
            // False: post
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // gr8

#endif
