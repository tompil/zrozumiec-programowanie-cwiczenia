#include "utf16_string.h"

#include <cstring>


utf16_string::decode_exception::decode_exception(const decode_exception& e) noexcept
{
	*this = decode_exception(e.m_desc);
}

utf16_string::decode_exception::decode_exception(const char * desc) noexcept
{
	size_t len = strlen(desc) + 1;
	m_desc = new char[len];
	strcpy_s(m_desc, len, desc);
}

utf16_string::decode_exception& utf16_string::decode_exception::operator=(const decode_exception& e) noexcept
{
	size_t len = strlen(e.m_desc) + 1;
	char * desc = new char[len];
	strcpy_s(desc, len, e.m_desc);
	delete[] m_desc;
	m_desc = desc;
	return *this;
}

const char* utf16_string::decode_exception::what() const noexcept
{ 
	if (m_desc == nullptr)
		return "";
	return m_desc;
}

