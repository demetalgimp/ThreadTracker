#include "TokenStream.hpp"
#include "UnitTests.hpp"

namespace UnitTests
{
//=== class StringStream ============================================================================================================================
	// void test_StringStream(void) {
	// //---	virtual int  back(void);
	// //---	virtual int  current(void);
	// //---	virtual int  next(void);
	// 	{	const char *test_string = "`~!@#$%^&*()-=+[{]}\\|;:'\",<.>/?0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ _";
	// 		Parser::Stream *stream = new Parser::StringStream(test_string);
	// 		UNITTEST_EQUALS(stream->next(), '`');
	// 		UNITTEST_EQUALS(stream->next(), '~');
	// 		UNITTEST_EQUALS(stream->next(), '!');
	// 		UNITTEST_EQUALS(stream->next(), '@');
	// 		UNITTEST_EQUALS(stream->current(), '@');
	// 		UNITTEST_EQUALS(stream->next(), '#');
	// 		UNITTEST_EQUALS(stream->next(), '$');
	// 		UNITTEST_EQUALS(stream->next(), '%');
	// 		UNITTEST_EQUALS(stream->next(), '^');
	// 		UNITTEST_EQUALS(stream->next(), '&');
	// 		UNITTEST_EQUALS(stream->next(), '*');
	// 		UNITTEST_EQUALS(stream->next(), '(');
	// 		UNITTEST_EQUALS(stream->next(), ')');
	// 		// UNITTEST_EQUALS(stream->back(), '('); // <-- back()
	// 		// UNITTEST_EQUALS(stream->next(), ')');
	// 		UNITTEST_EQUALS(stream->next(), '-');
	// 		UNITTEST_EQUALS(stream->next(), '=');
	// 		UNITTEST_EQUALS(stream->next(), '+');
	// 		UNITTEST_EQUALS(stream->next(), '[');
	// 		UNITTEST_EQUALS(stream->next(), '{');
	// 		UNITTEST_EQUALS(stream->current(), '{');
	// 		UNITTEST_EQUALS(stream->next(), ']');
	// 		UNITTEST_EQUALS(stream->next(), '}');
	// 		UNITTEST_EQUALS(stream->next(), '\\');
	// 		UNITTEST_EQUALS(stream->next(), '|');
	// 		UNITTEST_EQUALS(stream->next(), ';');
	// 		UNITTEST_EQUALS(stream->next(), ':');
	// 		UNITTEST_EQUALS(stream->next(), '\'');
	// 		UNITTEST_EQUALS(stream->next(), '"');
	// 		UNITTEST_EQUALS(stream->next(), ',');
	// 		UNITTEST_EQUALS(stream->next(), '<');
	// 		UNITTEST_EQUALS(stream->next(), '.');
	// 		UNITTEST_EQUALS(stream->next(), '>');
	// 		UNITTEST_EQUALS(stream->next(), '/');
	// 		UNITTEST_EQUALS(stream->next(), '?');
	// 		UNITTEST_EQUALS(stream->next(), '0');
	// 		UNITTEST_EQUALS(stream->next(), '1');
	// 		UNITTEST_EQUALS(stream->next(), '2');
	// 		UNITTEST_EQUALS(stream->next(), '3');
	// 		UNITTEST_EQUALS(stream->next(), '4');
	// 		UNITTEST_EQUALS(stream->next(), '5');
	// 		UNITTEST_EQUALS(stream->next(), '6');
	// 		UNITTEST_EQUALS(stream->next(), '7');
	// 		UNITTEST_EQUALS(stream->next(), '8');
	// 		UNITTEST_EQUALS(stream->next(), '9');
	// 		UNITTEST_EQUALS(stream->current(), '9');
	// 		UNITTEST_EQUALS(stream->next(), 'a');
	// 		UNITTEST_EQUALS(stream->next(), 'b');
	// 		UNITTEST_EQUALS(stream->next(), 'c');
	// 		UNITTEST_EQUALS(stream->next(), 'd');
	// 		UNITTEST_EQUALS(stream->current(), 'd');
	// 		UNITTEST_EQUALS(stream->next(), 'e');
	// 		UNITTEST_EQUALS(stream->next(), 'f');
	// 		UNITTEST_EQUALS(stream->next(), 'g');
	// 		UNITTEST_EQUALS(stream->next(), 'h');
	// 		UNITTEST_EQUALS(stream->next(), 'i');
	// 		UNITTEST_EQUALS(stream->next(), 'j');
	// 		UNITTEST_EQUALS(stream->next(), 'k');
	// 		UNITTEST_EQUALS(stream->next(), 'l');
	// 		UNITTEST_EQUALS(stream->next(), 'm');
	// 		UNITTEST_EQUALS(stream->next(), 'n');
	// 		UNITTEST_EQUALS(stream->next(), 'o');
	// 		UNITTEST_EQUALS(stream->next(), 'p');
	// 		UNITTEST_EQUALS(stream->next(), 'q');
	// 		UNITTEST_EQUALS(stream->next(), 'r');
	// 		UNITTEST_EQUALS(stream->next(), 's');
	// 		UNITTEST_EQUALS(stream->next(), 't');
	// 		UNITTEST_EQUALS(stream->next(), 'u');
	// 		UNITTEST_EQUALS(stream->next(), 'v');
	// 		UNITTEST_EQUALS(stream->next(), 'w');
	// 		UNITTEST_EQUALS(stream->next(), 'x');
	// 		UNITTEST_EQUALS(stream->next(), 'y');
	// 		UNITTEST_EQUALS(stream->next(), 'z');
	// 		// stream->setBookmark();
	// 		UNITTEST_EQUALS(stream->next(), 'A');
	// 		UNITTEST_EQUALS(stream->next(), 'B');
	// 		UNITTEST_EQUALS(stream->next(), 'C');
	// 		UNITTEST_EQUALS(stream->next(), 'D');
	// 		UNITTEST_EQUALS(stream->next(), 'E');
	// 		UNITTEST_EQUALS(stream->next(), 'F');
	// 		UNITTEST_EQUALS(stream->next(), 'G');
	// 		UNITTEST_EQUALS(stream->next(), 'H');
	// 		UNITTEST_EQUALS(stream->next(), 'I');
	// 		UNITTEST_EQUALS(stream->next(), 'J');
	// 		UNITTEST_EQUALS(stream->next(), 'K');
	// 		UNITTEST_EQUALS(stream->next(), 'L');
	// 		UNITTEST_EQUALS(stream->next(), 'M');
	// 		UNITTEST_EQUALS(stream->next(), 'N');
	// 		UNITTEST_EQUALS(stream->next(), 'O');
	// 		UNITTEST_EQUALS(stream->next(), 'P');
	// 		UNITTEST_EQUALS(stream->next(), 'Q');
	// 		UNITTEST_EQUALS(stream->next(), 'R');
	// 		UNITTEST_EQUALS(stream->next(), 'S');
	// 		UNITTEST_EQUALS(stream->next(), 'T');
	// 		UNITTEST_EQUALS(stream->next(), 'U');
	// 		UNITTEST_EQUALS(stream->next(), 'V');
	// 		UNITTEST_EQUALS(stream->next(), 'W');
	// 		UNITTEST_EQUALS(stream->next(), 'X');
	// 		UNITTEST_EQUALS(stream->next(), 'Y');
	// 		UNITTEST_EQUALS(stream->next(), 'Z');
	// 		UNITTEST_EQUALS(stream->next(), ' ');
	// 		UNITTEST_EQUALS(stream->next(), '_');
	// 		// stream->recallBookmark();
	// 		// UNITTEST_EQUALS(stream->next(), 'z');
	// 		// stream->recallBookmark();
	// 		// UNITTEST_EQUALS(stream->current(), '`');
	// 		// stream->recallBookmark();
	// 		// UNITTEST_EQUALS(stream->next(), '`');
	// 		delete stream;
	// 	}

	// //--- StringStream::StringStream(const String& string): string(string) {}
	// 	{
	// 		UNITTEST_EQUALS(Parser::StringStream(Tools::String("unit test")).current(), 'u');
	// 		UNITTEST_EQUALS(Parser::StringStream(Tools::String("test")).next(), 't');
	// 		UNITTEST_EQUALS(Parser::StringStream(Tools::String()).next(), -1);
	// 	}

	// //--- virtual int StringStream::back(void);
	// //--- virtual int StringStream::next(void);
	// //--- virtual int StringStream::current(void);
	// 	{	Parser::Stream *stream = new Parser::StringStream("123\n456");
	// 		UNITTEST_EQUALS(stream->getLineNumber(), 1u);
	// 		UNITTEST_EQUALS(stream->current(), '1');
	// 		UNITTEST_EQUALS(stream->next(), '2');
	// 		// UNITTEST_EQUALS(stream->back(), '1');
	// 		// UNITTEST_EQUALS(stream->current(), '1');
	// 		UNITTEST_EQUALS(stream->next(), '2');
	// 		UNITTEST_EQUALS(stream->next(), '3');
	// 		UNITTEST_EQUALS(stream->getLineNumber(), 1u);
	// 		UNITTEST_EQUALS(stream->next(), '\n');
	// 		UNITTEST_EQUALS(stream->getLineNumber(), 2u);
	// 		// UNITTEST_EQUALS(stream->back(), '3');
	// 		// UNITTEST_EQUALS(stream->getLineNumber(), 1u);
	// 		UNITTEST_EQUALS(stream->next(), '\n');
	// 		UNITTEST_EQUALS(stream->next(), '4');
	// 		UNITTEST_EQUALS(stream->getLineNumber(), 2u);
	// 		// UNITTEST_EQUALS(stream->back(), '\n');
	// 		// UNITTEST_EQUALS(stream->getLineNumber(), 2u);
	// 		// UNITTEST_EQUALS(stream->back(), '3');
	// 		// UNITTEST_EQUALS(stream->getLineNumber(), 1u);
	// 		delete stream;
	// 	}

	// //--- virtual int StringStream::peek(uint ahead = 0) const;
	// 	{	Parser::Stream *stream = new Parser::StringStream("123\n456");
	// 		UNITTEST_EQUALS(stream->peek(), '1');
	// 		UNITTEST_EQUALS(stream->peek(1), '2');
	// 		UNITTEST_EQUALS(stream->next(), '1');
	// 		UNITTEST_EQUALS(stream->peek(2), '3');
	// 	}

	// //--- virtual bool StringStream::peek(const String& seed, bool consume = false); // <-- method not 'const' b/c revises object if "skip_seed" true
	// 	{	Tools::String string("This is a test of the emergency broadcast system. This is only a test.");
	// 		Parser::Stream *stream = new Parser::StringStream(string);
	// 		UNITTEST_ASSERT(!stream->peek(""));
	// 		UNITTEST_ASSERT(!stream->peek("this"));
	// 		UNITTEST_ASSERT(stream->peek("This"));
	// 		UNITTEST_ASSERT(stream->peek("This", true));
	// 		UNITTEST_ASSERT(stream->peek(" is"));
	// 		delete stream;

	// 		string.setCaseCompare(true);
	// 		stream = new Parser::StringStream(string);
	// 		UNITTEST_ASSERT(stream->peek("tHIS"));
	// 		UNITTEST_ASSERT(stream->peek("This"));
	// 		UNITTEST_ASSERT(stream->peek("this", true));
	// 		UNITTEST_ASSERT(stream->peek(" is"));
	// 	}

	// //--- virtual bool StringStream::isEOF(void) const;
	// 	{	Parser::StringStream *stream = new Parser::StringStream("");
	// 		UNITTEST_ASSERT(stream->isEOF());
	// 		delete stream;

	// 		stream = new Parser::StringStream("t");
	// 		UNITTEST_ASSERT(!stream->isEOF());
	// 		stream->next();
	// 		stream->next();
	// 		UNITTEST_ASSERT(stream->isEOF());
	// 		delete stream;
	// 	}

	// //--- virtual void StringStream::skip(uint chars = 1);
	// 	// {	Parser::StringStream *stream = new Parser::StringStream("");
	// 	// 	stream->skip();
	// 	// 	delete stream;

	// 	// 	stream = new Parser::StringStream("testing");
	// 	// 	// stream->skip();
	// 	// 	UNITTEST_EQUALS(stream->current(), 'e');
	// 	// 	UNITTEST_EQUALS(stream->next(), 's');
	// 	// 	stream->skip(0);
	// 	// 	UNITTEST_EQUALS(stream->current(), 's');
	// 	// 	stream->skip(2);
	// 	// 	UNITTEST_EQUALS(stream->current(), 'i');
	// 	// 	stream->skip(3);
	// 	// 	UNITTEST_EQUALS(stream->current(), EOF);
	// 	// 	delete stream;
	// 	// }

	// //--- virtual uint StringStream::getLength(void) const;
	// 	// {	Parser::StringStream *stream = new Parser::StringStream("");
	// 	// 	UNITTEST_EQUALS(stream->getLength(), 0u);
	// 	// 	delete stream;

	// 	// 	stream = new StringStream("testing");
	// 	// 	UNITTEST_EQUALS(stream->getLength(), 7u);
	// 	// 	delete stream;
	// 	// }

	// //--- virtual uint StringStream::getPosition(void) const;
	// 	// {	StringStream *stream = new StringStream("");
	// 	// 	UNITTEST_EQUALS(stream->getPosition(), 0u);
	// 	// 	delete stream;

	// 	// 	stream = new StringStream("testing");
	// 	// 	stream->current();
	// 	// 	UNITTEST_EQUALS(stream->getPosition(), 0u);
	// 	// 	stream->current();
	// 	// 	UNITTEST_EQUALS(stream->getPosition(), 0u);
	// 	// 	stream->next();
	// 	// 	UNITTEST_EQUALS(stream->getPosition(), 1u);
	// 	// 	stream->skip(10);
	// 	// 	UNITTEST_EQUALS(stream->getPosition(), 7u);
	// 	// 	delete stream;
	// 	// }

	// //--- virtual int StringStream::operator*(void);
	// //--- virtual int StringStream::operator++(void);
	// //--- virtual int StringStream::operator--(void);
	// 	// {	StringStream stream1("");
	// 	// 	UNITTEST_EQUALS(*stream1, EOF);

	// 	// 	StringStream stream2("testing");
	// 	// 	UNITTEST_EQUALS(*stream2, 't');
	// 	// 	UNITTEST_EQUALS(*stream2, 't');
	// 	// 	UNITTEST_EQUALS(++stream2, 'e');
	// 	// 	UNITTEST_EQUALS(*stream2, 'e');
	// 	// 	UNITTEST_EQUALS(--stream2, 't');
	// 	// 	UNITTEST_EQUALS(--stream2, 't');
	// 	// }

	// //--- virtual String StringStream::toString(void) const;
	// 	{	Parser::StringStream stream("");
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	}
	// 	{	Parser::StringStream stream("unit test");
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	}
	// 	{	Parser::StringStream stream("this is a test");
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 		stream.next();
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	}
	// 	{	Parser::StringStream stream("this is a test");
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 		stream.next();
	// 		stream.next();
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	}
	// 	{	Parser::StringStream stream("this is a test");
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 		stream.next();
	// 		stream.next();
	// 		UNITTEST_PATTERN(stream.toString(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	}
	// //--- friend std::ostream& StringStream::operator<<(std::ostream& stream, const StringStream& string)
	// 	// {	std::ostringstream output;
	// 	// 	Tools::String text("this is a test");
	// 	// 	Parser::StringStream stream(text);
	// 	// 	output << stream;
	// 	// 	UNITTEST_PATTERN(output.str(), "[[]StringStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
	// 	// }
	// }
}