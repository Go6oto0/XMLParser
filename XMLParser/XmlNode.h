#pragma once
#include "XmlObject.h"
#include "XmlAttribute.h"
#include "Vector.hpp"
#include "String.h"
class XmlNode : public XmlObject {
private:
	String name;
	Vector<XmlAttribute> attributes;
	Vector<XmlObject*> children;
private:
	void copy(const XmlNode& other);
	void free();
public:
	XmlNode();
	XmlNode(const XmlNode& other);
	XmlNode& operator=(const XmlNode& other);
	~XmlNode();
	void addAttribute(const XmlAttribute& attribute);
	void addChild(const XmlObject* child);
	void serialize(std::ostream& os, size_t indent = 0) const override;
	XmlObject* clone() const override;
};