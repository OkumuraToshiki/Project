/*===========================================================================
  @file    FieldMesh.cpp
  @brief  フィールド描画
  @author 奥村俊紀
  @date   2021/09/09
===========================================================================*/
#include "FieldMesh.h"
#include "Texture.h"
#include "FileName.hpp"
/*===========================================================================
  定数定義
===========================================================================*/
namespace {
	const int nNumBlockX = 100;
	const int nNumBlockZ = 100;
	const float fSizeBlockX = 1.0f;
	const float fSizeBlockZ = 1.0f;
}
/*===========================================================================
  コンストラクタ
===========================================================================*/
FieldMeshClass::FieldMeshClass()
{
	HRESULT hr;
	// 位置、向きの初期設定
	m_Mesh.pos = XMFLOAT3(0.0f, -0.2f, 0.0f);
	m_Mesh.rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Mesh.primitiveType = PT_TRIANGLESTRIP;
	// テクスチャの読み込み
	hr = CreateTextureFromFile(GetDevice(),
		pszTexPath[TEXTURE_FIELD],
		&m_Mesh.pTexture);
	if (FAILED(hr))MessageBox(GetMainWnd(), "Textureエラー", "FieldMesh", MB_OK | MB_ICONEXCLAMATION);
	XMStoreFloat4x4(&m_Mesh.mtxTexture, XMMatrixIdentity());
	hr = MakeVertexField();
	if (FAILED(hr))MessageBox(GetMainWnd(), "頂点生成エラー", "FieldMesh", MB_OK | MB_ICONEXCLAMATION);
}
/*===========================================================================
  デストラクタ
===========================================================================*/
FieldMeshClass::~FieldMeshClass()
{
	ReleaseMesh(&m_Mesh);
}
/*===========================================================================
  更新
===========================================================================*/
void FieldMeshClass::Update()
{
	UpdateMesh(&m_Mesh);
}
/*===========================================================================
  描画
===========================================================================*/
void FieldMeshClass::Draw(LightClass* pLight)
{
	DrawMesh(GetDeviceContext(), &m_Mesh, pLight);
}
/*===========================================================================
  頂点の作成
===========================================================================*/
HRESULT FieldMeshClass::MakeVertexField()
{
	// 頂点数の設定
	m_Mesh.nNumVertex = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数の設定
	m_Mesh.nNumIndex = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// 一時的な頂点配列の作成
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_Mesh.nNumVertex];

	// 頂点配列の中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
#if 0
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
	int* pIndexWk = new int[m_Mesh.nNumIndex];

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

	HRESULT hr = MakeMeshVertex(GetDevice(), &m_Mesh, pVertexWk, pIndexWk);

	// 一時配列の解放
	delete[] pIndexWk;
	delete[] pVertexWk;

	return hr;
}