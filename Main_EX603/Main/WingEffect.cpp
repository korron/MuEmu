#include "stdafx.h"
#include "Item.h"
#include "WingEffect.h"
#include "TMemory.h"
#include "Import.h"
#include "Util.h"
#include "Defines.h"

DWORD	AddWingsEffect_Buff;
float	Color[3];
LPVOID	F1_This;
DWORD	F1_Arg1;
DWORD	F1_Arg11;
DWORD	F1_Arg2;
DWORD	F2_Arg5;
DWORD	F3_Arg3;
//
LPVOID  F1_Thisv1;
DWORD   F1_Arg1v1;
DWORD   F1_Arg11v1;
DWORD   F1_Arg2v1;
DWORD   F2_Arg5v1;
DWORD   F3_Arg3v1;
//
LPVOID  F1_Thisv2;
DWORD   F1_Arg1v2;
DWORD   F1_Arg11v2;
DWORD   F1_Arg2v2;
DWORD   F2_Arg5v2;
DWORD   F3_Arg3v2;
//
LPVOID  F1_Thisv3;
DWORD   F1_Arg1v3;
DWORD   F1_Arg11v3;
DWORD   F1_Arg2v3;
DWORD   F2_Arg5v3;
DWORD   F3_Arg3v3;
//
LPVOID  F1_Thisv4;
DWORD   F1_Arg1v4;
DWORD   F1_Arg11v4;
DWORD   F1_Arg2v4;
DWORD   F2_Arg5v4;
DWORD   F3_Arg3v4;
//
LPVOID  F1_Thisv5;
DWORD   F1_Arg1v5;
DWORD   F1_Arg11v5;
DWORD   F1_Arg2v5;
DWORD   F2_Arg5v5;
DWORD   F3_Arg3v5;
//
LPVOID  F1_Thisv6;
DWORD   F1_Arg1v6;
DWORD   F1_Arg11v6;
DWORD   F1_Arg2v6;
DWORD   F2_Arg5v6;
DWORD   F3_Arg3v6;
//
LPVOID  F1_Thisv7;
DWORD   F1_Arg1v7;
DWORD   F1_Arg11v7;
DWORD   F1_Arg2v7;
DWORD   F2_Arg5v7;
DWORD   F3_Arg3v7;
//
LPVOID  F1_Thisv8;
DWORD   F1_Arg1v8;
DWORD   F1_Arg11v8;
DWORD   F1_Arg2v8;
DWORD   F2_Arg5v8;
DWORD   F3_Arg3v8;
//
LPVOID  F1_Thisv9;
DWORD   F1_Arg1v9;
DWORD   F1_Arg11v9;
DWORD   F1_Arg2v9;
DWORD   F2_Arg5v9;
DWORD   F3_Arg3v9;
//
LPVOID  F1_Thisv10;
DWORD   F1_Arg1v10;
DWORD   F1_Arg11v10;
DWORD   F1_Arg2v10;
DWORD   F2_Arg5v10;
DWORD   F3_Arg3v10;
//
LPVOID  F1_Thisv11;
DWORD   F1_Arg1v11;
DWORD   F1_Arg11v11;
DWORD   F1_Arg2v11;
DWORD   F2_Arg5v11;
DWORD   F3_Arg3v11;
//
LPVOID  F1_Thisv12;
DWORD   F1_Arg1v12;
DWORD   F1_Arg11v12;
DWORD   F1_Arg2v12;
DWORD   F2_Arg5v12;
DWORD   F3_Arg3v12;
//
LPVOID  F1_Thisv13;
DWORD   F1_Arg1v13;
DWORD   F1_Arg11v13;
DWORD   F1_Arg2v13;
DWORD   F2_Arg5v13;
DWORD   F3_Arg3v13;
//
LPVOID  F1_Thisv14;
DWORD   F1_Arg1v14;
DWORD   F1_Arg11v14;
DWORD   F1_Arg2v14;
DWORD   F2_Arg5v14;
DWORD   F3_Arg3v14;
//
LPVOID  F1_Thisv15;
DWORD   F1_Arg1v15;
DWORD   F1_Arg11v15;
DWORD   F1_Arg2v15;
DWORD   F2_Arg5v15;
DWORD   F3_Arg3v15;
//
LPVOID  F1_Thisv16;
DWORD   F1_Arg1v16;
DWORD   F1_Arg11v16;
DWORD   F1_Arg2v16;
DWORD   F2_Arg5v16;
DWORD   F3_Arg3v16;
//
LPVOID  F1_Thisv17;
DWORD   F1_Arg1v17;
DWORD   F1_Arg11v17;
DWORD   F1_Arg2v17;
DWORD   F2_Arg5v17;
DWORD   F3_Arg3v17;
//
LPVOID  F1_Thisv18;
DWORD   F1_Arg1v18;
DWORD   F1_Arg11v18;
DWORD   F1_Arg2v18;
DWORD   F2_Arg5v18;
DWORD   F3_Arg3v18;
//
LPVOID  F1_Thisv19;
DWORD   F1_Arg1v19;
DWORD   F1_Arg11v19;
DWORD   F1_Arg2v19;
DWORD   F2_Arg5v19;
DWORD   F3_Arg3v19;
//
LPVOID  F1_Thisv20;
DWORD   F1_Arg1v20;
DWORD   F1_Arg11v20;
DWORD   F1_Arg2v20;
DWORD   F2_Arg5v20;
DWORD   F3_Arg3v20;
//
LPVOID  F1_Thisv21;
DWORD   F1_Arg1v21;
DWORD   F1_Arg11v21;
DWORD   F1_Arg2v21;
DWORD   F2_Arg5v21;
DWORD   F3_Arg3v21;
//
LPVOID  F1_Thisv22;
DWORD   F1_Arg1v22;
DWORD   F1_Arg11v22;
DWORD   F1_Arg2v22;
DWORD   F2_Arg5v22;
DWORD   F3_Arg3v22;
//
LPVOID  F1_Thisv23;
DWORD   F1_Arg1v23;
DWORD   F1_Arg11v23;
DWORD   F1_Arg2v23;
DWORD   F2_Arg5v23;
DWORD   F3_Arg3v23;
//
LPVOID  F1_Thisv24;
DWORD   F1_Arg1v24;
DWORD   F1_Arg11v24;
DWORD   F1_Arg2v24;
DWORD   F2_Arg5v24;
DWORD   F3_Arg3v24;
//
LPVOID  F1_Thisv25;
DWORD   F1_Arg1v25;
DWORD   F1_Arg11v25;
DWORD   F1_Arg2v25;
DWORD   F2_Arg5v25;
DWORD   F3_Arg3v25;
//
LPVOID  F1_Thisv26;
DWORD   F1_Arg1v26;
DWORD   F1_Arg11v26;
DWORD   F1_Arg2v26;
DWORD   F2_Arg5v26;
DWORD   F3_Arg3v26;
//
LPVOID  F1_Thisv27;
DWORD   F1_Arg1v27;
DWORD   F1_Arg11v27;
DWORD   F1_Arg2v27;
DWORD   F2_Arg5v27;
DWORD   F3_Arg3v27;
//
LPVOID  F1_Thisv28;
DWORD   F1_Arg1v28;
DWORD   F1_Arg11v28;
DWORD   F1_Arg2v28;
DWORD   F2_Arg5v28;
DWORD   F3_Arg3v28;
//
LPVOID  F1_Thisv29;
DWORD   F1_Arg1v29;
DWORD   F1_Arg11v29;
DWORD   F1_Arg2v29;
DWORD   F2_Arg5v29;
DWORD   F3_Arg3v29;
//
LPVOID  F1_Thisv30;
DWORD   F1_Arg1v30;
DWORD   F1_Arg11v30;
DWORD   F1_Arg2v30;
DWORD   F2_Arg5v30;
DWORD   F3_Arg3v30;
//
LPVOID  F1_Thisv31;
DWORD   F1_Arg1v31;
DWORD   F1_Arg11v31;
DWORD   F1_Arg2v31;
DWORD   F2_Arg5v31;
DWORD   F3_Arg3v31;
//
LPVOID  F1_Thisv32;
DWORD   F1_Arg1v32;
DWORD   F1_Arg11v32;
DWORD   F1_Arg2v32;
DWORD   F2_Arg5v32;
DWORD   F3_Arg3v32;
//
LPVOID  F1_Thisv33;
DWORD   F1_Arg1v33;
DWORD   F1_Arg11v33;
DWORD   F1_Arg2v33;
DWORD   F2_Arg5v33;
DWORD   F3_Arg3v33;
//
LPVOID  F1_Thisv34;
DWORD   F1_Arg1v34;
DWORD   F1_Arg11v34;
DWORD   F1_Arg2v34;
DWORD   F2_Arg5v34;
DWORD   F3_Arg3v34;
//
LPVOID  F1_Thisv35;
DWORD   F1_Arg1v35;
DWORD   F1_Arg11v35;
DWORD   F1_Arg2v35;
DWORD   F2_Arg5v35;
DWORD   F3_Arg3v35;
//
LPVOID  F1_Thisv36;
DWORD   F1_Arg1v36;
DWORD   F1_Arg11v36;
DWORD   F1_Arg2v36;
DWORD   F2_Arg5v36;
DWORD   F3_Arg3v36;
//
LPVOID  F1_Thisv37;
DWORD   F1_Arg1v37;
DWORD   F1_Arg11v37;
DWORD   F1_Arg2v37;
DWORD   F2_Arg5v37;
DWORD   F3_Arg3v37;
//
LPVOID  F1_Thisv38;
DWORD   F1_Arg1v38;
DWORD   F1_Arg11v38;
DWORD   F1_Arg2v38;
DWORD   F2_Arg5v38;
DWORD   F3_Arg3v38;
//
LPVOID  F1_Thisv39;
DWORD   F1_Arg1v39;
DWORD   F1_Arg11v39;
DWORD   F1_Arg2v39;
DWORD   F2_Arg5v39;
DWORD   F3_Arg3v39;
//
LPVOID  F1_Thisv40;
DWORD   F1_Arg1v40;
DWORD   F1_Arg11v40;
DWORD   F1_Arg2v40;
DWORD   F2_Arg5v40;
DWORD   F3_Arg3v40;
//
LPVOID  F1_Thisv41;
DWORD   F1_Arg1v41;
DWORD   F1_Arg11v41;
DWORD   F1_Arg2v41;
DWORD   F2_Arg5v41;
DWORD   F3_Arg3v41;
//
LPVOID  F1_Thisv42;
DWORD   F1_Arg1v42;
DWORD   F1_Arg11v42;
DWORD   F1_Arg2v42;
DWORD   F2_Arg5v42;
DWORD   F3_Arg3v42;
//
LPVOID  F1_Thisv43;
DWORD   F1_Arg1v43;
DWORD   F1_Arg11v43;
DWORD   F1_Arg2v43;
DWORD   F2_Arg5v43;
DWORD   F3_Arg3v43;
// ----------------------------------------------------------------------------------------------
Naked(AddWingsEffect)
{
	_asm
	{
		mov AddWingsEffect_Buff, edx
			mov edx, dword ptr ss : [ebp - 0x68]
			mov F1_Thisv1, edx
			mov F1_Thisv2, edx
			mov F1_Thisv3, edx
			mov F1_Thisv4, edx
			mov F1_Thisv5, edx
			mov F1_Thisv6, edx
			mov F1_Thisv7, edx
			mov F1_Thisv8, edx
			mov F1_Thisv9, edx
			mov F1_Thisv10, edx
			mov F1_Thisv11, edx
			mov F1_Thisv12, edx
			mov F1_Thisv13, edx
			mov F1_Thisv14, edx
			mov F1_Thisv15, edx
			mov F1_Thisv16, edx
			mov F1_Thisv17, edx
			mov F1_Thisv18, edx
			mov F1_Thisv19, edx
			mov F1_Thisv20, edx
			mov F1_Thisv21, edx
			mov F1_Thisv22, edx
			mov F1_Thisv23, edx
			mov F1_Thisv24, edx
			mov F1_Thisv25, edx
			mov F1_Thisv26, edx
			mov F1_Thisv27, edx
			mov F1_Thisv28, edx
			mov F1_Thisv29, edx
			mov F1_Thisv30, edx
			mov F1_Thisv31, edx
			mov F1_Thisv32, edx
			mov F1_Thisv33, edx
			mov F1_Thisv34, edx
			mov F1_Thisv35, edx
			mov F1_Thisv36, edx
			mov F1_Thisv37, edx
			mov F1_Thisv38, edx
			mov F1_Thisv39, edx
			mov F1_Thisv40, edx
			mov F1_Thisv41, edx
			mov F1_Thisv42, edx
			mov F1_Thisv43, edx
			lea edx, [ebp - 0x58]
			mov F1_Arg1v1, edx
			mov F1_Arg1v2, edx
			mov F1_Arg1v3, edx
			mov F1_Arg1v4, edx
			mov F1_Arg1v5, edx
			mov F1_Arg1v6, edx
			mov F1_Arg1v7, edx
			mov F1_Arg1v8, edx
			mov F1_Arg1v9, edx
			mov F1_Arg1v10, edx
			mov F1_Arg1v11, edx
			mov F1_Arg1v12, edx
			mov F1_Arg1v13, edx
			mov F1_Arg1v14, edx
			mov F1_Arg1v15, edx
			mov F1_Arg1v16, edx
			mov F1_Arg1v17, edx
			mov F1_Arg1v18, edx
			mov F1_Arg1v19, edx
			mov F1_Arg1v20, edx
			mov F1_Arg1v21, edx
			mov F1_Arg1v22, edx
			mov F1_Arg1v23, edx
			mov F1_Arg1v24, edx
			mov F1_Arg1v25, edx
			mov F1_Arg1v26, edx
			mov F1_Arg1v27, edx
			mov F1_Arg1v28, edx
			mov F1_Arg1v29, edx
			mov F1_Arg1v30, edx
			mov F1_Arg1v31, edx
			mov F1_Arg1v32, edx
			mov F1_Arg1v33, edx
			mov F1_Arg1v34, edx
			mov F1_Arg1v35, edx
			mov F1_Arg1v36, edx
			mov F1_Arg1v37, edx
			mov F1_Arg1v38, edx
			mov F1_Arg1v39, edx
			mov F1_Arg1v40, edx
			mov F1_Arg1v41, edx
			mov F1_Arg1v42, edx
			mov F1_Arg1v43, edx
			lea edx, [ebp - 0x18]
			mov F1_Arg11v1, edx
			mov F1_Arg11v2, edx
			mov F1_Arg11v3, edx
			mov F1_Arg11v4, edx
			mov F1_Arg11v5, edx
			mov F1_Arg11v6, edx
			mov F1_Arg11v7, edx
			mov F1_Arg11v8, edx
			mov F1_Arg11v9, edx
			mov F1_Arg11v10, edx
			mov F1_Arg11v11, edx
			mov F1_Arg11v12, edx
			mov F1_Arg11v13, edx
			mov F1_Arg11v14, edx
			mov F1_Arg11v15, edx
			mov F1_Arg11v16, edx
			mov F1_Arg11v17, edx
			mov F1_Arg11v18, edx
			mov F1_Arg11v19, edx
			mov F1_Arg11v20, edx
			mov F1_Arg11v21, edx
			mov F1_Arg11v22, edx
			mov F1_Arg11v23, edx
			mov F1_Arg11v24, edx
			mov F1_Arg11v25, edx
			mov F1_Arg11v26, edx
			mov F1_Arg11v27, edx
			mov F1_Arg11v28, edx
			mov F1_Arg11v29, edx
			mov F1_Arg11v30, edx
			mov F1_Arg11v31, edx
			mov F1_Arg11v32, edx
			mov F1_Arg11v33, edx
			mov F1_Arg11v34, edx
			mov F1_Arg11v35, edx
			mov F1_Arg11v36, edx
			mov F1_Arg11v37, edx
			mov F1_Arg11v38, edx
			mov F1_Arg11v39, edx
			mov F1_Arg11v40, edx
			mov F1_Arg11v41, edx
			mov F1_Arg11v42, edx
			mov F1_Arg11v43, edx
			mov edx, dword ptr ss : [ebp - 0x6c]
			mov F1_Arg2v1, edx
			mov F1_Arg2v2, edx
			mov F1_Arg2v3, edx
			mov F1_Arg2v4, edx
			mov F1_Arg2v5, edx
			mov F1_Arg2v6, edx
			mov F1_Arg2v7, edx
			mov F1_Arg2v8, edx
			mov F1_Arg2v9, edx
			mov F1_Arg2v10, edx
			mov F1_Arg2v11, edx
			mov F1_Arg2v12, edx
			mov F1_Arg2v13, edx
			mov F1_Arg2v14, edx
			mov F1_Arg2v15, edx
			mov F1_Arg2v16, edx
			mov F1_Arg2v17, edx
			mov F1_Arg2v18, edx
			mov F1_Arg2v19, edx
			mov F1_Arg2v20, edx
			mov F1_Arg2v21, edx
			mov F1_Arg2v22, edx
			mov F1_Arg2v23, edx
			mov F1_Arg2v24, edx
			mov F1_Arg2v25, edx
			mov F1_Arg2v26, edx
			mov F1_Arg2v27, edx
			mov F1_Arg2v28, edx
			mov F1_Arg2v29, edx
			mov F1_Arg2v30, edx
			mov F1_Arg2v31, edx
			mov F1_Arg2v32, edx
			mov F1_Arg2v33, edx
			mov F1_Arg2v34, edx
			mov F1_Arg2v35, edx
			mov F1_Arg2v36, edx
			mov F1_Arg2v37, edx
			mov F1_Arg2v38, edx
			mov F1_Arg2v39, edx
			mov F1_Arg2v40, edx
			mov F1_Arg2v41, edx
			mov F1_Arg2v42, edx
			mov F1_Arg2v43, edx

			fldz
			fstp dword ptr ss : [esp]
			mov edx, dword ptr ss : [ebp - 0x70]
			mov F2_Arg5v1, edx
			mov F2_Arg5v2, edx
			mov F2_Arg5v3, edx
			mov F2_Arg5v4, edx
			mov F2_Arg5v5, edx
			mov F2_Arg5v6, edx
			mov F2_Arg5v7, edx
			mov F2_Arg5v8, edx
			mov F2_Arg5v9, edx
			mov F2_Arg5v10, edx
			mov F2_Arg5v11, edx
			mov F2_Arg5v12, edx
			mov F2_Arg5v13, edx
			mov F2_Arg5v14, edx
			mov F2_Arg5v15, edx
			mov F2_Arg5v16, edx
			mov F2_Arg5v17, edx
			mov F2_Arg5v18, edx
			mov F2_Arg5v19, edx
			mov F2_Arg5v20, edx
			mov F2_Arg5v21, edx
			mov F2_Arg5v22, edx
			mov F2_Arg5v23, edx
			mov F2_Arg5v24, edx
			mov F2_Arg5v25, edx
			mov F2_Arg5v26, edx
			mov F2_Arg5v27, edx
			mov F2_Arg5v28, edx
			mov F2_Arg5v29, edx
			mov F2_Arg5v30, edx
			mov F2_Arg5v31, edx
			mov F2_Arg5v32, edx
			mov F2_Arg5v33, edx
			mov F2_Arg5v34, edx
			mov F2_Arg5v35, edx
			mov F2_Arg5v36, edx
			mov F2_Arg5v37, edx
			mov F2_Arg5v38, edx
			mov F2_Arg5v39, edx
			mov F2_Arg5v40, edx
			mov F2_Arg5v41, edx
			mov F2_Arg5v42, edx
			mov F2_Arg5v43, edx
			mov edx, AddWingsEffect_Buff
	}
	// ----
	if (IsCustomItem(AddWingsEffect_Buff, true))
	{
		if (AddWingsEffect_Buff == ITEM2(0, 102))
		{
			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 9, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 10, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v2, F1_Arg2v2, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v3, F1_Arg2v3, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v4, F1_Arg2v4, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v5, F1_Arg2v5, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v6, F1_Arg2v6, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v7, F1_Arg2v7, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v8, F1_Arg2v8, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v9, F1_Arg2v9, Color, 12, 0.4, 0);
			pPlayDynamicEffect(32290, &F1_Arg11v10, F1_Arg2v10, Color, 12, 0.4, 0);		
		}
		else if (AddWingsEffect_Buff == ITEM2(2, 100))
		{
			Color[0] = 0.1;
			Color[1] = 0.2;
			Color[2] = 0.5;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 5, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 8, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 11, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 12, 0);
			
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v2, F1_Arg2v2, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v3, F1_Arg2v3, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v4, F1_Arg2v4, Color, 4, 0.5, 5);
			
			Color[0] = 0.1;
			Color[1] = 0.5;
			Color[2] = 0.2;			
			pPlayDynamicEffect(0x7e73, &F1_Arg11v5, F1_Arg2v5, Color, 0, 1, 1);	
		}
		else if (AddWingsEffect_Buff == ITEM2(5, 100))
		{
			Color[0] = 0.7;
			Color[1] = 0.3;
			Color[2] = 0.1;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 1, 0);	
			pPlayDynamicEffect(0x7e73, &F1_Arg11v2, F1_Arg2v2, Color, 0, 1, 1);	
		}

		else if (AddWingsEffect_Buff == ITEM2(5, 102))
		{
			Color[0] = 0.5;
			Color[1] = 0.3;
			Color[2] = 0.1;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 3, 0);

			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 8, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 9, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 10, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 11, 0);
			
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v3, F1_Arg2v3, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v4, F1_Arg2v4, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v5, F1_Arg2v5, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v6, F1_Arg2v6, Color, 4, 0.5, 5);
			
			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;			
			//pPlayDynamicEffect(0x7E2D, &F1_Arg11v2, F1_Arg2v2, Color, 4, 1.5, 5);	
			pPlayDynamicEffect(0x7E0E, &F1_Arg11v2, F1_Arg2v2, Color, 0, 1.2, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(1, 100))
		{
			Color[0] = 0.5;
			Color[1] = 0.3;
			Color[2] = 0.1;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 9, 0);			
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v2, F1_Arg2v2, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v3, F1_Arg2v3, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v4, F1_Arg2v4, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v5, F1_Arg2v5, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v6, F1_Arg2v6, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v7, F1_Arg2v7, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v8, F1_Arg2v8, Color, 4, 0.5, 5);
			pPlayDynamicEffect(0x7E8C, &F1_Arg11v9, F1_Arg2v9, Color, 4, 1, 5);		
		}
		else if (AddWingsEffect_Buff == ITEM2(0, 101))
		{
			Color[0] = 1.2;
			Color[1] = 0.3;
			Color[2] = 0.1;
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 9, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 10, 0);
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 11, 0);			
			pPlayDynamicEffect(0x7E83, &F1_Arg11v2, F1_Arg2v2, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v3, F1_Arg2v3, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v4, F1_Arg2v4, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v5, F1_Arg2v5, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v6, F1_Arg2v6, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v7, F1_Arg2v7, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v8, F1_Arg2v8, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v9, F1_Arg2v9, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v10, F1_Arg2v10, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v11, F1_Arg2v11, Color, 0, -1, 0);			
		}
		else if (AddWingsEffect_Buff == ITEM2(0, 100))
		{
			Color[0] = 0.2;
			Color[1] = 0.3;
			Color[2] = 1;
            if(rand() %8)
            {
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 9, 0);
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 1, 0);
			}
			pPlayDynamicEffect(0x7E22, &F1_Arg11v2, F1_Arg2v2, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v3, F1_Arg2v3, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v4, F1_Arg2v4, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v5, F1_Arg2v5, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v6, F1_Arg2v6, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v7, F1_Arg2v7, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v8, F1_Arg2v8, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v9, F1_Arg2v9, Color, 12, 0.5, 1);
			pPlayDynamicEffect(0x7E22, &F1_Arg11v10, F1_Arg2v10, Color, 12, 0.5, 1);
		}
	}
	if (IsCustomWings(AddWingsEffect_Buff, true))
	{
		if (AddWingsEffect_Buff == ITEM2(12, 180))
		{
			{
			Color[0] = ((float)(rand() % 100) / 100);
			Color[1] = ((float)(rand() % 100) / 100);
			Color[2] = ((float)(rand() % 100) / 100);
			}
			
			{
				Color[0] = 1.0;
				Color[1] = 0.6;
				Color[2] = 0.0;
			}
				// ----
				pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 47, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v1, 0.6, Color, F2_Arg5v1, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 24, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v2, 0.6, Color, F2_Arg5v2, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 31, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v3, 0.6, Color, F2_Arg5v3, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 40, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v4, 0.6, Color, F2_Arg5v4, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 8, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v5, 0.6, Color, F2_Arg5v5, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 17, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v6, 0.6, Color, F2_Arg5v6, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 46, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v7, 0.6, Color, F2_Arg5v7, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 23, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v8, 0.6, Color, F2_Arg5v8, 1.0, 0);
				// --
				Color[0] = 1.0;
				Color[1] = 0.4;
				Color[2] = 0.0;
				// --
				pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 35, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v9, 0.8, Color, F2_Arg5v9, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 39, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v10, 0.8, Color, F2_Arg5v10, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 44, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v11, 0.8, Color, F2_Arg5v11, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 45, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v12, 0.8, Color, F2_Arg5v12, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v13, 0.8, Color, F2_Arg5v13, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 16, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v14, 0.8, Color, F2_Arg5v14, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 21, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v15, 0.8, Color, F2_Arg5v15, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 22, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v16, 0.8, Color, F2_Arg5v16, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 61, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v17, 0.8, Color, F2_Arg5v17, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 60, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v18, 0.8, Color, F2_Arg5v18, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 59, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v19, 0.8, Color, F2_Arg5v19, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 62, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v20, 0.8, Color, F2_Arg5v20, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 55, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v21, 0.8, Color, F2_Arg5v21, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 52, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v22, 0.8, Color, F2_Arg5v22, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 53, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v23, 0.8, Color, F2_Arg5v23, 1.0, 0);
				// --
				pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 54, 0);
				pPlayStaticEffect(0x7D83, &F1_Arg11v24, 0.8, Color, F2_Arg5v24, 1.0, 0);
				//----
				Color[0] = 1.0;
				Color[1] = 0.3;
				Color[2] = 0.0;
				// ---- 
				pAllowStaticEffect(F1_Thisv25, &F1_Arg11v25, F1_Arg2v25, 4, 0);
				pPlayStaticEffect(32002, &F1_Arg11v25, 2, Color, F2_Arg5v25, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv26, &F1_Arg11v26, F1_Arg2v26, 42, 0);
				pPlayStaticEffect(32002, &F1_Arg11v26, 2, Color, F2_Arg5v26, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv27, &F1_Arg11v27, F1_Arg2v27, 27, 0);
				pPlayStaticEffect(32002, &F1_Arg11v27, 2, Color, F2_Arg5v27, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv28, &F1_Arg11v28, F1_Arg2v28, 21, 0);
				pPlayStaticEffect(32002, &F1_Arg11v28, 2, Color, F2_Arg5v28, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv29, &F1_Arg11v29, F1_Arg2v29, 53, 0);
				pPlayStaticEffect(32002, &F1_Arg11v29, 2, Color, F2_Arg5v29, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 59, 0);
				pPlayStaticEffect(32002, &F1_Arg11v28, 2, Color, F2_Arg5v28, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 5, 0);
				pPlayStaticEffect(32002, &F1_Arg11v31, 2, Color, F2_Arg5v31, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv32, &F1_Arg11v32, F1_Arg2v32, 28, 0);
				pPlayStaticEffect(32002, &F1_Arg11v32, 2, Color, F2_Arg5v32, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv33, &F1_Arg11v33, F1_Arg2v33, 10, 0);
				pPlayStaticEffect(32002, &F1_Arg11v33, 2, Color, F2_Arg5v33, 2.0, 0);
				// - 
				pAllowStaticEffect(F1_Thisv34, &F1_Arg11v34, F1_Arg2v34, 33, 0);
				pPlayStaticEffect(32002, &F1_Arg11v34, 2, Color, F2_Arg5v34, 2.0, 0);

			//
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v1, F1_Arg2v1, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v2, F1_Arg2v2, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v3, F1_Arg2v3, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v4, F1_Arg2v4, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v5, F1_Arg2v5, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v6, F1_Arg2v6, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v7, F1_Arg2v7, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v8, F1_Arg2v8, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v9, F1_Arg2v9, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v10, F1_Arg2v10, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v11, F1_Arg2v11, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v12, F1_Arg2v12, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v13, F1_Arg2v13, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v14, F1_Arg2v14, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v15, F1_Arg2v15, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v16, F1_Arg2v16, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v17, F1_Arg2v17, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v18, F1_Arg2v18, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v19, F1_Arg2v19, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v20, F1_Arg2v20, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v21, F1_Arg2v21, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v22, F1_Arg2v22, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v23, F1_Arg2v23, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v24, F1_Arg2v24, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v25, F1_Arg2v25, Color, 9, 0.5, 10);
			pPlayDynamicEffect(0x7d4d, &F1_Arg11v26, F1_Arg2v26, Color, 9, 0.5, 10);
		}

		else if (AddWingsEffect_Buff == ITEM2(12, 181))
		{
			Color[0] = 0.34;
			Color[1] = 0.25;
			Color[2] = 1.0;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 61, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0.5, Color, F2_Arg5v1, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 42, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0.5, Color, F2_Arg5v2, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 60, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.0, Color, F2_Arg5v3, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 41, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.0, Color, F2_Arg5v4, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 63, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.0, Color, F2_Arg5v5, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 44, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.0, Color, F2_Arg5v6, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 42, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.0, Color, F2_Arg5v7, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 59, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.4, Color, F2_Arg5v8, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 40, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1.4, Color, F2_Arg5v9, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 62, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 2.6, Color, F2_Arg5v10, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 43, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 2.6, Color, F2_Arg5v11, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 65, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 1.4, Color, F2_Arg5v12, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 46, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1.4, Color, F2_Arg5v13, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 58, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 2.0, Color, F2_Arg5v14, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 39, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 2.0, Color, F2_Arg5v15, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 64, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 2.0, Color, F2_Arg5v16, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 32, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 2.0, Color, F2_Arg5v17, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 2.0, Color, F2_Arg5v18, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19, 2.0, Color, F2_Arg5v19, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 25, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 2.0, Color, F2_Arg5v20, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 27, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21, 2.0, Color, F2_Arg5v21, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v22, 0.5, Color, F2_Arg5v22, 1.0, 0);
			//
			Color[0] = 0.34;
			Color[1] = 0.25;
			Color[2] = 0.55;
			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v23, 0, Color, F2_Arg5v23, 1.0, 0);
			pPlayDynamicEffect(0x7e63, &F1_Arg11v23, F1_Arg2v23, Color, 1, 0.3, 2);

		}
		// --
		else if (AddWingsEffect_Buff == ITEM2(12, 186))
		{
			Color[0] = 0.0;
			Color[1] = 0.5;
			Color[2] = 0.7;
			// --
			// ----
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 1, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v1, 0.5, Color, F2_Arg5v1, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v2, 0.5, Color, F2_Arg5v2, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v3, 0.5, Color, F2_Arg5v3, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v4, 0.5, Color, F2_Arg5v4, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v6, 0.5, Color, F2_Arg5v6, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v7, 0.5, Color, F2_Arg5v7, 1.0, 0);
			// --

			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 0.5, Color, F2_Arg5v11, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 0.5, Color, F2_Arg5v13, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv12, &F1_Arg11v12, F1_Arg2v12, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v12, 0.5, Color, F2_Arg5v12, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 14, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 0.5, Color, F2_Arg5v14, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 0.5, Color, F2_Arg5v15, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 0.5, Color, F2_Arg5v17, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 18, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 0.5, Color, F2_Arg5v18, 1.0, 0);

			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 20, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 0.5, Color, F2_Arg5v20, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 21, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21, 0.5, Color, F2_Arg5v21, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv23, &F1_Arg11v23, F1_Arg2v23, 23, 0);
			pPlayStaticEffect(32002, &F1_Arg11v23, 0.5, Color, F2_Arg5v23, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 24, 0);
			pPlayStaticEffect(32002, &F1_Arg11v24, 0.5, Color, F2_Arg5v24, 1.0, 0);

			// -
			pAllowStaticEffect(F1_Thisv26, &F1_Arg11v26, F1_Arg2v26, 26, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v26, 0.5, Color, F2_Arg5v26, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv27, &F1_Arg11v27, F1_Arg2v27, 27, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v27, 0.5, Color, F2_Arg5v27, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv29, &F1_Arg11v29, F1_Arg2v29, 29, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v29, 0.5, Color, F2_Arg5v29, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 30, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v30, 0.5, Color, F2_Arg5v30, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 31, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v31, 0.5, Color, F2_Arg5v31, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv33, &F1_Arg11v33, F1_Arg2v33, 33, 0);
			pPlayStaticEffect(0x7e7c, &F1_Arg11v33, 0.5, Color, F2_Arg5v33, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv34, &F1_Arg11v34, F1_Arg2v34, 34, 0);
			pPlayStaticEffect(32002, &F1_Arg11v34, 0.5, Color, F2_Arg5v34, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv36, &F1_Arg11v36, F1_Arg2v36, 36, 0);
			pPlayStaticEffect(32002, &F1_Arg11v36, 0.5, Color, F2_Arg5v36, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv37, &F1_Arg11v37, F1_Arg2v37, 37, 0);
			pPlayStaticEffect(32002, &F1_Arg11v37, 0.5, Color, F2_Arg5v37, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv38, &F1_Arg11v38, F1_Arg2v38, 38, 0);
			pPlayStaticEffect(32002, &F1_Arg11v38, 0.5, Color, F2_Arg5v38, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv40, &F1_Arg11v40, F1_Arg2v40, 40, 0);
			pPlayStaticEffect(32002, &F1_Arg11v40, 0.5, Color, F2_Arg5v40, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv41, &F1_Arg11v41, F1_Arg2v41, 41, 0);
			pPlayStaticEffect(32002, &F1_Arg11v41, 0.5, Color, F2_Arg5v41, 1.0, 0);
			// -
			pAllowStaticEffect(F1_Thisv43, &F1_Arg11v43, F1_Arg2v43, 43, 0);
			pPlayStaticEffect(32002, &F1_Arg11v43, 0.5, Color, F2_Arg5v43, 1.0, 0);
			//
			pPlayDynamicEffect(0x7e35, &F1_Arg11v1, F1_Arg2v1, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v2, F1_Arg2v2, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v3, F1_Arg2v3, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v4, F1_Arg2v4, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v5, F1_Arg2v5, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v6, F1_Arg2v6, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v7, F1_Arg2v7, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v8, F1_Arg2v8, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v9, F1_Arg2v9, Color, 0, 0.1, 0.4);

			pPlayDynamicEffect(0x7e35, &F1_Arg11v20, F1_Arg2v20, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v21, F1_Arg2v21, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v22, F1_Arg2v22, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v23, F1_Arg2v23, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v24, F1_Arg2v24, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v25, F1_Arg2v25, Color, 0, 0.1, 0.4);
			pPlayDynamicEffect(0x7e35, &F1_Arg11v26, F1_Arg2v26, Color, 0, 0.1, 0.4);
		}

		else if (AddWingsEffect_Buff == ITEM2(12, 188))
		{

			//pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 66, 0);
			//pPlayStaticEffect(0x7919, &F1_Arg11v31, 1.8, Color, F2_Arg5v31, 0, 0);
			//pPlayDynamicEffect(0x7919, &F1_Arg11v31, F1_Arg2v31, Color, 1, 2, 1);


			Color[0] = 2.0;
			Color[1] = 0.0;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 0, 0);
			pPlayStaticEffect(32002, &F1_Arg11v30, 3, Color, F2_Arg5v30, 2.0, 0);

			Color[0] = 1.0;
			Color[1] = 0.5;
			Color[2] = 0.5;
			pPlayDynamicEffect(0x7E89, &F1_Arg11v30, F1_Arg2v30, Color, 0, 1, 1);

			Color[0] = 1.5;
			Color[1] = 1.5;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 1, Color, F2_Arg5v1, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1, Color, F2_Arg5v3, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1, Color, F2_Arg5v4, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1, Color, F2_Arg5v5, 2.0, 0);


			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 14, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 1, Color, F2_Arg5v14, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 1, Color, F2_Arg5v15, 2.0, 0);

			// --
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19, 1, Color, F2_Arg5v19, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 1, Color, F2_Arg5v20, 2.0, 0);

			// --

			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 0.9, Color, F2_Arg5v17, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 16, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 0.9, Color, F2_Arg5v18, 1.0, 0);

			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;

			pPlayDynamicEffect(0x7e85, &F1_Arg11v5, F1_Arg2v5, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v4, F1_Arg2v4, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v3, F1_Arg2v3, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v1, F1_Arg2v1, Color, 0.5, 0.3, 1);

			pPlayDynamicEffect(0x7e85, &F1_Arg11v15, F1_Arg2v15, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v14, F1_Arg2v14, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v19, F1_Arg2v19, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v20, F1_Arg2v20, Color, 0.5, 0.5, 1);

			pPlayDynamicEffect(0x7e86, &F1_Arg11v17, F1_Arg2v17, Color, 0, 0.5, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v18, F1_Arg2v18, Color, 0, 0.5, 1);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 183))
		{

			//pAllowStaticEffect(F1_Thisv31, &F1_Arg11v31, F1_Arg2v31, 66, 0);
			//pPlayStaticEffect(0x7919, &F1_Arg11v31, 1.8, Color, F2_Arg5v31, 0, 0);
			//pPlayDynamicEffect(0x7919, &F1_Arg11v31, F1_Arg2v31, Color, 1, 2, 1);


			Color[0] = 2.0;
			Color[1] = 0.0;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 0, 0);
			pPlayStaticEffect(32002, &F1_Arg11v30, 3, Color, F2_Arg5v30, 2.0, 0);

			Color[0] = 1.0;
			Color[1] = 0.5;
			Color[2] = 0.5;
			pPlayDynamicEffect(0x7E89, &F1_Arg11v30, F1_Arg2v30, Color, 0, 1, 1);

			Color[0] = 1.5;
			Color[1] = 1.5;
			Color[2] = 0.0;
			// --

			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1, Color, F2_Arg5v4, 2.0, 0);
			// --
		


			// --

			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 0.9, Color, F2_Arg5v17, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 16, 0);
			pPlayStaticEffect(32002, &F1_Arg11v18, 0.9, Color, F2_Arg5v18, 1.0, 0);

			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;

			pPlayDynamicEffect(0x7e85, &F1_Arg11v5, F1_Arg2v5, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v4, F1_Arg2v4, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v3, F1_Arg2v3, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v1, F1_Arg2v1, Color, 0.5, 0.3, 1);

			pPlayDynamicEffect(0x7e85, &F1_Arg11v15, F1_Arg2v15, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v14, F1_Arg2v14, Color, 0.5, 0.5, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v19, F1_Arg2v19, Color, 0.5, 0.3, 1);
			pPlayDynamicEffect(0x7e87, &F1_Arg11v20, F1_Arg2v20, Color, 0.5, 0.5, 1);

			pPlayDynamicEffect(0x7e86, &F1_Arg11v17, F1_Arg2v17, Color, 0, 0.5, 1);
			pPlayDynamicEffect(0x7e86, &F1_Arg11v18, F1_Arg2v18, Color, 0, 0.5, 1);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 189))
		{
			// --
			Color[0] = 1.5;
			Color[1] = 1.5;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 2, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0, Color, F2_Arg5v1, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 0, Color, F2_Arg5v3, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 0, Color, F2_Arg5v4, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 0, Color, F2_Arg5v5, 2.0, 0);
			// --
			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;

			pPlayDynamicEffect(0x7E83, &F1_Arg11v5, F1_Arg2v5, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v4, F1_Arg2v4, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v3, F1_Arg2v3, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v1, F1_Arg2v1, Color, 0, -1, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(12, 198))
		{
			// --
			Color[0] = 1.5;
			Color[1] = 1.5;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 2, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0, Color, F2_Arg5v1, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 0, Color, F2_Arg5v3, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 0, Color, F2_Arg5v4, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 0, Color, F2_Arg5v5, 2.0, 0);
			// --
			Color[0] = 255;
			Color[1] = 255;
			Color[2] = 255;

			pPlayDynamicEffect(0x7E83, &F1_Arg11v5, F1_Arg2v5, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v4, F1_Arg2v4, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v3, F1_Arg2v3, Color, 0, -1, 0);
			pPlayDynamicEffect(0x7E83, &F1_Arg11v1, F1_Arg2v1, Color, 0, -1, 0);

		}
		else if (AddWingsEffect_Buff == ITEM2(12, 190))
		{
			Color[0] = 1.5;
			Color[1] = 0.0;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 1, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 2, Color, F2_Arg5v1, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 2, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2, Color, F2_Arg5v2, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2, Color, F2_Arg5v3, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 4, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2, Color, F2_Arg5v4, 1.0, 0);
			// --

			pPlayDynamicEffect(0x7e73, &F1_Arg11v1, F1_Arg2v1, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v2, F1_Arg2v2, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v3, F1_Arg2v3, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v4, F1_Arg2v4, Color, 0, 1, 1);

			// --
			Color[0] = 0.0;
			Color[1] = 0.5;
			Color[2] = 1.5;
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 2, Color, F2_Arg5v6, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 2, Color, F2_Arg5v7, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 2, Color, F2_Arg5v8, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 2, Color, F2_Arg5v5, 1.0, 0);
			// --
			pPlayDynamicEffect(0x7e73, &F1_Arg11v6, F1_Arg2v6, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v7, F1_Arg2v7, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v8, F1_Arg2v8, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v5, F1_Arg2v5, Color, 0, 1, 1);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 185))
		{
			Color[0] = 2.0;
			Color[1] = 0.0;
			Color[2] = 0.0;
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pPlayStaticEffect(32131, &F1_Arg11v6, 0.5, Color, F2_Arg5v6, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pPlayStaticEffect(32131, &F1_Arg11v7, 0.5, Color, F2_Arg5v7, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pPlayStaticEffect(32131, &F1_Arg11v5, 0.5, Color, F2_Arg5v5, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 28, 0);
			pPlayStaticEffect(32131, &F1_Arg11v4, 0.5, Color, F2_Arg5v4, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 36, 0);
			pPlayStaticEffect(32131, &F1_Arg11v15, 0.5, Color, F2_Arg5v15, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 16, 0);
			pPlayStaticEffect(32131, &F1_Arg11v16, 0.5, Color, F2_Arg5v16, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 17, 0);
			pPlayStaticEffect(32131, &F1_Arg11v17, 0.5, Color, F2_Arg5v17, 2.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv18, &F1_Arg11v18, F1_Arg2v18, 18, 0);
			pPlayStaticEffect(32131, &F1_Arg11v18, 0.5, Color, F2_Arg5v18, 2.0, 0);
			//
			Color[0] = 1.5;
			Color[1] = 1.0;
			Color[2] = 0.0;
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1, Color, F2_Arg5v8, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv9, &F1_Arg11v9, F1_Arg2v9, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v9, 1, Color, F2_Arg5v9, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 1, Color, F2_Arg5v10, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv11, &F1_Arg11v11, F1_Arg2v11, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v11, 1, Color, F2_Arg5v11, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1, Color, F2_Arg5v3, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv13, &F1_Arg11v13, F1_Arg2v13, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v13, 1, Color, F2_Arg5v13, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 14, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 1, Color, F2_Arg5v14, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv19, &F1_Arg11v19, F1_Arg2v19, 19, 0);
			pPlayStaticEffect(32002, &F1_Arg11v19, 1, Color, F2_Arg5v19, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 20, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 1, Color, F2_Arg5v20, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv21, &F1_Arg11v21, F1_Arg2v21, 21, 0);
			pPlayStaticEffect(32002, &F1_Arg11v21, 1, Color, F2_Arg5v21, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv22, &F1_Arg11v22, F1_Arg2v22, 22, 0);
			pPlayStaticEffect(32002, &F1_Arg11v22, 1, Color, F2_Arg5v22, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv24, &F1_Arg11v24, F1_Arg2v24, 24, 0);
			pPlayStaticEffect(32002, &F1_Arg11v24, 1, Color, F2_Arg5v24, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv30, &F1_Arg11v30, F1_Arg2v30, 30, 0);
			pPlayStaticEffect(32002, &F1_Arg11v30, 1, Color, F2_Arg5v30, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv32, &F1_Arg11v32, F1_Arg2v32, 32, 0);
			pPlayStaticEffect(32002, &F1_Arg11v32, 1, Color, F2_Arg5v32, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv38, &F1_Arg11v38, F1_Arg2v38, 38, 0);
			pPlayStaticEffect(32002, &F1_Arg11v38, 1, Color, F2_Arg5v38, 0, 0);
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 184))
		{
			Color[0] = 1.5;
			Color[1] = 1.0;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 16, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 0.8, Color, F2_Arg5v16, 2.0, 0);
			//
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 0.8, Color, F2_Arg5v8, 0, 0);
			// --
			Color[0] = 1.0;
			Color[1] = 0.0;
			Color[2] = 0.0;
			// --
			pAllowStaticEffect(F1_Thisv17, &F1_Arg11v17, F1_Arg2v17, 19, 0);
			pPlayStaticEffect(32002, &F1_Arg11v17, 1, Color, F2_Arg5v17, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv20, &F1_Arg11v20, F1_Arg2v20, 23, 0);
			pPlayStaticEffect(32002, &F1_Arg11v20, 1, Color, F2_Arg5v20, 0, 0);
			// --
		}
		//
		else if (AddWingsEffect_Buff == ITEM2(12, 197))
		{
			Color[0] = 1.0;
			Color[1] = 0.5;
			Color[2] = 0.5;
			// --
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 1.3, Color, F2_Arg5v1, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 1.3, Color, F2_Arg5v2, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 13, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 1.3, Color, F2_Arg5v3, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 14, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 1.3, Color, F2_Arg5v4, 1.0, 0);
			// --


			pPlayDynamicEffect(0x7d69, &F1_Arg11v1, F1_Arg2v1, Color, 0, 0.3, 0);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v2, F1_Arg2v2, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v3, F1_Arg2v3, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v4, F1_Arg2v4, Color, 0, 1, 1);
			// --
			Color[0] = 0.0;
			Color[1] = 0.5;
			Color[2] = 1.5;
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.3, Color, F2_Arg5v6, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 1.3, Color, F2_Arg5v7, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 8, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 1.3, Color, F2_Arg5v8, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 5, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.3, Color, F2_Arg5v5, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv10, &F1_Arg11v10, F1_Arg2v10, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v10, 1.3, Color, F2_Arg5v10, 1.0, 0);
			// --
			pPlayDynamicEffect(0x7e73, &F1_Arg11v6, F1_Arg2v6, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v7, F1_Arg2v7, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v8, F1_Arg2v8, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v5, F1_Arg2v5, Color, 0, 1, 1);


			Color[0] = 0.0;
			Color[1] = 1.5;
			Color[2] = 0.5;

			pAllowStaticEffect(F1_Thisv14, &F1_Arg11v14, F1_Arg2v14, 19, 0);
			pPlayStaticEffect(32002, &F1_Arg11v14, 1.3, Color, F2_Arg5v14, 2.0, 0);
			pAllowStaticEffect(F1_Thisv15, &F1_Arg11v15, F1_Arg2v15, 20, 0);
			pPlayStaticEffect(32002, &F1_Arg11v15, 1.3, Color, F2_Arg5v15, 2.0, 0);
			pAllowStaticEffect(F1_Thisv16, &F1_Arg11v16, F1_Arg2v16, 21, 0);
			pPlayStaticEffect(32002, &F1_Arg11v16, 1.3, Color, F2_Arg5v16, 2.0, 0);


			pPlayDynamicEffect(0x7e73, &F1_Arg11v14, F1_Arg2v14, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v15, F1_Arg2v15, Color, 0, 1, 1);
			pPlayDynamicEffect(0x7e73, &F1_Arg11v16, F1_Arg2v16, Color, 0, 1, 1);
		}

		else if (AddWingsEffect_Buff == ITEM2(12, 202))
		{
			Color[0] = 2.0;
			Color[1] = 0.5;
			Color[2] = 0.5;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 4, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 2.5, Color, F2_Arg5v1, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2.5, Color, F2_Arg5v2, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2.5, Color, F2_Arg5v3, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2.5, Color, F2_Arg5v4, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 17, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 2.5, Color, F2_Arg5v5, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 18, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 2.5, Color, F2_Arg5v6, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 2, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 0, Color, F2_Arg5v7, 0, 0);
			pPlayDynamicEffect(0x7d65, &F1_Arg11v7, F1_Arg2v7, Color, 11, 0.1, 12);
		}
		// --
		else if (AddWingsEffect_Buff == ITEM2(12, 203))
		{
			Color[0] = 1.0;
			Color[1] = 0.0;
			Color[2] = 0.5;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 3, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 2.5, Color, F2_Arg5v1, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 4, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 2.5, Color, F2_Arg5v2, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 6, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 2.5, Color, F2_Arg5v3, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 7, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 2.5, Color, F2_Arg5v4, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv7, &F1_Arg11v7, F1_Arg2v7, 10, 0);
			pPlayStaticEffect(32002, &F1_Arg11v7, 2.5, Color, F2_Arg5v7, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv8, &F1_Arg11v8, F1_Arg2v8, 11, 0);
			pPlayStaticEffect(32002, &F1_Arg11v8, 2.5, Color, F2_Arg5v8, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 19, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 1.5, Color, F2_Arg5v5, 0, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 20, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 1.5, Color, F2_Arg5v6, 0, 0);
			// --
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 205))
		{
			Color[0] = 0.0;
			Color[1] = 0.0;
			Color[2] = 0.0;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0, Color, F2_Arg5v1, 0, 0);
			pPlayDynamicEffect(0x7d69, &F1_Arg11v1, F1_Arg2v1, Color, 11, 1, 12);
			// --
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 196))
		{
			Color[0] = 0.0;
			Color[1] = 0.0;
			Color[2] = 2.0;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 9, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0, Color, F2_Arg5v1, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv2, &F1_Arg11v2, F1_Arg2v2, 12, 0);
			pPlayStaticEffect(32002, &F1_Arg11v2, 0, Color, F2_Arg5v2, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv3, &F1_Arg11v3, F1_Arg2v3, 15, 0);
			pPlayStaticEffect(32002, &F1_Arg11v3, 0, Color, F2_Arg5v3, 1.0, 0);
			// --
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v1, F1_Arg2v1, Color, 0, 0.8, 1);
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v2, F1_Arg2v2, Color, 0, 0.8, 1);
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v3, F1_Arg2v3, Color, 0, 0.8, 1);
			// --
			pAllowStaticEffect(F1_Thisv4, &F1_Arg11v4, F1_Arg2v4, 26, 0);
			pPlayStaticEffect(32002, &F1_Arg11v4, 0, Color, F2_Arg5v4, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv5, &F1_Arg11v5, F1_Arg2v5, 29, 0);
			pPlayStaticEffect(32002, &F1_Arg11v5, 0, Color, F2_Arg5v5, 1.0, 0);
			// --
			pAllowStaticEffect(F1_Thisv6, &F1_Arg11v6, F1_Arg2v6, 32, 0);
			pPlayStaticEffect(32002, &F1_Arg11v6, 0, Color, F2_Arg5v6, 1.0, 0);
			// --
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v4, F1_Arg2v4, Color, 0, 0.8, 1);
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v5, F1_Arg2v5, Color, 0, 0.8, 1);
			pPlayDynamicEffect(0x7E1C, &F1_Arg11v6, F1_Arg2v6, Color, 0, 0.8, 1);
			// --
		}
		else if (AddWingsEffect_Buff == ITEM2(12, 187))
		{
			Color[0] = 1.0;
			Color[1] = 0.5;
			Color[2] = 0.0;
			pAllowStaticEffect(F1_Thisv1, &F1_Arg11v1, F1_Arg2v1, 0, 0);
			pPlayStaticEffect(32002, &F1_Arg11v1, 0, Color, F2_Arg5v1, 0, 0);
			pPlayDynamicEffect(0x7d65, &F1_Arg11v1, F1_Arg2v1, Color, 11, 0.5, 12);
			// --
		}
		

		_asm
		{
			mov AddWingsEffect_Buff, 0x0056CA63
				jmp AddWingsEffect_Buff
		}
	}
	// ----
	if (AddWingsEffect_Buff > 0x0A9D)
	{
		_asm
		{
			mov AddWingsEffect_Buff, 0x005667BB
				jmp AddWingsEffect_Buff
		}
	}
	// ----
	_asm
	{
		mov AddWingsEffect_Buff, 0x00566707
			jmp AddWingsEffect_Buff
	}
}

void WingEffect()
{
	SetRange((LPVOID)0x005666F7, 10, ASM::NOP);
	SetOp((LPVOID)0x005666F7, AddWingsEffect, ASM::JMP);
}