#define _SCL_SECURE_NO_WARNINGS

#include "big_numbers.h"

#define BOOST_TEST_MODULE BigNumberTests

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <climits>
#include <iostream>
#include <vector>


using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_SUITE(StringConstrAndStringOperatorTests)
	BOOST_AUTO_TEST_CASE(DefaultTest) {
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber()), "0");
	}
	BOOST_AUTO_TEST_CASE(EmptyStringTest) {
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber("")), "0");
	}
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber("0")), "0");
	}
	BOOST_AUTO_TEST_CASE(NegativeZeroTest) {
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber("-0")), "0");
	}
	BOOST_AUTO_TEST_CASE(PositiveRandomTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			char len = num_len(rng);
			std::string num = "";
			num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num += other_num(rng);
			}
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), num);
		}
	}
	BOOST_AUTO_TEST_CASE(PositivePlusRandomTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			char len = num_len(rng);
			std::string raw_num = "";
			raw_num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				raw_num += other_num(rng);
			}
			std::string num = "+" + raw_num;
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), raw_num);
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeRandomTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			char len = num_len(rng);
			std::string num = "-";
			num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num += other_num(rng);
			}
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), num);
		}
	}
	BOOST_AUTO_TEST_CASE(ZeroesTest) {
		boost::random::uniform_int_distribution<char> num_len(1, 30);
		boost::random::mt19937 rng(std::time(0));
		std::string num = "0";
		char len = num_len(rng);
		for (size_t i = 0; i < len; i++)
		{
			num += "0";
		}
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), "0");
	}
	BOOST_AUTO_TEST_CASE(AdditionnalZeroesTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> zeroes_len(1, 30);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 30; ++i) {
			std::string num = "";
			char zero_len = zeroes_len(rng);
			for (size_t i = 0; i < zero_len; i++)
			{
				num += "0";
			}
			char len = num_len(rng);
			std::string raw_num = "";
			raw_num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				raw_num += other_num(rng);
			}
			num += raw_num;
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), raw_num);
		}
	}
	BOOST_AUTO_TEST_CASE(AdditionnalZeroesPlusTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> zeroes_len(1, 30);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 30; ++i) {
			std::string num = "+";
			char zero_len = zeroes_len(rng);
			for (size_t i = 0; i < zero_len; i++)
			{
				num += "0";
			}
			char len = num_len(rng);
			std::string raw_num = "";
			raw_num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				raw_num += other_num(rng);
			}
			num += raw_num;
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), raw_num);
		}
	}
	BOOST_AUTO_TEST_CASE(AdditionnalZeroesNegativeTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> zeroes_len(1, 30);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 30; ++i) {
			std::string num = "-";
			char zero_len = zeroes_len(rng);
			for (size_t i = 0; i < zero_len; i++)
			{
				num += "0";
			}
			char len = num_len(rng);
			std::string raw_num = "";
			raw_num += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				raw_num += other_num(rng);
			}
			num += raw_num;
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(num)), "-" + raw_num);
		}
	}
	BOOST_AUTO_TEST_CASE(WrongInputTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::mt19937 rng(std::time(0));
		std::string chars(
			"abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"1234567890"
			"!@#$%^&*()"
			"`~-_=+[{]}\\|;:'\",<.>/? ");
		boost::random::uniform_int_distribution<char> index_char(0, chars.length() - 1);
		for (int j = 0; j < 30; ++j) {
			std::string text = "";
			size_t len = num_len(rng);
			for (int i = 0; i < len; ++i) {
				text += chars[index_char(rng)];
			}
			BOOST_CHECK_THROW(BigNumber bg(text), BigNumber::WrongInput);
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LLIntConstrAndStringOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg(0);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), "0");
	}
	BOOST_AUTO_TEST_CASE(MaxPositiveTest) {
		long long int bg{ LLONG_MAX };
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(bg)), std::to_string(bg));
	}
	BOOST_AUTO_TEST_CASE(MinNegativeTest) {
		long long int bg{ LLONG_MIN };
		BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(bg)), std::to_string(bg));
	}
	BOOST_AUTO_TEST_CASE(SmallPositiveTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, 20);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 5; ++i) {
			bg = dist(rng);
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(bg)), std::to_string(bg));
		}
	}
	BOOST_AUTO_TEST_CASE(SmallNegativeTest) {
		boost::random::uniform_int_distribution<long long int> dist(-20, 0);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 5; ++i) {
			bg = dist(rng);
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(bg)), std::to_string(bg));
		}
	}
	BOOST_AUTO_TEST_CASE(RandomNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 1000; ++i) {
			bg = dist(rng);
			BOOST_CHECK_EQUAL(static_cast<std::string>(BigNumber(bg)), std::to_string(bg));
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(BigNumberConstrTests)
	BOOST_AUTO_TEST_CASE(LvalueRefZeroConstrTest) {
		std::string num = "0";
		BigNumber bg_temp(num);
		BigNumber bg(bg_temp);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
	BOOST_AUTO_TEST_CASE(LvalueRefNegativeConstrTest) {
		std::string num = "-45664587437853457346876770";
		BigNumber bg_temp(num);
		BigNumber bg(bg_temp);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
	BOOST_AUTO_TEST_CASE(LvalueRefPositiveConstrTest) {
		std::string num = "4389665973466746363990690792";
		BigNumber bg_temp(num);
		BigNumber bg(bg_temp);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
	BOOST_AUTO_TEST_CASE(RvalueRefZeroConstrTest) {
		std::string num = "0";
		BigNumber bg_temp(num);
		BigNumber bg(std::move(bg_temp));
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
	BOOST_AUTO_TEST_CASE(RvalueRefNegativeConstrTest) {
		std::string num = "-45664587437853457346876770";
		BigNumber bg_temp(num);
		BigNumber bg(std::move(bg_temp));
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
	BOOST_AUTO_TEST_CASE(RvalueRefPositiveConstrTest) {
		std::string num = "4389665973466746363990690792";
		BigNumber bg_temp(num);
		BigNumber bg(std::move(bg_temp));
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), num);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(StreamOperatorTests)
	BOOST_AUTO_TEST_CASE(OutputStreamOperatorTest) {
		output_test_stream output;
		std::vector<std::string> nums{ "0", "104934850", "-59048582" };

		for (std::string str : nums)
		{
			BigNumber bg(str);
			output << bg;
			BOOST_CHECK(!output.is_empty(false));
			BOOST_CHECK(output.check_length(str.length(), false));
			BOOST_CHECK(output.is_equal(str));
		}
	}
	BOOST_AUTO_TEST_CASE(InputStreamOperatorTest) {
		std::vector<std::string> nums{ "0", "104934850", "-59048582" };
		for (std::string str : nums)
		{
			BigNumber bg1(str);
			BigNumber bg2;
			std::istringstream input(str);
			input >> bg2;
			BOOST_CHECK_EQUAL(bg1, bg2);
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(EqualOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1("0");
		BigNumber bg2(0);
		BOOST_CHECK_EQUAL(bg1, bg2);
	}
	BOOST_AUTO_TEST_CASE(MinusZeroTest) {
		BigNumber bg1("0");
		BigNumber bg2("-0");
		BOOST_CHECK_EQUAL(bg1, bg2);
	}
	BOOST_AUTO_TEST_CASE(RandomPositiveTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(std::to_string(bg));
			BOOST_CHECK_EQUAL(bg1, bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(RandomNegativeTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(std::to_string(bg));
			BOOST_CHECK_EQUAL(bg1, bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(RandomOppositeTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(-bg);
			BOOST_CHECK_MESSAGE(!(bg1 == bg2), "bg1 = " << bg1 << " bg2 = " << bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(NotEqualPositiveTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));

		for (int i = 0; i < 10; ++i) {
			char len = num_len(rng);
			std::string num1 = "";
			num1 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num1 += other_num(rng);
			}
			len = num_len(rng);
			std::string num2 = "";
			num2 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num2 += other_num(rng);
			}
			if (num1 == num2) --i; continue;
			BigNumber bg1(num1);
			BigNumber bg2(num2);
			BOOST_CHECK_MESSAGE(!(bg1 == bg2), "bg1 = " << bg1 << " bg2 = " << bg2);
		}

	}
	BOOST_AUTO_TEST_CASE(NotEqualNegativeTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));

		for (int i = 0; i < 10; ++i) {
			char len = num_len(rng);
			std::string num1 = "-";
			num1 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num1 += other_num(rng);
			}
			len = num_len(rng);
			std::string num2 = "-";
			num2 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num2 += other_num(rng);
			}
			if (num1 == num2) --i; continue;
			BigNumber bg1(num1);
			BigNumber bg2(num2);
			BOOST_CHECK_MESSAGE(!(bg1 == bg2), "bg1 = " << bg1 << " bg2 = " << bg2);
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(NotEqualOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1("0");
		BigNumber bg2(0);
		BOOST_CHECK(!(bg1!=bg2));
	}
	BOOST_AUTO_TEST_CASE(EqualPositiveTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(std::to_string(bg));
			BOOST_CHECK_MESSAGE(!(bg1 != bg2), "bg1 = " << bg1 << " bg2 = " << bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(EqualNegativeTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(std::to_string(bg));
			BOOST_CHECK_MESSAGE(!(bg1 != bg2), "bg1 = " << bg1 << " bg2 = " << bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(RandomOppositeTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		long long int bg;
		for (int i = 0; i < 10; ++i) {
			bg = dist(rng);
			BigNumber bg1(bg);
			BigNumber bg2(-bg);
			BOOST_CHECK_NE(bg1, bg2);
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));

		for (int i = 0; i < 10; ++i) {
			char len = num_len(rng);
			std::string num1 = "";
			num1 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num1 += other_num(rng);
			}
			len = num_len(rng);
			std::string num2 = "";
			num2 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num2 += other_num(rng);
			}
			if (num1 == num2) --i; continue;
			BigNumber bg1(num1);
			BigNumber bg2(num2);
			BOOST_CHECK_NE(bg1, bg2);
		}

	}
	BOOST_AUTO_TEST_CASE(NegativeTest) {
		boost::random::uniform_int_distribution<char> num_len(1, CHAR_MAX);
		boost::random::uniform_int_distribution<char> first_num('1', '9');
		boost::random::uniform_int_distribution<char> other_num('0', '9');
		boost::random::mt19937 rng(std::time(0));

		for (int i = 0; i < 10; ++i) {
			char len = num_len(rng);
			std::string num1 = "-";
			num1 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num1 += other_num(rng);
			}
			len = num_len(rng);
			std::string num2 = "-";
			num2 += first_num(rng);
			for (int j = 0; j < len - 1; ++j) {
				num2 += other_num(rng);
			}
			if (num1 == num2) --i; continue;
			BigNumber bg1(num1);
			BigNumber bg2(num2);
			BOOST_CHECK_NE(bg1, bg2);
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UnaryMinusOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg(0);
		BigNumber mbg = -bg;
		BOOST_CHECK_EQUAL(mbg, bg);
		BOOST_CHECK_EQUAL(static_cast<std::string>(mbg), "0");
	}
	BOOST_AUTO_TEST_CASE(PositiveTest) {
		BigNumber bg("24546");
		BigNumber mbg = -bg;
		BOOST_CHECK_EQUAL(static_cast<std::string>(mbg), "-24546");
	}
	BOOST_AUTO_TEST_CASE(NegativeTest) {
		BigNumber bg("-24546");
		BigNumber mbg = -bg;
		BOOST_CHECK_EQUAL(static_cast<std::string>(mbg), "24546");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AssignOperatorTests)
	BOOST_AUTO_TEST_CASE(LvalueAssignOpTest) {
		BigNumber bg1("0");
		BigNumber bg2(-4374577);
		BigNumber bg3(454535);
		BigNumber bg;
		bg = bg1;
		BOOST_CHECK_EQUAL(bg, bg1);
		bg = bg2;
		BOOST_CHECK_EQUAL(bg, bg2);
		bg = bg3;
		BOOST_CHECK_EQUAL(bg, bg3);
	}
	BOOST_AUTO_TEST_CASE(RvalueAssignOpTest) {
		BigNumber bg1("0");
		BigNumber bg2(-4374577);
		BigNumber bg3(454535);
		BigNumber bg;
		bg = std::move(bg1);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), "0");
		bg = std::move(bg2);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), "-4374577");
		bg = std::move(bg3);
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), "454535");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PlusOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1, bg2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 + bg2), "0");
	}
	BOOST_AUTO_TEST_CASE(ZeroAdditionTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bgz(0);
		for (int i = 0; i < 100; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg(ibg);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bgz + bg), std::to_string(ibg));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg + bgz), std::to_string(ibg));
			BOOST_CHECK_EQUAL(bg + bgz, bgz + bg);
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX/2);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 + bg2), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 + bg1), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(bg1 + bg2, bg2 + bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN / 2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 + bg2), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 + bg1), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(bg1 + bg2, bg2 + bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, LLONG_MAX);
		boost::random::uniform_int_distribution<long long int> dist2(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 + bg2), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 + bg1), std::to_string(ibg1 + ibg2));
			BOOST_CHECK_EQUAL(bg1 + bg2, bg2 + bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(OppositeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(-ibg);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 + bg2), "0");
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 + bg1), "0");
			BOOST_CHECK_EQUAL(bg1 + bg2, bg2 + bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(Test32000Plus1000) {
		BigNumber bg2(32000);
		BigNumber tau(1000);
		bg2 = bg2 + tau;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg2), "33000");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MinusOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1, bg2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 - bg2), "0");
	}
	BOOST_AUTO_TEST_CASE(ZeroAdditionTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bgz(0);
		for (int i = 0; i < 100; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg(ibg);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bgz - bg), std::to_string(-ibg));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg - bgz), std::to_string(ibg));
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 - bg2), std::to_string(ibg1 - ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 - bg1), std::to_string(ibg2 - ibg1));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN / 2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 - bg2), std::to_string(ibg1 - ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 - bg1), std::to_string(ibg2 - ibg1));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, LLONG_MAX/2);
		boost::random::uniform_int_distribution<long long int> dist2(LLONG_MIN/2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 - bg2), std::to_string(ibg1 - ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 - bg1), std::to_string(ibg2 - ibg1));
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 - bg2), "0");
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 - bg1), "0");
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MultiplicationOperatorTests)
	BOOST_AUTO_TEST_CASE(TwoZeroesTest) {
		BigNumber zero1;
		BigNumber zero2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(zero1 * zero2), "0");
	}
	BOOST_AUTO_TEST_CASE(MultByZeroTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BigNumber zero;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg * zero), "0");
		BOOST_CHECK_EQUAL(static_cast<std::string>(zero * bg), "0");
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, sqrt(LLONG_MAX));
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 * bg2), std::to_string(ibg1 * ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 * bg1), std::to_string(ibg2 * ibg1));
			BOOST_CHECK_EQUAL(bg1 * bg2, bg2 * bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(-sqrt(LLONG_MAX), -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 * bg2), std::to_string(ibg1 * ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 * bg1), std::to_string(ibg2 * ibg1));
			BOOST_CHECK_EQUAL(bg1 * bg2, bg2 * bg1);
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, sqrt(LLONG_MAX));
		boost::random::uniform_int_distribution<long long int> dist2(-sqrt(LLONG_MAX), -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1 * bg2), std::to_string(ibg1 * ibg2));
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg2 * bg1), std::to_string(ibg2 * ibg1));
			BOOST_CHECK_EQUAL(bg1 * bg2, bg2 * bg1);
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LessThanOperatorTests)
	BOOST_AUTO_TEST_CASE(LessThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_LT(bg, zero);
	}
	BOOST_AUTO_TEST_CASE(GreaterThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_LT(zero, bg);
	}
	BOOST_AUTO_TEST_CASE(BothPositive) {
		boost::random::uniform_int_distribution<long long int> separator_dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(0, separator - 1);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, LLONG_MAX);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LT(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(BothNegative) {
		boost::random::uniform_int_distribution<long long int> separator_dist(LLONG_MIN + 1, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, separator - 1);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, -1);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LT(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(DifferentSigns) {
		boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> greater_dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LT(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(VariousNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(bg1 < bg2, ibg1 < ibg2);
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			BOOST_CHECK_EQUAL(bg1 < bg2, false);
		}
	}
	BOOST_AUTO_TEST_CASE(GreaterNumber) {
		BigNumber bg1(33000);
		BigNumber bg2(32000);
		BOOST_CHECK_EQUAL(bg1 < bg2, false);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GreaterThanOperatorTests)
	BOOST_AUTO_TEST_CASE(LessThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_GT(zero, bg);
	}
	BOOST_AUTO_TEST_CASE(GreaterThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_GT(bg, zero);
	}
	BOOST_AUTO_TEST_CASE(BothPositive) {
		boost::random::uniform_int_distribution<long long int> separator_dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(0, separator - 1);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, LLONG_MAX);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GT(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(BothNegative) {
		boost::random::uniform_int_distribution<long long int> separator_dist(LLONG_MIN + 1, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, separator - 1);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, -1);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GT(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(DifferentSigns) {
		boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> greater_dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GT(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(VariousNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(bg1 > bg2, ibg1 > ibg2);
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			BOOST_CHECK_EQUAL(bg1 > bg2, false);
		}
	}
	BOOST_AUTO_TEST_CASE(LesserNumber) {
		BigNumber bg1(33000);
		BigNumber bg2(32000);
		BOOST_CHECK_EQUAL(bg2 > bg1, false);
	}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LessThanOrEqualOperatorTests)
	BOOST_AUTO_TEST_CASE(LessThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, 0);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_LE(bg, zero);
	}
	BOOST_AUTO_TEST_CASE(GreaterThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_LE(zero, bg);
	}
	BOOST_AUTO_TEST_CASE(BothPositive) {
		boost::random::uniform_int_distribution<long long int> separator_dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(0, separator);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, LLONG_MAX);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LE(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(BothNegative) {
		boost::random::uniform_int_distribution<long long int> separator_dist(LLONG_MIN + 1, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, separator);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, -1);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LE(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(DifferentSigns) {
		boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> greater_dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_LE(lesser, greater);
		}
	}
	BOOST_AUTO_TEST_CASE(VariousNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(bg1 <= bg2, ibg1 <= ibg2);
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			BOOST_CHECK_EQUAL(bg1 <= bg2, true);
		}
	}
	BOOST_AUTO_TEST_CASE(GreaterNumber) {
		BigNumber bg1(33000);
		BigNumber bg2(32000);
		BOOST_CHECK_EQUAL(bg1 <= bg2, false);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GreaterThanOrEqualOperatorTests)
	BOOST_AUTO_TEST_CASE(LessThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, 0);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_GE(zero, bg);
	}
	BOOST_AUTO_TEST_CASE(GreaterThanZero) {
		BigNumber zero;
		boost::random::uniform_int_distribution<long long int> dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BOOST_CHECK_GE(bg, zero);
	}
	BOOST_AUTO_TEST_CASE(BothPositive) {
		boost::random::uniform_int_distribution<long long int> separator_dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(0, separator);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, LLONG_MAX);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GE(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(BothNegative) {
		boost::random::uniform_int_distribution<long long int> separator_dist(LLONG_MIN + 1, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int separator = separator_dist(rng);
			boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, separator);
			boost::random::uniform_int_distribution<long long int> greater_dist(separator, -1);
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GE(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(DifferentSigns) {
		boost::random::uniform_int_distribution<long long int> lesser_dist(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> greater_dist(0, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			BigNumber lesser(lesser_dist(rng));
			BigNumber greater(greater_dist(rng));
			BOOST_CHECK_GE(greater, lesser);
		}
	}
	BOOST_AUTO_TEST_CASE(VariousNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			BOOST_CHECK_EQUAL(bg1 >= bg2, ibg1 >= ibg2);
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumbers) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			BOOST_CHECK_EQUAL(bg1 >= bg2, true);
		}
	}
	BOOST_AUTO_TEST_CASE(LesserNumber) {
		BigNumber bg1(33000);
		BigNumber bg2(32000);
		BOOST_CHECK_EQUAL(bg2 >= bg1, false);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DivisionOperatorTests)
	BOOST_AUTO_TEST_CASE(DivisionByZero) {
		BigNumber num(745974537);
		BigNumber zero;
		BOOST_CHECK_THROW(num / zero, BigNumber::DivisionByZero);
	}
	BOOST_AUTO_TEST_CASE(DivisionByOne) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber num(dist(rng));
		BigNumber one(1);
		BOOST_CHECK_EQUAL(num / one, num);
	}
	BOOST_AUTO_TEST_CASE(ZeroDivision) {
		BigNumber num(745974537);
		BigNumber zero;
		BOOST_CHECK_EQUAL(zero / num, zero);
	}
	BOOST_AUTO_TEST_CASE(PositiveByPositive) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i)
		{
			long long int lnum1 = dist(rng);
			long long int lnum2 = dist(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1 / num2), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveByNegative) {
		boost::random::uniform_int_distribution<long long int> dist1(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> dist2(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i)
		{
			long long int lnum1 = dist2(rng);
			long long int lnum2 = dist1(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1 / num2), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeByNegative) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i)
		{
			long long int lnum1 = dist(rng);
			long long int lnum2 = dist(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1 / num2), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeByPositive) {
		boost::random::uniform_int_distribution<long long int> dist1(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> dist2(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 50; ++i)
		{
			long long int lnum1 = dist1(rng);
			long long int lnum2 = dist2(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1 / num2), std::to_string(lnum1 / lnum2));
		}
	}
	//BOOST_AUTO_TEST_CASE(LargeBySmall) {
	//	boost::random::uniform_int_distribution<long long int> dist1(LLONG_MAX / 2, LLONG_MAX);
	//	boost::random::uniform_int_distribution<long long int> dist2(1, 1000);
	//	boost::random::mt19937 rng(std::time(0));
	//		long long int lnum1 = 45948366; //dist1(rng);
	//		long long int lnum2 = 1000; //dist2(rng);
	//		BigNumber num1(lnum1);
	//		BigNumber num2(lnum2);
	//		BOOST_CHECK_EQUAL(static_cast<std::string>(num1 / num2), std::to_string(lnum1 / lnum2));
	//}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PreIncrementationOperatorTests)
	BOOST_AUTO_TEST_CASE(IncrementZero) {
		BigNumber bg;
		BOOST_CHECK_EQUAL(++bg, BigNumber(1));
		BOOST_CHECK_EQUAL(bg, BigNumber(1));
	}
	BOOST_AUTO_TEST_CASE(IncrementMinusOne) {
		BigNumber bg(-1);
		BOOST_CHECK_EQUAL(++bg, BigNumber());
		BOOST_CHECK_EQUAL(bg, BigNumber());
	}
	BOOST_AUTO_TEST_CASE(IncrementPositive) {
		BigNumber bg(689360);
		BOOST_CHECK_EQUAL(++bg, BigNumber(689361));
		BOOST_CHECK_EQUAL(bg, BigNumber(689361));
	}
	BOOST_AUTO_TEST_CASE(IncrementNegative) {
		BigNumber bg(-689360);
		BOOST_CHECK_EQUAL(++bg, BigNumber(-689359));
		BOOST_CHECK_EQUAL(bg, BigNumber(-689359));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PreDecrementationOperatorTests)
	BOOST_AUTO_TEST_CASE(DecrementZero) {
		BigNumber bg;
		BOOST_CHECK_EQUAL(--bg, BigNumber(-1));
		BOOST_CHECK_EQUAL(bg, BigNumber(-1));
	}
	BOOST_AUTO_TEST_CASE(DecrementOne) {
		BigNumber bg(1);
		BOOST_CHECK_EQUAL(--bg, BigNumber());
		BOOST_CHECK_EQUAL(bg, BigNumber());
	}
	BOOST_AUTO_TEST_CASE(DecrementPositive) {
		BigNumber bg(689360);
		BOOST_CHECK_EQUAL(--bg, BigNumber(689359));
		BOOST_CHECK_EQUAL(bg, BigNumber(689359));
	}
	BOOST_AUTO_TEST_CASE(DecrementNegative) {
		BigNumber bg(-689360);
		BOOST_CHECK_EQUAL(--bg, BigNumber(-689361));
		BOOST_CHECK_EQUAL(bg, BigNumber(-689361));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PostIncrementationOperatorTests)
	BOOST_AUTO_TEST_CASE(IncrementZero) {
		BigNumber bg;
		BOOST_CHECK_EQUAL(bg++, BigNumber());
		BOOST_CHECK_EQUAL(bg, BigNumber(1));
	}
	BOOST_AUTO_TEST_CASE(IncrementMinusOne) {
		BigNumber bg(-1);
		BOOST_CHECK_EQUAL(bg++, BigNumber(-1));
		BOOST_CHECK_EQUAL(bg, BigNumber());
	}
	BOOST_AUTO_TEST_CASE(IncrementPositive) {
		BigNumber bg(689360);
		BOOST_CHECK_EQUAL(bg++, BigNumber(689360));
		BOOST_CHECK_EQUAL(bg, BigNumber(689361));
	}
	BOOST_AUTO_TEST_CASE(IncrementNegative) {
		BigNumber bg(-689360);
		BOOST_CHECK_EQUAL(bg++, BigNumber(-689360));
		BOOST_CHECK_EQUAL(bg, BigNumber(-689359));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PostDecrementationOperatorTests)
	BOOST_AUTO_TEST_CASE(DecrementZero) {
		BigNumber bg;
		BOOST_CHECK_EQUAL(bg--, BigNumber());
		BOOST_CHECK_EQUAL(bg, BigNumber(-1));
	}
	BOOST_AUTO_TEST_CASE(DecrementOne) {
		BigNumber bg(1);
		BOOST_CHECK_EQUAL(bg--, BigNumber(1));
		BOOST_CHECK_EQUAL(bg, BigNumber());
	}
	BOOST_AUTO_TEST_CASE(DecrementPositive) {
		BigNumber bg(689360);
		BOOST_CHECK_EQUAL(bg--, BigNumber(689360));
		BOOST_CHECK_EQUAL(bg, BigNumber(689359));
	}
	BOOST_AUTO_TEST_CASE(DecrementNegative) {
		BigNumber bg(-689360);
		BOOST_CHECK_EQUAL(bg--, BigNumber(-689360));
		BOOST_CHECK_EQUAL(bg, BigNumber(-689361));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(AdditionAssignmentOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1, bg2;
		bg1 += bg2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), "0");
	}
	BOOST_AUTO_TEST_CASE(ZeroAdditionTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bgz(0);
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg(ibg);
			bg += bgz;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg), std::to_string(ibg));
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 += bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 + ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN / 2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 += bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 + ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, LLONG_MAX);
		boost::random::uniform_int_distribution<long long int> dist2(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 += bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 + ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(OppositeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(-ibg);
			bg1 += bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), "0");

		}
	}
	BOOST_AUTO_TEST_CASE(Test32000Plus1000) {
		BigNumber bg2(32000);
		BigNumber tau(1000);
		bg2 += tau;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg2), "33000");
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(SubstractionAssignmentOperatorTests)
	BOOST_AUTO_TEST_CASE(ZeroTest) {
		BigNumber bg1, bg2;
		bg1 -= bg2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), "0");
	}
	BOOST_AUTO_TEST_CASE(ZeroAdditionTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bgz(0);
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg(ibg);
			bg -= bgz;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg), std::to_string(ibg));
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX / 2);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 -= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 - ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN / 2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 -= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 - ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, LLONG_MAX / 2);
		boost::random::uniform_int_distribution<long long int> dist2(LLONG_MIN / 2, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 -= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 - ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(SameNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg = dist(rng);
			BigNumber bg1(ibg);
			BigNumber bg2(ibg);
			bg1 -= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), "0");
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MultiplicationAssignmentOperatorTests)
	BOOST_AUTO_TEST_CASE(TwoZeroesTest) {
		BigNumber zero1;
		BigNumber zero2;
		zero1 *= zero2;
		BOOST_CHECK_EQUAL(static_cast<std::string>(zero1), "0");
	}
	BOOST_AUTO_TEST_CASE(MultByZeroTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		BigNumber bg(dist(rng));
		BigNumber zero;
		bg *= zero;
		BOOST_CHECK_EQUAL(static_cast<std::string>(bg), "0");
	}
	BOOST_AUTO_TEST_CASE(PositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(1, sqrt(LLONG_MAX));
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 *= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 * ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist(-sqrt(LLONG_MAX), -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i) {
			long long int ibg1 = dist(rng);
			long long int ibg2 = dist(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 *= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 * ibg2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeAndPositiveNumberTest) {
		boost::random::uniform_int_distribution<long long int> dist1(1, sqrt(LLONG_MAX));
		boost::random::uniform_int_distribution<long long int> dist2(-sqrt(LLONG_MAX), -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 100; ++i) {
			long long int ibg1 = dist1(rng);
			long long int ibg2 = dist2(rng);
			BigNumber bg1(ibg1);
			BigNumber bg2(ibg2);
			bg1 *= bg2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(bg1), std::to_string(ibg1 * ibg2));
		}
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DivisionAssignmentOperatorTests)
	BOOST_AUTO_TEST_CASE(DivisionByZero) {
		BigNumber num(745974537);
		BigNumber zero;
		BOOST_CHECK_THROW(num /= zero, BigNumber::DivisionByZero);
	}
	BOOST_AUTO_TEST_CASE(DivisionByOne) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		long long int inum = dist(rng);
		BigNumber num(inum);
		BigNumber one(1);
		num /= one;
		BOOST_CHECK_EQUAL(static_cast<std::string>(num), std::to_string(inum));
	}
	BOOST_AUTO_TEST_CASE(ZeroDivision) {
		BigNumber num(745974537);
		BigNumber zero;
		BOOST_CHECK_EQUAL(zero / num, zero);
	}
	BOOST_AUTO_TEST_CASE(PositiveByPositive) {
		boost::random::uniform_int_distribution<long long int> dist(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i)
		{
			long long int lnum1 = dist(rng);
			long long int lnum2 = dist(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			num1 /= num2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(PositiveByNegative) {
		boost::random::uniform_int_distribution<long long int> dist1(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> dist2(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i)
		{
			long long int lnum1 = dist2(rng);
			long long int lnum2 = dist1(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			num1 /= num2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeByNegative) {
		boost::random::uniform_int_distribution<long long int> dist(LLONG_MIN, -1);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i)
		{
			long long int lnum1 = dist(rng);
			long long int lnum2 = dist(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			num1 /= num2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1), std::to_string(lnum1 / lnum2));
		}
	}
	BOOST_AUTO_TEST_CASE(NegativeByPositive) {
		boost::random::uniform_int_distribution<long long int> dist1(LLONG_MIN, -1);
		boost::random::uniform_int_distribution<long long int> dist2(1, LLONG_MAX);
		boost::random::mt19937 rng(std::time(0));
		for (int i = 0; i < 10; ++i)
		{
			long long int lnum1 = dist1(rng);
			long long int lnum2 = dist2(rng);
			BigNumber num1(lnum1);
			BigNumber num2(lnum2);
			num1 /= num2;
			BOOST_CHECK_EQUAL(static_cast<std::string>(num1), std::to_string(lnum1 / lnum2));
		}
	}
BOOST_AUTO_TEST_SUITE_END()
