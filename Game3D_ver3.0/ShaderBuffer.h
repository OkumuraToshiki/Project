/*===========================================================================
  @file   ShaderBuffer.h
  @brief  シェーダー生成
  @author HAL名古屋
  @date   2021/09/16
===========================================================================*/
#ifndef _SHADERBUFFER_H_
#define _SHADERBUFFER_H_

#include "ShaderBase.h"
template <class T>
class MakeShaderBuffer
{
private:
	ShaderBuffer m_buf;
	T m_data;
public:
	//コンストラクタ
	ShaderBufferTemplate(){
		m_buf.Create(sizeof(T));
	}
	//デストラクタ
	virtual ~ShaderBufferTemplate() {  }

	T* operator->() { return &m_data; }
	const T& operator=(const T& obj) { return m_data = obj; }
	
	//スロットに挿入
	void BindVS(UINT slot) { m_buf.Write(&m_data); m_buf.BindVS(slot); }
	void BindPS(UINT slot) { m_buf.Write(&m_data); m_buf.BindPS(slot); }
	void BindHS(UINT slot) { m_buf.Write(&m_data); m_buf.BindHS(slot); }
	void BindDS(UINT slot) { m_buf.Write(&m_data); m_buf.BindDS(slot); }
};
struct ShaderBufferData
{

};
#endif // !_SHADERBUFFER_H_