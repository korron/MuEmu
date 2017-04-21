#define ItemId(x, y)            ((x * 512) + y)
#define pPreviewPetThis            *(DWORD*)0x007BC4F04
#define LODWORD(h)                ((DWORD)(__int64(h) & __int64(0xffffffff)))

enum eBugType
{
    NewPet        = 7972,
};

typedef void (__thiscall *ObjCreatePet)(int ItemId);
extern ObjCreatePet gObjCreatePet;
// --
typedef int (__cdecl *ObjCreateBug)(int BugId, int Arg2, int Arg3, int Arg4, int Arg5);
extern ObjCreateBug gObjCreateBug;
// --
void gObjCreatePetExHook();