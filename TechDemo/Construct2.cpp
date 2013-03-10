//=======================================================================================
// Construct2.cpp                                                                         
//=======================================================================================

#include "Construct2.h"
#include "Vertex.h"

Construct2::Construct2()
: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
}
 
Construct2::~Construct2()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

void Construct2::init(ID3D10Device* device, float radius, float scale)
{
	md3dDevice = device;
}


void Construct2::draw()
{
	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	md3dDevice->DrawIndexed(mNumFaces*3, 0, 0);
}