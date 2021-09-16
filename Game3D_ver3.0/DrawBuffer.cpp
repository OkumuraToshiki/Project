/*===========================================================================
  @file   DrawBuffer.h
  @brief  ���_�A�C���f�b�N�X�o�b�t�@�[�ݒ�
  @author HAL���É�
  @date   2021/09/16
===========================================================================*/
#include "DrawBuffer.h"
/*===========================================================================
  �R���X�g���N�^
===========================================================================*/
DrawBuffer::DrawBuffer()
	: m_pVertexBuffer(NULL), m_vtxSize(0), m_vtxCount(0)
	, m_pIndexBuffer(NULL), m_idxSize(0), m_idxCount(0)
{
}
/*===========================================================================
//�f�X�g���N�^
===========================================================================*/
DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pVertexBuffer);
}
/*===========================================================================
  ���_�o�b�t�@����
  @param pVtx ���_���
  @param size �T�C�Y
  @param pVtx ���_��
===========================================================================*/
HRESULT DrawBuffer::CreateVertexBuffer(const void* pVtx, UINT size, UINT count, bool isWrite)
{
	//--- �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	// �o�b�t�@�̑傫��
	bufDesc.ByteWidth =
		size * count;
	// �o�b�t�@�̎g�p���@
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	// �o�b�t�@�̗��p��
	bufDesc.BindFlags =
		D3D11_BIND_VERTEX_BUFFER;
	// �������ݎw��
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//�o�b�t�@�̏����l��ݒ�
	D3D11_SUBRESOURCE_DATA
		subResource = {};
	// �������Ɏg���f�[�^�̒u���ꏊ
	// �̎w��
	subResource.pSysMem = pVtx;

	//���_�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pVertexBuffer);

	//����ݒ�
	if (SUCCEEDED(hr))
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}
	return hr;
}
/*===========================================================================
  �C���f�b�N�X�o�b�t�@����
  @param pVtx �C���f�b�N�X���
  @param size �T�C�Y
  @param pVtx �C���f�b�N�X��
===========================================================================*/
HRESULT DrawBuffer::CreateIndexBuffer(const void* pIdx, UINT size, UINT count)
{
	// �o�b�t�@�̏���ݒ�
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// �o�b�t�@�̏����f�[�^
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	// �C���f�b�N�X�o�b�t�@����
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIndexBuffer);
	if (SUCCEEDED(hr))
	{
		m_idxSize = size;
		m_idxCount = count;
	}

	return hr;
}
/*===========================================================================
  �o�b�t�@�̒��g��`��
  @param primitive �|���S���̕`����@
===========================================================================*/
void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext* pContext =
		GetDeviceContext();
	// ���_�������̑傫��
	UINT stride = m_vtxSize;
	// ���_�f�[�^�̓ǂݎ��J�n�ʒu
	UINT offset = 0;

	pContext->IASetPrimitiveTopology(primitive);
	
	// �`��Ɏg�p����o�b�t�@�̐ݒ�
	pContext->IASetVertexBuffers(
		0, 1, 
		&m_pVertexBuffer, 
		&stride,
		&offset	
	);

	// �`��
	if (m_idxCount > 0)
	{
		// �`��Ɏg�p����C���f�b�N�X�o�b�t�@��ݒ�
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			m_idxSize == 4 ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT,
			0);

		// ���ޯ���ޯ̧���g�p���ĕ`��
		pContext->DrawIndexed(
			m_idxCount, 0, 0);
	}
	else
	{
		// ���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(m_vtxCount, 0);
	}

}
/*===========================================================================
  �o�b�t�@�R�s�[
===========================================================================*/
HRESULT DrawBuffer::Write(void* pVtx)
{
	HRESULT hr;
	ID3D11DeviceContext* pContext = GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;

	// �f�[�^�R�s�[
	hr = pContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (SUCCEEDED(hr))
	{
		rsize_t size = m_vtxCount * m_vtxSize;
		memcpy_s(mapResource.pData, size, pVtx, size);
		pContext->Unmap(m_pVertexBuffer, 0);
	}
	return hr;
}