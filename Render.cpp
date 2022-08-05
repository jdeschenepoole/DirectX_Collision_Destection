#include "global.h"

static int totalIndicesToDraw = 3;

void Render()	// 60Hz because of the SWAPCHAIN setttings...
{
    // Just clear the backbuffer
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
    g_pd3dDevice->ClearRenderTargetView( g_pRenderTargetView, ClearColor );


    // Clear the depth buffer to 1.0 (max depth)
    g_pd3dDevice->ClearDepthStencilView( g_pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0 );


    // Initialize the view matrix
    D3DXVECTOR3 Eye( g_eye.x, g_eye.y, g_eye.z );
    D3DXVECTOR3 At( g_target.x, g_target.y, g_target.z );
    D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &g_View, &Eye, &At, &Up );

    // Initialize the projection matrix
    D3DXMatrixPerspectiveFovLH( &g_Projection, 
							    static_cast<float>(D3DX_PI) * 0.5f, 
		                        static_cast<float>(g_windowWidth) / static_cast<float>(g_windowHeight), 
								0.1f, 100.0f );

	// ******************************************************************************
	// ******************************************************************************
	// Here we set all the "per frame" stuff - things that are the same for all
	//	the objects in the scene like lighting, perspective matrix, likely view, etc. 
	//


	g_pViewVariable->SetMatrix( ( float* )&g_View );				// matrix View
    g_pProjectionVariable->SetMatrix( ( float* )&g_Projection );	// matrix Projection
	g_pEyeVariable->SetFloatVector( (float*) &g_eye );				// float4 eye
	
	// Question 5
	g_pLightVariable->SetRawValue( &g_theLight, 0, sizeof( g_theLight ) );	// LightDesc light
	g_pLightTypeVariable->SetInt( g_theLight.GetType() );

	// ******************************************************************************
	// ******************************************************************************

	std::wstring error;

	// Now draw all the objects....
	std::vector<CObject>::iterator itObjects;
	for ( itObjects = g_vecObjects.begin(); 
		  itObjects != g_vecObjects.end(); itObjects++ )
	{
		// Initialize the world matrix
		D3DXMatrixIdentity( &g_World );

		// Take the data from the Object iterator and load 
		//	a bunch of matrices with those values and set the 
		//	world transform...
		::D3DXMATRIX matTranslate;
		::D3DXMATRIX matRotateX, matRotateY, matRotateZ;
		// Also: D3DXMATRIX matScale... (don't use yet)
		::D3DXMATRIX matFinal;	// Final result of all the mults..

		D3DXMatrixIdentity( &matTranslate );	// 'clear' 
		D3DXMatrixIdentity( &matRotateX );
		D3DXMatrixIdentity( &matRotateY );
		D3DXMatrixIdentity( &matRotateZ );


		// Translation matrix...
		D3DXMatrixTranslation( &matTranslate, 
			                   itObjects->Position.x, 
							   itObjects->Position.y, 
							   itObjects->Position.z );
		// Three rotational matrices...
		D3DXMatrixRotationX( &matRotateX, itObjects->Rotation.x );
		D3DXMatrixRotationY( &matRotateY, itObjects->Rotation.y );
		D3DXMatrixRotationZ( &matRotateZ, itObjects->Rotation.z );

		::D3DXMatrixIdentity( &matFinal );


		D3DXMATRIX matScale;
		D3DXMatrixIdentity( &matScale );
		float scale = itObjects->Scale;
		::D3DXMatrixScaling( &matScale, scale, scale, scale );
		::D3DXMatrixMultiply( &matFinal, &matFinal, &matScale );

		
		::D3DXMatrixMultiply( &matFinal, &matFinal, &matRotateX );
		::D3DXMatrixMultiply( &matFinal, &matFinal, &matRotateY );
		::D3DXMatrixMultiply( &matFinal, &matFinal, &matRotateZ );

		::D3DXMatrixMultiply( &matFinal, &matFinal, &matTranslate );

		// Apply this object matrix to the world transform...
		::D3DXMatrixMultiply( &g_World, &g_World, &matFinal );

		g_pWorldVariable->SetMatrix( ( float* )&g_World );

		// Point the renderer to the appropriate vertex 
		//	and index buffer
		UINT stride = sizeof( SimpleVertex );
		UINT offset = 0;
		g_pd3dDevice->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );
	    g_pd3dDevice->IASetIndexBuffer( g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );

		// Set primitive topology
		g_pd3dDevice->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// ******************************************************************************
		// ******************************************************************************

		// Copy the material information for each object into the shader...
		MaterialInfo tempMaterial = itObjects->material;
		g_pObjectMaterialVariable->SetRawValue( &tempMaterial, 0, sizeof(MaterialInfo) );
	
		// ******************************************************************************

		// NEED to set texture
		// HINT: use "SetResource( )"...
		g_pTexture01ShaderVariable->SetResource( g_pTexture01 );

		// ******************************************************************************

		D3D10_TECHNIQUE_DESC techDesc;
		g_pTechnique->GetDesc( &techDesc );
		for( UINT p = 0; p < techDesc.Passes; ++p )
		{
			g_pTechnique->GetPassByIndex( p )->Apply( 0 );

			// Get the ply information from the model
			CPlyInfo tempPlyInfo;
			if ( g_theObjectManager.GetPlyRenderingInfoByPlyFileName( itObjects->plyFileName, tempPlyInfo, error ) )
			{


				g_pd3dDevice->DrawIndexed( itObjects->numTriangles * 3, 
										   tempPlyInfo.indexBufferStartIndex,
										   tempPlyInfo.vertexBufferStartIndex );        // 36 vertices needed for 12 triangles in a triangle list
			}
		}
	}//for ( itObjects = g_vecObjects.begin(); 

    g_pSwapChain->Present( 0, 0 );
}