#ifndef _CObjectManager_HG_
#define _CObjectManager_HG_

// Written by Michael Feeney, Fanshawe College, 2009-2010
// mfeeney@fanshawec.ca
// It may be distributed under the terms of the General Public License:
// http://www.fsf.org/licenses/gpl.html
// Use this code at your own risk. It is indented only as a learning aid.

#include "CPlyFile5nt.h"
#include <vector>
#include <map>
#include <d3d10.h>
#include <d3dx10.h>

class CPlyInfo
{
public:
	CPlyInfo();
	~CPlyInfo();
	int numberOfVertices;
	int numberOfElements;
	int vertexBufferStartIndex;
	int indexBufferStartIndex;
	float extent;
	std::wstring plyFileName;
};

struct SimpleVertex
{
    D3DXVECTOR4 Pos;
    D3DXVECTOR4 Normal;
	D3DXVECTOR2 Texture;		// Added for texturing...
};

class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();

	// This takes a vector of ply file names, then loads them into an single
	//	vertex and index buffer. 
	//
	// NOTE: It takes a list of ply models because it loads them into a SINGLE vertex and index
	//	buffer, storing the offsets into that buffer. If the vertex formats of your models are the 
	//	same, it's common to store them all in one vertex buffer. 
	//
	// Another Note: You could do this a number of ways, for instance, you could create a big vertex
	//	buffer, then load the models one at a time into the buffer. To do this, you would have to 
	//	create the buffer as D3D10_USAGE_DYNAMIC, so that you can add to it later. 
	//	***BUT*** you can't *resize* the buffer, only write more data to it. You'll have to either
	//	create a buffer that's big enough for all of your data, or create multiple buffers (yuck).
	bool LoadPlyModelTypes( std::vector< std::wstring > vecPlyFiles, 
		                    ID3D10Device* &pd3dDevice,
	                        ID3D10Buffer* &pVertexBuffer,
							ID3D10Buffer* &pIndexBuffer,
							ID3D10InputLayout* &pVertexLayout,
							std::wstring &error );

	bool GetPlyRenderingInfoByPlyFileName( std::wstring plyFile, CPlyInfo &plyInfo, std::wstring &error );

	//Question 7 - Allows to retrieve a plyfile by index number
	CPlyInfo GetModel(int modelIndex);

	CPlyInfo GetRandomModel( void );

private:
	// Ordered by ply file name. 
	std::map< std::wstring, CPlyInfo > m_mapPlyObjectInBuffer;

	// Used internally to load each ply...
	bool m_LoadPlyModelType( CPlyInfo &tempPlyInfo, 
                             SimpleVertex* tempVertexArray, 
							 DWORD* tempIndexArray,
							 std::wstring &error );
	ID3D10Buffer*		m_pVertexBuffer;
	ID3D10Buffer*       m_pIndexBuffer;
	ID3D10Device*		m_pd3dDevice;
	ID3D10InputLayout*  m_pVertexLayout;

	int m_LastVertexBufferIndex;
	int m_LastIndexBufferIndex;
};


#endif