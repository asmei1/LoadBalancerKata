#pragma once
#include "IBuilder.h"
#include "Server.h"

class ServerBuilder : public IBuilder<ServerSPtr>
{
   ServerBuilder() = default;
public:
   ~ServerBuilder() = default;

   static ServerBuilder server()
   {
      return {};
   }

   ServerSPtr build() const override
   {
      return std::make_shared<Server>(this->capacity);
   }

   ServerBuilder& withCapacity(int capacity)
   {
      this->capacity = capacity;
      return *this;
   }

private:
   int capacity;
};

