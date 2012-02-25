#ifndef _WAVELIB_H_
#define _WAVELIB_H_

#pragma comment(lib, "WaveLib.lib")
#include <windows.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define	F_WO_ACTIVE			0x0001
#define	F_WO_NEED_UPDATE	0002
#define	F_WO_EFFECT			0x0004
#define	F_WO_ELLIPSE		0x0008

typedef struct _WAVE_OBJECT
{
	HWND	hWnd;
	DWORD	dwFlag;// �� F_WO_xxx ���
//********************************************************************
	HDC	hDcRender;
	HBITMAP	hBmpRender;
	LPVOID		lpDIBitsSource; // ԭʼ��������
	LPVOID		lpDIBitsRender; // ������ʾ����Ļ����������
	LPVOID		lpWave1; // ˮ���������ݻ���1
	LPVOID		lpWave2; // ˮ���������ݻ���2
//********************************************************************
	DWORD	dwBmpWidth;
	DWORD	dwBmpHeight;
	DWORD	dwDIByteWidth;  //= (dwBmpWidth * 3 + 3) and ~3
	DWORD	dwWaveByteWidth; // = dwBmpWidth * 4
	DWORD	dwRandom;
//********************************************************************
// ��Ч����
//********************************************************************
	DWORD	dwEffectType;
	DWORD	dwEffectParam1;
	DWORD	dwEffectParam2;
	DWORD	dwEffectParam3;
//********************************************************************
// �����д���Ч
//********************************************************************
	DWORD	dwEff2X;
	DWORD	dwEff2Y;
	DWORD	dwEff2XAdd;
	DWORD	dwEff2YAdd;
	DWORD	dwEff2Flip;
//********************************************************************
	BITMAPINFO		stBmpInfo;
}WAVE_OBJECT, *LPWAVE_OBJECT;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
extern "C" 
{
 DWORD WINAPI _WaveDropStone(LPWAVE_OBJECT _lpWaveObject, 
	 DWORD _dwX,
	 DWORD _dwY,
	 DWORD _dwSize, 
	 DWORD _dwWeight);

 DWORD WINAPI _WaveEffect(LPWAVE_OBJECT _lpWaveObject,
			DWORD _dwType,
			DWORD _dwParam1,
			DWORD _dwParam2,
			DWORD _dwParam3);

 DWORD WINAPI _WaveFree(LPWAVE_OBJECT _lpWaveObject);

 DWORD WINAPI _WaveInit(LPWAVE_OBJECT _lpWaveObject,
			HWND _hWnd, 
			HBITMAP _hBmp,
			DWORD _dwSpeed,
			DWORD _dwType);
}

 inline BOOL WINAPI _Init(LPWAVE_OBJECT stlpWaveObj, HINSTANCE hInstance, HWND hWinMain, UINT uResID)
{
	BITMAP	stBmp = {0};
	RECT	stRect = {0};
	HBITMAP hBitMap = LoadBitmap(hInstance, MAKEINTRESOURCE(uResID));

	DWORD ret = _WaveInit(stlpWaveObj, hWinMain, hBitMap, 30, 0);


//********************************************************************
// װ����Դ�е�λͼ����ʼ��ˮ������
//********************************************************************

		if (ret)
		{
			return FALSE;
		}


		DeleteObject(hBitMap);
//********************************************************************
// �����ڴ�С������λͼ�Ĵ�С
//********************************************************************

		SetWindowPos(hWinMain,
			HWND_TOPMOST,
			0,
			0,
			stlpWaveObj->dwBmpWidth + 0,
			stlpWaveObj->dwBmpHeight + 0,
			SWP_NOMOVE);

		_WaveEffect(stlpWaveObj,1,4,3,50);

		return TRUE;
 }

 inline BOOL WINAPI _Init(LPWAVE_OBJECT stlpWaveObj, HINSTANCE hInstance, HWND hWinMain, HBITMAP hBitMap)
 {
	 BITMAP	stBmp = {0};
	 RECT	stRect = {0};
	 //HBITMAP hBitMap = LoadBitmap(hInstance, MAKEINTRESOURCE(uResID));

	 DWORD ret = _WaveInit(stlpWaveObj, hWinMain, hBitMap, 30, 0);


	 //********************************************************************
	 // װ����Դ�е�λͼ����ʼ��ˮ������
	 //********************************************************************

	 if (ret)
	 {
		 return FALSE;
	 }


	 DeleteObject(hBitMap);
	 //********************************************************************
	 // �����ڴ�С������λͼ�Ĵ�С
	 //********************************************************************

	 SetWindowPos(hWinMain,
		 HWND_TOPMOST,
		 0,
		 0,
		 stlpWaveObj->dwBmpWidth + 0,
		 stlpWaveObj->dwBmpHeight + 0,
		 SWP_NOMOVE);

	 _WaveEffect(stlpWaveObj,1,4,3,50);

	 return TRUE;
 }

#endif