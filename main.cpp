#include <stdio.h>
#include "TokenStream.hpp"

static const char *test_elements_str =
        //--- operators and punctuation
            ": :: ~ ~= %\n"
            "%= ^ ^= & &=\n"
            "- -> -- -=\n"
            "+ += ++\n"
            "* *= | || |= \n"
            "/ /= ! != = ==\n"
            "> >> >= >>= \n"
            "< <= << <<=\n"
            "# ( ) [ ] \\ \n"
            "{ } ; , . ?\n"
            "` @ $\n"

        //--- numbers
            "0 0b1010010001111001100111 0123274127546312\n"
            "12304823876239012938409813 0x123456789ABCDEF\n"
            "-0 -0b101 -0123 -123 -0x01'23'456789abcdef\n"
            "+0 +0b101 +0123 +123 +0x01'23'456789abcdef\n"
            "123.1 123.0001 12'3.00'01\n"
            "123.1 z -123.1 z +123.1\n"
            "z 1.234e1 z -1.234e1 z\n"
            "+1.234e1 z 1.234e-1 z\n"
            "-1.234e-1 z +1.234e+1 z\n"
            "-123.1 -123.0001 +123.1 +123.0001\n"
            "123e789 123e-789 123e+789\n"
            "0123.e1 0123.e-1 0123.e+1\n"
            "0123.012e1 0123.012e-1 0123.012e+1\n"

        //--- operands
            "a abcde abc_12345 _abc _\n"

        //--- comments
            "/*one line comment*/\n"
            "/*multi-\n//line\ncomment*/\n"
            "/*comment/*within //comment*/\n"
            "/* abcdefghijklmnopqrstuvwxyz 0123456789 */\n"
            "/*abcdefghijklmnopqrstuvwxyz */"
            "/*0123456789ABCDEF0123456789ABCDEF */\n"
            "/**//* */\n/**/"
            "//abcdefghijklmnopqrstuvwxyz \n"
            "/*1234567890\n"
            "           \n"
;

void test_scanner(const Tools::String& string) {
    Parser::TokenStream stream(string);
    Parser::Token token;
    Tools::String accumulator;
    while ( !(token = stream.next()).isEOF() ) {
        std::cerr << token;
        if ( token.token_text == "\n" ) {
            std::cerr << std::endl;
        }
        accumulator += token.token_text;
    }
    std::cerr << std::endl;

    // if ( accumulator != string ) {
        std::vector<Tools::String> original = string.split('\n');
        std::vector<Tools::String> result = accumulator.split('\n');

        uint max_length = 0;
        for ( Tools::String line : original ) {
            max_length = (max_length < line.getLength()? line.getLength(): max_length);
        }

        for ( uint i = 0; i < original.size(); i++ ) {
            fprintf(stderr, "[%4d] %*s  [%4d] %s\n", i, -max_length, original[i].encode().getText(), i, result[i].encode().getText());
        }
    //     fprintf(stderr, "FAILED\n");

    // } else {
    //     fprintf(stderr, "Passed\n");
    // }
}

// struct __threadtracker_thread_state__ {
//     const char *method_name;
//     uint linenum;
// };
// static const char *__WEAVER_FN_HEADER__ =
//             "{"
//                 "struct __threadtracker_thread_state__ __tts__ = {"
//                         ".method_name = \"__FUNCTION__\", "
//                         ".linenum = __LINE__ "
//                 "};"
//                 "register_thread(&__tts__);"
//             "}";

void weave(const Tools::String& input_file, Tools::String& output) {
    // Tools::String source = Tools::File::readFile(input_file);
    Tools::String source =  "void fn(void) {\n"
                                "// do nothing(); \n"
                                "if ( a == b ) {\n"
                                    "/* nothing to do */\n"
                                "}\n"
                                "while ( true ) {\n"
                                    "do_nothing();\n"
                                "}\n"
                            "}\n";

    Parser::TokenStream stream(source);
    // Tools::String woven = stream.weave();
    // Tools::File::writeFile(output, woven);
    // bool in_function = false;
    // uint brace_count = 0;
    while ( !(stream.current().isEOF()) ) {
        Tools::String whole_token = stream.getWhiteSpace().encode() + stream.current().token_text;
        output += whole_token;
        stream.next();
fprintf(stderr, "!!!%s[%d]:[%s]\n", __FILE__, __LINE__, whole_token.getText());
    // // --- Look for function definitions
    //     if ( !in_function ) {
    //                                                                 fprintf(stderr, "!!!%s[%d]: Try function detection %s\n", __FILE__, __LINE__, stream.current().token_text.getText());
    //         if ( stream.current().token_type == Parser::eWord ) {
    //                                                                 fprintf(stderr, "!!!%s[%d]: Found function name? %s\n", __FILE__, __LINE__, stream.current().token_text.getText());
    //             if ( stream.next().token_type == Parser::eLeftParenthesis ) {
    //                 uint paren_count = 1;
    //                                                                 fprintf(stderr, "!!!%s[%d]: Found function parameters? %s\n", __FILE__, __LINE__, stream.current().token_text.getText());

    //             //--- Found what looks like a function definition, skip params looking for the opening brace
    //                 while ( paren_count > 0  &&  !stream.current().isEOF() ) {
    //                     output += stream.current().token_text;
    //                     stream.next();
    //                                                                 fprintf(stderr, "!!!%s[%d]: Found parameters! Paren count=%d %s\n", __FILE__, __LINE__, paren_count, stream.current().token_text.getText());
    //                     if ( stream.current().token_type == Parser::eLeftParenthesis ) {
    //                         paren_count++;

    //                     } else if ( stream.current().token_type == Parser::eRightParenthesis ) {
    //                         paren_count--;
    //                     }
    //                 }

    //             //--- If the next token is a brace, we've found a function definition
    //             while ( stream.current().isSpace() ) {
    //                 output += stream.current().token_text;
    //                 stream.next();
    //                                                                 fprintf(stderr, "!!!%s[%d]: Found parameters! Paren count=%d %s\n", __FILE__, __LINE__, paren_count, stream.current().token_text.getText());
    //             }
    //             if ( stream.current().token_type == Parser::eLeftBrace ) {

    //                     in_function = true;
    //                     brace_count = 1;
    //                     output += stream.current().token_text;
    //                     stream.next();
    //                     output += __WEAVER_FN_HEADER__;

    //                 //-- Go through the function body.
    //                     while ( brace_count > 0  &&  !stream.current().isEOF() ) {
    //                         output += stream.current().token_text;
    //                         stream.next();
    //                         if ( stream.current() == Parser::eLeftBrace ) {
    //                             brace_count++;

    //                         } else if ( stream.current() == Parser::eRightBrace ) {
    //                             brace_count--;
    //                         }
    //                     }

    //                     in_function = false;

    //                 } else {
    //                     //--- Not a function, just continue
    //                 }

    //             }
    //         }

    // //--- Inside a function, look for the closing brace
    //     } else {
    //                                                                 fprintf(stderr, "!!!%s[%d]: Found function %s\n", __FILE__, __LINE__, stream.current().token_text.getText());
    //         if ( stream.current() == Parser::eLeftBrace ) {
    //             brace_count++;

    //         } else if ( stream.current() == Parser::eRightBrace ) {
    //             brace_count--;
    //             if ( brace_count == 0 ) {
    //                 in_function = false;
    //             }
    //         }
    //         fprintf(stderr, "!!!%s[%d]:%s\n", __FILE__, __LINE__-1, output.getText());
    //     }
    }
    output += "\n";
}

#ifndef UNITTESTS_ONLY
int main(int cnt, char *args[]) {
    if ( cnt > 1  &&  Tools::String(args[1]) == "--test" ) {
        test_scanner(test_elements_str);
        args++;
        std::cerr << "----------------------------------------------------------------------------------" << std::endl;
    }
    Tools::String result;
    weave("",result);
    std::cout << result;
    // while ( *++args != nullptr ) {
    //     try {
    //         weave(Tools::File::readFile(*args), result);
    //         std::cout << result;

    //     } catch ( const Tools::String& error ) {
    //         std::cerr << error << std::endl;
    //     }
    // }
}
#endif