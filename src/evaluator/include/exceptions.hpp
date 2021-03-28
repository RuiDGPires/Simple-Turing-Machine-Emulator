#include <string>

namespace evl{
    class Exception {
        public:
            std::string file;
    };

    class MainStateExistsException : public Exception{
        public:
            std::string state;
        public:
            MainStateExistsException(std::string file, std::string state);
            ~MainStateExistsException();
    };

    class MainStateDoesntExistException : public Exception{
        public:
            std::string state;
        public:
            MainStateDoesntExistException(std::string file, std::string state);
            ~MainStateDoesntExistException();
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

    class ConnectionDoesntExistException : public Exception{
        public:
            std::string name;
        public:
            ConnectionDoesntExistException(std::string file, std::string name);
            ~ConnectionDoesntExistException();
    };

    class FileOpenFail : public Exception{
        public:
            FileOpenFail(std::string file);
            ~FileOpenFail();
    };

    enum GenericException{FILE_CLOSED, END_OF_FILE};
}