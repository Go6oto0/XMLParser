#include "doctest.h"
#include "../String/String.h"

#include <sstream>

TEST_CASE("String: copy constructor creates independent copy") {
    String original("hello");
    String copy(original);

    original[0] = 'H';

    CHECK(original == String("Hello"));
    CHECK(copy == String("hello"));
}

TEST_CASE("String: copy assignment handles existing data and self-assignment") {
    String first("first");
    String second("second");

    SUBCASE("Normal copy assignment") {
        first = second;

        CHECK(first == String("second"));
        CHECK(second == String("second"));
    }

    SUBCASE("Self-assignment keeps value") {
        first = first;

        CHECK(first == String("first"));
    }
}

TEST_CASE("String: move constructor transfers content") {
    String original("move me");

    String moved(std::move(original));

    CHECK(moved == String("move me"));
    CHECK(original.getLen() == 0);
}

TEST_CASE("String: move assignment replaces old content") {
    String destination("old");
    String source("new value");

    destination = std::move(source);

    CHECK(destination == String("new value"));
    CHECK(source.getLen() == 0);
}

TEST_CASE("String: append resizes and preserves content") {
    String str("abc");

    str.append("defghijklmnop");

    CHECK(str == String("abcdefghijklmnop"));
    CHECK(str.getLen() == 16);
}

TEST_CASE("String: operator+= supports chained appending") {
    String str("Hello");

    str += String(", ");
    str += String("world");
    str += String("!");

    CHECK(str == String("Hello, world!"));
}

TEST_CASE("String: operator+ creates new string without changing operands") {
    String first("abc");
    String second("def");

    String result = first + second;

    CHECK(result == String("abcdef"));
    CHECK(first == String("abc"));
    CHECK(second == String("def"));
}

TEST_CASE("String: push_back resizes multiple times") {
    String str;

    for (char c = 'a'; c <= 'z'; c++) {
        str.push_back(c);
    }

    CHECK(str.getLen() == 26);
    CHECK(str[0] == 'a');
    CHECK(str[25] == 'z');
    CHECK(str == String("abcdefghijklmnopqrstuvwxyz"));
}

TEST_CASE("String: clear resets string to empty reusable state") {
    String str("hello");

    str.clear();

    CHECK(str.getLen() == 0);
    CHECK(!str);

    str.push_back('a');
    str += String("bc");

    CHECK(str == String("abc"));
}

TEST_CASE("String: input operator skips leading whitespace and reads one word") {
    std::stringstream ss("   hello world");
    String str;

    ss >> str;

    CHECK(str == String("hello"));
}

TEST_CASE("String: output operator writes stored text") {
    String str("test value");
    std::stringstream ss;

    ss << str;

    CHECK(ss.str() == "test value");
}

TEST_CASE("String: comparison operators") {
    CHECK(String("abc") == String("abc"));
    CHECK_FALSE(String("abc") == String("abd"));

    CHECK(String("abc") < String("abd"));
    CHECK(String("abc") < String("abcd"));
    CHECK_FALSE(String("xyz") < String("abc"));
}