#include "UnitTests.hpp"
#include "Xml.hpp"

namespace UnitTest {
//=== class Xml =====================================================================================================================================
	/* NOTES:
	 * 		1) XML allows single or double quote for attributes.
	 * 		2) To test the attributes, they MUST be in alphabetical order because of the way std::map<> stores them. It's tempting to rewrite it
	 * 			for this reason.
	 */
	void test_Xml(void) {
	//---	Xml::Xml(TagTokenStream& stream)
	//---	virtual String Xml::toString(void) const override;
		{
			try {
				cchar *str = "<tag/>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), "<tag/>")
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str = "<tag attribute1=\"text1\"/>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), str);
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str = "<tag attribute1=\"text2\" attribute2=\"text2\" attribute3=\"text3\" attribute4=\"text4\"/>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), str);
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str = "<tag></tag>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), "<tag/>")
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str =
					"<tag_a>"
						"this is a "
						"<tag_b>amaricious, "
							"<tag>duplicitous</tag> "
						"</tag_b>"
						"test"
					"</tag_a>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), str);
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str = "<tag attribute1=\"text2\" attribute2=\"text2\" attribute3=\"text3\" attribute4=\"text4\"></tag>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), "<tag attribute1=\"text2\" attribute2=\"text2\" attribute3=\"text3\" attribute4=\"text4\"/>");
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str =
					"<Photo orientation='portrait' type='JPEG' uid='1234-12345678901234567890'>"
						"<filename>20240102-2345.jpeg</filename>"
						"<caption>Mary and Chris on beach <i>with a <u>concealed carry</u></i> rabbit</caption>"
					"</Photo>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), str);
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}

			try {
				cchar *str =
					"<CallList base_index=\"1\" index=\"1\" max=\"201\" timestamp=\"05/07/2010 21:36:12.0000\" type=\"Address\">"
						"<Item id=\"9843\" uuid=\"1234567890123-1234-0000-000000000000\">"
							"<Name>"
								"<First timestamp='05/07/2010 21:36:12.0000'>George</First>"
								"<Last>Lewis</Last>"
							"</Name>"
							"<Properties>"
								"<Property dataType=\"Bool\" key=\"fav\">true</Property>"
								"<Property dataType=\"String\" key=\"language\">Finnish</Property>"
							"</Properties>"
							"<PhoneNumberList>"
								"<PhoneNumber type=\"Home\">8015551212</PhoneNumber> uuid=\"1234567890123-1234-0001-000000000000\""
								"<PhoneNumber type=\"Cell\">2035551212</PhoneNumber> uuid=\"1234567890123-1234-0001-000000000001\""
							"</PhoneNumberList>"
						"</Item>"
					"</CallList>";
				Xml* xml = Xml::parse(new XmlTokenStream(str));
				UNITTEST_EQUALS(xml->toString(), str);
				delete xml;

			} catch ( const String& error ) {
				FAIL("Should not have got this exception: \"" + error + "\"");
			}
		}

	//---	Xml::Xml(const String& name)
		{
			Xml xml("namesless");
			UNITTEST_EQUALS(xml.name, "namesless");
			UNITTEST_EQUALS(xml.elements.size(), 0u);
			UNITTEST_EQUALS(xml.attributes.size(), 0u);
		}

	//---	Xml::Xml(XmlTokenStream xml_stream)
//		{
//			Xml xml(XmlTokenStream(xml_tests));
//			xml.
//		}

	//---	std::vector<Xml*> Xml::operator[](const String& name)
		{
	//TODO
		}

	//---	String Xml::operator()(const String& key)
		{	Xml xml("person");
			xml("height") = "163cm";
			UNITTEST_EQUALS(xml("height"), "163cm");
			xml("height") = "60\"";
			UNITTEST_EQUALS(xml("height"), "60\"");
		}

	//---	Xml* Xml::collectAttributes(const Token& token, Xml* xml = nullptr);
		{
	//TODO
		}

	//---	Xml* Xml::parse(XmlTokenStream xml_stream);
		{
	//TODO
		}

	//---	virtual const char* Xml::getChars(void)
		{
	//TODO
		}
	//---	std::vector<Xml*> operator[](const String& name);
		{

		}

	//---
		{
	//TODO
	//		std::ostringstream output;
	//		String text("this is a test");
	//		TokenStream stream(text);
	//		while ( !stream.isEOF() ) {
	//			stream.next();
	//			output << stream.current();
	//		}
	//		UNITTEST_EQUALS(output.str(), text);
		}
	}
}