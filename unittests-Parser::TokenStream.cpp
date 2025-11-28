#include "UnitTests.hpp"
#include "TokenStream.hpp"

namespace UnitTests {

//=== class StringStream ===================================================================================================================================
	void unittests_StringStream(void) {
	//--- StringStream(const Tools::String& string): stream(string) {}
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_EQUALS(ss.toString(), "[\"  Hello,\n World!  \": -1]");
		}
	//--- StringStream(const StringStream& stream): text(stream.text), index(stream.index) {}
		{	Parser::StringStream ss("  Hello,\n World!  ");
			Parser::StringStream ss2(ss);
			UNITTEST_EQUALS(ss2.toString(), ss.toString());
		}
	//--- char peek(int offset=0) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_EQUALS(ss.peek(0), ' ');
			UNITTEST_EQUALS(ss.peek(1), ' ');
			UNITTEST_EQUALS(ss.peek(2), 'H');
			UNITTEST_EQUALS(ss.peek(3), 'e');
			UNITTEST_EQUALS(ss.peek(4), 'l');
			UNITTEST_EQUALS(ss.peek(5), 'l');
			UNITTEST_EQUALS(ss.peek(6), 'o');
			UNITTEST_EQUALS(ss.peek(7), ',');
			UNITTEST_EQUALS(ss.peek(8), '\n');
			UNITTEST_EQUALS(ss.peek(9), ' ');
			UNITTEST_EQUALS(ss.peek(10), 'W');
			UNITTEST_EQUALS(ss.peek(11), 'o');
			UNITTEST_EQUALS(ss.peek(12), 'r');
			UNITTEST_EQUALS(ss.peek(13), 'l');
			UNITTEST_EQUALS(ss.peek(14), 'd');
			UNITTEST_EQUALS(ss.peek(15), '!');
			UNITTEST_EQUALS(ss.peek(16), ' ');
			UNITTEST_EQUALS(ss.peek(17), ' ');
			UNITTEST_EQUALS(ss.peek(18), 0);
			for ( int i = 1; i <= 15; i++ ) {
				ss.next();
			}
			UNITTEST_EQUALS(ss.peek(0), '!');
			UNITTEST_EQUALS(ss.peek(1), ' ');
			UNITTEST_EQUALS(ss.peek(2), ' ');
			UNITTEST_EQUALS(ss.peek(3), 0);
			UNITTEST_EQUALS(ss.peek(4), 0);
			UNITTEST_EQUALS(ss.peek(-1), 'd');
			UNITTEST_EQUALS(ss.peek(-2), 'l');
			UNITTEST_EQUALS(ss.peek(-3), 'r');
			UNITTEST_EQUALS(ss.peek(-4), 'o');
			UNITTEST_EQUALS(ss.peek(-5), 'W');
		}
	//--- //bool peek(const Tools::String& test, Stream& consumer) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_ASSERT(ss.peek("  He"));
		}
    //--- bool peek(const Tools::String& test, bool consume = false) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_ASSERT(ss.peek("  He", false));
			UNITTEST_EQUALS(ss.getIndex(), 0);
			UNITTEST_ASSERT(ss.peek("  He", true));
			UNITTEST_EQUALS(ss.getIndex(), 4);
			UNITTEST_ASSERT(!ss.peek(" He", true));
			UNITTEST_EQUALS(ss.getIndex(), 4);
			UNITTEST_ASSERT(ss.peek("llo", true));
			UNITTEST_EQUALS(ss.getIndex(), 7);
		}
    //--- char current(void) override;
		{	Parser::StringStream ss1("");
			UNITTEST_ASSERT(ss1.isEOF());
			UNITTEST_EQUALS(ss1.current(), -1);

			Parser::StringStream ss2(" bad");
			UNITTEST_EQUALS(ss2.getIndex(), -1);
			UNITTEST_EQUALS(ss2.next(), ' ');
			UNITTEST_EQUALS(ss2.getIndex(), 0);
			UNITTEST_EQUALS(ss2.next(), 'b');
			UNITTEST_EQUALS(ss2.current(), 'b');
		}
    //--- char next(void) override;
		{	Parser::StringStream ss1("");
			UNITTEST_ASSERT(ss1.isEOF());
			UNITTEST_EQUALS(ss1.current(), -1);
			UNITTEST_EQUALS(ss1.next(), 0);

			Parser::StringStream ss2(" ");
			UNITTEST_EQUALS(ss2.next(), ' ');

			Parser::StringStream ss3("this is a test");
			UNITTEST_EQUALS(ss3.next(), 't');
		}
    //--- void skip(int offset) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_EQUALS(ss.getIndex(), -1);
			ss.skip(2);
			UNITTEST_EQUALS(ss.getIndex(), 1);
			UNITTEST_EQUALS(ss.current(), ' ');
			ss.skip(5);
			UNITTEST_EQUALS(ss.getIndex(), 6);
			UNITTEST_EQUALS(ss.current(), 'o');
			ss.skip(3);
			UNITTEST_EQUALS(ss.getIndex(), 9);
			UNITTEST_EQUALS(ss.current(), ' ');
		}
    //--- //uint getLineNumber(void) const override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_EQUALS(ss.getLineNumber(), 1);
			for ( int i = 1; i <= 10; i++ ) {
				ss.next();
			}
			UNITTEST_EQUALS(ss.getLineNumber(), 2);
		}
 	//--- bool isSpace(void) override;
		{Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_ASSERT(ss.isSpace());
			ss.next();
			UNITTEST_ASSERT(ss.isSpace());
			ss.next();
			UNITTEST_ASSERT(!ss.isSpace());
		}
    //--- bool isEOL(void) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_ASSERT(!ss.isEOL());
			for ( int i = 1; i <= 7; i++ ) {
				ss.next();
			}
			UNITTEST_ASSERT(!ss.isEOL());
			ss.next();
			UNITTEST_ASSERT(ss.isEOL());
			ss.next();
			UNITTEST_ASSERT(!ss.isEOL());
		}
	//--- bool isEOF(void) override;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_ASSERT(!ss.isEOF());
			for ( int i = 1; i <= 17; i++ ) {
				ss.next();
			}
			UNITTEST_ASSERT(!ss.isEOF());
			ss.next();
			UNITTEST_ASSERT(!ss.isEOF());
			ss.next();
			UNITTEST_ASSERT(ss.isEOF());
		}
    //--- Tools::String toString(void) const;
		{	Parser::StringStream ss("  Hello,\n World!  ");
			UNITTEST_EQUALS(ss.toString(), "[\"  Hello,\n World!  \": -1]");
			ss.next();
			UNITTEST_EQUALS(ss.toString(), "[\"  Hello,\n World!  \": 0]");
			for ( int i = 1; i <= 5; i++ ) {
				ss.next();
			}
			UNITTEST_EQUALS(ss.toString(), "[\"  Hello,\n World!  \": 5]");
		}
	}

//=== class Token ===================================================================================================================================
	void unittests_Token(void) {
	//--- Token(void): token_type(eEmpty) {}
		{	Parser::Token token;
			UNITTEST_EQUALS(token.token_type, Parser::eEmpty);
			UNITTEST_EQUALS(token.token_text, "");
			UNITTEST_ASSERT(token.isEmpty());
			UNITTEST_ASSERT(!token.isEOF());
			UNITTEST_ASSERT(!token.isSpace());
			UNITTEST_ASSERT(!token);
		}
	//--- explicit Token(char letter);
		{	Parser::Token token('A');
			UNITTEST_EQUALS(token.token_type, (Parser::EToken)'A');
			UNITTEST_EQUALS(token.token_text, "A");
			UNITTEST_ASSERT(!token.isEmpty());
			UNITTEST_ASSERT(!token.isEOF());
			UNITTEST_ASSERT(!token.isSpace());
			UNITTEST_ASSERT(token);
		}
	//--- explicit Token(EToken token, const Tools::String& text = "");
		{	Parser::Token token(Parser::eWord, "Hello");
			// UNITTEST_EQUALS(token.token_type, Parser::eWord);
			// UNITTEST_EQUALS((const char*)token.token_text, "Hello");
			// UNITTEST_ASSERT(!token.isEmpty());
			// UNITTEST_ASSERT(!token.isEOF());
			// UNITTEST_ASSERT(!token.isSpace());
			// UNITTEST_ASSERT(token);
		}
	//--- explicit Token(wchar_t wchar, const Tools::String& text = ""): token_type((EToken)wchar), token_text(text) {}
		{	Parser::Token token(L'B', "World");
			UNITTEST_EQUALS(token.token_type, (Parser::EToken)L'B');
			UNITTEST_EQUALS(token.token_text, "World");
			UNITTEST_ASSERT(!token.isEmpty());
			UNITTEST_ASSERT(!token.isEOF());
			UNITTEST_ASSERT(!token.isSpace());
			UNITTEST_ASSERT(token);
		}
	}

//=== class TokenStream ===================================================================================================================================
	void unittests_TokenStream(void) {
    //--- TokenStream(const Tools::String& string): stream(string) {}
		{	Parser::TokenStream ts("  Hello, World!  ");
			UNITTEST_ASSERT(ts.peek("  He"));
			UNITTEST_ASSERT(!ts.peek(" He"));
			UNITTEST_ASSERT(ts.peek("  Hello"));
			UNITTEST_EQUALS(ts.next().toString(), "  "); // Consume spaces
			UNITTEST_EQUALS(ts.next().toString(), "Hello");
			UNITTEST_ASSERT(ts.peek(", Wo"));
			UNITTEST_EQUALS(ts.next().toString(), ",");
			UNITTEST_ASSERT(ts.peek(" World"));
		}
	//--- TokenStream(const StringStream& stream): stream(stream) {}
		{	Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
			UNITTEST_ASSERT(ts.peek("  He"));
			UNITTEST_ASSERT(!ts.peek(" He"));
			UNITTEST_ASSERT(ts.peek("  Hello"));
			ts.next(); // Consume spaces
			ts.next(); // Consume "Hello"
			UNITTEST_ASSERT(ts.peek(", Wo"));
		}
    //--- private: bool parseWhiteSpace(void);
		{}
    //--- private: void parseIdentifier(void);
		{}
	//--- private: void parseNumber(void);
		{}
	//--- private: void parseString(void);
		{}
	//--- bool peek(const Tools::String& test);
		{	Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
			UNITTEST_ASSERT(ts.peek("  He"));
			UNITTEST_ASSERT(!ts.peek(" He"));
			UNITTEST_ASSERT(ts.peek("  Hello"));
			ts.next(); // Consume spaces
			ts.next(); // Consume "Hello"
			UNITTEST_ASSERT(ts.peek(", Wo"));
			ts.next(); // Consume ","
			UNITTEST_ASSERT(ts.peek(" World"));
		}
	//--- EToken peek(int index) { return ((EToken)stream.peek(index)); }
		{
			Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
			UNITTEST_EQUALS(ts.peek(0), (Parser::EToken)' ');
			UNITTEST_EQUALS(ts.peek(1), (Parser::EToken)' ');
			UNITTEST_EQUALS(ts.peek(2), (Parser::EToken)'H');
			UNITTEST_EQUALS(ts.peek(3), (Parser::EToken)'e');
			UNITTEST_EQUALS(ts.peek(4), (Parser::EToken)'l');
			UNITTEST_EQUALS(ts.peek(5), (Parser::EToken)'l');
			UNITTEST_EQUALS(ts.peek(6), (Parser::EToken)'o');
			UNITTEST_EQUALS(ts.peek(7), (Parser::EToken)',');
		}
	//--- bool peek(char token) { return (stream.peek(1) == token); }
		{	Parser::StringStream ss("  Hello,-Wurld!  ");
			Parser::TokenStream ts(ss);
			UNITTEST_ASSERT(ts.peek(' '));

			ts.next(); // Consume spaces
			Parser::Token token = ts.next();
			UNITTEST_EQUALS(token.token_type, Parser::eWord);
			UNITTEST_EQUALS(token.token_text, "Hello");

			// ts.next(); // Consume ','
			// ts.next(); // Consume '-'
			token = ts.next();
			UNITTEST_ASSERT(ts.peek('W'));
			UNITTEST_EQUALS(ts.peek(1), 'W');
			UNITTEST_EQUALS(token.token_type, Parser::eComma);
			UNITTEST_EQUALS(token.token_text, ",");

			token = ts.next();
			UNITTEST_ASSERT(ts.peek('u'));
			UNITTEST_EQUALS(ts.peek(1), 'u');
			UNITTEST_EQUALS(token.token_type, Parser::eMinus);
			UNITTEST_EQUALS(token.token_text, "-");

			token = ts.next(); // Consume "World"
			UNITTEST_ASSERT(ts.peek(' '));
		}
    //--- Token current(void);
		{	Parser::StringStream ss("Hello, World!  ");
			Parser::TokenStream ts(ss);
			Parser::Token token = ts.current();
			UNITTEST_EQUALS(token.token_type, Parser::eWord);
			UNITTEST_EQUALS(token.token_text, "Hello");
			UNITTEST_ASSERT(!token.isEmpty());
			UNITTEST_ASSERT(!token.isEOF());
			UNITTEST_ASSERT(!token.isSpace());
			UNITTEST_ASSERT(token);
		}
    //--- Token next(void);
		{	Parser::StringStream ss(
					"class  StringStream: public CharStream {\n"
					"        Tools::String text1;\n"
					"        uint index;\n"
					"\n"
					"//--- Constructors and Destructor ----------------------------------------------------------------\n"
					"        public:\n"
					"            StringStream(const Tools::String& text2): "
										"text1(text2), index(0) {} /* stringstream constructor */\n"
					"            StringStream(const StringStream& stream): "
										"text1(stream.text1), index(stream.index) {}\n"
					"            virtual ~StringStream(void) {}\n"
					"==A!=B>=C<=D+=E-=F++G--HI<<J>>K*=L/=M%=N&=O|=P^=Q~=R"
					"<S>T>>=U<<=V/W*X+Y-Z&&a||b!c?d:e!f%g^h&i|j=k.l->m="
				);
			std::vector<Parser::Token> expected_tokens = {
				Parser::Token(Parser::eWord, "class"),
				Parser::Token(Parser::eSpace, "  "),
				Parser::Token(Parser::eWord, "StringStream"),
				Parser::Token(Parser::eColon, ":"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "public"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "CharStream"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eLeftBrace, "{"),
				Parser::Token(Parser::eSpace, "\n        "),
				Parser::Token(Parser::eWord, "Tools"),
				Parser::Token(Parser::eNameResolution, "::"),
				Parser::Token(Parser::eWord, "String"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "text1"),
				Parser::Token(Parser::eSemicolon, ";"),
				Parser::Token(Parser::eSpace, "\n        "),
				Parser::Token(Parser::eWord, "uint"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "index"),
				Parser::Token(Parser::eSemicolon, ";"),
				Parser::Token(Parser::eSpace, "\n\n//--- Constructors and Destructor ----------------------------------------------------------------\n        "),
				Parser::Token(Parser::eWord, "public"),
				Parser::Token(Parser::eColon, ":"),
				Parser::Token(Parser::eSpace, "\n            "),
				Parser::Token(Parser::eWord, "StringStream"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "const"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "Tools"),
				Parser::Token(Parser::eNameResolution, "::"),
				Parser::Token(Parser::eWord, "String"),
				Parser::Token(Parser::eAmpersand, "&"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "text2"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eColon, ":"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "text1"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "text2"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eComma, ","),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "index"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eNumber, "0"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eLeftBrace, "{"),
				Parser::Token(Parser::eRightBrace, "}"),
				Parser::Token(Parser::eSpace, " /* stringstream constructor */\n            "),
				Parser::Token(Parser::eWord, "StringStream"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "const"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "StringStream"),
				Parser::Token(Parser::eAmpersand, "&"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "stream"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eColon, ":"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "text1"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "stream"),
				Parser::Token(Parser::ePeriod, "."),
				Parser::Token(Parser::eWord, "text1"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eComma, ","),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eWord, "index"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "stream"),
				Parser::Token(Parser::ePeriod, "."),
				Parser::Token(Parser::eWord, "index"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eLeftBrace, "{"),
				Parser::Token(Parser::eRightBrace, "}"),
				Parser::Token(Parser::eSpace, "\n            "),
				Parser::Token(Parser::eWord, "virtual"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eTilde, "~"),
				Parser::Token(Parser::eWord, "StringStream"),
				Parser::Token(Parser::eLeftParenthesis, "("),
				Parser::Token(Parser::eWord, "void"),
				Parser::Token(Parser::eRightParenthesis, ")"),
				Parser::Token(Parser::eSpace, " "),
				Parser::Token(Parser::eLeftBrace, "{"),
				Parser::Token(Parser::eRightBrace, "}"),
				Parser::Token(Parser::eSpace, "\n"),
				Parser::Token(Parser::eEqualTo,	"=="),
				Parser::Token(Parser::eWord, "A"),
				Parser::Token(Parser::eNotEqualTo, "!="),
				Parser::Token(Parser::eWord, "B"),
				Parser::Token(Parser::eGreaterEqualTo, ">="),
				Parser::Token(Parser::eWord, "C"),
				Parser::Token(Parser::eLessEqualTo, "<="),
				Parser::Token(Parser::eWord, "D"),
				Parser::Token(Parser::eSumEquals, "+="),
				Parser::Token(Parser::eWord, "E"),
				Parser::Token(Parser::eMinusEquals, "-="),
				Parser::Token(Parser::eWord, "F"),
				Parser::Token(Parser::eIncrement, "++"),
				Parser::Token(Parser::eWord, "G"),
				Parser::Token(Parser::eDecrement, "--"),
				Parser::Token(Parser::eWord, "HI"),
				// Parser::Token(Parser::ePointer, "->"),
				// Parser::Token(Parser::eWord, "I"),
				Parser::Token(Parser::eShiftLeft, "<<"),
				Parser::Token(Parser::eWord, "J"),
				Parser::Token(Parser::eShiftRight, ">>"),
				Parser::Token(Parser::eWord, "K"),
				Parser::Token(Parser::eMultiplyEquals, "*="),
				Parser::Token(Parser::eWord, "L"),
				Parser::Token(Parser::eDivideEquals, "/="),
				Parser::Token(Parser::eWord, "M"),
				Parser::Token(Parser::eModulusEquals, "%="),
				Parser::Token(Parser::eWord, "N"),
				Parser::Token(Parser::eBitwiseAndEquals, "&="),
				Parser::Token(Parser::eWord, "O"),
				Parser::Token(Parser::eBitwiseOrEquals, "|="),
				Parser::Token(Parser::eWord, "P"),
				Parser::Token(Parser::eBitwiseXorEquals, "^="),
				Parser::Token(Parser::eWord, "Q"),
				Parser::Token(Parser::eBitwiseNotEquals, "~="),
				Parser::Token(Parser::eWord, "R"),
				Parser::Token(Parser::eLessThan, "<"),
				Parser::Token(Parser::eWord, "S"),
				Parser::Token(Parser::eGreaterThan, ">"),
				Parser::Token(Parser::eWord, "T"),
				Parser::Token(Parser::eShiftRightAssign, ">>="),
				Parser::Token(Parser::eWord, "U"),
				Parser::Token(Parser::eShiftLeftAssign, "<<="),
				Parser::Token(Parser::eWord, "V"),
				Parser::Token(Parser::eDivide, "/"),
				Parser::Token(Parser::eWord, "W"),
				Parser::Token(Parser::eMultiply, "*"),
				Parser::Token(Parser::eWord, "X"),
				Parser::Token(Parser::ePlus, "+"),
				Parser::Token(Parser::eWord, "Y"),
				Parser::Token(Parser::eMinus, "-"),
				Parser::Token(Parser::eWord, "Z"),
				Parser::Token(Parser::eBooleanAnd, "&&"),
				Parser::Token(Parser::eWord, "a"),
				Parser::Token(Parser::eBooleanOr, "||"),
				Parser::Token(Parser::eWord, "b"),
				Parser::Token(Parser::eBooleanNot, "!"),
				Parser::Token(Parser::eWord, "c"),
				Parser::Token(Parser::eQuestionMark, "?"),
				Parser::Token(Parser::eWord, "d"),
				Parser::Token(Parser::eColon, ":"),
				Parser::Token(Parser::eWord, "e"),
				Parser::Token(Parser::eBooleanNot, "!"),
				Parser::Token(Parser::eWord, "f"),
				Parser::Token(Parser::eModulus, "%"),
				Parser::Token(Parser::eWord, "g"),
				Parser::Token(Parser::eBitwiseXor, "^"),
				Parser::Token(Parser::eWord, "h"),
				Parser::Token(Parser::eBitwiseAnd, "&"),
				Parser::Token(Parser::eWord, "i"),
				Parser::Token(Parser::eBitwiseOr, "|"),
				Parser::Token(Parser::eWord, "j"),
				Parser::Token(Parser::eEquals, "="),
				Parser::Token(Parser::eWord, "k"),
				Parser::Token(Parser::ePeriod, "."),
				Parser::Token(Parser::eWord, "l"),
				Parser::Token(Parser::ePointer, "->"),
				Parser::Token(Parser::eWord, "m"),
				Parser::Token(Parser::eEquals, "=")
			};
			Parser::TokenStream ts(ss);
			for ( const Parser::Token& token: expected_tokens ) {
				Parser::Token next_token = ts.next();
				UNITTEST_EQUALS(next_token.toString(), token.toString());
			}
		}
    //--- Tools::String getWhiteSpace(void) { return whitespace; }
		{	Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
			Parser::Token token = ts.current();
			UNITTEST_EQUALS(token.token_type, Parser::eSpace);
			UNITTEST_EQUALS(token.token_text, "  ");
			UNITTEST_ASSERT(!token.isEmpty());
			UNITTEST_ASSERT(!token.isEOF());
			UNITTEST_ASSERT(token.isSpace());
			UNITTEST_ASSERT(token);
		}
    //--- Tools::String getText(void) { return whitespace + current_token.token_text; }
		{	Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
			Parser::Token token = ts.current();
			UNITTEST_EQUALS(ts.getText(), "  ");
			ts.next(); // Consume "  "
			token = ts.current();
			UNITTEST_EQUALS(ts.getText(), "Hello");
			ts.next(); // Consume "Hello"
			token = ts.current();
			UNITTEST_EQUALS(ts.getText(), ",");

		}
    //--- Tools::String toString(void) const;
		{	Parser::StringStream ss("  Hello, World!  ");
			UNITTEST_EQUALS(ss.toString(), "[\"  Hello, World!  \": -1]");
		}

		{	const Tools::String sample_code =
					"class  StringStream: public CharStream {\n"
					"        Tools::String text1;\n"
					"        uint index;\n"
					"\n"
					"//--- Constructors and Destructor ----------------------------------------------------------------\n"
					"        public:\n"
					"            StringStream(const Tools::String& text2): "
										"text1(text2), index(0) {} /* stringstream constructor */\n"
					"            StringStream(const StringStream& stream): "
										"text1(stream.text1), index(stream.index) {}\n"
					"            virtual ~StringStream(void) {}\n"
					"==A!=B>=C<=D+=E-=F++G--H->I<<J>>K*=L/=M%=N&=O|=P^=Q~=R"
					"<S>T>>=U<<=V/W*X+Y-Z&&a||b!c?d:e%f^g&h|i=j.k->"
				;
			Parser::StringStream ss(sample_code);
			Parser::TokenStream ts(ss);
			Parser::Token token = ts.current();
			Tools::String result;
			while ( !token.isEOF() ) {
				result += token.token_text;
				token = ts.next();
			}
			UNITTEST_EQUALS(result, sample_code);
		}
	}
	void unittests_Stream(void) {
		unittests_StringStream();
		unittests_Token();
		unittests_TokenStream();
	}
}
