#pragma once

#include <iostream>

namespace NPushkarev {
	class LongNumber {
		static const char END = '\0';
		static const char MINUS = '-';
		static const int NEGATIVE = -1;
		static const int POSITIVE = 1;
		
		int* numbers;
		int length;
		int sign;
		
		public:
			LongNumber();
			LongNumber(const char* const str);
			LongNumber(int value);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			int toInt(const LongNumber& x)const;
			bool operator == (const LongNumber& x) const;
			bool operator > (const LongNumber& x);
			bool operator < (const LongNumber& x);
			LongNumber abs(const LongNumber& x);
			
			LongNumber operator + (const LongNumber& x);
			LongNumber operator - (const LongNumber& x);
			LongNumber operator * (const LongNumber& x);
			LongNumber operator / (const LongNumber& x);
			LongNumber operator % (const LongNumber& x);
			
			int get_digits_number() const;
			bool is_positive() const;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const;
	};
}