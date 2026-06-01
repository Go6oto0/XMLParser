#include "XmlFile.h"
#include <fstream>
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
    rebuildRegistry(root);
    currentFileName = other.currentFileName;
}

void XmlFile::free()
{
    registry.clear();
    delete root;
    root = nullptr;
    nextId = 0;
    currentFileName.clear();
}

void XmlFile::moveFrom(XmlFile&& other)
{
    root = other.root;
    nextId = other.nextId;
    registry = std::move(other.registry);
    currentFileName = std::move(other.currentFileName);
    other.root = nullptr;
    other.nextId = 0;
    other.registry.clear();
    other.currentFileName.clear();
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

XmlFile& XmlFile::operator=(XmlFile&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

XmlFile::~XmlFile()
{
    free();
}
String XmlFile::toString(size_t num)
{
    if (num == 0)
        return "0";

    String result;

    while (num > 0)
    {
        char digit = (num % 10) + '0';
        result.push_back(digit);
        num /= 10;
    }

    // reverse
    size_t len = result.getLen();
    for (size_t i = 0; i < len / 2; i++)
    {
        char temp = result[i];
        result[i] = result[len - 1 - i];
        result[len - 1 - i] = temp;
    }

    return result;
}
void XmlFile::select(const String& id, const String& key) const
{
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    const XmlNode* node = registry.at(id);
    int ind = node->getAttributeInd(key);
    if (ind == -1)
    {
        std::cout << "no such attribute" << "\n";
        return;
    }
    std::cout << node->getAttributes()[ind].getValue() << "\n";
}
void XmlFile::set(const String& id, const String& key, const String& value)
{
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    XmlNode* node = registry.at(id);
    int ind = node->getAttributeInd(key);
    if (ind == -1)
    {
        std::cout << "no such attribute" << "\n";
        return;
    }
    node->getAttributes()[ind].setValue(value);
}
void XmlFile::children(const String& id) const
{
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    const XmlNode* node = registry.at(id);
    const Vector<XmlObject*>& children = node->getChildren();
    size_t len = children.getSize();
    for (size_t i = 0; i < len; i++)
    {
        const XmlNode* child = dynamic_cast<const XmlNode*>(children[i]);
        if (!child)
        {
            continue;
        }
        int ind = child->getAttributeInd("id");
        if (ind != -1)
        {
            std::cout << child->getAttributes()[ind].getValue() << "\n";
        }
    }
}
void XmlFile::child(const String& id, size_t pos) const {
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    const XmlNode* node = registry.at(id);
    const Vector<XmlObject*>& children = node->getChildren();
    size_t len = children.getSize();
    size_t current = 0;
    for (size_t i = 0; i < len; i++)
    {
        const XmlNode* child = dynamic_cast<const XmlNode*>(children[i]);
        if (!child)
        {
            continue;
        }
        if (current == pos)
        {
            int ind = child->getAttributeInd("id");
            if (ind != -1)
            {
                std::cout << child->getAttributes()[ind].getValue() << "\n";
                return;
            }
        }
        current++;
    }
    std::cout << "no such child" << "\n";
}
void XmlFile::text(const String& id) const {
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    const XmlNode* node = registry.at(id);
    const Vector<XmlObject*>& children = node->getChildren();
    size_t len = children.getSize();
    for (size_t i = 0; i < len; i++)
    {
        const XmlText* child = dynamic_cast<const XmlText*>(children[i]);
        if (!child)
        {
            continue;
        }
        std::cout << child->getText() << "\n";
    }
}
void XmlFile::deleteAttr(const String& id, const String& key) {
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    XmlNode* node = registry.at(id);
    int ind = node->getAttributeInd(key);
    if (ind == -1)
    {
        std::cout << "no such attribute" << "\n";
        return;
    }
    Vector<XmlAttribute>& attributes = node->getAttributes();
    attributes[ind] = attributes[attributes.getSize() - 1];
    attributes.pop_back();
}
void XmlFile::newChild(const String& id) {
    if (registry.count(id) == 0)
    {
        std::cout << "no such element" << "\n";
        return;
    }
    XmlNode* node = registry.at(id);
    XmlNode* child = new XmlNode();
    child->setName("newChild");
    String newId = String("auto_") + toString(nextId);
    nextId++;

    while (registry.count(newId) != 0)
    {
        newId = String("auto_") + toString(nextId);
        nextId++;
    }
    child->addAttribute(XmlAttribute("id", newId));
    node->addChild(child);
    registry[newId] = child;
}
void XmlFile::reachEndOfTag(std::istream& is) {
    while (true)
    {
        char cur;
        if (!is.get(cur))
            return;
        else if (cur == '>')
            return;
    }
}
XmlComment* XmlFile::createComment(std::istream& is) {
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
void XmlFile::setName(std::istream& is, XmlNode& child, char first) {
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
String XmlFile::createAttribute(std::istream& is) {
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
String XmlFile::createValue(std::istream& is) {
   
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
void XmlFile::addAttribute(std::istream& is, XmlNode& child) {
    String attr = createAttribute(is);
    String value = createValue(is);
    child.addAttribute(XmlAttribute(attr, value));
}
void XmlFile::handleId(XmlNode& child) {
    int ind = child.getAttributeInd("id");
    if (ind == -1)
    {
        String newId = String("auto_") + toString(nextId++);
        child.addAttribute(XmlAttribute("id", newId));
        registry[newId] = &child;
        return;
    }
    String id = child.getAttributes()[ind].getValue();

    if (registry.find(id) == registry.end())
    {
        registry[id] = &child;
        return;
    }

    size_t suffix = 1;
    String newId;

    do
    {
        newId = id + String("_") + toString(suffix++);
    } while (registry.find(newId) != registry.end());

    child.getAttributes()[ind].setValue(newId);
    registry[newId] = &child;
}
XmlNode* XmlFile::createNode(std::istream& is) {
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
XmlText* XmlFile::createText(std::istream& is, char first) {
    String text;
    text.push_back(first);
    while (is && is.peek() != '<') {
        char cur;
        is.get(cur);
        text.push_back(cur);
    }
    return new XmlText(text);
}
bool XmlFile::isWhitespaceOnly(const String& str)
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
void XmlFile::buildTree(std::istream& is, XmlNode& curNode) {
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
void XmlFile::serialize(std::ostream& os) const
{
    if (root)
    {
        for (size_t i = 0; i < root->getChildren().getSize(); i++)
        {

            root->getChildren()[i]->serialize(os);
        }
    }
}
XmlNode* XmlFile::getById(String id)
{
    return registry[id];
}

void XmlFile::open(const String& fileName) {
    std::ifstream ifs(fileName.getPtr());
    if (!ifs.is_open())
    {
        std::cout << "couldn't open file" << "\n";
        return;
    }
    free();
    currentFileName = fileName;
    deserialize(ifs);
}
void XmlFile::close() {
    free();
}
void XmlFile::save() const {
    if (!currentFileName)
    {
        std::cout << "no file opened";
        return;
    }
    std::ofstream ofs(currentFileName.getPtr());
    if (!ofs.is_open())
    {
        std::cout << "couldnt save file";
        return;
    }
    serialize(ofs);
}
void XmlFile::saveAs(const String& fileName) const {
    if (!currentFileName)
    {
        std::cout << "no file opened";
        return;
    }
    std::ofstream ofs(fileName.getPtr());
    if (!ofs.is_open())
    {
        std::cout << "couldnt save file";
        return;
    }
    serialize(ofs);
}
String XmlFile::getNameFromQuery(const String& query, size_t start) const {
    String result;
    size_t len = query.getLen();
    for (size_t i = start; i < len; i++)
    {
        if (query[i] == '/' || query[i] == '[' || query[i] == ']')
        {
            return result;
        }
        result.push_back(query[i]);
    }
    return result;
}
Vector<String> XmlFile::splitBySlash(const String& query) const{
    Vector<String> miniQueries;
    String curQuery;
    size_t len = query.getLen();
    for (size_t i = 0; i < len; i++)
    {
        if (query[i] == '/')
        {
            miniQueries.push_back(curQuery);
            curQuery.clear();
            continue;
        }
        curQuery.push_back(query[i]);
    }
    miniQueries.push_back(curQuery);
    return miniQueries;
}
Vector<XmlNode*> XmlFile::filterInd(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const {
    Vector<XmlNode*> result;
    size_t ind = 0;
    for (size_t i = filterStart + 1; miniQuery[i] >= '0' && miniQuery[i] <= '9'; i++)
    {
        ind *= 10;
        ind += miniQuery[i] - '0';
    }
    if (ind >= nodes.getSize())
    {
        return result;
    }
    result.push_back(nodes[ind]);
    return result;
}
Vector<XmlNode*> XmlFile::filterAllAttr(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const {
    Vector<XmlNode*> result;
    String attr;
    for (size_t i = filterStart + 2; miniQuery[i] != ']'; i++)
    {
        attr.push_back(miniQuery[i]);
    }
    for (size_t i = 0; i < nodes.getSize(); i++)
    {
        int ind = nodes[i]->getAttributeInd(attr);
        if (ind != -1)
        {
            std::cout << nodes[i]->getAttributes()[ind].getValue() << '\n';
        }
    }
    return result;
}
Vector<XmlNode*> XmlFile::filterByText(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const {
    Vector<XmlNode*> result;
    String name;
    for (size_t i = filterStart + 1; miniQuery[i] != '='; i++)
    {
        name.push_back(miniQuery[i]);
    }
    String val;
    for (size_t i = filterStart + name.getLen() + 3; miniQuery[i] != '"'; i++)
    {
        val.push_back(miniQuery[i]);
    }
    for (size_t i = 0; i < nodes.getSize(); i++)
    {
        Vector<XmlNode*> children = nodes[i]->getChildrenByName(name);
        for (size_t k = 0; k < children.getSize(); k++)
        {
            if (children[k]->getTextContent() == val)
            {
                result.push_back(nodes[i]);
            }
        }
    }
    return result;
}
Vector<XmlNode*> XmlFile::applyFilter(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const {
    if (miniQuery[filterStart + 1] >= '0' && miniQuery[filterStart + 1] <= '9')
    {
        return filterInd(nodes, miniQuery, filterStart);
    }
    if (miniQuery[filterStart + 1] == '@')
    {
        return filterAllAttr(nodes, miniQuery, filterStart);
    }
    if (miniQuery[filterStart + 1] >= 'a' && miniQuery[filterStart + 1] <= 'z')
    {
        return filterByText(nodes, miniQuery, filterStart);
    }
    std::cout << "No such filter" << '\n';
    Vector<XmlNode*> result;
    return result;
}
Vector<XmlNode*> XmlFile::applyQuery(const Vector<XmlNode*>& curResult, const String& miniQuery) const {
    String name = getNameFromQuery(miniQuery);
    Vector<XmlNode*> newResult;
    for (size_t i = 0; i < curResult.getSize(); i++)
    {
        Vector<XmlNode*> children = curResult[i]->getChildrenByName(name);

        for (size_t j = 0; j < children.getSize(); j++)
        {
            newResult.push_back(children[j]);
        }
    }
    if (miniQuery.getLen() == name.getLen())
    {
        return newResult;
    }
    size_t filterStart = name.getLen();
    if (miniQuery[filterStart] != '[')
    {
        return newResult;
    }
    return applyFilter(newResult, miniQuery, filterStart);
}
void XmlFile::xPath(const String& query) const {
    const Vector<String> miniQueries = splitBySlash(query);
    Vector<XmlNode*> base;
    base.push_back(root);
    for (size_t i = 0; i < miniQueries.getSize(); i++)
    {
        base = applyQuery(base, miniQueries[i]);
    }
    for (size_t i = 0; i < base.getSize(); i++)
    {
        base[i]->printText();
    }
}