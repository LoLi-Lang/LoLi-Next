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
    CHAR,
    STRING,
    BOOLEAN,
    LEFTPAREN,
    RIGHTPAREN,
    SINGLEQUOTE,
    ACUTE,
    COMMA,
    DOT,
    BACKSLASH,
    // SHARP_LEFTPAREN
    // COMMA_AT
    EMPTY,
    ERRORTOKEN,
    EOF_TOKEN
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

    Token(TokenType type, std::string token, int linum);
    Token(TokenType type, int linum);
    ~Token();
};


// --------------------------- //
// Tokenizer class
// --------------------------- //
typedef std::vector<Token> TokenStream_t; 

class Tokenizer 
{
public:
    Tokenizer();
    ~Tokenizer();
        
    // Scan the next character
    void scan(std::istream &file);

    // Get one token, move the index
    Token &get();

    // Get one token, not moving the index
    Token &lookahead();

private:
    // The vector containing all tokens
    TokenStream_t token_stream;

    // position of read index
    int index;

    // find type of character
    CharType find_char_type(const char c) const;

    // is the token a number
    bool is_num(const std::string &buffer) const;

    // convert escaped char string
    char convert_char(const char c) const;
};


} // namespace lolilang


#endif
