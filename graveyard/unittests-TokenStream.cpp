#include "TokenStream.hpp"
#include "UnitTests.hpp"

namespace UnitTests {

//=== class TokenStream =============================================================================================================================
// 	void test_TokenStream(void) {
// 	//---	TokenStream(Stream *stream);
// 	//---	virtual ~TokenStream(void);
// 	//---	virtual Token current(void);
// 	//---	virtual Token next(void);
// 	//---	virtual bool  isEOF(void);
// 		{	const char *test_string_doublequote = "\"test string\"";
// 			Parser::TokenStream stream(test_string_doublequote);
// 			UNITTEST_EQUALS(stream.next(), Parser::Token(Parser::eDoubleQuote, test_string_doublequote));
// 		}
// 		{ 	Parser::TokenStream stream1("LastModifiedDateTime\"05/07_2010 21:36:12.0000\"");
// 			UNITTEST_EQUALS(stream1.next(), Parser::Token(Parser::eWord, "LastModifiedDateTime"));
// 			UNITTEST_EQUALS(stream1.next(), Parser::Token(Parser::eDoubleQuote, "\"05/07_2010 21:36:12.0000\""));
// 			Parser::TokenStream stream2("word\"test string\"12345");
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eWord, "word"));
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eDoubleQuote, "\"test string\""));
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eNumber, "12345"));
// 			Parser::TokenStream stream3("!\"test string\"&");
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eBang, "!"));
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eDoubleQuote, "\"test string\""));
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eAmpersand, "&"));
// 		}
// 		{ 	Parser::TokenStream stream1("word'test string'");
// 			UNITTEST_EQUALS(stream1.next(), Parser::Token(Parser::eWord, "word"));
// 			UNITTEST_EQUALS(stream1.next(), Parser::Token(Parser::eSingleQuote, "'test string'"));
// 			Parser::TokenStream stream2("word'test string'12345");
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eWord, "word"));
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eSingleQuote, "'test string'"));
// 			UNITTEST_EQUALS(stream2.next(), Parser::Token(Parser::eNumber, "12345"));
// 			Parser::TokenStream stream3("!'test string'&");
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eBang, "!"));
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eSingleQuote, "'test string'"));
// 			UNITTEST_EQUALS(stream3.next(), Parser::Token(Parser::eAmpersand, "&"));
// 		}
// 		{
// 			static const char *test_string =
// 					"`~!!@#$%^&*()-=+[{]}\\|;:,<..>/?"
// 					" 0 1 2 3 4 5 6 7 8 9"
// 					" a b c d e f g h i j k l m n o p q r s t u v w x y z"
// 					" A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
// 					" _";
// 			Parser::TokenStream *stream = new Parser::TokenStream(test_string);
// 			UNITTEST_EQUALS(stream->current(), Parser::Token(Parser::eBackQuote, "`"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eTilde, "~"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eBang, "!"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eBang, "!"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eAt, "@"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eHash, "#"));
// 			UNITTEST_EQUALS(stream->current(), Parser::Token(Parser::eHash, "#"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDollar, "$"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::ePercent, "%"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eCircumflex, "^"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eAmpersand, "&"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eAsterix, "*"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eLeftParenthesis, "("));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eRightParenthesis, ")"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eHyphen, "-"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eEquals, "="));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::ePlus, "+"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eLeftBracket, "["));
// 			UNITTEST_EQUALS(stream->current(), Parser::Token(Parser::eLeftBracket, "["));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eLeftBrace, "{"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eRightBracket, "]"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eRightBrace, "}"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eBackslash, "\\"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eVerticalBar, "|"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eSemicolon, ";"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eColon, ":"));
// //			UNITTEST_EQUALS(stream->next(), Token(Parser::eSingleQuote, "'"));
// //			UNITTEST_EQUALS(stream->next(), Token(Parser::eDoubleQuote, "\""));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eComma, ","));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eLeftAngleBracket, "<"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::ePeriod, "."));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::ePeriod, "."));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eRightAngleBracket, ">"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eSlash, "/"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eQuestionMark, "?"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "0"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "1"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "2"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "3"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "4"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "5"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "6"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "7"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "8"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eDigit, "9"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eAlphaNumeric, "a"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "b"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "c"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "d"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "e"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "f"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "g"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "h"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "i"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "j"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "k"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "l"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "m"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "n"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "o"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "p"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "q"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "r"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "s"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "t"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "u"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "v"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "w"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "x"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "y"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "z"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "A"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "B"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "C"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "D"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "E"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "F"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "G"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "H"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "I"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "J"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "K"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "L"));
// 			// stream->setBookmark();
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "M"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "N"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "O"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "P"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "Q"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "R"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "S"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "T"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "U"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "V"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "W"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "X"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "Y"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "Z"));
// 			UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "_"));
// 			UNITTEST_ASSERT(stream->next().isEOF());
// 			// stream->recallBookmark();
// 			// UNITTEST_EQUALS(stream->current(), Parser::Token(Parser::eWord, "M"));
// 			// UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "N"));
// 			// UNITTEST_EQUALS(stream->next(), Parser::Token(Parser::eWord, "O"));
// 			// stream->recallBookmark(); // <-- recall*() without a set*() resets to the beginning of the stream!
// 			// UNITTEST_EQUALS(stream->current(), Parser::Token(Parser::eBackQuote, "`"));
// 			delete stream;
// 		}

// 	//---	TokenStream(const Tools::String& string);
// 	//---	void TokenStream::scoopString(void);
// 		// {	Parser::TokenStream *stream = new Parser::TokenStream("'hi'");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token(Parser::eChar, "'hi'"));
// 		// 	delete stream;

// 		// 	stream = new Parser::TokenStream("'hi");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token(Parser::eChar, "'hi"));
// 		// 	delete stream;

// 		// 	stream = new Parser::TokenStream("'\"hi'");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token(Parser::eChar, "'\"hi'"));
// 		// 	delete stream;
// 		// }
// 		// {	Parser::TokenStream *stream = new Parser::TokenStream("\"hi\"");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token('str', "\"hi\""));
// 		// 	delete stream;

// 		// 	stream = new Parser::TokenStream("\"hi");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token('str', "\"hi"));
// 		// 	delete stream;

// 		// 	stream = new Parser::TokenStream("\"'hi\"");
// 		// 	UNITTEST_EQUALS(stream->scoopString(""), Token('str', "\"'hi\""));
// 		// 	delete stream;
// 		// }

// 	//---	void TokenStream::scoopWord(void);
// 		// {	Parser::TokenStream stream("");
// 		// 	UNITTEST_EQUALS(stream.scoopWord(""), Parser::EToken::eEOF);
// 		// }
// 		// {	Parser::TokenStream stream("boingus");
// 		// 	UNITTEST_EQUALS(stream.scoopWord(""), Parser::Token('word', "boingus", ""));
// 		// }
// 		// {	Parser::TokenStream stream("boingus ");
// 		// 	UNITTEST_EQUALS(stream.scoopWord(""), Token('word', "boingus", ""));
// 		// }
// 		// {	Parser::TokenStream stream("boingus>");
// 		// 	UNITTEST_EQUALS(stream.scoopWord(""), Token('word', "boingus", ""));
// 		// }

// 	//---	void TokenStream::scoopDigits(char *str, uint& index, uint MAX);
// 		// {	Tools::String acc;
// 		// 	Parser::TokenStream("").scoopDigits(acc);
// 		// 	UNITTEST_EQUALS(acc.toString(), "")

// 		// 	acc.clear();
// 		// 	Parser::TokenStream("1").scoopDigits(acc);
// 		// 	UNITTEST_EQUALS(acc.toString(), "1")

// 		// 	acc.clear();
// 		// 	Parser::TokenStream("1 ").scoopDigits(acc);
// 		// 	UNITTEST_EQUALS(acc.toString(), "1")

// 		// 	acc.clear();
// 		// 	Parser::TokenStream("1234567890").scoopDigits(acc);
// 		// 	UNITTEST_EQUALS(acc.toString(), "1234567890")

// 		// 	acc.clear();
// 		// 	Parser::TokenStream(" 1 ").scoopDigits(acc);
// 		// 	UNITTEST_EQUALS(acc.toString(), "")
// 		// }

// 	//---	void TokenStream::scoopNumber(void);
// 	// 	{	Parser::TokenStream stream("");
// 	// 		stream.scoopNumber("");
// 	// 		UNITTEST_ASSERT(stream.isEOF());
// 	// 	}
// 	// 	{	TokenStream stream("01234");
// 	// //		UNITTEST_EQUALS(stream.scoopNumber(""), Token(Parser::eNumber, "01234", ""));
// 	// 		UNITTEST_EQUALS(stream.next(), Token(Parser::eNumber, "01234", ""));
// 	// 		UNITTEST_ASSERT(stream.next().isEOF());
// 	// 	}

// 	//---	bool TokenStream::scoopSpace(void);
// 		// {	Parser::TokenStream stream(" \t\n\r\f1234");
// 		// 	Tools::String spaces = stream.scoopSpace();
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(spaces), Token(Parser::eNumber, "1234", " \t\n\r\f"));
// 		// 	UNITTEST_ASSERT(stream.next().isEOF());
// 		// }
// 		// {	Parser::TokenStream stream("0 1234\t1111");
// 		// 	Tools::String spaces = stream.scoopSpace();
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(spaces), Token(Parser::eNumber, "0", ""));
// 		// 	spaces = stream.scoopSpace();
// 		// 	UNITTEST_EQUALS(spaces, " ");
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(spaces), Token(Parser::eNumber, "1234", " "));
// 		// 	spaces = stream.scoopSpace();
// 		// 	UNITTEST_EQUALS(spaces, "\t");
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(spaces), Token(Parser::eNumber, "1111", "\t"));
// 		// }
// 		// {	Parser::TokenStream stream("1234.");
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(""), Token(Parser::eNumber, "1234", ""));
// 		// }
// 		// {	Parser::TokenStream stream("1234e");
// 		// 	UNITTEST_EQUALS(stream.scoopNumber(""), Token(Parser::eNumber, "1234", ""));
// 		// }

// 	//---	bool TokenStream::isEOF(void);
// 		// {	Parser::TokenStream stream("");
// 		// 	UNITTEST_ASSERT(stream.isEOF());
// 		// }

// 	//---	Token TokenStream::current(void); -------------------------------------------------------------------------------------
// 	//---	Token TokenStream::next(void);
// 		{	Parser::TokenStream stream("");
// 			UNITTEST_EQUALS(stream.current(), Parser::Token(Parser::eEOF));
// 		}
// 		{	Parser::TokenStream stream("abc");
// 			UNITTEST_EQUALS(stream.current(), Parser::Token('word', "abc"));
// 			UNITTEST_EQUALS(stream.current(), Parser::Token('word', "abc"));
// 		}

// 	//---	Tools::String TokenStream::toString(void) const; -----------------------------------------------------------------------------
// 		{	Parser::TokenStream stream1("");
// 			UNITTEST_PATTERN(stream1.toString(), "[[]TokenStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
// 			stream1.current();
// 			UNITTEST_PATTERN(stream1.toString(), "[[]TokenStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
// 			Parser::TokenStream stream2("abc");
// 			stream2.current();
// 			UNITTEST_PATTERN(stream2.toString(), "[[]TokenStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
// 		}

// 	//---	Tools::String TokenStream::serialize(void) const; -----------------------------------------------------------------------------
// 		// {	Parser::TokenStream stream1("");

// 		// 	UNITTEST_EQUALS(stream1.serialize(),
// 		// 			"{"
// 		// 				"\"TokenStream\": {"
// 		// 					"\"current_token\": {"
// 		// 						"\"Token\": {"
// 		// 							"\"type\": \"'NULL'\", "
// 		// 							"\"text\": \"\", "
// 		// 							"\"whitespace\": \"\""
// 		// 						"}"
// 		// 					"}, "
// 		// 					"\"stream\": {"
// 		// 						"\"StringStream\": {"
// 		// 							"\"position\": \"0\", "
// 		// 							"\"bookmark\": \"0\", "
// 		// 							"\"string\": \"\""
// 		// 						"}"
// 		// 					"}"
// 		// 				"}"
// 		// 			"}");
// 		// 	stream1.current();
// 		// 	UNITTEST_EQUALS(stream1.serialize(),
// 		// 			"{"
// 		// 				"\"TokenStream\": {"
// 		// 					"\"current_token\": {"
// 		// 						"\"Token\": {"
// 		// 							"\"type\": \"' EOF'\", "
// 		// 							"\"text\": \"EOF\", "
// 		// 							"\"whitespace\": \"\""
// 		// 						"}"
// 		// 					"}, "
// 		// 					"\"stream\": {"
// 		// 						"\"StringStream\": {"
// 		// 							"\"position\": \"0\", "
// 		// 							"\"bookmark\": \"0\", "
// 		// 							"\"string\": \"\""
// 		// 						"}"
// 		// 					"}"
// 		// 				"}"
// 		// 			"}");
// 		// 	Parser::TokenStream stream2("abc");
// 		// 	stream2.current();
// 		// 	UNITTEST_EQUALS(stream2.serialize(),
// 		// 			"{"
// 		// 				"\"TokenStream\": {"
// 		// 					"\"current_token\": {"
// 		// 						"\"Token\": {"
// 		// 							"\"type\": \"'word'\", "
// 		// 							"\"text\": \"abc\", "
// 		// 							"\"whitespace\": \"\""
// 		// 						"}"
// 		// 					"}, "
// 		// 					"\"stream\": {"
// 		// 						"\"StringStream\": {"
// 		// 							"\"position\": \"3\", "
// 		// 							"\"bookmark\": \"0\", "
// 		// 							"\"string\": \"abc\""
// 		// 						"}"
// 		// 					"}"
// 		// 				"}"
// 		// 			"}");
// 		// }

// 	//---	void TokenStream::mustBe(std::set<Token> tokens); ---------------------------------------------------------------------
// 		// {	Tools::String tag_tokenStream_test1("<my_tag>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));

// 		// //--- Positive: looking for '<'
// 		// 	try {
// 		// 		Parser::Token token = stream.mustBe(std::set<Token>{Token(Parser::eLeftAngleBracket), Token(Parser::eLeftBrace)});
// 		// 		PASS();
// 		// 		UNITTEST_EQUALS(token, Token(Parser::eLeftAngleBracket));

// 		// 	} catch ( const Tools::String& err ) {
// 		// 		FAIL("Should not have thrown!");
// 		// 	}

// 		// //--- Positive: looking for eWord:"my_tag"
// 		// 	try {
// 		// 		Parser::Token token = stream.mustBe(std::set<Token>{Token(Parser::eWord)});
// 		// 		PASS();
// 		// 		UNITTEST_EQUALS(token, Token(Parser::eWord, "my_tag"));
// 		// 	} catch ( const Tools::String& err ) {
// 		// 		FAIL("Should have thrown because we're looking at text!");
// 		// 	}

// 		// //--- Positive: looking for '>'
// 		// 	try {
// 		// 		Parser::Token token = stream.mustBe(std::set<Token>{Token(Parser::eRightAngleBracket), Token(Parser::eRightBrace)});
// 		// 		PASS();
// 		// 		UNITTEST_EQUALS(token, Token(Parser::eRightAngleBracket));

// 		// 	} catch ( const Tools::String& err ) {
// 		// 		FAIL("Should not have thrown!");
// 		// 	}

// 		// //--- Negative
// 		// 	try {
// 		// 		Parser::Token token = stream.mustBe(std::set<Token>{Token(Parser::eLeftAngleBracket)});
// 		// 		FAIL("Should have thrown because we're now at EOT! Instead seeing: " + token.toString());

// 		// 	} catch ( const Tools::String& err ) {
// 		// 		PASS();
// 		// 	}
// 		// }

// 	//---	void TokenStream::mustBe(const Token& token); -------------------------------------------------------------------------
// 		// {	Tools::String tag_tokenStream_test1("<t>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));
// 		// 	try {
// 		// 		stream.mustBe(Token(Parser::eLeftAngleBracket));
// 		// 		PASS();
// 		// 	} catch ( const Tools::String& err ) {
// 		// 		std::cerr << err << std::endl;
// 		// 		FAIL("Should not have thrown!");
// 		// 	}

// 		// 	try {
// 		// 		stream.mustBe(Token(Parser::eLeftAngleBracket));
// 		// 		FAIL("Should have thrown because we're now looking at text!");
// 		// 	} catch ( const Tools::String& err ) {
// 		// 		PASS();
// 		// 	}

// 		// 	try {
// 		// 		stream.mustBe(Token(Parser::eWord));
// 		// 		PASS();
// 		// 	} catch ( const Tools::String& err ) {
// 		// 		std::cerr << err << std::endl;
// 		// 		Tools::String msg = Tools::String::formatString("Should have thrown because we're looking at 'text' (actually seeing %s)!", stream.current().toString().getText());
// 		// 		FAIL(msg.getText());
// 		// 	}
// 		// }

// 	//---	bool TokenStream::mayBe(std::set<Token> tokens);
// 		// {	Tools::String tag_tokenStream_test1("<t>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));
// 		// 	UNITTEST_EQUALS(stream.mayBe(std::set<Token>{Token(Parser::eLeftAngleBracket)}), Token(Parser::eLeftAngleBracket));
// 		// 	UNITTEST_EQUALS(stream.mayBe(std::set<Token>{Token(Parser::eWord)}), Token(Parser::eWord, "t"));
// 		// 	UNITTEST_EQUALS(stream.mayBe(std::set<Token>{Token(Parser::eRightAngleBracket)}), Token(Parser::eRightAngleBracket));
// 		// }
// 		// {	Tools::String tag_tokenStream_test1("<t>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));
// 		// 	UNITTEST_EQUALS(stream.mayBe(std::set<Token>{Token(Parser::eLeftParen)}), Token());
// 		// }

// 	//---	bool TokenStream::mayBe(const Token& token);
// 		// {	Tools::String tag_tokenStream_test1("<t>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));
// 		// 	UNITTEST_EQUALS(stream.mayBe(Token(Parser::eLeftAngleBracket)), Token(Parser::eLeftAngleBracket));
// 		// 	UNITTEST_EQUALS(stream.mayBe(Token(Parser::eWord)), Token(Parser::eWord, "t"));
// 		// 	UNITTEST_EQUALS(stream.mayBe(Token(Parser::eRightAngleBracket)), Token(Parser::eRightAngleBracket));
// 		// }
// 		// {	Tools::String tag_tokenStream_test1("<t>");
// 		// 	Parser::TokenStream stream(new StringStream(tag_tokenStream_test1));
// 		// 	UNITTEST_EQUALS(stream.mayBe(Token(Parser::eNumber)), Token());
// 		// }

// 	//---	friend std::ostream& TokenStream::operator<<(std::ostream& stream, const TokenStream& tokens);
// 		// {	std::ostringstream output;
// 		// 	Tools::String text("this is a test");
// 		// 	Parser::TokenStream stream(text);
// 		// 	while ( !stream.isEOF() ) {
// 		// 		stream.next();
// 		// 		Parser::Token token = stream.current();
// 		// 		output << token.whitespace << token.text;
// 		// 	}
// 		// 	UNITTEST_EQUALS(output.str(), text);
// 		// }
// 	}
}