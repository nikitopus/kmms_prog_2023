#pragma once

#include <iostream>
#include <string>

namespace NPushkarev{

class LongNumber {
	std::string value; // значение числа
	bool isNeg; // флаг отрицательности
    
public:
	LongNumber(); // конструктор умолчания (число равно нулю)
	LongNumber(long x); // конструктор преобразования из обычного целого числа
	LongNumber(const std::string &value); // конструктор преобразования из строки
	LongNumber(const LongNumber& longNumber); // конструктор копирования

	const std::string &getValue() const; // получение содержимого строки (строка модуля числа)

	const bool getIsNeg() const; // получение флага отрицательности числа
	void setIsNeg(bool isNeg); // установка флага отрицательности числа

	int sign() const; // получение знака числа
	const bool isEven() const; // проверка на чётность

	LongNumber abs() const; // получение модуля числа

	// операции сравнения
	const bool operator==(const LongNumber &longNumber) const;
	const bool operator!=(const LongNumber &longNumber) const;

	const bool operator<(const LongNumber &longNumber) const;
	const bool operator>(const LongNumber &longNumber) const;
	const bool operator<=(const LongNumber &longNumber) const;
	const bool operator>=(const LongNumber &longNumber) const;

	// операция присваивания
	LongNumber &operator=(const LongNumber &longNumber);

	// унарные плюс и минус
	LongNumber operator+() const &&;
	LongNumber operator-() const &&;

	// арифметические операции
	LongNumber operator+(const LongNumber &longNumber) const;
	LongNumber operator-(const LongNumber &longNumber) const;
	LongNumber operator*(const LongNumber &longNumber) const;
	LongNumber operator/(const LongNumber &longNumber) const;
	LongNumber operator%(const LongNumber &longNumber) const;
	LongNumber operator<<(size_t n) const;
	LongNumber operator>>(size_t n) const;

	friend std::ostream &operator<<(std::ostream &stream, const LongNumber &longNumber); // вывод числа в выходной поток
	friend std::istream &operator>>(std::istream &stream, LongNumber &longNumber); // ввод числа из входного потока
};
}