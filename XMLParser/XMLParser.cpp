#include <fstream>
#include <iostream>
#include "XmlFile.h"

int main()
{
    std::ifstream file("test.txt");

    if (!file.is_open())
    {
        std::cout << "Failed to open file\n";
        return 1;
    }

    XmlFile xml;

    std::cout << "Before deserialize\n";
    xml.deserialize(file);

    std::cout << "After deserialize\n";
    xml.serialize(std::cout);
    // Temporarily comment this out
    // xml.serialize(std::cout);

    return 0;
}