// Copyright (c) 2013, Cloudera, inc.

#include "kudu/util/net/dns_resolver.h"

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <gtest/gtest.h>

#include "kudu/util/countdown_latch.h"
#include "kudu/util/net/net_util.h"
#include "kudu/util/net/sockaddr.h"
#include "kudu/util/test_util.h"

namespace kudu {

class DnsResolverTest : public KuduTest {
 protected:
  DnsResolver resolver_;
};

TEST_F(DnsResolverTest, TestResolution) {
  vector<Sockaddr> addrs;
  Synchronizer s;
  {
    HostPort hp("localhost", 12345);
    resolver_.ResolveAddresses(hp, &addrs, s.AsStatusCallback());
  }
  ASSERT_STATUS_OK(s.Wait());
  ASSERT_TRUE(!addrs.empty());
  BOOST_FOREACH(const Sockaddr& addr, addrs) {
    LOG(INFO) << "Address: " << addr.ToString();
    EXPECT_TRUE(HasPrefixString(addr.ToString(), "127."));
    EXPECT_TRUE(HasSuffixString(addr.ToString(), ":12345"));
  }
}

} // namespace kudu