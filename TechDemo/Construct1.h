//=======================================================================================
// Box.h                                                                         
//=======================================================================================

#ifndef C1_H
#define C1_H

#include "Utility.h"
#include "Box.h"
#include "Quad.h"
#include "globals.h"

class Construct1
{
public:

	Construct1();
	~Construct1();
	
	void init(ID3D10Device* device, float rotation, float scale);
	void draw(ID3D10EffectMatrixVariable*, ID3D10EffectPass*);
	
	//bool sky;

private:
	//DWORD mNumVertices;
	//DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	//ID3D10Buffer* mVB;
	//ID3D10Buffer* mIB;
	
	D3DXMATRIX mBoxWorld;
	D3DXMATRIX mPlank1World;
	D3DXMATRIX mPrism1World;
	D3DXMATRIX mPrism2World;
	D3DXMATRIX mPlank2World;

	Box mBox;
	Quad mPlank1;
	Box mPrism1;
	Box mPrism2;
	Quad mPlank2;
};

#endif // C1_H
