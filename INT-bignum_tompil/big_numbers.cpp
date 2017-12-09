#include "big_numbers.h"

#include <climits>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <iostream>
#include <bitset>

using uchar_vec = std::vector<unsigned char>;

std::string dump_vector(const uchar_vec & vec)
{
	std::string tmp;
	if (vec.size() > 1)
		for (int i = 0; i < vec.size() - 2; ++i)
			tmp += std::to_string(vec[i]) + " | ";
	tmp += std::to_string(vec.back());
	return tmp;
}

inline uchar_vec zero_repr()
{
	return std::vector<unsigned char>({ 0 });
}

inline bool is_negative(unsigned char ch)
{ 
	return ~(UCHAR_MAX >> 1) & ch;
}

inline size_t find_last_if_not(const std::vector<unsigned char>& vec, unsigned char not)
{
	int i = vec.size() - 1;
	for (; i >= 1; --i)
		if (vec[i] != not) break;
	return i;
}

std::vector<unsigned char> mult10baseMAXCHAR(unsigned char num, int mult)
{
	// long multiplication algorithm
	const unsigned char multipler = 10;
	static_assert(sizeof(unsigned int) > sizeof(unsigned char), "size of unsigned int is too small");
	std::vector<unsigned char> temp_vect(1);
	temp_vect[0] = num;
	if (num == 0) return temp_vect;
	unsigned int temp = 0;
	while (mult--)
	{
		for (int i = 0; i < temp_vect.size(); ++i)
		{
			temp += temp_vect[i] * 10;
			temp_vect[i] = temp % (UCHAR_MAX + 1);
			temp /= (UCHAR_MAX + 1);
		}
		if (temp)
		{
			temp_vect.push_back(temp);
			temp = 0;
		}
	}
	return temp_vect;
}

void add2to1baseMAXCHAR(uchar_vec & num1, const uchar_vec & num2)
{
	// long addition algorithm
	static_assert(sizeof(unsigned int) > sizeof(unsigned char), "size of unsigned int is too small");
	unsigned int temp = 0;
	for (int i = 0;i < num2.size(); ++i)
	{
		if (i >= num1.size())
			num1.push_back(0);
		temp += num1[i] + num2[i];
		num1[i] = temp % (UCHAR_MAX + 1);
		temp /= UCHAR_MAX + 1;
	}
	if (temp) num1.push_back(temp);
}

void add2to1ReversedCiphers(std::string& first, const std::string& second)
{
	//long addition algorithm
	for (int i = 0; i < second.length(); ++i)
	{
		if (i >= first.length()) first.push_back('0');
		char temp1 = first[i] - '0';
		char temp2 = second[i] - '0';
		temp2 += temp1;
		int j = i;
		while (temp2 > 0)
		{
			first[j] = (temp2 % 10) + '0';
			temp2 /= 10;
			if (temp2 != 0)
			{
				++j;
				if (j >= first.length())
					first.push_back(temp2 + '0');
				else
				{
					temp1 = first[j] - '0';
					temp2 += temp1;
				}
			}
		}
	}
}

void mult256ReversedCiphers(std::string& number, int mult)
{
	//Long multiplication algorithm
	for (int i = 0; i < mult; ++i)
	{
		std::string strtemp1 = "";
		std::string strtemp2 = "0";
		std::string strtemp3 = "00";
		char ct1 = 0;
		char ct2 = 0;
		char ct3 = 0;
		for (char c : number)
		{
			ct1 += (c - '0') * 6;
			ct2 += (c - '0') * 5;
			ct3 += (c - '0') * 2;
			strtemp1.push_back((ct1 % 10) + '0');
			strtemp2.push_back((ct2 % 10) + '0');
			strtemp3.push_back((ct3 % 10) + '0');
			ct1 /= 10;
			ct2 /= 10;
			ct3 /= 10;
		}
		while (ct1)
		{
			strtemp1.push_back((ct1 % 10) + '0');
			ct1 /= 10;
		}
		while (ct2)
		{
			strtemp2.push_back((ct2 % 10) + '0');
			ct2 /= 10;
		}
		while (ct3)
		{
			strtemp3.push_back((ct3 % 10) + '0');
			ct3 /= 10;
		}
		add2to1ReversedCiphers(strtemp1, strtemp2);
		add2to1ReversedCiphers(strtemp1, strtemp3);
		number = std::move(strtemp1);
	}
}

void cut_exceeded_zeroes(std::string& str)
{
	size_t last_zero = str.find_last_not_of('0');
	if (last_zero != -1)
		str.resize(last_zero + 1);
	else
		str.resize(1);
}

BigNumber::BigNumber(const std::string& number) :
	m_repr(std::vector<unsigned char>(1, 0))
{
	if (number == "") return;
	bool sign = false;
	if (number[0] == '-')
	{
		sign = true;
	}
	else if (number[0] == '+')
	{
		sign = true;
	}
	int num_begin = number.substr(sign).find_first_not_of('0');
	if (num_begin == std::string::npos) return;
	if (sign) ++num_begin;
	int power10 = 0;

	for (int i = number.length() - 1; i >= num_begin; --i, ++power10)
	{
		char ch = number[i];
		if (ch < '0' || ch > '9') throw WrongInput();
		add2to1baseMAXCHAR(m_repr, mult10baseMAXCHAR(ch - '0', power10));
	}
	m_repr.resize(find_last_if_not(m_repr,0)+1);
	if (number[0] == '-')
	{
		for (unsigned char& uch : m_repr)
			uch = ~uch;
		if (!is_negative(m_repr.back()))
			m_repr.push_back(UCHAR_MAX);
	}
	else
	{
		m_repr.push_back(0);
		if (is_negative(m_repr.back()))
			m_repr.push_back(0);
	}
}

inline std::vector<unsigned char> negative_to_ZU1(long long int number)
{
	unsigned long long int abs = llabs(number);
	std::vector<unsigned char> temp(1, 0);
	constexpr int mod = UCHAR_MAX + 1;
	for (int i = 0; abs; ++i)
	{
		temp[i] = ~(abs % mod) & UCHAR_MAX;
		abs /= mod;
		if (abs) temp.push_back(0);
	}
	if(!is_negative(temp.back()))
		temp.push_back(UCHAR_MAX);
	return temp;
}

inline std::vector<unsigned char> positive_to_ZU1(long long int number)
{
	std::vector<unsigned char> temp(1, 0);
	constexpr int mod = UCHAR_MAX + 1;
	for (int i = 0 ; number; ++i)
	{
		temp[i] = number % mod;
		number /= mod;
		if (number) temp.push_back(0);
	}
	if (is_negative(temp.back()))
		temp.push_back(0);
	return temp;
}

BigNumber::BigNumber(long long int number)
{
	if(number < 0) 
		m_repr = negative_to_ZU1(number);
	else 
		m_repr = positive_to_ZU1(number);
}

const BigNumber& BigNumber::operator=(const BigNumber& number)
{
	m_repr = number.m_repr;
	return *this;
}

const BigNumber& BigNumber::operator=(BigNumber&& number)
{
	m_repr = std::move(number.m_repr);
	return *this;
}

BigNumber::operator std::string() const
{
	std::string s1 = "0";
	std::string temp;
	if (is_negative(m_repr.back())) //if negative
	{
		for (int i = 0; i < m_repr.size(); ++i)
		{
			temp = std::to_string((~m_repr[i]) & UCHAR_MAX);
			temp = std::string(temp.rbegin(), temp.rend());
			mult256ReversedCiphers(temp, i);
			add2to1ReversedCiphers(s1, temp);
		}
		cut_exceeded_zeroes(s1);
		return "-" + std::string(s1.rbegin(), s1.rend());
	}
	else
	{
		for (int i = 0; i < m_repr.size(); ++i)
		{
			temp = std::to_string(m_repr[i]);
			temp = std::string(temp.rbegin(), temp.rend());
			mult256ReversedCiphers(temp, i);
			add2to1ReversedCiphers(s1, temp);
		}
		cut_exceeded_zeroes(s1);
		return std::string(s1.rbegin(), s1.rend());
	}
}

BigNumber BigNumber::operator-() const
{
	bool is_zero = true;
	BigNumber bn;
	uchar_vec repr(m_repr.size());
	for (int i = 0; i < m_repr.size(); ++i)
	{
		if (m_repr[i]) is_zero = false;
		repr[i] = ~m_repr[i];
	}

	if (!is_zero)
	{
		//TODO: rewrite this ugly condition
		if (repr.size() > 1 && ((!is_negative(repr.back()) && !is_negative(repr[repr.size() - 2]) && repr.back() == 0) ||
			(is_negative(repr.back()) && is_negative(repr[repr.size() - 2]) && repr.back() == UCHAR_MAX)))
			repr.pop_back();
		bn.m_repr = std::move(repr);
	}
	return bn;
}

uchar_vec add2numbers_repr(const uchar_vec & number1, const uchar_vec & number2)
{
	const uchar_vec& shorter = number1.size() < number2.size() ? number1 : number2;
	const uchar_vec& longer = number1.size() >= number2.size() ? number1 : number2;
	std::vector<unsigned char> temp_vec(longer.size());

	unsigned int inttemp = 0;
	int i = 0;
	for (; i < shorter.size(); ++i)
	{
		inttemp += shorter[i] + longer[i];
		temp_vec[i] = inttemp % (UCHAR_MAX + 1);
		inttemp /= (UCHAR_MAX + 1);
	}
	unsigned char adder = 0;
	if (is_negative(shorter.back())) adder = UCHAR_MAX;
	for (; i < longer.size(); ++i)
	{
		inttemp += longer[i] + adder;
		temp_vec[i] = inttemp % (UCHAR_MAX + 1);
		inttemp /= (UCHAR_MAX + 1);
	}
	if (inttemp)
	{
		if (is_negative(shorter.back()) || is_negative(longer.back()))
		{
			for (i = 0; i < temp_vec.size(), inttemp; ++i)
			{
				inttemp += temp_vec[i];
				temp_vec[i] = inttemp % (UCHAR_MAX + 1);
				inttemp /= (UCHAR_MAX + 1);
			}
			if (inttemp)
				temp_vec.push_back(~1 % (UCHAR_MAX + 1));
		}
		else
			temp_vec.push_back(1);
	}
	return temp_vec;
}

bool is_result_of_addition_positive(const BigNumber& number1, const BigNumber& number2)
{
	BigNumber zero;
	bool number1_negative = is_negative(number1.back());
	bool number2_negative = is_negative(number2.back());
	if (number1_negative && number2_negative)
		return false;
	if (!number1_negative && !number2_negative)
		return true;
	if (number1_negative && !number2_negative)
		return number2 >= -number1;
	if (!number1_negative && number2_negative)
		return number1 >= -number2;
}

bool check_if_all_zeroes(const uchar_vec & repr)
{
	bool is_zero = true;
	for (unsigned char ch : repr)
		if (ch != UCHAR_MAX) is_zero = false;
	return is_zero;
}

void check_and_repair_representation(uchar_vec & repr, bool should_be_positive)
{
	unsigned char filler = should_be_positive ? 0 : UCHAR_MAX;
	size_t last_not_zero = find_last_if_not(repr, filler);
	if (is_negative(repr.back()))
		last_not_zero = is_negative(repr[last_not_zero]) ? last_not_zero : last_not_zero + 1;
	else
		last_not_zero = !is_negative(repr[last_not_zero]) ? last_not_zero : last_not_zero + 1;
	repr.resize(last_not_zero + 1);
	if (should_be_positive && is_negative(repr.back()))
		repr.push_back(filler);
}

BigNumber operator+(const BigNumber& number1, const BigNumber& number2)
{
	static_assert(sizeof(unsigned int) > sizeof(unsigned char), "unsigned int is too small");

	BigNumber temp;
	temp.m_repr = add2numbers_repr(number1.m_repr, number2.m_repr);
	if (check_if_all_zeroes(temp.m_repr))
	{
		temp.m_repr = zero_repr();
		return temp;
	}
	bool positive_result = is_result_of_addition_positive(number1, number2);
	check_and_repair_representation(temp.m_repr, positive_result);
	return temp;
}

BigNumber operator-(const BigNumber& number1, const BigNumber& number2)
{
	return number1 + (-number2);
}

uchar_vec long_multiplication_base_UCHAR_MAX(const uchar_vec repr1, const uchar_vec repr2)
{
	std::vector<uchar_vec> sub_numbers;
	for (int i = 0; i < repr2.size(); ++i)
	{
		sub_numbers.push_back(uchar_vec(i, 0));
		unsigned int rest = 0;
		for (unsigned char byte : repr1)
		{
			unsigned int temp_num = repr2[i] * byte + rest;
			sub_numbers.back().push_back(temp_num % (UCHAR_MAX + 1));
			rest = temp_num / (UCHAR_MAX + 1);
		}
		if(rest)
			sub_numbers.back().push_back(rest);
	}
	for (int i = 1; i < sub_numbers.size(); ++i)
		add2to1baseMAXCHAR(sub_numbers[0], sub_numbers[i]);
	if (is_negative(sub_numbers[0].back()))
		sub_numbers[0].push_back(0);
	return sub_numbers[0];
}

BigNumber operator*(const BigNumber& number1, const BigNumber& number2)
{
	BigNumber temp;
	bool first_negative = is_negative(number1.back());
	bool second_negative = is_negative(number2.back());
	BigNumber num1 = first_negative ? -number1 : number1;
	BigNumber num2 = second_negative ? -number2 : number2;
	temp.m_repr = long_multiplication_base_UCHAR_MAX(num1.m_repr, num2.m_repr);
	return first_negative ^ second_negative ? -temp : temp;
}

BigNumber divide_positives(const BigNumber& divident, const BigNumber& divisor)
{
	BigNumber one(1);
	if (divisor == BigNumber())
		throw BigNumber::DivisionByZero();
	if (divisor == one)
		return BigNumber(divident);
	BigNumber quotient;
	BigNumber temp;
	temp = temp + divisor;
	while (temp <= divident)
	{
		quotient = quotient + one;
		temp = temp + divisor;
	}
	return quotient;
}

BigNumber operator/(const BigNumber& divident, const BigNumber& divisor)
{
	//TODO: very ifefficient algorithm
	bool divident_negative = is_negative(divident.back());
	bool divisor_negative = is_negative(divisor.back());
	if (!divident_negative && !divisor_negative)
		return divide_positives(divident, divisor);
	if (divident_negative && divisor_negative)
		return divide_positives(-divident, -divisor);
	BigNumber quotient;
	if (divident_negative && !divisor_negative)
		quotient = divide_positives(-divident, divisor);
	else if (!divident_negative && divisor_negative)
		quotient = divide_positives(divident, -divisor);
	return -quotient;
}

bool lt_compare_positive_numbers(const BigNumber& number1, const BigNumber& number2)
{
	if(number1.size() < number2.size())
		return true;
	if (number1.size() > number2.size())
		return false;
	for (int i = number1.size() - 1; i >= 0; --i)
	{
		if (number1[i] > number2[i])
			return false;
		if (number1[i] < number2[i])
			return true;
	}
	return false;
}

bool lt_compare_negative_numbers(const BigNumber& number1, const BigNumber& number2)
{
	if (number1.size() > number2.size())
		return true;
	if (number1.size() < number2.size())
		return false;
	for (int i = number1.size() - 1; i >= 0; --i)
	{
		if (number1[i] > number2[i])
			return false;
		if (number1[i] < number2[i])
			return true;
	}
	return false;
}

bool operator<(const BigNumber& number1, const BigNumber& number2)
{
	bool number1_negative = is_negative(number1.back());
	bool number2_negative = is_negative(number2.back());
	if (number1_negative && !number2_negative) 
		return true;
	if (number2_negative && !number1_negative)
		return false;
	if (number1_negative && number2_negative)
		return lt_compare_negative_numbers(number1, number2);
	else if (!number1_negative && !number2_negative)
		return lt_compare_positive_numbers(number1, number2);
}

bool operator>(const BigNumber& number1, const BigNumber& number2)
{
	return number2 < number1;
}

bool operator<=(const BigNumber& number1, const BigNumber& number2)
{
	return !(number1 > number2);
}

bool operator>=(const BigNumber& number1, const BigNumber& number2)
{
	return !(number1 < number2);
}

bool BigNumber::operator==(const BigNumber& number) const
{
	int i = 0;
	int min_len = m_repr.size() < number.m_repr.size() ? m_repr.size() : number.m_repr.size();

	for (; i < min_len; ++i)
	{
		if (m_repr[i] != number.m_repr[i]) return false;
	}
	for (; i < m_repr.size(); ++i)
	{
		if (m_repr[i] != 0) return false;
	}
	for (; i < number.m_repr.size(); ++i)
	{
		if (number.m_repr[i] != 0) return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const BigNumber & num)
{
	os << static_cast<std::string>(num);
	return os;
}

std::istream& operator>>(std::istream& is, BigNumber & num)
{
	std::string temp;
	is >> temp;
	num = BigNumber(temp);
	return is;
}

BigNumber& BigNumber::operator++()
{
	*this = *this + BigNumber(1);
	return *this;
}

BigNumber& BigNumber::operator--()
{
	*this = *this - BigNumber(1);
	return *this;
}

BigNumber BigNumber::operator++(int)
{
	BigNumber temp(*this);
	*this = *this + BigNumber(1);
	return temp;
}

BigNumber BigNumber::operator--(int)
{
	BigNumber temp(*this);
	*this = *this - BigNumber(1);
	return temp;
}

BigNumber& BigNumber::operator+=(const BigNumber & num)
{
	*this = *this + num;
	return *this;
}

BigNumber& BigNumber::operator-=(const BigNumber & num)
{
	*this = *this - num;
	return *this;
}

BigNumber& BigNumber::operator*=(const BigNumber & num)
{
	*this = *this * num;
	return *this;
}

BigNumber& BigNumber::operator/=(const BigNumber & num)
{
	*this = *this / num;
	return *this;
}
