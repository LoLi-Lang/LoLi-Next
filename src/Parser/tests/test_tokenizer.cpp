#include <iostream>
#include <string>

#include "../Tokenizer.h"

using namespace lolilang;
using namespace tokenizer;

// Dump token stream for debug
void dump_tokens(Tokenizer &tokenizer)
{
    while(1) {
        Token &t = tokenizer.get();
        if (t.type == EOF_TOKEN) {
            break;
        }
        
        std::cout << t.type << "\t"
                  << t.token << "\t"
                  << t.linum << "\n";
    }
}



int main()
{
    Tokenizer tokenizer;

    tokenizer.scan(std::cin);

    dump_tokens(tokenizer);
}

    
