// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
#pragma once
#pragma warning( disable : 4142 4091 )
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Windows ヘッダーから使用されていない部分を除外します。
#endif
#define DIRECT3D_VERSION 0x900
#define DIRECTSOUND_VERSION 0x0900
#ifdef VLD_FORCE_ENABLE
//#include "vld.h"
#endif
#include <SDKDDKVer.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 一部の CString コンストラクターは明示的です。

// 一般的で無視しても安全な MFC の警告メッセージの一部の非表示を解除します。
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分

//#include <afxdisp.h>        // MFC オートメーション クラス



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC の Internet Explorer 4 コモン コントロール サポート
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable : 4995)

#define _AFX_DISABLE_DEPRECATED
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif
typedef double REFTIME;
#include "yaneCriticalSection.h"
/*
typedef PUINT DWORD_PTR
#include	<d3d8.h>
#include	<d3dx8.h>
#include <dxerr8.h>
#include <dmusici.h>    // DirectAudioを使用可能にする
*/

#include "kmp_pi.h"
#include "dshow.h"

#include <mmdeviceapi.h>
#include <endpointvolume.h>

struct playlistdata0{
	TCHAR name[1024];
	TCHAR art[1024];
	TCHAR alb[1024];
	TCHAR fol[1024];
	int sub;
	TCHAR game[256];
	int loop1;
	int loop2;
	int ret2;
	int icon;
	int time;
};

struct save{
	TCHAR ysf[1024];
	TCHAR ys6[1024];
	TCHAR ed6fc[1024];
	TCHAR ed6sc[1024];
	int douga;
	int supe;
	int supe2;

	int random;
	int kaisuu;
	int gameflg[4];

	int xx,yy;
	int gx,gy;

	TCHAR yso[1024];
	int gameflg2;

	TCHAR ed6tc[1024];
	int gameflg3;

	TCHAR zweiii[1024];
	int gameflg4;

	int dsvol;
	int render;

	TCHAR ysc[1024];
	int gameflg5;
	int gameflg6;

	TCHAR xa[1024];
	int gameflg7;

	TCHAR ys12[1024];
	int gameflg8;
	int gameflg9;

	TCHAR sor[1024];
	int gameflg10;
	TCHAR ys122[1024];

	TCHAR zwei[1024];
	int gameflg11;

	TCHAR gurumin[1024];
	int gameflg12;

	TCHAR dino[1024];
	int gameflg13;

	RECT p;

	TCHAR br4[1024];
	int gameflg14;

	TCHAR ed3[1024];
	int gameflg15;

	TCHAR ed4[1024];
	int gameflg16;

	TCHAR ed5[1024];
	int gameflg17;

	TCHAR tuki[1024];
	TCHAR nishi[1024];
	TCHAR arc[1024];
	TCHAR san1[1024];
	TCHAR san2[1024];

	int fs;
	int evr;
	int con;
	int aero;
	int pl;
	int ffd;
	int vob;
	int haali;
	int spc;
	int mp3;
	int kpivol;

	TCHAR font1[1024];
	TCHAR font2[1024];

	int mp3orig;

	int audiost;

	int savecheck;
	int savecheck_mp3;
	int savecheck_dshow;

	int bit24;

	int m4a;

	int kakuVol;
	int kakuVal;

	int saveloop;
	int saverenzoku;

	int bit32;

	int ms;
	int ms2;

	GUID soundguid;
	int soundcur;

	TCHAR zero[1024];

	DWORD samples;

	double wup;

	int aerocheck;

	int playlistnum;
	TCHAR playlistname[1000][256*2];

	int speanamode;
	int speananum;
};


char *b64_decode(char *s, int size,int &len);

int b64_ctoi(char c);

#define cmnh() 	CBrush m_brDlg; \
afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); \
afx_msg void OnMouseMove(UINT nFlags, CPoint point); \
afx_msg void OnLButtonDown(UINT nFlags, CPoint point); \
afx_msg void OnLButtonUp(UINT nFlags, CPoint point); \
virtual BOOL DestroyWindow(); \
afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); \
afx_msg void OnTimer(UINT_PTR nIDEvent); \
afx_msg BOOL OnNcActivate(BOOL bActive); \
afx_msg void OnMoving(UINT fwSide, LPRECT pRect); \
int m_bMoving1; \
CPoint m_pointOld1;
#include "ogg.h"
#include "oggDlg.h"
#include "PlayList.h"
#define cmn(xxx) 	ON_WM_CREATE()  \
ON_WM_MOUSEMOVE()  \
ON_WM_LBUTTONDOWN() \
ON_WM_MOVING() \
ON_WM_LBUTTONUP() \
ON_WM_CTLCOLOR()  \
ON_WM_TIMER() \
ON_WM_NCACTIVATE() \
END_MESSAGE_MAP() \
extern save savedata; \
extern CImageBase* Games; \
extern int gameon; \
extern int ip1; \
int xxx::OnCreate(LPCREATESTRUCT lpCreateStruct) \
{ \
	if (CDialog::OnCreate(lpCreateStruct) == -1) \
		return -1; \
	if (savedata.aero == 1) { \
		ModifyStyleEx(0, WS_EX_LAYERED); \
		SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY); \
		m_brDlg.CreateSolidBrush(RGB(255, 0, 0)); \
	} \
Games = NULL; \
	SetTimer(500, 100, NULL); \
    m_bMoving1 = 0; \
	return 0; \
} \
void xxx::OnMoving(UINT fwSide, LPRECT pRect) \
{ \
	CDialog::OnMoving(fwSide, pRect); \
	CRect r; \
	GetWindowRect(&r); \
	if (Games) \
		Games->MoveWindow(&r); \
} \
void xxx::OnLButtonDown(UINT nFlags, CPoint point) \
{ \
	m_bMoving1 = TRUE; \
	SetCapture(); \
	m_pointOld1 = point; \
	CDialog::OnLButtonDown(nFlags, point); \
} \
void xxx::OnLButtonUp(UINT nFlags, CPoint point) \
{ \
	if (m_bMoving1 == TRUE) { \
		m_bMoving1 = FALSE; \
		::ReleaseCapture(); \
	} \
	CDialog::OnLButtonUp(nFlags, point); \
} \
void xxx::OnMouseMove(UINT nFlags, CPoint point) \
{ \
	if (m_bMoving1 == TRUE) { \
		CRect rect; \
		GetWindowRect(&rect); \
		rect.left += (point.x - m_pointOld1.x); \
		rect.right += (point.x - m_pointOld1.x); \
		rect.top += (point.y - m_pointOld1.y); \
		rect.bottom += (point.y - m_pointOld1.y); \
		SetWindowPos(NULL, rect.left, rect.top, \
			rect.right - rect.left, rect.bottom - rect.top, \
			SWP_NOOWNERZORDER); \
		if (Games) \
			Games->MoveWindow(&rect); \
	} \
	CDialog::OnMouseMove(nFlags, point); \
} \
HBRUSH xxx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) \
{ \
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); \
	if (savedata.aero == 1) { \
		if (nCtlColor == CTLCOLOR_DLG) \
		{ \
			return m_brDlg; \
		} \
		if (nCtlColor == CTLCOLOR_STATIC) \
		{ \
			SetBkMode(pDC->m_hDC, TRANSPARENT); \
			return m_brDlg; \
		} \
	} \
	return hbr; \
} \
void xxx::OnTimer(UINT_PTR nIDEvent) \
{ \
    if(nIDEvent==500 && savedata.aero){ \
	KillTimer(500); \
    if(ip1 != 0) return; \
    if(Games == NULL){ \
	Games = new CImageBase; \
	Games->oya = this; \
	Games->Create(this); \
     } \
	CRect r; \
	GetWindowRect(&r); \
	if (Games) \
		Games->MoveWindow(&r); \
	if (Games) \
		::SetWindowPos(Games->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); \
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); \
    ip1 = 3; \
    SetTimer(501,10,NULL); \
    } \
    if(nIDEvent==501 && savedata.aero){ \
        ip1--; \
        if(ip1 <= 0){ ip1 = 0; KillTimer(501); }\
    } \
	CDialog::OnTimer(nIDEvent); \
} \
BOOL xxx::DestroyWindow() \
{ \
	if (Games){ \
		delete Games; \
    } \
    Games = NULL; \
	return CDialog::DestroyWindow(); \
} \
BOOL xxx::OnNcActivate(BOOL bActive) \
{ \
	SetTimer(500, 30, NULL); \
	return CDialog::OnNcActivate(bActive); \
} 




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。
