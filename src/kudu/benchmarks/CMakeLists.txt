# Copyright 2012 Cloudera, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(TPCH_SRCS
  tpch/rpc_line_item_dao.cc
)

add_library(tpch ${TPCH_SRCS})
target_link_libraries(tpch
  kudu_client
  integration-tests)

# tpch1
add_executable(tpch1 tpch/tpch1.cc)
target_link_libraries(tpch1
  tpch
  ${KUDU_TEST_LINK_LIBS})

# tpch_real_world
add_executable(tpch_real_world tpch/tpch_real_world.cc)
target_link_libraries(tpch_real_world
  tpch
  ${KUDU_TEST_LINK_LIBS})

# rle
add_executable(rle rle.cc)
target_link_libraries(rle
  kudu_util
  ${KUDU_TEST_LINK_LIBS})

# wal_hiccup
add_executable(wal_hiccup wal_hiccup.cc)
target_link_libraries(wal_hiccup
  kudu_util
  ${KUDU_TEST_LINK_LIBS})

# Tests
set(KUDU_TEST_LINK_LIBS tpch ${KUDU_TEST_LINK_LIBS})
ADD_KUDU_TEST(tpch/rpc_line_item_dao-test)
