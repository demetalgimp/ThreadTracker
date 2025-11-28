// #include <vector>
#include "Blob.hpp"
#include "TokenStream.hpp"

class Xml {
    struct Attribute {
        public:
            Tools::String name;
            Tools::String value;

        public:
            Attribute(const Tools::String& name, const Tools::String& value): name(name), value(value) {}

        public:
            static Attribute *toAttributePtr(Parser::TokenStream& stream) {
                Tools::String name;
                Tools::String value;

                //--- Get name
                Parser::Token token = stream.next();
                if ( token.token_type == Parser::eWord ) {
                    name = token.token_text;

                } else {
                    THROW_ERROR("Expected attribute name, got '%s'", token.token_text.getText());
                }

                //--- Get '=', if not present, throw error
                if ( !stream.consume("=") ) {
                    THROW_ERROR("Expected '=', got '%s'", stream.peek(0));
                }

                //--- Get value
                token = stream.next();
                if ( token.token_type == Parser::eStringConstant ) {
                    value = token.token_text;

                } else {
                    THROW_ERROR("Expected attribute value, got '%s'", token.token_text.getText());
                }

                return new Attribute(name, value);
            }

    };
    Tools::String name;
    std::vector<Attribute> attributes;
    std::vector<Xml> children;

    public:
        Xml(const Tools::String& text) {

            if ( text.startsWith("<") ) {
//+++ Fixme
                Parser::TokenStream stream(text);

                if ( stream.consume("<") ) {

                //--- Get tag name
                    Parser::Token token = stream.next();
                    if ( token.token_type == Parser::eWord ) {
                        name = token.token_text;

                    //--- While getAttribute(), add attributes

                    } else {
                        THROW_ERROR("Expected tag name, got '%s'", token.token_text.getText());
                    }

                } else {
                    THROW_ERROR("Expected '<' at start of tag", 0);
                }
//+++ Fixme
            //--- Extract the tag name

            //--- While getAttribute(), add attributes
            //--- If atom, done
            //--- Else, while not </tagname>, addChild(getChild())
            //--- Consume </tagname>
            } else {
                name = text;
            }
        }

        void addAttribute(const Tools::String& name, const Tools::String& value) {
            attributes.emplace_back(name, value);
        }

        void addChild(const Xml& child) {
            children.push_back(child);
        }

        Tools::String toString(int indent = 0) const {
            Tools::String indentation;
            for (int i = 0; i < indent; ++i) {
                indentation += "  ";
            }

            Tools::String result = indentation + "<" + name;

            for (const auto& attr : attributes) {
                result += " " + attr.name + "=\"" + attr.value + "\"";
            }

            if (children.empty()) {
                result += " />\n";
            } else {
                result += ">\n";
                for (const auto& child : children) {
                    result += child.toString(indent + 1);
                }
                result += indentation + "</" + name + ">\n";
            }

            return result;
        }
};

