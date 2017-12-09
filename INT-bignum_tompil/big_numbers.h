#pragma once

#include <string>
#include <iostream>
#include <vector>

class BigNumber
/*
	Class uses "One's complement" integral numbers encoding,
	but with one zero repressentation(all bits set to zero).
	All bits set to 1 are is unused value, may be for future use.
*/
{
private:
	std::vector<unsigned char> m_repr;
	size_t size() const { return m_repr.size(); }
	unsigned char operator[](size_t i) const { return m_repr[i]; }
	unsigned char& operator[](size_t i) { return m_repr[i]; }
	unsigned char back() const { return m_repr.back(); }
	unsigned char& back() { return m_repr.back(); }
	friend bool lt_compare_positive_numbers(const BigNumber& number1, const BigNumber& number2);
	friend bool lt_compare_negative_numbers(const BigNumber& number1, const BigNumber& number2);
	friend bool is_result_of_addition_positive(const BigNumber& number1, const BigNumber& number2);
public:
	BigNumber(const std::string& number);
	BigNumber(long long int number = 0);
	BigNumber(const BigNumber& number) : m_repr(number.m_repr) {}
	BigNumber(BigNumber&& number) : m_repr(std::move(number.m_repr)) {}
	const BigNumber& operator=(const BigNumber& number);
	const BigNumber& operator=(BigNumber&& number);
	operator std::string() const;
	BigNumber operator-() const;
	friend BigNumber operator+(const BigNumber& number1, const BigNumber& number2);
	friend BigNumber operator-(const BigNumber& number1, const BigNumber& number2);
	friend BigNumber operator*(const BigNumber& number1, const BigNumber& number2);
	friend BigNumber operator/(const BigNumber& divident, const BigNumber& divisor);
	friend bool operator<(const BigNumber& number1, const BigNumber& number2);
	friend bool operator>(const BigNumber& number1, const BigNumber& number2);
	friend bool operator<=(const BigNumber& number1, const BigNumber& number2);
	friend bool operator>=(const BigNumber& number1, const BigNumber& number2);
	bool operator==(const BigNumber& number) const;
	bool operator!=(const BigNumber& number) const { return !operator==(number); }
	friend std::ostream& operator<<(std::ostream& os, const BigNumber & num);
	friend std::istream& operator>>(std::istream& is, BigNumber & num);
	BigNumber& operator++();
	BigNumber& operator--();
	BigNumber operator++(int);
	BigNumber operator--(int);
	BigNumber& operator+=(const BigNumber & num);
	BigNumber& operator-=(const BigNumber & num);
	BigNumber& operator*=(const BigNumber & num);
	BigNumber& operator/=(const BigNumber & num);
	~BigNumber() {}

	class WrongInput {};
	class DivisionByZero {};
};
