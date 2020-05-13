#include "TCP_Sender.h"


namespace {
	void setup()
	{
		WSAData wsa_data;
		WORD DLL_version = MAKEWORD(2, 2);
		if (FAILED(WSAStartup(DLL_version, &wsa_data)))
		{
			int error = WSAGetLastError();
			throw std::runtime_error("Failed to install Windows Sockets API (WSA). Error code: " + std::to_string(error));
		}
	}
}



void TCP_Sender::Send(std::vector<uint8_t> const & data)
{
	if (data.size() < 1 || data.size() >= max_size_pack)
		throw std::range_error("Data size less than 1 or more " + std::to_string(max_size_pack));
	

	SOCKET Connection;
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (FAILED(connect(Connection, (SOCKADDR*)&addr, sizeof(addr))))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to connect. Error code: " + std::to_string(error));
	}

	std::vector<uint8_t> msg;
	msg.resize(2);
	msg[0] = (data.size()) >> 8;
	msg[1] = (data.size());

	std::copy(data.begin(), data.end(), std::back_inserter(msg));

	if (FAILED(send(Connection, (char*)msg.data(), msg.size(), NULL)))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to send. Error code: " + std::to_string(error));
	}

	closesocket(Connection);
}


TCP_Sender::TCP_Sender(uint32_t IP, unsigned short int port)
{
	setup();
	addr.sin_addr.s_addr = htonl(IP);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

}

TCP_Sender::~TCP_Sender()
{
	WSACleanup();
}








