#include "global.h"

bool LoadTexture( std::wstring textureFileName, ID3D10ShaderResourceView* pTexture, std::wstring &error )
{
	error = L"OK";

	HRESULT hr = D3DX10CreateShaderResourceViewFromFile( g_pd3dDevice, 
	                                                     textureFileName.c_str(),
														 NULL,			// Returns image information about texture
														 NULL,			// Used to load texture in other thread
														 &g_pTexture01, 
														 NULL );		// Used when loading on another thread (callback, etc.)
    if( FAILED( hr ) )
	{
		error = L"ERORR: Unable to load texture.";
		return false;
	}

	return true;
}