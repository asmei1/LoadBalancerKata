#pragma once
#include "IBuilder.h"
#include "Vm.h"

class VmBuilder : public IBuilder<VmSPtr>
{
   VmBuilder() = default;
public:
   ~VmBuilder() = default;

   static VmBuilder vm()
   {
      return {};
   }

   VmBuilder& ofSize(int size)
   {
      this->size = size;
      return *this;
   }

   VmSPtr build() const override
   {
      return std::make_shared<Vm>(this->size);
   }

private:
   int size = 0;

};
