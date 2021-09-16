/*===========================================================================
  @file   Enemy.h
  @brief  �G�l�~�[�Ǘ�
  @author �����r�I
  @date   2021/09/01
===========================================================================*/
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "VectorClass.h"
#include "Box.h"
#include "light.h"
class CAssimpModel;
/*===========================================================================
   �G�l�~�[�N���X
===========================================================================*/
class EnemyClass
{
private:
	Vector3f   m_Pos;
	Vector3f   m_Move;
	Vector3f   m_Rot;
	Vector3f   m_Size;
	XMFLOAT4X4 m_World;

	static CAssimpModel*    m_pModel;
	static Vector3f         m_vCenter;     // ���E�{�b�N�X���S���W
	static Vector3f         m_vBBox;       // ���E�{�b�N�X �T�C�Y
	static int              m_nRef;        //�Q�ƃJ�E���^
	LightClass*             m_Light;
	BoxClass*               m_box;         // ���E�{�b�N�X�\��
	Vector3f                m_vPosBBox;    // ���E�{�b�N�X���S���W(���[���h���)
	bool                    m_bCanJump;
	bool                    m_bIsHit;
public:
	EnemyClass() = default;
	EnemyClass(Vector3f _pos, LightClass*  _light);
	~EnemyClass();
	HRESULT Init();
	void    Uninit();
	void    Update();
	void    Draw();

};
#endif // !_ENEMY_H_
