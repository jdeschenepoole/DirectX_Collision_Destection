#ifndef _global_HG_
#define _global_HG_

#include <string>
#include <vector>		
#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "CLight.h"
#include "CObject.h"
#include "CHRTimer.h"		// Add the HR timer...
#include "CObjectManager.h"

extern CHRTimer g_TheTimer;

extern HINSTANCE   g_hInst;	// = NULL;
extern HWND        g_hWnd;	// = NULL;

// DX variables...
extern ID3D10Device*           g_pd3dDevice;		// = NULL;
extern IDXGISwapChain*         g_pSwapChain;		// = NULL;
extern ID3D10RenderTargetView* g_pRenderTargetView;	// = NULL;

extern UINT g_windowWidth;
extern UINT g_windowHeight;

// **********************************************
extern ID3D10Effect*               g_pEffect;				// = NULL;
extern ID3D10EffectTechnique*      g_pTechnique;			// = NULL;
extern ID3D10InputLayout*          g_pVertexLayout;		// = NULL;
extern ID3D10Buffer*               g_pVertexBuffer;		// = NULL;
extern ID3D10Buffer*               g_pIndexBuffer;			// = NULL;
extern ID3D10EffectMatrixVariable* g_pWorldVariable;		// = NULL;
extern ID3D10EffectMatrixVariable* g_pViewVariable;		// = NULL;
extern ID3D10EffectMatrixVariable* g_pProjectionVariable;	// = NULL;
extern D3DXMATRIX                  g_World;
extern D3DXMATRIX                  g_View;
extern D3DXMATRIX                  g_Projection;
// **********************************************
extern ID3D10Texture2D*			g_pDepthStencilBuffer;
extern ID3D10DepthStencilView*	g_pDepthStencilView;
// **********************************************

bool InitDirectXAndCreateWindow( HINSTANCE hInstance, int nCmdShow, 
	                             std::wstring title, 
								 UINT width, UINT height, 
								 std::wstring &error );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

void SimulationStep();
void Render();

// **********************************************
bool LoadAndPrepareShaderEffectFile( std::wstring shaderFileName, std::string effectName, std::wstring &error );
// **********************************************

bool LoadModelIntoBuffer( std::wstring modelFilename, CPlyInfo &plyInfo, std::wstring &error );


extern CObjectManager g_theObjectManager;

// **********************************************

// **********************************
extern ID3D10ShaderResourceView*           g_pTexture01;// = NULL;		// Our first texture
extern ID3D10ShaderResourceView*           g_pTexture02;// = NULL;		// Our second texture

extern ID3D10EffectShaderResourceVariable*	g_pTexture01ShaderVariable;		// Our texture variable inside the shader
extern ID3D10EffectShaderResourceVariable*	g_pTexture02ShaderVariable;		// Ditto, texture #2

bool LoadTexture( std::wstring textureFileName, ID3D10ShaderResourceView* pTexture, std::wstring &error );
// **********************************


// Lighting and material stuff

extern CLight g_theLight;	//LightDesc NOTE: we will likely want more than one of these.
extern D3DXVECTOR4 g_eye;		// essentially the camera
extern D3DXVECTOR4 g_target;	// camera target

extern ID3D10EffectVectorVariable*	g_pEyeVariable;			// "eye" in shader: Eye coordinates
extern ID3D10EffectVariable*		g_pLightVariable;		// "light" in shader: Description of our light
extern ID3D10EffectScalarVariable*	g_pLightTypeVariable;	// Type of light
extern ID3D10EffectVariable*		g_pObjectMaterialVariable;	// Description of the material of our object

// Will contain all our objects...
extern std::vector<CObject> g_vecObjects;	// Add this...

#endif 