#include "XmlTokenStream.hpp"
#include "UnitTests.hpp"

namespace UnitTests
{

//=== class XmlTokenStream ==========================================================================================================================
	void test_XmlTokenStream(void) {
	//---	XmlTokenStream(Stream *stream);
	//---	XmlTokenStream(const String& text);
	//---	virtual Token XmlTokenizer::next(void) override;
		{	XmlTokenStream *xml_stream = new XmlTokenStream(new StringStream("<xml>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<xml>"));
			delete xml_stream;
		}
		{	XmlTokenStream *xml_stream = new XmlTokenStream(new StringStream("<xml><xml/></xml>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<xml>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eAtomTag, "<xml/>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</xml>"));
			delete xml_stream;
		}
		{	XmlTokenStream *xml_stream = new XmlTokenStream(new StringStream("<xml attrib=\"value\">this is a test <xml attrib='value'/></xml>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<xml attrib=\"value\">"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "this is a test "));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eAtomTag, "<xml attrib='value'/>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</xml>"));
			delete xml_stream;
		}

		static const String xml_tests(
				"<person id=\"1\">\n"
				"	<first>name</first>\n"
				"	<last>surname</last>\n"
				"	<address>\n"
				"		<street attrib=\"tests\" attrib1=\"tests1\" attrib2=\"tests2\">20 Evergreen Rd.</street>\n"
				"		<city>Vernon</city>\n"
				"		<state>Connecticut, USA</state>\n"
				"		<phone type=\"touchtone\" network=\"POTS\"/>\n"
				"	</address>\n"
				"</person>"
			);
		{	XmlTokenStream *xml_stream = new XmlTokenStream(xml_tests);
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<person id=\"1\">"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<first>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "name"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</first>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<last>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "surname"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</last>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<address>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<street attrib=\"tests\" attrib1=\"tests1\" attrib2=\"tests2\">"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "20 Evergreen Rd."));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</street>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<city>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "Vernon"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</city>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eStartTag, "<state>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "Connecticut, USA"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</state>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eAtomTag, "<phone type=\"touchtone\" network=\"POTS\"/>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n\t"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</address>"));
			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eText, "\n"));

			UNITTEST_EQUALS(xml_stream->next(), Token(TokenType::eEndTag, "</person>"));
			delete xml_stream;
		}

	//---	virtual String XmlTokenStream::serialize(void) const override;
		{
			UNITTEST_EQUALS(XmlTokenStream(xml_tests).serialize(),
					"{"
						"\"XmlTokenStream\": {"
							"\"TokenStream\": {"
								"\"current_token\": {"
									"\"Token\": {"
										"\"type\": \"'NULL'\", "
										"\"text\": \"\", "
										"\"whitespace\": \"\""
									"}"
								"}, "
								"\"stream\": {"
									"\"StringStream\": {"
										"\"position\": \"0\", "
										"\"bookmark\": \"0\", "
										"\"string\": "
											"\"<person id=\"1\">\n"
											"	<first>name</first>\n"
											"	<last>surname</last>\n"
											"	<address>\n"
											"		<street attrib=\"tests\" attrib1=\"tests1\" attrib2=\"tests2\">20 Evergreen Rd.</street>\n"
											"		<city>Vernon</city>\n"
											"		<state>Connecticut, USA</state>\n"
											"		<phone type=\"touchtone\" network=\"POTS\"/>\n"
											"	</address>\n"
											"</person>\""
									"}"
								"}"
							"}"
						"}"
					"}");
		}
	//---	virtual String XmlTokenStream::toString(void) const override;
		{
			UNITTEST_PATTERN(XmlTokenStream(xml_tests).toString(), "[[]XmlTokenStream: [0-9A-Fa-f][0-9A-Fa-f]*[]]");
		}
	//--- friend 	std::ostream& operator<<(std::ostream& stream, const XmlTokenStream& tokens);
		{
		}
	}
}