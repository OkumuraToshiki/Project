/*===========================================================================
  @file   Player.h
  @brief  �v���C���[�Ǘ�
  @author �����r�I
  @date   2021/08/28
===========================================================================*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "VectorClass.h"
#include "Box.h"
#include "light.h"

class CFbxModel;
/*===========================================================================
   �v���C���[�N���X
===========================================================================*/
class PlayerClass
{
private:
	Vector3f  m_Pos;
	Vector3f  m_Move;
	Vector3f  m_Size;
	XMFLOAT4X4 m_World;

	CFbxModel*    m_pModel;
	LightClass    m_Light;
	Vector3f      m_vCenter;     // ���E�{�b�N�X���S���W
	Vector3f      m_vBBox;       // ���E�{�b�N�X �T�C�Y
	BoxClass*      m_box;         // ���E�{�b�N�X�\��
	Vector3f      m_vPosBBox;    // ���E�{�b�N�X���S���W(���[���h���)
	bool          m_bCanJump;
	bool          m_bIsHit;

public:
	PlayerClass() = default;
	PlayerClass(Vector3f _pos, LightClass _light);
	~PlayerClass();
	HRESULT Init();
	void    Uninit();
	void    Update();
	void    Draw();
private:
	bool canJump();
};
#endif // !_PLAYER_H_