#include <gtest/gtest.h>
#include "TCP_Receiver.h"
#include "TCP_Sender.h"

#include <thread>
#include <ctime>




TEST(TCP_test, stat_test_1)
{

	uint32_t IP = (127 << 24) | 1;
	TCP_Receiver rec(IP, 1111);
	TCP_Sender send(IP, 1111);

	std::vector<uint8_t> receiv_data;

	std::thread th([&] 
	{
		receiv_data = rec.Receive();
	});

	std::vector<uint8_t> vect_send = {1,2,4,5,6,3,78,9,0};
	send.Send(vect_send);

	th.join();

	EXPECT_TRUE(vect_send == receiv_data);
}

TEST(TCP_test, stat_test_2)
{

	uint32_t IP = (127 << 24) | 1;
	TCP_Receiver rec(IP, 1111);
	TCP_Sender send(IP, 1111);

	std::vector<uint8_t> receiv_data;

	std::thread th([&]
	{
		receiv_data = rec.Receive();
	});

	std::vector<uint8_t> vect_send = { 0 };
	send.Send(vect_send);

	th.join();

	EXPECT_TRUE(vect_send == receiv_data);
}


TEST(TCP_test, rand_test_1)
{

	uint32_t IP = (127 << 24) | 1;
	TCP_Receiver rec(IP, 1111);
	TCP_Sender send(IP, 1111);

	std::vector<uint8_t> receiv_data;

	std::thread th([&]
	{
		receiv_data = rec.Receive();
	});

	srand(time(NULL));

	auto size = 10000;
	std::vector<uint8_t> vect_send(size);
	for (auto &i : vect_send)
	{
		i = rand() % 255;
	}
	
	send.Send(vect_send);

	th.join();

	EXPECT_TRUE(vect_send == receiv_data);
}



TEST(TCP_test, rand_test_2)
{

	uint32_t IP = (127 << 24) | 1;
	TCP_Receiver rec(IP, 1111);
	TCP_Sender send(IP, 1111);

	std::vector<uint8_t> receiv_data;

	std::thread th([&]
	{
		receiv_data = rec.Receive();
	});

	srand(time(NULL));

	auto size = rand()%65000+1;
	std::vector<uint8_t> vect_send(size);
	for (auto &i : vect_send)
	{
		i = rand() % 255;
	}

	send.Send(vect_send);

	th.join();

	EXPECT_TRUE(vect_send == receiv_data);
}


int main(int argc, char* argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}