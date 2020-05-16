#pragma once
#include "Server.h"

class ServerBuilder
{
public:
   ServerBuilder() = default;
   ~ServerBuilder() = default;

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

