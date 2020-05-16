#pragma once
#include "IBuilder.h"
#include "Server.h"
#include "VmBuilder.h"

class ServerBuilder : public IBuilder<ServerSPtr>
{
   ServerBuilder() = default;
public:
   ~ServerBuilder() = default;


   ServerBuilder& withCurrentLoadOf(double currentLoad)
   {
      this->currentLoad = currentLoad;
      return *this;
   }

   static ServerBuilder server()
   {
      return {};
   }

   ServerSPtr build() const override
   {
      auto server = std::make_shared<Server>(this->capacity);

      if(0 < this->currentLoad)
      {
         int expectedLoad = static_cast<int>(this->currentLoad / 100 * server->getCapacity());
         server->addVm(VmBuilder::vm().ofSize(expectedLoad).build());
      }

      return server;
   }

   ServerBuilder& withCapacity(int capacity)
   {
      this->capacity = capacity;
      return *this;
   }

private:
   double currentLoad = 0;
   int capacity;
};

