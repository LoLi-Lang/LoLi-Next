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


#include "Tokenizer.h"


using namespace lolilang;


// --------------------------- //
// Token class
// --------------------------- //

// Constructor 
// param: type - the type of Token
// param: token - the string of token
// param: linum - the line number of token
Token::Token(TokenType type, std::string &token, int linum)
    :type(type), token(token), linum(linum){}

// Destructor
Token::~Token() { } 


// --------------------------- //
// Token class
// --------------------------- //
// Constructor
Tokenizer::Tokenizer() { }


// Destructor
Tokenizer::~Tokenizer() { } 


// Find the type of the incoming character
// param: c - the input char
// return: the chartype of the input char
CharType Tokenizer::findCharType(char c)
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
        || c == '~') {
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


// Scan the next char from file, save token stream to
// token_stream vector
// param: file - the input file
void Tokenizer::scan(std::istream &file)
{
    std::string buffer;

    int linum = 1;
    char c;
    char next;

    while (file.get(c)) {
        buffer.clear();

        // IDENTIFIER
        if (findCharType(c) == ALPHA_CHAR
            || findCharType(c) == SPECIAL_IDEN) {
            buffer += c;
            while(file.get(next)) {
                if (findCharType(next) == ALPHA_CHAR
                    || findCharType(next) == SPECIAL_IDEN
                    || findCharType(next) == NUMBER_CHAR) {
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
            else {
                token_stream.push_back(Token(NAME, buffer, linum));
            }
            continue;
        }   

        // NUMBERS
        if (findCharType(c) == NUMBER_CHAR) {
            enum States {
                BEGIN,
                FRACTION,
                EXPO_SIGN,
                EXPO_NUM,
                EXPO_NUM_FOLLOW,
                END,
                ERRORNUM
            };

            int state = 0;
            buffer += c;

            // starting FSM
            while (file.get(next)) {
                switch (state) {
                case BEGIN:
                    if (findCharType(next) == NUMBER_CHAR) {
                        buffer += next;
                    }
                    else if (next == '.') {
                        buffer += next;
                        state = FRACTION;
                    }
                    else if (next == 'e' || next == 'E'
                             || next == 'd' || next == 'D') {
                        buffer += next;
                        state = EXPO_SIGN;
                    }
                    else if (findCharType(next) == SPECIAL_CHAR
                             || findCharType(next) == SPECIAL_IDEN
                             || findCharType(next) == EMPTY_CHAR) {
                        state = 5;
                    }
                    else {
                        state = ERRORNUM;
                    }
                    break;
                case FRACTION:
                    if (findCharType(next) == NUMBER_CHAR) {
                        buffer += next;
                    }
                    else if (next == 'e' || next == 'E'
                             || next == 'd' || next == 'D') {
                        buffer += next;
                        state = 2;
                    }
                    else if (findCharType(next) == SPECIAL_CHAR
                             || findCharType(next) == SPECIAL_IDEN
                             || findCharType(next) == EMPTY_CHAR) {
                        state = 5;
                    }
                    else {
                        state = ERRORNUM;
                    }
                    break;
                case EXPO_SIGN:
                    if (next == '+' || next == '-') {
                        buffer += next;
                        state = EXPO_NUM;
                    }
                    else if (findCharType(next) == NUMBER_CHAR) {
                        buffer += next;
                        state = EXPO_NUM_FOLLOW;
                    }
                    else {
                        state = ERRORNUM;
                    }
                    break;
                case EXPO_NUM:
                    if (findCharType(next) == NUMBER_CHAR) {
                        buffer += next;
                        state = EXPO_NUM_FOLLOW;
                    }
                    else {
                        state = ERRORNUM;
                    }
                    break;
                case EXPO_NUM_FOLLOW:
                    if (findCharType(next) == NUMBER_CHAR) {
                        buffer += next;
                    }
                    else if (findCharType(next) == SPECIAL_CHAR
                             || findCharType(next) == SPECIAL_IDEN
                             || findCharType(next) == EMPTY_CHAR) {
                        state = END;
                    }
                    else {
                        state = ERRORNUM;
                    }
                    break;
                case END:
                    break;
                default:
                    break;
                }

                // End FSM
                if (state == END) {
                    file.putback(next);
                    token_stream.push_back(Token(NUMBER, buffer, linum));
                    break;
                }
                else if (state == ERRORNUM) {
                    file.putback(next);
                    token_stream.push_back(Token(ERRORTOKEN, buffer, linum));
                    break;
                }
                else {
                    continue;
                }
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
}

