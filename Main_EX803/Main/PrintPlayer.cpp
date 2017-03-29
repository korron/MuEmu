#include "stdafx.h"
#include "PrintPlayer.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"

DWORD ViewIndex = 0;
DWORD ViewReset = 0;
DWORD ViewValue = 0;
DWORD ViewPoint = 0;
DWORD ViewCurHP = 0;
DWORD ViewMaxHP = 0;
DWORD ViewCurMP = 0;
DWORD ViewMaxMP = 0;
DWORD ViewCurBP = 0;
DWORD ViewMaxBP = 0;
DWORD ViewCurSD = 0;
DWORD ViewMaxSD = 0;
DWORD ViewDamageHP = 0;
DWORD ViewDamageSD = 0;
DWORD ViewDamageTable[4] = {0,0,0,0};
DWORD ViewDamageCount = 0;
DWORD ViewDamageValue = 0;
DWORD ViewExperience = 0;
DWORD ViewNextExperience = 0;
QWORD ViewMasterExperience = 0;
QWORD ViewMasterNextExperience = 0;
DWORD ViewStrength = 0;
DWORD ViewDexterity = 0;
DWORD ViewVitality = 0;
DWORD ViewEnergy = 0;
DWORD ViewLeadership = 0;
DWORD ViewAddStrength = 0;
DWORD ViewAddDexterity = 0;
DWORD ViewAddVitality = 0;
DWORD ViewAddEnergy = 0;
DWORD ViewAddLeadership = 0;
DWORD ViewPhysiDamageMin = 0;
DWORD ViewPhysiDamageMax = 0;
DWORD ViewMagicDamageMin = 0;
DWORD ViewMagicDamageMax = 0;
DWORD ViewCurseDamageMin = 0;
DWORD ViewCurseDamageMax = 0;
DWORD ViewMulPhysiDamage = 0;
DWORD ViewDivPhysiDamage = 0;
DWORD ViewMulMagicDamage = 0;
DWORD ViewDivMagicDamage = 0;
DWORD ViewMulCurseDamage = 0;
DWORD ViewDivCurseDamage = 0;
DWORD ViewMagicDamageRate = 0;
DWORD ViewCurseDamageRate = 0;
DWORD ViewPhysiSpeed = 0;
DWORD ViewMagicSpeed = 0;
DWORD ViewAttackSuccessRate = 0;
DWORD ViewAttackSuccessRatePvP = 0;
DWORD ViewDefense = 0;
DWORD ViewDefenseSuccessRate = 0;
DWORD ViewDefenseSuccessRatePvP = 0;
DWORD ViewDamageMultiplier = 0;
DWORD ViewRFDamageMultiplierA = 0;
DWORD ViewRFDamageMultiplierB = 0;
DWORD ViewRFDamageMultiplierC = 0;
DWORD ViewDarkSpiritAttackDamageMin = 0;
DWORD ViewDarkSpiritAttackDamageMax = 0;
DWORD ViewDarkSpiritAttackSpeed = 0;
DWORD ViewDarkSpiritAttackSuccessRate = 0;
DWORD ViewSkillMagicDamage = 0;
DWORD ViewSkillPhysiDamage = 0;

void InitPrintPlayer() // OK
{
	SetDword(0x00508680,0xA0000001); // PrintTextReplace 64

	SetDword(0x00973AAA,0xA0000002); // PrintTextReplace 64

	SetDword(0x00508649,0xA0000001); // PrintTextReplace 203

	SetDword(0x009721D2,0xA0000002); // PrintTextReplace 203

	SetDword(0x00972210,0xA0000003); // PrintTextReplace 203

	MemorySet(0x0097391D,0xEB,1); // SetDefense

	MemorySet(0x0097253F,0xEB,1); // SetAttackSuccessRatePvP

	MemorySet(0x00973D80,0xEB,1); // SetDefenseSuccessRatePvP

	MemorySet(0x00973C20,0x90,2); // SetSpeed

	MemorySet(0x00972402,0xEB,1); // SetPhysiDamage

	MemorySet(0x009755FD,0xEB,1); // SetMagicDamage

	MemorySet(0x00976012,0xEB,1); // SetCurseDamage

	MemorySet(0x0096FEF6,0x90,2); // SetPointText

	MemorySet(0x009945BD,0x90,2); // SetHP

	MemorySet(0x009945CC,0x90,2); // SetHP

	MemorySet(0x00994614,0x90,2); // SetMP

	MemorySet(0x00994623,0x90,2); // SetMP

	MemorySet(0x00994874,0x90,2); // SetAG

	MemorySet(0x00994883,0x90,2); // SetAG

	MemorySet(0x00994744,0x90,2); // SetSD

	MemorySet(0x00994753,0x90,2); // SetSD

	MemorySet(0x009702E4,0x90,6); // SetStrText

	MemorySet(0x009703E2,0x90,6); // SetDexText

	MemorySet(0x009704E0,0x90,6); // SetVitText

	MemorySet(0x0097064E,0x90,6); // SetEngText

	MemorySet(0x0097076E,0x90,6); // SetChaText

	SetCompleteHook(0xE9,0x0096FF0A,&PrintPlayerViewPoint);

	SetCompleteHook(0xE9,0x009945E8,&PrintPlayerViewHP);

	SetCompleteHook(0xE9,0x0099463F,&PrintPlayerViewMP);

	SetCompleteHook(0xE9,0x0099489F,&PrintPlayerViewBP);

	SetCompleteHook(0xE9,0x0099476F,&PrintPlayerViewSD);

	SetCompleteHook(0xE9,0x0AD4A73D,&PrintPlayerViewLevelUpExperience1);

	SetCompleteHook(0xE9,0x09D63A17,&PrintPlayerViewLevelUpExperience2);

	SetCompleteHook(0xE9,0x0064B98F,&PrintPlayerViewLevelUpMasterExperience1);

	SetCompleteHook(0xE9,0x0064BA4A,&PrintPlayerViewLevelUpMasterExperience2);

	SetCompleteHook(0xE9,0x00436D38,&PrintPlayerViewText);

	SetCompleteHook(0xE9,0x0059B695,&PrintPlayerGetSkillMagicDamage);

	SetCompleteHook(0xE9,0x0059B90B,&PrintPlayerGetSkillPhysiDamage);

	SetCompleteHook(0xE9,0x00970358,&PrintPlayerViewStrength);

	SetCompleteHook(0xE9,0x00970456,&PrintPlayerViewDexterity);

	SetCompleteHook(0xE9,0x009705BE,&PrintPlayerViewVitality);

	SetCompleteHook(0xE9,0x009706C5,&PrintPlayerViewEnergy);

	SetCompleteHook(0xE9,0x009707E5,&PrintPlayerViewLeadership);

	SetCompleteHook(0xE9,0x0097C4F4,&PrintPlayerDarkHorseDamage);

	SetCompleteHook(0xE9,0x0097C546,&PrintPlayerDarkHorseSpeed);

	SetCompleteHook(0xE9,0x0097C746,&PrintPlayerDarkSpiritDamage);

	SetCompleteHook(0xE9,0x0097C7BF,&PrintPlayerDarkSpiritSpeed);

	SetCompleteHook(0xE8,0x0051DD27,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x0051DD7A,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x0051DDDC,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0051DE3E,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0051DEB5,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x0051DEF3,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0051DF1B,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x00547A0C,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063CF1D,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D13F,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D2B6,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D324,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x0063D79C,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D81F,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D88B,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D8D3,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D93A,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063D9B1,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DA28,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DABF,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DB0C,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DB39,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DBB3,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x0063DD80,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0063DDA9,&PrintDamageOnScreenED);

	SetCompleteHook(0xE8,0x0064397D,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643BCE,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643C3E,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643F67,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643FC4,&PrintDamageOnScreenHP);
}

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f,DWORD g) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x0078673A)(a,b,c,d,e,f,g);
}

void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f,DWORD g) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageSD;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x0078673A)(a,b,c,d,e,f,g);
}

void PrintDamageOnScreenRF(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f,DWORD g) // OK
{
	ViewDamageHP = ViewDamageTable[(ViewDamageValue-(ViewDamageCount--))];

	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x0078673A)(a,b,c,d,e,f,g);
}

void PrintDamageOnScreenED(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f,DWORD g) // OK
{
	if(((int)b) > 0)
	{
		b = b;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x0078673A)(a,b,c,d,e,f,g);
}

void PrintTextReplace(DWORD* value,DWORD type) // OK
{
	switch(value[0])
	{
		case 64: //"Velocidade de ataque: %d"
			switch(type)
			{
				case 1:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
				case 2:
					value[1] = ViewPhysiSpeed;
					break;
			}
			break;
		case 170: //"Dano mágico:%d~%d"
			GetViewMagicDamage(&value[1],&value[2]);
			break;
		case 203: //"Taxa de dano: %d~%d (%d)"
			switch(type)
			{
				case 1:
					GetViewDarkSpiritDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
					break;
				case 2:
					GetViewPhisyDamage(&value[1],&value[2]);
					value[3] = ViewAttackSuccessRate;
					break;
				case 3:
					GetViewPhisyDamage(&value[1],&value[2]);
					value[3] = ViewAttackSuccessRate;
					break;
			}
			break;
		case 204: //"Dano: %d~%d"
			GetViewPhisyDamage(&value[1],&value[2]);
			break;
		case 206: //"Taxa de defesa: %d (%d +%d)"
			value[0] = 208;
			value[1] = ViewDefense;
			value[2] = ViewDefenseSuccessRate;
			break;
		case 207: //"Defesa: %d (+%d)"
			value[0] = 209;
			value[1] = ViewDefense;
			break;
		case 208: //"Taxa de defesa: %d (%d)"
			value[1] = ViewDefense;
			value[2] = ViewDefenseSuccessRate;
			break;
		case 209: //"Defesa: %d"
			value[1] = ViewDefense;
			break;
		case 211: //"HP: %d / %d"
			value[1] = ViewCurHP;
			value[2] = ViewMaxHP;
			break;
		case 213: //"Mana: %d / %d"
			value[1] = ViewCurMP;
			value[2] = ViewMaxMP;
			break;
		case 214: //"AG: %d / %d"
			value[1] = ViewCurBP;
			value[2] = ViewMaxBP;
			break;
		case 215: //"Dano mágico: %d~%d (+%d)"
			GetViewMagicDamage(&value[1],&value[2],&value[3]);
			break;
		case 216: //"Dano mágico: %d~%d"
			GetViewMagicDamage(&value[1],&value[2]);
			break;
		case 217: //"Ponto(s): %d"
			value[1] = ViewPoint;
			break;
		case 358: //"Vida: %d/%d"
			value[1] = ViewCurHP;
			value[2] = ViewMaxHP;
			break;
		case 359: //"Mana: %d/%d"
			value[1] = ViewCurMP;
			value[2] = ViewMaxMP;
			break;
		case 379: //"(%s fruta(s)) %d pontos de atributo foram %s."
			value[2] = ViewValue;
			break;
		case 582: //"Dano da habilidade: %d%%"
			value[1] = ViewDamageMultiplier;
			break;
		case 879: //"Dano da habilidade: %d~%d"
			GetViewSkillDamage(&value[1],&value[2]);
			break;
		case 1692: //"Curse Spell: %d ~ %d"
			GetViewCurseDamage(&value[1],&value[2]);
			break;
		case 1693: //"Curse Spell: %d ~ %d(+%d)"
			GetViewCurseDamage(&value[1],&value[2],&value[3]);
			break;
		case 1694: //"Curse Spell: %d ~ %d"
			GetViewCurseDamage(&value[1],&value[2]);
			break;
		case 2037: //"SD : %d / %d"
			value[1] = ViewCurSD;
			value[2] = ViewMaxSD;
			break;
		case 2044: //"Taxa de ataque: %d"
			value[1] = ViewAttackSuccessRatePvP;
			break;
		case 2045: //"Taxa de defesa: %d"
			value[1] = ViewDefenseSuccessRatePvP;
			break;
		case 2109: //"Taxa de ataque: %d (+%d)"
			value[0] = 2044;
			value[1] = ViewAttackSuccessRatePvP;
			break;
		case 2110: //"Taxa de defesa:%d (+%d)"
			value[0] = 2045;
			value[1] = ViewDefenseSuccessRatePvP;
			break;
		case 3155: //"Melee Damage: %d%%"
			value[1] = ViewRFDamageMultiplierA;
			break;
		case 3156: //"Divine Damage (Roar, Slasher): %d%%"
			value[1] = ViewRFDamageMultiplierB;
			break;
		case 3157: //"AOE Damage (Dark Side): %d%%"
			value[1] = ViewRFDamageMultiplierC;
			break;
	}
}

void PrintFixStatPoint(DWORD type) // OK
{
	switch(type)
	{
		case 0:
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = GET_MAX_WORD_VALUE(ViewStrength);
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x32) = GET_MAX_WORD_VALUE(ViewAddStrength);
			break;
		case 1:
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = GET_MAX_WORD_VALUE(ViewDexterity);
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x34) = GET_MAX_WORD_VALUE(ViewAddDexterity);
			break;
		case 2:
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = GET_MAX_WORD_VALUE(ViewVitality);
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x36) = GET_MAX_WORD_VALUE(ViewAddVitality);
			break;
		case 3:
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = GET_MAX_WORD_VALUE(ViewEnergy);
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x38) = GET_MAX_WORD_VALUE(ViewAddEnergy);
			break;
		case 4:
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = GET_MAX_WORD_VALUE(ViewLeadership);
			*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x3E) = GET_MAX_WORD_VALUE(ViewAddLeadership);
			break;
	}
}

void GetViewPhisyDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}

void GetViewSkillDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ViewSkillPhysiDamage;

	(*DamageMax) += ViewSkillPhysiDamage+(ViewSkillPhysiDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}

void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewMagicDamageMin;

	(*DamageMax) = ViewMagicDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulMagicDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulMagicDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivMagicDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivMagicDamage)/100;
}

void GetViewMagicDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate) // OK
{
	(*DamageMin) = ViewMagicDamageMin;

	(*DamageMax) = ViewMagicDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulMagicDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulMagicDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivMagicDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivMagicDamage)/100;

	(*DamageRate) = ((*DamageMax)*ViewMagicDamageRate)/100;
}

void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewCurseDamageMin;

	(*DamageMax) = ViewCurseDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulCurseDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulCurseDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivCurseDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivCurseDamage)/100;
}

void GetViewCurseDamage(DWORD* DamageMin,DWORD* DamageMax,DWORD* DamageRate) // OK
{
	(*DamageMin) = ViewCurseDamageMin;

	(*DamageMax) = ViewCurseDamageMax;

	(*DamageMin) += ViewSkillMagicDamage;

	(*DamageMax) += ViewSkillMagicDamage+(ViewSkillMagicDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulCurseDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulCurseDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivCurseDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivCurseDamage)/100;

	(*DamageRate) = ((*DamageMax)*ViewCurseDamageRate)/100;
}

void GetViewDarkSpiritDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewDarkSpiritAttackDamageMin;

	(*DamageMax) = ViewDarkSpiritAttackDamageMax;
}

void GetViewDarkHorseDamage(DWORD* DamageMin,DWORD* DamageMax) // OK
{
	(*DamageMin) = ViewPhysiDamageMin;

	(*DamageMax) = ViewPhysiDamageMax;

	(*DamageMin) += ViewSkillPhysiDamage;

	(*DamageMax) += ViewSkillPhysiDamage+(ViewSkillPhysiDamage/2);

	(*DamageMin) += ((*DamageMin)*ViewMulPhysiDamage)/100;

	(*DamageMax) += ((*DamageMax)*ViewMulPhysiDamage)/100;

	(*DamageMin) -= ((*DamageMin)*ViewDivPhysiDamage)/100;

	(*DamageMax) -= ((*DamageMax)*ViewDivPhysiDamage)/100;
}

__declspec(naked) void PrintPlayerViewPoint() // OK
{
	static DWORD PrintPlayerViewPointAddress1 = 0x0096FF13;

	_asm
	{
		Mov Eax,ViewPoint
		Push Eax
		Jmp [PrintPlayerViewPointAddress1]
	}
}

__declspec(naked) void PrintPlayerViewHP() // OK
{
	static DWORD PrintPlayerViewHPAddress1 = 0x009945F2;

	_asm
	{
		Mov Eax,ViewMaxHP
		Push Eax
		Mov Ecx,ViewCurHP
		Push Ecx
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP() // OK
{
	static DWORD PrintPlayerViewMPAddress1 = 0x00994649;

	_asm
	{
		Mov Eax,ViewMaxMP
		Push Eax
		Mov Ecx,ViewCurMP
		Push Ecx
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP() // OK
{
	static DWORD PrintPlayerViewBPAddress1 = 0x009948A9;

	_asm
	{
		Mov Eax,ViewMaxBP
		Push Eax
		Mov Ecx,ViewCurBP
		Push Ecx
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD() // OK
{
	static DWORD PrintPlayerViewSDAddress1 = 0x00994779;

	_asm
	{
		Mov Eax,ViewMaxSD
		Push Eax
		Mov Ecx,ViewCurSD
		Push Ecx
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience1() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0AD4A74E;

	_asm
	{
		Mov Eax,ViewExperience
		Mov Ecx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Sub Eax,Dword Ptr Ds:[Ecx+0x10]
		Jmp [PrintPlayerViewLevelUpExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0A985E58;

	_asm
	{
		Mov Eax,ViewExperience
		Mov Ecx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Mov Dword Ptr Ds:[Ecx+0x10],Eax
		Mov Edx,ViewNextExperience
		Mov Eax,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Mov Dword Ptr Ds:[Eax+0x14],Edx
		Jmp [PrintPlayerViewLevelUpExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpMasterExperience1() // OK
{
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x0064B9A6;

	_asm
	{
		Lea Edx,ViewMasterExperience
		Mov Eax,Dword Ptr Ds:[Edx+0x00]
		Sub Eax,Dword Ptr Ds:[0x08B158C0]
		Mov Ecx,Dword Ptr Ds:[Edx+0x04]
		Sbb Ecx,Dword Ptr Ds:[0x08B158C4]
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpMasterExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x0064BA55;

	_asm
	{
		Lea Eax,ViewMasterExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x08B158C0],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x08B158C4],Edx
		Lea Eax,ViewMasterNextExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x08B158C8],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x08B158CC],Edx
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewText() // OK
{
	static DWORD PrintPlayerViewTextAddress1 = 0x00436D3E;

	_asm
	{
		Cmp Ecx,0xA0000000
		Jle NEXT1
		Mov Dword Ptr Ss:[Ebp-0x04],0x08499DE0
		Sub Ecx,0xA0000000
		Jmp NEXT2
		NEXT1:
		Xor Ecx,Ecx
		NEXT2:
		Push Ecx
		Mov Edx,Ebp
		Add Edx,0x08
		Push Edx
		Call [PrintTextReplace]
		Add Esp,0x04
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Jmp [PrintPlayerViewTextAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillMagicDamage() // OK
{
	static DWORD PrintPlayerGetSkillMagicDamageAddress1 = 0x0059B69C;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillMagicDamage,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp-0x18]
		Movzx Eax,Word Ptr Ds:[Edx+0x62]
		Jmp [PrintPlayerGetSkillMagicDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillPhysiDamage() // OK
{
	static DWORD PrintPlayerGetSkillPhysiDamageAddress1 = 0x0059B911;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillPhysiDamage,Edx
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Jmp [PrintPlayerGetSkillPhysiDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerViewStrength() // OK
{
	static DWORD PrintPlayerViewStrengthAddress1 = 0x00970366;

	_asm
	{
		Push 0
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Eax,ViewStrength
		Add Eax,ViewAddStrength
		Push Eax
		Jmp [PrintPlayerViewStrengthAddress1]
	}
}

__declspec(naked) void PrintPlayerViewDexterity() // OK
{
	static DWORD PrintPlayerViewDexterityAddress1 = 0x00970464;

	_asm
	{
		Push 1
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Eax,ViewDexterity
		Add Eax,ViewAddDexterity
		Push Eax
		Jmp [PrintPlayerViewDexterityAddress1]
	}
}

__declspec(naked) void PrintPlayerViewVitality() // OK
{
	static DWORD PrintPlayerViewVitalityAddress1 = 0x009705CC;

	_asm
	{
		Push 2
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Eax,ViewVitality
		Add Eax,ViewAddVitality
		Push Eax
		Jmp [PrintPlayerViewVitalityAddress1]
	}
}

__declspec(naked) void PrintPlayerViewEnergy() // OK
{
	static DWORD PrintPlayerViewEnergyAddress1 = 0x009706D3;

	_asm
	{
		Push 3
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Eax,ViewEnergy
		Add Eax,ViewAddEnergy
		Push Eax
		Jmp [PrintPlayerViewEnergyAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLeadership() // OK
{
	static DWORD PrintPlayerViewLeadershipAddress1 = 0x009707F3;

	_asm
	{
		Push 4
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Eax,ViewLeadership
		Add Eax,ViewAddLeadership
		Push Eax
		Jmp [PrintPlayerViewLeadershipAddress1]
	}
}

__declspec(naked) void PrintPlayerDarkHorseDamage() // OK
{
	static DWORD DarkHorseDamageMin,DarkHorseDamageMax;

	static DWORD PrintPlayerDarkHorseDamageAddress1 = 0x0097C514;

	_asm
	{
		Lea Eax,DarkHorseDamageMax
		Push Eax
		Lea Ecx,DarkHorseDamageMin
		Push Ecx
		Call [GetViewDarkHorseDamage]
		Add Esp,0x08
		Mov Edx,ViewDarkSpiritAttackSuccessRate
		Push Edx
		Mov Eax,DarkHorseDamageMax
		Push Eax
		Mov Ecx,DarkHorseDamageMin
		Push Ecx
		Jmp [PrintPlayerDarkHorseDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerDarkHorseSpeed() // OK
{
	static DWORD PrintPlayerDarkHorseSpeedAddress1 = 0x0097C54E;

	_asm
	{
		Mov Eax,ViewDarkSpiritAttackSpeed
		Push Eax
		Jmp [PrintPlayerDarkHorseSpeedAddress1]
	}
}

__declspec(naked) void PrintPlayerDarkSpiritDamage() // OK
{
	static DWORD DarkSpiritDamageMin,DarkSpiritDamageMax;

	static DWORD PrintPlayerDarkSpiritDamageAddress1 = 0x0097C766;

	_asm
	{
		Lea Eax,DarkSpiritDamageMax
		Push Eax
		Lea Ecx,DarkSpiritDamageMin
		Push Ecx
		Call [GetViewDarkSpiritDamage]
		Add Esp,0x08
		Mov Edx,ViewDarkSpiritAttackSuccessRate
		Push Edx
		Mov Eax,DarkSpiritDamageMax
		Push Eax
		Mov Ecx,DarkSpiritDamageMin
		Push Ecx
		Jmp [PrintPlayerDarkSpiritDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerDarkSpiritSpeed() // OK
{
	static DWORD PrintPlayerDarkSpiritSpeedAddress1 = 0x0097C7D0;

	_asm
	{
		Mov Eax,ViewDarkSpiritAttackSpeed
		Push Eax
		Jmp [PrintPlayerDarkSpiritSpeedAddress1]
	}
}
