/*===========================================================================
  @file   Box.h
  @brief  境界ボックス表示
  @author HAL名古屋
  @date   
===========================================================================*/
#ifndef _BOX_H_
#define _BOX_H_
#include "main.h"
class LightClass;
class BoxClass
{
private:
	ID3D11Buffer* m_pVertexBuffer;	// 頂点バッファ
	XMFLOAT4X4 m_world;
	XMFLOAT4 m_color;
	static ID3D11Buffer* m_pConstantBuffer[2];      // 定数バッファ
	static ID3D11VertexShader* m_pVertexShader;     // 頂点シェーダ
	static ID3D11InputLayout* m_pInputLayout;       // 頂点フォーマット
	static ID3D11PixelShader* m_pPixelShader;       // ピクセルシェーダ
	static ID3D11Buffer* m_pIndexBuffer;            // インデックスバッファ
	static int m_nRef;	// 参照カウンタ

public:
	BoxClass();
	~BoxClass();

	HRESULT Init(XMFLOAT3* pHalfSize);
	void Uninit();
	void Update();
	void Draw(LightClass& _light);

	XMFLOAT4X4& GetWorld() { return m_world; }
	void SetWorld(XMFLOAT4X4& world) { m_world = world; }
	XMFLOAT4& GetColor() { return m_color; }
	void SetColor(XMFLOAT4* pColor) { m_color = *pColor; }

};
#endif // !_BOX_H_