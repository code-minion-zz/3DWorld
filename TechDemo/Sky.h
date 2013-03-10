#ifndef SKYDOME_H
#define SKYDOME_H

#include "Utility.h"

class Sky
{
public:
	Sky();
	~Sky();
	
	void init(ID3D10Device* device, ID3D10ShaderResourceView* cubemap, float radius);
	//void colorInit(ID3D10Device* device, unsigned long color, float radius);

	void draw();
	ID3D10Buffer& getVertices() { return *mVB;};
	ID3D10Buffer& getIndices() { return *mIB;};

private:
	Sky(const Sky& rhs);
	Sky& operator=(const Sky& rhs);

private:
	ID3D10Device* md3dDevice;
	ID3D10Buffer* mVB;
	ID3D10Buffer* mIB;

	ID3D10ShaderResourceView* mCubeMap;

	UINT mNumIndices;
 
	ID3D10EffectTechnique* mTech;
	ID3D10EffectMatrixVariable* mfxWVPVar;
	ID3D10EffectShaderResourceVariable* mfxCubeMapVar;
};

#endif // SKY_H