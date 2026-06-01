#pragma once
#include <ostream>
#include <cstddef>
/**
 * @brief Представя динамичен низ от символи.
 *
 * Класът реализира собствена версия на низ с динамично управление
 * на паметта и поддръжка на основни операции като копиране,
 * преместване, конкатенация, достъп до символи и вход/изход.
 */
class String {
	char* str;
	size_t len;
	size_t capacity;

private:

	/**
	 * @brief Копира съдържанието на друг низ.
	 * @param other Низът, който се копира.
	 */
	void copy(const String& other);

	/**
	 * @brief Освобождава използваната памет.
	 */
	void free();

	/**
	 * @brief Премества ресурсите от друг низ.
	 * @param other Низът, от който се преместват ресурсите.
	 */
	void moveFrom(String&& other);

	/**
	 * @brief Преоразмерява вътрешния буфер.
	 * @param newCapacity Новият капацитет.
	 */
	void resizeTo(size_t newCapacity);

public:

	/**
	 * @brief Създава празен низ.
	 */
	String();

	/**
	 * @brief Конструктор за копиране.
	 * @param other Низът, който се копира.
	 */
	String(const String& other);

	/**
	 * @brief Конструктор за преместване.
	 * @param other Низът, който се премества.
	 */
	String(String&& other);

	/**
	 * @brief Създава низ от C-низ.
	 * @param str Нул-терминиран низ.
	 */
	String(const char* str);

	/**
	 * @brief Присвояване чрез копиране.
	 * @param other Низът, който се копира.
	 * @return Референция към текущия обект.
	 */
	String& operator=(const String& other);

	/**
	 * @brief Присвояване чрез преместване.
	 * @param other Низът, който се премества.
	 * @return Референция към текущия обект.
	 */
	String& operator=(String&& other);

	/**
	 * @brief Унищожава низа и освобождава паметта.
	 */
	~String();

	/**
	 * @brief Извежда низа в поток.
	 */
	friend std::ostream& operator<<(std::ostream& os, const String& other);

	/**
	 * @brief Осигурява достъп за промяна на символ по индекс.
	 * @param ind Индекс на символа.
	 * @return Референция към символа.
	 */
	char& operator[](size_t ind);

	/**
	 * @brief Добавя друг низ в края на текущия.
	 * @param other Низът за добавяне.
	 */
	void append(const String& other);

	/**
	 * @brief Добавя друг низ към текущия.
	 * @param other Низът за добавяне.
	 * @return Референция към текущия обект.
	 */
	String& operator+=(const String& other);

	/**
	 * @brief Сравнява два низа лексикографски.
	 */
	friend bool operator<(String const& lhs, String const& rhs);

	/**
	 * @brief Конкатенира два низа.
	 * @return Нов низ, съдържащ резултата.
	 */
	friend String operator+(const String& lhs, const String& rhs);

	/**
	 * @brief Прочита низ от входен поток.
	 */
	friend std::istream& operator>>(std::istream& is, String& str);

	/**
	 * @brief Изчиства съдържанието на низа.
	 */
	void clear();

	/**
	 * @brief Връща указател към вътрешния C-низ.
	 * @return Указател към символния масив.
	 */
	const char* getPtr() const;

	/**
	 * @brief Осигурява достъп само за четене до символ по индекс.
	 * @param index Индекс на символа.
	 * @return Константна референция към символа.
	 */
	const char& operator[](size_t index) const;

	/**
	 * @brief Проверява дали низът не е празен.
	 * @return true ако низът съдържа символи.
	 */
	operator bool() const;

	/**
	 * @brief Проверява дали два низа са равни.
	 */
	friend bool operator==(String const& lhs, String const& rhs);

	/**
	 * @brief Добавя символ в края на низа.
	 * @param c Символът за добавяне.
	 */
	void push_back(char c);

	/**
	 * @brief Връща дължината на низа.
	 * @return Броят символи в низа.
	 */
	size_t getLen() const;
};
