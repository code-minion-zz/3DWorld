//=======================================================================================
// Box.h                                                                         
//=======================================================================================

#ifndef BOX_H
#define BOX_H

#include "Utility.h"

class Box
{
public:

	Box();
	~Box();
	
	void init(ID3D10Device* device, float scale, D3DXVECTOR3 _color);
	void initPrism(ID3D10Device* device, float scale, D3DXVECTOR3 _color);
	void draw();
	
	bool sky;

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;
};

#endif // BOX_H
