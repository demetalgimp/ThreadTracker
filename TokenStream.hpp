#include "Blob.hpp"

namespace Parser {
    enum EToken {
    //--- All punctuation
        eBang = '!', eDoubleQuote = '"', eHash = '#', eDollar = '$', ePercent = '%', eAmpersand = '&',
        eSingleQuote = '\'', eLeftParenthesis = '(', eRightParenthesis = ')', eAsterix = '*',
        ePlus = '+', eComma = ',', ehyphen = '-', ePeriod = '.', eSlash = '/',
        eColon = ':', eSemicolon = ';', eLeftAngleBracket = '<', eEquals = '=', eRightAngleBracket = '>',
        eQuestionMark = '?', eAt = '@', eLeftBracket = '[', eBackslash = '\\', eRightBracket = ']',
        eCircumflex = '^', eBackQuote = '`', eLeftBrace = '{', eVerticalBar = '|', eRightBrace = '}',
        eTilde = '~',

    //--- Operator punctuation (overrideable)
        eBooleanNot = '!', eNotEqualTo = '!=',
        eLessThan = '<', eLessEqualTo = '<=', eShiftLeft = '<<', eShiftLeftAssign = '<<=',
        eGreaterThan = '>', eGreaterEqualTo = '>=', eShiftRight = '>>',  eShiftRightAssign = '>>=',
        eEqualTo = '==',
        eBitwiseOr = '|', eBooleanOr = '||', eBitwiseOrEquals = '|=',
        eBitwiseAnd = '&', eBooleanAnd = '&&', eBitwiseAndEquals = '&=',
        eMultiply = '*', eMultiplyEquals = '*=',
        eDivide = '/', eDivideEquals = '/=',
        eSum = '+', eSumEquals = '+=', eIncrement = '++',
        eMinus = '-', eMinusEquals = '-=', eDecrement = '--', ePointer = '->',
        eModulus = '%', eModulusEquals = '%=',
        eBitwiseXor = '^', eBitwiseXorEquals = '^=',
        eBitwiseNot = '~', eBitwiseNotEquals = '~=',
        //--- non-overrideable
        eArithmeticIf = '(?:)',

    //--- Operands and their punctuation
        eNameResolution = '::',
        eEmpty = 0, eWord = 'WORD',
        eNumber = '####', eDecimalNumber = '#..#', eHexadecimalNumber = '0x##', eBinaryNumber = '0b##', eFloatingNumber = '#.##', eScientificNumber = '#.e#',
        eQuoted = '""\'\'', eStringConstant = '".."', eCharConstant = '\'..\'',

    //--- etc.
        eComment = '/*//', eBlockComment = '/**/', eLineComment = '//..',
        eSpace = 'SPAC', eEOF = -1
    };


#define IS_A(token_specific, token_general) {\
            if ( token_general == eNumber \
                    &&  (token_specific == eDecimalNumber  \
                        ||  token_specific == eNumber  \
                        ||  token_specific == eHexadecimalNumber  \
                        ||  token_specific == eBinaryNumber \
                        ||  token_specific == eFloatingNumber \
                        ||  token_specific == eScientificNumber) \
                ) {\
                return true;\
            \
            } else if ( token_general == eQuoted \
                    &&  (token_specific == eQuoted \
                        ||  token_specific == eStringConstant \
                        ||  token_specific == eLineComment \) ) {\
                return true;\
            \
            } else if ( token_general == eSpace \
                    &&  (token_specific == eSpace \
                        ||  token_specific == eStringConstant \
                        ||  token_specific == eLineComment) ) {\
                return true;\
            \
            } else { \
                return false;\
            } \
        }

    class Stream {
        public:
            virtual char peek(int offset=0) = 0;
            // virtual bool peek(const Tools::String& test, Stream& consumer) = 0;
            virtual bool peek(const Tools::String& test, bool consume = false) = 0;
            virtual char current(void) = 0;
            virtual char next(void) = 0;
            virtual void skip(int offset) = 0;

        public:
            virtual bool isSpace(void) = 0;
            virtual bool isEOL(void) = 0;
            virtual bool isEOF(void) = 0;
    };

    class StringStream: public Stream {
        Tools::String text;
        uint index;

        public:
            StringStream(const Tools::String& text): text(text), index(0) {}
            StringStream(const StringStream& stream): text(stream.text), index(stream.index) {}

        public:
            virtual char peek(int offset=0) override;
            // bool peek(const Tools::String& test, Stream& consumer) override;
            virtual bool peek(const Tools::String& test, bool consume = false) override;
            virtual char current(void) override;
            virtual char next(void) override;
            virtual void skip(int offset) override;

        public:
            virtual bool isSpace(void) override;
            virtual bool isEOL(void) override;
            virtual bool isEOF(void) override;

        public:
            void testPrint(int linenum) const {
                fprintf(stderr, "%4d:%s\n", linenum, text.getText());
                fprintf(stderr, "%4s %*s^\n", "", index, " ");
            }
    };

    class TokenStream {
        public:
            struct Token {
                EToken token_type;
                Tools::String token_text;

                Token(void): token_type(eEmpty) {}
                Token(char letter);
                Token(EToken token, const Tools::String& text = "");

                bool isEmpty(void)  { return (token_type == eEmpty); }
                bool isEOF(void)    { return (token_type == eEOF); }
                bool isSpace(void)  { return (token_type == eSpace  ||  token_type == eStringConstant  ||  token_type == eLineComment); }
                operator bool(void) { return (token_type != eEmpty  &&  token_type != eEOF); }

                static void wideCharToString(EToken token, char *str);
                friend std::ostream& operator<<(std::ostream& stream, const Token& token) {
                    char tmps[5] = {0, 0, 0, 0, 0};
                    Token::wideCharToString(token.token_type, tmps);
                    stream << "{\"" << token.token_text.encode() << "\", '" << tmps << "'}";
                    return stream;
                }
            };

        private:
            StringStream stream;
            Token current_token;
            bool grab_white_space = true;
            Tools::String whitespace;

        public:
            TokenStream(const StringStream& stream): stream(stream) {}
            TokenStream(const Tools::String& string): stream(string) {}

        private:
            bool parseWhiteSpace(void);
            void parseIdentifier(void);
            void parseNumber(void);
            void parseString(void);

        public:
            bool peek(const Tools::String& test);
            EToken peek(int index) { return ((EToken)stream.peek(index)); }
            bool peek(char token) { return (stream.peek(1) == token); }
            Token next(void);
            Token current(void);
            Tools::String getWhiteSpace(void) { return whitespace; }
            Tools::String getText(void) { return whitespace + current_token.token_text; }
    };
}
