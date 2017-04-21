#pragma once
// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------
struct RGBCOLOROBJ
{
	float red;
	float green;
	float blue;
};

// ----------------------------------------------------------------------------------------------

class Fog
{
public:
				Fog();
				~Fog();
	// ----
	void		Init();
	void		ReadList(char * File);
	void		Load();
	float		*toRGB(float *rgba);
	RGBCOLOROBJ	gColor[255];
	bool EnableFog;
	int	m_LoadedCount;
	// ----
}; extern Fog gFog;
//extern bool EnableFog;
// ----------------------------------------------------------------------------------------------