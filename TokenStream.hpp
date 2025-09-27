#include "Blob.hpp"

namespace Parser {
    enum EToken {
        eBang = '!', eDoubleQuote = '"', eHash = '#', eDollar = '$', ePercent = '%', eAnd = '&',
        eSingleQuote = '\'', eLeftParenthesis = '(', eRightParenthesis = ')', eAsterix = '*',
        ePlus = '+', eComma = ',', ehyphen = '-', ePeriod = '.', eSlash = '/',
        eColon = ':', eSemicolon = ';', eLeftAngleBracket = '<', eEquals = '=', eRightAngleBracket = '>',
        eQuestionMark = '?', eAt = '@', eLeftBracket = '[', eBackslash = '\\', eRightBracket = ']',
        eCircumflex = '^', eBackQuote = '`', eLeftBrace = '{', eVerticalBar = '|', eRightBrace = '}',
        eTilde = '~',
        eBooleanNot = '!', eNotEqualTo = '!=',
        eLessThan = '<', eLessEqualTo = '<=', eShiftLeft = '<<', eShiftLeftAssign = '<<=',
        eGreaterThan = '>', eGreaterEqualTo = '>=', eShiftRight = '>>',  eShiftRightAssign = '>>=',
        eEqualTo = '==',
        eBitwiseOr = '|', eBooleanOr = '||', eBitwiseOrEquals = '|=',
        eBitwiseAnd = '&', eBooleanAnd = '&&', eBitwiseAndEquals = '&=',
        eMultiply = '*', eMultiplyEquals = '*=',
        eDivide = '/', eDivideEquals = '/=',
        eSum = '+', eSumEquals = '+=', eIncrement = '++',
        eMinus = '-', eMinusEquals = '-=', eDecrement = '--',
        eModulus = '%', eModulusEquals = '%=',
        eBitwiseXor = '^', eBitwiseXorEquals = '^=',
        eBitwiseNot = '~', eBitwiseNotEquals = '~=',
        eArithmeticIf = '(?:)',
        ePointer = '->',
        eEmpty = 0, eWord = 'WORD', eNumber = '#.##', eChar = '\'?\'', eString = '".."', eComment = '/**/', eSpace = 'SPAC', eEOF = -1, eNameResolution = '::'
    };

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
                fprintf(stderr, "%4d:%s\n", linenum, text.GetText());
                fprintf(stderr, "%4s %*s^\n", "", index, " ");
            }
    };

    class TokenStream {
        public:
            struct Token {
                EToken token_enum;
                Tools::String text;

                Token(void): token_enum(eEmpty) {}
                Token(char letter);
                Token(EToken token, const Tools::String& text = "");

                bool isEmpty(void) { return (token_enum == eEmpty); }
                bool isEOF(void)   { return (token_enum == eEOF); }
            };

        private:
            StringStream stream;
            Token current_token;

        public:
            TokenStream(const StringStream& stream): stream(stream) {}
            TokenStream(const Tools::String& string): stream(string) {}

        public:
            bool peek(const Tools::String& test);
            void getWhiteSpace(void);
            void getIdentifier(void);
            void getNumber(void);
            void getString(void);

        public:
            Token next(void);
            Token get(void);
    };
}
