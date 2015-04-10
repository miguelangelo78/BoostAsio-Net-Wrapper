#include "stdafx.h" // May need to delete this if not using precompiled headers
#include "net_handler.h"

boost::mutex global_lock;
#define TLOCK global_lock.lock();
#define TULOCK global_lock.unlock();

// Connection:
ServerConnection::ServerConnection(boost::shared_ptr< Hive > hive) : Connection(hive) {}

ServerConnection::~ServerConnection() {}

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
		std::cout << std::hex << std::setfill('0') <<
			std::setw(2) << (int) buffer[x] << " ";
		if ((x + 1) % 16 == 0)
		{
			std::cout << std::endl;
		}
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
	std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
	TULOCK;
}

void ServerConnection::OnError(const boost::system::error_code & error) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	TULOCK;
}

// Acceptor:
ServerAcceptor::ServerAcceptor(boost::shared_ptr< Hive > hive) : Acceptor(hive) {}

ServerAcceptor::~ServerAcceptor() {}

bool ServerAcceptor::OnAccept(boost::shared_ptr< Connection > connection, const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;

	return true;
}

void ServerAcceptor::OnTimer(const boost::posix_time::time_duration & delta) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
	TULOCK;
}

void ServerAcceptor::OnError(const boost::system::error_code & error) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	TULOCK;
}

void ClientConnection::OnAccept(const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;

	// Start the next receive
	Recv();
}

void ClientConnection::OnConnect(const std::string & host, uint16_t port) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
	TULOCK;
	
	// Start the next receive
	Recv();

	std::string str = "GET / HTTP/1.0\r\n\r\n";

	std::vector< uint8_t > request;
	std::copy(str.begin(), str.end(), std::back_inserter(request));
	Send(request);
}

void ClientConnection::OnSend(const std::vector< uint8_t > & buffer) {
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

void ClientConnection::OnRecv(std::vector< uint8_t > & buffer) {
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

	// Start the next receive
	Recv();
}

void ClientConnection::OnTimer(const boost::posix_time::time_duration & delta) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
	TULOCK;
}

void ClientConnection::OnError(const boost::system::error_code & error) {
	TLOCK;
	std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
	TULOCK;
}

ClientConnection::ClientConnection(boost::shared_ptr< Hive > hive): Connection(hive) {}

ClientConnection::~ClientConnection() {}
