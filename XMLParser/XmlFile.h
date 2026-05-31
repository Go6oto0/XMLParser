#pragma once
#include "XmlNode.h"
#include "String.h"
#include "Vector.hpp"
#include <map>
class XmlFile {
	XmlNode* root;
	size_t nextId;
	std::map<String, XmlNode*> registry;
private:
	void copy(const XmlFile& other);
	void free();
	void moveFrom(XmlFile&& other);
	void rebuildRegistry(XmlNode* curNode);
public:
	XmlFile();
	XmlFile(const XmlFile& other);
	XmlFile(XmlFile&& other);
	XmlFile& operator=(const XmlFile& other);
	XmlFile&& operator=(XmlFile&& other);
	~XmlFile();
	void deserialize(std::istream& is);
	void serialize(std::ostream& os);
	XmlNode* getById(String id);
	const XmlNode* getById(String id) const;
};