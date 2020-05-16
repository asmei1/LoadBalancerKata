#include "ServerBalancer.h"

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   for(const auto& vm : vms)
   {
      ServerSPtr lessLoaded = nullptr;
      for(const auto& server : servers)
      {
         if(nullptr == lessLoaded || lessLoaded->actualLoadPercentage > server->actualLoadPercentage)
         {
            lessLoaded = server;
         }
      }
      lessLoaded->addVm(vm);
   }
}
