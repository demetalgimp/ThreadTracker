#include
#include "UnitTests.hpp"

namespace UnitTests
{

//=== class CppTokenStream ==========================================================================================================================
	void test_CppTokenStream(void) {
	//---	virtual Token CppTokenizer::next(void);
		{	Token token;
			CppTokenStream *cpp_stream;

			cpp_stream = new CppTokenStream(new StringStream("//\n"));
			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token(TokenType::eEOF, "", "//\n"));
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;

			cpp_stream = new CppTokenStream(new StringStream("//this is a test\n"));
			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token(TokenType::eEOF, "", "//this is a test\n"));
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;

			cpp_stream = new CppTokenStream(new StringStream("/**//*this is a test*/  \t\f\n "));
			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token(TokenType::eEOF, "", "/**//*this is a test*/  \t\f\n "));
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;
		}
	//---	virtual Token  scoopWord(const String& spaces) override;
		{	Token token;
			CppTokenStream *cpp_stream;

			cpp_stream = new CppTokenStream(new StringStream("t s1 rest quest123 pest_123a __t __"));
			token = cpp_stream->current();
			UNITTEST_EQUALS(token, Token('word', "t", ""));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "s1", " "));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "rest", " "));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "quest123", " "));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "pest_123a", " "));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "__t", " "));

			token = cpp_stream->next();
			UNITTEST_EQUALS(token, Token('word', "__", " "));

			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;
		}
		{	CppTokenStream cpp_stream(new StringStream("a&&=b+c"));
			UNITTEST_EQUALS(cpp_stream.next(), Token('word', "a"));
			UNITTEST_EQUALS(cpp_stream.next(), Token('&&='));
			UNITTEST_EQUALS(cpp_stream.next(), Token('word', "b"));
			UNITTEST_EQUALS(cpp_stream.next(), Token('+'));
			UNITTEST_EQUALS(cpp_stream.next(), Token('word', "c"));
			UNITTEST_ASSERT(cpp_stream.next().isEOF());
		}
	//---	virtual String scoopSpace(void) override;
		{	CppTokenStream stream1(new StringStream("this test"));
			UNITTEST_EQUALS(stream1.next(), Token('word', "this"));
			UNITTEST_EQUALS(stream1.next(), Token('word', "test", " "));
			UNITTEST_ASSERT(stream1.next().isEOF());

			CppTokenStream stream2(new StringStream("this /**/test"));
			UNITTEST_EQUALS(stream2.next(), Token('word', "this"));
			UNITTEST_EQUALS(stream2.next(), Token('word', "test", " /**/"));
			UNITTEST_ASSERT(stream2.next().isEOF());

			CppTokenStream stream3(new StringStream("word//msg\ntest"));
			UNITTEST_EQUALS(stream3.next(), Token('word', "word"));
			UNITTEST_EQUALS(stream3.next(), Token('word', "test", "//msg\n"));
			UNITTEST_ASSERT(stream3.next().isEOF());
		}
		{	String cpp_text("void test_CppTokenizer(void) {\n"
							"//---	virtual Token CppTokenizer::next(void);\n"
							"	{\n"
							"\n"
							"/**/	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream(\"//\\n\"));\n"
							"		Token token = cpp_stream->next();\n"
							"		float counter = 12345.7890e+432;\n"
							"\n");
			CppTokenStream stream(new StringStream(cpp_text));
			String cpp_text_tokens;
			while ( !stream.isEOF() ) {
				Token token = stream.next();
				cpp_text_tokens += (token.whitespace + token.text);
			}
			UNITTEST_EQUALS(cpp_text_tokens, cpp_text);
		}
		{	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream("()[]{}\\;,?`@$#"));
			UNITTEST_EQUALS(cpp_stream->current(), Token(TokenType::eLeftParen, "("));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eRightParen, ")"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eLeftBracket, "["));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eRightBracket, "]"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eLeftBrace, "{"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eRightBrace, "}"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBackslash, "\\"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eSemicolon, ";"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eComma, ","));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eArithIf, "?"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBackQuote, "`"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eAt, "@"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eDollar, "$"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eHash, "#"));
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;
		}
		{	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream("....~=~!=!%=%^=^&&=&&-=&=&->--- "));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eElipsis, "..."));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::ePeriod, "."));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitNotAssign, "~="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitNot, "~"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eNotEquals, "!="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBoolNot, "!"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eModulusAssign, "%="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eModulus, "%"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitXorAssign, "^="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitXor, "^"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBoolAndAssign, "&&="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBoolAnd, "&&"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eMinusAssign, "-="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitAndAssign, "&="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitAnd, "&"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eDereference, "->"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eDecrement, "--"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eMinus, "-"));
			delete cpp_stream;
		}
		{	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream("===+=+++||=|||=| "));
			UNITTEST_EQUALS(cpp_stream->current(), Token(TokenType::eEqualsTo, "=="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eEquals, "="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::ePlusAssign, "+="));
			UNITTEST_EQUALS(cpp_stream->current(), Token(TokenType::eSumAssign, "+="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eIncrement, "++"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eSum, "+"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBoolOrAssign, "||="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBoolOr, "||"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitOrAssign, "|="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eBitOr, "|"));
			delete cpp_stream;
		}
		{	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream("<<=<<<=<>>=>>>=> "));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eShiftLeftAssign, "<<="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eShiftLeft, "<<"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eLessEquals, "<="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eLessThan, "<"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eShiftRightAssign, ">>="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eShiftRight, ">>"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eGreaterEquals, ">="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eGreaterThan, ">"));
			delete cpp_stream;
		}
		{	CppTokenStream *cpp_stream = new CppTokenStream(new StringStream("::/=*=*:/ "));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eScope, "::"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eDivideAssign, "/="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eMultiplyAssign, "*="));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eMultiply, "*"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eColon, ":"));
			UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eDivide, "/"));
			delete cpp_stream;
		}

	//---	virtual void CppTokenizer::scoopSpace(void);
	//---	virtual void CppTokenizer::scoopNumber(void);
		{	bool first = true;
			String integer_numbers =
					"0 1 2 3 4 5 6 7 8 9 01 11 21 31 41 51 61 71 81 91 1234567890 "	// <-- base₁₀
					"0x0 0x1234 0x0123456789ABCDEF 0x0123456789abcdef 0xABCDEF "	// <-- base₁₆
					"0123 0567 01234567"											// <-- base₈
					;
			std::vector<String> numbers_vector = integer_numbers.split(" ");
			CppTokenStream *cpp_stream = new CppTokenStream(new StringStream(integer_numbers));
			for ( String number : numbers_vector ) {
				UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eNumber, number, (first? "": " ")));
				first = false;
			}
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;
		}
		{	bool first = true;
			String float_numbers =
					"9876.1 9876.1234 "

					"1e2 1E2 9876e1 9876E1 "
					"1e-2 1E-2 9876e-1 9876E-1 "
					"1e+2 1E+2 9876e+1 9876E+1 "

					"1e1111 1E1111 9876e1111 9876E1111 "
					"1e-1111 1E-1111 9876e-1111 9876E-1111 "
					"1e+1111 1E+1111 9876e+1111 9876E+1111 "

					"1.1e1 1.1E1 9876.1234e1 9876.1234E1 "
					"1.1e-1 1.1E-1 9876.1234e-1 9876.1234E-1 "
					"1.1e+1 1.1E+1 9876.1234e+1 9876.1234E+1 "

					"1.1e1111 1.1E1111 9876.1234e1111 9876.1234E1111 "
					"1.1e-1111 1.1E-1111 9876.1234e-1111 9876.1234E-1111 "
					"1.1e+1111 1.1E+1111 9876.1234e+1111 9876.1234E+1111"
					;

			std::vector<String> numbers_vector = float_numbers.split(" ");
			CppTokenStream *cpp_stream = new CppTokenStream(new StringStream(float_numbers));
			for ( String number : numbers_vector ) {
				UNITTEST_EQUALS(cpp_stream->next(), Token(TokenType::eFloat, number, (first? "": " ")));
				first = false;
			}
			UNITTEST_ASSERT(cpp_stream->next().isEOF());
			delete cpp_stream;
		}

	//---			virtual String CppTokenStream::toString(void) const override;
	//--- friend 	std::ostream& operator<<(std::ostream& stream, const XmlTokenStream& tokens);
		{	cchar *text =	"	Token TokenStream::scoopNumber(const String& spaces) {\n"
							"		TokenType type = TokenType::eEOF;\n"
							"		TextAccumulator acc;\n"
							"		if ( stream->current() != EOF ) { // <-- read until an EOF\n"
							"			while ( isdigit(stream->current()) ) {\n"
							"				acc += stream->current();\n"
							"				stream->next();\n"
							"			}\n"
							"			type = TokenType::eNumber;\n"
							"		}\n"
							"		current_token = Token(type, acc.toString(), spaces);\n"
							"		return current_token;\n"
							"	}\n";
			CppTokenStream stream(text);
			std::ostringstream output;
			while ( !stream.isEOF() ) {
				stream.next();
				output << stream.current().whitespace << stream.current().text;
			}
			UNITTEST_EQUALS(output.str(), text);
		}
	}
}
