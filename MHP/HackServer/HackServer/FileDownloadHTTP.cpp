/*
    Http functions. Dont forget to initialize winsock.

    Luke Graham (39ster@gmail.com)
*/

#include "stdafx.h"
#include <stdio.h>
#include "FileDownloadHTTP.h"

int _httpErrorCode = 0;
int recvLine(int pSockId, char* pOut, int pOutSize);

int httpLastError()
{
    return _httpErrorCode;
}

int httpGet(char* pAddress, int pPort, char* pRequest)
{
    char buffer[0xFFFF];
    //Create the socket and connect to server.
    int sockId;
    sockaddr_in addr;
    hostent*  hostEntry;
    if ((sockId = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
        return 0;

    if ((hostEntry = gethostbyname(pAddress)) == NULL)
        return 0;

    addr.sin_family = AF_INET;
    addr.sin_addr = *((in_addr*)*hostEntry->h_addr_list);
    addr.sin_port = htons((unsigned short)pPort);
    if (connect(sockId, (sockaddr*)&addr, sizeof(sockaddr_in)) == -1)
        return 0;

    //Make and send get request
    sprintf_s(buffer, "GET %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "\r\n", pRequest, pAddress);
    send(sockId, buffer, strlen(buffer), 0);

    int length = 0;
    bool success = false;
    //Use a loop to receive all of the header.
    while((length = recvLine(sockId, buffer, sizeof(buffer))) > 0)
    {
        //trim line
        for(int i = length-1; i >= 0; i--)
        {
            if(buffer[i] < ' ')
                buffer[i] = 0;
            else break;
        }

        //if end of header
        if(!strlen(buffer))
            break;
		char* context	= NULL;
        //get first word
        char* token = strtok_s(buffer, " ", &context);
        if(token == NULL)
            break;

        //Check http error code
        if(strcmp(token, "HTTP/1.0") == 0 || strcmp(token, "HTTP/1.1") == 0)
        {
            _httpErrorCode = atoi(strtok_s(NULL, " ", &context));
            if(_httpErrorCode == 200)
                success = true;
        }

    }

    if(!success)
    {
        closesocket(sockId);
        return 0;
    } else return sockId;
}

int httpRecv(int pSockId, char* pOut, int pOutSize)
{
    int size;
    if((size = recv(pSockId, pOut, pOutSize, 0)) > 0)
        return size;
    return 0;
}

void httpClose(int pSockId)
{
    closesocket(pSockId);
}

int recvLine(int pSockId, char* pOut, int pOutSize)
{
    int received = 0;
    char letter;
    memset(pOut, 0, pOutSize);
    for(; received < pOutSize-1; received++)
    {
        if(recv(pSockId, (char*)&letter, 1, 0) > 0)
        {
            pOut[received] = letter;
            if(letter == '\n')
                break;
        } else break;
    }
    return received;
}
