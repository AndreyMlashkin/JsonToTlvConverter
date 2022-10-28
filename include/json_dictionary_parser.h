#pragma once

#ifdef _WIN32
  #define json_dictionary_parser_EXPORT __declspec(dllexport)
#else
  #define json_dictionary_parser_EXPORT
#endif

json_dictionary_parser_EXPORT void json_dictionary_parser();
