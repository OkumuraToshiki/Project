/*===========================================================================
  @file   ShaderBuffer.h
  @brief  �V�F�[�_�[����
  @author HAL���É�
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
	//�R���X�g���N�^
	ShaderBufferTemplate(){
		m_buf.Create(sizeof(T));
	}
	//�f�X�g���N�^
	virtual ~ShaderBufferTemplate() {  }

	T* operator->() { return &m_data; }
	const T& operator=(const T& obj) { return m_data = obj; }
	
	//�X���b�g�ɑ}��
	void BindVS(UINT slot) { m_buf.Write(&m_data); m_buf.BindVS(slot); }
	void BindPS(UINT slot) { m_buf.Write(&m_data); m_buf.BindPS(slot); }
	void BindHS(UINT slot) { m_buf.Write(&m_data); m_buf.BindHS(slot); }
	void BindDS(UINT slot) { m_buf.Write(&m_data); m_buf.BindDS(slot); }
};
struct ShaderBufferData
{

};
#endif // !_SHADERBUFFER_H_