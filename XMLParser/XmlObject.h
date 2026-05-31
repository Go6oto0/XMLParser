#pragma once
#include <iostream>
class XmlObject {
public:
	virtual void serialize(std::ostream& os, size_t indent = 0) const = 0;
	virtual XmlObject* clone() const = 0;
	virtual ~XmlObject() = default;
	void printIndents(std::ostream& os, size_t indent = 0) const;
};