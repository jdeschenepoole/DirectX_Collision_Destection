#ifndef _SMaterialInfo_HG_
#define _SMaterialInfo_HG_

#include <d3d10.h>
#include <d3dx10.h>

struct MaterialInfo
{
    D3DXVECTOR4 diffuse;		// float4 in shader
	D3DXVECTOR4 ambient;
    D3DXVECTOR4 spec;
};

#endif