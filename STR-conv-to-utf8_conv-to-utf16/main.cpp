#include "utf16_string/utf16_string.h"
#include "utf8_string/utf8_string.h"

#define BOOST_TEST_MODULE UTF-16_STRING_TESTS

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <string>

BOOST_AUTO_TEST_SUITE(Utf16StringTestSuite)
BOOST_AUTO_TEST_CASE(EmptyString)
{
	utf16_string str;
	size_t str_size = str.size();
	size_t str_length = str.length();
	const char16_t* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, 1);
	BOOST_CHECK_EQUAL(str_length, 0);
	BOOST_CHECK_EQUAL(str_data[0], (char16_t)'\0');
}
BOOST_AUTO_TEST_CASE(AsciiString)
{
	char16_t ascii_code[] = uR"(" !"#$%&'()*+,-./0123456789:;<=>?@"
			"ABCDEFGHIJKLMNOPRSTUVWXYZ[\]^_`abcdefghijklmnoprstuvwxyz{|}~")";
	size_t ascii_code_len = sizeof(ascii_code) / sizeof(*ascii_code);

	utf16_string str(ascii_code, ascii_code_len);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const char16_t* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, ascii_code_len);
	BOOST_CHECK_EQUAL(str_length, ascii_code_len - 1);
	BOOST_CHECK_EQUAL(str_data[str_size - 1], '\0');
	BOOST_CHECK_EQUAL_COLLECTIONS(
		str_data, str_data + str_size,
		ascii_code, ascii_code + ascii_code_len
		);
}
BOOST_AUTO_TEST_CASE(UnicodeOneWordLiteral)
{
	char16_t unicode[] = u"\u0000\u0662\uD7FF\uE000\uE747\uFFFF";
	size_t unicode_len = sizeof(unicode) / sizeof(*unicode);

	utf16_string str(unicode, unicode_len);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const char16_t* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, unicode_len);
	BOOST_CHECK_EQUAL(str_length, unicode_len - 1);
	BOOST_CHECK_EQUAL(str_data[str_size - 1], '\0');
	BOOST_CHECK_EQUAL_COLLECTIONS(
		str_data, str_data + str_size,
		unicode, unicode + unicode_len
		);
}
BOOST_AUTO_TEST_CASE(UnicodeTwoWordLiteral)
{
	char16_t unicode[] = u"\U00010000\U00010662\U0010D7FF\U0010FFFF";
	size_t unicode_len = sizeof(unicode) / sizeof(*unicode);

	utf16_string str(unicode, unicode_len);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const char16_t* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, unicode_len);
	BOOST_CHECK_EQUAL(str_length, 4);
	BOOST_CHECK_EQUAL(str_data[str_size - 1], '\0');
	BOOST_CHECK_EQUAL_COLLECTIONS(
		str_data, str_data + str_size,
		unicode, unicode + unicode_len
		);
}
BOOST_AUTO_TEST_CASE(UnicodeDecodeErrorLackOfSecondWord)
{
	const int test_strings_num = 3;
	const int test_strings_len = 6;

	char16_t unicode[test_strings_num][test_strings_len] = {
		{'a', 'd', 'b', 0xD800, 0xD990, '\0' },
		{ 'a', 'd', 'b', 0xD908, 'z', '\0' },
		{ 'a', 'd', 'b', 0xDBFF, 0xCDF6, '\0' } 
	};

	for (int i = 0; i < test_strings_num; ++i)
		BOOST_CHECK_THROW(utf16_string(unicode[i], test_strings_len),
							utf16_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(UnicodeDecodeErrorLackOfFirstWord)
{
	const int test_strings_num = 3;
	const int test_strings_len = 6;

	char16_t unicode[test_strings_num][test_strings_len] = { 
		{ 'a', 'd', 'b', 0xDC00, 0xE990, '\0' },
		{ 'a', 'd', 'b', 0xDE08, 'z', '\0' },
		{ 'a', 'd', 'b', 0xDFFF, 0xCDF6, '\0' }
	};

	for (int i = 0; i < test_strings_num; ++i)
		BOOST_CHECK_THROW(utf16_string(unicode[i], test_strings_len), utf16_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(UnicodeDecodeErrorCutOffTwoWordLiteral)
{
	char16_t unicode[] = { 'a', 'd', 'b', 0xD908, '\0' };
	BOOST_CHECK_THROW(utf16_string(unicode, 5), utf16_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(UnicodeDecodeErrorNotZeroTerminated)
{
	char16_t unicode[] = { 'a', 'd', 'b', '5', '7' };
	BOOST_CHECK_THROW(utf16_string(unicode, 5), utf16_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(DecodeUtf16ToUInt32)
{
	std::vector<uint32_t> codes = {0x0, 0xC45E, 0xD7FF, 0xE000, 0xECD4,
									0xFFFF, 0x10000, 0x10DEF5, 0x10FFFF};
	char16_t unicode[] = u"\u0000\uC45E\uD7FF\uE000\uECD4\uFFFF\U00010000"
							u"\U0010DEF5\U0010FFFF";
	size_t unicode_size = sizeof(unicode) / sizeof(*unicode);
	utf16_string str16(unicode, unicode_size);
	std::vector<uint32_t> decoded = str16.decode();
	BOOST_CHECK_EQUAL_COLLECTIONS(codes.begin(), codes.end(),
									decoded.begin(), decoded.end());
}
BOOST_AUTO_TEST_CASE(EncodeUInt32ToUtf16)
{
	std::vector<uint32_t> codes = { 0x0, 0xC45E, 0xD7FF, 0xE000, 0xECD4,
									0xFFFF, 0x10000, 0x10DEF5, 0x10FFFF };
	char16_t unicode[] = u"\u0000\uC45E\uD7FF\uE000\uECD4"
						 u"\uFFFF\U00010000\U0010DEF5\U0010FFFF";
	utf16_string str16(codes);
	const char16_t * encoded = str16.data();
	BOOST_CHECK_EQUAL_COLLECTIONS(encoded, encoded + str16.size(),
									unicode, unicode + str16.size());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Utf16StringDecodeExceptionTestSuite)
BOOST_AUTO_TEST_CASE(ConstructorsTest)
{
	utf16_string::decode_exception exc1;
	utf16_string::decode_exception exc2("utf16_string::decode_exception");
	utf16_string::decode_exception exc3(exc2);
	BOOST_CHECK_EQUAL(strcmp(exc1.what(), ""), 0);
	BOOST_CHECK_EQUAL(strcmp(exc2.what(), "utf16_string::decode_exception"), 0);
	BOOST_CHECK_EQUAL(strcmp(exc3.what(), "utf16_string::decode_exception"), 0);
}
BOOST_AUTO_TEST_CASE(AssignOperatorTest)
{
	utf16_string::decode_exception exc1("utf16_string::decode_exception");
	utf16_string::decode_exception exc2;
	exc2 = exc1;
	BOOST_CHECK_EQUAL(strcmp(exc1.what(), exc2.what()), 0);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Utf8StringTestSuite)
BOOST_AUTO_TEST_CASE(EmptyString)
{
	utf8_string str;
	size_t str_size = str.size();
	size_t str_length = str.length();
	const unsigned char* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, 1);
	BOOST_CHECK_EQUAL(str_length, 0);
	BOOST_CHECK_EQUAL(str_data[0], (unsigned char)'\0');
}
BOOST_AUTO_TEST_CASE(AsciiString)
{
	unsigned char ascii_code[] = 
		u8R"(" !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPRSTUVWXYZ")"
		u8R"("[\]^_`abcdefghijklmnoprstuvwxyz{|}~")";
	size_t ascii_code_len = sizeof(ascii_code) / sizeof(*ascii_code);

	utf8_string str(ascii_code, ascii_code_len);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const unsigned char* str_data = str.data();

	BOOST_CHECK_EQUAL(str_size, ascii_code_len);
	BOOST_CHECK_EQUAL(str_length, ascii_code_len - 1);
	BOOST_CHECK_EQUAL(str_data[str_size - 1], '\0');
	BOOST_CHECK_EQUAL_COLLECTIONS(
		str_data, str_data + str_size,
		ascii_code, ascii_code + ascii_code_len
		);
}
BOOST_AUTO_TEST_CASE(TwoByteChars)
{
	unsigned char code[] = u8"\u0080\u02EF\u07FF";
	size_t code_length = sizeof(code) / sizeof(*code);

	utf8_string str(code, code_length);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const unsigned char* str_code = str.data();

	BOOST_CHECK_EQUAL(str_size, code_length);
	BOOST_CHECK_EQUAL(str_length, 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(str_code, str_code + str_size,
		code, code + code_length);
}
BOOST_AUTO_TEST_CASE(ThreeByteChars)
{
	unsigned char code[] = u8"\u0800\u1AEF\uFFFF";
	size_t code_length = sizeof(code) / sizeof(*code);

	utf8_string str(code, code_length);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const unsigned char* str_code = str.data();

	BOOST_CHECK_EQUAL(str_size, code_length);
	BOOST_CHECK_EQUAL(str_length, 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(str_code, str_code + str_size,
		code, code + code_length);
}
BOOST_AUTO_TEST_CASE(FourByteChars)
{
	unsigned char code[] = u8"\U00010000\U0010CAEF\U0010FFFF";
	size_t code_length = sizeof(code) / sizeof(*code);

	utf8_string str(code, code_length);
	size_t str_size = str.size();
	size_t str_length = str.length();
	const unsigned char* str_code = str.data();

	BOOST_CHECK_EQUAL(str_size, code_length);
	BOOST_CHECK_EQUAL(str_length, 3);
	BOOST_CHECK_EQUAL_COLLECTIONS(str_code, str_code + str_size,
		code, code + code_length);
}
BOOST_AUTO_TEST_CASE(EncodedProhibitedUtf16CharNumber)
{
	const size_t num_of_test_codes = 3;
	const size_t code_len = 4;
	unsigned char code[num_of_test_codes][code_len] = {
		{ 0xED, 0xA0, 0x80, 0x00 }, // U+D800
		{ 0xED, 0xAB, 0x91, 0x00 }, // U+DAD1
		{ 0xED, 0xBF, 0xBF, 0x00 }  // U+DFFF
	};
	for (int i = 0; i < num_of_test_codes; ++i)
		BOOST_CHECK_THROW(utf8_string(code[i], code_len),
							utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(EncodedOverLimitCharNumber)
{
	const size_t num_of_test_codes = 3;
	const size_t code_len = 5;
	unsigned char code[num_of_test_codes][code_len] = {
		{ 0xF4, 0x90, 0x80, 0x80, 0x00 }, // U+110000
		{ 0xF6, 0xA4, 0x85, 0xAB, 0x00 }, // U+1A417B
		{ 0xF7, 0xBF, 0xBF, 0xBF, 0x00 }  // U+1FFFFF
	};
	for (int i = 0; i < num_of_test_codes; ++i)
		BOOST_CHECK_THROW(utf8_string(code[i], code_len),
			utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(PassedProhibitedUtf16CharNumber)
{
	using unicode_vec = std::vector<uint32_t>;
	std::vector<unicode_vec> codes = {
		unicode_vec( { 0xD800 } ),
		unicode_vec( { 0xDAC1 } ),
		unicode_vec( { 0xDFFF } )
	};
	for (unicode_vec& vec : codes)
		BOOST_CHECK_THROW(utf8_string str(vec), utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(PassedOverLimitCharNumber)
{
	using unicode_vec = std::vector<uint32_t>;
	std::vector<unicode_vec> codes = {
		unicode_vec({ 0x110000 }),
		unicode_vec({ 0x1A417B }),
		unicode_vec({ 0x1FFFFF })
	};
	for (unicode_vec& vec : codes)
		BOOST_CHECK_THROW(utf8_string str(vec), utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(NotZeroTerminated)
{
	unsigned char code[] = { 'a', 'g', '*', '3' };
	BOOST_CHECK_THROW(utf8_string(code, 4), utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(BrokenDataStream)
{
	using ch_vec = std::vector<unsigned char>;
	std::vector<ch_vec> codes = {
		ch_vec({ 0xCB, 0x00 }), // cut off U+02EF
		ch_vec({ 0xEB, 0xAF, 0x00 }), // broken length mark U+02EF
		ch_vec({ 0xE1, 0xAB, 0x00 }), // cut off U+1AEF
		ch_vec({ 0xF1, 0xAB, 0xAF, 0x00 }), // broken length U+1AEF
		ch_vec({ 0x1B, 0xAF, 0x00 }), // broken length
		ch_vec({ 0xF7, 0x9C, 0xAB, 0x00 }), // cut off U+1DCAEF
		ch_vec({ 0xF7, 0x9C, 0x00 }), // cut off U+1DCAEF
		ch_vec({ 0xF7, 0xAB, 0xAF, 0x00 }), // lack of bytes U+1DCAEF
		ch_vec({ 0xF7, 0xAF, 0x00 }), // lack of bytes U+1DCAEF
	};
	for (ch_vec ch : codes)
		BOOST_CHECK_THROW(utf8_string(ch.data(), ch.size()),
			utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(OversizedProperCodedCharacter)
{
	using ch_vec = std::vector<unsigned char>;
	std::vector<ch_vec> codes = {
		ch_vec({0x91, 0xA2, 0x00}),					  // oversized U+0062
		ch_vec({0xE0, 0x8B, 0xAF, 0x00}),			  // oversized U+02EF
		ch_vec({0xF0, 0x81, 0xAB, 0xAF, 0x00}),		  // oversized U+1AEF
		ch_vec({0xF8, 0x87, 0x9C, 0xAB, 0xAF, 0x00}), // oversized U+001DCAEF
	};
	for (ch_vec ch : codes)
		BOOST_CHECK_THROW(utf8_string(ch.data(), ch.size()),
			utf8_string::decode_exception);
}
BOOST_AUTO_TEST_CASE(EncodeUInt32ToUtf8)
{
	std::vector<uint32_t> codes = { 0x0, 0xC45E, 0xD7FF, 0xE000, 0xECD4,
		0xFFFF, 0x10000, 0x10DEF5, 0x10FFFF };
	unsigned char unicode[] = u8"\u0000\uC45E\uD7FF\uE000\uECD4"
		u8"\uFFFF\U00010000\U0010DEF5\U0010FFFF";
	size_t unicode_len = sizeof(unicode) / sizeof(*unicode);
	utf8_string str(codes);
	const unsigned char * encoded = str.data();
	BOOST_CHECK_EQUAL_COLLECTIONS(encoded, encoded + str.size(),
		unicode, unicode + unicode_len);
}
BOOST_AUTO_TEST_CASE(DecodeUtf8ToUInt32)
{
	std::vector<uint32_t> codes = { 0x0, 0xC45E, 0xD7FF, 0xE000, 0xECD4,
		0xFFFF, 0x10000, 0x10DEF5, 0x10FFFF };
	unsigned char unicode[] = u8"\u0000\uC45E\uD7FF\uE000\uECD4\uFFFF\U00010000"
		u8"\U0010DEF5\U0010FFFF";
	size_t unicode_size = sizeof(unicode) / sizeof(*unicode);
	utf8_string str(unicode, unicode_size);
	std::vector<uint32_t> decoded = str.decode();
	BOOST_CHECK_EQUAL_COLLECTIONS(codes.begin(), codes.end(),
		decoded.begin(), decoded.end());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Utf8StringDecodeExceptionTestSuite)
BOOST_AUTO_TEST_CASE(ConstructorsTest)
{
	utf8_string::decode_exception exc1;
	utf8_string::decode_exception exc2("utf8_string::decode_exception");
	utf8_string::decode_exception exc3(exc2);
	BOOST_CHECK_EQUAL(strcmp(exc1.what(), ""), 0);
	BOOST_CHECK_EQUAL(strcmp(exc2.what(), "utf8_string::decode_exception"), 0);
	BOOST_CHECK_EQUAL(strcmp(exc3.what(), "utf8_string::decode_exception"), 0);
}
BOOST_AUTO_TEST_CASE(AssignOperatorTest)
{
	utf8_string::decode_exception exc1("utf8_string::decode_exception");
	utf8_string::decode_exception exc2;
	exc2 = exc1;
	BOOST_CHECK_EQUAL(strcmp(exc1.what(), exc2.what()), 0);
}
BOOST_AUTO_TEST_SUITE_END()
