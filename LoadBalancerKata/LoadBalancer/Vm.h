#pragma once
#include <memory>

class Vm
{
public:
   Vm(int size)
   {
      this->size = size;
   }

   int size = 0;
};

using VmSPtr = std::shared_ptr<Vm>;

