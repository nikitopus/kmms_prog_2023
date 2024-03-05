#include <iostream>
#include <gtest/gtest.h>

#include "long_number.hpp"

TEST(get_digits_number, check_positive) {
	NPushkarev::LongNumber x("12345");
	ASSERT_EQ(5, x.get_digits_number())
		<< "Неправильно подсчитано количество разрядов в числе " << x;
}

TEST(get_digits_number, check_negative) {
	NPushkarev::LongNumber x("-1");
	ASSERT_EQ(1, x.get_digits_number())
		<< "Неправильно подсчитано количество разрядов в числе " << x;
}

class EqualityFixture : public testing::Test {
	public:
		NPushkarev::LongNumber one_v1 = NPushkarev::LongNumber("1");
		NPushkarev::LongNumber one_v2 = NPushkarev::LongNumber("1");
		NPushkarev::LongNumber stzero_one = NPushkarev::LongNumber("0001");
		NPushkarev::LongNumber zero_v1 = NPushkarev::LongNumber("000");
		NPushkarev::LongNumber zero_v2 = NPushkarev::LongNumber("0");
		NPushkarev::LongNumber twelve = NPushkarev::LongNumber("12");
		NPushkarev::LongNumber negative_one = NPushkarev::LongNumber("-1");
};

TEST_F(EqualityFixture, equal) {
	ASSERT_TRUE(one_v1 == one_v2) << "Проверка " << one_v1 << " == " << one_v2;
}

TEST_F(EqualityFixture, zero_equal) {
	ASSERT_TRUE(zero_v1 == zero_v2) << "Проверка " << zero_v1 << " == " << zero_v2;
}

TEST_F(EqualityFixture, stzero_equal) {
	ASSERT_TRUE(stzero_one == one_v1) << "Проверка " << stzero_one << " == " << one_v1;
}

TEST_F(EqualityFixture, not_equal) {
	ASSERT_FALSE(one_v1 == twelve) << "Проверка " << one_v1 << " == " << twelve;
}

TEST_F(EqualityFixture, not_equal_negative_var) {
	ASSERT_FALSE(one_v1 == negative_one) 
		<< "Проверка " << one_v1 << " == " << negative_one;
}

TEST(compare_greater, positive_greater) {
	NPushkarev::LongNumber x("123");
	NPushkarev::LongNumber y("45");
	ASSERT_TRUE(x > y) << "Проверка " << x << " > " << y;
}

TEST(compare_greater, negative_greater) {
	NPushkarev::LongNumber x("-123");
	NPushkarev::LongNumber y("-45");
	ASSERT_TRUE(x < y) << "Проверка " << x << " > " << y;
}

TEST(compare_greater, positive_not_greater) {
	NPushkarev::LongNumber x("123");
	NPushkarev::LongNumber y("456");
	ASSERT_FALSE(x > y) << "Проверка " << x << " > " << y;
}

TEST(compare_less, positive_less) {
	NPushkarev::LongNumber x("123");
	NPushkarev::LongNumber y("456");
	ASSERT_TRUE(x < y) << "Проверка " << x << " < " << y;
}

TEST(compare_less, negative_less) {
	NPushkarev::LongNumber x("-123");
	NPushkarev::LongNumber y("-456");
	ASSERT_TRUE(x > y) << "Проверка " << x << " < " << y;
}

TEST(compare_less, positive_not_less) {
	NPushkarev::LongNumber x("123");
	NPushkarev::LongNumber y("45");
	ASSERT_FALSE(x < y) << "Проверка " << x << " < " << y;
}

TEST (absolute, positive_abs) {
	NPushkarev::LongNumber x ("10");
	ASSERT_EQ (NPushkarev::LongNumber ("10"), x.abs(x)) << "Проверка abs(" << x << ")";
}

TEST (absolute, negative_abs) {
	NPushkarev::LongNumber x ("-10");
	ASSERT_EQ (NPushkarev::LongNumber ("10"), x.abs(x)) << "Проверка abs(" << x << ")";
}

TEST (toInt, positive) {
	NPushkarev::LongNumber x ("10");
	ASSERT_EQ (10, x.toInt(x)) << "Проверка toInt(" << x << ")";
}

TEST (toInt, negative) {
	NPushkarev::LongNumber x ("-10");
	ASSERT_EQ (-10, x.toInt(x)) << "Проверка toInt(" << x << ")";
}

TEST(addition, positive_sum) {
    NPushkarev::LongNumber x("123");
    NPushkarev::LongNumber y("456");
    NPushkarev::LongNumber result = x + y;
    ASSERT_EQ(NPushkarev::LongNumber("579"), result) << "Проверка " << x << " + " << y;
}

TEST(addition, first_zero_sum) {
    NPushkarev::LongNumber x("003");
    NPushkarev::LongNumber y("006");
    NPushkarev::LongNumber result = x + y;
    ASSERT_EQ(NPushkarev::LongNumber("9"), result) << "Проверка " << x << " + " << y;
}

TEST(addition, carry_sum) {
    NPushkarev::LongNumber x("99");
    NPushkarev::LongNumber y("61");
    NPushkarev::LongNumber result = x + y;
    ASSERT_EQ(NPushkarev::LongNumber("160"), result) << "Проверка " << x << " + " << y;
}

TEST(addition, negative_sum) {
	NPushkarev::LongNumber x("-123");
	NPushkarev::LongNumber y("-456");
	NPushkarev::LongNumber expected("-579");
	ASSERT_EQ(expected, x + y) << "Проверка " << x << " + " << y;
}

TEST(subtract, subtract_positive_numbers) {
    NPushkarev::LongNumber num1("54321");
    NPushkarev::LongNumber num2("12345");
    NPushkarev::LongNumber result = num1 - num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("41976"), result) << "Неправильная разность положительных чисел";
}

TEST(subtract, subtract_negative_numbers) {
    NPushkarev::LongNumber num1("-54321");
    NPushkarev::LongNumber num2("-12345");
    NPushkarev::LongNumber result = num1 - num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("-41976"), result) << "Неправильная разность отрицательных чисел";
}

TEST(divide, divide_positive_numbers) {
    NPushkarev::LongNumber num1("100");
    NPushkarev::LongNumber num2("25");
    NPushkarev::LongNumber result = num1/num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("4"), result) << "Неправильное целочисленное деление положительных чисел";
}

TEST(divide, divide_negative_numbers) {
    NPushkarev::LongNumber num1("-100");
    NPushkarev::LongNumber num2("25");
    NPushkarev::LongNumber result = num1/num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("-4"), result) << "Неправильное целочисленное деление отрицательного числа на положительное";
}

TEST(modulo, modulo_positive_numbers) {
    NPushkarev::LongNumber num1("100");
    NPushkarev::LongNumber num2("25");
    NPushkarev::LongNumber result = num1%num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("0"), result) << "Неправильный остаток от" << num1<<" mod "<<num2;
}

TEST(modulo, modulo_negative_numbers) {
    NPushkarev::LongNumber num1("-100");
    NPushkarev::LongNumber num2("25");
    NPushkarev::LongNumber result = num1%num2;
    
    ASSERT_EQ(NPushkarev::LongNumber("0"), result) << "Неправильный остаток от" << num1<<" mod "<<num2;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();		
}