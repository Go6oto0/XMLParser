#include "XmlObject.h"

void XmlObject::printIndents(std::ostream& os, size_t indent) const {
		for (size_t i = 0; i < indent; i++)
		{
			os << '\t';
		}
}