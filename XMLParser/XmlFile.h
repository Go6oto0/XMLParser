#pragma once
#include "XmlNode.h"
#include "String.h"
#include "Vector.hpp"
#include "XmlComment.h"
#include "XmlText.h"
#include <map>
class XmlFile {
	XmlNode* root;
	size_t nextId;
	std::map<String, XmlNode*> registry;
	String currentFileName;
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
	void serialize(std::ostream& os) const;
	XmlNode* getById(String id);
	XmlComment* createComment(std::istream& is);
	XmlNode* createNode(std::istream& is);
	void addAttribute(std::istream& is, XmlNode& child);
	String createValue(std::istream& is);
	String createAttribute(std::istream& is);
	void setName(std::istream& is, XmlNode& child, char first);
	String toString(size_t num);
	void select(const String& id, const String& key) const;
	void set(const String& id, const String& key, const String& value);
	void children(const String& id) const;
	void child(const String& id, size_t pos) const;
	void text(const String& id) const;
	void deleteAttr(const String& id, const String& key);
	void newChild(const String& id);
	void open(const String& filePath);
	void close();
	void save() const;
	void saveAs(const String& fileName) const;
	const XmlNode& getByTagName(const String& tagName) const;
	XmlText* createText(std::istream& is, char first);
	void reachEndOfTag(std::istream& is);
	bool isWhitespaceOnly(const String& str);
	void buildTree(std::istream& is, XmlNode& curNode);
	void handleId(XmlNode& child);
	const XmlNode* getById(String id) const;
	Vector<XmlNode*> applyQuery(const Vector<XmlNode*>& curResult, const String& miniQuery) const;
	Vector<String> splitBySlash(const String& query) const;
	Vector<XmlNode*> filterInd(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;
	Vector<XmlNode*> filterAllAttr(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;
	Vector<XmlNode*> filterByText(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;
	String getNameFromQuery(const String& query, size_t start = 0) const;
	Vector<XmlNode*> applyFilter(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;
	void xPath(const String& query) const;

};