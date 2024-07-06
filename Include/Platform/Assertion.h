#pragma once
#include <iostream>
#define Assertion(expression, message) if(expression == false) assert_func(message, __LINE__, __func__, __FILE__)
#define AssertionAlways(message) assert_func(message, __LINE__, __func__, __FILE__)
void assert_func(const std::string& message, int line, char const *function, char const *file)
{
    std::cout << "ASSERTION FAILED: \n" <<
              "Message: " << message << "\n" <<
              "Line: " << line << "\n" <<
              "Function: " << function << "\n" <<
              "File: " << file << "\n";

    exit(1);
}
