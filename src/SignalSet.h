
#ifndef CPUHOG_SIGNAL_SET_H
#define CPUHOG_SIGNAL_SET_H 1

#include <signal.h>

using namespace std;

namespace cpuh0g {
  class SignalSet {
    public:
      SignalSet () : _set() {
        clear();
      }

      ~SignalSet () {
      }

      void add (int signal) {
        ::sigaddset(&_set, signal); 
      }
      
      void remove (int signal) {
        ::sigdelset(&_set, signal); 
      }

      void clear () {
        ::sigemptyset(&_set);
      }

      sigset_t* ptr () {
        return &_set;
      }

    private:
      sigset_t _set;
  };
}

#endif
