#include "ServerLoadBalancerTest.h"

#include <gmock/gmock.h>

#include "ServerBuilder.h"
#include "VmBuilder.h"

#include "Server.h"
#include "ServerBalancer.h"

void ServerLoadBalancerTest::SetUp()
{
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

TEST_F(ServerLoadBalancerTest, balancingAServerWithEnoughRoom_getsFilledWithAllVms)
{
   ServerSPtr theServer = a(ServerBuilder::server().withCapacity(10));
   VmSPtr theFirstVm = a(VmBuilder::vm().ofSize(1));
   VmSPtr theSecondVm = a(VmBuilder::vm().ofSize(1));
   balance(aListOfServersWith(theServer), aListOfVmsWith(theFirstVm, theSecondVm));

   EXPECT_THAT(*theServer, hasVmsCountOf(2));
   //the server should contain vm
   EXPECT_TRUE(theServer->contains(theFirstVm));
   EXPECT_TRUE(theServer->contains(theSecondVm));
}

TEST_F(ServerLoadBalancerTest, aVm_shouldBeBalanced_onLessLoadedServerFirst)
{
   ServerSPtr lessLoadedServer = a(ServerBuilder::server().withCapacity(100).withCurrentLoadOf(45.0));
   ServerSPtr moreLoadedServer = a(ServerBuilder::server().withCapacity(100).withCurrentLoadOf(50.0));
   VmSPtr theVm = a(VmBuilder::vm().ofSize(10));

   balance(aListOfServersWith(moreLoadedServer, lessLoadedServer), aListOfVmsWith(theVm));

   //the less loaded server should contain vm
   EXPECT_TRUE(lessLoadedServer->contains(theVm));
}

TEST_F(ServerLoadBalancerTest, balanceAServerWithNotEnoughRoom_shouldNotBeFilledWithAVm)
{
   ServerSPtr theServer = a(ServerBuilder::server().withCapacity(10).withCurrentLoadOf(90.0));
   VmSPtr theVm = a(VmBuilder::vm().ofSize(2));
   balance(aListOfServersWith(theServer), aListOfVmsWith(theVm));

   EXPECT_FALSE(theServer->contains(theVm)) << "the less loaded server should not contain vm";
}

TEST_F(ServerLoadBalancerTest, balance_serversAndVms)
{
   ServerSPtr server1 = a(ServerBuilder::server().withCapacity(4));
   ServerSPtr server2 = a(ServerBuilder::server().withCapacity(6));

   VmSPtr vm1 = a(VmBuilder::vm().ofSize(1));
   VmSPtr vm2 = a(VmBuilder::vm().ofSize(4));
   VmSPtr vm3 = a(VmBuilder::vm().ofSize(2));

   balance(aListOfServersWith(server1, server2), aListOfVmsWith(vm1, vm2, vm3));

   EXPECT_TRUE(server1->contains(vm1)) << "The server 1 should contain the vm 1";
   EXPECT_TRUE(server2->contains(vm2)) << "The server 2 should contain the vm 2";
   EXPECT_TRUE(server1->contains(vm3)) << "The server 1 should contain the vm 3";

   EXPECT_THAT(*server1, hasLoadPercentageOf(75.0));
   EXPECT_THAT(*server2, hasLoadPercentageOf(66.66));
}