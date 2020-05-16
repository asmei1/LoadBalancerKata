#include "Server.h"

Server::Server(int capacity)
{
   this->capacity = capacity;
}

bool Server::contains(const VmSPtr& vm)
{
   return std::find(this->vms.cbegin(), this->vms.cend(), vm) != this->vms.cend();
}

bool Server::canFit(const VmSPtr& vm)
{
   return this->actualLoadPercentage + (static_cast<double>(vm->size) / this->capacity * MAXIMUM_LOAD) <= MAXIMUM_LOAD;
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

double Server::getCapacity() const
{
   return this->capacity;
}
