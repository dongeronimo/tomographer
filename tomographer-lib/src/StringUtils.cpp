#include "stringUtils.h"
#include <sstream>
namespace StringUtils {
const char* StringToCstr(const std::string& str){
    int newStrLen = str.length()+1;
    char* cstr = new char[newStrLen];
    snprintf(cstr, newStrLen*sizeof(char), "%s", str.data());
    return cstr;
}
const char* CloneStringFromStringstream(const std::stringstream& ss){
    auto x= ss.str();
    char* y = new char[x.length()+1];
    std::memset(y, 0, x.length()+1 * sizeof(char));
    std::memcpy(y, x.c_str(), sizeof(char)*x.length());
    return y;
}
}
