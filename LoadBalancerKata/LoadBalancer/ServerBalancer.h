#pragma once
#include <vector>


#include "Server.h"
#include "Vm.h"

class ServerBalancer
{
public:
   void balance(const std::vector<ServerSPtr>& servers, const std::vector<VmSPtr>& vms);
};

