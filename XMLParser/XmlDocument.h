#pragma once
#include "XmlNode.h"
#include "String.h"
#include "Vector.hpp"
class XmlFile {
	XmlNode* root = nullptr;
	size_t nextId = 1;

};