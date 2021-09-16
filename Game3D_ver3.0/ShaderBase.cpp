/*===========================================================================
  @file   ShaderBase.h
  @brief  シェーダー生成
  @author HAL名古屋
  @date   2021/09/16
===========================================================================*/
#include "ShaderBase.h"
#include "main.h"

//-----------------------------------------------------------------
//読み込み・作成のベース用クラス
//コンストラクタ
ShaderBase::ShaderBase()
{
}
//デストラクタ
ShaderBase::~ShaderBase()
{
}
//csoからシェーダー作成
HRESULT ShaderBase::Create(const char* FileName)
{
	HRESULT hr = E_FAIL;

	FILE *fp = NULL;
	fopen_s(&fp, FileName, "rb");
	if (fp == nullptr) { return hr; }

	// ファイルサイズ
	UINT size = 0;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);

	// データ読み込み
	fseek(fp, 0L, SEEK_SET);
	BYTE *pData = new BYTE[size];
	fread_s(pData, size, size, 1, fp);
	fclose(fp);

	// シェーダ作成
	hr = MakeShader(pData, size);

	delete[] pData;
	return hr;
}
//-----------------------------------------------------------------
//頂点シェーダー生成クラス
//コンストラクタ
VertexShader::VertexShader(Layout layout)
	: m_pInputLayout(nullptr)
	, m_layout(layout)
{
}
//デストラクタ
VertexShader::~VertexShader()
{
	
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
	
}
//指定の頂点シェーダーを設定
void VertexShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetShader(m_pVertexShader, NULL, 0);
	pContext->IASetInputLayout(m_pInputLayout);
}
//頂点シェーダーをクリア
void VertexShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->VSSetShader(NULL, NULL, 0);
	
}
//シェーダーを生成、レイアウト指定
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

	// シェーダ生成
	hr = pDevice->CreateVertexShader(pData, size, nullptr, &m_pVertexShader);
	if (FAILED(hr)) { return hr; }

	// 頂点レイアウト作成
	hr = pDevice->CreateInputLayout(pLayout[m_layout], layoutCnt[m_layout], pData, size, &m_pInputLayout);
	if (FAILED(hr)) { return hr; }

	return hr;
}
//-----------------------------------------------------------------
//ピクセルシェーダー生成クラス
//コンストラクタ
PixelShader::PixelShader()
{
	m_pPixelShader = 0;
}
//デストラクタ
PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPixelShader);
}
//指定のピクセルシェーダー設定
void PixelShader::Bind()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(m_pPixelShader, NULL, 0);
}
//ピクセルシェーダーをクリア
void PixelShader::Clear()
{
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->PSSetShader(NULL, NULL, 0);
}
//ピクセルシェーダー生成
HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(pData, size, nullptr, &m_pPixelShader);
	if (FAILED(hr)) { return hr; }

	return hr;
}
//-----------------------------------------------------------------
//バッファ生成、指定クラス
//コンストラクタ
ShaderBuffer::ShaderBuffer()
	:m_pBuffer(NULL)
{
}
//デストラクタ
ShaderBuffer::~ShaderBuffer()
{
	SAFE_RELEASE(m_pBuffer);
}
//バッファ生成
HRESULT ShaderBuffer::Create(UINT size)
{
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//--- 頂点バッファの作成---
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, NULL, &m_pBuffer);
	return hr;
}
//データをバッファに書き込み
void ShaderBuffer::Write(void* pData)
{
	assert(m_pBuffer);
	ID3D11DeviceContext* pContext = GetDeviceContext();
	pContext->UpdateSubresource(m_pBuffer, 0, NULL, pData, 0, 0);
}
//指定のスロットにバッファを入れる
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
//指定のスロットにテクスチャを入れる
void SetTextureVS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetDeviceContext()->VSSetShaderResources(slot, 1, &pTex);
}
//指定のスロットにテクスチャを入れる
void SetTexturePS(ID3D11ShaderResourceView* pTex, UINT slot)
{
	GetDeviceContext()->PSSetShaderResources(slot, 1, &pTex);
}
//-----------------------------------------------------------------
//ハルシェーダー生成クラス
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
//ドメインシェーダー生成クラス
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
