#include <ctype.h>
#include "TokenStream.hpp"

namespace Parser {

//=== Stream ======================================================================================
//=== StringStream ================================================================================
    char StringStream::peek(int offset) {
        return ( !isEOF()? text[index + offset]: -1 );
    }

    bool StringStream::peek(const Tools::String& test, bool consume) {
        bool result = text.startsWith(test, index);

        if ( consume ) {
            index += test.getLength();
        }

        return result;
    }

    char StringStream::current(void) {
        return ( index < text.getLength()? text[index]: -1 );
    }

    char StringStream::next(void) {
        char c = ( index < text.getLength()? text[++index]: -1 );
        return c;
    }

    void StringStream::skip(int offset) {
        if ( offset < 0 ) {
            index = (index + offset > 0? index + offset: 0);

        } else {
            index = (index + offset < text.getLength()? index + offset: text.getLength());
        }
    }

    bool StringStream::isSpace(void) {
        return isspace(current());
    }

    bool StringStream::isEOL(void) {
        char c = current();
        return (isEOF()  ||  c == '\n'  ||  c == '\r'  ||  c == '\f');
    }

    bool StringStream::isEOF(void) {
        return (index >= text.getLength());
    }

//=== Token =======================================================================================
    TokenStream::Token::Token(char letter): token_type((EToken)letter) {
        char tmps[2] = {letter, 0};
        token_text = tmps;
    }

    void TokenStream::Token::wideCharToString(EToken token, char *str) {
        for ( int i = 3; i >= 0; i-- ) {
            char c = (char)((token >> (i << 3)) & 0xFF);
            if ( c != 0 ) {
                *str++ = c;
            }
        }
    }

    TokenStream::Token::Token(EToken token, const Tools::String& text): token_type(token) {
        if ( text.isEmpty() ) {
            char tmps[5] = {0, 0, 0, 0, 0};
            wideCharToString(token, tmps);
            this->token_text = tmps;

        } else {
            this->token_text = text;
        }
    }

    bool TokenStream::peek(const Tools::String& test) {
        return stream.peek(test);
    }

    bool TokenStream::parseWhiteSpace(void) {
        EToken etoken = (stream.isEOF()? eEOF: eEmpty);
        char tmps[1000];
        uint index = 0;
        if ( stream.isSpace() ) {
            while ( index < sizeof(tmps)  &&  !stream.isEOF()  &&  stream.isSpace() ) {
                tmps[index++] = stream.current();
                stream.next();
            }

            etoken = eSpace;

        } else if ( stream.peek("//") ) {
            tmps[index++] = stream.current();
            tmps[index++] = stream.next();
            while ( !stream.isEOF() ) {
                tmps[index++] = stream.next();
                if ( stream.isEOL()  ||  stream.isEOF() ) {
                    stream.next();
                    break;
                }
            }

            etoken = eLineComment;

        } else if ( stream.peek("/*") ) {
            tmps[index++] = stream.current();
            tmps[index++] = stream.next();
            // tmps[index++] = stream.next();

            stream.next();
            while ( !stream.isEOF() ) {
                // tmps[index++] = stream.current();
                if ( stream.peek("*/") ) {
                    tmps[index++] = stream.current();
                    tmps[index++] = stream.next();
                    stream.next();
                    break;
                }
                tmps[index++] = stream.current();
                stream.next();
            }

            etoken = eBlockComment;
        }

        tmps[index++] = 0;
// fprintf(stderr, "!!!%s[%d]:<%s>\n", __FILE__, __LINE__, Tools::String(tmps).encode().getText());
        current_token = Token(etoken, tmps);
        return (etoken == eSpace || etoken == eLineComment || etoken == eBlockComment);
    }

    void TokenStream::parseIdentifier(void) {
        char tmps[200];

        uint index = 0;
        tmps[index++] = stream.current();
        while ( isalnum(stream.next())  ||  stream.current() == '_' ) {
            tmps[index++] = stream.current();
        }

        tmps[index] = 0;
        current_token = Token(eWord, tmps);
    }

//TODO: add suffixes {u,l,ul,lu,ll,ull,llu}
    void TokenStream::parseNumber(void) {
        EToken etoken = eDecimalNumber;
        char tmps[200];
        uint index = 0;
        if ( stream.current() == '-'  ||  stream.current() == '+' ) {
            tmps[index++] = stream.current();
            stream.next();
        }

        tmps[index++] = stream.current();
        if ( stream.peek("0b")  ||  stream.peek("0B") ) {
            tmps[index++] = stream.next();
            tmps[index++] = stream.next();
            while ( stream.next() == '0'  ||  stream.current() == '1'  ||  stream.current() == '\'' ) {
                tmps[index++] = stream.current();
            }

            etoken = eBinaryNumber;

        } else if ( stream.peek("0x")  ||  stream.peek("0X") ) {
            tmps[index++] = stream.next();
            tmps[index++] = stream.next();
            while ( isxdigit(stream.next())  ||  stream.current() == '\'' ) {
                tmps[index++] = stream.current();
            }

            etoken = eHexadecimalNumber;

        } else {
            while ( isdigit(stream.next())  ||  stream.current() == '\'' ) {
                tmps[index++] = stream.current();
            }

            if ( stream.current() == '.' ) {

                tmps[index++] = stream.current();
                if ( isdigit(stream.next()) ) {

                    tmps[index++] = stream.current();
                    while ( isdigit(stream.next())  ||  stream.current() == '\'' ) {
                        tmps[index++] = stream.current();
                    }
                }
                etoken = eFloatingNumber;
            }

            if ( tolower(stream.current()) == 'e' ) {
                tmps[index++] = stream.current();
                if ( stream.next() == '-'  ||  stream.current() == '+' ) {
                    tmps[index++] = stream.current();
                    stream.next();
                }

                if ( isdigit(stream.current()) ) {
                    tmps[index++] = stream.current();
                    while ( isdigit(stream.next())  ||  stream.current() == '\'' ) {
                        tmps[index++] = stream.current();
                    }
                }
                etoken = eScientificNumber;
            }
        }
        tmps[index] = 0;
        current_token = Token(etoken, tmps);
    }

    void TokenStream::parseString(void) {
        char tmps[1000];
        uint index = 0;
        char end_of_string = stream.current();
        tmps[index++] = stream.current();
        while ( !stream.isEOF() ) {
            tmps[index++] = stream.next();
            if ( stream.current() == '\\' ) {
                tmps[index++] = stream.next();

            } else if ( stream.current() == end_of_string ) {
                stream.next();
                break;
            }
        }
        // tmps[index++] = stream.current();
        tmps[index] = 0;
        current_token = Token( (end_of_string == '"'? eStringConstant: eCharConstant), tmps);
    }

    TokenStream::Token TokenStream::next(void) {
        current_token = Token(eEOF);
        // parseWhiteSpace();
        whitespace.clear();
        // if ( parseWhiteSpace()  &&  grab_white_space ) {
        //     whitespace += (const char*)current_token.token_text.getText();
        // }
        while ( parseWhiteSpace() ) {//} &&  grab_white_space ) {
            whitespace += (const char*)current_token.token_text.getText();
        }

        if ( current_token.isEmpty() ) {
            if ( current_token.isEOF() ) {
                current_token = Token(eEOF);
                return current_token;

            } else if ( isalpha(stream.current())  ||  stream.current() == '_' ) {
                parseIdentifier();

            } else if ( isdigit(stream.current()) ) {
                parseNumber();

            } else if ( stream.current() == '\''  ||  stream.current() == '"' ) {
                parseString();

            } else {
                switch ( stream.current() ) {
                    case '`':
                    case '@':
                    case '#':
                    case '$':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '\\':
                    case '{':
                    case '}':
                    case ';':
                    case ',':
                    case '.':
                    case '?': current_token = Token(stream.current()); break;

                    case ':':
                        if ( stream.peek(1) == eColon ) {
                            current_token = Token(eNameResolution);
                            stream.next();

                        } else {
                            current_token = Token(eColon);
                        }
                        break;

                    case '~':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eBitwiseNotEquals);
                            stream.next();

                        } else {
                            current_token = Token(eBitwiseNot);
                        }
                        break;

                    case '%':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eModulusEquals);
                            stream.next();

                        } else {
                            current_token = Token(eModulus);
                        }
                        break;

                    case '^':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eBitwiseXorEquals);
                            stream.next();

                        } else {
                            current_token = Token(eBitwiseXor);
                        }
                        break;

                    case '&':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eBitwiseAndEquals);
                            stream.next();

                        } else if ( stream.peek(1) == eAmpersand ) {
                            current_token = Token(eBooleanAnd);
                            stream.next();

                        } else {
                            current_token = Token(eBitwiseAnd);
                        }
                        break;

                    case '-':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eMinusEquals);
                            stream.next();

                        } else if ( stream.peek(1) == eMinus ) {
                            current_token = Token(eDecrement);
                            stream.next();

                        } else if ( isdigit(stream.peek(1)) ) {
                            parseNumber();
                            stream.skip(-1); // <-- patch the stream.next() below

                        } else {
                            current_token = Token(eMinus);
                        }
                        break;
                    case '+':

                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eSumEquals);
                            stream.next();

                        } else if ( stream.peek(1) == ePlus ) {
                            current_token = Token(eIncrement);
                            stream.next();

                        } else if ( isdigit(stream.peek(1)) ) {
                            parseNumber();
                            stream.skip(-1); // <-- patch the stream.next() below

                        } else {
                            current_token = Token(eSum);
                        }
                        break;

                    case '*':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eMultiplyEquals);
                            stream.next();

                        } else {
                            current_token = Token(eMultiply);
                        }
                        break;

                    case '|':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eBitwiseOrEquals);
                            stream.next();

                        } else if ( stream.peek(1) == eVerticalBar ) {
                            current_token = Token(eBooleanOr);
                            stream.next();

                        } else {
                            current_token = Token(eBitwiseOr);
                        }
                        break;

                    case '/':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eDivideEquals);
                            stream.next();

                        } else {
                            current_token = Token(eDivide);
                        }
                        break;

                    case '!':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eNotEqualTo);
                            stream.next();

                        } else {
                            current_token = Token(eBooleanNot);
                        }
                        break;

                    case '=':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eEqualTo);
                            stream.next();

                        } else {
                            current_token = Token(eEquals);
                        }
                        break;

                    case '<':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eLessEqualTo);
                            stream.next();

                        } else if ( stream.peek(1) == eLeftAngleBracket ) {
                            stream.next();
                            if ( stream.peek(1) == eEquals ) {
                                current_token = Token(eShiftLeftAssign);
                                stream.next();

                            } else {
                                current_token = Token(eShiftLeft);
                            }

                        } else {
                            current_token = Token(eLessThan);
                        }
                        break;

                    case '>':
                        if ( stream.peek(1) == eEquals ) {
                            current_token = Token(eGreaterEqualTo);
                            stream.next();

                        } else if ( stream.peek(1) == eRightAngleBracket ) {
                            stream.next();
                            if ( stream.peek(1) == eEquals ) {
                                current_token = Token(eShiftRightAssign);
                                stream.next();

                            } else {
                                current_token = Token(eShiftRight);
                            }

                        } else {
                            current_token = Token(eGreaterThan);
                        }
                        break;
                }
                stream.next();
            }
        }
        return current_token;
    }

    TokenStream::Token TokenStream::current(void) {
        if ( current_token.token_type == eEmpty ) {
            return next();

        } else {
            return current_token;
        }
    }
}

