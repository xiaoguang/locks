#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <pthread.h>
#include <tr1/functional>

namespace lock {

typedef std::tr1::function<void()> ThreadBody;
pthread_t makeThread(ThreadBody body);

}

#endif
