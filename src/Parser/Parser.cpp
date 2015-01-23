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
Parser::Parser(const TokenStream_t &tokens)
    :tokens(tokens)
{
    
}


// The parse method
void Parser::parse()
{
    


}

// The match method
// @type: The type of input token
void Parser::match(TokenType type)
{




}

// @str: The string input of the token
void Parser::match(string &str)
{




}


// --------------------------------------- //
// Syntax methods:
// Each one of the following method defines
// a part of the syntax of the LL1 Parser
// --------------------------------------- //
void Parser::ParseExpression(Tokenizer &tokens)
{





}
