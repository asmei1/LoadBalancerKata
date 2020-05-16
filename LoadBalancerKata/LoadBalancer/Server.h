#pragma once
#include <memory>
#include <vector>

#include "Vm.h"

class Server
{
   const static inline double MAXIMUM_LOAD = 100.;

public:
   Server(int capacity)
   {
      this->capacity = capacity;
   }

   bool contains(const VmSPtr& vm)
   {
      return true;
   }

   void addVm(const VmSPtr& vm);

   double actualLoadPercentage = 0;

private:
   int capacity = 0;
};

using ServerSPtr = std::shared_ptr<Server>;