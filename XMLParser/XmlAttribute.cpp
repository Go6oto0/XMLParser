#include "XmlAttribute.h"

XmlAttribute::XmlAttribute() = default;
XmlAttribute::XmlAttribute(const String& name, const String& value) : name(name), value(value)
{
}

void XmlAttribute::setValue(const String& val)
{
    value = val;
}


const String& XmlAttribute::getName() const
{
    return name;
}

const String& XmlAttribute::getValue() const
{
    return value;
}
