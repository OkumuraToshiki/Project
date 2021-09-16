/*===========================================================================
  @file   Enemy.h
  @brief  エネミー管理
  @author 奥村俊紀
  @date   2021/09/01
===========================================================================*/
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "VectorClass.h"
#include "Box.h"
#include "light.h"
class CAssimpModel;
/*===========================================================================
   エネミークラス
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
	static Vector3f         m_vCenter;     // 境界ボックス中心座標
	static Vector3f         m_vBBox;       // 境界ボックス サイズ
	static int              m_nRef;        //参照カウンタ
	LightClass*             m_Light;
	BoxClass*               m_box;         // 境界ボックス表示
	Vector3f                m_vPosBBox;    // 境界ボックス中心座標(ワールド空間)
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
