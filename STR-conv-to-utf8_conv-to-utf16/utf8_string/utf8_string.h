/*
BASIC UTF-8 ENCODING CLASS IMPLEMENTATION
Class implements UTF-8 definition from 'RFC 3629' document.
The 'RFC 3629' document is published here:
https://tools.ietf.org/html/rfc3629
Up to standard the implementation provides full compatibility
with UTF-16 encoding. The class encodes characters from 
the U+0000..U+10FFFF range and prohibits encoding character numbers
from U+D800 to U+DFFF(reserved by UTF-16 encoding characters from 
the U+10000..U+10FFFF range).
*/

#pragma once
#include <array>
#include <vector>


class utf8_string
{
private:
	std::vector<uint8_t> m_buffer;
	size_t m_length;

	struct code_len_marker
	{
		uint8_t marker;
		uint8_t mask;
		uint8_t len;
	};
	static const std::array<code_len_marker, 3> len_markers;
	static const uint8_t data_byte_mask = 0xC0;
	static const uint8_t data_byte_marker = 0x80;

	static bool is_utf8_permitted_char(uint32_t char_num);
	static bool is_ascii_char(uint8_t ch);
	static uint8_t get_encoded_char_len(uint8_t ch);
	static void check_repr(const uint8_t* begin, const uint8_t* end);
	static uint32_t get_repr(const uint8_t* begin, const uint8_t* end);
	static bool is_proper_size(uint32_t code, size_t size);
	static size_t get_len_to_encode(uint32_t code);
	static std::vector<uint8_t> get_char_repr(uint32_t code);
public:
	utf8_string() : m_length(0), m_buffer(std::vector<unsigned char>({ '\0' }))
		{}
	utf8_string(const uint8_t *code, size_t code_size);
	utf8_string(const std::vector<uint32_t> & codes);
	size_t length() const { return m_length; }
	size_t size() const { return m_buffer.size(); }
	unsigned const char* data() const { return m_buffer.data(); }
	std::vector<uint32_t> decode() const;
	~utf8_string() {}

	class decode_exception : public std::exception
	{
	private:
		char * m_desc;
	public:
		decode_exception() noexcept { m_desc = nullptr; }
		decode_exception(const decode_exception& e) noexcept;
		decode_exception(const char * desc) noexcept;
		decode_exception& operator=(const decode_exception& e) noexcept;
		~decode_exception() { delete[] m_desc; }
		const char* what() const noexcept;
	};
};