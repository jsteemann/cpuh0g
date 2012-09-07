
#ifndef CPUHOG_CONDITION_H
#define CPUHOG_CONDITION_H 1

#include <pthread.h>

#include "Mutex.h"
#include "MutexLocker.h"

using namespace std;

namespace cpuh0g {
  class Condition {
    public:
      Condition () : _mutex() {
        ::pthread_cond_init(&_condition, NULL);
      }

      virtual ~Condition () {
        ::pthread_cond_destroy(&_condition);
      }

      void wait () {
        MutexLocker mutex(&_mutex);
        ::pthread_cond_wait(&_condition, _mutex.ptr());
      }

      inline void signal () {
        MutexLocker mutex(&_mutex);
        ::pthread_cond_signal(&_condition);
      }

      inline void broadcast () {
        MutexLocker mutex(&_mutex);
        ::pthread_cond_broadcast(&_condition);
      }
      
    private:
      Condition (const Condition&);

      Condition& operator= (const Condition&);

    private:
      Mutex _mutex;

      pthread_cond_t _condition;

  };
}

#endif
