#include "long_number.hpp"

namespace NPushkarev{
// конструткор по умолчанию
LongNumber::LongNumber() {
	this->isNeg = false;
	this->value = "0";
}

// конструктор из стандартного целого числа
LongNumber::LongNumber(long x) {
	this->isNeg = x < 0;
	this->value = std::to_string(isNeg ? -x : x);
}

// конструктор из строки (пустая строка создаст число 0)
LongNumber::LongNumber(const std::string &value) {
	if (!value.length()) {
		this->value = "0";
		isNeg = false;

		return;
	}		

	isNeg = value[0] == '-';
	this->value = value.substr(isNeg);

	// определяем число ведущих нулей в строке
	int count = 0;
	while (this->value[count] == '0' && this->value.length() - count > 1)
		count++;

	this->value = this->value.substr(count); // удаляем ведущие нули

	// проверяем "на цифру" каждый символ строки, кидаем исключение, если есть другие символы
	for(size_t i = 0; i < this->value.length(); i++)
		if (this->value[i] < '0' || this->value[i] > '9')
			throw std::string("LongNumber(const string &value) - string contain incorrect characters: ") + this->value;
}

// конструктор копирования
LongNumber::LongNumber(const LongNumber& longNumber) {
	this->value = longNumber.getValue();
	this->isNeg = longNumber.getIsNeg();
}

// получение строки со значением числа
const std::string &LongNumber::getValue() const {
	return value;
}

// получение флага отрицательности числа
const bool LongNumber::getIsNeg() const {
	return isNeg;
}

// изменение флага отрицательности числа
void LongNumber::setIsNeg(bool isNeg) {
	this->isNeg = isNeg;
}

// получение знака числа
int LongNumber::sign() const {
	return (1 - 2 * isNeg) * (value != "0");
}

// проверка на чётность
const bool LongNumber::isEven() const {
	return (value[value.length() - 1] - '0') % 2 == 0;
}

// получение модуля числа
LongNumber LongNumber::abs() const {
	return LongNumber(value);
}

// проверка на равенство двух чисел (равны, если одного знака и одного значения)
const bool LongNumber::operator==(const LongNumber &longNumber) const {
	return (value == longNumber.getValue()) && (isNeg == longNumber.getIsNeg());
}

// проверка на неравенство - отрицание равенства
const bool LongNumber::operator!=(const LongNumber &longNumber) const {
	return !(*this == longNumber);
}

// проверка, что число меньше longNumber
const bool LongNumber::operator<(const LongNumber &longNumber) const {
	std::string value2 = longNumber.getValue(); // получаем значение второго числа
	size_t len1 = value.length(); // запоминаем длину первого числа
	size_t len2 = value2.length(); // запоминаем длину второго числа

	// если знаки одинаковые, то проверяем значения
	if (isNeg == longNumber.getIsNeg()) {
		// если длины не равны
		if (len1 != len2)
			return (len1 < len2) ^ isNeg; // меньше число с меньшей длинной для положительных и с большей длиной для отрицательных

		size_t i = 0;

		// ищем разряд, в котором значения отличаются
		while (i < len1 && value[i] == value2[i])
			i++;

		// если разряд найден, то меньше число с меньшей цифрой для положительных и с большей цифрой для отрицательных, иначе числа равны
		return (i < len1) && ((value[i] < value2[i]) ^ isNeg);
	}

	return isNeg; // знаки разные, если число отрицательное, то оно меньше, если положительное, то больше
}

// проверка, что число больше longNumber
const bool LongNumber::operator>(const LongNumber &longNumber) const {
	return !(*this < longNumber || *this == longNumber);
}

// проверка, что число меньше или равно longNumber
const bool LongNumber::operator<=(const LongNumber &longNumber) const {
	return *this < longNumber || *this == longNumber;
}

// проверка, что число больше или равно longNumber
const bool LongNumber::operator>=(const LongNumber &longNumber) const {
	return *this > longNumber || *this == longNumber;
}

// операция присваивания
LongNumber &LongNumber::operator=(const LongNumber &longNumber) {
	value = longNumber.getValue();
	isNeg = longNumber.getIsNeg();

	return *this;
}

// унарный минус, если было отрицательным, возвращаем положительное, иначе отрицательное
LongNumber LongNumber::operator-() const && {
	return LongNumber(isNeg ? value : std::string("-") + value);
}

// унарный плюс (просто копируем значение числа)
LongNumber LongNumber::operator+() const && {
	return LongNumber(*this);
}

// бинарный плюс (сложение двух чисел)
LongNumber LongNumber::operator+(const LongNumber &longNumber) const {
	bool isAddOp = !(longNumber.getIsNeg() ^ isNeg); // если знаки одинаковые, то выполняем сложение

	if (isAddOp) {
		std::string num2 = longNumber.getValue(); // запоминаем значение второго числа

		size_t len1 = value.length(); // запоминаем длину первого числа
		size_t len2 = num2.length(); // запоминаем длину второго числа
		size_t length = 1 + std::max(len1, len2);  // длина суммы равна максимуму из двух длин + 1 из-за возможного переноса разряда

		char res[length + 1]; // строковый массив для выполнения операции сложения

		res[length - 1] = res[length] = '\0';

		for (size_t i = 0; i < length - 1; i++) {
			int j = length - 1 - i;
			res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (value[len1 - 1 - i] - '0') : 0); // выполняем сложение разрядов
	    	res[j - 1] = res[j] / 10; // выполняем перенос в следущий разряд, если он был
		    res[j] = res[j] % 10 + '0'; // оставляем только единицы от возможного переноса и превращаем символ в цифру
		}

		res[0] += '0';
		
		return LongNumber(isNeg ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, в зависимости от знака`
	}
	else
		return isNeg ? (longNumber - (-LongNumber(*this))) : (*this - (-LongNumber(longNumber))); // одно из чисел отрицательное, а другое положительное, отправляем на вычитание, меняя знак
}

// бинарный минус (вычитание двух чисел)
LongNumber LongNumber::operator-(const LongNumber &longNumber) const {
	if (*this == longNumber) 
		return 0; // если числа равны, то какой смысл вычитать?

	// если оба числа положительные, то выполняем вычитание
	if (!isNeg && !longNumber.getIsNeg()) {
		std::string value2 = longNumber.getValue(); // запоминаем значение второго числа
		
		size_t len1 = value.length(); // запоминаем длину первого числа
		size_t len2 = value2.length(); // запоминаем длину второго числа
		size_t length = std::max(len1, len2); // длина результата не превысит максимума длин чисел
		
		bool isNegRes = longNumber > *this; // определяем знак результата

		int a[length], b[length]; // массивы аргументов
		a[0] = b[0] = 0; // обнуляем нулевые элементы массивов

		char res[length + 1]; // строковый массив для результата
		res[length - 1] = res[length] = '\0'; // устанавливаем символ окончания строки

		int sign = (2 * isNegRes - 1); // получаем числовое значение знака результата

		for (size_t i = 0; i < length - 1; i++) {
			a[i] += (i < len1) ? (value[len1 - 1 - i] - '0') : 0; // формируем разряды
			b[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0; // из строк аргументов

			b[i + 1] = -isNegRes; // в зависимости от знака занимаем или не занимаем
			a[i + 1] = isNegRes- 1; // 10 у следующего разряда

			res[length - 1 - i] += 10 + sign * (b[i] - a[i]);
			res[length - 1 - i - 1]  = res[length - 1 - i] / 10;
			res[length - 1 - i] = res[length - 1 - i] % 10 + '0';
		}

		// выполняем операцию с последним разрядом
		a[length - 1] += (length - 1 < len1) * (value[0] - '0');
		b[length - 1] += (length - 1 < len2) * (value2[0] - '0');

		// записываем в строку последний разряд
		res[0] += sign * (b[length - 1] - a[length - 1]) + '0';

		return LongNumber(isNegRes ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, учитывая знак
	} else // если оба числа отрицательные, то меняем местами, меняем знаки и повторяем вычитание, а если знаки разные, то отправляем на сумму
		return isNeg && longNumber.getIsNeg() ? (-LongNumber(longNumber) - (-LongNumber(*this))) : (*this + -LongNumber(longNumber)); 
}

// бинарная звёздочка (умножение двух чисел)
LongNumber LongNumber::operator*(const LongNumber &longNumber) const {
	if (value == "0" || longNumber.getValue() == "0")
		return 0; // если один из множителей равен нулю, то результат равен нулю

	std::string value2 = longNumber.getValue(); // запоминаем значение второго числа
		
	size_t len1 = value.length(); // запоминаем длину первого числа
	size_t len2 = value2.length(); // запоминаем длину второго числа
	size_t length = len1 + len2 + 1; // резульат влезет в сумму длин + 1 из-за возможного переноса
	bool isNegRes = isNeg ^ longNumber.getIsNeg(); // флаг отрицательности результата - отрицательный, если числа разных знаков


	int a[length], b[length]; // массивы аргументов и результата
	char res[length + 1]; // строковый массив для результата
	res[length] = '\0'; // устанавливаем символ окончания строки
	// заполняем массивы инверсной записью чисел (с ведущими нулями)
	for (size_t i = 0; i < length; i++) {
		a[i] = (i < len1) ? (value[len1 - 1 - i] - '0') : 0;
		b[i] = (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;
		res[i] = 0;
	}
	// выполняем умножение "в столбик""
	for (size_t i = 0; i < len1; i++) {
	    for (size_t j = 0; j < len2; j++) {
	        res[length - 1 - (i + j)] += a[i] * b[j];
	        res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
		    res[length - 1 - (i + j)] %= 10;
	    }
	}
	// переписываем результат в строку
	for (size_t i = 0; i < length; i++)
		res[length - 1 - i] += '0';
	return LongNumber(isNegRes ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, учитывая его знак
}

// бинарный слеш (деление двух чисел)
LongNumber LongNumber::operator/(const LongNumber &longNumber) const {
	std::string value1 = value;
	std::string value2 = longNumber.getValue(); // запоминаем значение второго числа

	if (value2[0] == '0')
		throw std::string("Division by zero!"); // нельзя делить на ноль, этому ещё в школе учат

	if (value[0] == '0')
		return 0; // а вот ноль делить можно на всё, кроме нуля, но смысл?

	if (value2 == "1")
		return LongNumber(longNumber.getIsNeg() ? -LongNumber(*this) : *this); // делить на 1 можно, но смысл?

	size_t zeroes = 0;
	while (value2[value2.length() - 1 - zeroes] == '0')
		zeroes++;

	if (zeroes >= value.length())
		return 0;

	// избавляемся от круглых чисел
	if (zeroes) {
		value1 = value1.substr(0, value1.length() - zeroes);
		value2 = value2.substr(0, value2.length() - zeroes);
	}

	bool isNegRes = isNeg ^ longNumber.getIsNeg(); // считаем знак числа

	LongNumber tmp(value2);

	size_t divider_length = value2.length(); // запоминаем длину делителя
	long divider_v = divider_length > 8 ? 0 : atol(value2.c_str()); // если длина больше 8, то обнуляем long'овый делитель, иначе переводим строку в long

	size_t length = value1.length(); // получаем длину делимого
	size_t index = 0; // стартуем с нулевого индекса

	std::string div; // строка результата деления
	std::string v; // строка подчисла (которое делится на делитель в столбик)

	// формируем начальное число для деления
	while (LongNumber(v) < tmp && index < length)
		v += value1[index++];

	do {
		int count = 0; // результат деления подчисла на делитель

		// если можем разделить, то делим
		if (LongNumber(v) >= tmp) {
			if (divider_length > 8) { // если не входит в long, то делим с помощью вычитания
				LongNumber mod = v;

				while (mod >= tmp) {
					mod = mod - tmp;
					count++;
				}

				v = mod.getValue();
			} else {
				long mod = stol(v);
				count = mod / divider_v;
				v = std::to_string(mod % divider_v);
			}
		}
		
		div += count + '0'; // если не делили, то добавили ноль к результату, иначе добавили результат дедения

		if (index <= length)
			v += value1[index++]; // формируем новое значение для подчисла
	} while (index <= length);

	return LongNumber(isNegRes && div != "0" ? std::string("-") + div : div); // возвращаем результат учитывая знак и возможное равенство нулю
}

// бинарный процент (операция взятия остатка от деления) (полностью аналогична делению)
LongNumber LongNumber::operator%(const LongNumber &longNumber) const {
	std::string value2 = longNumber.getValue();

	if (value2[0] == '0')
		throw std::string("Division by zero!");

	if (value[0] == '0' || value2 == "1")
		return 0;

	if (value.length() < 9 && value2.length() < 9) {
		long res = stol(value) % stol(value2);
		return isNeg ? -res : res;
	}

	LongNumber tmp(value2);

	size_t divider_length = value2.length(); // запоминаем длину делителя
	long divider_v = divider_length >= 9 ? 0 : atol(value2.c_str()); // если длина больше 8, то обнуляем long'овый делитель, иначе переводим строку в long

	size_t length = value.length();
	size_t index = 0;
	LongNumber mod2 = value;
	std::string v;

	while (LongNumber(v) < tmp && index < length)
		v += value[index++];

	do {
		if (LongNumber(v) >= tmp) {
			if (divider_v)
				v = std::to_string(stol(v) % divider_v);
			else {
				LongNumber mod = v;

				while (mod >= tmp)
					mod = mod - tmp;

				v = mod.getValue();
			}
		}

		if (index <= length) {
			mod2 = v;
			v += value[index++];				
		}
	} while (index <= length);

	if (mod2.getValue() == "0")
		return 0;

	return isNeg ? -LongNumber(mod2) : mod2;
}

LongNumber LongNumber::operator<<(size_t n) const {
	return LongNumber(std::string(isNeg ? "-" : "") + value + std::string(n, '0'));
}

LongNumber LongNumber::operator>>(size_t n) const {
	if (n >= value.length())
		return 0;

	return LongNumber(std::string(isNeg ? "-" : "") + value.substr(0, value.length() - n));
}

// вывод числа в выходной поток
std::ostream &operator<<(std::ostream &stream, const LongNumber &longNumber) {
	if (longNumber.getIsNeg())
		stream << "-";

	return stream << longNumber.getValue();
}

// ввод числа из входного потока
std::istream &operator>>(std::istream &stream, LongNumber &longNumber) {
	std::string value;
	stream >> value;
	longNumber = LongNumber(value);

	return stream;
}
}