/*===========================================================================
  @file   ShaderBase.h
  @brief  �V�F�[�_�[����
  @author HAL���É�
  @date   2021/09/16
===========================================================================*/
#include "ShaderBase.h"
#include "main.h"

//-----------------------------------------------------------------
//�ǂݍ��݁E�쐬�̃x�[�X�p�N���X
//�R���X�g���N�^
ShaderBase::ShaderBase()
{
}
//�f�X�g���N�^
ShaderBase::~ShaderBase()
{
}
//cso����V�F�[�_�[�쐬
HRESULT ShaderBase::Create(const char* FileName)
{
	HRESULT hr = E_FAIL;

	FILE *fp = NULL;
	fopen_s(&fp, FileName, "rb");
	if (fp == nullptr) { return hr; }

	// �t�@�C���T�C�Y
	UINT size = 0;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);

	// �f�[�^�ǂݍ���
	fseek(fp, 0L, SEEK_SET);
	BYTE *pData = new BYTE[size];
	fread_s(pData, size, size, 1, fp);
	fclose(fp);

	// �V�F�[�_�쐬
	hr = MakeShader(pData, size);

	delete[] pData;
	return hr;
}
//-----------------------------------------------------------------
//���_�V�F�[�_�[�����N���X
//�R���X�g���N�^
VertexShader::VertexShader(Layout layout)
	: m_pInputLayout(nullptr)
	, m_layout(layout)
{
}
//�f�X�g���N�^
VertexShader::~VertexShader()
{
	
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
	
}
//�w��̒��_�V�F�[�_�[��ݒ�
void VertexShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetShader(m_pVertexShader, NULL, 0);
	pContext->IASetInputLayout(m_pInputLayout);
}
//���_�V�F�[�_�[���N���A
void VertexShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetShader(NULL, NULL, 0);
	
}
//�V�F�[�_�[�𐶐��A���C�A�E�g�w��
HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	static const D3D11_INPUT_ELEMENT_DESC LayoutPUN[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	static const D3D11_INPUT_ELEMENT_DESC LayoutPUNT[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	static const D3D11_INPUT_ELEMENT_DESC LayoutPUNC[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	static const D3D11_INPUT_ELEMENT_DESC LayoutMMD[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE",		0, DXGI_FORMAT_R16G16_UINT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT",		0, DXGI_FORMAT_R8_UINT,				0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "EDGE",		0, DXGI_FORMAT_R8_UINT,				0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	static const D3D11_INPUT_ELEMENT_DESC LayoutPUNBB[] = {
		{"POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BONE_INDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	static const D3D11_INPUT_ELEMENT_DESC* pLayout[] =
	{
		LayoutPUN, LayoutPUNT, LayoutPUNC, LayoutMMD,LayoutPUNBB,
	};
	static const int layoutCnt[] =
	{
		_countof(LayoutPUN), _countof(LayoutPUNT),
		_countof(LayoutPUNC), _countof(LayoutMMD),
		_countof(LayoutPUNBB),
	};

	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// �V�F�[�_����
	hr = pDevice->CreateVertexShader(pData, size, nullptr, &m_pVertexShader);
	if (FAILED(hr)) { return hr; }

	// ���_���C�A�E�g�쐬
	hr = pDevice->CreateInputLayout(pLayout[m_layout], layoutCnt[m_layout], pData, size, &m_pInputLayout);
	if (FAILED(hr)) { return hr; }

	return hr;
}
//-----------------------------------------------------------------
//�s�N�Z���V�F�[�_�[�����N���X
//�R���X�g���N�^
PixelShader::PixelShader()
{
	m_pPixelShader = 0;
}
//�f�X�g���N�^
PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPixelShader);
}
//�w��̃s�N�Z���V�F�[�_�[�ݒ�
void PixelShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(m_pPixelShader, NULL, 0);
}
//�s�N�Z���V�F�[�_�[���N���A
void PixelShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(NULL, NULL, 0);
}
//�s�N�Z���V�F�[�_�[����
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, nullptr, &m_pPixelShader);
	if (FAILED(hr)) { return hr; }

	return hr;
}
//-----------------------------------------------------------------
//�o�b�t�@�����A�w��N���X
//�R���X�g���N�^
ShaderBuffer::ShaderBuffer()
	:m_pBuffer(NULL)
{
}
//�f�X�g���N�^
ShaderBuffer::~ShaderBuffer()
{
	SAFE_RELEASE(m_pBuffer);
}
//�o�b�t�@����
HRESULT ShaderBuffer::Create(UINT size)
{
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//--- ���_�o�b�t�@�̍쐬---
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, NULL, &m_pBuffer);
	return hr;
}
//�f�[�^���o�b�t�@�ɏ�������
void ShaderBuffer::Write(void* pData)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->UpdateSubresource(m_pBuffer, 0, NULL, pData, 0, 0);
}
//�w��̃X���b�g�Ƀo�b�t�@������
void ShaderBuffer::BindVS(UINT slot)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();
	
	pContext->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
void ShaderBuffer::BindPS(UINT slot)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();
	
	pContext->PSSetConstantBuffers(slot, 1, &m_pBuffer);
}

void ShaderBuffer::BindHS(UINT slot)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();

	pContext->HSSetConstantBuffers(slot, 1, &m_pBuffer);
}

void ShaderBuffer::BindDS(UINT slot)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();

	pContext->DSSetConstantBuffers(slot, 1, &m_pBuffer);
}
//�w��̃X���b�g�Ƀe�N�X�`��������
void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pTex);
}
//�w��̃X���b�g�Ƀe�N�X�`��������
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pTex);
}
//-----------------------------------------------------------------
//�n���V�F�[�_�[�����N���X
HullShader::HullShader()
{
	m_pHullShader = 0;
}

HullShader::~HullShader()
{
	SAFE_RELEASE(m_pHullShader)
}

void HullShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->HSSetShader(m_pHullShader, nullptr, 0);
}

void HullShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->HSSetShader(NULL, NULL, 0);
}

HRESULT HullShader::MakeShader(void * pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreateHullShader(pData, size, nullptr, &m_pHullShader);
	if (FAILED(hr)) { return hr; }

	return hr;
}
//-----------------------------------------------------------------
//�h���C���V�F�[�_�[�����N���X
DomainShader::DomainShader()
{
	m_pDomainShader = 0;
}

DomainShader::~DomainShader()
{
	SAFE_RELEASE(m_pDomainShader);
}

void DomainShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->DSSetShader(m_pDomainShader, nullptr, 0);
}

void DomainShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->DSSetShader(NULL, NULL, 0);
}

HRESULT DomainShader::MakeShader(void * pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreateDomainShader(pData, size, nullptr, &m_pDomainShader);
	if (FAILED(hr)) { return hr; }

	return hr;
}
