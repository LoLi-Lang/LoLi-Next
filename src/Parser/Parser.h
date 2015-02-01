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


#include <string>

#include "Tokenizer.h"
#include "AST.h"



namespace lolilang {
namespace parser {

using namespace tokenizer;

// --------------------------- //
// Parser class
// --------------------------- //
class Parser
{
public:
    Tokenizer tokenizer;

    Parser(const Tokenizer& tokenizer);
    ~Parser();

    void parse();

private:
    // match a type or string, return if matched
    int match(const TokenType type);

    int match(const std::string &expect);

    // match a type or string, return if matched
    Token &lookahead();

    // handle and print out error
    void handle_error(const Token &t, const std::string &expect) const;

    // --------------------------------------- //
    // Syntax methods:
    // Each one of the following method defines
    // a part of the syntax of the LL1 Parser
    // --------------------------------------- //
    // Parse an Expression
    Expression *ParseExpression();
};


} // namespace parser
} // namespace lolilang


#endif
