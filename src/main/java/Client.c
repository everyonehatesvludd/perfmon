#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#define DEFAULT_PORT "5000"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char const *argv[])
{
    WSADATA wsaData;

    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;

    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("Error at connect(): %ld\n", WSAGetLastError());
        closesocket(ConnectSocket);
        freeaddrinfo(result);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }

    const char *sendbuf = "Hello Server!";
    iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // char recvbuf[512];
    // iResult = recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0);
    // if (iResult > 0)
    // {
    //     printf("Bytes received: %d\n", iResult);
    //     recvbuf[iResult] = '\0';
    //     printf("Received: %s\n", recvbuf);
    // }
    // else if (iResult == 0)
    // {
    //     printf("Connection closed\n");
    // }
    // else
    // {
    //     printf("recv failed: %d\n", WSAGetLastError());
    // }

    closesocket(ConnectSocket);
    freeaddrinfo(result);
    WSACleanup();

    return 0;
}
