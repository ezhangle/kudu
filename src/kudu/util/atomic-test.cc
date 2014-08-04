// Copyright (c) 2014, Cloudera, inc.

#include "kudu/util/atomic.h"

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace kudu {

// TODO Add some multi-threaded tests; currently AtomicInt is just a
// wrapper around 'atomicops.h', but should the underlying
// implemention change, it would help to have tests that make sure
// invariants are preserved in a multi-threaded environment.
TEST(Atomic, BasicOps) {
  std::vector<MemoryOrder> memory_orders = boost::assign::list_of
      (kMemOrderNoBarrier)
      (kMemOrderRelease)
      (kMemOrderAcquire);

  BOOST_FOREACH(const MemoryOrder mem_order, memory_orders) {
    AtomicInt<int64_t> i(0);
    EXPECT_EQ(0, i.Load(mem_order));
    i.Store(2, mem_order);
    EXPECT_EQ(2, i.Load(mem_order));
    EXPECT_TRUE(i.CompareAndSwap(2, 5, mem_order));
    EXPECT_EQ(5, i.Load(mem_order));
    EXPECT_EQ(5, i.CompareAndSwapVal(5, 7, mem_order));
    i.StoreMax(8, mem_order);
    EXPECT_EQ(8, i.Load(mem_order));
    i.StoreMax(7, mem_order);
    EXPECT_EQ(8, i.Load(mem_order));
    i.StoreMin(7, mem_order);
    EXPECT_EQ(7, i.Load(mem_order));
    i.StoreMin(9, mem_order);
    EXPECT_EQ(7, i.Load(mem_order));
    EXPECT_EQ(7, i.Exchange(11, mem_order));
    EXPECT_EQ(11, i.Load(mem_order));
  }

  memory_orders = boost::assign::list_of
      (kMemOrderBarrier)
      (kMemOrderNoBarrier);
  BOOST_FOREACH(const MemoryOrder mem_order, memory_orders) {
    AtomicInt<int64_t> i(0);
    EXPECT_EQ(1, i.Increment(mem_order));
    EXPECT_EQ(3, i.IncrementBy(2, mem_order));
  }
}

} // namespace kudu