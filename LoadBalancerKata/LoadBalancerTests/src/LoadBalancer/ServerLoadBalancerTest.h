#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

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

   template<typename ... Args>
   std::vector<VmSPtr> aListOfVmsWith(const Args... vm)
   {
      return { vm ... };
   }
   std::vector<VmSPtr> anEmptyListOfVms();

   template<typename ... Args>
   std::vector<ServerSPtr> aListOfServersWith(const Args... servers)
   {
      return { servers... };
   }
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);
};


MATCHER_P(hasLoadPercentageOf, expectedPercentage, std::string("a server with load percentage of ")
   .append(std::to_string(expectedPercentage))
   .append("%").c_str())
{
   const double EPSILON = 0.01;
   *result_listener << "is " << arg.actualLoadPercentage << "%";
   return areDoubleSame(arg.actualLoadPercentage, expectedPercentage, EPSILON);
}


MATCHER_P(hasVmsCountOf, vmCount, std::string("a server contains ")
   .append(std::to_string(vmCount))
   .append(" vms").c_str())
{
   const double EPSILON = 0.01;
   *result_listener << "contains " << arg.actualLoadPercentage << " vms instead";
   return arg.getVmsCount() == vmCount;
}


