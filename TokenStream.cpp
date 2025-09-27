#include <ctype.h>
#include "TokenStream.hpp"

namespace Parser {

//=== Stream ======================================================================================
//=== StringStream ================================================================================
    char StringStream::peek(int offset) {
        return ( !isEOF()? text[index + offset]: -1 );
    }

    bool StringStream::peek(const Tools::String& test, bool consume) {
        bool result = text.StartsWith(test, index);
        if ( consume ) {
            index += test.GetLength();
        }
        return result;
    }

    char StringStream::current(void) {
        return ( index < text.GetLength()? text[index]: -1 );
    }

    char StringStream::next(void) {
        char c = ( index < text.GetLength()? text[++index]: -1 );
        return c;
    }

    void StringStream::skip(int offset) {
        if ( offset < 0 ) {
            index = (index + offset > 0? index + offset: 0);
        } else {
            index = (index + offset < text.GetLength()? index + offset: text.GetLength());
        }
    }

    bool StringStream::isSpace(void) {
        // return isspace(text[index]);
        return isspace(current());
    }

    bool StringStream::isEOL(void) {
        char c = current();
        return (isEOF()  ||  c == '\n'  ||  c == '\r'  ||  c == '\f');
    }

    bool StringStream::isEOF(void) {
        return (index >= text.GetLength());
    }

//=== Token =======================================================================================
    TokenStream::Token::Token(char letter): token_enum((EToken)letter) {
        char tmps[2] = {letter, 0};
        text = tmps;
    }

    TokenStream::Token::Token(EToken token, const Tools::String& text): token_enum(token) {
        if ( text.IsEmpty() ) {
            char tmps[5] = {0, 0, 0, 0, 0}, *s = tmps;
            // int i = 3;
            // char c;
            // c = (char)((token >> (i << 3)) & 0xFF);
            // if ( c != 0 ) {
            //     *s++ = c;
            // }
            // i--;
            // c = (char)((token >> (i << 3)) & 0xFF);
            // if ( c != 0 ) {
            //     *s++ = c;
            // }
            // i--;
            // c = (char)((token >> (i << 3)) & 0xFF);
            // if ( c != 0 ) {
            //     *s++ = c;
            // }
            // i--;
            // c = (char)((token >> (i << 3)) & 0xFF);
            // if ( c != 0 ) {
            //     *s++ = c;
            // }
            for ( int i = 3; i >= 0; i-- ) {
                char c = (char)((token >> (i << 3)) & 0xFF);
                if ( c != 0 ) {
                    *s++ = c;
                }
            }
            this->text = tmps;

        } else {
            this->text = text;
        }
    }

    bool TokenStream::peek(const Tools::String& test) {
        return stream.peek(test);
    }

    void TokenStream::getWhiteSpace(void) {
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
        // etoken = (stream.isEOF()? eEOF: (tmps[0] != 0? eSpace: eEmpty));
        current_token = Token(etoken, tmps);
    }

    void TokenStream::getIdentifier(void) {
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
    void TokenStream::getNumber(void) {
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

    void TokenStream::getString(void) {
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
        getWhiteSpace();
        if ( current_token.isEmpty() ) {
            if ( current_token.isEOF() ) {
                current_token = Token(eEOF);
                return current_token;

            } else if ( isalpha(stream.current())  ||  stream.current() == '_' ) {
                getIdentifier();

            } else if ( isdigit(stream.current()) ) {
                getNumber();

            } else if ( stream.current() == '\''  ||  stream.current() == '"' ) {
                getString();

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
                        if ( stream.peek(1) == ':' ) {
                            current_token = Token(eNameResolution);
                            stream.next();
                        } else {
                            current_token = Token(eColon);
                        }
                        break;
                    case '~':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eBitwiseNotEquals);
                            stream.next();
                        } else {
                            current_token = Token(eBitwiseNot);
                        }
                        break;
                    case '%':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eModulusEquals);
                            stream.next();
                        } else {
                            current_token = Token(eModulus);
                        }
                        break;
                    case '^':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eBitwiseXorEquals);
                            stream.next();
                        } else {
                            current_token = Token(eBitwiseXor);
                        }
                        break;
                    case '&':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eBitwiseAndEquals);
                            stream.next();
                        } else if ( stream.peek(1) == '&' ) {
                            current_token = Token(eBooleanAnd);
                            stream.next();
                        } else {
                            current_token = Token(eBitwiseAnd);
                        }
                        break;
                    case '-':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eMinusEquals);
                            stream.next();
                        } else if ( stream.peek(1) == '-' ) {
                            current_token = Token(eDecrement);
                            stream.next();
                        } else if ( isdigit(stream.peek(1)) ) {
                            getNumber();
                            stream.skip(-1); // <-- patch the stream.next() below
                        } else {
                            current_token = Token(eMinus);
                        }
                        break;
                    case '+':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eSumEquals);
                            stream.next();
                        } else if ( stream.peek(1) == '+' ) {
                            current_token = Token(eIncrement);
                            stream.next();
                        } else if ( isdigit(stream.peek(1)) ) {
                            getNumber();
                            stream.skip(-1); // <-- patch the stream.next() below
                        } else {
                            current_token = Token(eSum);
                        }
                        break;
                    case '*':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eMultiplyEquals);
                            stream.next();
                        } else {
                            current_token = Token(eMultiply);
                        }
                        break;
                    case '|':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eBitwiseOrEquals);
                            stream.next();
                        } else if ( stream.peek(1) == '|' ) {
                            current_token = Token(eBooleanOr);
                            stream.next();
                        } else {
                            current_token = Token(eBitwiseOr);
                        }
                        break;
                    case '/':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eDivideEquals);
                            stream.next();
                        } else {
                            current_token = Token(eDivide);
                        }
                        break;
                    case '!':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eNotEqualTo);
                            stream.next();
                        } else {
                            current_token = Token(eBooleanNot);
                        }
                        break;
                    case '=':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eEqualTo);
                            stream.next();
                        } else {
                            current_token = Token(eEquals);
                        }
                        break;
                    case '<':
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eLessEqualTo);
                            stream.next();
                        } else if ( stream.peek(1) == '<' ) {
                            stream.next();
                            if ( stream.peek(1) == '=' ) {
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
                        if ( stream.peek(1) == '=' ) {
                            current_token = Token(eGreaterEqualTo);
                            stream.next();
                        } else if ( stream.peek(1) == '>' ) {
                            stream.next();
                            if ( stream.peek(1) == '=' ) {
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

    TokenStream::Token TokenStream::get(void) {
        if ( current_token.token_enum == eEmpty ) {
            return next();

        } else {
            return current_token;
        }
    }
}

