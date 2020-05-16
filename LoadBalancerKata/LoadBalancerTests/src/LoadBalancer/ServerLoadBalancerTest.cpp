#include "ServerLoadBalancerTest.h"

#include <gmock/gmock.h>


#include "Server.h"
#include "ServerBalancer.h"

void ServerLoadBalancerTest::SetUp()
{
}

ServerBuilder ServerLoadBalancerTest::server()
{
   return {};
}

ServerSPtr ServerLoadBalancerTest::a(const ServerBuilder& builder)
{
   return builder.build();
}

std::vector<ServerSPtr> ServerLoadBalancerTest::aListOfServersWith(const ServerSPtr& server)
{
   return { server };
}

std::vector<VmSPtr> ServerLoadBalancerTest::anEmptyListOfVms()
{
   return {};
}

void ServerLoadBalancerTest::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   ServerBalancer().balance(servers, vms);
}

TEST_F(ServerLoadBalancerTest, balancingAServer_noVms_serverStaysEmpty)
{
   ServerSPtr theServer = a(server().withCapacity(1));

   balance(aListOfServersWith(theServer), anEmptyListOfVms());

   EXPECT_THAT(*theServer, hasLoadPercentageOf(0.0));
}