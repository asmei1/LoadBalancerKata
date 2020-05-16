#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include "VmBuilder.h"
#include "Tools/Helper.h"

#include "Server.h"
#include "Vm.h"

class ServerBuilder;

class ServerLoadBalancerTest : public ::testing::Test
{
protected:
   void SetUp() override;

   template<typename T>
   auto a(const T& builder)
   {
      return builder.build();
   }

   std::vector<ServerSPtr> aListOfServersWith(const ServerSPtr& server);
   std::vector<VmSPtr> aListOfVmsWith(const VmSPtr& vm);
   std::vector<VmSPtr> anEmptyListOfVms();
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);
};


MATCHER_P(hasLoadPercentageOf, expectedPercentage, "a server with load percentage of ")
{
   const double EPSILON = 0.01;
   return areDoubleSame(arg.actualLoadPercentage, expectedPercentage, EPSILON);
}


