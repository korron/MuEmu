#ifndef _Config_H
#define _Config_H

class cConfig
{
public:
	void Load();
	char msg[100];
	char msg2[100];
	char msg3[100];
	char msg4[100];
	char msg5[100];
	char msg6[100];
	char msg7[100];
	char msg8[100];
	char RankText[32];
	char RankText1[32];
	char RankText2[32];
	char RankText3[32];
	char RankText4[32];
	char RankText5[32];
	char RankText6[32];
	char RankText7[32];
	char RankText8[32];
	char RankText9[32];
	char RankText10[32];
	char RankText11[32];
	char RankText12[32];
	char RankText13[32];
	char RankText14[32];
	char RankText15[32];
	char RankText16[32];
	char RankText17[32];
	char RankText18[32];
	int Min;
	int Max;
	int Min1;
	int Max1;
	int Min2;
	int Max2;
	int Min3;
	int Max3;
	int Min4;
	int Max4;
	int Min5;
	int Max5;
	int Min6;
	int Max6;
	int Min7;
	int Max7;
	int Min8;
	int Max8;
	int Min9;
	int Max9;
	int Min10;
	int Max10;
	int Min11;
	int Max11;
	int Min12;
	int Max12;
	int Min13;
	int Max13;
	int Min14;
	int Max14;
	int Min15;
	int Max15;
	int Min16;
	int Max16;
	int Min17;
	int Max17;
	int Min18;
	int Max18;
};

// Arquivo de configuracao
// "./" Indica que o arquivo e na mesa pasta do main.exe
#define CONFIG_FILE "./Data/Custom/RankText.cfg"
#define MAIN_FILE "./Data/Custom/Gameload.cfg"
extern cConfig Config;

#endif