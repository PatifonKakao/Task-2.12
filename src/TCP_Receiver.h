#pragma once

#pragma comment( lib, "wsock32.lib" )
#include <winsock2.h>

#include <vector>
#include <stdexcept>
#include <string>


class TCP_Receiver
{
public:

	std::vector<uint8_t> Receive();
	TCP_Receiver(uint32_t IP, unsigned short int port);
	~TCP_Receiver();

private:

	SOCKADDR_IN addr;
	SOCKET sListen;

	static const unsigned short int max_size_pack = 65535;

};