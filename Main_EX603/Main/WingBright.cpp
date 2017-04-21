#include "stdafx.h"
#include "WingBright.h"
#include "Offset.h"
#include "Util.h"
#include "TMemory.h"
#include "ToolKit.h"
#include "Import.h"
#include "Defines.h"
// ---------------------------------------------------------------------------------------------

Wings gWings;
// ---------------------------------------------------------------------------------------------

DWORD dwItemId;
DWORD dwWingThis;
DWORD dwWingStyle;
DWORD dwWingEff;
// ----
DWORD mdTmpEax;
DWORD mdTmpEsi;
DWORD mdTmpEdi;
DWORD mdTmpEcx;
DWORD mdTmpEdx;
DWORD mdTmpEbx;
DWORD mdTmpEbp;
DWORD mdTmpEsp;
// ----
DWORD dwCustomItemGlowJmp00		= 0x005FAA3F; //0x005E04E6 1.03Y
DWORD dwCustomItemGlowJmp01		= 0x005FAA33; //0x005E5375 1.03Y
// ---------------------------------------------------------------------------------------------

Naked(CustomItemGlow)
{
        _asm
        {
                MOV mdTmpEax,EAX
                MOV mdTmpEsi,ESI
                MOV mdTmpEdi,EDI
                MOV mdTmpEcx,ECX
                MOV mdTmpEdx,EDX
                MOV mdTmpEbx,EBX
                // ----
                MOV EAX, DWORD PTR SS:[EBP+0x10]
                MOV dwItemId, EAX
                // ----
                MOV EDX,DWORD PTR SS:[EBP+0x8]
                MOV dwWingThis, EDX
                // ----
                MOV EAX,DWORD PTR SS:[EBP+0xC]
                MOV dwWingStyle, EAX
                // ----
        }
        // ----
        if(dwItemId == ITEM2(12,181) || dwItemId == ITEM2(12,182)  || dwItemId == ITEM2(12,183) || dwItemId == ITEM2(12,184)
		 || dwItemId == ITEM2(12,185) || dwItemId == ITEM2(12,186) || dwItemId == ITEM2(12,187) || dwItemId == ITEM2(12,188)
		 || dwItemId == ITEM2(12,189) || dwItemId == ITEM2(12,190) || dwItemId == ITEM2(12,191) || dwItemId == ITEM2(12,192)
		 || dwItemId == ITEM2(12,193) || dwItemId == ITEM2(12,194) || dwItemId == ITEM2(12,195) || dwItemId == ITEM2(12,196)
		 || dwItemId == ITEM2(12,197) || dwItemId == ITEM2(12,198) || dwItemId == ITEM2(12,199) || dwItemId == ITEM2(12,200)
		 || dwItemId == ITEM2(12,201) || dwItemId == ITEM2(12,202) || dwItemId == ITEM2(12,203) || dwItemId == ITEM2(12,204)
		 || dwItemId == ITEM2(12,205) || dwItemId == ITEM2(12,206) || dwItemId == ITEM2(12,207) || dwItemId == ITEM2(12,208)
		 || dwItemId == ITEM2(12,209) || dwItemId == ITEM2(12,210) || dwItemId == ITEM2(12,211) || dwItemId == ITEM2(12,212)
		 || dwItemId == ITEM2(12,213) || dwItemId == ITEM2(12,214) || dwItemId == ITEM2(12,215) || dwItemId == ITEM2(12,216)
		 || dwItemId == ITEM2(12,217) || dwItemId == ITEM2(12,218) || dwItemId == ITEM2(12,219) || dwItemId == ITEM2(12,220)
		 || dwItemId == ITEM2(12,221) || dwItemId == ITEM2(12,222) || dwItemId == ITEM2(12,223) || dwItemId == ITEM2(12,224)
		 || dwItemId == ITEM2(12,225) || dwItemId == ITEM2(12,226) || dwItemId == ITEM2(12,227) || dwItemId == ITEM2(12,228)
		 || dwItemId == ITEM2(12,229) || dwItemId == ITEM2(12,230) || dwItemId == ITEM2(12,231) || dwItemId == ITEM2(12,232)
		 || dwItemId == ITEM2(12,233) || dwItemId == ITEM2(12,234) || dwItemId == ITEM2(12,235) || dwItemId == ITEM2(12,236)
		 || dwItemId == ITEM2(12,237) || dwItemId == ITEM2(12,238) || dwItemId == ITEM2(12,239) || dwItemId == ITEM2(12,240)
		 || dwItemId == ITEM2(12,241) || dwItemId == ITEM2(12,242) || dwItemId == ITEM2(12,243) || dwItemId == ITEM2(12,244)
		 || dwItemId == ITEM2(12,245) || dwItemId == ITEM2(12,246) || dwItemId == ITEM2(12,247) || dwItemId == ITEM2(12,248)
		 || dwItemId == ITEM2(12,249) || dwItemId == ITEM2(12,250) || dwItemId == ITEM2(12,251) || dwItemId == ITEM2(12,252)
		 || dwItemId == ITEM2(12,180)
		 )
        {
                // ----
                *(float*)(dwWingThis+72) = 1.0;
                *(float*)(dwWingThis+76) = 1.0;
                *(float*)(dwWingThis+80) = 1.0;
                // ----
                glColor3fv((GLfloat*)(dwWingThis+72));
                // ----
                pCustomEffGet2(dwWingThis,
                        2,
                        *(float*)(dwWingStyle+152),
                        *(DWORD*)(dwWingStyle+68),
                        *(float*)(dwWingStyle+100),
                        *(float*)(dwWingStyle+104),
                        *(float*)(dwWingStyle+108),
                        *(DWORD*)(dwWingStyle+60),
                        -1);
                // ----
        }

        if(dwItemId == ITEM2(12,1080))
        {
                // ----
                *(float*)(dwWingThis+72) = 1.5;
                *(float*)(dwWingThis+76) = 1.2;
                *(float*)(dwWingThis+80) = 1.1;
                // ----
                glColor3fv((GLfloat*)(dwWingThis+72));
                // ----
                pTexEffect(dwWingThis,1,0x42,*(float*)(dwWingStyle+152),
                        *(DWORD*)(dwWingStyle+68),
                        *(float*)(dwWingStyle+100),
                        *(float*)(dwWingStyle+104),
                        *(float*)(dwWingStyle+108),
                        -1);
                // ----
                pTexEffect(dwWingThis,0,2,*(float*)(dwWingStyle+152),
                        *(DWORD*)(dwWingStyle+68),
                        *(float*)(dwWingStyle+100),
                        *(float*)(dwWingStyle+104),
                        *(float*)(dwWingStyle+108),
                        -1);
                // ----
                pTexEffect(dwWingThis,0,0x42,*(float*)(dwWingStyle+152),
                        *(DWORD*)(dwWingStyle+68),
                        *(float*)(dwWingStyle+100),
                        *(float*)(dwWingStyle+104),
                        *(float*)(dwWingStyle+108),
                        -1); //
 
                _asm
                {
                        MOV EAX,mdTmpEax
                        MOV ESI,mdTmpEsi
                        MOV EDI,mdTmpEdi
                        MOV ECX,mdTmpEcx
                        MOV EDX,mdTmpEdx
                        MOV EBX,mdTmpEbx
                        //---
                        JMP dwCustomItemGlowJmp01
                }
        }
        // ----
        _asm
        {
                MOV EAX,mdTmpEax
                MOV ESI,mdTmpEsi
                MOV EDI,mdTmpEdi
                MOV ECX,mdTmpEcx
                MOV EDX,mdTmpEdx
                MOV EBX,mdTmpEbx
                //---
                CMP DWORD PTR SS:[EBP+0x10],0x1CB7 // 1.04D GMO
                JMP dwCustomItemGlowJmp00
        }
}
Naked(HieuUngBufferGlow)
{
	DWORD dwItem;
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
			MOV dwItem, EAX
			// ----
			CMP dwItem, ITEM2(12, 180)
			JE Return
			//CMP dwItem, ITEM2(12, 182)
			//JE Return
			CMP dwItem, ITEM2(12, 183)
			JE Return
			/*CMP dwItem, ITEM2(12, 186)
			JE Return*/
			//CMP dwItem, ITEM2(12, 184)
			//JE Return
			CMP dwItem, ITEM2(12, 188)
			JE Return
			CMP dwItem, ITEM2(12, 189)
			JE Return
			CMP dwItem, ITEM2(12, 190)
			JE Return
			CMP dwItem, ITEM2(12, 191)
			JE Return
			CMP dwItem, ITEM2(12, 193)
			JE Return
			CMP dwItem, ITEM2(12, 194)
			JE Return
			CMP dwItem, ITEM2(12, 196)
			JE Return
			//CMP dwItem, ITEM2(12, 195)
			//JE Return
			CMP dwItem, ITEM2(12, 197)
			JE Return
			CMP dwItem, ITEM2(12, 198)
			JE Return
			//CMP dwItem, ITEM2(12, 198)
			//JE Return
			//CMP dwItem, ITEM2(12, 199)
			//JE Return
			CMP dwItem, ITEM2(12, 201)
			JE Return
			
	
			//CMP dwItem, ITEM2(12, 204)
		//	JE Return
		//	CMP dwItem, ITEM2(12, 205)
			//JE Return
			CMP dwItem, ITEM2(12, 202)
			JE Return
		//	CMP dwItem, ITEM2(12, 210)
		//	JE Return
		//	CMP dwItem, ITEM2(12, 210)
		
		Return :
		MOV EAX, 0x005FF983
			JMP EAX
	}
}

void Wings::Load()
{
	SetRange((LPVOID)0x005FAA38 , 7, ASM::NOP);
	SetOp((LPVOID)0x005FAA38, (LPVOID)CustomItemGlow, ASM::JMP);
	SetRange((LPVOID)0x005FF97C, 1, ASM::NOP);
	SetOp((LPVOID)0x005FF97C, HieuUngBufferGlow, ASM::JMP);
}
// ---------------------------------------------------------------------------------------------

