#include "stdafx.h"
#include "PrintPlayer.h"
#include "CustomMessage.h"
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
	SetDword(0x004FA27B,0xA0000001); // PrintTextReplace 64

	SetDword(0x007828CF,0xA0000002); // PrintTextReplace 64

	SetDword(0x0084D782,0xA0000003); // PrintTextReplace 64

	SetDword(0x0084DBD6,0xA0000004); // PrintTextReplace 64

	SetDword(0x004FA240,0xA0000001); // PrintTextReplace 203

	SetDword(0x0078154E,0xA0000002); // PrintTextReplace 203

	SetDword(0x0078158D,0xA0000003); // PrintTextReplace 203

	SetDword(0x0084D705,0xA0000004); // PrintTextReplace 203

	SetDword(0x0084DB89,0xA0000005); // PrintTextReplace 203

	SetDword(0x0080FF79,0xA0000001); // PrintTextReplace 358

	SetDword(0x0084D563,0xA0000002); // PrintTextReplace 358

	SetDword(0x0084D9F3,0xA0000003); // PrintTextReplace 358

	SetCompleteHook(0xE9,0x0077FB09,&PrintPlayerLevel1);

	SetCompleteHook(0xE9,0x0077FB3E,&PrintPlayerLevel2);

	SetCompleteHook(0xE9,0x0080FCF0,&PrintPlayerViewHP1);

	SetCompleteHook(0xE9,0x0080FEFD,&PrintPlayerViewHP2);

	SetCompleteHook(0xE9,0x0080FD27,&PrintPlayerViewMP1);

	SetCompleteHook(0xE9,0x00810090,&PrintPlayerViewMP2);

	SetCompleteHook(0xE9,0x0081025B,&PrintPlayerViewBP1);

	SetCompleteHook(0xE9,0x00810361,&PrintPlayerViewBP2);

	SetCompleteHook(0xE9,0x0081052B,&PrintPlayerViewSD1);

	SetCompleteHook(0xE9,0x00810631,&PrintPlayerViewSD2);

	SetCompleteHook(0xE9,0x0064C934,&PrintPlayerViewLevelUpExperience1);

	SetCompleteHook(0xE9,0x0064C9E4,&PrintPlayerViewLevelUpExperience2);

	SetCompleteHook(0xE9,0x0065158A,&PrintPlayerViewLevelUpMasterExperience1);

	SetCompleteHook(0xE9,0x0065164D,&PrintPlayerViewLevelUpMasterExperience2);

	SetCompleteHook(0xE9,0x00402327,&PrintPlayerViewText);

	SetCompleteHook(0xE9,0x00593B53,&PrintPlayerSetAttackSpeed);

	SetCompleteHook(0xE9,0x00595EA1,&PrintPlayerGetSkillMagicDamage);

	SetCompleteHook(0xE9,0x00596142,&PrintPlayerGetSkillPhysiDamage);

	SetCompleteHook(0xE9,0x007801AD,&PrintPlayerViewStrength);

	SetCompleteHook(0xE9,0x007818F2,&PrintPlayerViewDexterity);

	SetCompleteHook(0xE9,0x00782CE9,&PrintPlayerViewVitality);

	SetCompleteHook(0xE9,0x007830C3,&PrintPlayerViewEnergy);

	SetCompleteHook(0xE9,0x00784B4F,&PrintPlayerViewLeadership);
	
	SetCompleteHook(0xE8,0x00510FEB,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x0051100D,&PrintDamageOnScreenRF);

	SetCompleteHook(0xE8,0x0051107B,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x005428A4,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006439A1,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643BAD,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643D29,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00643D91,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x006441B6,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064422F,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00644291,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006442CF,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064435A,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006443CB,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006443F1,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00644465,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x0064A4AB,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064A71D,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064A779,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064AAC0,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0064AB1C,&PrintDamageOnScreenHP);
}

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x00770CA0)(a,b,c,d,e,f);
}

void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageSD;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x00770CA0)(a,b,c,d,e,f);
}

void PrintDamageOnScreenRF(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e,DWORD f) // OK
{
	ViewDamageHP = ViewDamageTable[(ViewDamageValue-(ViewDamageCount--))];

	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD))0x00770CA0)(a,b,c,d,e,f);
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
				case 3:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
				case 4:
					value[1] = ViewDarkSpiritAttackSpeed;
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
				case 4:
					GetViewDarkHorseDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
					break;
				case 5:
					GetViewDarkSpiritDamage(&value[1],&value[2]);
					value[3] = ViewDarkSpiritAttackSuccessRate;
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
			switch(type)
			{
				case 1:
					value[1] = ViewCurHP;
					value[2] = ViewMaxHP;
					break;
				case 2:
					value[1] = value[1];
					value[2] = value[2];
					break;
				case 3:
					value[1] = value[1];
					value[2] = value[2];
					break;
			}
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

__declspec(naked) void PrintPlayerLevel1() // OK
{
	static DWORD PrintPlayerLevelAddress1 = 0x0050D100;
	static DWORD PrintPlayerLevelAddress2 = 0x0077FB28;

	_asm
	{
		Mov Eax,ViewReset
		Push Eax
		Mov Ecx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Xor Edx,Edx
		Mov Dx,Word Ptr Ds:[Ecx+0x0E]
		Push Edx
		Push 0
		Lea Ecx,gCustomMessage
		Call [CCustomMessage::GetMessage]
		Push Eax
		Lea Ecx,Dword Ptr Ss:[Ebp-0x128]
		Push Ecx
		Call [PrintPlayerLevelAddress1]
		Add Esp,0x10
		Jmp [PrintPlayerLevelAddress2]
	}
}

__declspec(naked) void PrintPlayerLevel2() // OK
{
	static DWORD PrintPlayerLevelAddress1 = 0x0050D100;
	static DWORD PrintPlayerLevelAddress2 = 0x0077FB68;

	_asm
	{
		Mov Eax,ViewReset
		Push Eax
		Mov Ecx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Xor Edx,Edx
		Mov Dx,Word Ptr Ds:[Ecx+0x0E]
		Push Edx
		Push 0
		Lea Ecx,gCustomMessage
		Call [CCustomMessage::GetMessage]
		Push Eax
		Lea Ecx,Dword Ptr Ss:[Ebp-0x128]
		Push Ecx
		Call [PrintPlayerLevelAddress1]
		Add Esp,0x10
		Jmp [PrintPlayerLevelAddress2]
	}
}

__declspec(naked) void PrintPlayerViewHP1() // OK
{
	static DWORD PrintPlayerViewHPAddress1 = 0x0080FD27;

	_asm
	{
		Mov Ecx,ViewMaxHP
		Test Ecx,Ecx
		Jle EXIT
		Mov Edx,ViewMaxHP
		Mov Eax,ViewCurHP
		Sub Edx,Eax
		Mov Dword Ptr Ss:[Ebp-0x174],Edx
		Fild Dword Ptr Ss:[Ebp-0x174]
		Mov Ecx,ViewMaxHP
		Mov Dword Ptr Ss:[Ebp-0x178],Ecx
		Fidiv Dword Ptr Ss:[Ebp-0x178]
		Fstp Dword Ptr Ss:[Ebp-0x134]
		EXIT:
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewHP2() // OK
{
	static float PositionModifierHP = 3.25f;

	static DWORD PrintPlayerViewHPAddress1 = 0x0080FF12;

	_asm
	{
		Mov Ecx,ViewCurHP
		Push Ecx
		Push Ecx
		Fld Dword Ptr Ds:[0x00D461A4]
		Fstp Dword Ptr Ss:[Esp]
		Fld Dword Ptr Ss:[Ebp-0x0C]
		Cmp Ecx,0x186A0
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierHP]
		Cmp Ecx,0xF4240
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierHP]
		EXIT:
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP1() // OK
{
	static DWORD PrintPlayerViewMPAddress1 = 0x0080FD5B;

	_asm
	{
		Mov Edx,ViewMaxMP
		Test Edx,Edx
		Jle EXIT
		Mov Eax,ViewMaxMP
		Mov Ecx,ViewCurMP
		Sub Eax,Ecx
		Mov Dword Ptr Ss:[Ebp-0x17C],Eax
		Fild Dword Ptr Ss:[Ebp-0x17C]
		Mov Edx,ViewMaxMP
		Mov Dword Ptr Ss:[Ebp-0x180],Edx
		Fidiv Dword Ptr Ss:[Ebp-0x180]
		Fstp Dword Ptr Ss:[Ebp-0x10]
		EXIT:
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP2() // OK
{
	static float PositionModifierMP = 3.25f;

	static DWORD PrintPlayerViewMPAddress1 = 0x008100A5;

	_asm
	{
		Mov Ecx,ViewCurMP
		Push Ecx
		Push Ecx
		Fld Dword Ptr Ds:[0x00D461A4]
		Fstp Dword Ptr Ss:[Esp]
		Fld Dword Ptr Ss:[Ebp-0x0C]
		Cmp Ecx,0x186A0
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierMP]
		Cmp Ecx,0xF4240
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierMP]
		EXIT:
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP1() // OK
{
	static DWORD PrintPlayerViewBPAddress1 = 0x0081028C;

	_asm
	{
		Mov Ecx,ViewMaxBP
		Test Ecx,Ecx
		Jle EXIT
		Mov Edx,ViewMaxBP
		Mov Eax,ViewCurBP
		Sub Edx,Eax
		Mov Dword Ptr Ss:[Ebp-0x140],Edx
		Fild Dword Ptr Ss:[Ebp-0x140]
		Mov Ecx,ViewMaxBP
		Mov Dword Ptr Ss:[Ebp-0x144],Ecx
		Fidiv Dword Ptr Ss:[Ebp-0x144]
		Fstp Dword Ptr Ss:[Ebp-0x24]
		EXIT:
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP2() // OK
{
	static float PositionModifierBP = 3.25f;

	static DWORD PrintPlayerViewBPAddress1 = 0x00810373;

	_asm
	{
		Mov Edx,ViewCurBP
		Push Edx
		Push Ecx
		Fld Dword Ptr Ds:[0x00D461A4]
		Fstp Dword Ptr Ss:[Esp]
		Fld Dword Ptr Ss:[Ebp-0x10]
		Cmp Edx,0x186A0
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierBP]
		Cmp Edx,0xF4240
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierBP]
		EXIT:
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD1() // OK
{
	static DWORD PrintPlayerViewSDAddress1 = 0x0081055C;

	_asm
	{
		Mov Ecx,ViewMaxSD
		Test Ecx,Ecx
		Jle EXIT
		Mov Edx,ViewMaxSD
		Mov Eax,ViewCurSD
		Sub Edx,Eax
		Mov Dword Ptr Ss:[Ebp-0x140],Edx
		Fild Dword Ptr Ss:[Ebp-0x140]
		Mov Ecx,ViewMaxSD
		Mov Dword Ptr Ss:[Ebp-0x144],Ecx
		Fidiv Dword Ptr Ss:[Ebp-0x144]
		Fstp Dword Ptr Ss:[Ebp-0x14]
		EXIT:
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD2() // OK
{
	static float PositionModifierSD = 3.25f;

	static DWORD PrintPlayerViewSDAddress1 = 0x00810643;

	_asm
	{
		Mov Edx,ViewCurSD
		Push Edx
		Push Ecx
		Fld Dword Ptr Ds:[0x00D461A4]
		Fstp Dword Ptr Ss:[Esp]
		Fld Dword Ptr Ss:[Ebp-0x10]
		Cmp Edx,0x186A0
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierSD]
		Cmp Edx,0xF4240
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierSD]
		EXIT:
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience1() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0064C945;

	_asm
	{
		Mov Ecx,ViewExperience
		Mov Edx,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Sub Ecx,Dword Ptr Ds:[Edx+0x10]
		Jmp [PrintPlayerViewLevelUpExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0064C9EF;

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
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x006515A1;

	_asm
	{
		Lea Edx,ViewMasterExperience
		Mov Eax,Dword Ptr Ds:[Edx+0x00]
		Sub Eax,Dword Ptr Ds:[0x087935E0]
		Mov Ecx,Dword Ptr Ds:[Edx+0x04]
		Sbb Ecx,Dword Ptr Ds:[0x087935E4]
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpMasterExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x00651658;

	_asm
	{
		Lea Eax,ViewMasterExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x087935E0],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x087935E4],Edx
		Lea Eax,ViewMasterNextExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x087935E8],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x087935EC],Edx
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewText() // OK
{
	static DWORD PrintPlayerViewTextAddress1 = 0x0040232E;

	_asm
	{
		Cmp Ecx,0xA0000000
		Jle NEXT1
		Mov Dword Ptr Ss:[Ebp-0x04],0x08128ADC
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
		Add Esp,0x08
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Jmp [PrintPlayerViewTextAddress1]
	}
}

__declspec(naked) void PrintPlayerSetAttackSpeed() // OK
{
	static DWORD PrintPlayerSetAttackSpeedAddress1 = 0x00593C6E;

	_asm
	{
		Mov Eax,ViewPhysiSpeed
		Mov Ecx,Dword Ptr Ss:[Ebp-0x2C]
		Mov Edx,Dword Ptr Ds:[gProtect.m_MainInfo.DWMaxAttackSpeed+Ecx*4]
		And Edx,0xFFFF
		Cmp Eax,Edx
		Jle NEXT1
		Mov Eax,Edx
		NEXT1:
		Mov Ecx,Dword Ptr Ss:[Ebp-0x78]
		Mov Word Ptr Ds:[Ecx+0x54],Ax
		Mov Edx,ViewMagicSpeed
		Mov Eax,Dword Ptr Ss:[Ebp-0x2C]
		Mov Ecx,Dword Ptr Ds:[gProtect.m_MainInfo.DWMaxAttackSpeed+Eax*4]
		And Ecx,0xFFFF
		Cmp Edx,Ecx
		Jle NEXT2
		Mov Edx,Ecx
		NEXT2:
		Mov Eax,Dword Ptr Ss:[Ebp-0x78]
		Mov Word Ptr Ds:[Eax+0x60],Dx
		Jmp [PrintPlayerSetAttackSpeedAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillMagicDamage() // OK
{
	static DWORD PrintPlayerGetSkillMagicDamageAddress1 = 0x00595EA8;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillMagicDamage,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Movzx Eax,Word Ptr Ds:[Edx+0x62]
		Jmp [PrintPlayerGetSkillMagicDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillPhysiDamage() // OK
{
	static DWORD PrintPlayerGetSkillPhysiDamageAddress1 = 0x00596148;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillPhysiDamage,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Jmp [PrintPlayerGetSkillPhysiDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerViewStrength() // OK
{
	static DWORD PrintPlayerViewStrengthAddress1 = 0x007801B5;

	_asm
	{
		Push 0
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Edx,ViewStrength
		Add Edx,ViewAddStrength
		Push Edx
		Jmp [PrintPlayerViewStrengthAddress1]
	}
}

__declspec(naked) void PrintPlayerViewDexterity() // OK
{
	static DWORD PrintPlayerViewDexterityAddress1 = 0x007818F7;

	_asm
	{
		Push 1
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Ecx,ViewDexterity
		Add Ecx,ViewAddDexterity
		Push Ecx
		Jmp [PrintPlayerViewDexterityAddress1]
	}
}

__declspec(naked) void PrintPlayerViewVitality() // OK
{
	static DWORD PrintPlayerViewVitalityAddress1 = 0x00782CF1;

	_asm
	{
		Push 2
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Edx,ViewVitality
		Add Edx,ViewAddVitality
		Push Edx
		Jmp [PrintPlayerViewVitalityAddress1]
	}
}

__declspec(naked) void PrintPlayerViewEnergy() // OK
{
	static DWORD PrintPlayerViewEnergyAddress1 = 0x007830CB;

	_asm
	{
		Push 3
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Ecx,ViewEnergy
		Add Ecx,ViewAddEnergy
		Push Ecx
		Jmp [PrintPlayerViewEnergyAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLeadership() // OK
{
	static DWORD PrintPlayerViewLeadershipAddress1 = 0x00784B57;

	_asm
	{
		Push 4
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Edx,ViewLeadership
		Add Edx,ViewAddLeadership
		Push Edx
		Jmp [PrintPlayerViewLeadershipAddress1]
	}
}
