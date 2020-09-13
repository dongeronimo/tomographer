#ifndef __string_utils
#define __string_utils
#include <string>
namespace StringUtils {
const char* StringToCstr(const std::string& str);
const char* CloneStringFromStringstream(const std::stringstream& ss);
}
#endif
