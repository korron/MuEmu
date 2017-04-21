#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include "gl/gl.h"
#include "cg/cg.h"
#include "cg/cgGL.h"
#include "Glow.h"
#include "Graphics.h"
#include "glext.h"

bool g_bInitialised = false;
bool g_bEnabled = GetPrivateProfileIntA("Setting", "TronGlow", 0, ".\\Settings.ini");

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;

CGcontext g_cgContext;
CGprofile g_cgVertProfile;
CGprofile g_cgFragProfile;

CGprogram g_cgVP_GlowDarken;
CGprogram g_cgFP_GlowDarken;

CGprogram g_cgVP_GlowBlur;
CGprogram g_cgFP_GlowBlur;

CGprogram g_cgVP_GlowCombine;
CGprogram g_cgFP_GlowCombine;

CGparameter g_cgpVP0_ModelViewMatrix;
CGparameter g_cgpVP1_ModelViewMatrix;
CGparameter g_cgpVP1_XOffset;
CGparameter g_cgpVP1_YOffset;
CGparameter g_cgpVP2_ModelViewMatrix;

unsigned int g_uiSceneTex;
unsigned int g_uiBlurTex;
int	cg_blur_steps = 0;

bool LoadProgram(CGprogram* pDest, CGprofile profile, const char* szFile)
{
     char file[512];
     sprintf(file, "%s", szFile);

     *pDest = cgCreateProgramFromFile(g_cgContext, CG_SOURCE, file, profile, "main", 0);
     if (!(*pDest)) 
	 {
          MessageBox(NULL, cgGetErrorString(cgGetError()), NULL, NULL);
          return false;
     }
     
     cgGLLoadProgram(*pDest);
     return true;
}

void InitScreenGlow(void)
{
     cg_blur_steps = 4;

	 // OPENGL EXTENSION LOADING
     glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");

	 // TEXTURE CREATION
     unsigned char* pBlankTex = new unsigned char[pWinWidth*pWinHeight*3];
     memset(pBlankTex, 0, pWinWidth*pWinHeight*3);

     glGenTextures(1, &g_uiSceneTex);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiSceneTex);
     glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB8, pWinWidth, pWinHeight, 0, GL_RGB8, GL_UNSIGNED_BYTE, pBlankTex);

     glGenTextures(1, &g_uiBlurTex);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiBlurTex);
     glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB8, pWinWidth/2, pWinHeight/2, 0, GL_RGB8, GL_UNSIGNED_BYTE, pBlankTex);

     delete[] pBlankTex;
     g_bInitialised = true;

	 // CG INITIALISATION
     g_cgContext = cgCreateContext();
     if (!g_cgContext) 
	 {
          MessageBox(NULL, "Couldn't make Cg context", NULL, NULL);
          return;
     }

	 // VERTEX PROFILE
     g_cgVertProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
     if (g_cgVertProfile == CG_PROFILE_UNKNOWN) {
          MessageBox(NULL, "Couldn't fetch valid VP profile", NULL, NULL);
          return;
     }

     cgGLSetOptimalOptions(g_cgVertProfile);

	 // VP LOADING
     if (!LoadProgram(&g_cgVP_GlowDarken, g_cgVertProfile, "Data/Custom/Effects/glow_darken_vp.cg"))
          return;

     if (!LoadProgram(&g_cgVP_GlowBlur, g_cgVertProfile, "Data/Custom/Effects/glow_blur_vp.cg"))
          return;

     if (!LoadProgram(&g_cgVP_GlowCombine, g_cgVertProfile, "Data/Custom/Effects/glow_combine_vp.cg"))
          return;

	 // VP PARAM GRABBING
     g_cgpVP0_ModelViewMatrix = cgGetNamedParameter(g_cgVP_GlowDarken, "ModelViewProj");

     g_cgpVP1_ModelViewMatrix = cgGetNamedParameter(g_cgVP_GlowBlur, "ModelViewProj");
     g_cgpVP1_XOffset = cgGetNamedParameter(g_cgVP_GlowBlur, "XOffset");
     g_cgpVP1_YOffset = cgGetNamedParameter(g_cgVP_GlowBlur, "YOffset");

     g_cgpVP2_ModelViewMatrix = cgGetNamedParameter(g_cgVP_GlowCombine, "ModelViewProj");

	 // FRAGMENT PROFILE
     g_cgFragProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
     if (g_cgFragProfile == CG_PROFILE_UNKNOWN) 
	 {
          MessageBox(NULL, "Couldn't fetch valid FP profile", NULL, NULL);
          return;
     }

     cgGLSetOptimalOptions(g_cgFragProfile);

	 // FP LOADING
     if (!LoadProgram(&g_cgFP_GlowDarken, g_cgFragProfile, "Data/Custom/Effects/glow_darken_fp.cg"))
          return;

     if (!LoadProgram(&g_cgFP_GlowBlur, g_cgFragProfile, "Data/Custom/Effects/glow_blur_fp.cg"))
          return;

     if (!LoadProgram(&g_cgFP_GlowCombine, g_cgFragProfile, "Data/Custom/Effects/glow_combine_fp.cg"))
          return;

	 printf("InitScreenGlow() Success.\n");
}

void DrawQuad(int width, int height)
{
     glBegin(GL_QUADS);
		 glTexCoord2f(0,0);
		 glVertex3f(0, 1, -1);
		 glTexCoord2f(0,height);
		 glVertex3f(0, 0, -1);
		 glTexCoord2f(width,height);
		 glVertex3f(1, 0, -1);
		 glTexCoord2f(width,0);
		 glVertex3f(1, 1, -1);
     glEnd();
}

void DoBlur(unsigned int uiSrcTex, unsigned int uiTargetTex, int srcTexWidth, int srcTexHeight, int destTexWidth, int destTexHeight, float xofs, float yofs)
{
     cgGLBindProgram(g_cgVP_GlowBlur);
     cgGLBindProgram(g_cgFP_GlowBlur);

     glActiveTextureARB(GL_TEXTURE0_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

     glActiveTextureARB(GL_TEXTURE1_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

     glActiveTextureARB(GL_TEXTURE2_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

     glActiveTextureARB(GL_TEXTURE3_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiSrcTex);

     cgGLSetParameter1f(g_cgpVP1_XOffset, xofs);
     cgGLSetParameter1f(g_cgpVP1_YOffset, yofs);

     glViewport(0, 0, destTexWidth, destTexHeight);

     DrawQuad(srcTexWidth, srcTexHeight);
     
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, uiTargetTex);
     glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, destTexWidth, destTexHeight, 0);
}

void RenderScreenGlow(void)
{
	 if (!g_bEnabled)
		 return;

     if (!g_bInitialised)
          InitScreenGlow();

     if (cg_blur_steps == 0)
          return;

	 // STEP 1: Grab the screen and put it into a texture
     glActiveTextureARB(GL_TEXTURE0_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);

     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiSceneTex);
     glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, pWinWidth, pWinHeight, 0);

	 // STEP 2: Set up an orthogonal projection
     glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
     glLoadIdentity();
     
     glMatrixMode(GL_PROJECTION);
     glPushMatrix();
     glLoadIdentity();
     glOrtho(0, 1, 1, 0, 0.1, 100);
     
     glColor3f(1,1,1);

	 // STEP 3: Initialize Cg programs and parameters for darkening mid to dark areas of the scene
     cgGLEnableProfile(g_cgVertProfile);
     cgGLEnableProfile(g_cgFragProfile);

     cgGLBindProgram(g_cgVP_GlowDarken);
     cgGLBindProgram(g_cgFP_GlowDarken);

     cgGLSetStateMatrixParameter(g_cgpVP0_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	 // STEP 4: Render the current scene texture to a new, lower-res texture, darkening non-bright areas of the scene
     glViewport(0, 0, pWinWidth/4, pWinHeight/4); //There was by default division by 2, but it won't work correctly, so 4 is right perfectly

     glActiveTextureARB(GL_TEXTURE0_ARB);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiSceneTex);

     DrawQuad(pWinWidth, pWinHeight);

     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiBlurTex);
     glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGB, 0, 0, pWinWidth/4, pWinHeight/4, 0); //There was by default division by 2, but it won't work correctly, so 4 is right perfectly

	 // STEP 5: Initialise Cg programs and parameters for blurring
     cgGLBindProgram(g_cgVP_GlowBlur);
     cgGLBindProgram(g_cgFP_GlowBlur);

     cgGLSetStateMatrixParameter(g_cgpVP1_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

	 // STEP 6: Apply blur
     int iNumBlurSteps = cg_blur_steps;
     for (int i = 0; i < iNumBlurSteps; i++) 
	 {
          DoBlur(g_uiBlurTex, g_uiBlurTex, pWinWidth/2, pWinHeight/2, pWinWidth/2, pWinHeight/2, 1, 0);     
          DoBlur(g_uiBlurTex, g_uiBlurTex, pWinWidth/2, pWinHeight/2, pWinWidth/2, pWinHeight/2, 0, 1);
     }

	 // STEP 7: Set up Cg for combining blurred glow with original scene
     cgGLBindProgram(g_cgVP_GlowCombine);
     cgGLBindProgram(g_cgFP_GlowCombine);
     
     cgGLSetStateMatrixParameter(g_cgpVP2_ModelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

     glActiveTextureARB(GL_TEXTURE0_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiSceneTex);

     glActiveTextureARB(GL_TEXTURE1_ARB);
     glEnable(GL_TEXTURE_RECTANGLE_NV);
     glBindTexture(GL_TEXTURE_RECTANGLE_NV, g_uiBlurTex);

	 // STEP 8: Do the combination, rendering to the screen without grabbing it to a texture
     glViewport(0, 0, pWinWidth, pWinHeight);
     DrawQuad(pWinWidth/4, pWinHeight/4); //There was by default division by 2, but it won't work correctly, so 4 is right perfectly

	 // STEP 9: Restore the original projection and modelview matrices and disable rectangular textures on all units
     glMatrixMode(GL_PROJECTION);
     glPopMatrix();

     glMatrixMode(GL_MODELVIEW);
     glPopMatrix();

     cgGLDisableProfile(g_cgVertProfile);
     cgGLDisableProfile(g_cgFragProfile);

     glActiveTextureARB(GL_TEXTURE0_ARB);
     glDisable(GL_TEXTURE_RECTANGLE_NV);
     
     glActiveTextureARB(GL_TEXTURE1_ARB);
     glDisable(GL_TEXTURE_RECTANGLE_NV);

     glActiveTextureARB(GL_TEXTURE2_ARB);
     glDisable(GL_TEXTURE_RECTANGLE_NV);

     glActiveTextureARB(GL_TEXTURE3_ARB);
     glDisable(GL_TEXTURE_RECTANGLE_NV);

     glActiveTextureARB(GL_TEXTURE0_ARB);
}