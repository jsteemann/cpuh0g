
#ifndef CPUHOG_MUTEX_H
#define CPUHOG_MUTEX_H 1

#include <pthread.h>

using namespace std;

namespace cpuh0g {
  class Mutex {
    public:
      Mutex () {
        if (0 != ::pthread_mutex_init(&_mutex, NULL)) {
          throw "cannot initialize mutex";
        }
      }

      ~Mutex () {
        if (0 != pthread_mutex_destroy(&_mutex)) {
          throw "cannot destroy mutex";
        }
      }

      inline pthread_mutex_t* ptr () {
        return &_mutex;
      }

      inline void lock () {
        if (0 != ::pthread_mutex_lock(&_mutex)) {
          throw "cannot lock mutex";
        }
      }

      inline void unlock () {
        if (0 != ::pthread_mutex_unlock(&_mutex)) {
          throw "cannot unlock mutex";
        }
      }
      
    private:
      Mutex (const Mutex&);

      Mutex& operator= (const Mutex&);

    private:
      pthread_mutex_t _mutex;

  };
}

#endif
