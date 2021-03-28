#include "platform.h"
#include "include/pathLib.hpp"

void Path::setDiv(){
    switch (get_platform()){
        case WINDOWS:
            div = '\\';
            break;
        case OSX:
        case LINUX:
            div = '/';
            break;
        default:
            div = '/';
            break;
    }
}

Path::Path(std::string fullpath){
    length = fullpath.size();
    int i = 0;
    setDiv();

    this->fullpath = fullpath;
    isFile = false;
    hasExt = false;
    pos_file_name_start = -1;
    pos_ext = -1;
    

    for (i = length -1; i >= 0; i--){
        if (fullpath[i] == div){
            pos_file_name_start = i+1;
            break;
        }
    }

    if (i==-1)
        pos_file_name_start = 0;

    if (pos_file_name_start != length)
        isFile = true;

    if (isFile){
        std::string name = getFileName();

        for (i = length - 1; i >=pos_file_name_start; i--){
            if (fullpath[i] == '.'){
                pos_ext = i+1;
                break;
            }
        }

        if (pos_ext != length && i != pos_file_name_start-1)
            hasExt = true;

    }else{
        if (fullpath[length-1] != div)
            fullpath.push_back(div);
    }
}

Path::~Path(){}

std::string Path::getFileName(){
    if (!isFile)
        return "";

    return fullpath.substr(pos_file_name_start, length-pos_file_name_start);   
}

std::string Path::getFileExtension(){
    if (!hasExt)
        return "";

    return fullpath.substr(pos_ext, length-pos_ext);   
}

std::string Path::getFullPath(){
    return fullpath; 
}

std::string Path::getParent(){
    return fullpath.substr(0, pos_file_name_start);   
}

int Path::size(){
    return fullpath.size();
}

Path Path::join(Path s){
    if (hasExt)
        throw -2;
        
    
    if (s.size() == 0)
        return *this;
    
    std::string new_path = fullpath;

    if (s[0] == div)
        new_path.append(s.getFullPath().substr(1,s.size()-1));
    else
        new_path.append(s.getFullPath());

    return Path(new_path);
}

Path Path::getParentPath(){
    return Path(getParent());
}

std::string Path::toString() const{
    return this->fullpath;
}

std::ostream& operator << ( std::ostream& outs, const Path &p ){
  return outs << p.toString();
}

Path::operator std::string() const {
    return this->toString();
}

char& Path::operator[](int index)
{
    if (index >= length) {
        throw -2;
    }
    return fullpath[index];
}

