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


#include <cstdlib>

#include "Tokenizer.h"


using namespace lolilang;


// --------------------------- //
// Token class
// --------------------------- //

// Constructor 
// param: type - the type of Token
// param: token - the string of token
// param: linum - the line number of token
Token::Token(TokenType type, std::string token, int linum)
    :type(type), token(token), linum(linum)
{ }

Token::Token(TokenType type)
    :type(type)
{ }

// Destructor
Token::~Token() { } 


// --------------------------- //
// Token class
// --------------------------- //
// Constructor
Tokenizer::Tokenizer() 
    : index(0)
{
    token_stream.push_back(Token(EOF_TOKEN));
}


// Destructor
Tokenizer::~Tokenizer() { } 


// Find the type of the incoming character
// @c - the input char
// return: the chartype of the input char
CharType Tokenizer::findCharType(const char c) const
{
    if ('0' <= c && c <= '9') {
        return NUMBER_CHAR;
    }
    
    if (('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z')) {
        return ALPHA_CHAR;
    }
    
    if (c == '!' || c == '$'
        || c == '%' || c == '&'
        || c == '*' || c == '+'
        || c == '-' || c == '.'
        || c == '/' || c == ':'
        || c == '=' || c == '>'
        || c == '?' || c == '@'
        || c == '^' || c == '_'
        || c == '~' || c == '#'
        || c == '<' || c == '>') {
        return SPECIAL_IDEN;
    }

    if (c == ' ' || c == '\n' ||
        c == '\r' || c == '\t') {
        return EMPTY_CHAR;
    }
    
    if (c == ';') {
        return COMMENT_CHAR;
    }

    if (c == EOF) {
        return END_CHAR;
    }
    
    return SPECIAL_CHAR;
}


// Is the token a number
// @buffer: The input buffer string
bool Tokenizer::is_num(const std::string &buffer) const
{
    char *pend;
    const char *numchar = buffer.c_str();

    strtod(numchar, &pend);
    if (pend == &numchar[buffer.size()]) {
        return true;
    }
    return false;
}


// Get one token, move the index
// return: The token to store info to
Token& Tokenizer::get()
{
    Token &T = token_stream[index];
    ++index;
    return T;
}


// Get one token, not moving the index
// return: The token to store info to
Token& Tokenizer::lookahead()
{
    return token_stream[index];
}


// Scan the next char from file, save token stream to
// token_stream vector
// @file - the input file
void Tokenizer::scan(std::istream &file)
{
    std::string buffer;

    int linum = 1;
    char c;
    char next;

    token_stream.clear();

    while (file.get(c)) {
        buffer.clear();

        // IDENTIFIER AND NUMBER
        if (findCharType(c) == NUMBER_CHAR
            || findCharType(c) == ALPHA_CHAR
            || findCharType(c) == SPECIAL_IDEN) {
            buffer += c;
            while(file.get(next)) {
                if (findCharType(next) == NUMBER_CHAR
                    || findCharType(next) == ALPHA_CHAR
                    || findCharType(next) == SPECIAL_IDEN) {
                    buffer += next;
                }
                else {
                    break;
                }
            }
            file.putback(next);

            if (buffer == ":t" || buffer == ":f"
                || buffer == ":true" || buffer == ":false") {
                token_stream.push_back(Token(BOOLEAN, buffer, linum));
            }
            else if (is_num(buffer)) {
                token_stream.push_back(Token(NUMBER, buffer, linum));
            }
            else {
                token_stream.push_back(Token(NAME, buffer, linum));
            }
            continue;
        }   

        // COMMENTS
        if (findCharType(c) == COMMENT_CHAR) {
            while (file.get(next)) {
                if (next == '\n' || next == '\r') {
                    break;
                }
            }
            file.putback(next);
            continue;
        }

        // SRTING
        if (c == '"') {
            while (file.get(next)) {
                if (next == '"') {
                    break;
                }
                if (next == '\\') {
                    file.get(next);
                    // Deal with special ASCII chars
                    switch (next) {
                    case 'a': buffer += '\a';
                        break;
                    case 'b': buffer += '\b';
                        break;
                    case 'n': buffer += '\n';
                        break;
                    case 'r': buffer += '\r';
                        break;
                    case 't': buffer += '\t';
                        break;
                    case '\\': buffer += '\\';
                        break;
                    case '"': buffer += '"';
                        break;
                    default: 
                        break;
                    }
                }
                else {
                    buffer += next;
                }
            }
            // file.putback(next);
            token_stream.push_back(Token(STRING, buffer, linum));
            continue;
        }
        
        // EMPTY
        if (findCharType(c) == EMPTY_CHAR) {
            if (c == '\n' || c == '\r') {
                linum++;
            }
            while (file.get(next)) {
                if (next == '\n' || c == '\r') {
                    linum++;
                }
                if (findCharType(next) != EMPTY_CHAR) {
                    break;
                }
            }
            file.putback(next);
            continue;
        }

        // SPECIAL
        if (findCharType(c) == SPECIAL_CHAR) {
            buffer += c;

            switch(c) {
            case '`': token_stream.push_back(Token(ACUTE, buffer, linum));
                break;
            case ',': token_stream.push_back(Token(COMMA, buffer, linum));
                break;
            case '.': token_stream.push_back(Token(DOT, buffer, linum));
                break;
            case '(': token_stream.push_back(Token(LEFTPAREN, buffer, linum));
                break;
            case ')': token_stream.push_back(Token(RIGHTPAREN, buffer, linum));
                break;
            default:
                break;
            }
            continue;
        }
    } // while loop

    token_stream.push_back(Token(EOF_TOKEN));
}