#include "stdafx.h"
#include "net_handler.h"
#include <conio.h>
#include <iostream>

void server_side() {
	// Server side:
	sptr_hive_t hive(NEW_HIVE);
		
	sptr_sacceptor_t acceptor(NEW_SACCEPTOR(hive));
	acceptor->Listen("127.0.0.1", 23);

	sptr_sconn_t conn(NEW_SCONNECTION(hive));
	acceptor->Accept(conn);

	while (!_kbhit()) {
		hive->Poll();
		Sleep(1);
	}

	hive->Stop();
}

void client_side() {
	// Client side:
	sptr_hive_t hive(NEW_HIVE);
	sptr_cconn_t conn(NEW_CCONNECTION(hive));
	conn->Connect("www.google.com", 80);
	
	while (!_kbhit()) {
		hive->Poll();
		Sleep(1);
	}

	hive->Stop();
}

int _tmain(int argc, _TCHAR* argv[]){
	//server_side();
	client_side();

	std::cin.get();
	return 0;
}
