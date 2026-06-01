#include "doctest.h"

#include "../XML/XmlNode.h"
#include "../XML/XmlText.h"
#include "../XML/XmlComment.h"

#include <sstream>

TEST_CASE("XmlNode: addAttribute and getAttributeInd") {
    XmlNode node("person");

    node.addAttribute(XmlAttribute("id", "0"));
    node.addAttribute(XmlAttribute("type", "student"));

    CHECK(node.getAttributeInd("id") == 0);
    CHECK(node.getAttributeInd("type") == 1);
    CHECK(node.getAttributeInd("missing") == -1);
}

TEST_CASE("XmlNode: addChild stores children") {
    XmlNode node("person");

    node.addChild(new XmlText("hello"));
    node.addChild(new XmlNode("name"));

    CHECK(node.getChildren().getSize() == 2);
}

TEST_CASE("XmlNode: getTextContent collects only direct text children") {
    XmlNode node("person");

    node.addChild(new XmlText("Hello "));
    node.addChild(new XmlNode("name"));
    node.addChild(new XmlText("World"));

    CHECK(node.getTextContent() == String("Hello World"));
}

TEST_CASE("XmlNode: getChildrenByName returns only matching XmlNode children") {
    XmlNode parent("person");

    parent.addChild(new XmlNode("name"));
    parent.addChild(new XmlText("ignored text"));
    parent.addChild(new XmlNode("address"));
    parent.addChild(new XmlNode("name"));

    Vector<XmlNode*> result = parent.getChildrenByName("name");

    REQUIRE(result.getSize() == 2);
    CHECK(result[0]->getName() == String("name"));
    CHECK(result[1]->getName() == String("name"));
}

TEST_CASE("XmlNode: serialize node with single text child on one line") {
    XmlNode node("name");
    node.addChild(new XmlText("John"));

    std::stringstream ss;
    node.serialize(ss);

    CHECK(ss.str() == "<name>John</name>");
}

TEST_CASE("XmlNode: serialize node with attributes and text") {
    XmlNode node("address");
    node.addAttribute(XmlAttribute("type", "home"));
    node.addChild(new XmlText("Sofia"));

    std::stringstream ss;
    node.serialize(ss);

    CHECK(ss.str() == "<address type=\"home\">Sofia</address>");
}

TEST_CASE("XmlNode: serialize nested nodes") {
    XmlNode person("person");
    person.addAttribute(XmlAttribute("id", "0"));

    XmlNode* name = new XmlNode("name");
    name->addChild(new XmlText("John"));

    person.addChild(name);

    std::stringstream ss;
    person.serialize(ss);

    CHECK(ss.str() == "<person id=\"0\">\n\t<name>John</name>\n</person>");
}

TEST_CASE("XmlNode: printText prints text from children") {
    XmlNode node("person");

    node.addChild(new XmlText("Hello"));
    node.addChild(new XmlText("World"));

    std::stringstream ss;
    node.printText(ss);

    CHECK(ss.str() == "HelloWorld");
}

TEST_CASE("XmlNode: clone creates independent deep copy") {
    XmlNode original("person");
    original.addAttribute(XmlAttribute("id", "0"));
    original.addChild(new XmlText("John"));

    XmlObject* clonedObject = original.clone();
    XmlNode* cloned = dynamic_cast<XmlNode*>(clonedObject);

    REQUIRE(cloned != nullptr);

    CHECK(cloned->getName() == String("person"));
    CHECK(cloned->getAttributeInd("id") == 0);
    CHECK(cloned->getTextContent() == String("John"));

    CHECK(cloned != &original);
    CHECK(cloned->getChildren()[0] != original.getChildren()[0]);

    delete clonedObject;
}

TEST_CASE("XmlNode: copy constructor creates independent children") {
    XmlNode original("person");
    original.addChild(new XmlText("John"));

    XmlNode copy(original);

    REQUIRE(copy.getChildren().getSize() == 1);
    REQUIRE(original.getChildren().getSize() == 1);

    CHECK(copy.getTextContent() == String("John"));
    CHECK(copy.getChildren()[0] != original.getChildren()[0]);
}

TEST_CASE("XmlNode: copy assignment replaces old children") {
    XmlNode first("first");
    first.addChild(new XmlText("Old"));

    XmlNode second("second");
    second.addChild(new XmlText("New"));

    first = second;

    CHECK(first.getName() == String("second"));
    CHECK(first.getTextContent() == String("New"));
    CHECK(first.getChildren()[0] != second.getChildren()[0]);
}

TEST_CASE("XmlNode: move constructor transfers children") {
    XmlNode original("person");
    original.addChild(new XmlText("John"));

    XmlNode moved(std::move(original));

    CHECK(moved.getName() == String("person"));
    CHECK(moved.getTextContent() == String("John"));
    CHECK(moved.getChildren().getSize() == 1);
}

TEST_CASE("XmlNode: move assignment replaces current content") {
    XmlNode destination("old");
    destination.addChild(new XmlText("Old"));

    XmlNode source("new");
    source.addChild(new XmlText("New"));

    destination = std::move(source);

    CHECK(destination.getName() == String("new"));
    CHECK(destination.getTextContent() == String("New"));
    CHECK(destination.getChildren().getSize() == 1);
}