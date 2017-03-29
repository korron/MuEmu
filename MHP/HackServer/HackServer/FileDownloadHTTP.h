#pragma once

int httpGet(char* pAddress, int pPort, char* pRequest);
int httpRecv(int pSockId, char* pOut, int pOutSize);
int httpLastError();
void httpClose(int pSockId);
