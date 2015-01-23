// --*- C++ -*-------------------------------------//
// 
//                 The Loli Language
//
//
// filename: Parser.h
// descript: Defines the language syntax.
//           Inputs tokens, output AST for language
// author  : Kevin Hu <hxy9243@gmail.com>
// note: 
//
//-------------------------------------------------//


#ifndef __PARSER_H__
#define __PARSER_H__


#include "Tokenizer.h"
#include "AST.h"


namespace lolilang {


// --------------------------- //
// Parser class
// --------------------------- //
class Parser
{
public:
    Tokenizer::TokenStream_t tokens;

    Parser(const Tokenizer::TokenStream_t &tokens);
    ~Parser();

    void parse();

private:
    Expression *ParseExpression(tokens);
}


} // namespace lolilang


#endif
