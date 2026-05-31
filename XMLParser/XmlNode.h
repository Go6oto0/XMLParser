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
	String id;
private:
	void copy(const XmlNode& other);
	void free();
public:
	XmlNode();
	XmlNode(const XmlNode& other);
	XmlNode& operator=(const XmlNode& other);
	~XmlNode();
	const String& getId() const;
	void addAttribute(const XmlAttribute& attribute);
	void addChild(XmlObject* child);
	const Vector<XmlAttribute>& getAttributes() const;
	Vector<XmlAttribute>& getAttributes();
	int getAttributeInd(const String& attr) const;
	XmlNode(const String&);
	const String& getName() const;
	void setName(const String&);
	const Vector<XmlObject*>& getChildren() const;
	void serialize(std::ostream& os, size_t indent = 0) const override;
	XmlObject* clone() const override;
};