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
DWORD ViewDarkSpiritAttackDamageMin = 0;
DWORD ViewDarkSpiritAttackDamageMax = 0;
DWORD ViewDarkSpiritAttackSpeed = 0;
DWORD ViewDarkSpiritAttackSuccessRate = 0;
DWORD ViewSkillMagicDamage = 0;
DWORD ViewSkillPhysiDamage = 0;

void InitPrintPlayer() // OK
{
	MemorySet(0x0061807D,0x90,6); // Master Experience

	SetDword(0x004A022B,0xA0000001); // PrintTextReplace 64

	SetDword(0x00587AB6,0xA0000002); // PrintTextReplace 64

	SetDword(0x006D7DDF,0xA0000003); // PrintTextReplace 64

	SetDword(0x00744526,0xA0000004); // PrintTextReplace 64

	SetDword(0x007449E3,0xA0000005); // PrintTextReplace 64

	SetDword(0x004A01D1,0xA0000001); // PrintTextReplace 203

	SetDword(0x006D7298,0xA0000002); // PrintTextReplace 203

	SetDword(0x006D72DA,0xA0000003); // PrintTextReplace 203

	SetDword(0x007444CB,0xA0000004); // PrintTextReplace 203

	SetDword(0x00744988,0xA0000005); // PrintTextReplace 203

	SetDword(0x0071A5FE,0xA0000001); // PrintTextReplace 358

	SetDword(0x00744302,0xA0000002); // PrintTextReplace 358

	SetDword(0x007447C0,0xA0000003); // PrintTextReplace 358

	SetCompleteHook(0xE9,0x006D5E42,&PrintPlayerLevel1);

	SetCompleteHook(0xE9,0x006D5E77,&PrintPlayerLevel2);

	SetCompleteHook(0xE9,0x0071A3E9,&PrintPlayerViewHP1);

	SetCompleteHook(0xE9,0x0071A589,&PrintPlayerViewHP2);

	SetCompleteHook(0xE9,0x0071A42F,&PrintPlayerViewMP1);

	SetCompleteHook(0xE9,0x0071A6CB,&PrintPlayerViewMP2);

	SetCompleteHook(0xE9,0x0071A89E,&PrintPlayerViewBP1);

	SetCompleteHook(0xE9,0x0071A96C,&PrintPlayerViewBP2);

	SetCompleteHook(0xE9,0x0071AB36,&PrintPlayerViewSD1);

	SetCompleteHook(0xE9,0x0071AC10,&PrintPlayerViewSD2);

	SetCompleteHook(0xE9,0x0060FD79,&PrintPlayerViewLevelUpExperience1);

	SetCompleteHook(0xE9,0x0060FF11,&PrintPlayerViewLevelUpExperience2);

	SetCompleteHook(0xE9,0x00618029,&PrintPlayerViewLevelUpMasterExperience1);

	SetCompleteHook(0xE9,0x00618183,&PrintPlayerViewLevelUpMasterExperience2);

	SetCompleteHook(0xE9,0x004024D7,&PrintPlayerViewText);

	SetCompleteHook(0xE9,0x0050A0AA,&PrintPlayerSetAttackSpeed);

	SetCompleteHook(0xE9,0x0050B8A6,&PrintPlayerGetSkillMagicDamage);

	SetCompleteHook(0xE9,0x0050BA5F,&PrintPlayerGetSkillPhysiDamage);

	SetCompleteHook(0xE9,0x006D64B7,&PrintPlayerViewStrength);

	SetCompleteHook(0xE9,0x006D75FE,&PrintPlayerViewDexterity);

	SetCompleteHook(0xE9,0x006D8090,&PrintPlayerViewVitality);

	SetCompleteHook(0xE9,0x006D8370,&PrintPlayerViewEnergy);

	SetCompleteHook(0xE9,0x006D901B,&PrintPlayerViewLeadership);

	SetCompleteHook(0xE8,0x004C3E91,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00606D00,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00606E98,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00606FB0,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00607016,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x0060738E,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006073E9,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00607485,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x006074E0,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00607500,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x00607560,&PrintDamageOnScreenSD);

	SetCompleteHook(0xE8,0x0060C10D,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0060C95C,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0060C98C,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0060D3CC,&PrintDamageOnScreenHP);

	SetCompleteHook(0xE8,0x0060D3FC,&PrintDamageOnScreenHP);
}

void PrintDamageOnScreenHP(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageHP;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x006A2D30)(a,b,c,d,e);
}

void PrintDamageOnScreenSD(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(((int)b) > 0)
	{
		b = ViewDamageSD;
	}

	((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x006A2D30)(a,b,c,d,e);
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
					value[1] = ViewPhysiSpeed;
					break;
				case 4:
					value[1] = ViewDarkSpiritAttackSpeed;
					break;
				case 5:
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
	static DWORD PrintPlayerLevelAddress1 = 0x004B23E0;
	static DWORD PrintPlayerLevelAddress2 = 0x006D5E61;

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
	static DWORD PrintPlayerLevelAddress1 = 0x004B23E0;
	static DWORD PrintPlayerLevelAddress2 = 0x006D5EA3;

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
	static DWORD PrintPlayerViewHPAddress1 = 0x0071A42F;

	_asm
	{
		Mov Eax,ViewMaxHP
		Test Eax,Eax
		Jle EXIT
		Mov Ecx,ViewMaxHP
		Mov Edx,ViewCurHP
		Sub Ecx,Edx
		Mov Dword Ptr Ss:[Ebp-0x174],Ecx
		Fild Dword Ptr Ss:[Ebp-0x174]
		Mov Eax,ViewMaxHP
		Mov Dword Ptr Ss:[Ebp-0x178],Eax
		Fidiv Dword Ptr Ss:[Ebp-0x178]
		Fstp Dword Ptr Ss:[Ebp-0x134]
		EXIT:
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewHP2() // OK
{
	static float PositionModifierHP = 3.25f;

	static DWORD PrintPlayerViewHPAddress1 = 0x0071A59B;

	_asm
	{
		Mov Edx,ViewCurHP
		Push Edx
		Push 0x43E70000
		Fld Dword Ptr Ss:[Ebp-0x18]
		Cmp Edx,0x186A0
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierHP]
		Cmp Edx,0xF4240
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierHP]
		EXIT:
		Jmp [PrintPlayerViewHPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP1() // OK
{
	static DWORD PrintPlayerViewMPAddress1 = 0x0071A473;

	_asm
	{
		Mov Ecx,ViewMaxMP
		Test Ecx,Ecx
		Jle EXIT
		Mov Edx,ViewMaxMP
		Mov Eax,ViewCurMP
		Sub Edx,Eax
		Mov Dword Ptr Ss:[Ebp-0x17C],Edx
		Fild Dword Ptr Ss:[Ebp-0x17C]
		Mov Ecx,ViewMaxMP
		Mov Dword Ptr Ss:[Ebp-0x180],Ecx
		Fidiv Dword Ptr Ss:[Ebp-0x180]
		Fstp Dword Ptr Ss:[Ebp-0x20]
		EXIT:
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewMP2() // OK
{
	static float PositionModifierMP = 3.25f;

	static DWORD PrintPlayerViewMPAddress1 = 0x0071A6DC;

	_asm
	{
		Mov Eax,ViewCurMP
		Push Eax
		Push 0x43E70000
		Fld Dword Ptr Ss:[Ebp-0x18]
		Cmp Eax,0x186A0
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierMP]
		Cmp Eax,0xF4240
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierMP]
		EXIT:
		Jmp [PrintPlayerViewMPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP1() // OK
{
	static DWORD PrintPlayerViewBPAddress1 = 0x0071A8D5;

	_asm
	{
		Mov Eax,ViewMaxBP
		Test Eax,Eax
		Jle EXIT
		Mov Ecx,ViewMaxBP
		Mov Edx,ViewCurBP
		Sub Ecx,Edx
		Mov Dword Ptr Ss:[Ebp-0x140],Ecx
		Fild Dword Ptr Ss:[Ebp-0x140]
		Mov Eax,ViewMaxBP
		Mov Dword Ptr Ss:[Ebp-0x144],Eax
		Fidiv Dword Ptr Ss:[Ebp-0x144]
		Fstp Dword Ptr Ss:[Ebp-0x04]
		EXIT:
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewBP2() // OK
{
	static float PositionModifierBP = 3.25f;

	static DWORD PrintPlayerViewBPAddress1 = 0x0071A97D;

	_asm
	{
		Mov Eax,ViewCurBP
		Push Eax
		Push 0x43E70000
		Fld Dword Ptr Ss:[Ebp-0x20]
		Cmp Eax,0x186A0
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierBP]
		Cmp Eax,0xF4240
		Jl EXIT
		Fsub Dword Ptr Ds:[PositionModifierBP]
		EXIT:
		Jmp [PrintPlayerViewBPAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD1() // OK
{
	static DWORD PrintPlayerViewSDAddress1 = 0x0071AB79;

	_asm
	{
		Mov Eax,ViewMaxSD
		Test Eax,Eax
		Jle EXIT
		Mov Ecx,ViewMaxSD
		Mov Edx,ViewCurSD
		Sub Ecx,Edx
		Mov Dword Ptr Ss:[Ebp-0x140],Ecx
		Fild Dword Ptr Ss:[Ebp-0x140]
		Mov Eax,ViewMaxSD
		Mov Dword Ptr Ss:[Ebp-0x144],Eax
		Fidiv Dword Ptr Ss:[Ebp-0x144]
		Fstp Dword Ptr Ss:[Ebp-0x04]
		EXIT:
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewSD2() // OK
{
	static float PositionModifierSD = 3.25f;

	static DWORD PrintPlayerViewSDAddress1 = 0x0071AC21;

	_asm
	{
		Mov Eax,ViewCurSD
		Push Eax
		Push 0x43E70000
		Fld Dword Ptr Ss:[Ebp-0x1C]
		Cmp Eax,0x186A0
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierSD]
		Cmp Eax,0xF4240
		Jl EXIT
		Fadd Dword Ptr Ds:[PositionModifierSD]
		EXIT:
		Jmp [PrintPlayerViewSDAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience1() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0060FD85;

	_asm
	{
		Mov Esi,ViewExperience
		Lea Ecx,Dword Ptr Ss:[Esp+0x38]
		Sub Esi,Dword Ptr Ds:[Edx+0x10]
		Jmp [PrintPlayerViewLevelUpExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpExperienceAddress1 = 0x0060FF28;

	_asm
	{
		Mov Dword Ptr Ss:[Esp+0x18],Ebx
		Mov Dword Ptr Ss:[Esp+0x1C],Ebx
		Mov Dword Ptr Ss:[Esp+0x20],Ebx
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
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x00618044;

	_asm
	{
		Lea Ecx,Dword Ptr Ss:[Esp+0x34]
		Stos Word Ptr Es:[Edi]
		Stos Byte Ptr Es:[Edi]
		Mov Word Ptr Ds:[0x07FE8D36],Dx
		Lea Edx,ViewMasterExperience
		Mov Esi,Dword Ptr Ds:[Edx+0x00]
		Sub Esi,Dword Ptr Ds:[0x07FE8D18]
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewLevelUpMasterExperience2() // OK
{
	static DWORD PrintPlayerViewLevelUpMasterExperienceAddress1 = 0x0061819A;

	_asm
	{
		Mov Dword Ptr Ss:[Esp+0x18],Ebx
		Mov Dword Ptr Ss:[Esp+0x1C],Ebx
		Mov Dword Ptr Ss:[Esp+0x20],Ebx
		Lea Eax,ViewMasterExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x07FE8D18],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x07FE8D1C],Edx
		Lea Eax,ViewMasterNextExperience
		Mov Ecx,Dword Ptr Ds:[Eax+0x00]
		Mov Dword Ptr Ds:[0x07FE8D20],Ecx
		Mov Edx,Dword Ptr Ds:[Eax+0x04]
		Mov Dword Ptr Ds:[0x07FE8D24],Edx
		Jmp [PrintPlayerViewLevelUpMasterExperienceAddress1]
	}
}

__declspec(naked) void PrintPlayerViewText() // OK
{
	static DWORD PrintPlayerViewTextAddress1 = 0x004024DE;

	_asm
	{
		Cmp Ecx,0xA0000000
		Jle NEXT1
		Mov Dword Ptr Ss:[Ebp-0x04],0x079F5190
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
	static DWORD PrintPlayerSetAttackSpeedAddress1 = 0x0050A1BC;

	_asm
	{
		Mov Eax,ViewPhysiSpeed
		Mov Ecx,Dword Ptr Ss:[Ebp-0x24]
		Mov Edx,Dword Ptr Ds:[gProtect.m_MainInfo.DWMaxAttackSpeed+Ecx*4]
		And Edx,0xFFFF
		Cmp Eax,Edx
		Jle NEXT1
		Mov Eax,Edx
		NEXT1:
		Mov Ecx,Dword Ptr Ss:[Ebp-0x68]
		Mov Word Ptr Ds:[Ecx+0x54],Ax
		Mov Edx,ViewMagicSpeed
		Mov Eax,Dword Ptr Ss:[Ebp-0x24]
		Mov Ecx,Dword Ptr Ds:[gProtect.m_MainInfo.DWMaxAttackSpeed+Eax*4]
		And Ecx,0xFFFF
		Cmp Edx,Ecx
		Jle NEXT2
		Mov Edx,Ecx
		NEXT2:
		Mov Eax,Dword Ptr Ss:[Ebp-0x68]
		Mov Word Ptr Ds:[Eax+0x60],Dx
		Jmp [PrintPlayerSetAttackSpeedAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillMagicDamage() // OK
{
	static DWORD PrintPlayerGetSkillMagicDamageAddress1 = 0x0050B8AF;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillMagicDamage,Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Movzx Edx,Word Ptr Ds:[Ecx+0x62]
		Jmp [PrintPlayerGetSkillMagicDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerGetSkillPhysiDamage() // OK
{
	static DWORD PrintPlayerGetSkillPhysiDamageAddress1 = 0x0050BA65;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Mov ViewSkillPhysiDamage,Eax
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Jmp [PrintPlayerGetSkillPhysiDamageAddress1]
	}
}

__declspec(naked) void PrintPlayerViewStrength() // OK
{
	static DWORD PrintPlayerViewStrengthAddress1 = 0x006D64C4;

	_asm
	{
		Push 0
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Ecx,ViewStrength
		Add Ecx,ViewAddStrength
		Push Ecx
		Jmp [PrintPlayerViewStrengthAddress1]
	}
}

__declspec(naked) void PrintPlayerViewDexterity() // OK
{
	static DWORD PrintPlayerViewDexterityAddress1 = 0x006D760B;

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
	static DWORD PrintPlayerViewVitalityAddress1 = 0x006D809D;

	_asm
	{
		Push 2
		Call [PrintFixStatPoint]
		Add Esp,0x04
		Mov Ecx,ViewVitality
		Add Ecx,ViewAddVitality
		Push Ecx
		Jmp [PrintPlayerViewVitalityAddress1]
	}
}

__declspec(naked) void PrintPlayerViewEnergy() // OK
{
	static DWORD PrintPlayerViewEnergyAddress1 = 0x006D837D;

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
	static DWORD PrintPlayerViewLeadershipAddress1 = 0x006D9027;

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
