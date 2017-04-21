#include "StdAfx.h"
#include "Config.h"

cConfig Config;

void cConfig::Load()
{
	GetPrivateProfileStringA("Text", "msg", "Null", msg, sizeof(msg), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg2", "Null", msg2, sizeof(msg2), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg3", "Null", msg3, sizeof(msg3), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg4", "Null", msg4, sizeof(msg4), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg5", "Null", msg5, sizeof(msg5), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg6", "Null", msg6, sizeof(msg6), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg7", "Null", msg7, sizeof(msg7), MAIN_FILE);
	GetPrivateProfileStringA("Text", "msg8", "Null", msg8, sizeof(msg8), MAIN_FILE);
	// RankTitle
	GetPrivateProfileStringA("Rank", "Title", "Null", RankText, sizeof(RankText), CONFIG_FILE);
	GetPrivateProfileStringA("Rank1", "Title", "Null", RankText1, sizeof(RankText1), CONFIG_FILE);
	GetPrivateProfileStringA("Rank2", "Title", "Null", RankText2, sizeof(RankText2), CONFIG_FILE);
	GetPrivateProfileStringA("Rank3", "Title", "Null", RankText3, sizeof(RankText3), CONFIG_FILE);
	GetPrivateProfileStringA("Rank4", "Title", "Null", RankText4, sizeof(RankText4), CONFIG_FILE);
	GetPrivateProfileStringA("Rank5", "Title", "Null", RankText5, sizeof(RankText5), CONFIG_FILE);
	GetPrivateProfileStringA("Rank6", "Title", "Null", RankText6, sizeof(RankText6), CONFIG_FILE);
	GetPrivateProfileStringA("Rank7", "Title", "Null", RankText7, sizeof(RankText7), CONFIG_FILE);
	GetPrivateProfileStringA("Rank8", "Title", "Null", RankText8, sizeof(RankText8), CONFIG_FILE);
	GetPrivateProfileStringA("Rank9", "Title", "Null", RankText9, sizeof(RankText9), CONFIG_FILE);
	GetPrivateProfileStringA("Rank10", "Title", "Null", RankText10, sizeof(RankText10), CONFIG_FILE);
	GetPrivateProfileStringA("Rank11", "Title", "Null", RankText11, sizeof(RankText11), CONFIG_FILE);
	GetPrivateProfileStringA("Rank12", "Title", "Null", RankText12, sizeof(RankText12), CONFIG_FILE);
	GetPrivateProfileStringA("Rank13", "Title", "Null", RankText13, sizeof(RankText13), CONFIG_FILE);
	GetPrivateProfileStringA("Rank14", "Title", "Null", RankText14, sizeof(RankText14), CONFIG_FILE);
	GetPrivateProfileStringA("Rank15", "Title", "Null", RankText15, sizeof(RankText15), CONFIG_FILE);
	GetPrivateProfileStringA("Rank16", "Title", "Null", RankText16, sizeof(RankText16), CONFIG_FILE);
	GetPrivateProfileStringA("Rank17", "Title", "Null", RankText17, sizeof(RankText17), CONFIG_FILE);
	GetPrivateProfileStringA("Rank18", "Title", "Null", RankText18, sizeof(RankText18), CONFIG_FILE);

	Min = GetPrivateProfileIntA("Rank", "Min", 0, CONFIG_FILE);
	Max = GetPrivateProfileIntA("Rank", "Max", 49, CONFIG_FILE);
	Min1 = GetPrivateProfileIntA("Rank1", "Min", 50, CONFIG_FILE);
	Max1 = GetPrivateProfileIntA("Rank1", "Max", 100, CONFIG_FILE);
	Min2 = GetPrivateProfileIntA("Rank2", "Min", 101, CONFIG_FILE);
	Max2 = GetPrivateProfileIntA("Rank2", "Max", 160, CONFIG_FILE);
	Min3 = GetPrivateProfileIntA("Rank3", "Min", 161, CONFIG_FILE);
	Max3 = GetPrivateProfileIntA("Rank3", "Max", 230, CONFIG_FILE);
	Min4 = GetPrivateProfileIntA("Rank4", "Min", 231, CONFIG_FILE);
	Max4 = GetPrivateProfileIntA("Rank4", "Max", 310, CONFIG_FILE);
	Min5 = GetPrivateProfileIntA("Rank5", "Min", 311, CONFIG_FILE);
	Max5 = GetPrivateProfileIntA("Rank5", "Max", 400, CONFIG_FILE);
	Min6 = GetPrivateProfileIntA("Rank6", "Min", 401, CONFIG_FILE);
	Max6 = GetPrivateProfileIntA("Rank6", "Max", 500, CONFIG_FILE);
	Min7 = GetPrivateProfileIntA("Rank7", "Min", 501, CONFIG_FILE);
	Max7 = GetPrivateProfileIntA("Rank7", "Max", 610, CONFIG_FILE);
	Min8 = GetPrivateProfileIntA("Rank8", "Min", 611, CONFIG_FILE);
	Max8 = GetPrivateProfileIntA("Rank8", "Max", 730, CONFIG_FILE);
	Min9 = GetPrivateProfileIntA("Rank9", "Min", 731, CONFIG_FILE);
	Max9 = GetPrivateProfileIntA("Rank9", "Max", 860, CONFIG_FILE);
	Min10 = GetPrivateProfileIntA("Rank10", "Min", 861, CONFIG_FILE);
	Max10 = GetPrivateProfileIntA("Rank10", "Max", 1000, CONFIG_FILE);
	Min11 = GetPrivateProfileIntA("Rank11", "Min", 0, CONFIG_FILE);
	Max11 = GetPrivateProfileIntA("Rank11", "Max", 49, CONFIG_FILE);
	Min12 = GetPrivateProfileIntA("Rank12", "Min", 50, CONFIG_FILE);
	Max12 = GetPrivateProfileIntA("Rank12", "Max", 100, CONFIG_FILE);
	Min13 = GetPrivateProfileIntA("Rank13", "Min", 101, CONFIG_FILE);
	Max13 = GetPrivateProfileIntA("Rank13", "Max", 160, CONFIG_FILE);
	Min14 = GetPrivateProfileIntA("Rank14", "Min", 231, CONFIG_FILE);
	Max14 = GetPrivateProfileIntA("Rank14", "Max", 310, CONFIG_FILE);
	Min15 = GetPrivateProfileIntA("Rank15", "Min", 311, CONFIG_FILE);
	Max15 = GetPrivateProfileIntA("Rank15", "Max", 400, CONFIG_FILE);
	Min16 = GetPrivateProfileIntA("Rank16", "Min", 401, CONFIG_FILE);
	Max16 = GetPrivateProfileIntA("Rank16", "Max", 500, CONFIG_FILE);
	Min17 = GetPrivateProfileIntA("Rank17", "Min", 501, CONFIG_FILE);
	Max17 = GetPrivateProfileIntA("Rank17", "Max", 610, CONFIG_FILE);
	Min18 = GetPrivateProfileIntA("Rank18", "Min", 611, CONFIG_FILE);
	Max18 = GetPrivateProfileIntA("Rank18", "Max", 730, CONFIG_FILE);
}