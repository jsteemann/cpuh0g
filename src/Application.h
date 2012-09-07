
#ifndef CPUHOG_APPLICATION_H
#define CPUHOG_APPLICATION_H 1

#include <sys/time.h>
#include <errno.h>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

#include "ApplicationOptions.h"
#include "SignalHandler.h"
#include "Thread.h"
#include "Version.h"

using namespace std;

namespace cpuh0g {
  class Application {
    public:
      static SignalHandlerType signalHandler (int sig) {
        cout << "caught termination signal" << endl;
        return HANDLER_EXIT;
      }

      Application () : _signalHandler() {
        _signalHandler.installHandler(SIGINT, &signalHandler);
      }
     

      ~Application () {
      }

      int run (ApplicationOptions& options) {
        options.addOption(Option("--threads",  "number of threads", 1));
        options.addOption(Option("--duration", "run duration (in seconds)", 5));
        options.addOption(Option("--silent",   "be silent", 0, false));
        options.addOption(Option("--version",  "print version information and exit", 0, false));
        options.addOption(Option("--help",     "print help and exit", 0, false));

        if (! options.parse()) {
          options.usage();
          return EXIT_FAILURE;
        }
        else if (options.getValue("--help")) {
          options.usage();
          return EXIT_SUCCESS;
        }
        else if (options.getValue("--version")) {
          cout << Version::get() << endl;
          return EXIT_SUCCESS;
        }

        int numThreads = options.getValue("--threads");
        int duration = options.getValue("--duration");
        int verbose = ! options.getValue("--silent");
        int i;

        vector<Thread*> threads;
        for (i = 0; i < numThreads; ++i) {
          Thread* t = new Thread();
          threads.push_back(t);
        }

        this->sleep(0.1);

        if (verbose) {
          cout << timestring("%Y-%m-%d %H:%M:%S") << " hogging CPU time with " << numThreads << " thread(s) now for " << duration << " second(s)" << endl;
        }

        for (i = 0; i < numThreads; ++i) {
          threads[i]->start();
        }

        this->sleep((double) duration);
        
        for (i = 0; i < numThreads; ++i) {
          Thread* t = threads[i];
          t->join();
          delete t;
        }
        
        if (verbose) {
          cout << timestring("%Y-%m-%d %H:%M:%S") << " finished hogging CPU time" << endl;
        }

        return EXIT_SUCCESS;
      }

    private:
      static string timestring (const char* format) {
        time_t t = ::time(NULL);
        char mbstr[32];

        if (::strftime(mbstr, sizeof(mbstr), format, ::localtime(&t))) {
          return string(mbstr);
        }
        return "-";
      }

      void sleep (const double seconds) {
        struct timespec timeout;

        timeout.tv_sec = (long) seconds;
        timeout.tv_nsec = (long) ((seconds - (double) timeout.tv_sec) * 1000000000.0);

        do {
          if (0 == ::nanosleep(&timeout, &timeout) || EINTR != errno) {
            break;
          }
        } while (1);
      }

    private:
      SignalHandler _signalHandler;

  };
}

#endif
