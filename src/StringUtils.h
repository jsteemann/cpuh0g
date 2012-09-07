
#ifndef CPUHOG_STRING_UTILS_H
#define CPUHOG_STRING_UTILS_H 1

#include <string>
#include <sstream>

using namespace std;

namespace cpuh0g {
  class StringUtils {
    public:
      static string toString (const int value) {
        ostringstream out;

        out << value;

        return out.str();
      }

      static string trim (const char* value) {
        string copy(value);

        copy.erase(0, copy.find_first_not_of("\t\r\n "));
        copy.erase(copy.find_last_not_of("\t\r\n ") + 1);

        return copy;
      }
     
      static string trim (const string& value) {
        string copy(value);

        copy.erase(0, copy.find_first_not_of("\t\r\n "));
        copy.erase(copy.find_last_not_of("\t\r\n ") + 1);

        return copy;
      }

  };
}

#endif
