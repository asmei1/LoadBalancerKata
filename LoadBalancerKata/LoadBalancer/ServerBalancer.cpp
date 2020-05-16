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
         return lhs->getActualLoadPercentage() < rhs->getActualLoadPercentage();
      });
}

std::vector<ServerSPtr> ServerBalancer::serversThatCanFitVm(const std::vector<ServerSPtr>& servers, VmSPtr vm)
{
   std::vector<ServerSPtr> serversThatCanFitVm;
   std::copy_if(servers.cbegin(), servers.cend(), std::back_inserter(serversThatCanFitVm), [vm](const auto& server)
      {
         return server->canFit(vm);
      });

   return serversThatCanFitVm;
}

void ServerBalancer::addToCapableLessLoadedServer(const std::vector<ServerSPtr>& servers, VmSPtr vm)
{
   if(auto server = extractLessLoadServer(serversThatCanFitVm(servers, vm));
      nullptr != server) 
   {
      server->addVm(vm);
   }
}

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   for(const auto& vm : vms)
   {
      addToCapableLessLoadedServer(servers, vm);
   }
}
