#pragma once
#include "../String/String.h"
#include "XmlObject.h"
/**
 * @brief Представя XML коментар в XML дървото.
 *
 * Класът съхранява съдържанието на XML коментар и предоставя
 * функционалност за неговата сериализация, клониране и извеждане.
 */
class XmlComment : public XmlObject {
	String comment;

public:

	/**
	 * @brief Връща съдържанието на коментара.
	 * @return Константна референция към текста на коментара.
	 */
	const String& getComment() const;

	/**
	 * @brief Записва коментара в изходен поток във валиден XML формат.
	 * @param os Изходен поток.
	 * @param indent Ниво на влагане за отстъп.
	 */
	void serialize(std::ostream& os, size_t indent = 0) const override;

	/**
	 * @brief Извежда текстовото съдържание на коментара.
	 * @param os Изходен поток.
	 */
	void printText(std::ostream& os = std::cout) const override;

	/**
	 * @brief Създава дълбоко копие на коментара.
	 * @return Указател към новосъздаденото копие.
	 */
	XmlObject* clone() const override;

	/**
	 * @brief Създава XML коментар с подадено съдържание.
	 * @param str Текстът на коментара.
	 */
	XmlComment(const String& str);
};