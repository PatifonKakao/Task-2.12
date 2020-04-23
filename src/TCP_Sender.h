#pragma once

#pragma comment( lib, "wsock32.lib" )
#include <winsock2.h>

#include <vector>
#include <stdexcept>
#include <string>


class TCP_Sender 
{
public:
	void Send(std::vector<uint8_t> const &data);

	TCP_Sender(uint32_t IP, unsigned short int port);
	~TCP_Sender();

private:
	SOCKADDR_IN addr;

	static const unsigned short int max_size_pack = 65535;

};

