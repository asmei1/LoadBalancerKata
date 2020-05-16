#pragma once
#include <vector>


#include "Server.h"
#include "Vm.h"

class ServerBalancer
{
public:
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);

private:
   void addToCapableLessLoadedServer(const std::vector<ServerSPtr>& servers, VmSPtr vm);
   ServerSPtr extractLessLoadServer(const std::vector<ServerSPtr>& servers);
   std::vector<ServerSPtr> serversThatCanFitVm(const std::vector<ServerSPtr>& servers, VmSPtr vm);
};

