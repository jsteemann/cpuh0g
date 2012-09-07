
#ifndef CPUHOG_SIGNAL_HANDLER_H
#define CPUHOG_SIGNAL_HANDLER_H 1

#include <signal.h>
#include <pthread.h>

#include <map>

#include "SignalSet.h"

using namespace std;
      
namespace cpuh0g {
  enum SignalHandlerType {
    HANDLER_CONTINUE,
    HANDLER_EXIT
  };

  typedef SignalHandlerType(*SignalHandlerFunc)(int);
  
  typedef map<int, SignalHandlerFunc> SignalHandlersMapType;
  
  static sig_atomic_t shutdownInProgress = 0;
 
  static SignalHandlersMapType handlers; 


  class SignalHandler {
    public:
      SignalHandler () {
      }

      ~SignalHandler () {
      }
      
      void block (SignalSet* set) { 
        if (0 != ::pthread_sigmask(SIG_BLOCK, set->ptr(), NULL)) {
          throw "cannot set signalset";
        }
      }

      void unblock (SignalSet* set) {
        if (0 != ::pthread_sigmask(SIG_UNBLOCK, set->ptr(), NULL)) {
          throw "cannot unset signalset";
        }
      }
  
      bool installHandler (const int signal, SignalHandlerFunc handlerFunc) {
        struct sigaction sa;
        sa.sa_flags = 0;
        ::sigemptyset(&sa.sa_mask);
        sa.sa_handler = &signalHandler;

        if (0 == ::sigaction(signal, &sa, NULL)) {
          handlers[signal] = handlerFunc;
          return true;
        }

        return false;
      }
          
      void uninstallHandler (const int sig) {
        struct sigaction sa;
        ::sigemptyset(&sa.sa_mask);
        sa.sa_handler = SIG_DFL;

        ::sigaction(sig, &sa, NULL);
        handlers.erase(sig);
      }

      static void signalHandler (int sig) {
        if (shutdownInProgress) {
          return;
        }

        shutdownInProgress = 1;

        SignalHandlersMapType::const_iterator i = handlers.find(sig);
        if (i != handlers.end()) {
          SignalHandlerType result = (*i).second(sig);

          if (result == HANDLER_CONTINUE) {
            shutdownInProgress = 0;
            ::signal(sig, &signalHandler);
            return;
          }
        }

        ::raise(sig);
        exit(EXIT_FAILURE);
      }

  };
  
}

#endif
