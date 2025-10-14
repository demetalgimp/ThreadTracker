#ifndef UNITTESTS_HPP
#define UNITTESTS_HPP

#include <unistd.h>
#include <regex.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "Memory.hpp"

#define VT220_RESET  "\x1B[0m"
#define VT220_RED    "\x1B[31m"
#define VT220_GREEN  "\x1B[32m"
#define VT220_YELLOW "\x1B[38;5;190m"

extern uint test_number;
extern uint tests_that_passed;
extern uint tests_that_failed;

void process_wait_results(pid_t pid);
void process_test(bool test, const char *expected_str, auto expected, const char *got_str, auto got);
// namespace UnitTests {
// 	extern void test_scanner(const char *test_elements_str);
// }
// class UnitTest {
// 	typedef const char cchar;
// 	typedef unsigned int uint;

// 	private:
// 		static void unittest_String(void);
// 		static void unittest_Token(void);
// 		static void unittest_StringStream(void);
// 		// static void unittest_TokenStream(void);
// 		// static void unittest_CppTokenStream(void);
// 		// static void unittest_XmlTokenStream(void);
// 		// static void unittest_XmlTagTokenStream(void);
// 		static void unittest_Xml(void);

// 	public:
// 		static void main(void);
// };
struct VT200 {
	static constexpr const char *reset = "\x1B[0m";

//--- Foreground presets
	static constexpr const char *FG_Black = "\x1B[30m";
	static constexpr const char *BG_Black = "\x1B[40m";
	static constexpr const char *FG_Bright_Black = "\x1B[90m";
	static constexpr const char *BG_Bright_Black = "\x1B[100m";
	static constexpr const char *FG_Red = "\x1B[31m";
	static constexpr const char *BG_Red = "\x1B[41m";
	static constexpr const char *FG_Bright_Red = "\x1B[91m";
	static constexpr const char *BG_Bright_Red = "\x1B[101m";
	static constexpr const char *FG_Green = "\x1B[32m";
	static constexpr const char *BG_Green = "\x1B[42m";
	static constexpr const char *FG_Bright_Green = "\x1B[92m";
	static constexpr const char *BG_Bright_Green = "\x1B[102m";
	static constexpr const char *FG_Yellow = "\x1B[93m";
	static constexpr const char *BG_Yellow = "\x1B[43m";
	static constexpr const char *FG_Bright_Yellow = "\x1B[93m";
	static constexpr const char *BG_Bright_Yellow = "\x1B[103m";
	static constexpr const char *FG_Blue = "\x1B[34m";
	static constexpr const char *BG_Blue = "\x1B[44m";
	static constexpr const char *FG_Bright_Blue = "\x1B[94m";
	static constexpr const char *BG_Bright_Blue = "\x1B[104m";
	static constexpr const char *FG_Magenta = "\x1B[35m";
	static constexpr const char *BG_Magenta = "\x1B[45m";
	static constexpr const char *FG_Bright_Magenta = "\x1B[95m";
	static constexpr const char *BG_Bright_Magenta = "\x1B[105m";
	static constexpr const char *FG_Cyan = "\x1B[36m";
	static constexpr const char *BG_Cyan = "\x1B[46m";
	static constexpr const char *FG_Bright_Cyan = "\x1B[96m";
	static constexpr const char *BG_Bright_Cyan = "\x1B[106m";
	static constexpr const char *FG_White = "\x1B[37m";
	static constexpr const char *BG_White = "\x1B[47m";
	static constexpr const char *FG_Bright_White = "\x1B[97m";
	static constexpr const char *BG_Bright_White = "\x1B[107m";
};

#define JAILED
extern uint test_cnt;
extern uint test_fail;

	Tools::String autoToString(auto var);
	void IAS_unittest_assert(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_to_test, const bool to_test);
	void IAS_unittest_pattern(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const Tools::String& output_to_test, const char* regex_text);

	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const long output_to_test, const long expected);
	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const Tools::String& output_to_test, const Tools::String& expected);

	void IAS_unittest_not_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const long output_to_test, const long expected);

#define PASS() { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_pass(usecase_file, usecase_method, usecase_lineno); \
	}

#define FAIL(MSG) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_fail(usecase_file, usecase_method, usecase_lineno, MSG); \
	}

//--- ERROR! Because I am using Eclipse (which has fallen from grace), moving these macros cannot be left in a header file without TONS of errors.
// #define UNITTEST_ASSERT(TO_TEST) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_unittest_assert(usecase_file, usecase_method, usecase_lineno, #TO_TEST, TO_TEST); \
	}

#define UNITTEST_EQUALS(OUTPUT_TO_TEST, EXPECTED) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_unittest_equals(usecase_file, usecase_method, usecase_lineno, #OUTPUT_TO_TEST, #EXPECTED, OUTPUT_TO_TEST, EXPECTED); \
	}

#define UNITTEST_PATTERN(OUTPUT_TO_TEST, PATTERN) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_unittest_pattern(usecase_file, usecase_method, usecase_lineno, #OUTPUT_TO_TEST, #PATTERN, OUTPUT_TO_TEST, PATTERN); \
	}

#define UNITTEST_ASSERT(OUTPUT_TO_TEST) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_unittest_assert(usecase_file, usecase_method, usecase_lineno, #OUTPUT_TO_TEST, OUTPUT_TO_TEST); \
	}

#define UNITTEST_REFUTE(OUTPUT_TO_TEST) { \
		const char *usecase_file = __FILE__; \
		const char *usecase_method = __FUNCTION__; \
		uint usecase_lineno = __LINE__; \
		IAS_unittest_refute(usecase_file, usecase_method, usecase_lineno, #OUTPUT_TO_TEST, OUTPUT_TO_TEST); \
	}


// #define JAIL(OP, OP_NAME,expected, got) { \
// 		std::cout << "Test #" << test_cnt << ":\t" << OP_NAME << " : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got OP _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// #ifdef JAILED

// 	#define TEST_EQUALS(got, expected) { \
// 		std::cout << "Test #" << test_cnt << ":\tEQUALS? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got == _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_NOT_EQUALS(got, expected) { \
// 		std::cout << "Test #" << test_cnt << ":\tDIFFERS? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got != _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_GREATER_EQUALS(got, expected) { \
// 		std::cout << "Test #" << test_cnt << ":\tGREATER_EQUALS? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got >= _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_GREATER_THAN(got, expected) { \
// 		std::cout << "Test #" << test_cnt << ":\tGREATER_THAN? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got > _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_LESSER_EQUALS(got, expected) { \
// 		std::cout << "Test #" << test_cnt << ":\tLESSER_EQUALS? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got <= _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_LESSER_THAN(got, expected)	{ \
// 		std::cout << "Test #" << test_cnt << ":\tLESS_THAN? : " << __FILE__ << " [line #" << __LINE__ << "]: "; \
// 		std::cout.flush(); \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			auto _expected = expected; \
// 			auto _got = got; \
// 			process_test((_got < _expected), #expected, expected, #got, got); \
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_BINARY_EQUALS(got, expected, bytes) { \
// 		pid_t pid; \
// 		if ( (pid = fork()) == 0 ) { \
// 			uint8_t *_got = (uint8_t *)(got); \
// 			uint8_t *_expected = (uint8_t *)(expected); \
// 			if ( memcmp(_got, _expected, bytes) == 0 ) { \
// 				std::cout << VT220_GREEN << "PASSED." << VT220_RESET << "\n"; \
// 			} else { \
// 				std::cout << VT220_RED << "FAILED. Expected \"" << _expected << "\" but got \"" << _got << "\"" << VT220_RESET << std::endl; \
// 			} \
// 			exit(0);\
// 			\
// 		} else { \
// 			process_wait_results(pid); \
// 		} \
// 	}

// 	#define TEST_TRUE(test)  { \
//         pid_t pid; \
//         if ( (pid = fork()) == 0 ) { \
//             auto _test = test; \
//             std::cout << "Test #" << test_cnt << ":\tTRUE? " << __FILE__ << "[line #" << __LINE__ << "]: \"" << #test << "\"..."; \
//             std::cout << (_test? VT220_GREEN "PASSED": VT220_RED "FAILED") << "." << VT220_RESET << std::endl; \
//             exit(0); \
//             \
// 		} else { \
// 			process_wait_results(pid); \
//         } \
// 	}

// 	#define TEST_FALSE(test) { \
//         pid_t pid; \
//         if ( (pid = fork()) == 0 ) { \
//             auto _test = test; \
//             std::cout << "Test #" << test_cnt << ":\tFALSE? " << __FILE__ << "[line #" << __LINE__ << "]: \"" << #test << "\"..."; \
//             std::cout << (!_test? VT220_GREEN "PASSED": VT220_RED "FAILED") << "." << VT220_RESET << std::endl; \
//             exit(0); \
//             \
// 		} else { \
// 			process_wait_results(pid); \
//         } \
// 	}
// #else
// 	#error "JAILED must be defined for unit tests."
// #endif

// // void process_wait_results(pid_t pid) {
// // 	int status;
// // 	waitpid(pid, &status, 0);
// // 	test_cnt++;

// // 	if ( WCOREDUMP(status) ) {
// // 		std::cout << VT220_RED << "...exited core dump." << VT220_RESET << std::endl;
// // 		test_fail++;

// // 	} else if ( WIFSIGNALED(status) ) {
// // 		std::cout << "...exited on signal." << std::endl;
// // 		test_fail++;

// // 	} else {
// // 		unsigned char results = WEXITSTATUS(status);
// // 	}
// // }

// // void process_test(bool test, const char *expected_str, auto expected, const char *got_str, auto got) {
// // 	if ( test ) {
// // 		std::cout << VT220_GREEN << "PASSED." << VT220_RESET << "\n";
// // 		exit(0);

// // 	} else {
// // 		std::cout << "Got=" << got_str << "" << VT220_RED << "[" << got << "] " << VT220_RESET \
// // 				<< "expected=" << expected_str << VT220_RED << "[" << expected <<"]" << VT220_RESET \
// // 				<< "..." << VT220_RED << " FAILED!" << VT220_RESET
// // 				<< std::endl;
// // 		exit(1);
// // 	}
// // }

// extern void Blob_unittests(void);
// extern void String_unittests(void);
// // int main(int cnt, char *arg[], char *env[]) {
// // 	Blob_unittests();
// // 	String_unittests();
// // 	std::cout << "Total: " << test_cnt << "   failed: " << test_fail << std::endl;
// // }

#endif

