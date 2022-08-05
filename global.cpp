#include "global.h"

// High Res timer
CHRTimer g_TheTimer;

// Add this...
std::vector<CObject> g_vecObjects;

HINSTANCE   g_hInst = NULL;
HWND        g_hWnd = NULL;
// DX variables...
ID3D10Device*           g_pd3dDevice = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D10RenderTargetView* g_pRenderTargetView = NULL;

UINT g_windowWidth = 0;
UINT g_windowHeight = 0;

// **********************************************
ID3D10Effect*               g_pEffect = NULL;
ID3D10EffectTechnique*      g_pTechnique = NULL;
ID3D10InputLayout*          g_pVertexLayout = NULL;
ID3D10Buffer*               g_pVertexBuffer = NULL;
ID3D10Buffer*               g_pIndexBuffer = NULL;
ID3D10EffectMatrixVariable* g_pWorldVariable = NULL;
ID3D10EffectMatrixVariable* g_pViewVariable = NULL;
ID3D10EffectMatrixVariable* g_pProjectionVariable = NULL;

D3DXMATRIX                  g_World;
D3DXMATRIX                  g_View;
D3DXMATRIX                  g_Projection;
// **********************************************
ID3D10Texture2D*			g_pDepthStencilBuffer = NULL;
ID3D10DepthStencilView*		g_pDepthStencilView = NULL;

// *********************************************
CLight g_theLight;
D3DXVECTOR4 g_eye;
D3DXVECTOR4 g_target;

// Lighting and material stuff
ID3D10EffectVectorVariable*	g_pEyeVariable = NULL;			// Eye coordinates
ID3D10EffectVariable*		g_pLightVariable = NULL;		// Description of our light
ID3D10EffectScalarVariable*	g_pLightTypeVariable = NULL;	// Type of light
ID3D10EffectVariable*		g_pObjectMaterialVariable = NULL;	// Description of the material of our object


// **********************************
ID3D10ShaderResourceView*           g_pTexture01 = NULL;		// Our first texture
ID3D10ShaderResourceView*           g_pTexture02 = NULL;		// Our second texture

ID3D10EffectShaderResourceVariable*	g_pTexture01ShaderVariable = NULL;		// Our texture variable inside the shader
ID3D10EffectShaderResourceVariable*	g_pTexture02ShaderVariable = NULL;		// Ditto, texture #2

// **********************************

CObjectManager g_theObjectManager;
