#include "stdafx.h"
#include "PetHook.h"
#include "Util.h"
#include "Defines.h"
#include "TMemory.h"

ObjCreateBug gObjCreateBug		= (ObjCreateBug)0x00501700;
ObjCreatePet gObjCreatePet		= (ObjCreatePet)0x00835E40;

void gObjCreatePetEx(int ItemId)
{
    int ItemSwitch        = *(WORD*)ItemId;
    int PetPreview        = LODWORD(pPreviewPetThis) + 776;
    // ----
    switch (ItemSwitch)
    {
        case ItemId(13, 145):
            gObjCreateBug(eBugType::NewPet, PetPreview + 252, PetPreview, 0, 0);
        break;
        // ---
    }
    gObjCreatePet(ItemId);
}


void gObjCreatePetExHook()
{
    SetHook((LPVOID)gObjCreatePetEx,(LPVOID)0x007DD304,ASM::CALL);
    SetHook((LPVOID)gObjCreatePetEx,(LPVOID)0x00833B08,ASM::CALL);
}
