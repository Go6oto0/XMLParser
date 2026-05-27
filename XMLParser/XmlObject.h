#pragma once
#include <iostream>
class XmlObject {
protected:
	size_t id;
public:
	virtual void serialize(std::ostream& os, size_t indent = 0) const = 0;
	size_t getId() const;
	virtual XmlObject* clone() const = 0;
	virtual ~XmlObject() = default;
	void printIndents(std::ostream& os, size_t indent = 0) const;
};