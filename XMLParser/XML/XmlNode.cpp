#include "XmlNode.h"
#include "XmlText.h"
void XmlNode::copy(const XmlNode& other) {
	id = other.id;
	name = other.name;
	attributes = other.attributes;
	for (XmlObject* xmlObj : other.children) {
		children.push_back(xmlObj->clone());
	}
}
void XmlNode::moveFrom(XmlNode&& other) {
	id = other.id;
	name = other.name;
	attributes = other.attributes;
	children = other.children;
	other.id.clear();
	other.name.clear();
	other.attributes.clear();
	other.children.clear();
}

void XmlNode::free() {
	for (XmlObject* child : children)
	{
		delete child;
	}
	children.clear();
}

XmlNode::XmlNode() = default;

XmlNode::XmlNode(const XmlNode& other) {
	copy(other);
}
XmlNode::XmlNode(XmlNode&& other) {
	moveFrom(std::move(other));
}
XmlNode& XmlNode::operator=(XmlNode&& other) {
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
XmlNode& XmlNode::operator=(const XmlNode& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
/**
 * @brief Finds the index of an attribute by name.
 *
 * @param attr Name of the attribute to search for.
 * @return Index of the attribute if found, otherwise -1.
 */
int XmlNode::getAttributeInd(const String& attr) const {
	for (size_t i = 0; i < attributes.getSize(); i++)
	{
		if (attr == attributes[i].getName())
		{
			return i;
		}
	}
	return -1;
}
XmlNode::~XmlNode()
{
	free();
}
/**
 * @brief Adds an attribute to the XML node.
 *
 * @param attribute Attribute to add.
 */
void XmlNode::addAttribute(const XmlAttribute& attribute) {
	attributes.push_back(attribute);
}
/**
 * @brief Adds a child XML object to the node.
 *
 * The node takes ownership of the provided pointer.
 *
 * @param child Child object to add.
 */
void XmlNode::addChild(XmlObject* child) {

	children.push_back(child);
}
/**
 * @brief Returns the node attributes.
 *
 * @return Constant reference to the collection of attributes.
 */
const Vector<XmlAttribute>& XmlNode::getAttributes() const
{
	return attributes;
}
/**
 * @brief Returns the node attributes.
 *
 * @return Reference to the collection of attributes.
 */
Vector<XmlAttribute>& XmlNode::getAttributes()
{
	return attributes;
}
/**
 * @brief Returns the child XML objects of the node.
 *
 * @return Constant reference to the collection of child objects.
 */
const Vector<XmlObject*>& XmlNode::getChildren() const
{
	return children;
}
/**
 * @brief Writes the XML node and its children to an output stream.
 *
 * The node is written with indentation according to its depth in the tree.
 *
 * @param os Output stream to write to.
 * @param indent Indentation level of the node.
 */
void XmlNode::serialize(std::ostream& os, size_t indent) const
{
    printIndents(os, indent);

    os << "<" << name;

    for (const XmlAttribute& attr : attributes)
    {
        os << ' ' << attr.getName()
           << "=\"" << attr.getValue() << "\"";
    }

    if (children.getSize() == 1 &&
        dynamic_cast<const XmlText*>(children[0]))
    {
        os << '>';
        children[0]->serialize(os, 0);
        os << "</" << name << '>';
        return;
    }

    os << ">\n";

    for (const XmlObject* child : children)
    {
        child->serialize(os, indent + 1);
        os << '\n';
    }

    printIndents(os, indent);
    os << "</" << name << ">";
}
/**
 * @brief Creates an XML node with a given name.
 *
 * @param name Name of the XML element.
 */
XmlNode::XmlNode(const String& name) : name(name) {}
/**
 * @brief Prints the text content of all child objects.
 *
 * @param os Output stream to print to.
 */
void XmlNode::printText(std::ostream& os) const {
	for (const XmlObject* child : children)
	{
		child->printText(os);
		std::cout << " ";
	}
}
/**
 * @brief Collects the direct text content of the XML node.
 *
 * @return String containing the text from direct text children.
 */
String XmlNode::getTextContent() const
{
	String text;
	for (XmlObject* child : children)
	{
		XmlText* childText = dynamic_cast<XmlText*>(child);
		if (childText)
		{
			text += childText->getText();
		}
		/*XmlNode* childNode = dynamic_cast<XmlNode*>(child);

		if (childNode)
		{
			text += childNode->getTextContent();
		}*/
	}

	return text;
}
/**
 * @brief Finds all child elements with a given name.
 *
 * @param name Name of the child elements to search for.
 * @return Collection of matching child nodes.
 */
Vector<XmlNode*> XmlNode::getChildrenByName(const String& name) const
{
	Vector<XmlNode*> result;
	for (XmlObject* child : children)
	{
		XmlNode* node = dynamic_cast<XmlNode*>(child);
		if (!node)
		{
			continue;
		}
		if (node->getName() == name)
		{
			result.push_back(node);
		}
	}
	return result;
}
XmlObject* XmlNode::clone() const {
	return new XmlNode(*this);
}
const String& XmlNode::getId() const {
	return id;
}
const String& XmlNode::getName() const {
	return name;
}

void XmlNode::setName(const String& name)
{
	this->name = name;
}
