#pragma once
#include "String.h"
class XmlAttribute {
private:
	String name;
	String value;
public:
	XmlAttribute();
	XmlAttribute(const String& name, const String& value);
	XmlAttribute(String* name, String* value);
	const String& getName() const;
	const String& getValue() const;
};