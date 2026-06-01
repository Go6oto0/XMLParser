#pragma once
#include "XmlNode.h"
#include "../String/String.h"
#include "../Containers/Vector.hpp"
#include "XmlComment.h"
#include "XmlText.h"
#include <map>
/**
 * @brief Представя XML документ и предоставя операции за
 * зареждане, записване, обработка и търсене в XML дърво.
 *
 * Класът поддържа XML дърво, регистър на елементите по техните
 * идентификатори и изпълнение на XPath-подобни заявки.
 */
class XmlFile {
	XmlNode* root;
	size_t nextId;
	std::map<String, XmlNode*> registry;
	String currentFileName;

private:

	/**
	 * @brief Копира съдържанието на друг XML документ.
	 * @param other Документът, който се копира.
	 */
	void copy(const XmlFile& other);

	/**
	 * @brief Освобождава използваните ресурси.
	 */
	void free();

	/**
	 * @brief Премества ресурсите от друг XML документ.
	 * @param other Документът, от който се преместват ресурсите.
	 */
	void moveFrom(XmlFile&& other);

	/**
	 * @brief Възстановява регистъра с идентификатори.
	 * @param curNode Текущ възел от дървото.
	 */
	void rebuildRegistry(XmlNode* curNode);

public:

	/**
	 * @brief Създава празен XML документ.
	 */
	XmlFile();

	/**
	 * @brief Конструктор за копиране.
	 * @param other Документът, който се копира.
	 */
	XmlFile(const XmlFile& other);

	/**
	 * @brief Конструктор за преместване.
	 * @param other Документът, който се премества.
	 */
	XmlFile(XmlFile&& other);

	/**
	 * @brief Присвояване чрез копиране.
	 * @param other Документът, който се копира.
	 * @return Референция към текущия обект.
	 */
	XmlFile& operator=(const XmlFile& other);

	/**
	 * @brief Присвояване чрез преместване.
	 * @param other Документът, който се премества.
	 * @return Референция към текущия обект.
	 */
	XmlFile& operator=(XmlFile&& other);

	/**
	 * @brief Унищожава XML документа.
	 */
	~XmlFile();

	/**
	 * @brief Зарежда XML документ от поток.
	 * @param is Входен поток.
	 */
	void deserialize(std::istream& is);

	/**
	 * @brief Записва XML документа в поток.
	 * @param os Изходен поток.
	 */
	void serialize(std::ostream& os) const;

	/**
	 * @brief Намира възел по идентификатор.
	 * @param id Идентификатор на възела.
	 * @return Указател към намерения възел.
	 */
	XmlNode* getById(String id);

	/**
	 * @brief Създава XML коментар от поток.
	 * @param is Входен поток.
	 * @return Създаденият коментар.
	 */
	XmlComment* createComment(std::istream& is);

	/**
	 * @brief Създава XML възел от поток.
	 * @param is Входен поток.
	 * @return Създаденият възел.
	 */
	XmlNode* createNode(std::istream& is);

	/**
	 * @brief Добавя атрибут към възел.
	 * @param is Входен поток.
	 * @param child Възелът, към който се добавя атрибутът.
	 */
	void addAttribute(std::istream& is, XmlNode& child);

	/**
	 * @brief Прочита стойност на атрибут.
	 * @param is Входен поток.
	 * @return Прочетената стойност.
	 */
	String createValue(std::istream& is);

	/**
	 * @brief Прочита име на атрибут.
	 * @param is Входен поток.
	 * @return Прочетеното име.
	 */
	String createAttribute(std::istream& is);

	/**
	 * @brief Задава име на XML възел.
	 * @param is Входен поток.
	 * @param child Възелът, чието име се задава.
	 * @param first Първият прочетен символ.
	 */
	void setName(std::istream& is, XmlNode& child, char first);

	/**
	 * @brief Преобразува число в низ.
	 * @param num Числото за преобразуване.
	 * @return Низовото представяне на числото.
	 */
	String toString(size_t num);

	/**
	 * @brief Извежда стойността на атрибут.
	 * @param id Идентификатор на елемента.
	 * @param key Име на атрибута.
	 */
	void select(const String& id, const String& key) const;

	/**
	 * @brief Променя стойността на атрибут.
	 * @param id Идентификатор на елемента.
	 * @param key Име на атрибута.
	 * @param value Нова стойност.
	 */
	void set(const String& id, const String& key, const String& value);

	/**
	 * @brief Извежда децата на елемент.
	 * @param id Идентификатор на родителя.
	 */
	void children(const String& id) const;

	/**
	 * @brief Извежда дете по позиция.
	 * @param id Идентификатор на родителя.
	 * @param pos Позиция на детето.
	 */
	void child(const String& id, size_t pos) const;

	/**
	 * @brief Извежда текстовото съдържание на елемент.
	 * @param id Идентификатор на елемента.
	 */
	void text(const String& id) const;

	/**
	 * @brief Изтрива атрибут от елемент.
	 * @param id Идентификатор на елемента.
	 * @param key Име на атрибута.
	 */
	void deleteAttr(const String& id, const String& key);

	/**
	 * @brief Добавя ново дете към елемент.
	 * @param id Идентификатор на родителя.
	 */
	void newChild(const String& id);

	/**
	 * @brief Отваря XML файл.
	 * @param filePath Път до файла.
	 */
	void open(const String& filePath);

	/**
	 * @brief Затваря текущия документ.
	 */
	void close();

	/**
	 * @brief Записва документа в текущия файл.
	 */
	void save() const;

	/**
	 * @brief Записва документа в нов файл.
	 * @param fileName Име на файла.
	 */
	void saveAs(const String& fileName) const;

	/**
	 * @brief Намира възел по име на таг.
	 * @param tagName Името на тага.
	 * @return Константна референция към намерения възел.
	 */
	const XmlNode& getByTagName(const String& tagName) const;

	/**
	 * @brief Създава текстов възел.
	 * @param is Входен поток.
	 * @param first Първи символ от текста.
	 * @return Създаденият текстов възел.
	 */
	XmlText* createText(std::istream& is, char first);

	/**
	 * @brief Пропуска символите до края на таг.
	 * @param is Входен поток.
	 */
	void reachEndOfTag(std::istream& is);

	/**
	 * @brief Проверява дали низ съдържа само празни символи.
	 * @param str Проверяваният низ.
	 * @return true ако съдържа само празни символи.
	 */
	bool isWhitespaceOnly(const String& str);

	/**
	 * @brief Построява XML дървото.
	 * @param is Входен поток.
	 * @param curNode Текущ възел.
	 */
	void buildTree(std::istream& is, XmlNode& curNode);

	/**
	 * @brief Обработва идентификатора на възел.
	 * @param child Възелът за обработка.
	 */
	void handleId(XmlNode& child);

	/**
	 * @brief Намира възел по идентификатор.
	 * @param id Идентификатор на възела.
	 * @return Константен указател към намерения възел.
	 */
	const XmlNode* getById(const String& id) const;

	/**
	 * @brief Изпълнява част от XPath заявка.
	 */
	Vector<XmlNode*> applyQuery(const Vector<XmlNode*>& curResult, const String& miniQuery) const;

	/**
	 * @brief Разделя XPath заявка по '/'.
	 */
	Vector<String> splitBySlash(const String& query) const;

	/**
	 * @brief Прилага филтър по индекс.
	 */
	Vector<XmlNode*> filterInd(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;

	/**
	 * @brief Прилага филтър за атрибути.
	 */
	Vector<XmlNode*> filterAllAttr(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;

	/**
	 * @brief Прилага филтър по текстово съдържание.
	 */
	Vector<XmlNode*> filterByText(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;

	/**
	 * @brief Извлича име на елемент от XPath заявка.
	 */
	String getNameFromQuery(const String& query, size_t start = 0) const;

	/**
	 * @brief Прилага филтър върху резултат от заявка.
	 */
	Vector<XmlNode*> applyFilter(const Vector<XmlNode*>& nodes, const String& miniQuery, size_t filterStart) const;

	/**
	 * @brief Изпълнява XPath-подобна заявка.
	 * @param query Заявката за изпълнение.
	 */
	void xPath(const String& query) const;
};