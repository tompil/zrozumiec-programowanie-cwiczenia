#include "utf16_string.h"
#include <algorithm>
#include <iostream>
#include <utility>

bool utf16_string::is_one_word_literal(char16_t word) 
{
	return is_one_word_literal( (uint32_t)word );
}

bool utf16_string::is_one_word_literal(uint32_t word) 
{
	if ((word >= 0x0000 && word <= 0xD7FF) || (word >= 0xE000 && word <= 0xFFFF))
		return true;
	return false;
}

bool utf16_string::is_first_word_in_literal(char16_t word) 
{
	if (word >= 0xD800 && word <= 0xDBFF)
		return true;
	return false;
}

bool utf16_string::is_second_word_in_literal(char16_t word) 
{
	if (word >= 0xDC00 && word <= 0xDFFF)
		return true;
	return false;
}

bool utf16_string::is_two_word_literal(char16_t word1, char16_t word2) 
{
	if(is_first_word_in_literal(word1) && is_second_word_in_literal(word2))
		return true;
	return false;
}

bool utf16_string::is_two_word_literal(uint32_t code) 
{
	return code >= 0x10000 && code <= 0x10FFFF;
}

uint32_t utf16_string::decode_two_word_literal(char16_t word1, char16_t word2) 
{
	uint32_t tmp1 = word1 & 0x03FF;
	uint32_t tmp2 = word2 & 0x03FF;
	tmp1 <<= 10;
	uint32_t tmp = tmp1 | tmp2;
	tmp += 0x10000;
	return tmp;
}

std::pair<char16_t, char16_t> utf16_string::encode_two_word_literal(uint32_t code) 
{
	std::pair<char16_t, char16_t> vars;
	code -= 0x10000;
	vars.first = (code >> 10) | 0xD800;
	vars.second = (code & 0x3FF) | 0xDC00;
	return vars;
}

void utf16_string::throw_decode_exception(const char * error_text) 
{
	delete[] m_buffer;
	throw utf16_string::decode_exception(error_text);
}

void utf16_string::dump() const
{
	using std::cout;
	using std::endl;

	cout << "size: " << m_size << endl;
	cout << "length: " << m_length << endl;
	cout << std::hex;
	for (size_t i = 0; i < m_size; ++i)
		cout << "0x" << m_buffer[i] << " ";
	cout << endl;
}

utf16_string::utf16_string() : m_size(1), m_length(0)
{
	m_buffer = new char16_t[1];
	m_buffer[0] = '\0';
}

utf16_string::utf16_string(const char16_t code[], size_t code_size) : m_length(0)
{
	m_buffer = new char16_t[code_size];
	if(code[code_size - 1])
		throw_decode_exception("code not zero terminated");
	m_buffer[code_size - 1] = 0;
	for (size_t i = 0; i < code_size - 1; ++i)
	{
		if (is_one_word_literal(code[i]))
			m_buffer[i] = code[i];
		else
		{
			if (i + 1 == code_size - 1)
				throw_decode_exception("code cut off");
			if (is_two_word_literal(code[i], code[i + 1]))
			{
				m_buffer[i] = code[i];
				m_buffer[i + 1] = code[i + 1];
				++i;
			}
			else
				throw_decode_exception("encoding literal error");
		}
		++m_length;
	}

	m_size = code_size;
}

utf16_string::utf16_string(const std::vector<uint32_t> & codes) : m_length(codes.size())
{
	std::vector<char16_t> buffer;
	for (uint32_t code : codes)
	{
		if (is_one_word_literal(code))
			buffer.push_back(code);
		else if (is_two_word_literal(code))
		{
			auto encoded = encode_two_word_literal(code);
			buffer.push_back(encoded.first);
			buffer.push_back(encoded.second);
		}
		else
			throw decode_exception("wrong character code");
	}
	buffer.push_back(0);
	m_size = buffer.size();
	m_buffer = new char16_t[m_size];
	for (size_t i = 0; i < m_size; ++i)
		m_buffer[i] = buffer[i];
}

std::vector<uint32_t> utf16_string::decode() const
{
	std::vector<uint32_t> tmp;
	for (int i = 0; i < m_size - 1; ++i)
	{
		if (is_one_word_literal(m_buffer[i]))
			tmp.push_back(m_buffer[i]);
		else if (is_two_word_literal(m_buffer[i], m_buffer[i + 1]))
		{
			tmp.push_back(decode_two_word_literal(m_buffer[i], m_buffer[i + 1]));
			++i;
		}
	}
	return tmp;
}