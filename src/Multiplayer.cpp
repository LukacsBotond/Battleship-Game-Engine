#include "Multiplayer.h"


void InitializeWinsock()
{
	WSADATA wsaData;
	int result;

	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
	{
		cout << "Hiba a WSAStartup() –nál\n";
	}
	//cout << "initialize test" << endl;
}

/*void stringToCharArray(string s, string s1, char* char_array)
{
	string fullString = s + "." + s1;

	//char* char_array;

	char_array = &fullString[0];

	//cout << char_array;
	//return char_array;

}*/

string CharArrayToString(char* array)
{
	string s(array);

	return s;
}


string recvFromPlayer(SOCKET PlayerSocket, sockaddr_in Address)
{
	const int messageLen = 25;
	char message[messageLen];
	int result;
	int addressSize = sizeof(Address);
	string coordinates;

	cout << "waiting for message" << endl;
	//recvfrom waits for a message to arrive
	result = recvfrom(PlayerSocket, message, messageLen, 0, (SOCKADDR*)&Address, &addressSize);

	if (result == SOCKET_ERROR)
	{
		cout << "Hiba a fogadasnal a kovetkezo hibakoddal:\n" << WSAGetLastError();
		closesocket(PlayerSocket);
		WSACleanup();
		return "";
	}

	message[result] = '\0';

	//convert the char array message to a string
	coordinates = CharArrayToString(message);

	//cout << "Received message:" << coordinates;

	if (result == 0)
	{
		cout << "A kapcsolat megszakadt.\n";
		WSACleanup();
		return "";
	}

	return coordinates;
}

sockaddr_in createAddress()
{
	sockaddr_in Address;

	Address.sin_family = AF_INET;
	Address.sin_port = htons(13000);
	inet_pton(AF_INET, "127.0.0.1", &Address.sin_addr);

	return Address;

}

SOCKET bindPlayers(sockaddr_in Address)
{
	SOCKET playerSocket;

	playerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// Bind the socket.
	if (bind(playerSocket, (SOCKADDR*)&Address, sizeof(Address)) == SOCKET_ERROR)
	{
		printf("bind() failed.\n");
		cout << WSAGetLastError();

		closesocket(playerSocket);
		WSACleanup();
	}

	return playerSocket;

}

void sendToPlayer(sockaddr_in Address, string x, string y)
{

	int addressSize = sizeof(Address);
	int result;
	string fullString = x + "." + y;

	//creating a char array and copy the string into it,sendto only works with char array
	char* message = new char[fullString.length() + 1];
	strcpy_s(message, fullString.length() + 1, fullString.c_str());

	const int messageLen = strlen(message);

	SOCKET playerSocket;

	playerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//Send message to the address
	result = sendto(playerSocket, message, messageLen, 0, (SOCKADDR*)&Address, addressSize);
	if (result == SOCKET_ERROR)
	{
		cout << "Hiba a kuldesnel a kovetkezo hibakoddal:\n" << WSAGetLastError();
		closesocket(playerSocket);
		WSACleanup();
	}

	if (result == 0)
	{
		cout << "A kapcsolat megszakadt.\n";
		closesocket(playerSocket);
		WSACleanup();
	}

}

void sendSettingToPlayer(sockaddr_in Address, string setting)
{
	int addressSize = sizeof(Address);
	int result;

	//creating a char array and copy the string into it,sendto only works with char array
	char* message = new char[setting.length() + 1];
	strcpy_s(message, setting.length() + 1, setting.c_str());

	const int messageLen = strlen(message);

	SOCKET playerSocket;

	playerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//Send message to the address
	result = sendto(playerSocket, message, messageLen, 0, (SOCKADDR*)&Address, addressSize);
	if (result == SOCKET_ERROR)
	{
		cout << "Hiba a kuldesnel a kovetkezo hibakoddal:\n" << WSAGetLastError();
		closesocket(playerSocket);
		WSACleanup();
	}

	if (result == 0)
	{
		cout << "A kapcsolat megszakadt.\n";
		closesocket(playerSocket);
		WSACleanup();
	}

}

void sendMessage(string x, string y)
{
	sockaddr_in Address;

	InitializeWinsock();
	Address = createAddress();

	sendToPlayer(Address, x, y);

	WSACleanup();
}

void sendSetting(string x)
{
	sockaddr_in Address;

	InitializeWinsock();
	Address = createAddress();

	sendSettingToPlayer(Address, x);

	WSACleanup();
}

string recvMessage()
{
	InitializeWinsock();
	sockaddr_in Address;
	SOCKET player;
	string coordinates;

	Address = createAddress();
	player = bindPlayers(Address);

	coordinates = recvFromPlayer(player, Address);

	WSACleanup();

	return coordinates;
}

