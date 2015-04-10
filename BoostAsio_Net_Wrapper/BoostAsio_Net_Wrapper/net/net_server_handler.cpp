#include "stdafx.h" // May need to delete this if not using precompiled headers
#include "net_handler.h"

boost::mutex global_lock;

// Server events:

// Server Connection:
void ServerConnection::OnAccept(const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;

	// Start the next receive
	Recv();
}

void ServerConnection::OnConnect(const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;

	// Start the next receive
	Recv();
}

void ServerConnection::OnSend(const std::vector< uint8_t > & buffer) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
	for (size_t x = 0; x < buffer.size(); ++x)
	{
		std::cout << std::hex << std::setfill('0') <<
			std::setw(2) << (int) buffer[x] << " ";
		if ((x + 1) % 16 == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	TULOCK;
}

void ServerConnection::OnRecv(std::vector< uint8_t > & buffer) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
	for (size_t x = 0; x < buffer.size(); ++x)
	{
		std::cout << (char)buffer[x];
	}
	std::cout << std::endl;
	TULOCK;

	// Start the next receive
	Recv();

	// Echo the data back
	Send(buffer);
}

void ServerConnection::OnTimer(const boost::posix_time::time_duration & delta) {
	TLOCK;

	TULOCK;
}

void ServerConnection::OnError(const boost::system::error_code & error) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	TULOCK;
}

// Server Acceptor:
bool ServerAcceptor::OnAccept(boost::shared_ptr< Connection > connection, const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;

	return true;
}

void ServerAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
	TLOCK;
	
	TULOCK;
}

void ServerAcceptor::OnError(const boost::system::error_code & error) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	TULOCK;
}

// Server Handler:
void NetServer::server_work() {
	while (!_kbhit()) {
		updateHive();
	}
}
