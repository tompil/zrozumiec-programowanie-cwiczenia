#pragma once
#include <exception>
#include <utility>
#include <vector>


class utf16_string
{
private:
	char16_t *m_buffer;
	size_t m_size;
	size_t m_length;

	static bool is_one_word_literal(char16_t word);
	static bool is_one_word_literal(uint32_t word);
	static bool is_two_word_literal(char16_t word1, char16_t word2);
	static bool is_two_word_literal(uint32_t code);
	static bool is_first_word_in_literal(char16_t word);
	static bool is_second_word_in_literal(char16_t word);
	static uint32_t decode_two_word_literal(char16_t word1, char16_t word2);
	static std::pair<char16_t, char16_t> encode_two_word_literal(uint32_t code);
	
	void throw_decode_exception(const char * error_text);
	void dump() const;
public:
	utf16_string();
	utf16_string(const char16_t code[], size_t code_size);
	utf16_string(const std::vector<uint32_t> & codes);
	size_t length() const { return m_length; }
	size_t size() const { return m_size; }
	const char16_t* data() const { return m_buffer; }
	std::vector<uint32_t> decode() const;
	~utf16_string() { delete[] m_buffer; }

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