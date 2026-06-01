#pragma once
#include "../String/String.h"
/**
 * @brief Представя атрибут на XML елемент.
 *
 * Класът съхранява име и стойност на XML атрибут и предоставя
 * достъп до тяхното четене и промяна.
 */
class XmlAttribute {
private:
	String name;
	String value;

public:

	/**
	 * @brief Създава празен XML атрибут.
	 */
	XmlAttribute();

	/**
	 * @brief Създава XML атрибут с име и стойност.
	 * @param name Име на атрибута.
	 * @param value Стойност на атрибута.
	 */
	XmlAttribute(const String& name, const String& value);

	/**
	 * @brief Променя стойността на атрибута.
	 * @param val Новата стойност.
	 */
	void setValue(const String& val);

	/**
	 * @brief Връща името на атрибута.
	 * @return Константна референция към името.
	 */
	const String& getName() const;

	/**
	 * @brief Връща стойността на атрибута.
	 * @return Константна референция към стойността.
	 */
	const String& getValue() const;
};