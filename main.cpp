// bellhop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "bellhopM.h"

int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";
    if (argc == 1 || argv == nullptr)
        return -1;

    std::string filename = argv[1];
    if (filename.empty())
        std::cout << "'No envfil has been selected\n";

	bellhopM(filename);

}

