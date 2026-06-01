#pragma once
#include "XmlObject.h"
#include "String.h"
class XmlComment : public XmlObject {
	String comment;
public:
	const String& getComment() const;
	void serialize(std::ostream& os, size_t indent = 0) const override;
	void printText(std::ostream& os = std::cout) const override;
	XmlObject* clone() const override;
	XmlComment(const String& str);

};