

#include <iostream>
#include <string>

#include "../Tokenizer.h"

using namespace lolilang;

// Dump token stream for debug
void dump_tokens(Tokenizer &tokenizer)
{
    Tokenizer::TokenStream_t token_stream = tokenizer.token_stream;
    for (std::vector<Token>::iterator i = token_stream.begin();
         i != token_stream.end();
         ++i) {
        
        std::cout << i->type 
                  << "\t"   
                  << i->token 
                  << "\t"
                  << i->linum
                  << std::endl;
    }
}



int main()
{
    Tokenizer tokenizer;

    tokenizer.scan(std::cin);

    dump_tokens(tokenizer);
}

    
