#include "XmlComment.h"

const String& XmlComment::getComment() const {
    return comment;
}

void XmlComment::serialize(std::ostream& os, size_t indent) const {
    printIndents(os, indent);
    os << "<!-- " << comment << " -->";
}

XmlObject* XmlComment::clone() const
{
    return new XmlComment(*this);
}

XmlComment::XmlComment(const String& str) : comment(str)
{
}
