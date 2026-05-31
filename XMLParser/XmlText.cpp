#include "XmlText.h"

const String& XmlText::getText() const {
    return text;
}

void XmlText::serialize(std::ostream& os, size_t indent) const {
    printIndents(os, indent);
    os << text;
}
XmlText::XmlText(const String& text) : text(text) {}

XmlObject* XmlText::clone() const
{
    return new XmlText(*this);
}
