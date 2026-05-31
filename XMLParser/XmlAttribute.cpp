#include "XmlAttribute.h"

XmlAttribute::XmlAttribute() = default;
XmlAttribute::XmlAttribute(const String& name, const String& value) : name(name), value(value)
{
}

XmlAttribute::XmlAttribute(String* name, String* value) : name(*name), value(*value)
{
}

const String& XmlAttribute::getName() const
{
    return name;
}

const String& XmlAttribute::getValue() const
{
    return value;
}
