//------------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//------------------------------------------------------------------------------
#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
    #include <Windows.h>

	#ifdef OpenRP1210DrvExport
		#define DLLEXPORT __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif

    #define Tick timeGetTime
#elif __linux__
    #include <time.h>
    #include <stdint.h>
    #include <math.h>

    #define HWND unsigned long
    #define DWORD unsigned long
    #define DLLEXPORT
    #define WINAPI

    int64_t Tick(void)
    {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        return t.tv_sec * 1000 + lround(t.tv_nsec / 1E6);
    }
#endif

#include <string.h>
#include "RP1210.h"

short WINAPI RP1210_ClientConnect(HWND hwndClient,
                                  short nDeviceId,
                                  const char *fpchProtocol,
                                  long lTxBufferSize,
                                  long lRcvBufferSize,
                                  short nIsAppPacketizingIncomingMsgs)
{
    return 1;
}

short WINAPI RP1210_ClientDisconnect(short nClientID)
{
	return NO_ERRORS;
}

short WINAPI RP1210_SendMessage(short nClientID,
                                char *fpchClientMessage,
                                short nMessageSize,
                                short nNotifyStatusOnTx,
                                short nBlockOnSend)
{
	return NO_ERRORS;
}

short WINAPI RP1210_ReadMessage(short nClientID,
                                char *fpchAPIMessage,
                                short nBufferSize,
                                short nBlockOnRead)
{
    short r = NO_ERRORS;
    static DWORD lastTick = 0;
    static unsigned char v = 0;

    if(lastTick == 0)
        lastTick = Tick();

    DWORD currentTick = Tick();
    if(currentTick - lastTick > 100)
    {
        v++;
        if(v > 255)
            v = 0;

        lastTick = Tick();
    }

    char data[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0xFE, 0xEE, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x00 };
    data[16] = v;

    if(nBufferSize >= 17)
    {
        if(fpchAPIMessage)
            memcpy(fpchAPIMessage, data, 17);

        r = 17;
    }
    else
        r = ERR_MESSAGE_TOO_LONG;

    return r;
}

short WINAPI RP1210_SendCommand(short nCommandNumber,
                                short nClientID,
                                char *fpchClientCommand,
                                short nMessageSize)
{
	return NO_ERRORS;
}

void WINAPI RP1210_ReadVersion(char *fpchDLLMajorVersion,
                               char *fpchDLLMinorVersion,
                               char *fpchAPIMajorVersion,
                               char *fpchAPIMinorVersion)
{
    strcpy(fpchDLLMajorVersion, "1");
    strcpy(fpchDLLMinorVersion, "0");
    strcpy(fpchAPIMajorVersion, "3");
    strcpy(fpchAPIMinorVersion, "0");
}

short WINAPI RP1210_ReadDetailedVersion(short nClientID,
                                        char *fpchAPIVersionInfo,
                                        char *fpchDLLVersionInfo,
                                        char *fpchFWVersionInfo)
{
	return NO_ERRORS;
}

short WINAPI RP1210_GetHardwareStatus(short nClientID,
                                      char *fpchClientInfo,
                                      short nInfoSize,
                                      short nBlockOnRequest)
{
	return NO_ERRORS;
}

short WINAPI RP1210_GetErrorMsg(short err_code, char *fpchMessage)
{
	return NO_ERRORS;
}

short WINAPI RP1210_GetLastErrorMsg(short err_code,
                                    int *SubErrorCode,
                                    char *fpchMessage)
{
	return NO_ERRORS;
}