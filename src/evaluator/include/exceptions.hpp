#include <string>

namespace evl{
    class ParseFailException {
            public:
                int line;
            public:
                ParseFailException(int line);
                ~ParseFailException();
        };

        class SyntaxFailException {
            public:
                int line;
            public:
                SyntaxFailException(int line);
                ~SyntaxFailException();
        };
        class UnexpectedTokenException {
            public:
                int line;
                std::string str;
            public:
                UnexpectedTokenException(std::string token_str, int line);
                ~UnexpectedTokenException();
        };
        class InvalidMethodException {
            public:
                std::string name;
            public:
                InvalidMethodException(std::string name);
                ~InvalidMethodException();
        };
        class ConnectionExistsException {
            public:
                std::string name;
            public:
                ConnectionExistsException(std::string name);
                ~ConnectionExistsException();
        };
        enum GenericException{FILE_CLOSED, FILE_OPEN_FAIL, END_OF_FILE};
}