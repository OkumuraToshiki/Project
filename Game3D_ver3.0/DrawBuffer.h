/*===========================================================================
  @file   DrawBuffer.h
  @brief  ���_�A�C���f�b�N�X�o�b�t�@�[�ݒ�
  @author HAL���É�
  @date   2021/09/16
===========================================================================*/
#ifndef __DRAW_BUFFER_H__
#define __DRAW_BUFFER_H__

#include "main.h"
class DrawBuffer
{
public:
	DrawBuffer();
	~DrawBuffer();

	HRESULT CreateVertexBuffer(const void* pVtx, UINT size, UINT count,
		bool isWrite = false
	);
	HRESULT CreateIndexBuffer(const void* pIdx, UINT size, UINT count);
	void Draw(D3D11_PRIMITIVE_TOPOLOGY primitive);
	HRESULT Write(void* pVtx);
private:
	
	ID3D11Buffer* m_pVertexBuffer;         // ���_�o�b�t�@
	UINT          m_vtxSize;               // ���_�̃f�[�^�T�C�Y
	UINT          m_vtxCount;              // ���_�̐�
	ID3D11Buffer* m_pIndexBuffer;          // �C���f�b�N�X�o�b�t�@
	UINT          m_idxSize;               // �C���f�b�N�X�T�C�Y
	UINT          m_idxCount;              // �C���f�b�N�X�̐�
};
#endif // __DRAW_BUFFER_H__