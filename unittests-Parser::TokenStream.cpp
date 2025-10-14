#include "UnitTests.hpp"
#include "TokenStream.hpp"

namespace UnitTests {

//=== class StringStream ===================================================================================================================================
	void unittests_StringStream(void) {
	//--- StringStream(const Tools::String& string): stream(string) {}
		{	Parser::StringStream ss("  Hello, World!  ");
			// UNITTEST_EQUALS((const char*)ss.getText(), "  Hello, World!  ");
			UNITTEST_EQUALS(ss.peek(1), ' ');
			UNITTEST_EQUALS(ss.peek(2), ' ');
			UNITTEST_EQUALS(ss.peek(3), 'H');
			UNITTEST_EQUALS(ss.peek(4), 'e');
			UNITTEST_EQUALS(ss.peek(5), 'l');
			UNITTEST_EQUALS(ss.peek(6), 'l');
			UNITTEST_EQUALS(ss.peek(7), 'o');
			UNITTEST_EQUALS(ss.peek(8), ',');
			UNITTEST_EQUALS(ss.peek(9), ' ');
			UNITTEST_EQUALS(ss.peek(10), 'W');
			UNITTEST_EQUALS(ss.peek(11), 'o');
			UNITTEST_EQUALS(ss.peek(12), 'r');
			UNITTEST_EQUALS(ss.peek(13), 'l');
			UNITTEST_EQUALS(ss.peek(14), 'd');
			UNITTEST_EQUALS(ss.peek(15), '!');
			UNITTEST_EQUALS(ss.peek(16), ' ');
			UNITTEST_EQUALS(ss.peek(17), ' ');
			UNITTEST_EQUALS(ss.peek(18), '\0');
			UNITTEST_EQUALS(ss.peek(19), '\0');
			UNITTEST_EQUALS(ss.peek(20), '\0');
			UNITTEST_EQUALS(ss.peek(-1), '\0');
			UNITTEST_EQUALS(ss.peek(-2), '\0');
			UNITTEST_EQUALS(ss.peek(-3), '\0');
			for ( int i = 1; i <= 16; i++ ) {
				ss.next();
			}
			UNITTEST_EQUALS(ss.peek(1), '\0');
			UNITTEST_EQUALS(ss.peek(2), '\0');
			UNITTEST_EQUALS(ss.peek(3), '\0');
			UNITTEST_EQUALS(ss.peek(-1), '!');
			UNITTEST_EQUALS(ss.peek(-2), 'd');
			UNITTEST_EQUALS(ss.peek(-3), 'l');
			UNITTEST_EQUALS(ss.peek(-4), 'r');
			UNITTEST_EQUALS(ss.peek(-5), 'o');
		}
	//--- StringStream(const StringStream& stream): text(stream.text), index(stream.index) {}
		{
		}
	//--- char peek(int offset=0) override;
		{
		}
	//--- //bool peek(const Tools::String& test, Stream& consumer) override;
		{
		}
    //--- bool peek(const Tools::String& test, bool consume = false) override;
		{
		}
    //--- char current(void) override;
		{
		}
    //--- char next(void) override;
		{
		}
    //--- void skip(int offset) override;
		{
		}
    //--- //uint getLineNumber(void) const override;
		{
		}
 	//--- bool isSpace(void) override;
		{
		}
    //--- bool isEOL(void) override;
		{
		}
    //--- bool isEOF(void) override;
		{
		}
	//--- void testPrint(int linenum) const;
		{
		}
    //--- Tools::String toString(void) const;
		{
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
			UNITTEST_ASSERT(token.isSpace());
			UNITTEST_ASSERT(!token);
		}
	//--- explicit Token(char letter);
		{	Parser::Token token('A');
			UNITTEST_EQUALS(token.token_type, (Parser::EToken)'A');
			UNITTEST_EQUALS(token.token_text, "");
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
		}
	//--- TokenStream(const StringStream& stream): stream(stream) {}
		{	Parser::StringStream ss("  Hello, World!  ");
			Parser::TokenStream ts(ss);
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
			ts.next(); // Consume "Hello"
			UNITTEST_ASSERT(ts.peek(", Wo"));
			ts.next(); // Consume ","
			UNITTEST_ASSERT(ts.peek(" World"));
		}
	//--- EToken peek(int index) { return ((EToken)stream.peek(index)); }
		{	Parser::StringStream ss("  Hello, World!  ");

		}
	//--- bool peek(char token) { return (stream.peek(1) == token); }
		{	Parser::StringStream ss("  Hello, World!  ");

		}
    //--- Token next(void);
		{	Parser::StringStream ss("  Hello, World!  ");

		}
    //--- Token current(void);
		{	Parser::StringStream ss("  Hello, World!  ");

		}
    //--- Tools::String getWhiteSpace(void) { return whitespace; }
		{	Parser::StringStream ss("  Hello, World!  ");

		}
    //--- Tools::String getText(void) { return whitespace + current_token.token_text; }
		{	Parser::StringStream ss("  Hello, World!  ");

		}
    //--- Tools::String toString(void) const;
		{	Parser::StringStream ss("  Hello, World!  ");
			UNITTEST_EQUALS(ss.toString(), "  Hello, World!  ");
		}
	}
	void unittests_Stream(void) {
		unittests_StringStream();
		unittests_Token();
		unittests_TokenStream();
	}
}
