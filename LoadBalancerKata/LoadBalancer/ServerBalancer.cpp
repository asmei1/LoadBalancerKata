#include "ServerBalancer.h"

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   for(const auto& vm : vms)
   {
      servers.at(0)->addVm(vm);
   }
}
