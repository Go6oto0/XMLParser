#include <fstream>
#include <iostream>
#include "XmlFile.h"
#include "CommandListener.h"
int main()
{
    CommandListener cmdl;
    XmlFile file;
    cmdl.run(file);

    // Temporarily comment this out
    // xml.serialize(std::cout);

    return 0;
}