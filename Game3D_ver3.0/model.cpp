//=============================================================================
//
// モデル処理 [model.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "model.h"
#include "main.h"
#include "FbxModel.h"
#include "input.h"
#include "debugproc.h"
#include "Camera.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_ICE01		"data/model/iceBall01.fbx"	// ファイル１
#define MODEL_ICE02		"data/model/iceBall02.fbx"	// ファイル２
#define VIEW_ANGLE		XMConvertToRadians(45.0f)
#define VIEW_ASPECT		((float)SCREEN_WIDTH/SCREEN_HEIGHT)
#define VIEW_NEAR_Z		(10.0f)
#define VIEW_FAR_Z		(1000.0f)

#define VALUE_MOVE		(5.0f)
#define VALUE_ROTATE	(XM_PI*0.02f)

#define LIGHT0_DIFFUSE	XMFLOAT4(1.f,0.0f,0.0f,1.2f)
#define LIGHT0_AMBIENT	XMFLOAT4(1.0f,1.0f,0.2f,1.2f)
#define LIGHT0_SPECULAR	XMFLOAT4(1.0f,1.0f,1.0f,1.2f)
#define LIGHT0_DIR		XMFLOAT3(0.2f,1.0f,10.0f)

// 構造体定義
typedef struct _tObject
{
	int			status;				// ステータス
	XMFLOAT3	pos;				// 座標
	XMFLOAT3	rot;				// 角度
	XMFLOAT3	scale;				// 拡大率
	XMMATRIX	matrix;				// 変換マトリックス
	int			morph_count;		// モーフィング計算用時間カウント値
	int			morph_dir;			// モーフィングの方向(0:順方向 1:逆方向)
	int			morph_time[2];		// モーフィングのキーフレーム

	int*		pIndex;				// インデックスバッファ保持用
	TFbxVertex*	pVertex[2];			// バーテックスバッファ保持用
	TFbxVertex*	pVertexWk;			// バーテックスバッファ作業用
	int			nVertex;			// 頂点数保持用
}tObject;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void InitLight(void);
//XMVECTOR Screenpos(XMVECTOR World_Pos);
XMVECTOR GetRay(XMVECTOR pos, float fRadius);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CFbxModel*			g_pModel;
XMFLOAT4X4			g_mtxWorld;

CFbxLight			g_light;

tObject				g_Object;	// モーフィングオブジェクト

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// カメラの初期化
	//InitCamera();

	// ライトの初期化
	InitLight();

	// 位置・回転・スケールの初期設定
	g_Object.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object.rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_Object.scale = XMFLOAT3(0.1f, 0.1f, 0.1f);

	// その他初期値
	g_Object.status = 0;
	g_Object.morph_time[0] = 0;	// １個めのモーフィング時間
	g_Object.morph_time[1] = 60;	// ２個めのモーフィング時間
	g_Object.morph_dir = 0;	// 順方向
	g_Object.morph_count = 0;
	g_Object.nVertex = 0;

	// FBXファイルの読み込み１
	g_pModel = new CFbxModel();
	hr = g_pModel->Init(pDevice, pDeviceContext, MODEL_ICE01);
	if (SUCCEEDED(hr)) {
		g_pModel->SetCamera(CCamera::Get()->GetEye());
		g_pModel->SetLight(g_light);
	}

	// 頂点配列、インデックス配列取得
	g_Object.nVertex = g_pModel->GetVertexCount();
	int nIndex = g_pModel->GetIndexCount();
	if (g_Object.nVertex <= 0 || nIndex <= 0) return E_FAIL;
	g_Object.pVertex[0] = new TFbxVertex[g_Object.nVertex];
	g_Object.pVertexWk = new TFbxVertex[g_Object.nVertex];
	g_Object.pIndex = new int[nIndex];
	if (g_pModel->GetVertex(g_Object.pVertex[0], g_Object.nVertex) != g_Object.nVertex
		|| g_pModel->GetIndex(g_Object.pIndex, nIndex) != nIndex) {
		delete[] g_Object.pIndex;
		delete[] g_Object.pVertex[0];
		delete[] g_Object.pVertexWk;
		return E_FAIL;
	}

	// FBXファイルの読み込み２
	CFbxModel* pModel = new CFbxModel();
	hr = pModel->Init(pDevice, pDeviceContext, MODEL_ICE02);
	if (FAILED(hr)) return hr;

	// 頂点配列、インデックス配列取得
	int nVertex = pModel->GetVertexCount();
	nIndex = pModel->GetIndexCount();
	if (nVertex <= 0 || nIndex <= 0) return E_FAIL;
	g_Object.pVertex[1] = new TFbxVertex[nVertex];
//	g_Object.pIndex = new int[nIndex];	// モデル１と同じはずなので用意しない
	if (pModel->GetVertex(g_Object.pVertex[1], nVertex) != nVertex
		|| pModel->GetIndex(g_Object.pIndex, nIndex) != nIndex) {
		delete[] g_Object.pIndex;
		delete[] g_Object.pVertex[0];
		delete[] g_Object.pVertex[1];
		delete[] g_Object.pVertexWk;
		return E_FAIL;
	}

	// データ取得用FBXファイルの解放
	SAFE_DELETE(pModel);

	return hr;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	// 頂点配列、インデックス配列解放
	delete[] g_Object.pIndex;
	delete[] g_Object.pVertex[0];
	delete[] g_Object.pVertex[1];
	delete[] g_Object.pVertexWk;

	// FBXファイルの解放
	SAFE_DELETE(g_pModel);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	if (GetKeyPress(VK_A)) {
		g_Object.rot.x -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_D)) {
		g_Object.rot.x += VALUE_ROTATE;
	}
	if (GetKeyPress(VK_W)) {
		g_Object.rot.z += VALUE_ROTATE;
	}
	if (GetKeyPress(VK_S)) {
		g_Object.rot.z -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_Q)) {
		g_Object.rot.y -= VALUE_ROTATE;
	}
	if (GetKeyPress(VK_E)) {
		g_Object.rot.y += VALUE_ROTATE;
	}

	// 状態変更
	if (GetKeyTrigger(VK_1))
	{
		g_Object.status = 0;
	}
	else if (GetKeyTrigger(VK_2))
	{
		g_Object.status = 1;
	}
	else if (GetKeyTrigger(VK_3))
	{
		g_Object.status = 2;
	}


	// 頂点情報の計算
	switch (g_Object.status)
	{
	case 0:
		memcpy_s(g_Object.pVertexWk, sizeof(TFbxVertex)*g_Object.nVertex, g_Object.pVertex[0], sizeof(TFbxVertex)*g_Object.nVertex);
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);
		g_Object.status += 10;
		break;
	case 1:
		memcpy_s(g_Object.pVertexWk, sizeof(TFbxVertex)*g_Object.nVertex, g_Object.pVertex[1], sizeof(TFbxVertex)*g_Object.nVertex);
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);
		g_Object.status += 10;
		break;
	case 2:
		// 進行割合を計算
		float ratio = (float)(g_Object.morph_count - g_Object.morph_time[0]) /
			(float)(g_Object.morph_time[1] - g_Object.morph_time[0]);
		// 頂点情報に反映
		for (int i = 0; i < g_Object.nVertex; i++)
		{
			g_Object.pVertexWk[i].vPos.x = g_Object.pVertex[0][i].vPos.x+
				(g_Object.pVertex[1][i].vPos.x- g_Object.pVertex[0][i].vPos.x)*ratio;
			g_Object.pVertexWk[i].vPos.y = g_Object.pVertex[0][i].vPos.y+
				(g_Object.pVertex[1][i].vPos.y - g_Object.pVertex[0][i].vPos.y)*ratio;
			g_Object.pVertexWk[i].vPos.z = g_Object.pVertex[0][i].vPos.z+
				(g_Object.pVertex[1][i].vPos.z - g_Object.pVertex[0][i].vPos.z)*ratio;
		}
		// 計算した頂点情報をセット
		g_pModel->SetVertex(g_Object.pVertexWk, g_Object.nVertex);

		// 往復の変更
		switch (g_Object.morph_dir)
		{
		case 0:
			g_Object.morph_count +=10;
			if (g_Object.morph_count >= g_Object.morph_time[1])
			{
				g_Object.morph_dir = 1;
			}
			
			break;
		case 1:
			g_Object.morph_count -=2;
			if (g_Object.morph_count <= g_Object.morph_time[0])
			{
				g_Object.morph_dir = 0;
			}
			
			break;
		}
		
		PrintDebugProc("MorphingCount:%d\n\n", g_Object.morph_count);
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	XMMATRIX mtxWorld, mtxScl, mtxRot, mtxTranslate;

	// ビューマトリックスの作成
	//XMStoreFloat4x4(&g_mtxView,
	//	XMMatrixLookAtLH(
	//		XMVectorSet(g_posCameraP.x, g_posCameraP.y, g_posCameraP.z, 1.0f),
	//		XMVectorSet(g_posCameraR.x, g_posCameraR.y, g_posCameraR.z, 1.0f),
	//		XMVectorSet(g_vecCameraU.x, g_vecCameraU.y, g_vecCameraU.z, 0.0f)));

	//// プロジェクションマトリックスの作成
	//XMStoreFloat4x4(&g_mtxProjection,
	//	XMMatrixPerspectiveFovLH(VIEW_ANGLE, VIEW_ASPECT, VIEW_NEAR_Z, VIEW_FAR_Z));

	// ワールドマトリックスの初期化
	mtxWorld = XMMatrixIdentity();

	// スケールを反映
	mtxScl = XMMatrixScaling(g_Object.scale.x, g_Object.scale.y, g_Object.scale.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

	// 回転を反映
	mtxRot = XMMatrixRotationRollPitchYaw(g_Object.rot.x, g_Object.rot.y, g_Object.rot.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

	// 移動を反映
	mtxTranslate = XMMatrixTranslation(g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

	// ワールドマトリックスの設定
	XMStoreFloat4x4(&g_mtxWorld, mtxWorld);

	// FBXファイル表示
	g_pModel->Render(g_mtxWorld, CCamera::Get()->GetView(), CCamera::Get()->GetProj(), eOpacityOnly);
	SetZWrite(false);
	g_pModel->Render(g_mtxWorld, CCamera::Get()->GetView(), CCamera::Get()->GetProj(), eTransparentOnly);
	SetZWrite(true);
}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	/*g_posCameraP = XMFLOAT3(POS_CAMERA_P_X, POS_CAMERA_P_Y, POS_CAMERA_P_Z);
	g_posCameraR = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_vecCameraU = XMFLOAT3(0.0f, 1.0f, 0.0f);*/
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	XMStoreFloat3(&g_light.m_direction, XMVector3Normalize(XMLoadFloat3(&LIGHT0_DIR)));
	g_light.m_diffuse = LIGHT0_DIFFUSE;
	g_light.m_ambient = LIGHT0_AMBIENT;
	g_light.m_specular = LIGHT0_SPECULAR;
}
