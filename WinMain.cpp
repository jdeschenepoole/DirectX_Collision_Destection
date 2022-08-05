#include "global.h"
#include "TGetRandom.h"

MaterialInfo getRandomMaterial(void)
{
	MaterialInfo randMaterial;
	// Place 1.0f in all the 4th locations (so math will work or ambient will be 'off')
	randMaterial.ambient.w = 1.0f;
	randMaterial.diffuse.w = 1.0f;
	randMaterial.spec.w = 1.0f;

	randMaterial.ambient.x = getRand<float>(0.0f, 0.1f);
	randMaterial.ambient.y = getRand<float>(0.0f, 0.1f);
	randMaterial.ambient.z = getRand<float>(0.0f, 0.1f);

	randMaterial.diffuse.x = getRand<float>(0.0f, 1.0f);
	randMaterial.diffuse.y = getRand<float>(0.0f, 1.0f);
	randMaterial.diffuse.z = getRand<float>(0.0f, 1.0f);

	float specular = 0.3f;
	randMaterial.spec.x = getRand<float>(0.0f, specular);
	randMaterial.spec.y = getRand<float>(0.0f, specular);
	randMaterial.spec.z = getRand<float>(0.0f, specular);

	return randMaterial;
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
 
// Save the "handle to the instance." a.k.a. the number that windows uses to identify this application instance
	::g_hInst = hInstance;

	std::wstring error;
	if ( !InitDirectXAndCreateWindow( hInstance, nCmdShow, L"Physics & Simulation - Project 2", 1024, 768, error ) )
	{
		MessageBox( NULL, error.c_str(), L"Something is Wrong", MB_OK );
		exit( -1 );
	}
	

	// Loads Shader Effect File, (filename)
	if ( !LoadAndPrepareShaderEffectFile( L"Lights05.fx", "Render", error ) )	
	{
		MessageBox( NULL, error.c_str(), L"Something is wrong", MB_OK );
		exit( -1 );
	}

	std::vector< std::wstring > vecModels;
	vecModels.push_back( L"Ply\\s21.ply" );
	//vecModels.push_back( L"Ply\\bun_zipper_res4.ply" );
	vecModels.push_back( L"Ply\\g0_ASCII_Scaled.ply" );
	error = L"";
	if ( !g_theObjectManager.LoadPlyModelTypes( vecModels, ::g_pd3dDevice,
		                                        ::g_pVertexBuffer, ::g_pIndexBuffer, 
												::g_pVertexLayout, error ) )
	{
		MessageBox( NULL, error.c_str(), L"Can't load ply models", MB_OK );
	}
	// *******************************************************************************

	// *******************************************************************************
	// Creates the First Object (Enviroment)
	// *******************************************************************************

	CObject myObject;
	CPlyInfo plyInfo;
	::g_theObjectManager.GetPlyRenderingInfoByPlyFileName(L"Ply\\g0_ASCII_Scaled.ply", plyInfo, error);
	myObject.plyFileName = plyInfo.plyFileName;

	myObject.numTriangles = plyInfo.numberOfElements;
	myObject.numVertices = plyInfo.numberOfVertices;
	myObject.maxExtent = plyInfo.extent;
	myObject.Scale = 1.0f; //0.001f

	// Set the material for the Object...
	MaterialInfo m = MaterialInfo();
	m.ambient = D3DXVECTOR4(0.9f, 0.9f, 0.9f, 1.0f);
	m.diffuse = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	m.spec = D3DXVECTOR4(0.8f, 0.7f, 0.4f, 1.0f);
	myObject.material = m;

	// Place the Object
	myObject.Position.x = -850.0f;
	myObject.Position.y = -7840.0f ;
	myObject.Position.z = -600.0f;

	g_vecObjects.push_back( myObject );


	// *******************************************************************************
	// Creates the Other Objects (Player)
	// *******************************************************************************

	CObject myObject2;
	::g_theObjectManager.GetPlyRenderingInfoByPlyFileName(L"Ply\\s21.ply", plyInfo, error);
	myObject2.plyFileName = plyInfo.plyFileName;

	myObject2.numTriangles = plyInfo.numberOfElements;
	myObject2.numVertices = plyInfo.numberOfVertices;
	myObject2.maxExtent = plyInfo.extent;
	myObject2.Scale = 1.0f;

	// Set the material for the Object...
	MaterialInfo m2 = MaterialInfo();
	m2.ambient = D3DXVECTOR4(0.1f, 0.3f, 0.5f, 1.0f);
	m2.diffuse = D3DXVECTOR4(0.9f, 0.7f, 0.2f, 1.0f);
	m2.spec = D3DXVECTOR4(0.8f, 0.7f, 0.4f, 1.0f);
	myObject2.material = m2;

	// Place the Object
	myObject2.Position.x = 0.0f;
	myObject2.Position.y = 0.0f;
	myObject2.Position.z = 0.0f;

	g_vecObjects.push_back( myObject2 );

	// ****************************************************************************
	// Place the camera (aka the 'eye')
	// ****************************************************************************
	//::g_eye.x = 5.0f;
	//::g_eye.y = -4.0f;
	//::g_eye.z = -5.0f;
	//::g_target.x = 5.0f;
	//::g_target.y = -4.0f;
	//::g_target.z = -2.0f;
	::g_eye.x = 0.0f;
	::g_eye.y = 0.0f;
	::g_eye.z = -3.0f;
	::g_target.x = 0.0f;
	::g_target.y = 0.0f;
	::g_target.z = 0.0f;

	// ****************************************************************************
	// Set up the light...
	// ****************************************************************************
	D3DXVECTOR4 dir( 0.0f, 1.0f, 0.0f, 0.0f );
    D3DXVECTOR4 pos( 0.0f, 1.0f, -2.0f, 0.0f );
    D3DXVECTOR4 spot( 0.0f, 2.0f, -2.0f, 0.0f );
	g_theLight = CLight(0.5f, dir, pos, spot );
	g_theLight.SetAmbient(0.6f);
	g_theLight.SetDiffuse(0.1f);
	g_theLight.SetSpecular(0.5f);
	g_theLight.ChangeType(0);

	// ****************************************************************************
	// Load a texture...
	// ****************************************************************************
	error = L"";
	if ( !LoadTexture( L"textures\\metal_1.jpg", g_pTexture01, error ) )
	{
		MessageBox( NULL, error.c_str(), L"Something is wrong", MB_OK );
		exit( -1 );
	}

	// ****************************************************************************
	
	// Main message loop
    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
			SimulationStep();
            Render();
        }
    }

	// Shut'er down!
	if( g_pd3dDevice ) g_pd3dDevice->ClearState();

    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    if( g_pSwapChain ) g_pSwapChain->Release();
    if( g_pd3dDevice ) g_pd3dDevice->Release();

    return ( int )msg.wParam;
}




