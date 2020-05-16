#pragma once
#include "Server.h"

class ServerBuilder
{
   ServerBuilder() = default;
public:
   ~ServerBuilder() = default;

   static ServerBuilder server()
   {
      return {};
   }

   ServerSPtr build() const
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

