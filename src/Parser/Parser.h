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
    TokenStream_t tokens;

    Parser(const TokenStream_t &tokens);
    ~Parser();

    void parse();

private:
    // match a type or string, return if matched
    int match(const TokenType type);

    int match(const string &str);

    // --------------------------------------- //
    // Syntax methods:
    // Each one of the following method defines
    // a part of the syntax of the LL1 Parser
    // --------------------------------------- //
    // Parse an Expression
    Expression *ParseExpression();
}


} // namespace lolilang


#endif
