// --*- C++ -*-------------------------------------//
// 
//                 The Loli Language
//
//
// filename: Tokenizer.h
// descript: The tokens definition and tokenizer
//           implementation
// author  : Kevin Hu <hxy9243@gmail.com>
// note: 
//
//-------------------------------------------------//


#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__


#include <fstream>
#include <string>
#include <vector>


namespace lolilang {


// --------------------------- //
// Typedefs and constants
// --------------------------- //
enum CharType 
{
    ALPHA_CHAR,
    NUMBER_CHAR,
    EMPTY_CHAR,
    COMMENT_CHAR,
    SPECIAL_IDEN,
    SPECIAL_CHAR,
    END_CHAR
};

enum TokenType
{
    NAME,
    NUMBER,
    STRING,
    BOOLEAN,
    LEFTPAREN,
    RIGHTPAREN,
    SINGLEQUOTE,
    ACUTE,
    COMMA,
    DOT,
    // SHARP_LEFTPAREN
    // COMMA_AT
    EMPTY,
    ERRORTOKEN
};


// --------------------------- //
// Token class
// --------------------------- //
class Token
{
public:
    TokenType type;
    std::string token;
    int linum;

    Token(TokenType type, std::string &token, int linum);
    ~Token();
};


// --------------------------- //
// Tokenizer class
// --------------------------- //
typedef std::vector<Token> TokenStream_t; 

class Tokenizer 
{
public:
    // The vector containing all tokens
    TokenStream_t token_stream;

    Tokenizer();
    ~Tokenizer();
        
    // Scan the next character
    void scan(std::istream &file);

private:
    // find type of character
    CharType findCharType(const char c) const;

    // is the token a number
    bool is_num(const std::string &buffer) const;
};


} // namespace lolilang


#endif
