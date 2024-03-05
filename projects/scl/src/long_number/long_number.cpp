#include "long_number.hpp"
#include <cmath>

namespace NPushkarev {

	//Конструктор по умолчанию
	LongNumber::LongNumber():numbers(nullptr), length(0), sign(0) {}
	
	//Конструктор с входными данными
	LongNumber::LongNumber(const char* const str) {
		length = get_length(str);
		sign = (str[0] == MINUS) ? NEGATIVE : POSITIVE;

		int startIndex = (sign == NEGATIVE) ? 1 : 0;
		while (startIndex < length && str[startIndex] == '0') {
			startIndex++;
		}

		if (startIndex == length) {
			length = 1;
			sign = POSITIVE;
			startIndex = 0;
		} else if (length > 1) {
			length -= startIndex;
		}

		numbers = new int[length];
		for (int i = 0; i < length; i++) {
			numbers[i] = str[i + startIndex] - '0';
		}
	}

    LongNumber::LongNumber (int value) {
        sign = (value >= 0) ? POSITIVE: NEGATIVE;
        value = std::abs(value);
        length = (value == 0) ? 1 : static_cast<int>(std::log10(value)) + 1;
        numbers = new int[length];
        for (int i = length - 1; i >= 0; --i) {
            numbers[i] = value % 10;
            value /= 10;
        }
    }

	//Конструктор копирования
	LongNumber::LongNumber(const LongNumber& x): length (x.length), sign (x.sign) {
		numbers = new int[length];
		for (int i=0; i<length; i++) {
			numbers [i] = x.numbers[i];
		}
	}

	//Конструктор перемещения
	LongNumber::LongNumber(LongNumber&& x): numbers(x.numbers), length(x.length), sign (x.sign) {
		x.numbers = nullptr;
		x.sign = 0;
		x.length = 0;		
	}
	
	//Деструктор
	LongNumber::~LongNumber() {
		delete [] numbers;
	}
	
	//Оператор присваивания значения из строки
	LongNumber& LongNumber::operator = (const char* const str) {
		delete [] numbers;
		length = get_length (str);
		numbers = new int[length];
		sign = (str[0]==MINUS) ? NEGATIVE : POSITIVE;
		int startIndex = (sign==NEGATIVE) ? 1 : 0;
		for (int i = 0; i < length; i++) {
			numbers[i]= str[i+startIndex] - '0';
		}
		return *this;
	}

	//Оператор присваивания значений другого экземпляра класса
	LongNumber& LongNumber::operator = (const LongNumber& x) {
		if (this!=&x){
			delete [] numbers;
			length = x.length;
			sign = x.sign;
			numbers = new int [length];
			for (int i=0; i<length; i++) {
				numbers [i] = x.numbers[i];
			}
		}
		return *this;
	}
	
	//Оператор перемещения
	LongNumber& LongNumber::operator = (LongNumber&& x) {
		if (this!=&x){
			length = x.length;
			numbers = x.numbers;
			sign = x.sign;
			x.numbers = nullptr;
			x.sign = 0;
			x.length = 0;	
		}	
		return *this;
	}
	
	// Метод перевода числа в int
    int LongNumber::toInt(const LongNumber& x) const{
        int result = 0;
        for (int i = 0; i < x.length; ++i) {
            result = result * 10 + x.numbers[i];
        }
        return (x.sign==POSITIVE) ? result : -result;
    }
	
	//Оператор эквивалентности
	bool LongNumber::operator == (const LongNumber& x) const {
		if (sign != x.sign || length !=x.length){
			return false;
		}
		for (int i=0; i<length; i++) {
			if (numbers [i] != x.numbers[i]){
				return false;
			}
		}
		return true;
	}

	//Оператор больше
	bool LongNumber::operator > (const LongNumber& x) {
		if (sign > x.sign ){
			return true;
		} else if (sign < x.sign) {
			return false;
		}

		if (length>x.length){
			return (sign == POSITIVE);
		}else if (length<x.length){
			return (sign==NEGATIVE);
		}

		for (int i=length-1; i>=0; i--) {
			if (numbers [i] > x.numbers[i]){
				return (sign==POSITIVE);
			}else if (numbers[i]<x.numbers[i]){
				return (sign==NEGATIVE);
			}
		}
		return false;
	}
	
	//Оператор меньше
	bool LongNumber::operator < (const LongNumber& x) {
		if (sign < x.sign ){
			return true;
		} else if (sign > x.sign) {
			return false;
		}

		if (length<x.length){
			return (sign == POSITIVE);
		}else if (length>x.length){
			return (sign==NEGATIVE);
		}

		for (int i=length-1; i>=0; i--) {
			if (numbers [i] < x.numbers[i]){
				return (sign==POSITIVE);
			}else if (numbers[i]>x.numbers[i]){
				return (sign==NEGATIVE);
			}
		}
		return false;
	}

	//Модуль числа
	LongNumber LongNumber::abs (const LongNumber& x) {
		LongNumber result = *this;
		result.sign = POSITIVE;
		return result;
	}
	
	//Сложение
    LongNumber LongNumber::operator+(const LongNumber& x) {
        // Переводим оба числа в int
        int thisInt = this->toInt(*this);
        int otherInt = x.toInt(x);

        int sum = thisInt + otherInt;

        // Переводим результат обратно в LongNumber
		LongNumber result(sum);	
        return result;
    }
	
	LongNumber LongNumber::operator-(const LongNumber& x) {
        // Переводим оба числа в int
        int thisInt = this->toInt(*this);
        int otherInt = x.toInt(x);

        int sum = thisInt - otherInt;

        // Переводим результат обратно в LongNumber
		LongNumber result(sum);	
        return result;
	}

	
	LongNumber LongNumber::operator * (const LongNumber& x) {
        // Переводим оба числа в int
        int thisInt = this->toInt(*this);
        int otherInt = x.toInt(x);

        int sum = thisInt * otherInt;

        // Переводим результат обратно в LongNumber
		LongNumber result(sum);	
        return result;
	}
	
	LongNumber LongNumber::operator / (const LongNumber& x) {
        // Переводим оба числа в int
        int thisInt = this->toInt(*this);
        int otherInt = x.toInt(x);

        int sum = thisInt / otherInt;

        // Переводим результат обратно в LongNumber
		LongNumber result(sum);	
        return result;
	}

	LongNumber LongNumber::operator%(const LongNumber &x){
        // Переводим оба числа в int
        int thisInt = this->toInt(*this);
        int otherInt = x.toInt(x);

        int sum = thisInt % otherInt;

        // Переводим результат обратно в LongNumber
		LongNumber result(sum);	
        return result;
	}

	int LongNumber::get_digits_number() const {
		return length;
	}
	
	bool LongNumber::is_positive() const {
		return sign == POSITIVE;
	}
	
	// ----------------------------------------------------------
	// PRIVATE
	// ----------------------------------------------------------
	
	int LongNumber::get_length(const char* const str) const {
		int length = 0;
		for (int i = 0; str[i]!=END; i++){
			length++;
		}
		return length;
	}
	
	// ----------------------------------------------------------
	// FRIENDLY
	// ----------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const NPushkarev::LongNumber& x) {
    if (!x.is_positive()) {
        os << '-';
    }
    for (int i = 0; i < x.get_digits_number(); ++i) {
        os << x.numbers[i];
    }
    return os;
}
}