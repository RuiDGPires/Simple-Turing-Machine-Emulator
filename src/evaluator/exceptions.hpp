#include <string>

namespace evl{
    class ParseFailException {
            public:
                int line;
                ParseFailException(int line);
                ~ParseFailException();
        };

        class SyntaxFailException {
            public:
                int line;
                SyntaxFailException(int line);
                ~SyntaxFailException();
        };
        class UnexpectedTokenException {
            public:
                int line;
                std::string str;
                UnexpectedTokenException(std::string token_str, int line);
                ~UnexpectedTokenException();
        };
        class InvalidMethodException {
            public:
                std::string name;
                InvalidMethodException(std::string name);
                ~InvalidMethodException();
        };
        enum GenericException{FILE_CLOSED, FILE_OPEN_FAIL, END_OF_FILE};
}