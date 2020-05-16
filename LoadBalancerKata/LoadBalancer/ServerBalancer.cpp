#include "ServerBalancer.h"

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   if(vms.size() > 0)
   {
      servers.at(0)->addVm(vms[0]);
   }
}
