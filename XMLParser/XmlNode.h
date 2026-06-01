#pragma once
#include "XmlObject.h"
#include "XmlAttribute.h"
#include "Vector.hpp"
#include "String.h"
/**
 * @brief Представя XML елемент в XML дървото.
 *
 * Класът съхранява име на елемент, списък от атрибути,
 * списък от деца и идентификатор. Поддържа добавяне на атрибути
 * и деца, сериализация, клониране и извличане на текстово съдържание.
 */
class XmlNode : public XmlObject {
private:
	String name;
	Vector<XmlAttribute> attributes;
	Vector<XmlObject*> children;
	String id;

private:

	/**
	 * @brief Копира съдържанието на друг XML възел.
	 * @param other Възелът, който се копира.
	 */
	void copy(const XmlNode& other);

	/**
	 * @brief Освобождава паметта, заета от децата на възела.
	 */
	void free();

	/**
	 * @brief Премества съдържанието от друг XML възел.
	 * @param other Възелът, от който се преместват ресурсите.
	 */
	void moveFrom(XmlNode&& other);

public:

	/**
	 * @brief Създава празен XML възел.
	 */
	XmlNode();

	/**
	 * @brief Конструктор за копиране.
	 * @param other Възелът, който се копира.
	 */
	XmlNode(const XmlNode& other);

	/**
	 * @brief Конструктор за преместване.
	 * @param other Възелът, който се премества.
	 */
	XmlNode(XmlNode&& other);

	/**
	 * @brief Присвояване чрез преместване.
	 * @param other Възелът, който се премества.
	 * @return Референция към текущия обект.
	 */
	XmlNode& operator=(XmlNode&& other);

	/**
	 * @brief Присвояване чрез копиране.
	 * @param other Възелът, който се копира.
	 * @return Референция към текущия обект.
	 */
	XmlNode& operator=(const XmlNode& other);

	/**
	 * @brief Унищожава XML възела.
	 */
	~XmlNode();

	/**
	 * @brief Връща идентификатора на възела.
	 * @return Константна референция към идентификатора.
	 */
	const String& getId() const;

	/**
	 * @brief Добавя атрибут към възела.
	 * @param attribute Атрибутът за добавяне.
	 */
	void addAttribute(const XmlAttribute& attribute);

	/**
	 * @brief Добавя дете към възела.
	 * @param child Указател към детето за добавяне.
	 */
	void addChild(XmlObject* child);

	/**
	 * @brief Връща атрибутите на възела.
	 * @return Константна референция към списъка с атрибути.
	 */
	const Vector<XmlAttribute>& getAttributes() const;

	/**
	 * @brief Връща атрибутите на възела.
	 * @return Референция към списъка с атрибути.
	 */
	Vector<XmlAttribute>& getAttributes();

	/**
	 * @brief Извежда текстовото съдържание на възела.
	 * @param os Изходен поток.
	 */
	void printText(std::ostream& os = std::cout) const override;

	/**
	 * @brief Връща директното текстово съдържание на възела.
	 * @return Низ с текстовото съдържание.
	 */
	String getTextContent() const;

	/**
	 * @brief Намира всички деца с дадено име.
	 * @param name Име на търсените деца.
	 * @return Списък от намерените XML възли.
	 */
	Vector<XmlNode*> getChildrenByName(const String& name) const;

	/**
	 * @brief Намира индекса на атрибут по име.
	 * @param attr Име на атрибута.
	 * @return Индекс на атрибута или -1, ако не е намерен.
	 */
	int getAttributeInd(const String& attr) const;

	/**
	 * @brief Създава XML възел с подадено име.
	 * @param name Име на XML елемента.
	 */
	XmlNode(const String& name);

	/**
	 * @brief Връща името на възела.
	 * @return Константна референция към името.
	 */
	const String& getName() const;

	/**
	 * @brief Задава име на възела.
	 * @param name Новото име на възела.
	 */
	void setName(const String& name);

	/**
	 * @brief Връща децата на възела.
	 * @return Константна референция към списъка с деца.
	 */
	const Vector<XmlObject*>& getChildren() const;

	/**
	 * @brief Записва XML възела в изходен поток.
	 * @param os Изходен поток.
	 * @param indent Ниво на отстъп.
	 */
	void serialize(std::ostream& os, size_t indent = 0) const override;

	/**
	 * @brief Създава копие на възела.
	 * @return Указател към новосъздаденото копие.
	 */
	XmlObject* clone() const override;
};