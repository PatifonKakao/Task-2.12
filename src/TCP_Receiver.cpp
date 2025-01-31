#include "TCP_Receiver.h"


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



std::vector<uint8_t> TCP_Receiver::Receive()
{
	
	SOCKET newConnection;
	int size_of_addr = sizeof(addr);
	if (FAILED(newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr)))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to switch socket to accept mode. Error code: " + std::to_string(error));
	}
	
	std::vector<uint8_t> msg;
	msg.resize(max_size_pack);

	if (FAILED(recv(newConnection, (char*)msg.data(), max_size_pack, NULL)))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to receive. Error code: " + std::to_string(error));
	}

	closesocket(newConnection);

	unsigned short int size_msg = 0;
	size_msg = msg[1];
	size_msg |= msg[0] << 8;

	if (size_msg > 0) 
	{
		std::vector<uint8_t> out_data;
		std::copy(msg.begin() + 2, msg.begin() + size_msg + 2, std::back_inserter(out_data));
		return out_data;
	}
	if (size_msg == 0)
		return {};
}


TCP_Receiver::TCP_Receiver(uint32_t IP, unsigned short int port)
{
	setup();
	int size_of_addr = sizeof(addr);
	addr.sin_addr.s_addr = htonl(IP);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	sListen = socket(AF_INET, SOCK_STREAM, NULL);

	if (SOCKET_ERROR == bind(sListen, (SOCKADDR*)&addr, size_of_addr))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to bind socket. Error code: " + std::to_string(error));
	}

	if (FAILED(listen(sListen, SOMAXCONN)))
	{
		int error = WSAGetLastError();
		throw std::runtime_error("Failed to put socket in listening state. Error code: " + std::to_string(error));
	}
}

TCP_Receiver::~TCP_Receiver()
{
	closesocket(sListen);
	WSACleanup();
}


