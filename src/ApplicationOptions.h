
#ifndef CPUHOG_APPLICATION_OPTIONS_H
#define CPUHOG_APPLICATION_OPTIONS_H 1

#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>

#include "StringUtils.h"
#include "Version.h"

using namespace std;

namespace cpuh0g {
  class Option {
    public:
      Option (const string& name, const string& description, int defaultValue, bool hasValue = true) : 
        _name(name), _description(description), _value(defaultValue), _hasValue(hasValue) {
      }

      ~Option () {
      }
      
      bool hasValue () const {
        return _hasValue;
      }

      int getValue () const {
        return _value;
      }

      void setValue (const string& value) {
        _value = ::atoi(value.c_str());
      }
      
      const string& getDescription () const {
        return _description;
      }
      
      const string& getName () const {
        return _name;
      }
      
    private: 

      string _name;

      string _description;

      int _value;

      bool _hasValue;
  };

  class ApplicationOptions {
    public:
      ApplicationOptions (int argc, char** argv) : _options(), _argc(argc), _argv(argv), _executable(argv[0]) {
      }

      ~ApplicationOptions () {
      }

      void usage () const {
        size_t maxLength = 0;
        for (MapType::const_iterator i = _options.begin(); i != _options.end(); ++i) {
          size_t length = (*i).second.getName().size();

          if (length > maxLength) {
            maxLength = length;
          }
        }

        cout << "Usage: " << _executable << " [OPTIONS]" << endl;
        cout << endl;
        cout << "The following options are available:" << endl;
       
        for (MapType::const_iterator i = _options.begin(); i != _options.end(); ++i) {
          ostringstream value;
          if ((*i).second.hasValue()) {
            value << " (value: " << (*i).second.getValue() << ")";
          }
          cout << " " << setiosflags(ios::left) << setw(maxLength + 3) << (*i).second.getName() 
                      << setiosflags(ios::left) << (*i).second.getDescription() << value.str() << endl; 
        }

        cout << endl;
      }

      bool parse () {
        for (int i = 1; i < _argc; ++i) {
          string option = StringUtils::trim(_argv[i]);
         
          getValue(option);

          size_t pos = option.find('=');
          if (pos == string::npos) {
            // no =
            if (! hasValue(option)) {
              setValue(option, "1");
              continue;
            }

            if (i + 1 < _argc) {
              // use next argv
              if (! setValue(option, StringUtils::trim(_argv[i + 1]))) {
                return false;
              }
              ++i;
            }
          }
          else {
            // has =
            if (! setValue(StringUtils::trim(option.substr(0, pos)), StringUtils::trim(option.substr(pos + 1)))) {
              return false;
            }
          }
        }

        return true;
      }

      int getValue (const string& name) const {
        MapType::const_iterator i = _options.find(name);
        
        if (i == _options.end()) {
          ostringstream message;
          message << "invalid option " << name;
          throw message.str();
        }
        
        return (*i).second.getValue();
      }
      
      void addOption (const Option& option) {
        _options.insert(pair<string, Option>(option.getName(), option));
      }


    private:
      
      bool hasValue (const string& name) const {
        MapType::const_iterator i = _options.find(name);
        
        if (i == _options.end()) {
          return true;
        }
        
        return (*i).second.hasValue();
      }

      bool setValue (const string& name, const string& value) {
        MapType::iterator i = _options.find(name);

        if (i == _options.end()) {
          cerr << "invalid option " << name << endl;
          return false;
        }

        (*i).second.setValue(value);
        return true;
      }

      typedef map<string, Option> MapType;

      MapType _options;

      int _argc;

      char** _argv;

      string _executable;

  };
}

#endif

