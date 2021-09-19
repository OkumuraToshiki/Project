/*===========================================================================
  @file    FieldMesh.cpp
  @brief  フィールド描画
  @author 奥村俊紀
  @date   2021/09/09
===========================================================================*/
#include "FieldMesh.h"
#include "DrawBuffer.h"
#include "ShaderResource.h"
#include "Camera.h"
#include "FileName.hpp"
/*===========================================================================
  定数定義
===========================================================================*/
namespace {
	const int   nNumBlockX = 100;
	const int   nNumBlockZ = 100;
	const float fSizeBlockX = 1.0f;
	const float fSizeBlockZ = 1.0f;
}
/*===========================================================================
  コンストラクタ
===========================================================================*/
FieldMeshClass::FieldMeshClass() :m_pBuffer(new DrawBuffer()),
m_pShader(new ShaderResource(
	VertexShader::LAYOUT_PUNC, 
	"data/shader/TextureVS.cso", 
	"data/shader/TexturePS.cso"))
{
	HRESULT hr = S_OK;
	hr = CreateTextureFromFile(
		GetDevice(),
		pszTexPath[TEXTURE_FIELD],
		&m_pSRV);
	hr = MakeBuffer();
}
/*===========================================================================
  デストラクタ
===========================================================================*/
FieldMeshClass::~FieldMeshClass()
{
	SAFE_DELETE(m_pShader);
	SAFE_DELETE(m_pBuffer);
}
/*===========================================================================
  更新
===========================================================================*/
void FieldMeshClass::Update()
{
	
}
/*===========================================================================
  描画
===========================================================================*/
void FieldMeshClass::Draw(LightClass* pLight)
{
	m_pShader->Bind();
	m_DrawData.worldBuffer->world = XMMatrixTranspose(XMMatrixTranslation(0, 0, 0));
	m_DrawData.worldBuffer->view = XMMatrixTranspose(XMLoadFloat4x4(&CCamera::Get()->GetView()));
	m_DrawData.worldBuffer->proj = XMMatrixTranspose(XMLoadFloat4x4(&CCamera::Get()->GetProj()));
	m_DrawData.eyeBuffer = CCamera::Get()->GetEye();
	//printf("1");
	m_DrawData.worldBuffer.BindVS(0);
	SetTexturePS(m_pSRV, 0);
	//polygon描画
	m_pBuffer->Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
/*===========================================================================
  頂点の作成
===========================================================================*/
HRESULT FieldMeshClass::MakeBuffer()
{
	HRESULT hr;
	int m_nVertexCnt;
	int m_nIndexCnt;
	// 頂点数の設定
	m_nVertexCnt = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数の設定
	m_nIndexCnt = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// 一時的な頂点配列の作成
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_nVertexCnt];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
#if 1
	const float texSizeX = 1.0f / nNumBlockX;
	const float texSizeZ = 1.0f / nNumBlockZ;
#else
	const float texSizeX = 1.0f;
	const float texSizeZ = 1.0f;
#endif

	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockZ + 1; ++nCntVtxZ) {
		const float ANGLE = XM_2PI / nNumBlockX;

		for (int nCntVtxX = 0; nCntVtxX < nNumBlockX + 1; ++nCntVtxX) {
			// 頂点座標の設定
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.x = -(nNumBlockX / 2.0f) * fSizeBlockX + nCntVtxX * fSizeBlockX;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.z = (nNumBlockZ / 2.0f) * fSizeBlockZ - nCntVtxZ * fSizeBlockZ;

			// 法線の設定
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].nrm = XMFLOAT3(0.0f, 1.0, 0.0f);

			// 反射光の設定
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// 一時的なインデックス配列生成
	int* pIndexWk = new int[m_nIndexCnt];

	//インデックスバッファの中身を埋める
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockZ; ++nCntVtxZ) {
		if (nCntVtxZ > 0) {
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (nNumBlockX + 1);
			nCntIdx++;
		}

		for (int nCntVtxX = 0; nCntVtxX < nNumBlockX + 1; ++nCntVtxX) {
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (nNumBlockX + 1) + nCntVtxX;
			nCntIdx++;
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockX + 1) + nCntVtxX;
			nCntIdx++;
		}

		if (nCntVtxZ < nNumBlockZ - 1) {
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockX + 1) + nNumBlockX;
			nCntIdx++;
		}
	}

	hr = m_pBuffer->CreateVertexBuffer(pVertexWk, sizeof(VERTEX_3D), m_nVertexCnt);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = m_pBuffer->CreateIndexBuffer(pIndexWk, sizeof(unsigned long), m_nIndexCnt);
	if (FAILED(hr))
	{
		return hr;
	}
	// 一時配列の解放
	delete[] pIndexWk;
	delete[] pVertexWk;

	return hr;
}