#include <unistd.h>
#include <regex.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "UnitTests.hpp"
#include "unittests-Tools::String.hpp"

uint test_number = 0;
uint tests_that_passed = 0;
uint tests_that_failed = 0;

// void process_wait_results(pid_t pid) {
// 	int status;
// 	waitpid(pid, &status, 0);

// 	if ( WCOREDUMP(status) ) {
// 		std::cout << VT220_RED << "...exited core dump." << VT220_RESET << std::endl;

// 	} else if ( WIFSIGNALED(status) ) {
// 		std::cout << "...exited on signal." << std::endl;

// 	} else {
// 		unsigned char results = WEXITSTATUS(status);
// 	}
// }

// void process_test(bool test, const char *expected_str, auto expected, const char *got_str, auto got) {
// 	if ( test ) {
// 		std::cout << VT220_GREEN << "PASSED." << VT220_RESET << "\n";
// 		exit(0);

// 	} else {
// 		std::cout << "Got=\"" << got_str << "\"" << VT220_RED << "[" << got << "] " << VT220_RESET \
// 				<< "expected=\"" << expected_str << "\"" << VT220_RED << "[" << expected <<"]" << VT220_RESET \
// 				<< "..." << VT220_RED << " FAILED!" << VT220_RESET
// 				<< std::endl;
// 		exit(1);
// 	}
// }

	Tools::String autoToString(auto var) {
		std::ostringstream output;
		output << var;
		return output.str().c_str();
	}

	void IAS_unittest_assert(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_to_test, bool to_test) {
		test_number++;

		std::cout << "Test #" << test_number << " [" << src_filename << ":" << method << ":" << lineno << "]: ";

		if ( to_test ) {
			tests_that_passed++;

			std::cout << std::flush
				<< VT200::FG_Green << str_to_test << VT200::reset
				<< "... PASSED.";

		} else {
			tests_that_failed++;

			std::cout
				<< VT200::FG_Red
				<< str_to_test.encode() << "... "
				<< VT200::reset
				<< str_to_test.encode() << "... FAILED.";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

	void IAS_unittest_pattern(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const Tools::String& output_to_test, const char* regex_text) {
		test_number++;

		regex_t regex_exec;
		regmatch_t pmatch[1];
		if ( regcomp(&regex_exec, regex_text, REG_NEWLINE) == 0 ) {

			std::cout << std::flush
				<< "Test #" << test_number << " [" << src_filename << ":" << method << ":" << lineno << "]: ";

			if ( regexec(&regex_exec, (char*)output_to_test.getText(), 1, pmatch, 0) == 0 ) {
				tests_that_passed++;

				std::cout
					<< output_to_test.encode() << "... PASSED.";

			} else {
				tests_that_failed++;

				std::cout
					<< Tools::String(str_output_to_test).encode() << str_output_to_test << "... "
					<< VT200::FG_Red << "FAILED: " << VT200::reset
					<< "expected: ["
					<< VT200::FG_Red << Tools::String(regex_text).encode() << VT200::reset
					<< "] but got: ["
					<< VT200::FG_Red << Tools::String(output_to_test).encode() << VT200::reset
					<< "]";
			}

			std::cout
				<< std::endl
				<< std::flush;

		} else {
			std::cerr << "Bad regex: " << regex_text << std::endl;
			abort();
		}
	}

	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											long output_to_test, long expected) {
		test_number++;
		std::cout << std::flush
			<< "Test #" << test_number << " [" << src_filename << ":" << method << ":" << lineno << "]: ";

		if ( output_to_test == expected ) {
			tests_that_passed++;
			std::cout
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " == ["
				<< VT200::FG_Green << output_to_test << VT200::reset
				<< "]... PASSED.";

		} else {
			tests_that_failed++;
			std::cout
				<< str_output_to_test.encode() << "... "
				<< VT200::FG_Red << "FAILED: " << VT200::reset
				<< "expected: "
				<< "[" << VT200::FG_Red << expected << VT200::reset << "] "
				<< "but got: "
				<< "[" << VT200::FG_Red << output_to_test << VT200::reset << "]";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const Tools::String& output_to_test, const Tools::String& expected) {
		test_number++;

		std::cout << std::flush
			<< "Test #" << test_number << " [" << src_filename << ":" << method << ":" << lineno << "]: ";

		if ( output_to_test == expected ) {
			tests_that_passed++;
			std::cout
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " == ["
				<< VT200::FG_Green << output_to_test.encode() << VT200::reset
				<< "]... PASSED.";

		} else {
			tests_that_failed++;
			std::cout
				<< str_output_to_test.encode() << "... "
				<< VT200::FG_Red << "FAILED: " << VT200::reset
				<< "expected: "
				<< "[" << VT200::FG_Red << expected.encode() << VT200::reset << "] "
				<< "but got: "
				<< "[" << VT200::FG_Red << output_to_test.encode() << VT200::reset << "]";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

	void IAS_unittest_not_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											long output_to_test, long expected) {
		test_number++;

		std::cout << std::flush
			<< "Test #" << test_number << " [" << src_filename << ":" << method << ":" << lineno << "]: ";

		if ( output_to_test == expected ) {
			tests_that_passed++;
			std::cout
				<< str_expected.encode() << " == ["
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " ... PASSED.";

		} else {
			tests_that_failed++;
			std::cout
				<< str_output_to_test.encode() << "... "
				<< VT200::FG_Red << "FAILED: " << VT200::reset
				<< "expected: "
				<< "[" << VT200::FG_Red << expected << VT200::reset << "] "
				<< "but got: "
				<< "[" << VT200::FG_Red << output_to_test << VT200::reset << "]";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

int main(int cnt, char *arg[], char *env[]) {
	fprintf(stderr, "Unit tests starting...\n");
	// fprintf(stderr, "sizeof(char)=%zu sizeof(wchar_t)=%zu sizeof(short)=%zu sizeof(int)=%zu sizeof(long)=%zu sizeof(long long)=%zu sizeof(void*)=%zu sizeof(size_t)=%zu\n",
			// sizeof(char), sizeof(wchar_t), sizeof(short), sizeof(int), sizeof(long), sizeof(long long), sizeof(void*), sizeof(size_t));
	UnitTests::unittests_Memory();
	UnitTests::unittests_String();
	UnitTests::unittests_Stream();
}

