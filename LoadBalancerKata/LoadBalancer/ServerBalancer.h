#pragma once
#include <vector>


#include "Server.h"
#include "Vm.h"

class ServerBalancer
{
public:
   ServerSPtr extractLessLoadServer(const std::vector<ServerSPtr>& servers);
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);
};

