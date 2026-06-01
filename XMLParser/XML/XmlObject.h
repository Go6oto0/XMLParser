#pragma once
#include <iostream>
/**
 * @brief Абстрактен базов клас за всички обекти в XML дървото.
 *
 * Класът дефинира общ интерфейс за сериализация, клониране и
 * извличане на текстово съдържание. Всички конкретни XML обекти
 * (елементи, текстови възли и коментари) наследяват този клас.
 */
class XmlObject {
public:

	/**
	 * @brief Записва обекта в изходен поток.
	 * @param os Изходен поток.
	 * @param indent Ниво на отстъп при сериализация.
	 */
	virtual void serialize(std::ostream& os, size_t indent = 0) const = 0;

	/**
	 * @brief Създава копие на обекта.
	 * @return Указател към новосъздаденото копие.
	 */
	virtual XmlObject* clone() const = 0;

	/**
	 * @brief Виртуален деструктор.
	 */
	virtual ~XmlObject() = default;

	/**
	 * @brief Извежда текстовото съдържание на обекта.
	 * @param os Изходен поток.
	 */
	virtual void printText(std::ostream& os) const = 0;

	/**
	 * @brief Извежда отстъпи според нивото на влагане.
	 * @param os Изходен поток.
	 * @param indent Брой нива на отстъп.
	 */
	void printIndents(std::ostream& os, size_t indent = 0) const;
};