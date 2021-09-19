/*===========================================================================
  @file   ShaderResource.cpp
  @brief  cso読み込み
  @author 奥村俊紀
  @date   2021/09/17
===========================================================================*/
#include "ShaderResource.h"
#include "main.h"
#include "Defines.h"
ShaderResource::ShaderResource(VertexShader::Layout layout, const char* vertex, const char* pixel)
	:m_pVShader(new VertexShader(layout)),m_pPShader(new PixelShader())
{
#ifdef _DEBUG
	FnAssert(m_pVShader->Create(vertex), "頂点シェーダ読み込み失敗");
	FnAssert(m_pPShader->Create(pixel), "ピクセルシェーダ読み込み失敗");
#else
	m_pVShader->Create(vertex);
	m_pPShader->Create(pixel);
#endif // _DEBUG
}

ShaderResource::~ShaderResource()
{
	SAFE_DELETE(m_pPShader);
	SAFE_DELETE(m_pVShader);
}

void ShaderResource::Bind()
{
	m_pVShader->Bind();
	m_pPShader->Bind();
}