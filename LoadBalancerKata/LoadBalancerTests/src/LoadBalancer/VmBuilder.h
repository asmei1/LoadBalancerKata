#pragma once
#include "Vm.h"

class VmBuilder
{
public:
   VmBuilder() = default;
   ~VmBuilder() = default;

   VmBuilder& ofSize(int size)
   {
      this->size = size;
      return *this;
   }

   VmSPtr build() const
   {
      return std::make_shared<Vm>(this->size);
   }

private:
   int size = 0;

};
