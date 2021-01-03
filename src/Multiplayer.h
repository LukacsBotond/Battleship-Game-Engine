#pragma once
#include <stdio.h>
#include "winsock2.h"
#include <Ws2tcpip.h>
#include <iostream>
#include <string.h>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

//Initializing winsock,with this we can use sockets to send data
void InitializeWinsock();

string recvFromPlayer(SOCKET, sockaddr_in);

void sendToPlayer(sockaddr_in, string, string);

void sendMessage(string, string);

void sendSetting(string);

void sendSettingToPlayer(sockaddr_in,string);

string recvMessage();

char* stringToCharArray(string, string);

sockaddr_in createAddress();

SOCKET bindPlayers(sockaddr_in Address);

