#include "doctest.h"
#include "../XML/XmlFile.h"
#include <sstream>

TEST_CASE("XmlFile: splitBySlash") {
    XmlFile file;

    Vector<String> result = file.splitBySlash("person/address/city");

    REQUIRE(result.getSize() == 3);

    CHECK(result[0] == String("person"));
    CHECK(result[1] == String("address"));
    CHECK(result[2] == String("city"));
}
TEST_CASE("XmlFile: getNameFromQuery without filter") {
    XmlFile file;

    CHECK(file.getNameFromQuery("person") == String("person"));
    CHECK(file.getNameFromQuery("address/city") == String("address"));
}
TEST_CASE("XmlFile: getNameFromQuery with filter") {
    XmlFile file;

    CHECK(file.getNameFromQuery("person[0]") == String("person"));
    CHECK(file.getNameFromQuery("person[@id]") == String("person"));
}
TEST_CASE("XmlFile: deserialize generates registry") {
    XmlFile file;

    std::stringstream ss;
    ss << "<person id=\"10\"><name>John</name></person>";

    file.deserialize(ss);

    XmlNode* person = file.getById("10");

    REQUIRE(person != nullptr);
    CHECK(person->getName() == String("person"));
}
TEST_CASE("XmlFile: automatic id generation") {
    XmlFile file;

    std::stringstream ss;
    ss << "<person></person>";

    file.deserialize(ss);

    XmlNode* generated = file.getById("auto_0");

    REQUIRE(generated != nullptr);
    CHECK(generated->getName() == String("person"));
}
TEST_CASE("XmlFile: duplicate ids are renamed") {
    XmlFile file;

    std::stringstream ss;
    ss << "<a id=\"x\"></a><b id=\"x\"></b>";

    file.deserialize(ss);

    REQUIRE(file.getById("x") != nullptr);
    REQUIRE(file.getById("x_1") != nullptr);

    CHECK(file.getById("x")->getName() == String("a"));
    CHECK(file.getById("x_1")->getName() == String("b"));
}
TEST_CASE("XmlFile: newChild creates child and registry entry") {
    XmlFile file;

    std::stringstream ss;
    ss << "<person id=\"0\"></person>";

    file.deserialize(ss);

    file.newChild("0");

    XmlNode* child = file.getById("auto_0");

    REQUIRE(child != nullptr);
    CHECK(child->getName() == String("newChild"));
}
TEST_CASE("XmlFile: copy constructor serializes same content") {
    XmlFile original;

    std::stringstream input;
    input << "<person id=\"0\"></person>";

    original.deserialize(input);

    XmlFile copy(original);

    std::stringstream originalOut;
    std::stringstream copyOut;

    original.serialize(originalOut);
    copy.serialize(copyOut);

    CHECK(copyOut.str() == originalOut.str());
}
TEST_CASE("XmlFile: move constructor transfers ownership") {
    XmlFile original;

    std::stringstream ss;
    ss << "<person id=\"0\"></person>";

    original.deserialize(ss);

    XmlFile moved(std::move(original));

    REQUIRE(moved.getById("0") != nullptr);
}