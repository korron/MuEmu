//---------------------------------------------------------------------------
#include "stdafx.h"
#include "Util.h"
#include "NewFont.h"
//---------------------------------------------------------------------------
Font gFont;
//---------------------------------------------------------------------------
char MyFontFaceName[100];
char sValue[99];
//--
int Bold = GetPrivateProfileIntA("Font", "Main_Font_Bold", 0, ".\\Settings.ini");
int Height = GetPrivateProfileIntA("Font", "Main_Font_Height", 13, ".\\Settings.ini");
int Italic = GetPrivateProfileIntA("Font", "Main_Font_Italic", 0, ".\\Settings.ini");
int Unicode = GetPrivateProfileIntA("Font", "Main_Font_Unicode", 1, ".\\Settings.ini");
//--
int Width = GetPrivateProfileIntA("Font", "Main_Font_Width", 0, ".\\Settings.ini");
int UnderLine = GetPrivateProfileIntA("Font", "Main_Font_Underline", 0, ".\\Settings.ini");
int Quality = GetPrivateProfileIntA("Font", "Main_Font_Quality", 3, ".\\Settings.ini");
int StrikeOut = GetPrivateProfileIntA("Font", "Main_Font_StrikeOut", 0, ".\\Settings.ini");
//---------------------------------------------------------------------------
void Font::Load()
{
    GetPrivateProfileStringA("Font", "Main_Font_Name", "Tahoma", MyFontFaceName, 100, ".\\Settings.ini");
    //--
    SetCompleteHook(0xE8, Offset_CreateFontA1, &Font::LoadNewFont);
    SetCompleteHook(0xE8, Offset_CreateFontA2, &Font::LoadNewFont);
    SetCompleteHook(0xE8, Offset_CreateFontA3, &Font::LoadNewFont);
    SetCompleteHook(0xE8, Offset_CreateFontA4, &Font::LoadNewFont);
    SetCompleteHook(0xE8, Offset_CreateFontA5, &Font::LoadNewFont);
    //--
    SetByte((Offset_CreateFontA1 + 5), 0x90);
    SetByte((Offset_CreateFontA2 + 5), 0x90);
    SetByte((Offset_CreateFontA3 + 5), 0x90);
    SetByte((Offset_CreateFontA4 + 5), 0x90);
    SetByte((Offset_CreateFontA5 + 5), 0x90);
}
//---------------------------------------------------------------------------
HFONT Font::LoadNewFont()
{
    HFONT MyFont;
    //--
    if (Bold == 0)
    {
        if (Unicode == 1)
        {
            MyFont = CreateFontA(Height, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x01, 0, 0, Quality, 0, MyFontFaceName);
        }
        else
        {
            MyFont = CreateFontA(Height, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x0, 0, 0, Quality, 0, MyFontFaceName);
        }
    }
    else
    {
        if (Unicode == 1)
        {
            MyFont = CreateFontA(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x01, 0, 0, Quality, 0, MyFontFaceName);
        }
        else
        {
            MyFont = CreateFontA(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x0, 0, 0, Quality, 0, MyFontFaceName);
        }
    }


    return MyFont;
}
//---------------------------------------------------------------------------