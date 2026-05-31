#include "XmlFile.h"
#include "XmlComment.h"
#include "XmlText.h"
void XmlFile::rebuildRegistry(XmlNode* curNode) {
    if (curNode == nullptr)
    {
        return;
    }
    registry[curNode->getId()] = curNode;
    const Vector<XmlObject*>& children = curNode->getChildren();
    size_t len = children.getSize();
    for (size_t i = 0; i < len; i++)
    {
        XmlNode* child = dynamic_cast<XmlNode*>(children[i]);
        if (child)
        {
            rebuildRegistry(child);
        }
    }
}

void XmlFile::copy(const XmlFile& other) {
    root = static_cast<XmlNode*>(other.root->clone());
    nextId = other.nextId;
    rebuildRegistry(other.root);
}

void XmlFile::free()
{
    registry.clear();
    delete root;
    root = nullptr;
    nextId = 0;
}

void XmlFile::moveFrom(XmlFile&& other)
{
    root = other.root;
    nextId = other.nextId;
    registry = std::move(other.registry);
    other.root = nullptr;
    other.nextId = 0;
    other.registry.clear();
}

XmlFile::XmlFile()
{
    root = nullptr;
    nextId = 0;
    registry.clear();
}

XmlFile::XmlFile(const XmlFile& other)
{
    copy(other);
}

XmlFile::XmlFile(XmlFile&& other)
{
    moveFrom(std::move(other));
}

XmlFile& XmlFile::operator=(const XmlFile& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

XmlFile&& XmlFile::operator=(XmlFile&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return std::move(*this);
}

XmlFile::~XmlFile()
{
    free();
}
void reachEndOfTag(std::istream& is) {
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;
        else if (cur == '>')
            return;
    }
}
XmlComment* createComment(std::istream& is) {
    String comment;
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return new XmlComment(comment);
        else if (cur == '>')
            return new XmlComment(comment);
        comment.push_back(cur);
    }
}
void setName(std::istream& is, XmlNode& child, char first) {
    String name;
    name.push_back(first);
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;
        char next = is.peek();
        if (cur == ' ' || next == '>') {
            child.setName(name);
            return;
        }
        name.push_back(cur);
    }
}
String createAttribute(std::istream& is) {
    String attr;
    while (true) {
        char cur;
        if (!is.get(cur))
            return attr;
        if (cur == '=' || cur == ' ')
            return attr;
        attr.push_back(cur);
    }
}
String createValue(std::istream& is) {
   
    String value;
    bool closingQuotes = false;
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return value;
        char next = is.peek();
        if (next != ' ')
            break;
    }
    while (true) {
        char cur;
        if (!is.get(cur))
            return value;
        else if ((cur == '"' || cur == '\'') && closingQuotes)
            return value;
        else if ((cur == '"' || cur == '\'') && closingQuotes == false)
            closingQuotes = true;
        else if (!closingQuotes)
            value.push_back(cur);
        else
            return value;
    }
}
void addAttribute(std::istream& is, XmlNode& child) {
    String attr;
    String value;
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;
        else if (cur == ' ')
        {
            attr = createAttribute(is);
            value = createValue(is);
            child.addAttribute(XmlAttribute(attr, value));
        }
        else if (cur == '>')
            return;
    }
}
XmlNode* createNode(std::istream& is) {
    XmlNode* child = new XmlNode;
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;
        else if (!child->getName())
            setName(is, *child, cur);
        else if (cur != '>')
            addAttribute(is, *child);
        else
            return child;
    }
}
XmlText* createText(std::istream& is, char first) {
    String text;
    text.push_back(first);
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return new XmlText(text);
        char next = is.peek();
        if (next == '<')
            return new XmlText(text);
        text.push_back(cur);
    }
}
void buildTree(std::istream& is, XmlNode& curNode) {
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;

        if (cur == '<') {
            char next = is.peek();
            if (next == '/') {
                reachEndOfTag(is);
                return;
            }
            else if (next == '!') {
                is.get(cur);
                is.get(cur);
                is.get(cur);
                curNode.addChild(createComment(is));
            }
            else
            {
                XmlNode* child = createNode(is);
                curNode.addChild(child);
                buildTree(is, *child);
            }
        }
        else {
            curNode.addChild(createText(is, cur));
        }

    }
}
void XmlFile::deserialize(std::istream& is)
{
    root = new XmlNode("root");
    buildTree(is, *root);
}

void XmlFile::serialize(std::ostream& os)
{
    if (root)
    {
        root->serialize(os);
    }
}

XmlNode* XmlFile::getById(String id)
{
    return registry[id];
}

const XmlNode* XmlFile::getById(String id) const {
    return registry.at(id);
}
