#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ServerBuilder.h"
#include "Vm.h"

class ServerLoadBalancerTest : public ::testing::Test
{
protected:
   void SetUp() override;

   ServerBuilder server();
   ServerSPtr a(const ServerBuilder& builder);


   std::vector<ServerSPtr> aListOfServersWith(const ServerSPtr& server);
   std::vector<VmSPtr> anEmptyListOfVms();
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);
};


MATCHER_P(hasLoadPercentageOf, expectedPercentage, "a server with load percentage of ")
{
   return arg.actualLoadPercentage == expectedPercentage || abs(arg.actualLoadPercentage - expectedPercentage) < 0.01;
}


