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

XmlNode& XmlNode::operator=(const XmlNode& other) {
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}
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

void XmlNode::addAttribute(const XmlAttribute& attribute) {
	attributes.push_back(attribute);
}

void XmlNode::addChild(XmlObject* child) {

	children.push_back(child);
}

const Vector<XmlAttribute>& XmlNode::getAttributes() const
{
	return attributes;
}

Vector<XmlAttribute>& XmlNode::getAttributes()
{
	return attributes;
}

const Vector<XmlObject*>& XmlNode::getChildren() const
{
	return children;
}

void XmlNode::serialize(std::ostream& os, size_t indent) const {
	printIndents(os, indent);
	os << "<" << name;
	for (const XmlAttribute& attr : attributes) {
		os << " " << attr.getName() << "=\"" << attr.getValue() << "\"";
	}
	os << ">";
	os << '\n';
	for (const XmlObject* child : children) {
		child->serialize(os, indent + 1);
		os << '\n';
	}
	printIndents(os, indent);
	os << "</" << name << ">";

}
XmlNode::XmlNode(const String& name) : name(name) {}
void XmlNode::printText(std::ostream& os) const {
	for (const XmlObject* child : children)
	{
		child->printText(os);
	}
}
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
