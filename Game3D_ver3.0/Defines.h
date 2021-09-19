#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>

// ���\�[�X�p�X
#define ASSET(path)	"Assets/"path

// ���s�G���[
#define FnAssert(fn, str) do { _ASSERT_EXPR(SUCCEEDED(fn), _CRT_WIDE(str)); } while(0)

#endif // __DEFINES_H__