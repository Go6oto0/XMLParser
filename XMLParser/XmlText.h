#pragma once
#include "XmlObject.h"
#include "String.h"
class XmlText : public XmlObject {
	String text;
public:
	const String& getText() const;
	XmlText(const String& text);
	void printText(std::ostream& os = std::cout) const override;
	void serialize(std::ostream& os, size_t indent = 0) const override;
	XmlObject* clone() const override;
};