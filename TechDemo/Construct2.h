//=======================================================================================
// Construct2.h                                                                         
//=======================================================================================

#ifndef Construct2_H
#define Construct2_H

#include "Utility.h"
#include "Box.h"
#include "Quad.h"

class Construct2
{
public:

	Construct2();
	~Construct2();
	
	/// rotation in radians
	void init(ID3D10Device* device, float rotation, float scale);
	void draw();
	

private:
	DWORD mNumVertices;
	DWORD mNumFaces;

	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;

	Box mPrism1;
	Quad mPlank;
	Box mPrism2;
};

#endif // Construct2_H
