//=============================================================================
// Tech Demo.cpp                                  
//				by Kit!
//
// Demonstrates shadow mapping, lighting, mesh loading, cube mapping, skeletal animation, LOD, .
//
// Controls:
//		'A'/'D'/'W'/'S' - Move
//      Hold down left mouse button and move mouse to rotate.
//
//=============================================================================

#include "WindowApp.h"
//#include "Light.h"
#include "Box.h"
#include "Quad.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Camera.h"
#include "Effects.h"
#include "InputLayouts.h"
#include "TextureMgr.h"
#include "Sky.h"
#include "globals.h"
#include "DrawableTex2D.h"
#include "Construct1.h"
//#include "Mesh.h"
#include <stdlib.h>
#include <time.h>
#ifdef _DEBUG
//#include <vld.h>
#endif


class TechDemoApp : public WindowApp
{
public:
	TechDemoApp(HINSTANCE hInstance);
	~TechDemoApp();

	void initApp();
	void onResize();
	void updateScene(float dt);
	void drawScene(); 

	LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void drawSceneToShadowMap();
private:

	POINT mOldMousePos;
	float mfElapsedTime;
	UINT muDirection;
	static const UINT LEFT = 0;
	static const UINT RIGHT = 1;

	bool toggleZbuffer;

	Quad mFloor;
	Box mCube;
	Box mPrism;
	Box mSkyBox;
	Sphere mBall;
	Construct1 c1;
	//Sky mSky;
//	Mesh mTree;

	

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


	TechDemoApp theApp(hInstance);
	
	theApp.initApp();

	return theApp.run();
}

TechDemoApp::TechDemoApp(HINSTANCE hInstance)
: WindowApp(hInstance)
{
	
	//D3DXMatrixTranslation(&mFloorWorld, 0.0f, 15.0f, -10.0f);
	D3DXMatrixIdentity(&mFloorWorld);
	D3DXMatrixTranslation(&mParentCubeWorld, 85.0f, 10.0f, 20.0f);
	//srand( (UINT)time (NULL) );
	//D3DXMatrixTranslation(&mChildCubeWorld, 10.0f, 10.0f, 10.0f);
	D3DXMATRIX rotation;
	D3DXMatrixRotationY(&rotation, 3.14f/2.f);
//	D3DXMatrixMultiply(&mChildCubeWorld, &mChildCubeWorld, &rotation);
	mfElapsedTime = 0.f;
	muDirection = LEFT;
	toggleZbuffer = true;
 
	//for(int i = 0; i < 5; ++i)
	//{
	//	D3DXMatrixTranslation(&mTreeWorld[i*2+0], -5.0f - 1 + rand() % 3, 0.f, -12.0f - 2 + rand() % 4 + i*6.0f);
	//	D3DXMatrixTranslation(&mTreeWorld[i*2+1], +5.0f - 1 + rand() % 3, 0.f, -12.0f - 2 + rand() % 4 + i*6.0f);

	//}

	//mReflectMtrl[0] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//mReflectMtrl[1] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//mReflectMtrl[2] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//mReflectMtrl[3] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//mReflectMtrl[4] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//mReflectMtrl[5] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//mReflectMtrl[6] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//mReflectMtrl[7] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//mReflectMtrl[8] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//mReflectMtrl[9] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);


	D3DXMatrixScaling(&mFloorTexMtx, 10.0f, 20.0f, 1.0f);
	D3DXMatrixIdentity(&mIdentityTexMtx);
 
	mReflectNone = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
	mReflectAll  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

}

TechDemoApp::~TechDemoApp()
{
	if( md3dDevice )
		md3dDevice->ClearState();


	fx::DestroyAll();
	InputLayout::DestroyAll();
}

void TechDemoApp::initApp()
{
	WindowApp::initApp();

	fx::InitAll(md3dDevice);
	InputLayout::InitAll(md3dDevice);
	GetTextureMgr().init(md3dDevice);

	D3D10_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(D3D10_DEPTH_STENCIL_DESC));
	dsDesc.DepthEnable					= true;
	dsDesc.DepthWriteMask				= D3D10_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc					= D3D10_COMPARISON_LESS;
	dsDesc.StencilEnable				= true;
	dsDesc.StencilReadMask				= 0xff;
	dsDesc.StencilWriteMask				= 0xff;

	// Normal Stencil State
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFailOp		= D3D10_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp		= D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc		= D3D10_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilDepthFailOp	= D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFailOp		= D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp		= D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc			= D3D10_COMPARISON_ALWAYS;

	HR(md3dDevice->CreateDepthStencilState(&dsDesc, &enabledDepthStencilState));
	
	ZeroMemory(&dsDesc, sizeof(D3D10_DEPTH_STENCIL_DESC));

	// Disabled Stencil
	dsDesc.DepthEnable					= false;
	dsDesc.DepthWriteMask				= D3D10_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc					= D3D10_COMPARISON_LESS;
	dsDesc.StencilEnable				= true;
	dsDesc.FrontFace.StencilPassOp		= D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc		= D3D10_COMPARISON_EQUAL;
	dsDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	dsDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

	HR(md3dDevice->CreateDepthStencilState(&dsDesc, &disabledDepthStencilState));

	mTech                = fx::ShadowFX->GetTechniqueByName("ShadowTech");
	mfxLightVar          = fx::ShadowFX->GetVariableByName("gLight");
	mfxEyePosVar         = fx::ShadowFX->GetVariableByName("gEyePosW");
	mfxLightWVPVar       = fx::ShadowFX->GetVariableByName("gLightWVP")->AsMatrix();
	mfxWVPVar            = fx::ShadowFX->GetVariableByName("gWVP")->AsMatrix();
	mfxWorldVar          = fx::ShadowFX->GetVariableByName("gWorld")->AsMatrix();
	mfxTexMtxVar         = fx::ShadowFX->GetVariableByName("gTexMtx")->AsMatrix();
	mfxReflectMtrlVar    = fx::ShadowFX->GetVariableByName("gReflectMtrl")->AsVector();
	mfxCubeMapEnabledVar = fx::ShadowFX->GetVariableByName("gCubeMapEnabled")->AsScalar();
	mfxDiffuseMapVar     = fx::ShadowFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	mfxSpecMapVar        = fx::ShadowFX->GetVariableByName("gSpecMap")->AsShaderResource();
	mfxNormalMapVar      = fx::ShadowFX->GetVariableByName("gNormalMap")->AsShaderResource();
	mfxStencilBuffer	 = fx::ShadowFX->GetVariableByName("gStencilBuffer")->AsDepthStencil();
	mfxShadowMapVar      = fx::ShadowFX->GetVariableByName("gShadowMap")->AsShaderResource();
	mfxCubeMapVar        = fx::ShadowFX->GetVariableByName("gCubeMap")->AsShaderResource();

	D3D10_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D10_RASTERIZER_DESC));
	rsDesc.FillMode = D3D10_FILL_SOLID;
	rsDesc.CullMode = D3D10_CULL_NONE;
	rsDesc.FrontCounterClockwise = false;
	HR(md3dDevice->CreateRasterizerState(&rsDesc, &mNoCullRS));

	rsDesc.FrontCounterClockwise = true;
	HR(md3dDevice->CreateRasterizerState(&rsDesc, &mReverseRS));


	mBuildShadowMapTech            = fx::BuildShadowMapFX->GetTechniqueByName("BuildShadowMapTech");
	mfxBuildShadowMapLightWVPVar   = fx::BuildShadowMapFX->GetVariableByName("gLightWVP")->AsMatrix();
	mfxBuildShadowMapDiffuseMapVar = fx::BuildShadowMapFX->GetVariableByName("gDiffuseMap")->AsShaderResource();


	mDrawShadowMapTech     = fx::DrawShadowMapFX->GetTechniqueByName("DrawShadowMapTech");
	mfxDrawShadowMapTexVar = fx::DrawShadowMapFX->GetVariableByName("gShadowMap")->AsShaderResource();


	mShadowMap.init(md3dDevice, 1024, 1024, false, DXGI_FORMAT_UNKNOWN);
 
	mClearColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	GetCamera().position() = D3DXVECTOR3(0.0f, 1.8f, -10.0f);

	mFloorMapRV         = GetTextureMgr().createTex(L"Textures/grass/grass-texture-2.dds");
	mFloorNormalMapRV   = GetTextureMgr().createTex(L"Textures/grass/grass-texture-2_NRM.dds");
	mFloorSpecMapRV		= GetTextureMgr().createTex(L"Textures/grass/grass-texture-2_SPEC.dds");
	mBaseMapRV          = GetTextureMgr().createTex(L"Textures/stone/stone_diffuse.dds");
	mBaseNormalMapRV    = GetTextureMgr().createTex(L"Textures/stone/stone_normal.dds");
	mBallMapRV          = GetTextureMgr().createTex(L"Textures/blackdiffuse.dds");
	mColumnMapRV        = GetTextureMgr().createTex(L"Textures/bricks/bricks_diffuse.dds");
	mColumnNormalMapRV  = GetTextureMgr().createTex(L"Textures/bricks/bricks_normal.dds");
	mSpecMapRV          = GetTextureMgr().createTex(L"Textures/spec.dds");
	mDefaultSpecMapRV   = GetTextureMgr().createTex(L"Textures/default_spec.dds");
	mDefaultNormalMapRV = GetTextureMgr().createTex(L"Textures/default_normal.dds");
	//mEnvMapRV           = GetTextureMgr().createCubeTex(L"Textures/sky/nightsky.dds");

	mFloor.init(md3dDevice, 2, 2, 200.0f);
	mCube.init(md3dDevice, 10.0f, D3DXVECTOR3(0.8f,0.8f,0.8f));
	//mPrism.initPrism(md3dDevice, 10.0f);
	mBall.init(md3dDevice, 16.f, 30, 30);
	mSkyBox.sky = true;
	mSkyBox.init(md3dDevice, 200.f, D3DXVECTOR3(0.7f,.3f,1.f));
	c1.init(md3dDevice, 0.f, 10.f);

	//mTree.init(md3dDevice, L"Meshes/tree.m3d");
	//mTree.setCubeMap(mEnvMapRV);

	// direction updated at runtime
	mParallelLight.ambient  = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	mParallelLight.diffuse  = D3DXCOLOR(0.5f, .5f, .5f, 1.0f);
	mParallelLight.specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

 
	D3DXMatrixOrthoLH(&mLightVolume, 30.0f, 30.0f, 1.0f, 100.0f);
}

void TechDemoApp::onResize()
{
	WindowApp::onResize();

	float aspect = (float)mClientWidth/mClientHeight;
	GetCamera().setLens(0.25f*PI, aspect, 0.5f, 1000.0f);
}

void TechDemoApp::updateScene(float dt)
{
	WindowApp::updateScene(dt);

	if (muDirection == LEFT)
	{
		mfElapsedTime += dt;
	}
	else
	{
		mfElapsedTime -= dt;
	}
	
	if (mfElapsedTime > 1.60f)
	{
		muDirection = RIGHT;
	}
	if (mfElapsedTime < -1.60f)
	{
		muDirection = LEFT;
	}

	D3DXMATRIX rotation, trans;

	/*D3DXMatrixMultiply(&mParentCubeWorld, &mParentCubeWorld, D3DXMatrixRotationY(&rotation,1.0f*dt));
	mChildCubeWorld = (*D3DXMatrixTranslation(&mChildCubeWorld, 1.0f, 1.0f, 0.0f));
	D3DXMatrixRotationZ(&rotation, 1.0f * mfElapsedTime);
	D3DXMatrixMultiply(&mChildCubeWorld, &mChildCubeWorld, &rotation);
	D3DXMatrixTranslation(&trans, 1.0f, 1.0f, 0.0f);
	D3DXMatrixMultiply(&mChildCubeWorld, &mChildCubeWorld, &trans);
	D3DXMatrixMultiply(&mChildCubeWorld, &mChildCubeWorld, &mParentCubeWorld);*/

	// Update angles based on input to orbit camera around scene.
	if(GetAsyncKeyState('A') & 0x8000)	{
		GetCamera().strafe(-13.f*dt);
		//if ( GetCamera().position().x >
	}
	if(GetAsyncKeyState('D') & 0x8000)	GetCamera().strafe(+13.f*dt);
	if(GetAsyncKeyState('W') & 0x8000)	GetCamera().walk(+13.f*dt);
	if(GetAsyncKeyState('S') & 0x8000)	GetCamera().walk(-13.f*dt);
	if(GetAsyncKeyState('Z') & 0x8000)	toggleZbuffer = !toggleZbuffer;

	// Camera Collision

 
	GetCamera().rebuildView();

	// Animate light and keep shadow in sync.
	D3DXVECTOR3 lightPos;
	lightPos.x = 30.0f*cosf(0.25f*mTimer.getGameTime());
	lightPos.y = 20.0f;
	lightPos.z = 30.0f*sinf(0.25f*mTimer.getGameTime());


	D3DXMatrixLookAtLH(&mLightView, &lightPos,
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	D3DXVECTOR3 lightDirection = -lightPos;
	D3DXVec3Normalize(&mParallelLight.dir, &lightDirection);
}

void TechDemoApp::drawScene()
{
	WindowApp::drawScene();

	
	// Restore default states, input layout and primitive topology 
	// because mFont->DrawText changes them.  Note that we can 
	// restore the default states by passing null.

	md3dDevice->OMSetDepthStencilState(0, 0);

	if (toggleZbuffer)	{
		md3dDevice->OMSetDepthStencilState(enabledDepthStencilState, 1);		
	} else {
		md3dDevice->OMSetDepthStencilState(disabledDepthStencilState, 1);
	}

	float blendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
	md3dDevice->OMSetBlendState(0, blendFactor, 0xffffffff);
	md3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	md3dDevice->IASetInputLayout(InputLayout::PosTangentNormalTex);



	//
	// Draw scene to the shadow map.
	//

	//mShadowMap.begin();

	//drawSceneToShadowMap();

	//mShadowMap.end();

	// restore rendering to backbuffer
	resetOMTargetsAndViewport();

	//
	// Draw the rest of the scene.
	//

	md3dDevice->IASetInputLayout(InputLayout::PosTangentNormalTex);

	// Set per frame constants.
	mfxEyePosVar->SetRawValue(&GetCamera().position(), 0, sizeof(D3DXVECTOR3));
	mfxLightVar->SetRawValue(&mParallelLight, 0, sizeof(Light));
	
	mfxCubeMapVar->SetResource(mEnvMapRV);
	mfxShadowMapVar->SetResource(mShadowMap.depthMap());
 
	D3DXMATRIX view = GetCamera().view();
	D3DXMATRIX proj = GetCamera().proj();

    D3D10_TECHNIQUE_DESC techDesc;

    mTech->GetDesc( &techDesc );


	//mTree.setLight(mParallelLight);
	//mTree.setEyePos(GetCamera().position());
	//mTree.enableCubeMap(false);
	//mTree.setShadowMap(mShadowMap.depthMap());

    for(UINT i = 0; i < techDesc.Passes; ++i)
    {
        ID3D10EffectPass* pass = mTech->GetPassByIndex(i);
		/*md3dDevice->OMSetDepthStencilState(mStencilWrite, 1);
		mfxDiffuseMapVar->SetResource(mBallMapRV);
		mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		mfxSpecMapVar->SetResource(mDefaultSpecMapRV);
		pass->Apply(0);
		mBall.draw();*/
		
		//md3dDevice->OMSetDepthStencilState(mStencilRead, 1);
		//
		// draw floor
		//
		mfxWVPVar->SetMatrix((float*)&(mFloorWorld*view*proj));
		mfxLightWVPVar->SetMatrix((float*)&(mFloorWorld*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mFloorWorld);
		mfxTexMtxVar->SetMatrix((float*)&mFloorTexMtx);
		mfxDiffuseMapVar->SetResource(mFloorMapRV);
		mfxNormalMapVar->SetResource(mFloorNormalMapRV);
		mfxSpecMapVar->SetResource(mFloorSpecMapRV);
		mfxCubeMapEnabledVar->SetBool(false);
		mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		pass->Apply(0);
		mFloor.draw();


		// Draw Sky
		mfxWorldVar->SetMatrix((float*)&mParentCubeWorld);
		mfxWVPVar->SetMatrix((float*)&(mParentCubeWorld*view*proj));
		md3dDevice->RSSetState(mReverseRS);
		pass->Apply(0);
		mSkyBox.draw();
		md3dDevice->RSSetState(0);
		//
		// draw parent cube
		//
		//mfxLightWVPVar->SetMatrix((float*)&(mParentCubeWorld*mLightView*mLightVolume));
		mfxWorldVar->SetMatrix((float*)&mParentCubeWorld);
		//mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		//mfxDiffuseMapVar->SetResource(mBaseMapRV);
		//mfxNormalMapVar->SetResource(mBaseNormalMapRV);
		//mfxSpecMapVar->SetResource(mSpecMapRV);
		//mfxCubeMapEnabledVar->SetBool(false);
		//mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		pass->Apply(0);
		mCube.draw();
		//c1.draw();
		
		//
		// draw child cube
		//
		//mfxWVPVar->SetMatrix((float*)&(mChildCubeWorld*view*proj));
		//mfxLightWVPVar->SetMatrix((float*)&(mChildCubeWorld*mLightView*mLightVolume));
		//mfxWorldVar->SetMatrix((float*)&mChildCubeWorld);
		//mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		//
		//mfxDiffuseMapVar->SetResource(mBallMapRV);
		//mfxNormalMapVar->SetResource(mDefaultNormalMapRV);
		//mfxSpecMapVar->SetResource(mDefaultSpecMapRV);
		//mfxCubeMapEnabledVar->SetBool(true);
		//mfxReflectMtrlVar->SetFloatVector((float*)&mReflectAll);
		//pass->Apply(0);
		//mPrism.draw();
		c1.draw(mfxWorldVar, pass);
		//
		// draw trees
		//
		//mfxTexMtxVar->SetMatrix((float*)&mIdentityTexMtx);
		//mfxCubeMapEnabledVar->SetBool(false);
		//mfxReflectMtrlVar->SetFloatVector((float*)&mReflectNone);
		//mfxDiffuseMapVar->SetResource(mColumnMapRV);
		//mfxNormalMapVar->SetResource(mColumnNormalMapRV);
		//for(int i = 0; i < 10; ++i)
		//{
		//	mfxWVPVar->SetMatrix((float*)&(mTreeWorld[i]*view*proj));
		//	mfxLightWVPVar->SetMatrix((float*)&(mTreeWorld[i]*mLightView*mLightVolume));
		//	mfxWorldVar->SetMatrix((float*)&mTreeWorld[i]);
		//	pass->Apply(0);
		//	mTree.draw(mTreeWorld[i], mLightView * mLightVolume);
		//}	

		// Unbind shadow map from shader stage since we will be binding it
		// as a depth buffer when we rebuild the shadow map the next frame.
		mfxShadowMapVar->SetResource(0);
		pass->Apply(0);
    }

		//md3dDevice->OMSetDepthStencilState(mStencilRead, 1);
	// Draw sky last to save fill rate.
	

	// We specify DT_NOCLIP, so we do not care about width/height of the rect.
	RECT R = {5, 5, 0, 0};
//	md3dDevice->RSSetState(0);
	mFont->DrawText(0, mFrameStats.c_str(), -1, &R, DT_NOCLIP, WHITE);

	mSwapChain->Present(0, 0);
}

LRESULT TechDemoApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT mousePos;
	int dx = 0;
	int dy = 0;
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		if( wParam & MK_LBUTTON )
		{
			SetCapture(mhMainWnd);

			mOldMousePos.x = LOWORD(lParam);
			mOldMousePos.y = HIWORD(lParam);
		}
		return 0;

	case WM_LBUTTONUP:
		ReleaseCapture();
		return 0;

	case WM_MOUSEMOVE:
		if( wParam & MK_LBUTTON )
		{
			mousePos.x = (int)LOWORD(lParam); 
			mousePos.y = (int)HIWORD(lParam); 

			dx = mousePos.x - mOldMousePos.x;
			dy = mousePos.y - mOldMousePos.y;

			GetCamera().pitch( dy * 0.0087266f );
			GetCamera().rotateY( dx * 0.0087266f );
			
			mOldMousePos = mousePos;
		}
		return 0;
	}

	return WindowApp::msgProc(msg, wParam, lParam);
}
 
void TechDemoApp::drawSceneToShadowMap()
{
	D3D10_TECHNIQUE_DESC techDesc;
    mBuildShadowMapTech->GetDesc( &techDesc );

    for(UINT i = 0; i < techDesc.Passes; ++i)
    {
        ID3D10EffectPass* pass = mBuildShadowMapTech->GetPassByIndex(i);

		//
		// draw floor
		//
		//D3DXMATRIX floorWVP = mFloorWorld*mLightView*mLightVolume;
		//mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&floorWVP);
		//mfxBuildShadowMapDiffuseMapVar->SetResource(mFloorMapRV);
		//pass->Apply(0);
		//mFloor.draw();
		//
		// draw parent cube
		//
		D3DXMATRIX baseWVP = mParentCubeWorld*mLightView*mLightVolume;
		mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&baseWVP);
		mfxBuildShadowMapDiffuseMapVar->SetResource(mBaseMapRV);
		pass->Apply(0);
		mCube.draw();
		//
		// draw child cube
		//
		//D3DXMATRIX centerBallWVP = mChildCubeWorld*mLightView*mLightVolume;
		//mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&centerBallWVP);
		//mfxBuildShadowMapDiffuseMapVar->SetResource(mBallMapRV);
		//pass->Apply(0);
		//mCube.draw();

		//
		// draw columns
		//
		/*for(int i = 0; i < 10; ++i)
		{
			D3DXMATRIX columnWVP = mTreeWorld[i]*mLightView*mLightVolume;
			mfxBuildShadowMapLightWVPVar->SetMatrix((float*)&columnWVP);
			mfxBuildShadowMapDiffuseMapVar->SetResource(mColumnMapRV);
			pass->Apply(0);
			md3dDevice->RSSetState(mNoCullRS);
			mTree.drawToShadowMap(mfxBuildShadowMapDiffuseMapVar,pass);
			md3dDevice->RSSetState(0);
		}	*/
    }
}
