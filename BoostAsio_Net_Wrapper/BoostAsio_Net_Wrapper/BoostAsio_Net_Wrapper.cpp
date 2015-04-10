#include "stdafx.h"
#include <iostream>
#include "net\net_handler.h"

void server_side() {
	// Server side:
	NetServer server("127.0.0.1", 23);
}

void client_side() {
	// Client side:
	NetClient client("www.google.com", 80);
}

int _tmain(int argc, _TCHAR* argv[]){
	//server_side();
	client_side();

	std::cin.get();
	return 0;
}
