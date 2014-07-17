# Copyright (c) 2012, Cloudera, inc.

set(TPCH_SRCS
  tpch/rpc_line_item_dao.cc
)

add_library(tpch ${TPCH_SRCS})
target_link_libraries(tpch
  client
  integration-tests)

# tpch1
add_executable(tpch1 tpch/tpch1.cc)
target_link_libraries(tpch1
  tpch
  ${KUDU_TEST_LINK_LIBS})

# ms3_demo
add_executable(ms3_demo tpch/ms3_demo.cc tpch/rpc_line_item_dao.cc)
target_link_libraries(ms3_demo
  client
  tpch
  ${KUDU_TEST_LINK_LIBS})

# rle
add_executable(rle rle.cc)
target_link_libraries(rle
  kudu_util
  ${KUDU_TEST_LINK_LIBS})

# Tests
set(KUDU_TEST_LINK_LIBS tpch ${KUDU_TEST_LINK_LIBS})
ADD_KUDU_TEST(tpch/rpc_line_item_dao-test)