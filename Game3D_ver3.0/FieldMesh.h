/*===========================================================================
  @file    FieldMesh.h
  @brief  ÉtÉBÅ[ÉãÉhï`âÊ
  @author âúë∫èrãI
  @date   2021/09/09
===========================================================================*/
#ifndef _FIELDMESH_H_
#define _FIELDMESH_H_

#include "ShaderBuffer.h"
#include "Texture.h"
class LightClass;
class DrawBuffer;
class ShaderResource;

struct DrawData
{
	struct SD_WORLD
	{
		XMMATRIX view;
		XMMATRIX proj;
		XMMATRIX world;
	};
	MakeShaderBuffer<SD_WORLD> worldBuffer;
	MakeShaderBuffer<XMVECTOR> eyeBuffer;
};

class FieldMeshClass
{
private:
	DrawBuffer* m_pBuffer;
	ShaderResource* m_pShader;
	ID3D11ShaderResourceView* m_pSRV;
	DrawData m_DrawData;
public:
	FieldMeshClass();
	~FieldMeshClass();
	void Update();
	void Draw(LightClass* pLight);
private:
	HRESULT MakeBuffer();
};
#endif // !_FIELDMESH_H_