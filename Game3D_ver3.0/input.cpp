//=============================================================================
//
// ���͏��� [input.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "input.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�ő吔
#define NUM_JOY_MAX			(32)				// �Q�[���p�b�h�ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static HRESULT InitKeyboard();
static void UninitKeyboard();
static HRESULT UpdateKeyboard();

static HRESULT InitJoystick();
static void UninitJoystick();
static HRESULT UpdateJoystick();

static HRESULT InitMouse();
static void UninitMouse();
static HRESULT UpdateMouse();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static WORD				g_wKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
static WORD				g_wKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K��Ԃ�ێ����郏�[�N
static WORD				g_wKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��Ԃ�ێ����郏�[�N
static WORD				g_wKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��Ԃ�ێ����郏�[�N
static int				g_nKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

static DWORD			g_dwJoyCount;
static JOYINFOEX		g_joyState[NUM_JOY_MAX];
static DWORD			g_dwJoyButtonTrigger[NUM_JOY_MAX];
static DWORD			g_dwJoyButtonRelease[NUM_JOY_MAX];

static POINT			g_ptMouse;
static const int		g_nMouseBtn[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput()
{
	HRESULT hr = S_OK;

	// �L�[�{�[�h�̏�����
	hr = InitKeyboard();

	// �Q�[���p�b�h�̏�����
	if (SUCCEEDED(hr)) {
		hr = InitJoystick();
	}

	// �}�E�X�̏�����
	if (SUCCEEDED(hr)) {
		hr = InitMouse();
	}

	return hr;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput()
{
	// �}�E�X�̏I������
	UninitMouse();

	// �Q�[���p�b�h�̏I������
	UninitJoystick();

	// �L�[�{�[�h�̏I������
	UninitKeyboard();
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput()
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �Q�[���p�b�h�̍X�V
	UpdateJoystick();

	// �}�E�X�̍X�V
	UpdateMouse();
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT InitKeyboard()
{
	HRESULT hr = S_OK;

	return hr;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	// (�������Ȃ�)
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr = S_OK;
	WORD wKeyState;

	// �L�[�{�[�h�̏�Ԃ��擾
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) {
		wKeyState = GetAsyncKeyState(nCntKey);

		g_wKeyStateTrigger[nCntKey] = (g_wKeyState[nCntKey] ^ wKeyState) & wKeyState;
		g_wKeyStateRelease[nCntKey] = (g_wKeyState[nCntKey] ^ wKeyState) & ~wKeyState;
		g_wKeyStateRepeat[nCntKey] = g_wKeyStateTrigger[nCntKey];

		if (wKeyState & 0x8000) {
			g_nKeyStateRepeatCnt[nCntKey]++;
			if (g_nKeyStateRepeatCnt[nCntKey] >= 20) {
				g_wKeyStateRepeat[nCntKey] = wKeyState;
			}
		} else {
			g_nKeyStateRepeatCnt[nCntKey] = 0;
			g_wKeyStateRepeat[nCntKey] = 0;
		}

		g_wKeyState[nCntKey] = wKeyState;
	}

	return hr;
}

//=============================================================================
// �Q�[���p�b�h�̏���������
//=============================================================================
HRESULT InitJoystick()
{
	GetJoyCount();

	return S_OK;
}

//=============================================================================
// �Q�[���p�b�h�̏I������
//=============================================================================
void UninitJoystick()
{
	// (�������Ȃ�)
}

//=============================================================================
// �Q�[���p�b�h�̍X�V����
//=============================================================================
HRESULT UpdateJoystick()
{
	HRESULT hr = S_OK;

	for (DWORD i = 0; i < g_dwJoyCount; ++i) {
		JOYINFOEX& ji = g_joyState[i];
		DWORD dwButtons = ji.dwButtons;
		ZeroMemory(&ji, sizeof(ji));
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(i, &ji) != JOYERR_NOERROR) {
			hr = E_FAIL;
			break;
		}
		g_dwJoyButtonTrigger[i] = (g_joyState[i].dwButtons ^ dwButtons) & dwButtons;
		g_dwJoyButtonRelease[i] = (g_joyState[i].dwButtons ^ dwButtons) & ~dwButtons;
	}
	return hr;
}

//=============================================================================
// �}�E�X�̏���������
//=============================================================================
HRESULT InitMouse()
{
	return S_OK;
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void UninitMouse()
{
	// (�������Ȃ�)
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
HRESULT UpdateMouse()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(GetMainWnd(), &pt);
	g_ptMouse = pt;
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyPress(int nKey)
{
	return (g_wKeyState[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K��Ԃ��擾
//=============================================================================
bool GetKeyTrigger(int nKey)
{
	return (g_wKeyStateTrigger[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyRepeat(int nKey)
{
	return (g_wKeyStateRepeat[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyRelease(int nKey)
{
	return (g_wKeyStateRelease[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h�ڑ����擾
//=============================================================================
DWORD GetJoyCount()
{
	JOYINFO	ji;
	DWORD dwCount = joyGetNumDevs();
	if (dwCount > NUM_JOY_MAX)
		dwCount = NUM_JOY_MAX;
	for (g_dwJoyCount = 0; g_dwJoyCount < dwCount; ++g_dwJoyCount) {
		if (joyGetPos(g_dwJoyCount, &ji) != JOYERR_NOERROR)
			break;
	}
	return g_dwJoyCount;
}

//=============================================================================
// �Q�[���p�b�h���擾
//=============================================================================
JOYINFOEX *GetJoyState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return nullptr;
	return &g_joyState[dwJoy];
}

//=============================================================================
// �Q�[���p�b�hX���擾
//=============================================================================
LONG GetJoyX(DWORD dwJoy)
{
	if (g_dwJoyCount == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwXpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�hY���擾
//=============================================================================
LONG GetJoyY(DWORD dwJoy)
{
	if (g_dwJoyCount == 0)return 0L;
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwYpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�hZ���擾
//=============================================================================
LONG GetJoyZ(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)g_joyState[dwJoy].dwZpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�h �{�^�����擾
//=============================================================================
bool GetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_joyState[dwJoy].dwButtons & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h �g���K���擾
//=============================================================================
bool GetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_dwJoyButtonTrigger[dwJoy] & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h �����[�X���擾
//=============================================================================
bool GetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (g_dwJoyButtonRelease[dwJoy] & (1 << dwBtn)) ? true : false;
}
bool IsPressLeft()
{
	if (GetKeyPress(VK_A))return true;
	return false;
}
bool IsPressRight()
{
	if (GetKeyPress(VK_D))return true;
	return false;
}
bool IsPressUp()
{
	if (GetKeyPress(VK_W))return true;
	return false;
}
bool IsPressDown()
{
	if (GetKeyPress(VK_S))return true;
	return false;
}
Vector2f InputPlayerMove()
{
	Vector2f fMove(0.0f, 0.0f);
	if (IsPressRight() || GetJoyX(0) > 0)fMove.x =  1.0f;
	if (IsPressLeft()  || GetJoyX(0) < 0)fMove.x = -1.0f;
	if (IsPressUp()    || GetJoyY(0) > 0)fMove.y =  1.0f;
	if (IsPressDown()  || GetJoyY(0) < 0)fMove.y = -1.0f;
	fMove.Normalize();
	return fMove;
}

//=============================================================================
// �}�E�X���W�擾
//=============================================================================
POINT *GetMousePosition()
{
	return &g_ptMouse;
}

//=============================================================================
// �}�E�X �{�^�����擾
//=============================================================================
bool GetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyPress(g_nMouseBtn[dwBtn]);
}

//=============================================================================
// �}�E�X �g���K���擾
//=============================================================================
bool GetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyTrigger(g_nMouseBtn[dwBtn]);
}

//=============================================================================
// �}�E�X �����[�X���擾
//=============================================================================
bool GetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyRelease(g_nMouseBtn[dwBtn]);
}
//=============================================================================
// �}�E�X ���W���擾
//=============================================================================
XMFLOAT2 GetMousePos(void)
{
	POINT* posMouse = GetMousePosition();	// �}�E�X���W�擾�p
	XMFLOAT2 mousePos;						// �}�E�X���W�i�[�p

	// �}�E�X���W�擾
	posMouse = GetMousePosition();

	mousePos = XMFLOAT2(((float)posMouse->x - (float)SCREEN_CENTER_X), (float)SCREEN_CENTER_Y - (float)posMouse->y);

	return mousePos;
}
//=============================================================================
// �h���b�O�����擾
//=============================================================================
XMFLOAT2 GetDragDistance(DWORD dwBtn)
{
	XMFLOAT2 Start, End;
	if (GetMouseTrigger(dwBtn))
	{
		Start = GetMousePos();
		
	}
	if (GetMouseButton(dwBtn))
	{
		End = GetMousePos();
		return XMFLOAT2((End.x - Start.x), (End.y - Start.y));
	}
	return XMFLOAT2(0, 0);
}

//=============================================================================
// �}�E�X���W �|���S���͈͓��O����
//=============================================================================
bool IsMouseAreaClick(PolygonInfo poly, XMFLOAT2 mousePos)
{
	if (poly.fPos.x - poly.fSize.x*0.5f <= mousePos.x &&
		poly.fPos.x + poly.fSize.x*0.5f >= mousePos.x &&
		poly.fPos.y - poly.fSize.y*0.5f <= mousePos.y &&
		poly.fPos.y + poly.fSize.y*0.5f >= mousePos.y)
	{
		return true;
	}
	return false;
}