#pragma once
#include <memory>
#include <vector>

#include "Vm.h"

class Server
{
   const static inline double MAXIMUM_LOAD = 100.;
   std::vector<VmSPtr> vms;

public:
   Server(int capacity);

   bool contains(const VmSPtr& vm);

   double getCapacity() const;

   void addVm(const VmSPtr& vm);

   int getVmsCount() const;

   double actualLoadPercentage = 0;

private:
   int capacity = 0;
};

using ServerSPtr = std::shared_ptr<Server>;