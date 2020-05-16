#include "ServerBalancer.h"

void ServerBalancer::balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms)
{
   if(vms.size() > 0)
   {
      servers.at(0)->actualLoadPercentage = static_cast<double>(vms[0]->size) / servers[0]->capacity * 100.;
   }
}
