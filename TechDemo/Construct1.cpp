//=======================================================================================
// Construct1.cpp                                                                         
//=======================================================================================

//#include "globals.h"
#include "Construct1.h"
#include "Effects.h"
//#include "globals.h"
#include "Vertex.h"
#include "Camera.h"

Construct1::Construct1()
//: mNumVertices(0), mNumFaces(0), md3dDevice(0), mVB(0), mIB(0)
{
	D3DXMatrixTranslation(&mBoxWorld, 5.0f, 10.0f, 20.0f);
	D3DXMatrixTranslation(&mPrism1World, 15.0f, 10.0f, 20.0f);
	D3DXMatrixTranslation(&mPrism2World, 25.0f, 10.0f, 20.0f);
	D3DXMatrixTranslation(&mPlank1World, 35.0f, 10.0f, 20.0f);
	D3DXMatrixTranslation(&mPlank2World, -5.0f, 10.0f, 20.0f);
}
 
Construct1::~Construct1()
{
//	ReleaseCOM(mVB);
//	ReleaseCOM(mIB);
}

void Construct1::init(ID3D10Device* device, float rotation, float scale)
{
	md3dDevice = device;
	mBox.init(device, scale, D3DXVECTOR3(0.f,1.f,0.f));
	mPrism1.initPrism(device, scale, D3DXVECTOR3(1.f,0.f,0.f));
	mPrism2.initPrism(device, scale, D3DXVECTOR3(1.f,0.f,0.f));
	mPlank1.init(device, 2, 2, scale);
	mPlank2.init(device, 2, 2, scale);
	
}

void Construct1::draw(ID3D10EffectMatrixVariable* EV, ID3D10EffectPass* pass)
{
	D3DXMATRIX proj = GetCamera().proj();
	D3DXMATRIX view = GetCamera().view();
	EV->SetMatrix((float*)&mBoxWorld);
	pass->Apply(0);
	//mfxWorldVar->SetMatrix((float*)&mBoxWorld);
	//fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix()->SetMatrix((float*)&mBoxWorld);
	//fx::ShadowFX->GetTechniqueByName("ShadowTech")->GetPassByIndex(0)->Apply(0);
	mBox.draw();
	EV->SetMatrix((float*)&mPrism1World);
	pass->Apply(0);
	//fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix()->SetMatrix((float*)&mPrism1World);
	//fx::ShadowFX->GetTechniqueByName("ShadowTech")->GetPassByIndex(0)->Apply(0);
	//mfxWorldVar->SetMatrix((float*)&mPrism1World);
	mPrism1.draw();
	EV->SetMatrix((float*)&mPrism2World);
	pass->Apply(0);
	//fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix()->SetMatrix((float*)&mPrism2World);
	//fx::ShadowFX->GetTechniqueByName("ShadowTech")->GetPassByIndex(0)->Apply(0);
	//mfxWorldVar->SetMatrix((float*)&mPrism2World);
	mPrism2.draw();
	EV->SetMatrix((float*)&mPlank1World);
	pass->Apply(0);
	//fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix()->SetMatrix((float*)&mPlank1World);
	//fx::ShadowFX->GetTechniqueByName("ShadowTech")->GetPassByIndex(0)->Apply(0);
	//mfxWorldVar->SetMatrix((float*)&mPlank1World);
	mPlank1.draw();
	EV->SetMatrix((float*)&mPlank2World);
	pass->Apply(0);
	//fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix()->SetMatrix((float*)&mPlank2World);
	//fx::ShadowFX->GetTechniqueByName("ShadowTech")->GetPassByIndex(0)->Apply(0);
	//mfxWorldVar->SetMatrix((float*)&mPlank2World);
	mPlank2.draw();
}