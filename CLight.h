#ifndef _CLight_HG_
#define _CLight_HG_

#include <d3d10.h>
#include <d3dx10.h>
#include "SMaterial.h"

class CLight
{
public:
	CLight();
	CLight(float att, D3DXVECTOR4 dir, D3DXVECTOR4 pos, D3DXVECTOR4 spot);
	~CLight();
	void ChangeType(int type);
	void ChangeType(int type, float x, float y, float z, float w);
	int GetType();
	void SetSpecular(float spec);
	void SetAmbient(float amb);
	void SetDiffuse(float diffuse);
	void SetMaterial(float spec, float amb, float diffuse);
	
	void SetAtten(float att);

	//Sets types of Light
	void SetPoint(float x, float y, float z, float w);
	void SetDirectional(float x, float y, float z, float w);
	void SetSpot(float x, float y, float z, float w);

protected:
	MaterialInfo material;
	D3DXVECTOR4 pos;
	D3DXVECTOR4 dir;
	D3DXVECTOR4 attenuation;
	D3DXVECTOR4 spotPowerRange;
	int lightType;

};

#endif