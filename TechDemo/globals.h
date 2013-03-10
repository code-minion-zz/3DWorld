#ifndef GLOBAL_H
#define GLOBAL_H

#include "DrawableTex2D.h"
#include "Light.h"

	static DrawableTex2D mShadowMap;

	static D3DXVECTOR4 mReflectNone;
	static D3DXVECTOR4 mReflectAll;

	static D3DXVECTOR4 mReflectMtrl[10];
	
	static D3DXMATRIX mFloorWorld;
	static D3DXMATRIX mParentCubeWorld;

	static D3DXMATRIX mFloorTexMtx;
	static D3DXMATRIX mIdentityTexMtx;
	
	static Light mParallelLight;

	static D3DXMATRIX mLightView;
	static D3DXMATRIX mLightVolume;

	static ID3D10ShaderResourceView* mFloorMapRV ;
	static ID3D10ShaderResourceView* mFloorNormalMapRV ;
	static ID3D10ShaderResourceView* mFloorSpecMapRV ;
	static ID3D10ShaderResourceView* mBaseMapRV ;
	static ID3D10ShaderResourceView* mBaseNormalMapRV;
	static ID3D10ShaderResourceView* mBallMapRV;
	static ID3D10ShaderResourceView* mColumnMapRV;
	static ID3D10ShaderResourceView* mColumnNormalMapRV;
	static ID3D10ShaderResourceView* mSpecMapRV;
	static ID3D10ShaderResourceView* mDefaultSpecMapRV;
	static ID3D10ShaderResourceView* mDefaultNormalMapRV;
	static ID3D10ShaderResourceView* mEnvMapRV;
 
	static ID3D10EffectTechnique* mTech;
	static ID3D10EffectVariable* mfxLightVar;
	static ID3D10EffectVariable* mfxEyePosVar;
	static ID3D10EffectMatrixVariable* mfxLightWVPVar;
	static ID3D10EffectMatrixVariable* mfxWVPVar;
	static ID3D10EffectMatrixVariable* mfxWorldVar;
	static ID3D10EffectMatrixVariable* mfxTexMtxVar;
	static ID3D10EffectVectorVariable* mfxReflectMtrlVar;
	static ID3D10EffectScalarVariable* mfxCubeMapEnabledVar;
	static ID3D10EffectShaderResourceVariable* mfxDiffuseMapVar;
	static ID3D10EffectShaderResourceVariable* mfxSpecMapVar;
	static ID3D10EffectShaderResourceVariable* mfxNormalMapVar;
	static ID3D10EffectShaderResourceVariable* mfxShadowMapVar;
	static ID3D10EffectShaderResourceVariable* mfxCubeMapVar;

	static ID3D10RasterizerState* mNoCullRS;
	static ID3D10RasterizerState* mReverseRS;

	static ID3D10EffectTechnique* mBuildShadowMapTech;
	static ID3D10EffectMatrixVariable* mfxBuildShadowMapLightWVPVar;
	static ID3D10EffectShaderResourceVariable* mfxBuildShadowMapDiffuseMapVar;

	static ID3D10EffectTechnique* mDrawShadowMapTech;
	static ID3D10EffectShaderResourceVariable* mfxDrawShadowMapTexVar;

	static ID3D10EffectDepthStencilVariable* mfxStencilBuffer;
	static ID3D10DepthStencilState*		mStencilWrite;
	static ID3D10DepthStencilState*		mStencilRead;
	static ID3D10DepthStencilState*		disabledDepthStencilState;
	static ID3D10DepthStencilState*		enabledDepthStencilState;
	 
//static void setWorld(D3DXMATRIX _world) {
//	mfxWorldVar->SetMatrix(_world);
//}

#endif // GLOBAL_H