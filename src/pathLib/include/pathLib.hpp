#include <string>

class Path{
    private:
        std::string fullpath;
        int pos_file_name_start, pos_ext;
        int length;
        char div;
        bool isFile;
        bool hasExt;
        void setDiv();
    public:
        Path(std::string fullpath);
        ~Path();

        std::string getFileName();
        std::string getFileExtension();
        std::string getFullPath();
        std::string getParent();

        Path getParentPath();
        int size();
        Path join(Path s);

        std::string toString() const;
        operator std::string() const;
        char &operator[](int);
};


std::ostream& operator << ( std::ostream& outs, const Path &p );

