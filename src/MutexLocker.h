
#ifndef CPUHOG_MUTEX_LOCKER_H
#define CPUHOG_MUTEX_LOCKER_H 1

#include "Mutex.h"

using namespace std;

namespace cpuh0g {
  class MutexLocker {
    public:
      MutexLocker (Mutex* mutex) : _mutex(mutex) {
        _mutex->lock();
      }

      ~MutexLocker () {
        _mutex->unlock();
      }

    private:
      Mutex* _mutex;

  };
}

#endif
