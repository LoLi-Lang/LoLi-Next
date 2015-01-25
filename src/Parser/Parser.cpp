// --*- C++ -*-------------------------------------//
// 
//                 The Loli Language
//
//
// filename: Parser.cpp
// descript: Defines the language syntax.
//           Inputs tokens, output AST for language
// author  : Kevin Hu <hxy9243@gmail.com>
// note: 
//
//-------------------------------------------------//


#include "Parser.h"


using namespace lolilang;


// Constructor for parser
// @tokens: The input token stream 
Parser::Parser(const Tokenizer &tokenizer)
    :tokenizer(tokenizer)
{
    
}


// Destructor for parser
Parser::~Parser()
{
    
}


// The parse method
void Parser::parse()
{
    if (match(LEFTPAREN)) {
        ParseExpression();
    }

    match(RIGHTPAREN);
}


// The match method
// @type: The type of input token
// return: If matched
int Parser::match(const TokenType type)
{
    Token &t = tokenizer.get();
    if (t.type == type) {
        return true;
    }
    return false;
}


// @str: The string input of the token
// return: If matched
int Parser::match(const std::string &str)
{
    Token &t = tokenizer.get();
    if (t.token == str) {
        return true;
    }
    return false;
}


// --------------------------------------- //
// Syntax methods:
// Each one of the following method defines
// a part of the syntax of the LL1 Parser
// --------------------------------------- //
// Parse an Expression
// @tokens: The tokenizer class
// return: ASTNode of Expression
Expression* Parser::ParseExpression()
{
    Token &t = tokenizer.lookahead();
    if (t.type == NAME) {
        // keep parsing

    }

    return NULL;
}
