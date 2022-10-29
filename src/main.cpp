#include <jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfactory.h>
#include <jsontotlvconverteroutputstrategy/jsontotlvconverteroutputstrategyfactory.h>
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

    auto converterInputStrategy  = JsonToTlvConverterInputStrategyFactory::createStrategy(argc, argv);
    auto converterOutputStrategy = JsonToTlvConverterOutputStrategyFactory::createStrategy(argc, argv);

    JsonToTlvConverter converter(converterInputStrategy, converterOutputStrategy);

    converter.convertAll();
    return 0;
}
