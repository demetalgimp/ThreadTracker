#include <iostream>
#include <string>
#include <vector>
#include "Blob.hpp"
#include "UnitTests.hpp"

#define STRING_TEST_100_CHARS  "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//                                       1         2         3         4         5         6         7         8         9         0

namespace UnitTests {
	void unittests_Memory(void) {
	//--- Memory(void): mText(const_cast<uchar*>(EMPTY)), mLength(0) {}
		{
			Tools::Blob memory;
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
		}
	//--- Memory(const char *str, size_t bytes = 0, bool is_binary = false);
		{
			Tools::Blob memory((uchar*)nullptr);
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());

			Tools::Blob memory2("");
			UNITTEST_EQUALS((const char*)memory2.getText(), "");
			UNITTEST_EQUALS(memory2.getLength(), 0u);
			UNITTEST_ASSERT(memory2.getText() != nullptr);
			UNITTEST_ASSERT(memory2.isStrCompatible());

			Tools::Blob memory3("1234567890");
			UNITTEST_EQUALS((const char*)memory3.getText(), "1234567890");
			UNITTEST_EQUALS(memory3.getLength(), 10u);
			UNITTEST_ASSERT(memory3.getText() != nullptr);
			UNITTEST_ASSERT(memory3.isStrCompatible());

			Tools::Blob memory4("1234567890", 5);
			UNITTEST_EQUALS((const char*)memory4.getText(), "12345");
			UNITTEST_EQUALS(memory4.getLength(), 5u);
			UNITTEST_ASSERT(memory4.getText() != nullptr);
			UNITTEST_ASSERT(memory4.isStrCompatible());

			const uchar test_data[] = { '1', '2', '3', '4', '5', 0, 6, 7, 8, 9, 10 };
			Tools::Blob memory5(test_data, sizeof(test_data), true);
			UNITTEST_EQUALS(memcmp(memory5.getText(), test_data, sizeof(test_data)), 0);
			UNITTEST_EQUALS(memory5.getLength(), sizeof(test_data));
			UNITTEST_ASSERT(memory5.getText() != nullptr);
			UNITTEST_ASSERT(!memory5.isStrCompatible());
		}
	//--- Memory(const uchar *str, size_t bytes);
		{
			Tools::Blob memory((uchar*)nullptr, 0);
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());

			Tools::Blob memory2((const uchar*)"", 0);
			UNITTEST_EQUALS((const char*)memory2.getText(), "");
			UNITTEST_EQUALS(memory2.getLength(), 0u);
			UNITTEST_ASSERT(memory2.getText() != nullptr);
			UNITTEST_ASSERT(memory2.isStrCompatible());

			Tools::Blob memory3((const uchar*)"1234567890", 10);
			UNITTEST_EQUALS((const char*)memory3.getText(), "1234567890");
			UNITTEST_EQUALS(memory3.getLength(), 10u);
			UNITTEST_ASSERT(memory3.getText() != nullptr);
			UNITTEST_ASSERT(memory3.isStrCompatible());

			Tools::Blob memory4((const uchar*)"1234567890", 5);
			UNITTEST_EQUALS((const char*)memory4.getText(), "12345");
			UNITTEST_EQUALS(memory4.getLength(), 5u);
			UNITTEST_ASSERT(memory4.getText() != nullptr);
			UNITTEST_ASSERT(memory4.isStrCompatible());

			const uchar test_data[] = { '1', '2', '3', '4', '5', 0, 6, 7, 8, 9, 10 };
			Tools::Blob memory5(test_data, sizeof(test_data), true);
			UNITTEST_EQUALS(memcmp(memory5.getText(), test_data, sizeof(test_data)), 0);
			UNITTEST_EQUALS(memory5.getLength(), sizeof(test_data));
			UNITTEST_ASSERT(memory5.getText() != nullptr);
			UNITTEST_ASSERT(!memory5.isStrCompatible());
		}
	//--- Memory(const Memory& blob);
		{
			Tools::Blob memory("1234567890");
			Tools::Blob memory2(memory);
			UNITTEST_EQUALS((const char*)memory2.getText(), "1234567890");
			UNITTEST_EQUALS(memory2.getLength(), 10u);
			UNITTEST_ASSERT(memory2.getText() != nullptr);
			UNITTEST_ASSERT(memory2.isStrCompatible());

			Tools::Blob memory3;
			Tools::Blob memory4(memory3);
			UNITTEST_EQUALS((const char*)memory4.getText(), "");
			UNITTEST_EQUALS(memory4.getLength(), 0u);
			UNITTEST_ASSERT(memory4.getText() != nullptr);
			UNITTEST_ASSERT(!memory4.isStrCompatible());

			const uchar test_data[] = { '1', '2', '3', '4', '5', 0, 6, 7, 8, 9, 10 };
			Tools::Blob memory5(test_data, sizeof(test_data), true);
			Tools::Blob memory6(memory5);
			UNITTEST_EQUALS(memcmp(memory6.getText(), test_data, sizeof(test_data)), 0);
			UNITTEST_EQUALS(memory6.getLength(), sizeof(test_data));
			UNITTEST_ASSERT(memory6.getText() != nullptr);
			UNITTEST_ASSERT(!memory6.isStrCompatible());
		}
	//--- Memory& operator=(const char *str);
		{
			Tools::Blob memory;
			memory = nullptr;
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
			memory = "";
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
			memory = "123456";
			UNITTEST_EQUALS((const char*)memory.getText(), "123456");
			UNITTEST_EQUALS(memory.getLength(), 6u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
			memory = "12345678901234567890";
			UNITTEST_EQUALS((const char*)memory.getText(), "12345678901234567890");
			UNITTEST_EQUALS(memory.getLength(), 20u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
		}
	//--- Memory& operator=(const Memory& blob);
		{
			Tools::Blob memory;
			Tools::Blob memory2("1234567890");
			memory = memory2;
			UNITTEST_EQUALS((const char*)memory.getText(), "1234567890");
			UNITTEST_EQUALS(memory.getLength(), 10u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
			memory = Tools::Blob();
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
			const uchar test_data[] = { '1', '2', '3', '4', '5', 0, 6, 7, 8, 9, 10 };
			Tools::Blob memory3(test_data, sizeof(test_data), true);
			memory = memory3;
			UNITTEST_EQUALS(memcmp(memory.getText(), test_data, sizeof(test_data)), 0);
			UNITTEST_EQUALS(memory.getLength(), sizeof(test_data));
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
		}
	//--- Memory& operator=(const String& string);
		{
			Tools::Blob memory;
			Tools::String string("1234567890");
			memory = string;
			UNITTEST_EQUALS((const char*)memory.getText(), "1234567890");
			UNITTEST_EQUALS(memory.getLength(), 10u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
			memory = Tools::Blob();
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
			const uchar test_data[11] = { '1', '2', '3', '4', '5', 0, 6, 7, 8, 9, 10 };
			Tools::Blob memory3(test_data, sizeof(test_data), true);
			Tools::String string2((const char*)memory3.getText(), 0, memory3.getLength());
			memory = string2;
			UNITTEST_EQUALS(memcmp(memory.getText(), test_data, sizeof(test_data)), -1); // <-- Because of the embedded null byte
			UNITTEST_EQUALS(memory.getLength(), 5); // <-- Only the first 5 bytes are part of the string
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
		}
	//--- bool operator==(const char *str);
		{
			Tools::Blob memory;
			UNITTEST_ASSERT(memory == nullptr);
			UNITTEST_ASSERT(memory == "");
			UNITTEST_ASSERT(!(memory == "A"));
			Tools::Blob memory2("1234567890");
			UNITTEST_ASSERT(!(memory2 == nullptr));
			UNITTEST_ASSERT(!(memory2 == ""));
			UNITTEST_ASSERT(memory2 == "1234567890");
			UNITTEST_ASSERT(!(memory2 == "123456789"));
			UNITTEST_ASSERT(!(memory2 == "A"));
		}
	//--- bool operator==(const Memory& blob);
		{
			Tools::Blob memory;
			Tools::Blob memory2;
			UNITTEST_ASSERT(memory == memory2);
			Tools::Blob memory3("1234567890");
			UNITTEST_ASSERT(!(memory3 == memory));
			Tools::Blob memory4("1234567890");
			UNITTEST_ASSERT(memory3 == memory4);
			Tools::Blob memory5("123456789");
			UNITTEST_ASSERT(!(memory3 == memory5));
			Tools::Blob memory6("A");
			UNITTEST_ASSERT(!(memory3 == memory6));
			Tools::Blob memory7("B");
			UNITTEST_ASSERT(!(memory3 == memory7));
			Tools::Blob memory8("C");
			UNITTEST_ASSERT(!(memory3 == memory8));
		}
	//--- uchar operator[](uint index) const;
		{	Tools::Blob memory;
			UNITTEST_EQUALS(memory[0], 255); // <-- 255 == uchar(-1)
		}
		{	Tools::Blob memory("1234567890");
			UNITTEST_EQUALS(memory[0], '1');
			UNITTEST_EQUALS(memory[9], '0');
			UNITTEST_EQUALS(memory[10], 255); // <-- 255 == uchar(-1)
			UNITTEST_EQUALS(memory[100], 255); // <-- 255 == uchar(-1)
		}

	//--- void clear(void);
		{
			Tools::Blob memory("1234567890");
			UNITTEST_EQUALS((const char*)memory.getText(), "1234567890");
			UNITTEST_EQUALS(memory.getLength(), 10u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(memory.isStrCompatible());
			memory.clear();
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_EQUALS(memory.getLength(), 0u);
			UNITTEST_ASSERT(memory.getText() != nullptr);
			UNITTEST_ASSERT(!memory.isStrCompatible());
		}
	//--- bool isEmpty(void) const
		{
			Tools::Blob memory;
			UNITTEST_ASSERT(memory.isEmpty());
			memory = "1234567890";
			UNITTEST_ASSERT(!memory.isEmpty());
			memory.clear();
			UNITTEST_ASSERT(memory.isEmpty());
		}
	//--- size_t getLength(void) const
		{
			Tools::Blob memory;
			UNITTEST_EQUALS(memory.getLength(), 0u);
			memory = "1234567890";
			UNITTEST_EQUALS(memory.getLength(), 10u);
			memory.clear();
			UNITTEST_EQUALS(memory.getLength(), 0u);
		}
	//--- const uchar *getText(void) const
		{
			Tools::Blob memory;
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_ASSERT(memory.getText() != nullptr);
			memory = "1234567890";
			UNITTEST_EQUALS((const char*)memory.getText(), "1234567890");
			UNITTEST_ASSERT(memory.getText() != nullptr);
			memory.clear();
			UNITTEST_EQUALS((const char*)memory.getText(), "");
			UNITTEST_ASSERT(memory.getText() != nullptr);
		}
	//--- Tools::String Tools::Memory::hexDump(void) const; -------------------------------------------------------------------
		{	static const Tools::Blob sample_text(
					"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzA"
					"BCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789ab"
					"cdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLM"
					"NOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmn"
			);
			static const Tools::String expected_results(
					"00000: 30 31 32 33  34 35 36 37 | 38 39 61 62  63 64 65 66   0123456789abcdef  \n"
					"00010: 67 68 69 6A  6B 6C 6D 6E | 6F 70 71 72  73 74 75 76   ghijklmnopqrstuv  \n"
					"00020: 77 78 79 7A  41 42 43 44 | 45 46 47 48  49 4A 4B 4C   wxyzABCDEFGHIJKL  \n"
					"00030: 4D 4E 4F 50  51 52 53 54 | 55 56 57 58  59 5A 30 31   MNOPQRSTUVWXYZ01  \n"
					"00040: 32 33 34 35  36 37 38 39 | 61 62 63 64  65 66 67 68   23456789abcdefgh  \n"
					"00050: 69 6A 6B 6C  6D 6E 6F 70 | 71 72 73 74  75 76 77 78   ijklmnopqrstuvwx  \n"
					"00060: 79 7A 41 42  43 44 45 46 | 47 48 49 4A  4B 4C 4D 4E   yzABCDEFGHIJKLMN  \n"
					"00070: 4F 50 51 52  53 54 55 56 | 57 58 59 5A  30 31 32 33   OPQRSTUVWXYZ0123  \n"
					"00080: 34 35 36 37  38 39 61 62 | 63 64 65 66  67 68 69 6A   456789abcdefghij  \n"
					"00090: 6B 6C 6D 6E  6F 70 71 72 | 73 74 75 76  77 78 79 7A   klmnopqrstuvwxyz  \n"
					"000A0: 41 42 43 44  45 46 47 48 | 49 4A 4B 4C  4D 4E 4F 50   ABCDEFGHIJKLMNOP  \n"
					"000B0: 51 52 53 54  55 56 57 58 | 59 5A 30 31  32 33 34 35   QRSTUVWXYZ012345  \n"
					"000C0: 36 37 38 39  61 62 63 64 | 65 66 67 68  69 6A 6B 6C   6789abcdefghijkl  \n"
					"000D0: 6D 6E 6F 70  71 72 73 74 | 75 76 77 78  79 7A 41 42   mnopqrstuvwxyzAB  \n"
					"000E0: 43 44 45 46  47 48 49 4A | 4B 4C 4D 4E  4F 50 51 52   CDEFGHIJKLMNOPQR  \n"
					"000F0: 53 54 55 56  57 58 59 5A | 30 31 32 33  34 35 36 37   STUVWXYZ01234567  \n"
					"00100: 38 39 61 62  63 64 65 66 | 67 68 69 6A  6B 6C 6D 6E   89abcdefghijklmn  \n"
					"00110: 6F 70 71 72  73 74 75 76 | 77 78 79 7A  41 42 43 44   opqrstuvwxyzABCD  \n"
					"00120: 45 46 47 48  49 4A 4B 4C | 4D 4E 4F 50  51 52 53 54   EFGHIJKLMNOPQRST  \n"
					"00130: 55 56 57 58  59 5A 30 31 | 32 33 34 35  36 37 38 39   UVWXYZ0123456789  \n"
					"00140: 61 62 63 64  65 66 67 68 | 69 6A 6B 6C  6D 6E 6F 70   abcdefghijklmnop  \n"
					"00150: 71 72 73 74  75 76 77 78 | 79 7A 41 42  43 44 45 46   qrstuvwxyzABCDEF  \n"
					"00160: 47 48 49 4A  4B 4C 4D 4E | 4F 50 51 52  53 54 55 56   GHIJKLMNOPQRSTUV  \n"
					"00170: 57 58 59 5A  30 31 32 33 | 34 35 36 37  38 39 61 62   WXYZ0123456789ab  \n"
					"00180: 63 64 65 66  67 68 69 6A | 6B 6C 6D 6E                cdefghijklmn      \n"
			);
			UNITTEST_EQUALS(sample_text.hexDump(), expected_results);

			static const Tools::String full_ascii_expected_results(
					"00000: 01 02 03 04  05 06 07 08 | 09 0A 0B 0C  0D 0E 0F 10   ................  \n"
					"00010: 11 12 13 14  15 16 17 18 | 19 1A 1B 1C  1D 1E 1F 20   ...............   \n"
					"00020: 21 22 23 24  25 26 27 28 | 29 2A 2B 2C  2D 2E 2F 30   !\"#$%&'()*+,-./0  \n"
					"00030: 31 32 33 34  35 36 37 38 | 39 3A 3B 3C  3D 3E 3F 40   123456789:;<=>?@  \n"
					"00040: 41 42 43 44  45 46 47 48 | 49 4A 4B 4C  4D 4E 4F 50   ABCDEFGHIJKLMNOP  \n"
					"00050: 51 52 53 54  55 56 57 58 | 59 5A 5B 5C  5D 5E 5F 60   QRSTUVWXYZ[\\]^_`  \n"
					"00060: 61 62 63 64  65 66 67 68 | 69 6A 6B 6C  6D 6E 6F 70   abcdefghijklmnop  \n"
					"00070: 71 72 73 74  75 76 77 78 | 79 7A 7B 7C  7D 7E 7F 80   qrstuvwxyz{|}~..  \n"
					"00080: 81 82 83 84  85 86 87 88 | 89 8A 8B 8C  8D 8E 8F 90   ................  \n"
					"00090: 91 92 93 94  95 96 97 98 | 99 9A 9B 9C  9D 9E 9F A0   ................  \n"
					"000A0: A1 A2 A3 A4  A5 A6 A7 A8 | A9 AA AB AC  AD AE AF B0   ................  \n"
					"000B0: B1 B2 B3 B4  B5 B6 B7 B8 | B9 BA BB BC  BD BE BF C0   ................  \n"
					"000C0: C1 C2 C3 C4  C5 C6 C7 C8 | C9 CA CB CC  CD CE CF D0   ................  \n"
					"000D0: D1 D2 D3 D4  D5 D6 D7 D8 | D9 DA DB DC  DD DE DF E0   ................  \n"
					"000E0: E1 E2 E3 E4  E5 E6 E7 E8 | E9 EA EB EC  ED EE EF F0   ................  \n"
					"000F0: F1 F2 F3 F4  F5 F6 F7 F8 | F9 FA FB FC  FD FE FF      ...............   \n"
				);
			char tmps[256];
			for ( uint i = 0; i < sizeof(tmps) - 1; i++ ) {
				tmps[i] = i + 1;
			}
			tmps[sizeof(tmps) - 1] = 0;
			UNITTEST_EQUALS(Tools::String(tmps).hexDump(), full_ascii_expected_results);
		}

	//--- String toString(void) const;
		{}

	}
    void unittests_String(void) {
	//--- static int my_strcmp(const unsigned char *str1, const unsigned char *str2);
		{
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"abc", (const unsigned char*)"abc") == 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"abc", (const unsigned char*)"abcd") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"abcd", (const unsigned char*)"abc") > 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"", (const unsigned char*)"") == 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"", (const unsigned char*)"a") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"a", (const unsigned char*)"") > 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)nullptr, (const unsigned char*)nullptr) == 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)nullptr, (const unsigned char*)"a") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcmp((const unsigned char*)"a", (const unsigned char*)nullptr) > 0);
		}
	//--- static int my_strcasecmp(const unsigned char *str1, const unsigned char *str2);
		{
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"abc", (const unsigned char*)"abc") == 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"abc", (const unsigned char*)"ABCD") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"ABCD", (const unsigned char*)"abc") > 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"", (const unsigned char*)"") == 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"", (const unsigned char*)"A") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"a", (const unsigned char*)"") > 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)nullptr, (const unsigned char*)nullptr) == 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)nullptr, (const unsigned char*)"a") < 0);
			UNITTEST_ASSERT(Tools::String::my_strcasecmp((const unsigned char*)"a", (const unsigned char*)nullptr) > 0);
		}
	//--- static const unsigned char *my_strstr(const unsigned char *str, const unsigned char *sub);
		{
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)"is a test") == (const unsigned char*)"is a test");
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)"was a test") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)"this is a test") == (const unsigned char*)"this is a test");
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)"this is a test ") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)"") == (const unsigned char*)"this is a test");
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"this is a test", (const unsigned char*)nullptr) == (const unsigned char*)"this is a test");
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"", (const unsigned char*)nullptr) == (const unsigned char*)"");
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)nullptr, (const unsigned char*)nullptr) == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)nullptr, (const unsigned char*)"") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strstr((const unsigned char*)"", (const unsigned char*)"") == (const unsigned char*)"");
		}
	//--- static const unsigned char *my_strcasestr(const unsigned char *str, const unsigned char *sub);
		{
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)"is a test") == (const unsigned char*)"Is A Test");
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)"was a test") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)"this is a test") == (const unsigned char*)"This Is A Test");
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)"this is a test ") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)"") == (const unsigned char*)"This Is A Test");
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"This Is A Test", (const unsigned char*)nullptr) == (const unsigned char*)"This Is A Test");
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"", (const unsigned char*)nullptr) == (const unsigned char*)"");
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)nullptr, (const unsigned char*)nullptr) == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)nullptr, (const unsigned char*)"") == nullptr);
			UNITTEST_ASSERT(Tools::String::my_strcasestr((const unsigned char*)"", (const unsigned char*)"") == (const unsigned char*)"");
		}
	//--- static bool strsub(const char *str, const char *sub);
		{	UNITTEST_ASSERT(!Tools::String::strsub("this is a test", "is a"));
			UNITTEST_ASSERT(!Tools::String::strsub("this is a test", "was a"));
			UNITTEST_ASSERT(Tools::String::strsub("this is a test", "this is a test"));
			UNITTEST_ASSERT(!Tools::String::strsub("this is a test", "this is a test "));
			UNITTEST_ASSERT(Tools::String::strsub("this is a test", ""));
			UNITTEST_ASSERT(Tools::String::strsub("this is a test", nullptr));
			UNITTEST_ASSERT(Tools::String::strsub("", nullptr));
			UNITTEST_ASSERT(Tools::String::strsub(nullptr, nullptr));
			UNITTEST_ASSERT(Tools::String::strsub(nullptr, ""));
			UNITTEST_ASSERT(Tools::String::strsub("", ""));
		}
	//--- static bool strcasesub(const char *str, const char *sub);
		{
			UNITTEST_ASSERT(!Tools::String::strcasesub("This Is A Test", "is a"));
			UNITTEST_ASSERT(!Tools::String::strcasesub("This Is A Test", "was a"));
			UNITTEST_ASSERT(Tools::String::strcasesub("This Is A Test", "this is a test"));
			UNITTEST_ASSERT(!Tools::String::strcasesub("This Is A Test", "this is a test "));
			UNITTEST_ASSERT(Tools::String::strcasesub("This Is A Test", ""));
			UNITTEST_ASSERT(Tools::String::strcasesub("This Is A Test", nullptr));
			UNITTEST_ASSERT(Tools::String::strcasesub("", nullptr));
			UNITTEST_ASSERT(Tools::String::strcasesub(nullptr, nullptr));
			UNITTEST_ASSERT(Tools::String::strcasesub(nullptr, ""));
			UNITTEST_ASSERT(Tools::String::strcasesub("", ""));
		}
	//--- String(void): Memory(), mBufferSize(BUFFER_SIZE)
		{
			Tools::String string;
			UNITTEST_ASSERT(Tools::String() != nullptr);
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}

	//--- Tools::String::Tools::String(const char *str = nullptr, size_t count = 0); --------------------------------------
		{	Tools::String string;
			UNITTEST_ASSERT(Tools::String() != nullptr);
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}
		{	Tools::String string(nullptr);
			UNITTEST_ASSERT(Tools::String() != nullptr);
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}
		{	Tools::String string("");
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}
		{	Tools::String string("A");
			UNITTEST_EQUALS(string.getLength(), 1u);
			UNITTEST_EQUALS(string.getBufferSize(), 1u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "A"), 0);
		}
		{	Tools::String string("01234567890123456789012345678901234567890123456789");
			UNITTEST_EQUALS(string.getLength(), 50u);
			UNITTEST_EQUALS(string.getBufferSize(), 50u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "01234567890123456789012345678901234567890123456789"), 0);
		}
		{	Tools::String string("01234567890123456789012345678901234567890123456789", 30);
			UNITTEST_EQUALS(string.getLength(), 20u);
			UNITTEST_EQUALS(string.getBufferSize(), 20u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "01234567890123456789"), 0);
		}
		{	Tools::String string(STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string.getLength(), 100u);
			UNITTEST_EQUALS(string.getBufferSize(), 100u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), STRING_TEST_100_CHARS), 0);
		}
		{	Tools::String string(STRING_TEST_100_CHARS STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string.getLength(), 200u);
			UNITTEST_EQUALS(string.getBufferSize(), 200u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), STRING_TEST_100_CHARS STRING_TEST_100_CHARS), 0);
		}
		{	Tools::String string(STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string.getLength(), 300u);
			UNITTEST_EQUALS(string.getBufferSize(), 300u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS), 0);
		}
		{	Tools::String string(STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string.getLength(), 400u);
			UNITTEST_EQUALS(string.getBufferSize(), 400u);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS STRING_TEST_100_CHARS), 0);
		}

	//---	Tools::String::Tools::String(const Tools::String& string); -------------------------------------------------------------
		{	Tools::String string("012345678901234567890123456789");
			Tools::String new_string(string);
			UNITTEST_EQUALS(new_string.getLength(), 30u);
			UNITTEST_EQUALS(new_string.getBufferSize(), 30u);
			UNITTEST_EQUALS(strcmp((const char*)new_string.getText(), "012345678901234567890123456789"), 0);
		}
		{	Tools::String string;
			Tools::String new_string(string);
			UNITTEST_EQUALS(new_string.getLength(), 0u);
			UNITTEST_EQUALS(new_string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)new_string.getText(), ""), 0);
		}

	//---	bool Tools::String::operator==(const char *str) const; ---------------------------------------------------
	//---	bool Tools::String::operator==(const Tools::String& string) const; ----------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String() == "");
			UNITTEST_ASSERT(Tools::String() == Tools::String());
		}
		{
			UNITTEST_ASSERT(Tools::String("1234567890") == "1234567890");
			UNITTEST_ASSERT(Tools::String("123456") + "7890" == Tools::String("1234567890"));
			UNITTEST_ASSERT(Tools::String("1234567890") == "1234567890");
			UNITTEST_ASSERT(Tools::String("123456") + "7890" == Tools::String("1234567890"));
		}

	//---	bool Tools::String::operator!=(const Tools::String& string) const; ----------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("1234567890") != "");
			UNITTEST_ASSERT(Tools::String("1234567890") != "1");
			UNITTEST_ASSERT(Tools::String("1234567890") != "123456789");
			UNITTEST_ASSERT(Tools::String("1234567890") != Tools::String(""));
			UNITTEST_ASSERT(Tools::String("1234567890") != Tools::String("1"));
			UNITTEST_ASSERT(Tools::String("1234567890") != Tools::String("123456789"));
		}

	//---	bool Tools::String::operator>=(const char *str) const;
		{
			UNITTEST_ASSERT(Tools::String("a") >= "");
			UNITTEST_ASSERT(Tools::String("a") >= nullptr);
			UNITTEST_ASSERT(Tools::String("ab") >= "a");
			UNITTEST_ASSERT(Tools::String() >= "");
			UNITTEST_ASSERT(Tools::String() >= nullptr);
			UNITTEST_ASSERT(Tools::String("a") >= "a");
			UNITTEST_ASSERT(Tools::String("ab") >= "ab");
		}

	//---	bool Tools::String::operator>=(const Tools::String& string) const;
		{
			UNITTEST_ASSERT(Tools::String("a") >= Tools::String());
			UNITTEST_ASSERT(Tools::String("ab") >= Tools::String("a"));
			UNITTEST_ASSERT(Tools::String() >= Tools::String());
			UNITTEST_ASSERT(Tools::String("a") >= Tools::String("a"));
			UNITTEST_ASSERT(Tools::String("ab") >= Tools::String("ab"));
		}

	//---	bool Tools::String::operator<=(const char *str) const;
		{
			UNITTEST_ASSERT(Tools::String() <= "a");
			UNITTEST_ASSERT(Tools::String("a") <= "ab");
			UNITTEST_ASSERT(Tools::String() <= "");
			// UNITTEST_ASSERT(Tools::String() <= nullptr);
			UNITTEST_ASSERT(Tools::String("a") <= "a");
			UNITTEST_ASSERT(Tools::String("ab") <= "ab");
		}

	//---	bool Tools::String::operator<=(const Tools::String& string) const;
		{
			UNITTEST_ASSERT(Tools::String() <= Tools::String("a"));
			UNITTEST_ASSERT(Tools::String("a") <= Tools::String("ab"));
			UNITTEST_ASSERT(Tools::String() <= Tools::String());
			UNITTEST_ASSERT(Tools::String("a") <= Tools::String("a"));
			UNITTEST_ASSERT(Tools::String("ab") <= Tools::String("ab"));
		}

	//---	bool Tools::String::operator>(const char *str) const;
		{
			UNITTEST_ASSERT(Tools::String("a") > "");
			UNITTEST_ASSERT(Tools::String("a") > nullptr);
			UNITTEST_ASSERT(Tools::String("ab") > "a");
		}

	//---	bool Tools::String::operator>(const Tools::String& string) const;
		{
			UNITTEST_ASSERT(Tools::String("a") > Tools::String());
			UNITTEST_ASSERT(Tools::String("a") > Tools::String(nullptr));
			UNITTEST_ASSERT(Tools::String("ab") > Tools::String("a"));
		}

	//---	bool Tools::String::operator<(const char *str) const;
		{
			UNITTEST_ASSERT(Tools::String() < "a");
			UNITTEST_ASSERT(Tools::String("a") < "ab");
		}

	//---	bool Tools::String::operator<(const Tools::String& string) const;
		{
			UNITTEST_ASSERT(Tools::String() < Tools::String("a"));
			UNITTEST_ASSERT(Tools::String("a") < Tools::String("ab"));
		}

	//---	Tools::String& Tools::String::operator=(const char *str);
		{	Tools::String string;
			string = nullptr;
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), ""), 0);
			string = "123456";
			UNITTEST_EQUALS(string.getLength(), 6u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "123456"), 0);
			string = "123";
			UNITTEST_EQUALS(string.getLength(), 3u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "123"), 0);
		}
		{	Tools::String string("this is a test");
			string = nullptr;
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), ""), 0);

			string = "123456";
			UNITTEST_EQUALS(string.getLength(), 6u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "123456"), 0);

			string = "12345678901234567890";
			UNITTEST_EQUALS(string.getLength(), 20u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string.getText(), "12345678901234567890"), 0);
		}

	//---	Tools::String& Tools::String::operator=(const Tools::String& string); ------------------------------------------------------
		{	Tools::String string;
			string = Tools::String();
			UNITTEST_EQUALS(string, "");
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string = Tools::String("this is a test of the emergency");
			UNITTEST_EQUALS(string, "this is a test of the emergency");
			UNITTEST_EQUALS(string.getLength(), 31u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}

	//---	Tools::String& Tools::String::operator+=(const char *str); ----------------------------------------------------------
		{	Tools::String string;
			string += nullptr;
			UNITTEST_EQUALS(string, "");
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}
		{	Tools::String string;
			string += "";
			UNITTEST_EQUALS(string, "");
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
		}
		{	Tools::String string;
			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 100u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 200u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 300u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 400u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 500u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 600u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 700u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 800u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);

			string += STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 900u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 4u + 150u);
		}

	//--- String& String::operator+=(const String& string)
		{	Tools::String string;
			const Tools::String const_STRING_TEST_100_CHARS(STRING_TEST_100_CHARS);
			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 100u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 200u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 300u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 400u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 500u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 50u);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 600u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 700u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);

			string += const_STRING_TEST_100_CHARS;
			UNITTEST_EQUALS(string,
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
					STRING_TEST_100_CHARS
				);
			UNITTEST_EQUALS(string.getLength(), 800u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 3u + 100u);
		}

	//---	Tools::String& Tools::String::operator+=(const Tools::String& string); -----------------------------------------------------
		{	Tools::String string;
			string += Tools::String();
			UNITTEST_EQUALS(string, "");
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string += Tools::String(STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string, Tools::String(STRING_TEST_100_CHARS));
			UNITTEST_EQUALS(string.getLength(), 100u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);

			string += Tools::String(STRING_TEST_100_CHARS);
			UNITTEST_EQUALS(string,
							Tools::String(STRING_TEST_100_CHARS
							STRING_TEST_100_CHARS)
						);
		// note: this once generated an segfault error
			string += Tools::String("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw");
			UNITTEST_EQUALS(string,
							 Tools::String(STRING_TEST_100_CHARS
							 STRING_TEST_100_CHARS
							 "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvw")
						);
			Tools::String s;
			UNITTEST_EQUALS(string.getLength(), 301u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE * 2u + 51u);
		}
//---	Tools::String Tools::String::operator+(const char *str) const; --------------------------------------------------
		{	Tools::String string;
			Tools::String string_result;
			string_result = string + nullptr;
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), ""), 0);
			string_result = string + "";
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), ""), 0);
		}
		{	Tools::String string("123456");
			Tools::String string_result;
			string_result = string + nullptr;
			UNITTEST_EQUALS(string.getLength(), 6u);
			UNITTEST_EQUALS(string.getBufferSize(), 6u);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "123456"), 0);
			string_result = string + "";
			UNITTEST_EQUALS(string.getLength(), 6u);
			UNITTEST_EQUALS(string.getBufferSize(), 6u);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "123456"), 0);
		}
		{	Tools::String string("123456");
			Tools::String string_result;
			string_result = string + "7890";
			UNITTEST_EQUALS(string_result.getLength(), 10u);
			UNITTEST_EQUALS(string_result.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "1234567890"), 0);
			string_result = string + "7890" + "abcdefghij";
			UNITTEST_EQUALS(string_result.getLength(), 20u);
			UNITTEST_EQUALS(string_result.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "1234567890abcdefghij"), 0);
		}

	//---	Tools::String Tools::String::operator+(const Tools::String& string) const; ---------------------------------------------
		{	Tools::String string;
			Tools::String string_result;
			string_result = string + Tools::String();
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), ""), 0);
		}
		{	Tools::String string("123456");
			Tools::String string_result;
			string_result = string + Tools::String();
			UNITTEST_EQUALS(string.getLength(), 6u);
			UNITTEST_EQUALS(string.getBufferSize(), 6u);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "123456"), 0);
		}
		{	Tools::String string("123456");
			Tools::String string_result;
			string_result = string + Tools::String("7890");
			UNITTEST_EQUALS(string_result.getLength(), 10u);
			UNITTEST_EQUALS(string_result.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "1234567890"), 0);
			string_result = string + Tools::String("7890") + Tools::String("abcdefghij");
			UNITTEST_EQUALS(string_result.getLength(), 20u);
			UNITTEST_EQUALS(string_result.getBufferSize(), Tools::String::BUFFER_SIZE);
			UNITTEST_EQUALS(strcmp((const char*)string_result.getText(), "1234567890abcdefghij"), 0);
		}

	//---	friend Tools::String Tools::String::operator+(const char* str, const Tools::String& string); -------------------------------
		{
			UNITTEST_EQUALS("" + Tools::String("string"), "string");
			UNITTEST_EQUALS("test" + Tools::String(""), "test");
			UNITTEST_EQUALS("" + Tools::String(""), "");
			UNITTEST_EQUALS("test" + Tools::String("string"), "teststring");
		}

	//---	bool Tools::String::startsWith(const char * sub); -----------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").startsWith(""));
			UNITTEST_ASSERT(Tools::String("abc").startsWith(""));
			UNITTEST_ASSERT(Tools::String("abc").startsWith("a"));
			UNITTEST_ASSERT(Tools::String("abcdef").startsWith("abc"));
			UNITTEST_ASSERT(!Tools::String("abcdef").startsWith("bc"));
		}

	//---	bool Tools::String::startsWith(const Tools::String& sub); -----------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").startsWith(Tools::String("")));
			UNITTEST_ASSERT(Tools::String("abc").startsWith(Tools::String("")));
			UNITTEST_ASSERT(Tools::String("abc").startsWith(Tools::String("a")));
			UNITTEST_ASSERT(Tools::String("abcdef").startsWith(Tools::String("abc")));
			UNITTEST_ASSERT(!Tools::String("abcdef").startsWith(Tools::String("bc")));
		}

	//---	bool Tools::String::contains(const char* sub); -------------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").contains(""));
			UNITTEST_ASSERT(Tools::String("abc").contains(""));
			UNITTEST_ASSERT(Tools::String("abc").contains("a"));
			UNITTEST_ASSERT(Tools::String("abc").contains("b"));
			UNITTEST_ASSERT(Tools::String("abcdef").contains("abc"));
			UNITTEST_ASSERT(Tools::String("abcdef").contains("bc"));
			UNITTEST_ASSERT(!Tools::String("abcdef").contains("bcb"));
			UNITTEST_ASSERT(Tools::String("abcdef").contains("def"));
			UNITTEST_ASSERT(!Tools::String("abcdef").contains("defg"));
		}

	//---	bool Tools::String::contains(const Tools::String& sub); -------------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").contains(Tools::String("")));
			UNITTEST_ASSERT(Tools::String("abc").contains(Tools::String("")));
			UNITTEST_ASSERT(Tools::String("abc").contains(Tools::String("a")));
			UNITTEST_ASSERT(Tools::String("abc").contains(Tools::String("b")));
			UNITTEST_ASSERT(Tools::String("abcdef").contains(Tools::String("abc")));
			UNITTEST_ASSERT(Tools::String("abcdef").contains(Tools::String("bc")));
			UNITTEST_ASSERT(!Tools::String("abcdef").contains(Tools::String("bcb")));
			UNITTEST_ASSERT(Tools::String("abcdef").contains(Tools::String("def")));
			UNITTEST_ASSERT(!Tools::String("abcdef").contains(Tools::String("defg")));
		}

	//---	Tools::String& Tools::String::clear(void); -----------------------------------------------------------------------------
		{
            Tools::String string("");
            string.clear();
			UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String("").getBufferSize());

            string = "abc";
            string.clear();
            UNITTEST_EQUALS(string.getLength(), 0u);
			UNITTEST_EQUALS(string.getBufferSize(), Tools::String("").getBufferSize());
		}

	//---	Tools::String Tools::String::trim(void) const;
		{
			UNITTEST_EQUALS(Tools::String("").trim(), "");
			UNITTEST_EQUALS(Tools::String(" ").trim(), "");
			UNITTEST_EQUALS(Tools::String(" \n\t").trim(), "");
			UNITTEST_EQUALS(Tools::String("    \n\t").trim(), "");
			UNITTEST_EQUALS(Tools::String("abc").trim(), "abc");
			UNITTEST_EQUALS(Tools::String(" abc").trim(), "abc");
			UNITTEST_EQUALS(Tools::String(" \n\tabc").trim(), "abc");
			UNITTEST_EQUALS(Tools::String("abc ").trim(), "abc");
			UNITTEST_EQUALS(Tools::String("abc \n\t").trim(), "abc");
			UNITTEST_EQUALS(Tools::String(" \n\tabc \n\t").trim(), "abc");
			UNITTEST_EQUALS(Tools::String(" \n\tabc \n\t").trim(), "abc");
			UNITTEST_EQUALS(Tools::String("ab c").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String(" ab c").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String(" \t\nab c").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String("ab c ").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String("ab c \t\n").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String(" ab c ").trim(), "ab c");
			UNITTEST_EQUALS(Tools::String(" \f\n\r\t\vab \n\tc \f\n\r\t\v").trim(), "ab \n\tc");
		}
	//--- String trimRight(void) const;
		{
			UNITTEST_EQUALS(Tools::String("").trimRight(), "");
			UNITTEST_EQUALS(Tools::String(" ").trimRight(), "");
			UNITTEST_EQUALS(Tools::String("  \f\n\r\t\v").trimRight(), "");
			UNITTEST_EQUALS(Tools::String("  \f\n\r\t\v").trimRight(), "");
			UNITTEST_EQUALS(Tools::String(" \f\n\r\t\vab \n\tc \f\n\r\t\v").trimRight(), " \f\n\r\t\vab \n\tc");
		}
	//--- String trimLeft(void) const;
		{
			UNITTEST_EQUALS(Tools::String("").trimLeft(), "");
			UNITTEST_EQUALS(Tools::String(" ").trimLeft(), "");
			UNITTEST_EQUALS(Tools::String("  \f\n\r\t\v").trimLeft(), "");
			UNITTEST_EQUALS(Tools::String(" \f\n\r\t\vab \n\tc \f\n\r\t\v").trimLeft(), "ab \n\tc \f\n\r\t\v");
		}
	//---	std::vector<Tools::String> Tools::String::split(const Tools::String& needle);
		{	std::vector<Tools::String> strings;
            uint cntr = 0;
			Tools::String test="This is a test of the emergency broadcast system. This is only a test.";
			strings = test.split('x');
			UNITTEST_EQUALS(strings.size(), 1u);
			UNITTEST_EQUALS(strings[cntr++], test);
			UNITTEST_EQUALS(strings.size(), cntr);

            cntr = 0;
			strings = test.split('e');
			UNITTEST_EQUALS(strings[cntr++], Tools::String("This is a t"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("st of th"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String(" "));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("m"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("rg"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("ncy broadcast syst"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("m. This is only a t"));
            UNITTEST_EQUALS(strings[cntr++], Tools::String("st."));
			UNITTEST_EQUALS(strings.size(), cntr);

            cntr = 0;
			strings = test.split('.');
			UNITTEST_EQUALS(strings[cntr++], Tools::String("This is a test of the emergency broadcast system"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String(" This is only a test"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String(""));
			UNITTEST_EQUALS(strings.size(), cntr);

            cntr = 0;
			strings = test.split('T');
			UNITTEST_EQUALS(strings[cntr++], Tools::String(""));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("his is a test of the emergency broadcast system. "));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("his is only a test."));
			UNITTEST_EQUALS(strings.size(), cntr);

            cntr = 0;
			strings = test.split(' ');
			UNITTEST_EQUALS(strings[cntr++], Tools::String("This"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("is"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("a"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("test"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("of"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("the"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("emergency"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("broadcast"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("system."));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("This"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("is"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("only"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("a"));
			UNITTEST_EQUALS(strings[cntr++], Tools::String("test."));
			UNITTEST_EQUALS(strings.size(), cntr);
		}

	//---	bool Tools::String::isEmpty(void) const; ---------------------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").isEmpty());
			UNITTEST_ASSERT(!Tools::String("abc").isEmpty());
		}

	//---	uint Tools::String::getLength(void) const; -------------------------------------------------------------------
		{
			UNITTEST_EQUALS(Tools::String("").getLength(), 0u);
			UNITTEST_EQUALS(Tools::String("a").getLength(), 1u);
			UNITTEST_EQUALS(Tools::String("1234567890").getLength(), 10u);
		}

	//---	const char* Tools::String::getChars(void) const; -------------------------------------------------------------
		{
			UNITTEST_EQUALS(strcmp((const char*)Tools::String("").getText(), ""), 0);
			UNITTEST_EQUALS(strcmp((const char*)Tools::String("a").getText(), "a"), 0);
			UNITTEST_EQUALS(strcmp((const char*)Tools::String("1234567890").getText(), "1234567890"), 0);
		}

	//---	void Tools::String::getChars(bool ignore); -------------------------------------------------------------
		{	Tools::String string("abcdefg");
			UNITTEST_ASSERT(string == "abcdefg");
			UNITTEST_ASSERT(string != "ABCDEFG");
			UNITTEST_ASSERT(string != "aBcDefg");
			UNITTEST_ASSERT(string.startsWith("abc"));
			UNITTEST_ASSERT(!string.startsWith("ABC"));
			UNITTEST_ASSERT(!string.startsWith("aBc"));
			UNITTEST_ASSERT(!string.startsWith("def"));
			UNITTEST_ASSERT(!string.startsWith("DEF"));
			UNITTEST_ASSERT(!string.startsWith("Def"));
			UNITTEST_ASSERT(string.contains("def"));
			UNITTEST_ASSERT(!string.contains("DEF"));
			UNITTEST_ASSERT(!string.contains("Def"));

			string.setCaseCompare(true);
			UNITTEST_ASSERT(string == "abcdefg");
			UNITTEST_ASSERT(string == "ABCDEFG");
			UNITTEST_ASSERT(string == "aBcDefg");
			UNITTEST_ASSERT(string.startsWith("abc"));
			UNITTEST_ASSERT(string.startsWith("ABC"));
			UNITTEST_ASSERT(string.startsWith("aBc"));
			UNITTEST_ASSERT(string.contains("abc"));
			UNITTEST_ASSERT(string.contains("ABC"));
			UNITTEST_ASSERT(string.contains("aBc"));
			UNITTEST_ASSERT(string.contains("def"));
			UNITTEST_ASSERT(string.contains("DEF"));
			UNITTEST_ASSERT(string.contains("Def"));
		}
	//---	static bool Tools::String::strsub(const char *str, const char *sub); -----------------------------------------
		{
			UNITTEST_ASSERT( Tools::String::strsub((const char *)"",    (const char *)""));
			UNITTEST_ASSERT( Tools::String::strsub((const char *)"abc", (const char *)""));
			UNITTEST_ASSERT( Tools::String::strsub((const char *)"abc", (const char *)"a"));
			UNITTEST_ASSERT( Tools::String::strsub((const char *)"abc", (const char *)"abc"));
			UNITTEST_ASSERT(!Tools::String::strsub((const char *)"abc", (const char *)"abcd"));
			UNITTEST_ASSERT(!Tools::String::strsub((const char *)"abc", (const char *)"bc"));
			UNITTEST_ASSERT(!Tools::String::strsub((const char *)"abc", (const char *)"A"));
			UNITTEST_ASSERT(!Tools::String::strsub((const char *)"abc", (const char *)"ABc"));
		}

	//---	static Tools::String Tools::String::toString(long long number, uint base = 10); -------------------------------------
		{
			UNITTEST_EQUALS(Tools::String::toString(1000), "1000");
			UNITTEST_EQUALS(Tools::String::toString(-1000), "-1000");
			UNITTEST_EQUALS(Tools::String::toString(0), "0");
			UNITTEST_EQUALS(Tools::String::toString(0x0, 16), "0");
			UNITTEST_EQUALS(Tools::String::toString(0xFFFF, 16), "FFFF");
			UNITTEST_EQUALS(Tools::String::toString(0x0123456789ABCDEF, 16), "123456789ABCDEF");
			UNITTEST_EQUALS(Tools::String::toString(01234567, 8), "1234567");
			UNITTEST_EQUALS(Tools::String::toString(0x4321, 2), "100001100100001");
		}

	//---	static Tools::String Tools::String::formatString(const Tools::String& fmt, ...); -------------------------------------------
		{	Tools::String string = Tools::String::formatString("this %s %d", "is a test", 80);
			UNITTEST_EQUALS(string, "this is a test 80");
		}

	//---   Tools::String encode(void) const; ------------------------------------------------------------------------
		{
			Tools::String string = "";
			UNITTEST_EQUALS(string.encode(), "");
			string = "abcd";
			UNITTEST_EQUALS(string.encode(), "abcd");
			string = "\a\b\f\n\r\t\v";
			UNITTEST_EQUALS(string.encode(), "\\a\\b\\f\\n\\r\\t\\v");
			char tmps[256 + 1];
			for ( uint i = 0; i < sizeof(tmps); i++ ) {
				tmps[i] = i;
			}
			tmps[0] = ' ';
			tmps[sizeof(tmps) - 1] = 0;
			const char *expect =
		//	 01   2   3   4   5   6   7 8 9 A B C D E   F
			" \\x01\\x02\\x03\\x04\\x05\\x06\\a\\b\\t\\n\\v\\f\\r\\x0E\\x0F"
			 "\\x10\\x11\\x12\\x13\\x14\\x15\\x16\\x17\\x18\\x19\\x1A\\x1B\\x1C\\x1D\\x1E\\x1F"
		//	 0123456789ABCDEF
			" !\"#$%&'()*+,-./"
			"0123456789:;<=>?"
			"@ABCDEFGHIJKLMNO"
			"PQRSTUVWXYZ[\\]^_"
			"`abcdefghijklmno"
			"pqrstuvwxyz{|}~\\x7F"
			"\\x80\\x81\\x82\\x83\\x84\\x85\\x86\\x87\\x88\\x89\\x8A\\x8B\\x8C\\x8D\\x8E\\x8F"
			"\\x90\\x91\\x92\\x93\\x94\\x95\\x96\\x97\\x98\\x99\\x9A\\x9B\\x9C\\x9D\\x9E\\x9F"
			"\\xA0\\xA1\\xA2\\xA3\\xA4\\xA5\\xA6\\xA7\\xA8\\xA9\\xAA\\xAB\\xAC\\xAD\\xAE\\xAF"
			"\\xB0\\xB1\\xB2\\xB3\\xB4\\xB5\\xB6\\xB7\\xB8\\xB9\\xBA\\xBB\\xBC\\xBD\\xBE\\xBF"
			"\\xC0\\xC1\\xC2\\xC3\\xC4\\xC5\\xC6\\xC7\\xC8\\xC9\\xCA\\xCB\\xCC\\xCD\\xCE\\xCF"
			"\\xD0\\xD1\\xD2\\xD3\\xD4\\xD5\\xD6\\xD7\\xD8\\xD9\\xDA\\xDB\\xDC\\xDD\\xDE\\xDF"
			"\\xE0\\xE1\\xE2\\xE3\\xE4\\xE5\\xE6\\xE7\\xE8\\xE9\\xEA\\xEB\\xEC\\xED\\xEE\\xEF"
			"\\xF0\\xF1\\xF2\\xF3\\xF4\\xF5\\xF6\\xF7\\xF8\\xF9\\xFA\\xFB\\xFC\\xFD\\xFE\\xFF";
			UNITTEST_EQUALS(Tools::String(tmps).encode(), expect);
		}

	//---	static Tools::String Tools::String::wideCharToString(ushort wchar); -------------------------------------------------
		{
			UNITTEST_EQUALS(Tools::String::wideCharToString('a'),    "a");
			UNITTEST_EQUALS(Tools::String::wideCharToString('ab'),   "ab");
			UNITTEST_EQUALS(Tools::String::wideCharToString('abc'),  "abc");
			UNITTEST_EQUALS(Tools::String::wideCharToString('abcd'), "abcd");
		}

	// //--- friend  std::ostream& operator<<(std::ostream& stream, const Tools::String& string); ---------------------------
	// 	// {	std::ostringstream output;
	// 	// 	Tools::String text("this is a test");
	// 	// 	output << text;
	// 	// 	UNITTEST_ASSERT(output.str(), text);
	// 	// }

	// //---	Tools::String Tools::String::serialize(void) const; ------------------------------------------------------------------
	// 	// {
	// 	// 	UNITTEST_EQUALS(Tools::String("").serialize(),
	// 	// 			"{ \"Tools::String\": "
	// 	// 				"{"
	// 	// 					"\"buffer\": \"\", "
	// 	// 					"\"length\": \"0\", "
	// 	// 					"\"size\": \"250\", "
	// 	// 					"\"compare_fn\": \"strcmp()\", "
	// 	// 					"\"strsub_fn\": \"strsub()\", "
	// 	// 					"\"strstr_fn\": \"strstr()\""
	// 	// 				"}"
	// 	// 			"}");
	// 	// 	UNITTEST_EQUALS((Tools::String("") + "1234567890").serialize(),
	// 	// 			"{ \"Tools::String\": "
	// 	// 				"{"
	// 	// 					"\"buffer\": \"1234567890\", "
	// 	// 					"\"length\": \"10\", "
	// 	// 					"\"size\": \"10\", "
	// 	// 					"\"compare_fn\": \"strcmp()\", "
	// 	// 					"\"strsub_fn\": \"strsub()\", "
	// 	// 					"\"strstr_fn\": \"strstr()\""
	// 	// 				"}"
	// 	// 			"}");
	// 	// 	UNITTEST_EQUALS(Tools::String("abc").serialize(),
	// 	// 			"{ \"Tools::String\": "
	// 	// 				"{"
	// 	// 					"\"buffer\": \"abc\", "
	// 	// 					"\"length\": \"3\", "
	// 	// 					"\"size\": \"3\", "
	// 	// 					"\"compare_fn\": \"strcmp()\", "
	// 	// 					"\"strsub_fn\": \"strsub()\", "
	// 	// 					"\"strstr_fn\": \"strstr()\""
	// 	// 				"}"
	// 	// 			"}");
	// 	// 	UNITTEST_EQUALS((Tools::String("abc") + "1234567890").serialize(),
	// 	// 			"{ \"Tools::String\": "
	// 	// 				"{"
	// 	// 					"\"buffer\": \"abc1234567890\", "
	// 	// 					"\"length\": \"13\", "
	// 	// 					"\"size\": \"13\", "
	// 	// 					"\"compare_fn\": \"strcmp()\", "
	// 	// 					"\"strsub_fn\": \"strsub()\", "
	// 	// 					"\"strstr_fn\": \"strstr()\""
	// 	// 				"}"
	// 	// 			"}");
	// 	// }
	//---	Tools::String Tools::String::toString(void) const; ------------------------------------------------------------------
		{
			UNITTEST_EQUALS(Tools::String("").toString(), "");
			UNITTEST_EQUALS((Tools::String("") + "1234567890").toString(), "1234567890");
			UNITTEST_EQUALS(Tools::String("abc").toString(), "abc");
			UNITTEST_EQUALS((Tools::String("abc") + "1234567890").toString(), "abc1234567890");
		}
	//--- static Tools::String toString(int128_t value, uint radix = 10); ------------------------------------------------
		{
			UNITTEST_EQUALS(Tools::String::toString(0LL), "0");
			UNITTEST_EQUALS(Tools::String::toString(12345678901234LL), "12345678901234");
			UNITTEST_EQUALS(Tools::String::toString(-12345678901234LL), "-12345678901234");
			UNITTEST_EQUALS(Tools::String::toString(0x0123456789ABCDEFLL, 16), "123456789ABCDEF");
			UNITTEST_EQUALS(Tools::String::toString(01234567012345LL, 8), "1234567012345");
			UNITTEST_EQUALS(Tools::String::toString(0x432143214321LL, 2), "10000110010000101000011001000010100001100100001");
		}

		{
			UNITTEST_EQUALS(Tools::String::toString(0), "0");
			UNITTEST_EQUALS(Tools::String::toString(1234567890), "1234567890");
			UNITTEST_EQUALS(Tools::String::toString(-1234567890), "-1234567890");
			UNITTEST_EQUALS(Tools::String::toString(0x0123456789ABCDEF, 16), "123456789ABCDEF");
			UNITTEST_EQUALS(Tools::String::toString(01234567, 8), "1234567");
			UNITTEST_EQUALS(Tools::String::toString(0x4321, 2), "100001100100001");
		}
	// //---	std::vector<Tools::String> Tools::String::split(const char *needle);
	// 	// {	std::vector<Tools::String> strings;
	// 	// 	Tools::String test="The is a test of emergency broadcast system. This is only a test.";
	// 	// 	strings = test.split("xxx");
	// 	// 	UNITTEST_EQUALS(strings.size(), 1u);
	// 	// 	UNITTEST_EQUALS(strings[0], test);

	// 	// 	strings = test.split("emer");
	// 	// 	UNITTEST_EQUALS(strings.size(), 2u);
	// 	// 	UNITTEST_EQUALS(strings[0], Tools::String("The is a test of "));
	// 	// 	UNITTEST_EQUALS(strings[1], Tools::String("gency broadcast system. This is only a test."));
	// 	// }

	//---	bool Tools::String::isEmpty(void) const; ---------------------------------------------------------------------
		{
			UNITTEST_ASSERT(Tools::String("").isEmpty());
			UNITTEST_ASSERT(!Tools::String("abc").isEmpty());
		}

	//---	uint Tools::String::getLength(void) const; -------------------------------------------------------------------
		{
			UNITTEST_EQUALS(Tools::String("").getLength(), 0u);
			UNITTEST_EQUALS(Tools::String("a").getLength(), 1u);
			UNITTEST_EQUALS(Tools::String("1234567890").getLength(), 10u);
		}

	//---	const char* Tools::String::getChars(void) const; -------------------------------------------------------------
		{
			UNITTEST_EQUALS(strcmp((char*)Tools::String("").getText(), ""), 0);
			UNITTEST_EQUALS(strcmp((char*)Tools::String("a").getText(), "a"), 0);
			UNITTEST_EQUALS(strcmp((char*)Tools::String("1234567890").getText(), "1234567890"), 0);
		}

	//---	void Tools::String::getChars(bool ignore); -------------------------------------------------------------
		{	Tools::String string("abcdefg");
			UNITTEST_ASSERT(string == "abcdefg");
			UNITTEST_ASSERT(string != "ABCDEFG");
			UNITTEST_ASSERT(string != "aBcDefg");
			UNITTEST_ASSERT(string.startsWith("abc"));
			UNITTEST_ASSERT(!string.startsWith("ABC"));
			UNITTEST_ASSERT(!string.startsWith("aBc"));
			UNITTEST_ASSERT(!string.startsWith("def"));
			UNITTEST_ASSERT(!string.startsWith("DEF"));
			UNITTEST_ASSERT(!string.startsWith("Def"));
			UNITTEST_ASSERT(string.contains("def"));
			UNITTEST_ASSERT(!string.contains("DEF"));
			UNITTEST_ASSERT(!string.contains("Def"));

			string.setCaseCompare(true);
			UNITTEST_ASSERT(string == "abcdefg");
			UNITTEST_ASSERT(string == "ABCDEFG");
			UNITTEST_ASSERT(string == "aBcDefg");
			UNITTEST_ASSERT(string.startsWith("abc"));
			UNITTEST_ASSERT(string.startsWith("ABC"));
			UNITTEST_ASSERT(string.startsWith("aBc"));
			UNITTEST_ASSERT(string.contains("abc"));
			UNITTEST_ASSERT(string.contains("ABC"));
			UNITTEST_ASSERT(string.contains("aBc"));
			UNITTEST_ASSERT(string.contains("def"));
			UNITTEST_ASSERT(string.contains("DEF"));
			UNITTEST_ASSERT(string.contains("Def"));
		}

	//---	static bool Tools::String::strcasesub(const char *str, const char *sub); ----------------------------------------
		{
			UNITTEST_ASSERT(Tools::String::strcasesub("", ""));
			UNITTEST_ASSERT(Tools::String::strcasesub("abc", ""));
			UNITTEST_ASSERT(Tools::String::strcasesub("abc", "a"));
			UNITTEST_ASSERT(Tools::String::strcasesub("abc", "abc"));
			UNITTEST_ASSERT(!Tools::String::strcasesub("abc", "abcd"));
			UNITTEST_ASSERT(!Tools::String::strcasesub("abc", "bc"));
			UNITTEST_ASSERT(Tools::String::strcasesub("abc", "A"));
			UNITTEST_ASSERT(Tools::String::strcasesub("abc", "ABc"));
		}
	}
}