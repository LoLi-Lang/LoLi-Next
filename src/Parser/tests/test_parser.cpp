#include <iostream>
#include <string>

#include "../Tokenizer.h"
#include "../Parser.h"

using namespace lolilang;


int main()
{
    Tokenizer tokenizer;

    tokenizer.scan(std::cin);

    Parser parser(tokenizer);

    parser.parse();
}

    
