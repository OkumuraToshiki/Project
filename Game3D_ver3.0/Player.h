/*===========================================================================
  @file   Player.h
  @brief  プレイヤー管理
  @author 奥村俊紀
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
   プレイヤークラス
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
	Vector3f      m_vCenter;     // 境界ボックス中心座標
	Vector3f      m_vBBox;       // 境界ボックス サイズ
	BoxClass*      m_box;         // 境界ボックス表示
	Vector3f      m_vPosBBox;    // 境界ボックス中心座標(ワールド空間)
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