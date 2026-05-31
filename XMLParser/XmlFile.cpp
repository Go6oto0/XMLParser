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
        else if (cur == '-') {
            char next = is.peek();
            if (next == '-') {
                is.get(cur);
                is.get(cur);
            return new XmlComment(comment);
            }
        }
        comment.push_back(cur);
    }
}
void setName(std::istream& is, XmlNode& child, char first) {
    String name;
    name.push_back(first);
    while (true)
    {
        char next = is.peek();
        if (next == ' ' || next == '>' || !is)
        {
            child.setName(name);
            return;
        }
        
        char cur;
        is.get(cur);
        name.push_back(cur);
    }
}
String createAttribute(std::istream& is) {
    String attr;
    while (true) {
        char cur;
        if (!is.get(cur))
            return attr;
        if (cur == '=')
            return attr;
        attr.push_back(cur);
    }
}
String createValue(std::istream& is) {
   
    String value;
    char quote;
    if (!is.get(quote))
        return value;
    while (true) {
        char cur;
        if (!is.get(cur))
            return value;
        else if (cur == quote)
            return value;
        value.push_back(cur);
    }
}
void addAttribute(std::istream& is, XmlNode& child) {
    String attr = createAttribute(is);
    String value = createValue(is);
    child.addAttribute(XmlAttribute(attr, value));
}
void handleId(XmlNode& child) {
    if
}
XmlNode* createNode(std::istream& is) {
    XmlNode* child = new XmlNode;
    char cur;
    if (!is.get(cur))
        return child;
    setName(is, *child, cur);
    while (true)
    {
        if (!is.get(cur))
            return child;
        else if (cur == ' ')
            addAttribute(is, *child);
        else if (cur == '>') {
            handleId(*child);
            return child;
        }
    }
}
XmlText* createText(std::istream& is, char first) {
    String text;
    text.push_back(first);
    while (is && is.peek() != '<') {
        char cur;
        is.get(cur);
        text.push_back(cur);
    }
    return new XmlText(text);
}
bool isWhitespaceOnly(const String& str)
{
    for (size_t i = 0; i < str.getLen(); i++)
    {
        char ch = str[i];

        if (ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r')
        {
            return false;
        }
    }

    return true;
}
void buildTree(std::istream& is, XmlNode& curNode) {
    std::cout << curNode.getName();
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
            XmlText* text = createText(is, cur);
            if (!isWhitespaceOnly(text->getText()))
            {
                curNode.addChild(text);
            }
            else
                delete text;
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
