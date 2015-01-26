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

Token::Token(TokenType type, int linum)
    :type(type), linum(linum)
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
    token_stream.push_back(Token(EOF_TOKEN, 0));
}


// Destructor
Tokenizer::~Tokenizer() { } 


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


// Find the type of the incoming character
// @c - the input char
// return: the chartype of the input char
CharType Tokenizer::find_char_type(const char c) const
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
        || c == '<' || c == '>'
        || c == '~' || c == '#'
        || c == '|') {
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
// return: If it's valid number string
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


// convert escaped char string
// @c: the char after escape sign
// return: the corresponding char
char Tokenizer::convert_char(const char c) const
{
    switch (c) {
    case 'a': return '\a';
        break;
    case 'b': return '\b';
        break;
    case 'n': return '\n';
        break;
    case 'r': return '\r';
        break;
    case 't': return '\t';
        break;
    case '\\': return '\\';
        break;
    case '"': return '"';
        break;
    case '\'': return '\'';
        break;
    default: 
        return c;
        break;
    }
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
        if (find_char_type(c) == NUMBER_CHAR
            || find_char_type(c) == ALPHA_CHAR
            || find_char_type(c) == SPECIAL_IDEN) {
            buffer += c;
            while(file.get(next)) {
                if (find_char_type(next) == NUMBER_CHAR
                    || find_char_type(next) == ALPHA_CHAR
                    || find_char_type(next) == SPECIAL_IDEN) {
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
        if (find_char_type(c) == COMMENT_CHAR) {
            while (file.get(next)) {
                if (next == '\n' || next == '\r') {
                    break;
                }
            }
            file.putback(next);
            continue;
        }

        // CHAR
        if (c == '\'') {
            file.get(next);
            if (next != '\\') {
                buffer += next;
            }
            else {
                file.get(next);
                buffer += convert_char(next);
            }
            file.get(next);
            if (next == '\'') {
                token_stream.push_back(Token(CHAR, buffer, linum));
            }
            else {
                token_stream.push_back(Token(ERRORTOKEN, linum));
            }
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
        if (find_char_type(c) == EMPTY_CHAR) {
            if (c == '\n' || c == '\r') {
                linum++;
            }
            while (file.get(next)) {
                if (next == '\n' || c == '\r') {
                    linum++;
                }
                if (find_char_type(next) != EMPTY_CHAR) {
                    break;
                }
            }
            file.putback(next);
            continue;
        }

        // SPECIAL
        if (find_char_type(c) == SPECIAL_CHAR) {
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
            case '\\': token_stream.push_back(Token(BACKSLASH, buffer, linum));
                break;
            default:
                token_stream.push_back(Token(SPECIAL, buffer, linum));
                break;
            }
            continue;
        }
    } // while loop

    token_stream.push_back(Token(EOF_TOKEN, linum));
}
