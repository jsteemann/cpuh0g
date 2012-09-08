
#ifndef CPUHOG_THREAD_H
#define CPUHOG_THREAD_H 1

#include <pthread.h>
#include <signal.h>
#include <sys/prctl.h>
#include <stdint.h>

#include "Condition.h"

using namespace std;

namespace cpuh0g {
  class Thread {
    public:
      Thread (const string& name) : _condition(), _thread(), _attributes(), _name(name), _killed(0) {
        if (0 != ::pthread_attr_init(&_attributes)) {
          throw "cannot create thread attributes";
        }

        if (0 != ::pthread_attr_setdetachstate(&_attributes, PTHREAD_CREATE_DETACHED)) {
          throw "cannot create thread state";
        }

        if (0 != ::pthread_create(&_thread, NULL, &threadStarter, (void*) this)) {
          throw "cannot create thread";
        }
      }

      ~Thread () {
        ::pthread_attr_destroy(&_attributes);
      }

      const string& getName () const {
        return _name;
      }

      void start () {
        _condition.broadcast();
      }

      void join () {
        _killed = 1;
        ::pthread_join(_thread, NULL);
      }

      typedef void*(*startRoutine)(void*);

    private:
      static void* threadStarter (void* data) {
        Thread* thread = (Thread*) data;

        ::prctl(PR_SET_NAME, thread->getName().substr(0, 16).c_str(), 0, 0, 0);
        thread->wait();
        thread->execute();
      }

      void wait () {
        _condition.wait();
      }
      
      void execute () {
        volatile uint64_t value = 0;

        while (! _killed) {
          value++;
        }
      }

    private:
      Condition _condition;

      pthread_t _thread;

      pthread_attr_t _attributes;

      string _name;

      volatile sig_atomic_t _killed;

  };

}

#endif
