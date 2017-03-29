/*
    URL functions.

    Luke Graham (39ster@gmail.com)
*/

#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include "FileDownloadURL.h"

//Breaks apart a url into a port, address and request
void breakUrl(const char* pUrl, URLPARTS_T* pUrlStruct)
{
    char url[2048];
    char *ptr1 = url;
    strncpy_s(url, pUrl, sizeof(url));
    pUrlStruct->port = 80;

    //find protocol (like http:// or ftp://)
    char* ptr2 = strstr(ptr1, "://");
    if(ptr2 != 0)
    {
        *ptr2 = 0;
        if(pUrlStruct->protocolLen > 0)
            strncpy_s(pUrlStruct->protocol, pUrlStruct->protocolLen, ptr1, pUrlStruct->protocolLen);

        if(strcmp(ptr1, "ftp") == 0)
            pUrlStruct->port = 21;

        ptr1 = ptr2 + 3;
    } else if(pUrlStruct->protocolLen > 0)
        *pUrlStruct->protocol = 0;

    //find request (the part starting at "/" after the address and port)
    ptr2 = strchr(ptr1, '/');
    if(ptr2 != 0)
    {
        if(pUrlStruct->requestLen > 0)
            strncpy_s(pUrlStruct->request, pUrlStruct->requestLen, ptr2, pUrlStruct->requestLen);

        *ptr2 = 0;
    } else if(pUrlStruct->requestLen > 1)
        strncpy_s(pUrlStruct->request, pUrlStruct->requestLen, "/", pUrlStruct->requestLen);

    //find port (the part after ":")
    ptr2 = strchr(ptr1, ':');
    if(ptr2 != 0)
    {
        pUrlStruct->port = atoi(ptr2+1);
        *ptr2 = 0;
    }

    //whats left should only be the address
    if(pUrlStruct->addressLen > 0)
        strncpy_s(pUrlStruct->address, pUrlStruct->addressLen, ptr1, pUrlStruct->addressLen);
}

int hexToAscii(char pHex);
//Decodes the hex parts of the request (e.g %20 is ' ')
void decodeRequest(const char* pRequest, char* pOut, int pOutSize)
{
    char* ptr1 = (char*)pRequest;
    memset(pOut, 0, pOutSize);
    for(int i = 0; i < pOutSize-1; i++)
    {
        if(*ptr1 == 0)
            break;

        switch(*ptr1)
        {
            case '%':
                pOut[i] = hexToAscii(*++ptr1) << 4;
                pOut[i] += hexToAscii(*++ptr1);
            break;

            default:
                pOut[i] = *ptr1;
            break;
        }
        ptr1++;
    }
}

int hexToAscii(char pHex)
{
    if(pHex >= '0' && pHex <= '9')
        return pHex - '0';
    if(pHex >= 'A' && pHex <= 'F')
        return pHex - 'A' + 10;
    if(pHex >= 'a' && pHex <= 'f')
        return pHex - 'a' + 10;
    return 0;
}
