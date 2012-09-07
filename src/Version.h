
#ifndef CPUHOG_VERSION_H
#define CPUHOG_VERSION_H 1

#include <string>
#include <sstream>

#define CPUHOG_VERSION_MAJOR 0
#define CPUHOG_VERSION_MINOR 0
#define CPUHOG_VERSION_REVISION 1
#define CPUHOG_VERSION_RELEASE "alpha"
#define CPUHOG_BUILD_DATE __DATE__

#define CPUHOG_NAME "cpuh0g"

using namespace std;

namespace cpuh0g {
  class Version {
    public:
      static const int getMajor () {
        return CPUHOG_VERSION_MAJOR;
      }
      
      static const int getMinor () {
        return CPUHOG_VERSION_MINOR;
      }
      
      static const int getRevision () {
        return CPUHOG_VERSION_REVISION;
      }
      
      static const string getRelease () {
        return CPUHOG_VERSION_RELEASE;
      }

      static const string getName () {
        return CPUHOG_NAME;
      }

      static const string get () {
        ostringstream version;

        version << getName() << "-" << getMajor() << "." << getMinor() << "." << getRevision() << "-" << getRelease() << ", build date: " << CPUHOG_BUILD_DATE;

        return version.str();
      }
  };
}

#endif
