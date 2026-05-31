#include "XmlNode.h"

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
