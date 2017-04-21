#include "stdafx.h"
#include "Fog.h"
#include "ReadScript.h"
// ----------------------------------------------------------------------------------------------

Fog	gFog;

// ----------------------------------------------------------------------------------------------

Fog::Fog()
{
	//this->Init();
	for(int i=0;i<255;i++)
	{
		gColor[i].red = 0.0;
		gColor[i].green = 0.0;
		gColor[i].blue = 0.0;
	}
}
// ----------------------------------------------------------------------------------------------

Fog::~Fog()
{
	// ----
}
// ----------------------------------------------------------------------------------------------

void Fog::Init()
{
	for(int i=0;i<255;i++)
	{
		gColor[i].red = 0.0;
		gColor[i].green = 0.0;
		gColor[i].blue = 0.0;
	}
}

void Fog::Load()
{
	SMDFile = fopen("Data\\Custom\\Fog.cfg", "r");

	this->Init();
	int Token;
	int type = -1;
	int Map;
	int Red;
	int Green;
	int Blue;

	this->m_LoadedCount = 0;

	while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			if ( type < 0 || type > 4 )
			{
				break;
			}

		    Token = GetToken();

			if ( strcmp("end", TokenString ) == 0)
			{
				break;
			}

			Map		= TokenNumber;
			Token	= GetToken();
			Red		= TokenNumber;
			Token	= GetToken();
			Green	= TokenNumber;
			Token	= GetToken();
			Blue	= TokenNumber;

			this->gColor[Map].red = (float)Red;
			this->gColor[Map].green = (float)Green;
			this->gColor[Map].blue = (float)Blue;
			// ----

			this->m_LoadedCount++;
		}
    }

	fclose(SMDFile);

}

float *Fog::toRGB(float *rgba)
{
	rgba[0] /= 255.0;
	rgba[1] /= 255.0;
	rgba[2] /= 255.0;

	return rgba;
}