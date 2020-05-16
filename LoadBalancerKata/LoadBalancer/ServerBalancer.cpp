#include "ServerBalancer.h"

#include <algorithm>

ServerSPtr ServerBalancer::extractLessLoadServer(const std::vector<ServerSPtr>& servers)
{
   return *std::min_element(servers.cbegin(), servers.cend(),
      [](const auto& lhs, const auto& rhs)
      {
         return lhs->actualLoadPercentage < rhs->actualLoadPercentage;
      });
}

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   for(const auto& vm : vms)
   {
      extractLessLoadServer(servers)->addVm(vm);
   }
}
