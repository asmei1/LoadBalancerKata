#include "ServerLoadBalancerTest.h"

#include <gmock/gmock.h>

#include "ServerBuilder.h"

#include "Server.h"
#include "ServerBalancer.h"

void ServerLoadBalancerTest::SetUp()
{
}

std::vector<ServerSPtr> ServerLoadBalancerTest::aListOfServersWith(const ServerSPtr& server)
{
   return { server };
}

std::vector<VmSPtr> ServerLoadBalancerTest::aListOfVmsWith(const VmSPtr& vm)
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
   VmSPtr theVm = a(VmBuilder::vm().ofSize(1));
   balance(aListOfServersWith(theServer), aListOfVmsWith(theVm));

   EXPECT_THAT(*theServer, hasLoadPercentageOf(100.0));
   //the server should contain vm
   EXPECT_TRUE(theServer->contains(theVm));
}

TEST_F(ServerLoadBalancerTest, balancingOneServerWithTenSlotsCapacity_andOneSlotVm_fillTheServerWithTenPercent)
{
   ServerSPtr theServer = a(ServerBuilder::server().withCapacity(10));
   VmSPtr theVm = a(VmBuilder::vm().ofSize(1));
   balance(aListOfServersWith(theServer), aListOfVmsWith(theVm));

   EXPECT_THAT(*theServer, hasLoadPercentageOf(10.0));
   //the server should contain vm
   EXPECT_TRUE(theServer->contains(theVm));

}