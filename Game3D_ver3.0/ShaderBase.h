/*===========================================================================
  @file   ShaderBase.h
  @brief  シェーダー生成
  @author HAL名古屋
  @date   2021/09/16
===========================================================================*/
#ifndef _SHADERBASE_H_
#define _SHADERBASE_H_

#include "Texture.h"
//------------------------------------------------------------
//読み込み・作成のベースクラス
class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase();

	HRESULT Create(const char* FileName);
	virtual void Bind() = 0;
	virtual void Clear() = 0;

protected:
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

};
//------------------------------------------------------------
//頂点シェーダー生成クラス
class VertexShader : public ShaderBase
{
public:
	enum Layout
	{
		LAYOUT_PUN,		// pos-uv-normal
		LAYOUT_PUNT,	// pos-uv-normal-tangent
		LAYOUT_PUNC,	// pos-color-uv-normal
		LAYOUT_PMD,		// pmdモデル
		LAYOUT_PUNBB,    // pos-uv-normal-boneIdx-boneWeight
	};
public:
	VertexShader(Layout layout);
	virtual ~VertexShader();

	virtual void Bind();
	virtual void Clear();
protected:
	virtual HRESULT MakeShader(void* pData, UINT size);

private:
	Layout m_layout;
	ID3D11InputLayout* m_pInputLayout;
	ID3D11VertexShader* m_pVertexShader;
};
//------------------------------------------------------------
//ピクセルシェーダー生成クラス
class PixelShader : public ShaderBase
{
public:
	PixelShader();
	virtual ~PixelShader();

	virtual void Bind();
	virtual void Clear();
protected:
	virtual HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11PixelShader* m_pPixelShader;
};
//------------------------------------------------------------
//ハルシェーダー生成クラス
class HullShader :public ShaderBase
{
public:
	HullShader();
	virtual ~HullShader();
	virtual void Bind();
	virtual void Clear();
protected:
	virtual HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11HullShader* m_pHullShader;
};
//------------------------------------------------------------
//ドメインシェーダー生成クラス
class DomainShader :public ShaderBase
{
public:
	DomainShader();
	virtual ~DomainShader();
	virtual void Bind();
	virtual void Clear();
protected:
	virtual HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11DomainShader* m_pDomainShader;
};
//------------------------------------------------------------
//バッファ生成クラス
class ShaderBuffer
{
public:
	ShaderBuffer();
	~ShaderBuffer();

	HRESULT Create(UINT size);
	void Write(void* pData);
	void BindVS(UINT slot);
	void BindPS(UINT slot);
	void BindHS(UINT slot);
	void BindDS(UINT slot);
	void Clear() { m_pBuffer = 0; }
	ID3D11Buffer* GetBuf() { return m_pBuffer; }
private:
	ID3D11Buffer* m_pBuffer;
	
};
//------------------------------------------------------------
void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot = 0);
#endif // !_SHADERBASE_H_