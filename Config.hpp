#ifndef __LOCK_CONFIG_HPP__
#define __LOCK_CONFIG_HPP__

#define WORK_LOAD 1 << 10
#define NUM_THREADS 1 << 4
#define NUM_SLOTS 1 << 4
#define NUM_RUNS 1 << 2
#define NUM_REENTRIES 1 << 12

#include <type_traits>

using std::aligned_storage;
using std::alignment_of;

namespace lock {

typedef aligned_storage<63, alignment_of<bool>::value>::type Padding_63;
typedef aligned_storage<62, alignment_of<bool>::value>::type Padding_62;

}

#endif
