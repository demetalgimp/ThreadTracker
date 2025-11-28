#include <ctype.h>
#include "TokenStream.hpp"

namespace Parser {

//=== Stream ======================================================================================
//=== StringStream ================================================================================
    char StringStream::peek(int offset) {
        if ( index < 0 ) {
            index = 0;
        }
        bool between = (0 <= text[index + offset]  &&  text[index + offset] < 0xFF);
        return ( !isEOF()  &&  between? text[index + offset]: 0 );
    }

    bool StringStream::peek(const Tools::String& test, bool consume) {
        if ( index < 0 ) {
            index = 0;
        }
        bool result = text.startsWith(test, index);

        if ( consume ) {
            index += test.getLength();
        }

        return result;
    }

    char StringStream::current(void) {
        if ( index < 0 ) {
            return next();

        } else {
            return ( index < (int)text.getLength()? text[index]: 0 );
        }
    }

    char StringStream::next(void) {
        if ( text[index + 1] == '\n' ) {
            line_number++;
        }

        return ( index < (int)text.getLength()? text[++index]: 0 );
    }

    void StringStream::skip(int offset) {
        if ( offset < 0 ) {
            index = (index + offset > 0? index + offset: 0);

        } else {
            index = (index + offset < (int)text.getLength()? index + offset: text.getLength());
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
        return (index >= (int)text.getLength())  ||  (text.getLength() == 0);
    }

//=== Token =======================================================================================
    Token::Token(char letter): token_type((EToken)letter) {
        char tmps[2] = {letter, 0};
        token_text = tmps;
    }

    // void TokenStream::Token::wideCharToString(EToken token, char *str) {
    //     for ( int i = 3; i >= 0; i-- ) {
    //         char c = (char)((token >> (i << 3)) & 0xFF);
    //         if ( c != 0 ) {
    //             *str++ = c;
    //         }
    //     }
    // }

    Token::Token(EToken token, const Tools::String& text): token_type(token) {
        if ( text.isEmpty() ) {
            this->token_text = Tools::String::wideCharToString(token);

        } else {
            this->token_text = text;
        }
    }

    bool TokenStream::peek(const Tools::String& test) {
        return stream.peek(test);
    }

    bool TokenStream::parseWhiteSpace(void) {
        EToken etoken = (stream.isEOF()? eEOF: eEmpty);
        char tmps[10000];
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
        EToken etoken = eNumber;
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

    void TokenStream::parseTwoCharToken(char first, char second, EToken combined) {
        if ( stream.peek(1) == second ) {
            current_token = Token(combined);
            stream.next();

        } else {
            current_token = Token(first);
        }
    }

    Token TokenStream::next(void) {
        current_token = Token(eEOF);
        // parseWhiteSpace();
        // whitespace.clear();
        // if ( parseWhiteSpace()  &&  grab_white_space ) {
        //     whitespace += (const char*)current_token.token_text.getText();
        // }
        Tools::String whitespace;
        while ( parseWhiteSpace() ) {//} &&  grab_white_space ) {
            whitespace += (const char*)current_token.token_text.getText();
        }
        if ( !whitespace.isEmpty() ) {
            current_token = Token(eSpace, whitespace);
            return current_token;
        } else {
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

                        case '&':
                            if ( stream.peek(1) == eEquals ) {
                                current_token = Token(eBitwiseAndEquals);
                                stream.next();

                            } else if ( stream.peek(1) == eAmpersand ) {
                                current_token = Token(eBooleanAnd);
                                stream.next();

                            } else {
                                current_token = Token('&');
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

                        case '-':
                            if ( stream.peek(1) == eEquals ) {
                                current_token = Token(eMinusEquals);
                                stream.next();

                            } else if ( stream.peek(1) == eMinus ) {
                                current_token = Token(eDecrement);
                                stream.next();

                            } else if ( stream.peek(1) == eGreaterThan ) {
                                current_token = Token(ePointer);
                                stream.next();

                            // } else if ( isdigit(stream.peek(1)) ) {
                            //     parseNumber();
                            //     stream.skip(-1); // <-- patch the stream.next() below

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

                            // } else if ( isdigit(stream.peek(1)) ) {
                            //     parseNumber();
                            //     stream.skip(-1); // <-- patch the stream.next() below

                            } else {
                                current_token = Token(eSum);
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

                        case ':': parseTwoCharToken(':', ':', eNameResolution); break;
                        case '~': parseTwoCharToken('~', '=', eBitwiseNotEquals); break;
                        case '%': parseTwoCharToken('%', '=', eModulusEquals); break;
                        case '^': parseTwoCharToken('^', '=', eBitwiseXorEquals); break;
                        case '*': parseTwoCharToken('*', '=', eMultiplyEquals); break;
                        case '/': parseTwoCharToken('/', '=', eDivideEquals); break;
                        case '!': parseTwoCharToken('!', '=', eNotEqualTo); break;
                        case '=': parseTwoCharToken('=', '=', eEqualTo); break;
                    }
                    stream.next();
                }
            }
        }
        return current_token;
    }

    Token TokenStream::current(void) {
        if ( current_token.token_type == eEmpty ) {
            return next();

        } else {
            return current_token;
        }
    }
}

