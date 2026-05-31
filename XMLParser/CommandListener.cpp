#include "CommandListener.h"

void CommandListener::run(XmlFile& file)
{
    String command;

    while (true)
    {
        std::cout << "> ";
        std::cin >> command;

        if (command == "open")
        {
            String path;
            std::cin >> path;
            file.open(path);
        }
        else if (command == "close")
        {
            file.close();
        }
        else if (command == "save")
        {
            file.save();
        }
        else if (command == "saveas")
        {
            String path;
            std::cin >> path;
            file.saveAs(path);
        }
        else if (command == "print")
        {
            file.serialize(std::cout);
        }
        else if (command == "select")
        {
            String id, key;
            std::cin >> id >> key;
            file.select(id, key);
        }
        else if (command == "set")
        {
            String id, key, value;
            std::cin >> id >> key >> value;
            file.set(id, key, value);
        }
        else if (command == "children")
        {
            String id;
            std::cin >> id;
            file.children(id);
        }
        else if (command == "child")
        {
            String id;
            size_t n;
            std::cin >> id >> n;
            file.child(id, n);
        }
        else if (command == "text")
        {
            String id;
            std::cin >> id;
            file.text(id);
        }
        else if (command == "delete")
        {
            String id, key;
            std::cin >> id >> key;
            file.deleteAttr(id, key);
        }
        else if (command == "newchild")
        {
            String id;
            std::cin >> id;
            file.newChild(id);
        }
        else if (command == "xpath")
        {
            String path;
            std::cin >> path;
            //file.xpath(path);
        }
        else if (command == "help")
        {
            //printHelp();
        }
        else if (command == "exit")
        {
            break;
        } 
        else
        {
            std::cout << "Unknown command\n";
        }
    }
}
