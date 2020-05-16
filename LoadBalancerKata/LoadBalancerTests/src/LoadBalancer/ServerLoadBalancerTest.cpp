#include "ServerLoadBalancerTest.h"

#include <gmock/gmock.h>

#include "ServerBuilder.h"

#include "Server.h"
#include "ServerBalancer.h"

void ServerLoadBalancerTest::SetUp()
{
}
VmSPtr ServerLoadBalancerTest::a(const VmBuilder& builder)
{
   return builder.build();
}

VmBuilder ServerLoadBalancerTest::vm() const
{
   return {};
}

ServerSPtr ServerLoadBalancerTest::a(const ServerBuilder& builder)
{
   return builder.build();
}

std::vector<ServerSPtr> ServerLoadBalancerTest::aListOfServersWith(ServerSPtr server)
{
   return { server };
}

std::vector<VmSPtr> ServerLoadBalancerTest::aListOfVmsWith(VmSPtr vm)
{
   return { vm };
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
   ServerSPtr theServer = a(ServerBuilder::server().withCapacity(1));

   balance(aListOfServersWith(theServer), anEmptyListOfVms());

   EXPECT_THAT(*theServer, hasLoadPercentageOf(0.0));
}

TEST_F(ServerLoadBalancerTest, balancingOneServerWithOneSlotCapacity_andOneSlotVm_fillsTheServerWithTheVm)
{
   ServerSPtr theServer = a(ServerBuilder::server().withCapacity(1));
   VmSPtr theVm = a(vm().ofSize(1));
   balance(aListOfServersWith(theServer), aListOfVmsWith(theVm));

   EXPECT_THAT(*theServer, hasLoadPercentageOf(100.0));
   EXPECT_TRUE(theServer->contains(theVm)) << "the server should contain vm";
}