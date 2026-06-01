#pragma once
#include "XmlObject.h"
#include "String.h"
/**
 * @brief Представя текстов възел в XML дървото.
 *
 * Класът съхранява текстово съдържание, намиращо се между XML тагове,
 * и предоставя функционалност за неговата сериализация, извеждане
 * и клониране.
 */
class XmlText : public XmlObject {
	String text;

public:

	/**
	 * @brief Връща текстовото съдържание на възела.
	 * @return Константна референция към текста.
	 */
	const String& getText() const;

	/**
	 * @brief Създава текстов възел с подадено съдържание.
	 * @param text Текстът на възела.
	 */
	XmlText(const String& text);

	/**
	 * @brief Извежда текстовото съдържание на възела.
	 * @param os Изходен поток.
	 */
	void printText(std::ostream& os = std::cout) const override;

	/**
	 * @brief Записва текстовия възел в изходен поток.
	 * @param os Изходен поток.
	 * @param indent Ниво на отстъп.
	 */
	void serialize(std::ostream& os, size_t indent = 0) const override;

	/**
	 * @brief Създава копие на текстовия възел.
	 * @return Указател към новосъздаденото копие.
	 */
	XmlObject* clone() const override;
};