#include "Server.h"

Server::Server(int capacity)
{
   this->capacity = capacity;
}

void Server::addVm(const VmSPtr& vm)
{
   this->vms.push_back(vm);

   this->actualLoadPercentage = (static_cast<double>(vm->size) / this->capacity) * MAXIMUM_LOAD;
}

int Server::getVmsCount() const
{
   return this->vms.size();
}
