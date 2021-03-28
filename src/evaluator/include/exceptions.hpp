#include <string>

namespace evl{
    class Exception {
        public:
            std::string file;
    };

    class ParseFailException : public Exception{
        public:
            int line;
        public:
            ParseFailException(std::string file, int line);
            ~ParseFailException();
    };

    class SyntaxFailException : public Exception{
        public:
            int line;
        public:
            SyntaxFailException(std::string file, int line);
            ~SyntaxFailException();
    };
    class UnexpectedTokenException : public Exception{
        public:
            int line;
            std::string str;
        public:
            UnexpectedTokenException(std::string file, std::string token_str, int line);
            ~UnexpectedTokenException();
    };
    class InvalidMethodException : public Exception{
        public:
            std::string name;
        public:
            InvalidMethodException(std::string file, std::string name);
            ~InvalidMethodException();
    };

    class InvalidDecoratorException : public Exception{
        public:
            std::string name;
        public:
            InvalidDecoratorException(std::string file, std::string name);
            ~InvalidDecoratorException();
    };

    class ConnectionExistsException : public Exception{
        public:
            std::string name;
        public:
            ConnectionExistsException(std::string file, std::string name);
            ~ConnectionExistsException();
    };

    class FileOpenFail : public Exception{
        public:
            FileOpenFail(std::string file);
            ~FileOpenFail();
    };

    enum GenericException{FILE_CLOSED, END_OF_FILE};
}