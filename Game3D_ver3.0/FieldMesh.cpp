/*===========================================================================
  @file    FieldMesh.cpp
  @brief  �t�B�[���h�`��
  @author �����r�I
  @date   2021/09/09
===========================================================================*/
#include "FieldMesh.h"
#include "Texture.h"
#include "FileName.hpp"
/*===========================================================================
  �萔��`
===========================================================================*/
namespace {
	const int nNumBlockX = 100;
	const int nNumBlockZ = 100;
	const float fSizeBlockX = 1.0f;
	const float fSizeBlockZ = 1.0f;
}
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
FieldMeshClass::FieldMeshClass()
{
	HRESULT hr;
	// �ʒu�A�����̏����ݒ�
	m_Mesh.pos = XMFLOAT3(0.0f, -0.2f, 0.0f);
	m_Mesh.rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Mesh.primitiveType = PT_TRIANGLESTRIP;
	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(GetDevice(),
		pszTexPath[TEXTURE_FIELD],
		&m_Mesh.pTexture);
	if (FAILED(hr))MessageBox(GetMainWnd(), "Texture�G���[", "FieldMesh", MB_OK | MB_ICONEXCLAMATION);
	XMStoreFloat4x4(&m_Mesh.mtxTexture, XMMatrixIdentity());
	hr = MakeVertexField();
	if (FAILED(hr))MessageBox(GetMainWnd(), "���_�����G���[", "FieldMesh", MB_OK | MB_ICONEXCLAMATION);
}
/*===========================================================================
  �f�X�g���N�^
===========================================================================*/
FieldMeshClass::~FieldMeshClass()
{
	ReleaseMesh(&m_Mesh);
}
/*===========================================================================
  �X�V
===========================================================================*/
void FieldMeshClass::Update()
{
	UpdateMesh(&m_Mesh);
}
/*===========================================================================
  �`��
===========================================================================*/
void FieldMeshClass::Draw(LightClass* pLight)
{
	DrawMesh(GetDeviceContext(), &m_Mesh, pLight);
}
/*===========================================================================
  ���_�̍쐬
===========================================================================*/
HRESULT FieldMeshClass::MakeVertexField()
{
	// ���_���̐ݒ�
	m_Mesh.nNumVertex = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// �C���f�b�N�X���̐ݒ�
	m_Mesh.nNumIndex = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// �ꎞ�I�Ȓ��_�z��̍쐬
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_Mesh.nNumVertex];

	// ���_�z��̒��g�𖄂߂�
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
			// ���_���W�̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.x = -(nNumBlockX / 2.0f) * fSizeBlockX + nCntVtxX * fSizeBlockX;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].vtx.z = (nNumBlockZ / 2.0f) * fSizeBlockZ - nCntVtxZ * fSizeBlockZ;

			// �@���̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].nrm = XMFLOAT3(0.0f, 1.0, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (nNumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// �ꎞ�I�ȃC���f�b�N�X�z�񐶐�
	int* pIndexWk = new int[m_Mesh.nNumIndex];

	//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < nNumBlockZ; ++nCntVtxZ) {
		if (nCntVtxZ > 0) {
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
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
			// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
			pIdx[nCntIdx] = nCntVtxZ * (nNumBlockX + 1) + nNumBlockX;
			nCntIdx++;
		}
	}

	HRESULT hr = MakeMeshVertex(GetDevice(), &m_Mesh, pVertexWk, pIndexWk);

	// �ꎞ�z��̉��
	delete[] pIndexWk;
	delete[] pVertexWk;

	return hr;
}