#include "ServerBalancer.h"

#include <algorithm>

ServerSPtr ServerBalancer::extractLessLoadServer(const std::vector<ServerSPtr>& servers)
{
   if(true == servers.empty())
   {
      return nullptr;
   }

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
      std::vector<ServerSPtr> serversThatCanFitVm;
      for(const auto& server : servers)
      {
         if(true == server->canFit(vm))
         {
            serversThatCanFitVm.push_back(server);
         }
      }

      
      if(auto server = extractLessLoadServer(serversThatCanFitVm);
         nullptr != server) 
      {
        server->addVm(vm);
      }

   }
}
