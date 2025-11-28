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

	// char process_wait_results(pid_t pid) {
	// 	int status;
	// 	unsigned char results = 0;
	// 	waitpid(pid, &status, 0);

	// 	if ( WCOREDUMP(status) ) {
	// 		std::cout << VT220_RED << "...exited core dump." << VT220_RESET << std::endl;

	// 	} else if ( WIFSIGNALED(status) ) {
	// 		std::cout << "...exited on signal (" << WTERMSIG(status) << ")" << std::endl;

	// 	} else {
	// 		results = WEXITSTATUS(status);
	// 	}
	// 	return results;
	// }

	Tools::String autoToString(auto var) {
		std::ostringstream output;
		output << var;
		return output.str().c_str();
	}

	void IAS_line(bool to_test, const Tools::String& src_filename, const Tools::String& method, uint lineno) {
		test_number++;
		(to_test? tests_that_passed++ : tests_that_failed++);
		// std::cout << "Test #" << test_number << "(" << tests_that_passed << "/" << tests_that_failed << ") ";
		std::cout << "Test #" << test_number << "(failed: " << tests_that_failed << ") ";
		std::cout << "[" << src_filename << ":" << method << ":" << lineno << "]: ";
	}

	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											long output_to_test, long expected) {
		bool to_test = (output_to_test == expected);
		IAS_line(to_test, src_filename, method, lineno);

		if ( to_test ) {
			std::cout
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " == ["
				<< VT200::FG_Green << output_to_test << VT200::reset
				<< "]... PASSED.";

		} else {
			std::cout
				<< VT200::FG_Red << str_output_to_test.encode() << VT200::reset
				<< "... "
				<< VT200::FG_Red << "FAILED: " << VT200::reset
				<< "expected: ["
				<< VT200::FG_Red << expected << VT200::reset 
				<< "] but got: ["
				<< VT200::FG_Red << output_to_test << VT200::reset
				<< "]";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

	void IAS_unittest_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											const Tools::String& output_to_test, const Tools::String& expected) {
		bool to_test = (output_to_test == expected);
		IAS_line(to_test, src_filename, method, lineno);

		if ( to_test ) {
			std::cout
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " == ["
				<< VT200::FG_Green << output_to_test.encode() << VT200::reset
				<< "]... PASSED.";

		} else {
			std::cout
				<< VT200::FG_Red << str_output_to_test.encode() << VT200::reset
				<< "... "
				<< VT200::FG_Red << "FAILED: " << VT200::reset
				<< "expected: ["
				<< VT200::FG_Red << expected.encode() << VT200::reset
				<< "] but got: ["
				<< VT200::FG_Red << output_to_test.encode() << VT200::reset
				<< "]";
		}
		std::cout
			<< std::endl
			<< std::flush;
	}

	void IAS_unittest_assert(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_to_test, bool to_test) {
		IAS_line(to_test, src_filename, method, lineno);

		if ( to_test ) {
			std::cout << std::flush
				<< VT200::FG_Green << str_to_test << VT200::reset
				<< "... PASSED.";

		} else {
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

			bool to_test = (regexec(&regex_exec, (char*)output_to_test.getText(), 1, pmatch, 0) == 0);
			IAS_line(to_test, src_filename, method, lineno);

			if ( to_test ) {
				std::cout
					<< output_to_test.encode() << "... PASSED.";

			} else {
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

	void IAS_unittest_not_equals(const Tools::String& src_filename, const Tools::String& method, uint lineno,
											const Tools::String& str_output_to_test, const Tools::String& str_expected,
											long output_to_test, long expected) {
		bool to_test = (output_to_test == expected);
		IAS_line(to_test, src_filename, method, lineno);

		if ( to_test ) {
			std::cout
				<< str_expected.encode() << " == ["
				<< VT200::FG_Green << str_output_to_test << VT200::reset
				<< " ... PASSED.";

		} else {
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

