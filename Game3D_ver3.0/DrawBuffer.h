/*===========================================================================
  @file   DrawBuffer.h
  @brief  頂点、インデックスバッファー設定
  @author HAL名古屋
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
	
	ID3D11Buffer* m_pVertexBuffer;         // 頂点バッファ
	UINT          m_vtxSize;               // 頂点のデータサイズ
	UINT          m_vtxCount;              // 頂点の数
	ID3D11Buffer* m_pIndexBuffer;          // インデックスバッファ
	UINT          m_idxSize;               // インデックスサイズ
	UINT          m_idxCount;              // インデックスの数
};
#endif // __DRAW_BUFFER_H__