// https://probablydance.com/2019/12/30/measuring-mutexes-spinlocks-and-how-bad-the-linux-scheduler-really-is/

#ifndef __LOCK_CONFIG_HPP__
#define __LOCK_CONFIG_HPP__

#define NUM_REENTRIES 1 << 18
#define WORK_LOAD 1 << 2
#define NUM_THREADS 1 << 7
#define NUM_SLOTS 1 << 7
#define NUM_RUNS 1 << 1

#include <type_traits>

using std::aligned_storage;
using std::alignment_of;

namespace lock {

typedef aligned_storage<63, alignment_of<bool>::value>::type Padding_63;
typedef aligned_storage<62, alignment_of<bool>::value>::type Padding_62;
typedef aligned_storage<61, alignment_of<bool>::value>::type Padding_61;
typedef aligned_storage<54, alignment_of<bool>::value>::type Padding_54;

}

#endif
