#include "jsontotlvconverterinputstrategy.h"
#include "jsontotlvconverter.h"

#include <iostream>
#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[])
{
    if(argc == 2 && strcmp(argv[1], "help") == 0 ||
       (argc != 1 && argc != 3))
    {
        std::cout << "Programm takes 0 or 2 arguments on start:\n"
                     "If you specify no arguments, programm will read data from standard input and write to standard output stream.\n"
                     "In other case, user shall specify input and output files\n";
        return 0;
    }

    JsonToTlvConverterInputStrategyFactory factory;
    auto converterInputStrategy = factory.createStrategy(argc, argv);


    JsonToTlvConverter converter(converterInputStrategy);
    if(argc == 1)
    {
        converter.setInputSource(std::cin);
        converter.setOutputSource(std::cout);
    }
    else
    {
        converter.setInputSource(argv[1]);
        converter.setOutputSource(argv[2]);
    }

    converter.convertAll();
    return 0;
}
