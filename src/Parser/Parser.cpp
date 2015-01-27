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

#include <cassert>
#include <iostream>


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


// The match method
// @type: The type of input token
// return: If matched
int Parser::match(const TokenType type)
{
    Token &t = tokenizer.get();
    if (t.type == type) {
        return true;
    }

    // handle error
    handle_error(t, TokenTypeString[type]);

    return false;
}


// @str: The string input of the token
// return: If matched
int Parser::match(const std::string &expect)
{
    Token &t = tokenizer.get();
    if (t.token == expect) {
        return true;
    }

    handle_error(t, expect);

    return false;
}


// The lookahead method
// @type: The type of input token
// return: If matched
int Parser::lookahead(const TokenType type)
{
    Token &t = tokenizer.lookahead();
    if (t.type == type) {
        return true;
    }
    return false;
}

// @str: The string input of the token
// return: If matched
int Parser::lookahead(const std::string &expect)
{
    Token &t = tokenizer.lookahead();
    if (t.token == expect) {
        return true;
    }
    return false;
}


// handle and print out error
// @t: The input token where there's error
void Parser::handle_error(const Token &t, const std::string& expect) const
{
    std::cout << "[ERROR] Illegal token: " << t.token 
              << " on line: " << t.linum << ". "
              << "Expect: " << expect << std::endl;
}


// The parse method. The entry of whole parser.
void Parser::parse()
{
    if (match(LEFTPAREN)) {
        ParseExpression();
    }

    match(RIGHTPAREN);
}


// --------------------------------------- //
// Syntax methods:
// Each one of the following method defines
// a part of the syntax of the recursive 
// descent Parser
// --------------------------------------- //
// Parse an Expression
// @tokens: The tokenizer class
// return: ASTNode of Expression
Expression* Parser::ParseExpression()
{
    Token &first = tokenizer.lookahead();

    if (first.type == NAME) {
        while (1) {
            Token &follow = tokenizer.lookahead();

            if (follow.type != NAME) {
                break;
            }

            match(NAME);
            std::cout << "[INFO] Parsed a " << follow.token
                      << std::endl;
        }
    }

    return NULL;
}
