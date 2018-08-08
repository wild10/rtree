//============================================================================
// Name        : TcpServer.h
// Author      : Daniel Palomino
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : RTree Backend
// Created on  : 31 jul. 2018
//============================================================================

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include "utils.h"

/*
TRAMA:

QUERIES:
* DELETE|0|END
* INSERT|1|100|230|END
* RANGE|2|120|360|520|450|END
* NEAREST|K|120|320|END

RESPONSES:
* SUCCESS|0|END

COMMAND|N|X1|Y1|X2|Y2|END

COMMAND: Comando a utilizar en el rtree.
N: Numero de Coordenadas siguientes.
(X1,Y1): Primera coordenada.
END: Flag finalizador.

------------------------------------------
* OBJECTS|2|1|12|32|2|65|256|23|65|END

COMMAND|K|N1|X1|Y1|...|N2|X1|Y1|...|END

COMMAND: Comando a utilizar en el rtree.
K: Numero de objetos siguientes
N1: Numero de Coordenadas del objeto siguiente.
(X1,Y1): Primera coordenada.

------------------------------------------

* MBR|2|2|120|360|520|450|2|120|360|520|450|END

COMMAND|K|N1|X1|Y1|...|N2|X1|Y1|...|END

COMMAND: Comando a utilizar en el rtree.
K: Numero de MBRs siguientes
N1=2: Numero de Coordenadas del MBR siguiente.
((X1,Y1),(X2,Y2)): Primer MBR.

*/

using namespace std;

class TcpServer
{
private:
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;

	map<string, command> cmd{
		{ "DELETE", DELETE },
		{ "INSERT", INSERT },
		{ "RANGE", RANGE },
		{ "NEAREST", NEAREST },
		{ "SUCCESS", SUCCESS },
		{ "OBJECTS", OBJECTS },
		{ "MBR", MBR }
	};

public:
	struct message client_message;

public:
	TcpServer(string host, int port);
	bool bindSocket();
	void listenToClient();
	bool acceptConnection();
	bool sendData(string data);
	bool receiveData(int size);
	void split(const string& s, char delimiter, string& command, vector<pair<int, int>>& tokens);
	void join(const string& command, vector<vector<pair<int, int>>>& objects, string& output);
};

#endif