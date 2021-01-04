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

//send a coordinate to the other player
void sendToPlayer(sockaddr_in, string, string);
void sendMessage(string, string);

//send a setting to the other player
void sendSetting(string);
void sendSettingToPlayer(sockaddr_in,string);

//receive a string from the sender
string recvFromPlayer(SOCKET, sockaddr_in);
string recvMessage();

char* stringToCharArray(string, string);
//creating Address
sockaddr_in createAddress();
//Binding players together with the address
SOCKET bindPlayers(sockaddr_in Address);

