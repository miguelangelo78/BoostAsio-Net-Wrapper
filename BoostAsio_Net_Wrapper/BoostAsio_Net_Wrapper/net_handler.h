#pragma once
#include "network_sockapi.h"
#include <boost\thread\mutex.hpp>

class ServerConnection : public Connection
{
private:
	void OnAccept(const std::string & host, uint16_t port);
	void OnConnect(const std::string & host, uint16_t port);
	void OnSend(const std::vector< uint8_t > & buffer);
	void OnRecv(std::vector< uint8_t > & buffer);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	ServerConnection(boost::shared_ptr< Hive > hive);
	~ServerConnection();
};

class ServerAcceptor : public Acceptor
{
private:
	bool OnAccept(boost::shared_ptr< Connection > connection, const std::string & host, uint16_t port);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);

public:
	ServerAcceptor(boost::shared_ptr< Hive > hive);
	~ServerAcceptor();
};

class ClientConnection : public Connection {
private:
	void OnAccept(const std::string & host, uint16_t port);
	void OnConnect(const std::string & host, uint16_t port);
	void OnSend(const std::vector< uint8_t > & buffer);
	void OnRecv(std::vector< uint8_t > & buffer);
	void OnTimer(const boost::posix_time::time_duration & delta);
	void OnError(const boost::system::error_code & error);
public:
	ClientConnection(boost::shared_ptr< Hive > hive);
	~ClientConnection();
};

typedef boost::shared_ptr<Hive> sptr_hive_t;
typedef boost::shared_ptr<ServerAcceptor> sptr_sacceptor_t;
typedef boost::shared_ptr<ServerConnection> sptr_sconn_t;
typedef boost::shared_ptr<ClientConnection> sptr_cconn_t;

#define NEW_HIVE new Hive()
#define NEW_SACCEPTOR(hive) new ServerAcceptor(hive)
#define NEW_SCONNECTION(hive) new ServerConnection(hive)
#define NEW_CCONNECTION(hive) new ClientConnection(hive)