#include "CLight.h"

CLight::CLight()
{

}

CLight::CLight(float att, D3DXVECTOR4 dir, D3DXVECTOR4 pos, D3DXVECTOR4 spot)
{
	SetAtten(att);
	SetDirectional(dir.x, dir.y, dir.z, dir.w);
	SetPoint(pos.x, pos.y, pos.z, pos.w);
	SetSpot(spot.x, spot.y, spot.z, spot.w);
	ChangeType(0);
}

CLight::~CLight()
{

}

/*   LightTypes:
		0 - directional (parallel)
		1 - point
		else - spot
*/
void CLight::ChangeType(int type)
{
	lightType = type;
}

void CLight::ChangeType(int type, float x, float y, float z, float w)
{
	lightType = type;
	switch (type)
	{
		case '0':
			SetDirectional(x,y,z,w);
			break;
		case '1':
			SetPoint(x,y,z,w);
			break;
		case '2':
			SetSpot(x,y,z,w);
			break;
	}
}

int CLight::GetType()
{
	return lightType;
}

void CLight::SetSpecular(float specular)
{
	material.spec = D3DXVECTOR4( specular, specular, specular, 1.0f);
}

void CLight::SetAtten(float atten)
{
	attenuation = D3DXVECTOR4( atten, atten, atten, 1.0f );
}

void CLight::SetAmbient(float amb)
{
	material.ambient = D3DXVECTOR4( amb, amb, amb, 1.0f);
}

void CLight::SetDiffuse(float diffuse)
{
	material.diffuse = D3DXVECTOR4( diffuse, diffuse, diffuse, 1.0f);
}

void CLight::SetDirectional(float x, float y, float z, float w)
{
	dir.x = x;
	dir.y = y;
	dir.z = z;
	dir.w = w;
}

void CLight::SetPoint(float x, float y, float z, float w)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	pos.w = w;
}

void CLight::SetSpot(float x, float y, float z, float w)
{
	spotPowerRange.x = x;
	spotPowerRange.y = y;
	spotPowerRange.z = z;
	spotPowerRange.w = w;
}

void CLight::SetMaterial(float spec, float amb, float diffuse)
{
	SetSpecular(spec);
	SetAmbient(amb);
	SetDiffuse(diffuse);
}