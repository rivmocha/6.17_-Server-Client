#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    //Windows Only
    //Wisock 라이브러리 초기화
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "WSAStartup Failed." << endl;
        exit(-1);
    }


    SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (ServerSocket == INVALID_SOCKET)
    {
        cout << "Create socket failed." << endl;
        exit(-1);
    }

    SOCKADDR_IN ServerSockADDR;

    memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));
    ServerSockADDR.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerSockADDR.sin_port = htons(20000);
    ServerSockADDR.sin_family = PF_INET;


    if (bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {

        cout << "bind failed." << GetLastError() << endl;
        exit(-1);
    }

    if (listen(ServerSocket, 0) == SOCKET_ERROR)
    {
        cout << "listen failed." << endl;
        exit(-1);
    }

    SOCKADDR_IN ClientADDR;
    int ClientAddrLen = sizeof(ClientADDR);
    SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientADDR, &ClientAddrLen);
    if (ClientSocket == SOCKET_ERROR)
    {
        cout << "accept failed." << endl;
        exit(-1);
    }

    char Message[] = "끊어!";
    int SendLength = send(ClientSocket, Message, strlen(Message), 0);

    closesocket(ClientSocket);
    closesocket(ServerSocket);

    //Windows Only
    WSACleanup();

    return 0;
}
