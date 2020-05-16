#pragma once
#include <memory>

class Server
{
public:
   Server(int capacity)
   {
   }

   double actualLoadPercentage = 0;

private:
};

using ServerSPtr = std::shared_ptr<Server>;