#pragma once
#include "String.h"
class XmlAttribute {
private:
	String name;
	String value;
public:
	XmlAttribute();
	XmlAttribute(const String& name, const String& value);
	void setValue(const String& val);
	const String& getName() const;
	const String& getValue() const;
};