#include "ServerLoadBalancerTest.h"

void ServerLoadBalancerTest::SetUp()
{
}

TEST_F(ServerLoadbalancerTest, balancingAServer_noVms_serverStaysEmpty)
{
   Server theServer = a(server().withCapacity(1));

   balance(aListOfServersWith(theServer), anEmptyListOfVms());

   EXPECT_THAT(theServer, hasLoadPercentageOf(0.0));
}