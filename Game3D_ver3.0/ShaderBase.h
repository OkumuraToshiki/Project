/*===========================================================================
  @file   ShaderBase.h
  @brief  �V�F�[�_�[����
  @author HAL���É�
  @date   2021/09/16
===========================================================================*/
#ifndef _SHADERBASE_H_
#define _SHADERBASE_H_

#include "Texture.h"
//------------------------------------------------------------
//�ǂݍ��݁E�쐬�̃x�[�X�N���X
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
//���_�V�F�[�_�[�����N���X
class VertexShader : public ShaderBase
{
public:
	enum Layout
	{
		LAYOUT_PUN,		// pos-uv-normal
		LAYOUT_PUNT,	// pos-uv-normal-tangent
		LAYOUT_PUNC,	// pos-color-uv-normal
		LAYOUT_PMD,		// pmd���f��
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
//�s�N�Z���V�F�[�_�[�����N���X
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
//�n���V�F�[�_�[�����N���X
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
//�h���C���V�F�[�_�[�����N���X
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
//�o�b�t�@�����N���X
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