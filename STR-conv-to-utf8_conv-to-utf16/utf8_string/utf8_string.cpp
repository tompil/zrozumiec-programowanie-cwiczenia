#include "utf8_string.h"

#include <iostream>
#include <utility>
#include <vector>

const std::array<utf8_string::code_len_marker, 3> utf8_string::len_markers = {
	utf8_string::code_len_marker({ 0xC0, 0xE0, 2 }),
	utf8_string::code_len_marker({ 0xE0, 0xF0, 3 }),
	utf8_string::code_len_marker({ 0xF0, 0xF8, 4 })
};

bool utf8_string::is_utf8_permitted_char(uint32_t char_num)
{
	return (char_num <= 0xD7FF) || (char_num >= 0xE000 && char_num <= 0x10FFFF);
}

bool utf8_string::is_ascii_char(uint8_t ch)
{
	return ch < 0x80;
}

uint8_t utf8_string::get_encoded_char_len(uint8_t ch)
{
	for (code_len_marker m : len_markers)
		if ((ch & m.mask) == m.marker)
			return m.len;
	throw decode_exception("broken first byte of encoded character");
}

uint32_t utf8_string::get_repr(const uint8_t* begin, const uint8_t* end)
{
	size_t len = end - begin;
	const uint8_t first_byte_mask = len_markers[len - 2].mask;

	uint32_t tmp = (uint32_t)(*begin & ~first_byte_mask) << (6 * --len);

	for (const uint8_t* p_tmp = begin + 1; p_tmp != end; ++p_tmp)
	{
		if ((*p_tmp & data_byte_mask) != data_byte_marker)
			throw decode_exception("broken data stream");
		tmp |= (uint32_t)(*p_tmp & ~data_byte_mask) << (6 * --len);
	}

	return tmp;
}

void push_back_repr(std::vector<uint8_t>& v, const uint8_t* begin, const uint8_t* end)
{
	for (const uint8_t* tmp = begin; tmp != end; ++tmp)
		v.push_back(*tmp);
}

void push_back_repr(std::vector<uint8_t>& dest, const std::vector<uint8_t>& src)
{
	for (uint8_t ch : src)
		dest.push_back(ch);
}

void utf8_string::check_repr(const uint8_t* begin, const uint8_t* end)
{
	uint32_t repr = get_repr(begin, end);
	if (!is_utf8_permitted_char(repr))
		throw decode_exception("not permitted in utf-8 encoding character encoded");
	size_t len = end - begin;
	if (!is_proper_size(repr, len))
		throw decode_exception("wrong character code size");
}

bool utf8_string::is_proper_size(uint32_t code, size_t size)
{
	switch (size)
	{
	case 1:
		return code <= 0x7F;
	case 2:
		return code >= 0x80 && code <= 0x7FF;
	case 3:
		return code >= 0x800 && code <= 0xFFFF;
	case 4:
		return code >= 10000 && code <= 0x10FFFF;
	default: 
		return false;
	}
}

size_t utf8_string::get_len_to_encode(uint32_t code)
{
	if (code <= 0x7F)
		return 1;
	if (code >= 0x80 && code <= 0x7FF)
		return 2;
	if (code >= 0x800 && code <= 0xFFFF)
		return 3;
	if (code >= 10000 && code <= 0x10FFFF)
		return 4;
	return 0;
}

utf8_string::utf8_string(const uint8_t *code, size_t code_size)
	: m_length(0), m_buffer()
{
	if (code[code_size - 1] != '\0')
		throw decode_exception("input string note zero terminated");
	try
	{
		for (size_t i = 0; i < code_size - 1; ++i)
		{
			if (is_ascii_char(code[i]))
				m_buffer.push_back(code[i]);
			else
			{
				uint8_t char_len = get_encoded_char_len(code[i]);
				check_repr(&code[i], &code[i] + char_len);
				push_back_repr(m_buffer, &code[i], &code[i] + char_len);
				i += char_len - 1;
			}
			++m_length;
		}
	}
	catch (decode_exception& e)
	{
		throw;
	}
	m_buffer.push_back('\0');
}

std::vector<uint8_t> utf8_string::get_char_repr(uint32_t code)
{
	size_t len = get_len_to_encode(code);

	if (len == 1)
		return std::vector<uint8_t>(1, (uint8_t)code);

	std::vector<uint8_t> tmp(len, data_byte_marker);
	code_len_marker clm = len_markers[len - 2];

	for (size_t i = len - 1; i > 0; --i, code >>= 6)
		tmp[i] |= code & ~data_byte_mask;

	tmp[0] = clm.marker | (code & ~clm.mask);
	return tmp;
}

utf8_string::utf8_string(const std::vector<uint32_t> & codes)
	: m_length(0), m_buffer()
{
	for (uint32_t ch : codes)
	{
		if (!is_utf8_permitted_char(ch))
			throw decode_exception("character code not permitted by UTF-8");
		std::vector<uint8_t> code_repr = get_char_repr(ch);
		push_back_repr(m_buffer, code_repr);
		++m_length;
	}
	m_buffer.push_back('\0');
}

std::vector<uint32_t> utf8_string::decode() const
{
	std::vector<uint32_t> tmp;
	for (size_t i = 0; i < m_buffer.size() - 1; ++i)
		if (is_ascii_char(m_buffer[i]))
			tmp.push_back(m_buffer[i]);
		else
		{
			uint8_t char_len = get_encoded_char_len(m_buffer[i]);
			uint32_t repr = get_repr(&m_buffer[i], &m_buffer[i] + char_len);
			tmp.push_back(repr);
			i += char_len - 1;
		}
	return tmp;
}