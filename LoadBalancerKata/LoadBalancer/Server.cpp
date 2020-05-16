#include "Server.h"

void Server::addVm(const VmSPtr& vm)
{
   this->actualLoadPercentage = (static_cast<double>(vm->size) / this->capacity) * MAXIMUM_LOAD;
}
