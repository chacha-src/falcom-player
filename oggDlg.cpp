// oggDlg.cpp : インプリメンテーション ファイル
//
//#define _DLL
#include "stdafx.h"
int flacmode = 0;
#include "kmp_pi.h"
//#include "afxdll_.h"
#include "Dwmapi.h"
//#include "Shobjidl.h"
//#include <shlobj.h> 
//const GUID  IID_ITaskbarList3 = { 0xea1afb91,0x9e28,0x4b86,{0x90,0xe9,0x9e,0x9f,0x8a,0x5e,0xef,0xaf}} ;
//const GUID  IID_ICustomDestinationList = {0x6332debf,0x87b5,0x4670,{0x90,0xc0,0x5e,0x57,0xb4,0x08,0xa4,0x9e}};
//const CLSID CLSID_DestinationList ={ 0x77F10CF0, 0x3DB5, 0x4966, { 0xB5, 0x20, 0xB7, 0xC5, 0x4F, 0xD3, 0x5E, 0xD6 } };
//const CLSID CLSID_EnumerableObjectCollection = {0x2d3468c1,0x36a7,0x43b6,{0xac,0x24,0xd3,0xf0,0x2f,0xd9,0x60,0x7a}};
//#undef NTDDI_VERSION
//#define NTDDI_VERSION NTDDI_VERSION_FROM_WIN32_WINNT(NTDDI_WIN7)
#define INITGUID
#undef NO_SHLWAPI_STRFCNS
#define STRICT_TYPED_ITEMIDS 
#include <propkey.h>
#include <propvarutil.h>
#include "libmad\decoder.h"
#include "mp3info.h"
#include "ogg.h"
#include "oggDlg.h"
#include <math.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>
#include <MMSystem.h>
#include "dsound.h"
#include "Douga.h"
#include "itiran.h"
#include "itiran_FC.h"
#include "itiran_YSF.h"
#include "itiran_YS6.h"
#include "itiran_YSO.h"
#include "ED63rd.h"
#include "ZWEIII.h"
#include "YsC1.h"
#include "YsC2.h"
#include "XA.h"
#include "Ys12_1.h"
#include "Ys12_2.h"
#include "Sor.h"
#include "Zwei.h"
#include "Gurumin.h"
#include "Dino.h"
#include "Br4.h"
#include "ED3.h"
#include "ED4.h"
#include "ED5.h"
#include "TUKI.h"
#include "Nishi.h"
#include "Arc.h"
#include "San1.h"
#include "San2.h"
//#include "vfw.h"
#include "CImageBase.h"

#include <direct.h>
#include "Folder.h"
#include "Render.h"
#include "PlayList.h"
#include "Mp3Image.h"
#include "Kpilist.h"
#include "CInt24.h"
#include "ZeroFol.h"
int wavbit;
int wavsam = 16;
#include "Id3tagv1.h"
#include "Id3tagv2.h"
#include "mp3.h"
#include "OSVersion.h"
#include "codec/neaacdec.h"
#include "m4a.h"
#include "flac.h"
#include "dsd\dsd.h"
#include "opus.h"
#include <intrin.h>

#include <vector>
#include <algorithm>

bool ProcessAudioWithRubberBand(float tempoRate);
void ConvertRawBytesToFloat(const std::vector<uint8_t>& raw_data,
	uint16_t bits_per_sample, uint16_t channels,
	std::vector<float>& out_float_data);
void ConvertFloatToRawBytes(const std::vector<float>& float_data,
	uint16_t target_bits_per_sample, uint16_t channels,
	std::vector<uint8_t>& out_raw_data);
extern std::vector<float> m_convertedPcmFloatData;
extern std::vector<float> inputFloatData;
extern std::vector<uint8_t> m_bufwav3_1;
std::vector<uint8_t> m_bufwav3_2;


CImageBase* Games;

#pragma warning(push)
#pragma warning(disable : 4201)
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#pragma warning(pop)
#include <endpointvolume.h>
#include <FunctionDiscoveryKeys_devpkey.h>

static mp3 mp3_;
static m4a m4a_;
static flac flac_;
dsd dsd_;
opus opus_;

int readadpcm(CFile& adpcmf, char* bw, int len);
int readadpcmzwei(CFile& adpcmf, char* bw, int len);
int readadpcmgurumin(CFile& adpcmf, char* bw, int len);
int readadpcmarc(CFile& adpcmf, char* bw, int len);
BOOL wavwait, thend;
int wavch = 2;
int muon;
IMPLEMENT_DYNCREATE(CWread, CWinThread)
CWread::CWread() {}
CWread::~CWread() {}
BOOL CWread::InitInstance() { return TRUE; }
BEGIN_MESSAGE_MAP(CWread, CWinThread)
	ON_THREAD_MESSAGE(WM_APP + 100, wavread1)
END_MESSAGE_MAP()
void CWread::wavread1(WPARAM a, LPARAM b) {
	wavread(); thend = 1; wavwait = 1; AfxEndThread(0); return;
}

#define ID_HOTKEY0 8000
#define ID_HOTKEY1 8001
#define ID_HOTKEY2 8002
#define ID_HOTKEY3 8003

#include <eh.h>
#include "afxwin.h"
class SE_Exception
{
private:
	unsigned int nSE;
public:
	SE_Exception() {}
	SE_Exception(unsigned int n) : nSE(n) {}
	~SE_Exception() {}
	unsigned int getSeNumber() { return nSE; }
};
void trans_func(unsigned int, EXCEPTION_POINTERS*);
void trans_func(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	throw SE_Exception();
}

BOOL sflg = FALSE;
MMRESULT    mmRes;
HWAVEOUT    hwo;
CPlayList* pl = NULL;
CMp3Image* mi = NULL;
BOOL plw, miw;
extern TCHAR karento2[1024];
char kare[256];
extern COggDlg* og;
char cm[10000];
CCriticalSection2 cs;
CString fnn, stitle;
int stf;
int plf, hsc;
char* ogg, * wav;
CDC dc, * cdc0, dcsub;
CBitmap bmp, bmpsub;
float fade, fadeadd;
int mcnt, mcnt2, mcnt1, mcnt3, mcnt4, mcnt5, mcnt6;
char cm1[10000];
int wavbit2;
extern save savedata;
int spelv[400];
int spetm[400];
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int fade1, playf;
LPDIRECTSOUND8 m_ds;
LPDIRECTSOUNDBUFFER m_dsb1 = NULL;
LPDIRECTSOUNDBUFFER8 m_dsb = NULL;
LPDIRECTSOUND3DBUFFER m_dsb3d = NULL;

LPDIRECTSOUNDBUFFER m_p;
LPDIRECTSOUND3DBUFFER m_lpDS3DBuffer;
HANDLE hNotifyEvent[20];
LPDIRECTSOUNDNOTIFY dsnf1;
LPDIRECTSOUNDNOTIFY dsnf2;
UINT HandleNotifications(LPVOID lpvoid);
UINT WASAPIHandleNotifications(LPVOID lpvoid);
ULONG WAVDALen;
UINT WAVDAStartLen;

extern IMMDeviceEnumerator* deviceEnumerator;
extern IMMDeviceCollection* pDeviceCollection;
extern IMMDevice* pDevice;
extern IAudioClient* pAudioClient;
extern IAudioRenderClient* pRenderClient;

int randomno;
int playwavkpi(BYTE* bw, int old, int l1, int l2);
int readkpi(BYTE* bw, int cnt);
int playwavflac(BYTE* bw, int old, int l1, int l2);
int readflac(BYTE* bw, int cnt);
int playwavdsd(BYTE* bw, int old, int l1, int l2);
int readdsd(BYTE* bw, int cnt);
int playwavm4a(BYTE* bw, int old, int l1, int l2);
int readm4a(BYTE* bw, int cnt);
int playwavopus(BYTE* bw, int old, int l1, int l2);
int readopus(BYTE* bw, int cnt);
int playwavmp3(BYTE* bw, int old, int l1, int l2);
int readmp3(BYTE* bw, int cnt);
void playwavds2(BYTE* bw, int old, int l1, int l2);
BOOL playwavadpcm(BYTE* bw, int old, int l1, int l2);
//スレッド
UINT wavread(LPVOID);
extern BYTE bufimage[0x30000f];

CString extn;
int ogpl0 = 0;
/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ
extern void DoEvent();
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

	// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_in;
	virtual BOOL OnInitDialog();
	CLinkStatic m_link;
	CStatic m_cpu;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_STATICin, m_in);
	DDX_Control(pDX, IDC_Link, m_link);
	DDX_Control(pDX, IDC_STATICin2, m_cpu);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
double aa1_ = 0;
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	COSVersion os;
	CString s;
	s.Format(_T("%s"), os.GetVersionString());

	m_in.SetWindowText(s);


	char CPUBrandString[0x40];
	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 0x80000002);
	memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	s = CPUBrandString;
	m_cpu.SetWindowText(s);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

/////////////////////////////////////////////////////////////////////////////
// COggDlg ダイアログ

COggDlg::COggDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COggDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COggDlg)
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void COggDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COggDlg)
	DDX_Control(pDX, IDC_CHECK15, m_ysc2);
	DDX_Control(pDX, IDC_CHECK14, m_ysc1);
	DDX_Control(pDX, IDC_STATICds, m_dsvols);
	DDX_Control(pDX, IDC_SLIDER3, m_dsval);
	DDX_Control(pDX, IDC_CHECK13, m_zweiii);
	DDX_Control(pDX, IDC_CHECK12, m_ed6tc);
	DDX_Control(pDX, IDC_CHECK11, m_yso);
	DDX_Control(pDX, IDC_SLIDER2, m_time);
	DDX_Control(pDX, IDC_EDIT1, m_kaisuu);
	DDX_Control(pDX, IDC_CHECK6, m_junji);
	DDX_Control(pDX, IDC_CHECK5, m_random);
	DDX_Control(pDX, IDC_BUTTON13, m_sita);
	DDX_Control(pDX, IDC_BUTTON12, m_ue);
	DDX_Control(pDX, IDC_CHECK10, m_ed6sc);
	DDX_Control(pDX, IDC_CHECK9, m_ed6fc);
	DDX_Control(pDX, IDC_CHECK8, m_ysf);
	DDX_Control(pDX, IDC_CHECK7, m_ys6);
	DDX_Control(pDX, IDC_CHECK4, m_st);
	DDX_Control(pDX, IDC_CHECK1, m_supe);
	DDX_Control(pDX, IDC_BUTTON3, m_ps);
	DDX_Control(pDX, IDC_STATIC2, m_vol);
	DDX_Control(pDX, IDC_SLIDER1, m_sl);
	DDX_Control(pDX, IDC_CHECK3, m_dou);
	DDX_Control(pDX, IDC_CHECK2, m_c2);
	DDX_Control(pDX, IDC_STATIC11, m_11);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK16, m_xa);
	DDX_Control(pDX, IDC_CHECK17, m_ys121);
	DDX_Control(pDX, IDC_CHECK18, m_ys122);
	DDX_Control(pDX, IDC_CHECK19, m_sor);
	DDX_Control(pDX, IDC_CHECK20, m_zwei);
	DDX_Control(pDX, IDC_CHECK21, m_gurumin);
	DDX_Control(pDX, IDC_BUTTON14, m_rund);
	DDX_Control(pDX, IDC_CHECK22, m_dino);
	DDX_Control(pDX, IDC_BUTTON4, m_saisai);
	DDX_Control(pDX, IDC_CHECK23, m_br4);
	DDX_Control(pDX, IDC_CHECK24, m_ed3);
	DDX_Control(pDX, IDC_CHECK25, m_ed4);
	DDX_Control(pDX, IDC_CHECK26, m_ed5);
	DDX_Control(pDX, IDC_BUTTON8, d_ys6);
	DDX_Control(pDX, IDC_BUTTON7, d_ys3);
	DDX_Control(pDX, IDC_BUTTON15, d_yso);
	DDX_Control(pDX, IDC_BUTTON6, d_ed6fc);
	DDX_Control(pDX, IDC_BUTTON2, d_ed6sc);
	DDX_Control(pDX, IDC_BUTTON17, d_ed6tc);
	DDX_Control(pDX, IDC_BUTTON19, d_z2);
	DDX_Control(pDX, IDC_BUTTON23, d_ysc1);
	DDX_Control(pDX, IDC_BUTTON24, d_ysc2);
	DDX_Control(pDX, IDC_BUTTON25, d_xa);
	DDX_Control(pDX, IDC_BUTTON27, d_ys1);
	DDX_Control(pDX, IDC_BUTTON28, d_ys2);
	DDX_Control(pDX, IDC_BUTTON31, d_sor);
	DDX_Control(pDX, IDC_BUTTON33, d_z1);
	DDX_Control(pDX, IDC_BUTTON35, d_guru);
	DDX_Control(pDX, IDC_BUTTON37, d_dino);
	DDX_Control(pDX, IDC_BUTTON39, d_br4);
	DDX_Control(pDX, IDC_BUTTON44, d_ed3);
	DDX_Control(pDX, IDC_BUTTON45, d_ed4);
	DDX_Control(pDX, IDC_BUTTON46, d_ed5);
	DDX_Control(pDX, IDC_BUTTON47, d_tuki);
	DDX_Control(pDX, IDC_BUTTON48, d_nishi);
	DDX_Control(pDX, IDC_BUTTON51, d_arc);
	DDX_Control(pDX, IDC_BUTTON53, d_san1);
	DDX_Control(pDX, IDC_BUTTON54, d_san2);
	DDX_Control(pDX, IDC_BUTTON57, m_playlist);
	DDX_Control(pDX, IDC_BUTTON58, m_mp3jake);
	DDX_Control(pDX, IDC_STATIC_OS, m_OS);
	DDX_Control(pDX, IDC_SLIDER4, m_kakuVol);
	DDX_Control(pDX, IDC_STATICds2, m_kakuVolval);
	DDX_Control(pDX, IDC_STATIC_OS2, m_cpu);
	DDX_Control(pDX, IDC_STATIC_OS3, m_os3);
	DDX_Control(pDX, IDC_STATIC_LRC, m_lrc);
	DDX_Control(pDX, IDC_SLIDER7, m_tempo_sl);
	DDX_Control(pDX, IDC_STATICds3, m_temp_num);
	DDX_Control(pDX, IDC_STATIC_LRC2, m_lrc2);
	DDX_Control(pDX, IDC_STATIC_LRC3, m_lrc3);
	DDX_Control(pDX, IDC_STATICds4, m_pitch);
	DDX_Control(pDX, IDC_SLIDER8, m_pitch_sl);
}

BEGIN_MESSAGE_MAP(COggDlg, CDialog)
	//{{AFX_MSG_MAP(COggDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnPause)
	ON_BN_CLICKED(IDC_BUTTON4, OnRestart)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6_FC)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7_YSF)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8_YS6)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9_Folder)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON15, OnYso)
	ON_BN_CLICKED(IDC_BUTTON17, OnButton17_ED6TC)
	ON_BN_CLICKED(IDC_BUTTON19, OnZWEIII)
	ON_BN_CLICKED(IDC_BUTTON21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON23, OnYsC1)
	ON_BN_CLICKED(IDC_BUTTON24, OnYsC2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON25, &COggDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON27, &COggDlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &COggDlg::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON31, &COggDlg::OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON33, &COggDlg::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON35, &COggDlg::OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON37, &COggDlg::OnBnClickedButton37)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &COggDlg::OnNMReleasedcaptureSlider2)
	ON_BN_CLICKED(IDC_BUTTON39, &COggDlg::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON44, &COggDlg::OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON45, &COggDlg::OnBnClickedButton45)
	ON_BN_CLICKED(IDC_BUTTON46, &COggDlg::OnBnClickedButton46)
	ON_BN_CLICKED(IDC_BUTTON47, &COggDlg::OnBnClickedButton47)
	ON_BN_CLICKED(IDC_BUTTON48, &COggDlg::OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON51, &COggDlg::OnBnClickedButton51)
	ON_BN_CLICKED(IDC_BUTTON53, &COggDlg::OnBnClickedButton53)
	ON_BN_CLICKED(IDC_BUTTON54, &COggDlg::OnBnClickedButton54)

	ON_MESSAGE(WM_APP + 1, dp1)
	ON_MESSAGE(WM_APP + 2, dp2)
	ON_WM_COPYDATA()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_ACTIVATE()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON57, &COggDlg::OnPlayList)
	ON_BN_CLICKED(IDC_BUTTON58, &COggDlg::OnBnmp3jake)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_MOVING()
	ON_WM_SETFOCUS()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_NCACTIVATE()
END_MESSAGE_MAP()

REFTIME aa1, aa2 = 0;


//FFT関連設定
// FFTライブラリ(fft4g.c)
#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)
	void rdft(int, int, double*, int*, double*);
	void ddst(int, int, double*, int*, double*);
#if defined(__cplusplus)
}
#endif // defined(__cplusplus)

//#define BUFSZ			(8192*4)
#define HIGHDIV			4
#define BUFSZH			(BUFSZ/HIGHDIV)
#define SQRT_BUFSZ2		64
#define M_PI			3.1415926535897932384
#define ABS(N)			( (N)<0 ? -(N) : (N) )

int ipTab2[2 + SQRT_BUFSZ2 * 50];		// FFT sin/cos table  [ >= 2+sqrt(BUFSZH/2) ]
double wTab2[BUFSZH * 50];		// FFT sin/cos table for ddst()
double aFFT2[BUFSZH * 50];			// FFT data
double aFFT2a[BUFSZH * 50];			// FFT data

double fnWFilter[BUFSZ / 2];
//double syuha[88] = { 27.500 ,29.135,30.868,32.703,34.648,36.708,38.891,41.203,43.654,46.249,48.999,51.913,55.000,58.270,61.735,65.406,69.296,73.416,77.782,82.407,87.307,92.499,97.999,103.826,110.000,116.541,123.471,130.813,138.591,146.832,155.563,164.814,174.614,184.997,195.998,207.652,220.000,233.082,246.942,261.626,277.183,293.665,311.127,329.628,349.228,369.994,391.995,415.305,440.000,466.164,493.883,523.251,554.365,587.330,622.254,659.255,698.456,739.989,783.991,830.609,880.000,932.328,987.767,1046.502,1108.731,1174.659,1244.508,1318.510,1396.913,1479.978,1567.982,1661.219,1760.000,1864.655,1975.533,2093.005,2217.461,2349.318,2489.016,2637.020,2793.826,2959.955,3135.963,3322.438,3520.000,3729.310,3951.066,4186.009 };
int			logtbl[100 + 1];
HFONT	hFont;
int mode, modesub;
int voldsf;
int timingf, timerf1;
int uTimerId;
void CALLBACK TimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
COggDlg* og;
static char* adbuf, * adbuf2;
BOOL thend1;
BOOL videoonly;
STARTUPINFO si;
PROCESS_INFORMATION pi;
int spc;
int killw1 = 0, ttt_;
CString ext[150][300];
CString kpif[400];
TCHAR kpifs[200][64];
BOOL kpichk[200];
int kpicnt;

/////////////////////////////////////////////////////////////////////////////
// COggDlg メッセージ ハンドラ
extern CString ndd;
ITaskbarList3* ptl;
ICustomDestinationList* pcdl;
IObjectCollection* poc;

int plcnt = 0;





BOOL COggDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == THBN_CLICKED) {
		UINT CommandID = LOWORD(wParam);
		if (0 == CommandID)
			OnRestart();
		else if (1 == CommandID)
			OnPause();
		else if (2 == CommandID)
			stop();
		else if (3 == CommandID)
			OnPlayList();
	}
	return CDialog::OnCommand(wParam, lParam);
}

void COggDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

#define MDC (88*2+170-8*5)*4
#define MDCP (88*2+175)*4

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

CImageBase* maini;
// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR COggDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void COggDlg::Resize()
{
	CString s;
	m_ue.GetWindowText(s);
	if (s == "▼") {
		m_ue.SetWindowText(_T("▲"));
		CRect rect_1, rect_2;
		GetWindowRect(&rect_1);
		m_ue.GetWindowRect(&rect_2);
		rect_1.bottom = rect_2.bottom + 3;
		rect_1.right = rect_2.right + 5;
		MoveWindow(&rect_1);
		if (maini)
			maini->MoveWindow(&rect_1);
	}
	else {
		m_ue.SetWindowText(_T("▼"));
		CRect rect_1, rect_2;
		GetWindowRect(&rect_1);
		m_sita.GetWindowRect(&rect_2);
		rect_1.bottom = rect_2.bottom + 3;
		rect_1.right = rect_2.right + 5;
		MoveWindow(&rect_1);
		if (maini)
			maini->MoveWindow(&rect_1);
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////M A I N/////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//PCMWAVEFORMAT fm;

/* WAVEファイルのヘッダ */
typedef struct {
	char ckidRIFF[4];
	int ckSizeRIFF;
	char fccType[4];
	char ckidFmt[4];
	int ckSizeFmt;
	PCMWAVEFORMAT WaveFmt;
	char ckidData[4];
	int ckSizeData;
} WAVEFILEHEADER;
WAVEFILEHEADER wh;

int mcopy(char* a, int len);
long LoadOggVorbis(const TCHAR* file_name, int word, char** ogg, CSliderCtrl& m_time);
void ReleaseOggVorbis(char**);
void DoEvent();
VOID CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
BOOL AllocOutputBuffer();
void FreeOutputBuffer(void);
void playwav();
void playwavds(char* bw);

CDouga* pMainFrame1 = NULL;
OggVorbis_File vf;
DWORD hw;
PCMWAVEFORMAT p;
CFile cc;
CString filen = _T("");
CSemaphore	m_Smp;

PCMWAVEFORMAT    wfx;
UINT ttt;
int cc1, wl, t, oggsize, dd, loop1, loop2;//,oggsize1,oggsize2;
__int64 playb;
int ru2 = 0, ru;
int lo, loc, endf, ps = 0, locs;
int poss = 0, poss2 = 0, poss3 = 0, poss4 = 0, poss5 = 0, poss6 = 0, loopcnt, pl_no;
int current_section;
long whsize;
int ret2;

//#define OUTPUT_BUFFER_NUM  10
//#define BUFSZ			(4096*6)
#define OUTPUT_BUFFER_SIZE  BUFSZ
#define BUFSZ1 (2048*8)
#define BUFSZH1			(BUFSZ1/HIGHDIV)
BYTE bufwav[OUTPUT_BUFFER_SIZE * 6];
BYTE buf[OUTPUT_BUFFER_NUM][OUTPUT_BUFFER_SIZE];
LPWAVEHDR  g_OutputBuffer[OUTPUT_BUFFER_NUM];
long data_size;

CString ti;
CString s, ss;
int tt = 0;
int killw;
ULONG PlayCursora, WriteCursora;
double oggsize2 = 0;
BYTE bufwav3[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 6];


char abuf[28];
char bbuf[2048];
ULONGLONG gp; int sep;
int lenl = 0;


WCHAR douga[2050];
extern IGraphBuilder* pGraphBuilder;
extern IMediaControl* pMediaControl;
extern IMediaPosition* pMediaPosition;
CString ply = _T("");
int plym = -1;

SOUNDINFO si1;
int kbps = 0;
int Vbr = 0;
DWORD cnt3 = 0;

int loop3;
CString tagname, tagfile, tagalbum;
int playy = 1;
void st1();
void st2();
int bufzero = 0;
extern 	int syukai;

int horizontalDPI;
int ms2;
int endflg = 0;

int tempo;
int pitch;
//////////////////////////////////////////////////////////////////////////////
BOOL COggDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ms2 = 0;
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	// Get desktop dc
	sflg = FALSE;
	CDC* desktopDc = GetDC();
	// Get native resolution
	horizontalDPI = GetDeviceCaps(desktopDc->m_hDC, LOGPIXELSX);
	hD = (float)(horizontalDPI) / (99.0f);
	if (hD < 1.02f) hD = 1.02f;
	hD /= 4.0f;
	SetStretchBltMode(dc.m_hDC, COLORONCOLOR);
	ReleaseDC(desktopDc);
	plw = 0;
	pi.dwProcessId = -1;
	randomf = 0; hsc = 0; spc = 0;
	wavbit = 44100; wavbit2 = 44100; wavch = 2;
	fade1 = 0;
	thend1 = TRUE;
	videoonly = FALSE;
	kpicnt = 0;
	kpi[0] = 0;
	mod = NULL; kmp = NULL;
	extn = "";
	mod = NULL;
	kmp = NULL;
	kmp1 = NULL;
	aa1_ = 0.0;
	hDLLk = NULL;
	mp3_.mp3init();





	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。
	fnn = "";
	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	//フォント設定
	LOGFONT LogFont;
	CClientDC dc1(this);
	dc1.GetCurrentFont()->GetLogFont(&LogFont);
	_tcscpy(LogFont.lfFaceName, _T("ＭＳ ゴシック"));
	LogFont.lfHeight = 16 * 4;
	LogFont.lfWidth = 8 * 4;
	LogFont.lfQuality = DRAFT_QUALITY;
	LogFont.lfWeight = FW_ULTRABOLD;
	hFont = CreateFontIndirect(&LogFont);
	/*	hFont = CreateFont(16,8,0,0,500,FALSE,FALSE,FALSE,
	SHIFTJIS_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
	DRAFT_QUALITY,FIXED_PITCH | FF_MODERN,
	_T("Arphic Gothic JIS"));
	if(hFont==NULL)
	hFont = CreateFont(16,8,0,0,500,FALSE,FALSE,FALSE,
	SHIFTJIS_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
	DRAFT_QUALITY,FIXED_PITCH  | FF_MODERN,
	_T("ＭＳ ゴシック"));
	*/

	ogg = NULL; wav = NULL; adbuf2 = NULL;
	plf = 0;
	timeBeginPeriod(1);
	SetTimer(5656, 2000, NULL);
	SetTimer(5657, 50, NULL);
	SetTimer(1233, 17, NULL);
	SetTimer(6555, 1200, NULL);
	SetTimer(9000, 10, NULL);
	timingf = timerf1 = 0;
	stf = 1;
	m_dou.SetCheck(1);
	// CG: 以下のブロックはツールヒント コンポーネントによって追加されました
	COSVersion os;
	DWORD edition;
	OSVERSIONINFOEX in;
	BOOL dumy;
	os.GetVersionInfo(in, edition, dumy);
	CString cpus;
	char CPUBrandString[0x40];
	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 0x80000002);
	memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	cpus = CPUBrandString;
	{
		// ツールヒント コントロールを作成します
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		// TODO: コントロールを追加するために以下のフォームの 1 つを使用してください:
		// m_tooltip.AddTool(GetDlgItem(IDC_<name>), <string-table-id>);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1), _T("演奏中のogg/wav/mp3/avi/kpiファイルを停止します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON2), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON6), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON7), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON8), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON15), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON17), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON19), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON25), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON23), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON24), _T("曲一覧表からoggを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON27), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON28), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON31), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON35), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON33), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON37), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON39), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON44), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON45), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON46), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON47), _T("曲一覧表からmp3を選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON48), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON51), _T("曲一覧表からwav(adp)を選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON53), _T("曲一覧表からwavを選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON54), _T("曲一覧表からmp3を選択し再生します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON57), _T("プレイリストを表示／非表示します。\n表示されている時に演奏を開始またはドロップで演奏するとリストに追加されます。\n非表示の時はリストには追加されません。\n本体へのドロップは1つだけでしたがプレイリストへのドロップは複数出来ます。"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON3), _T("演奏中のogg/wav/mp3/avi/kpiファイルを一時停止/再開します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON4), _T("演奏中だった曲を頭から再演奏します"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON5), _T("フェードアウトして停止します。(内蔵デコーダのみ)"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON9), _T("各ゲームのフォルダ位置を指定します"));
		m_tooltip.AddTool(GetDlgItem(IDOK), _T("簡易プレイヤを終了します"));
		m_tooltip.AddTool(GetDlgItem(IDC_SLIDER1), _T("音量を変更します\nWindows全体の音量が関係してきます。"));
		m_tooltip.AddTool(GetDlgItem(IDC_SLIDER3), _T("DirectSound音量を変更します\nこの簡易プレイヤのみの変更でとどまります。\nWindowsの音量は変化しません。"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK1), _T("スペクトルアナライザー(波形)を表示/非表示します"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK2), _T("演奏中の曲をwavで保存します"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK3), _T("動画(OPやイベント)のoggの時に動画画面も表示します"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK4), _T("スペクトルアナライザー(波形)をモノラル表示、ステレオ表示切り替えを行います"));

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON12), _T("拡張パネルを開く/閉じる"));

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON21), _T("各種設定を行います。"));

		m_tooltip.AddTool(GetDlgItem(IDC_CHECK5), _T("「再生するゲーム」で選択されているゲームをランダムに演奏します"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK6), _T("「再生するゲーム」で選択されているゲームを順番に演奏します"));

		m_tooltip.AddTool(GetDlgItem(IDC_CHECK7), _T("イース6 ナピシュテムの匣"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK8), _T("イース フェルガナの誓い"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK9), _T("空の軌跡 First Chapter"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK10), _T("空の軌跡 Second Chapter"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK11), _T("イース オリジン"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK12), _T("空の軌跡 The 3rd"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK13), _T("Zweii II"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK14), _T("YS I&&II Chronicles Ys 1"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK15), _T("YS I&&II Chronicles Ys 2"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK16), _T("XANADU NEXT"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK17), _T("Ys 完全版 Ys 1"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK18), _T("Ys 完全版 Ys 2"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK19), _T("Sorcerian Original"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK20), _T("Zwei!!"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK21), _T("ぐるみん"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK22), _T("ダイナソア リザレクション"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK23), _T("Brandish4 - ブランディッシュ4 眠れる神の塔"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK24), _T("英雄伝説III 白き魔女"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK25), _T("英雄伝説IV 朱紅い雫"));
		m_tooltip.AddTool(GetDlgItem(IDC_CHECK26), _T("英雄伝説V 海の檻歌"));
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTON58), _T("mp3/m4a/ogg/flacに埋め込まれているジャケットを表示します。"));

		m_tooltip.AddTool(GetDlgItem(IDC_EDIT1), _T("次の曲へいくためのループ回数を設定します"));

		m_tooltip.AddTool(GetDlgItem(IDC_SLIDER4), _T("100%以上の音量を設定できます"));
		m_tooltip.AddTool(GetDlgItem(IDC_STATICds2), _T("100%以上の音量を設定できます"));
		m_tooltip.AddTool(GetDlgItem(IDC_SLIDER7), _T("mp3,ogg,flac,m4a,opus,adpcm,dsd,kpiのテンポを変えます。wav,動画は変わりません。"));
		m_tooltip.AddTool(GetDlgItem(IDC_SLIDER8), _T("mp3,ogg,flac,m4a,opus,adpcm,dsd,kpiのピッチを変えます。wav,動画は変わりません。"));

		CString s;
		s.Format(_T("%s\n↑の情報が間違っている時は↓の内容を作者へ\n詳細：Ver %d.%d(%d) Build %d\n\n%s"), os.GetVersionString(), in.dwMajorVersion, in.dwMinorVersion, edition, in.dwBuildNumber, cpus);
		m_tooltip.AddTool(GetDlgItem(IDC_STATIC_OS), s);
		m_tooltip.AddTool(GetDlgItem(IDC_STATIC_OS2), s);
	}
	m_tooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);
	// FFT三角関数テーブルの初期化
	ipTab2[0] = 0;
	int i;
	// 窓関数テーブルの初期化
	for (i = 0; i < 15360; i++) {
		//fnWFilter[i/2] = (1-cos(2*M_PI*(i/2)/BUFSZ))/2; // Hanning窓
		fnWFilter[i] = 0.54f - 0.46f * (float)cos((2.0f * M_PI * i) / (i - 1));//sin(M_PI*(i + 0.5) / 4096); // sin窓
		//fnWFilter[i] = sin(syuha[i/47]/1000.0);
	}


	for (i = 0; i < 300; i++) { spelv[i] = 0; spetm[i] = 0; }
	fade = 1.0;
	fadeadd = 0.0;

	CString s;
	s.Format(_T("%d"), savedata.kaisuu);
	m_kaisuu.SetWindowText(s);

	//画面位置
	if (savedata.xx != -10000) {
		MoveWindow(savedata.xx, savedata.yy, 1, 1);
	}

	Resize();

	if (savedata.random) {
		m_junji.SetCheck(1);
		m_random.SetCheck(0);
	}
	else {
		m_junji.SetCheck(0);
		m_random.SetCheck(1);
	}
	m_ys6.SetCheck(savedata.gameflg[0]);
	m_ysf.SetCheck(savedata.gameflg[1]);
	m_ed6fc.SetCheck(savedata.gameflg[2]);
	m_ed6sc.SetCheck(savedata.gameflg[3]);
	m_yso.SetCheck(savedata.gameflg2);
	m_ed6tc.SetCheck(savedata.gameflg3);
	m_zweiii.SetCheck(savedata.gameflg4);
	m_ysc1.SetCheck(savedata.gameflg5);
	m_ysc2.SetCheck(savedata.gameflg6);
	m_xa.SetCheck(savedata.gameflg7);
	m_ys121.SetCheck(savedata.gameflg8);
	m_ys122.SetCheck(savedata.gameflg9);
	m_sor.SetCheck(savedata.gameflg10);
	m_zwei.SetCheck(savedata.gameflg11);
	m_gurumin.SetCheck(savedata.gameflg12);
	m_dino.SetCheck(savedata.gameflg13);
	m_br4.SetCheck(savedata.gameflg14);
	m_ed3.SetCheck(savedata.gameflg15);
	m_ed4.SetCheck(savedata.gameflg16);
	m_ed5.SetCheck(savedata.gameflg17);

	m_dsval.ShowWindow(SW_HIDE);
	m_dsval.SetRange(-498, 1);
	m_dsval.SetPos(-200);
	//	m_dsval.SetPos(savedata.dsvol);
	voldsf = 1;

	cdc0 = GetDC(); //new CClientDC(this);
	dc.CreateCompatibleDC(NULL);
	dcsub.CreateCompatibleDC(NULL);
	bmp.CreateCompatibleBitmap(cdc0, 2000, 1000);
	bmpsub.CreateCompatibleBitmap(cdc0, 5000, 100);
	dc.SelectObject(&bmp);
	dc.FillSolidRect(0, 0, 3000, 1000, RGB(0, 0, 0));
	dcsub.SelectObject(&bmpsub);
	dcsub.FillSolidRect(0, 0, 6000, 399, RGB(0, 0, 0));
	ReleaseDC(cdc0);
	mode = modesub = 0;
	m_supe.SetCheck(savedata.supe);
	m_st.SetCheck(savedata.supe2);
	mcnt = mcnt1 = mcnt2 = mcnt3 = mcnt4 = mcnt5 = mcnt6 = 0;
	m_time.SetRange(0, 1);
	m_time.SetSelection(0, 1);

	m_lpDS3DBuffer = NULL;
	if (WASAPIInit() == 0) init(GetSafeHwnd());


	RegisterHotKey(GetSafeHwnd(), ID_HOTKEY0, 0, VK_UP);
	RegisterHotKey(GetSafeHwnd(), ID_HOTKEY1, 0, VK_DOWN);
	RegisterHotKey(GetSafeHwnd(), ID_HOTKEY2, 0, VK_RIGHT);
	RegisterHotKey(GetSafeHwnd(), ID_HOTKEY3, 0, VK_LEFT);

	ptl = NULL;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void**)&ptl);
	if (ptl) {
		ptl->HrInit();
		ptl->SetProgressState(m_hWnd, TBPF_NOPROGRESS | TBPF_NORMAL);
		SetTimer(5219, 200, NULL);
	}
	pcdl = NULL;
	CoCreateInstance(CLSID_DestinationList, NULL, CLSCTX_INPROC_SERVER, IID_ICustomDestinationList, (void**)&pcdl);
	if (pcdl) {
		UINT cMinSlots;
		IObjectArray* poaRemoved;
		pcdl->BeginList(&cMinSlots, IID_PPV_ARGS(&poaRemoved));
		CoCreateInstance(CLSID_EnumerableObjectCollection, NULL, CLSCTX_INPROC, IID_PPV_ARGS(&poc));
		IShellLink* psl = NULL;
		_CreateShellLink(_T("*1"), _T("再演奏"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T("*2"), _T("一時停止"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T("*3"), _T("停止"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T(""), _T(""), &psl, 0, true, FALSE);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T("*4"), _T("プレイリスト開閉"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T(""), _T(""), &psl, 0, true, FALSE);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T("*5"), _T("レンダリング設定"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		_CreateShellLink(_T("*6"), _T("フォルダ設定"), &psl, 0, true);
		poc->AddObject(psl);	psl->Release();
		IObjectArray* poa; poc->QueryInterface(IID_PPV_ARGS(&poa));
		pcdl->AddUserTasks(poa); poa->Release();
		pcdl->CommitList(); poaRemoved->Release();
		poc->Release();
	}

	m_pDlgColor = NULL;



	//Windows7 / Vista用 ボリュームチェンジ
	deve = NULL; dev = NULL; audio = NULL;
	if (SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&deve))) {
		deve->GetDefaultAudioEndpoint(eRender, eConsole, &dev);
		dev->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&audio);
		float lv;
		audio->GetMasterVolumeLevelScalar(&lv);
		m_sl.SetRange(0, 100000);
		m_sl.SetPos((int)((float)lv * 100000.0f));
	}
	else {
		deve = NULL;
		m_sl.SetRange(0, 1000);
		m_sl.SetPos(600);
		DWORD vol = GetVol();
		union a {
			DWORD vol2;
			WORD b[2];
		} volu;
		volu.vol2 = vol;
		DWORD c = (DWORD)volu.b[0];
		float d = (float)c; d = d / 65535.0f;
		d = 1000.0f * d + 1.0f;
		m_sl.SetPos((int)d);
	}

	SetTimer(5211, 20, NULL);
	SetTimer(9998, 1000, NULL);
	Modec();


	m_tempo_sl.SetRange(50, 200);
	m_tempo_sl.SetPos(100);
	m_pitch_sl.SetRange(50, 200);
	m_pitch_sl.SetPos(100);
	tempo = 100;

	ttt_ = 5;
	//	uTimerId = timeSetEvent(1, 0, TimeCallback, NULL, TIME_PERIODIC);
#if WIN64
#else
	plug(karento2, NULL);
#endif	
	WAVEFORMATEX wfx1;
	wfx1.wFormatTag = WAVE_FORMAT_PCM;
	wfx1.nChannels = 2;
	wfx1.nSamplesPerSec = 48000;
	wfx1.wBitsPerSample = 24;
	wfx1.nBlockAlign = wfx1.nChannels * wfx1.wBitsPerSample / 8;
	wfx1.nAvgBytesPerSec = wfx1.nSamplesPerSec * wfx1.nBlockAlign;
	wfx1.cbSize = 0;

	waveOutOpen(&hwo, WAVE_MAPPER, &wfx1, NULL, NULL, CALLBACK_NULL);

	/////////////////////////////////

	s.Format(_T("%s"), os.GetVersionString());
	m_OS.SetWindowText(s);
	__cpuid(CPUInfo, 0x00000001);
	CString avx2;
	avx2 = "SSE2未対応";
	if (CPUInfo[0] >= 2) {
		__cpuid(CPUInfo, 0x00000001);
		if (CPUInfo[1] & (1 << 26))  avx2 = "SSE2対応";
		if (CPUInfo[2] & (1))  avx2 = "SSE3対応";
		if (CPUInfo[2] & (1 << 9))  avx2 = "SSSE3対応";
		if (CPUInfo[2] & (1 << 12))  avx2 = "FMA3対応";
		if (CPUInfo[2] & (1 << 19))  avx2 = "SSE4.1対応";
		if (CPUInfo[2] & (1 << 20))  avx2 = "SSE4.2対応";
	}
	if (CPUInfo[0] >= 2) {
		__cpuid(CPUInfo, 0x80000001);
		if (CPUInfo[2] & (1 << 6))  avx2 = "SSE4a対応";
	}
	__cpuid(CPUInfo, 0x00000001);
	if (CPUInfo[0] >= 2) {
		if (CPUInfo[2] & (1 << 28))  avx2 = "AVX対応";
	}
	if (CPUInfo[0] >= 7) {
		__cpuid(CPUInfo, 0x00000007);
		if (CPUInfo[1] & (1 << 5))  avx2 = "AVX2対応";
		if (CPUInfo[1] & (1 << 16))  avx2 = "AVX512対応";
	}
	s.Format(_T("%s / %s"), cpus, avx2);
	s.Trim();
	m_cpu.SetWindowText(s);

	// CPU 拡張命令一覧
	avx2 = L"使用可能命令：";
	__cpuid(CPUInfo, 0x00000001);
	if (CPUInfo[0] >= 2) {
		if (CPUInfo[3] & (1 << 23))  avx2 += "MMX ";
		if (CPUInfo[3] & (1 << 25))  avx2 += "SSE ";
		if (CPUInfo[3] & (1 << 26))  avx2 += "SSE2 ";
		if (CPUInfo[2] & (1))        avx2 += "SSE3 ";
		if (CPUInfo[2] & (1 << 9))   avx2 += "SSSE3 ";
		if (CPUInfo[2] & (1 << 12))  avx2 += "FMA3 ";
		if (CPUInfo[2] & (1 << 19))  avx2 += "SSE4.1 ";
		if (CPUInfo[2] & (1 << 20))  avx2 += "SSE4.2 ";
	}
	if (CPUInfo[0] >= 2) {
		__cpuid(CPUInfo, 0x80000001);
		if (CPUInfo[2] & (1 << 6))  avx2 += "SSE4a ";
	}
	__cpuid(CPUInfo, 0x00000001);
	if (CPUInfo[0] >= 2) {
		if (CPUInfo[2] & (1 << 28))  avx2 += "AVX ";
	}
	if (CPUInfo[0] >= 7) {
		__cpuid(CPUInfo, 0x00000007);
		if (CPUInfo[1] & (1 << 5))  avx2 += "AVX2 ";
		if (CPUInfo[1] & (1 << 16))  avx2 += "AVX512 ";
	}
	m_os3.SetWindowText(avx2);


	m_kakuVol.SetRange(100, 900);
	s.Format(_T("%3d"), savedata.kakuVal);
	m_kakuVolval.SetWindowText(s);
	m_kakuVol.SetPos(savedata.kakuVol);
	m_kakuVol.SetRange(100, 900);
	s.Format(_T("%3d"), savedata.kakuVal);
	m_kakuVolval.SetWindowText(s);
	m_kakuVol.SetPos(savedata.kakuVol);
	CKpilist kp;
	kp.status = 1;
	kp.Init();
	kp.Save();

	CFont* curFont;
	curFont = m_cpu.GetFont();
	LOGFONTW mylf;
	curFont->GetLogFont(&mylf);
	mylf.lfHeight = 16 * hD * 3;
	mylf.lfWidth = 7 * hD * 3;
	mylf.lfWeight = FW_NORMAL;
	m_newFont = new CFont;
	m_newFont->CreateFontIndirectW(&mylf);
	m_cpu.SetFont(m_newFont);

	curFont = m_os3.GetFont();
	curFont->GetLogFont(&mylf);
	mylf.lfHeight = 16 * hD * 3;
	mylf.lfWidth = 5 * hD * 3;
	mylf.lfWeight = FW_NORMAL;
	m_newFont1 = new CFont;
	m_newFont1->CreateFontIndirectW(&mylf);
	m_os3.SetFont(m_newFont1);

	//
	SetTimer(15011, 200, NULL);

	m_lrc.SetWindowText(L"");
	m_lrc2.SetWindowText(L"歌詞(.lrc)が表示されます");
	m_lrc3.SetWindowText(L"");
	lrc_backup = L"";
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}
//////////////////////////////////////////////////////////////////////////////
void COggDlg::OnPaint()
{
	CPaintDC dcc(this); // 描画用のデバイス コンテキスト
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dcc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dcc.DrawIcon(x, y, m_hIcon);
	}
	else
	{


		if (savedata.ms2 <= ms2) {
			SetStretchBltMode(dcc.m_hDC, COLORONCOLOR); //高画質モード
			SetBrushOrgEx(dcc.m_hDC, 0, 0, NULL); //ブラシのずれを防止
			dcc.StretchBlt(0, 0, (int)((MDCP)*hD), (int)((81 + 16) * hD * 4), &dc, 0, 0, MDCP + 5, (81 + 16) * 4, SRCCOPY);
			ms2 = 0;
		}
		///CDialog::OnPaint();
	}
}
BYTE offenc[7] = { 0xd9,0x3F,0x86,0x7B,0xC7,0x61,0xaa };
int oggf = 0;
// OggVorbisコールバック関数
size_t Callback_Read(
	void* ptr,
	size_t size,
	size_t nmemb,
	void* datasource
) {
	FILE* fp = (FILE*)datasource;
	if (oggf == 0) {
		__int64 iti = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		BYTE buf[2];
		fread(buf, 1, 1, fp);
		if (buf[0] == 0x4f)
			oggf = 1;
		else if (buf[0] == 0x04)
			oggf = 2;
		else if (buf[0] == 0x96)
			oggf = 3;
		fseek(fp, iti, SEEK_SET);
	}

	size_t ret = 0;
	if (oggf == 1)
		ret = fread(ptr, size, nmemb, fp);
	else if (oggf == 2) {
		ret = fread(ptr, size, nmemb, fp);
		size_t ret2 = ret * size;
		BYTE* b = (BYTE*)ptr;
		for (int i = 0; i < (int)ret2; i++) {
			b[i] = b[i] << 4 | b[i] >> 4;
			b[i] ^= 0x0f;
		}
	}
	else if (oggf == 3) {
		int len = ftell(fp);
		int len1 = len % 7;
		ret = fread(ptr, size, nmemb, fp);
		size_t ret2 = ret * size;
		BYTE* b = (BYTE*)ptr;
		for (int i = 0; i < (int)ret2; i++) {
			b[i] ^= offenc[len1];
			len1++; if (len1 > 6) len1 = 0;
		}
	}
	else {
		ret = 0;
	}

	return ret;

}

int Callback_Seek(
	void* datasource,
	ogg_int64_t offset,
	int whence
) {
	FILE* fp = (FILE*)datasource;
	return fseek(fp, offset, whence);
}

int Callback_Close(void* datasource) {
	oggf = 0;
	return 0;
}

long Callback_Tell(void* datasource) {
	FILE* fp = (FILE*)datasource;
	return ftell(fp);
}

ov_callbacks callbacks = {
	Callback_Read,
	Callback_Seek,
	Callback_Close,
	Callback_Tell
};




long LoadOggVorbis(const TCHAR* file_name, int word, char** ogg, CSliderCtrl& m_time)
{
	int eof = 0;
	oggf = 0;
	FILE* fp;
	long size = 0;
	vorbis_info* vi;

	/* 量子化バイト数が正しい値かどうか調べる */
	if (!(word == 1 || word == 2)) {
		return -1;
	}
	/* ファイルを開く */
	fp = _tfopen(file_name, _T("rb"));
	if (fp == NULL) {
		return -1;
	}
	/* OggVorbis初期化 */
	if (ov_open_callbacks(fp, &vf, NULL, 0, callbacks) < 0) {
		fprintf(stderr, "Input does not appear to be an Ogg bitstream.\n");
		fclose(fp);
		return -1;
	}
	else {
		vi = ov_info(&vf, -1);
	}

	/* ヘッダサイズの収得 */
	whsize = sizeof(wh.ckidRIFF) + sizeof(wh.ckSizeRIFF) + sizeof(wh.fccType) +
		sizeof(wh.ckidFmt) + sizeof(wh.ckSizeFmt) + sizeof(wh.WaveFmt) +
		sizeof(wh.ckidData) + sizeof(wh.ckSizeData);

	/* デコード後のデータサイズを求め、メモリ確保 */
	data_size = (long)ceil(vi->channels * vi->rate * ov_time_total(&vf, -1) * word);
	m_time.SetRange(0, (data_size) / 4, TRUE);
	dd = vi->channels * vi->rate * word;
	*ogg = (char*)malloc(whsize);
	if (ogg == NULL) {
		free(ogg);
		ov_clear(&vf);
		fclose(fp);
		return -1;
	}
	/* ヘッダの初期化 */
	memcpy(wh.ckidRIFF, "RIFF", 4);
	wh.ckSizeRIFF = whsize + size - 8;
	memcpy(wh.fccType, "WAVE", 4);
	memcpy(wh.ckidFmt, "fmt ", 4);
	wh.ckSizeFmt = sizeof(PCMWAVEFORMAT);

	//	wh.WaveFmt.cbSize          = sizeof(WAVEFORMATEX);
	wh.WaveFmt.wf.wFormatTag = WAVE_FORMAT_PCM;
	wh.WaveFmt.wf.nChannels = vi->channels;
	wavch = vi->channels;
	wavbit = vi->rate;
	wh.WaveFmt.wf.nSamplesPerSec = vi->rate;
	wh.WaveFmt.wf.nAvgBytesPerSec = vi->rate * vi->channels * word;
	wh.WaveFmt.wf.nBlockAlign = vi->channels * word;
	wh.WaveFmt.wBitsPerSample = word * 8;

	memcpy(wh.ckidData, "data", 4);
	wh.ckSizeData = size;

	/* メモリへのヘッダの書き込み */
	int s = 0;
	memcpy(*ogg, &wh.ckidRIFF, sizeof(wh.ckidRIFF));          s += sizeof(wh.ckidRIFF);
	memcpy(*ogg + s, &wh.ckSizeRIFF, sizeof(wh.ckSizeRIFF));  s += sizeof(wh.ckSizeRIFF);
	memcpy(*ogg + s, &wh.fccType, sizeof(wh.fccType));        s += sizeof(wh.fccType);
	memcpy(*ogg + s, &wh.ckidFmt, sizeof(wh.ckidFmt));        s += sizeof(wh.ckidFmt);
	memcpy(*ogg + s, &wh.ckSizeFmt, sizeof(wh.ckSizeFmt));    s += sizeof(wh.ckSizeFmt);
	memcpy(*ogg + s, &wh.WaveFmt, sizeof(wh.WaveFmt));        s += sizeof(wh.WaveFmt);
	memcpy(*ogg + s, &wh.ckidData, sizeof(wh.ckidData));      s += sizeof(wh.ckidData);
	memcpy(*ogg + s, &wh.ckSizeData, sizeof(wh.ckSizeData));

	return data_size;// + whsize;
}

void wav_start();
void wav_start()
{
	whsize = sizeof(wh.ckidRIFF) + sizeof(wh.ckSizeRIFF) + sizeof(wh.fccType) +
		sizeof(wh.ckidFmt) + sizeof(wh.ckSizeFmt) + sizeof(wh.WaveFmt) +
		sizeof(wh.ckidData) + sizeof(wh.ckSizeData);

	/* デコード後のデータサイズを求め、メモリ確保 */
	wav = (char*)malloc(whsize);
	/* ヘッダの初期化 */
	memcpy(wh.ckidRIFF, "RIFF", 4);
	memcpy(wh.fccType, "WAVE", 4);
	memcpy(wh.ckidFmt, "fmt ", 4);
	wh.ckSizeFmt = sizeof(PCMWAVEFORMAT);

	//	wh.WaveFmt.cbSize          = sizeof(WAVEFORMATEX);
	wh.WaveFmt.wf.wFormatTag = WAVE_FORMAT_PCM;
	wh.WaveFmt.wf.nChannels = wavch;
	wh.WaveFmt.wf.nSamplesPerSec = wavbit;
	wh.WaveFmt.wBitsPerSample = wavsam;
	wh.WaveFmt.wf.nBlockAlign = wh.WaveFmt.wf.nChannels * wh.WaveFmt.wBitsPerSample / 8;
	wh.WaveFmt.wf.nAvgBytesPerSec = wh.WaveFmt.wf.nSamplesPerSec * wh.WaveFmt.wf.nBlockAlign;
	wh.ckSizeFmt = 16;
	memcpy(wh.ckidData, "data", 4);

	/* メモリへのヘッダの書き込み */
	int s = 0;
	memcpy(wav, &wh.ckidRIFF, sizeof(wh.ckidRIFF));          s += sizeof(wh.ckidRIFF);
	memcpy(wav + s, &wh.ckSizeRIFF, sizeof(wh.ckSizeRIFF));  s += sizeof(wh.ckSizeRIFF);
	memcpy(wav + s, &wh.fccType, sizeof(wh.fccType));        s += sizeof(wh.fccType);
	memcpy(wav + s, &wh.ckidFmt, sizeof(wh.ckidFmt));        s += sizeof(wh.ckidFmt);
	memcpy(wav + s, &wh.ckSizeFmt, sizeof(wh.ckSizeFmt));    s += sizeof(wh.ckSizeFmt);
	memcpy(wav + s, &wh.WaveFmt, sizeof(wh.WaveFmt));        s += sizeof(wh.WaveFmt);
	memcpy(wav + s, &wh.ckidData, sizeof(wh.ckidData));      s += sizeof(wh.ckidData);
	memcpy(wav + s, &wh.ckSizeData, sizeof(wh.ckSizeData));
}

void ReleaseOggVorbis(char** ogg)
{
	if (ogg != NULL) {
		ov_clear(&vf);
		free(*ogg);
		ogg = NULL;
	}
}

//main
void DoEvent()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

DWORD COggDlg::GetVol()
{
	WAVEFORMATEX wfx1;
	wfx1.wFormatTag = WAVE_FORMAT_PCM;
	wfx1.nChannels = 2;
	wfx1.nSamplesPerSec = 48000;
	wfx1.wBitsPerSample = 24;
	wfx1.nBlockAlign = wfx1.nChannels * wfx1.wBitsPerSample / 8;
	wfx1.nAvgBytesPerSec = wfx1.nSamplesPerSec * wfx1.nBlockAlign;
	wfx1.cbSize = 0;

	mmRes = waveOutOpen(&hwo,
		WAVE_MAPPER,
		&wfx1,
#ifdef WIN64
		(DWORD_PTR)m_hWnd,
#else
		(DWORD)m_hWnd,
#endif
		(DWORD)NULL,
		CALLBACK_WINDOW);

	DWORD v;
	waveOutGetVolume(hwo, &v);
	waveOutClose(hwo);
	return v;
}

extern int flg3;
void COggDlg::dsdclose() {
	dsd_.kpiClose(kmp);
	kmp = NULL;

}
ULONGLONG po;
void COggDlg::dsdload(CString& filen, CString& tagfile, CString& tagname, CString& tagalbum, ULONGLONG& po1, int flg1) {
	CString ss;
	char buf[1024];
	ss = "";
	ZeroMemory(&sikpi, sizeof(sikpi));
	dsdart = "";
	dsdtitle = "";
	sikpi.dwSamplesPerSec = savedata.samples; sikpi.dwChannels = 6; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = ((savedata.bit24 == 1) ? 24 : 16);
	if (savedata.bit32 == 1) {
		sikpi.dwBitsPerSample = 32;
	}
	ULONGLONG pointer;
	if (1) {
		if (ss == "") {
			kpiInit();
#if UNICODE
			TCHAR* f = filen.GetBuffer();
			kmp = dsd_.kpiOpen(f, &sikpi, pointer);
			po = pointer;
			filen.ReleaseBuffer();
#else
			kmp = dsd_.Open(filen, &sikpi);
#endif
			if (kmp == NULL) { m_saisai.EnableWindow(TRUE); return; }
		}
		else {
		}
	}
	wavbit = sikpi.dwSamplesPerSec;	wavch = sikpi.dwChannels;	loop1 = 0; oggsize = loop2 = (int)((double)sikpi.dwLength * (double)sikpi.dwSamplesPerSec / 1000.0 / (wavsam / 16.0));
	wavsam = sikpi.dwBitsPerSample;
	CString s; s.Format(L"%d", oggsize);
	//AfxMessageBox(s);
	si1.dwSamplesPerSec = wavbit;
	si1.dwChannels = wavch;
	si1.dwBitsPerSample = wavsam;
	if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
	data_size = oggsize = loop2 * (wavsam / 4);
	if (wavch == 1) oggsize /= 2;
	if (wavch == 1) data_size /= 2;
	m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
	dsd_.kpiSetPosition(kmp, 0);
	kbps = 0;
	wav_start();
	CFile ff;
	ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL);
	ff.Seek(pointer, CFile::begin);
	int read = ff.Read(bufimage, sizeof(bufimage));
	ff.Close();
	int j;
	int flg = 0;
	ZeroMemory(buf, sizeof(buf));
	tagfile = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
	if (dsdtitle != "") {
		tagfile = dsdtitle;
	}
	for (j = 0; j < read - 6; j++) {
		if (bufimage[j] == 'T' && bufimage[j + 1] == 'I' && bufimage[j + 2] == 'T' && bufimage[j + 3] == '2') {
			int kk = bufimage[j + 7] - 4;
			j += 5 + 4 + 4;
			int l = 0;
			for (int k = j; k < j + kk; k++) {
				buf[l] = bufimage[k];
				l++;
			}
			flg = 1;
			buf[l] = 0;
			buf[l + 1] = 0;
			buf[l + 2] = 0;
			WCHAR* a = (WCHAR*)buf;
			tagfile = a;
			flg = 0;
			break;
		}
	}
	ZeroMemory(buf, sizeof(buf));
	if (dsdart != "") {
		tagname = dsdart;
	}
	flg = 0;
	for (j = 0; j < read - 6; j++) {
		if (bufimage[j] == 'T' && bufimage[j + 1] == 'P' && bufimage[j + 2] == 'E' && bufimage[j + 3] == '1') {
			int kk = bufimage[j + 7] - 4;
			j += 5 + 4 + 4;
			int l = 0;
			for (int k = j; k < j + kk; k++) {
				buf[l] = bufimage[k];
				l++;
			}
			flg = 1;
			buf[l] = 0;
			buf[l + 1] = 0;
			buf[l + 2] = 0;
			WCHAR* a = (WCHAR*)buf;
			tagname = a;
			flg = 0;
			break;
		}
	}
	ZeroMemory(buf, sizeof(buf));
	flg = 0;
	for (j = 0; j < read - 6; j++) {
		if (bufimage[j] == 'T' && bufimage[j + 1] == 'A' && bufimage[j + 2] == 'L' && bufimage[j + 3] == 'B') {
			int kk = bufimage[j + 7] - 4;
			j += 5 + 4 + 4;
			int l = 0;
			for (int k = j; k < j + kk; k++) {
				buf[l] = bufimage[k];
				l++;
			}
			flg = 1;
			buf[l] = 0;
			buf[l + 1] = 0;
			buf[l + 2] = 0;
			WCHAR* a = (WCHAR*)buf;
			tagalbum = a;
			flg = 0;
			break;
		}
	}
	int i;
	for (i = 0; i < read; i++) {// 00 06 5D 6A 64 61 74 61
		if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
			break;
		}
		if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
			break;
		}
	}
	if (i != read && flg1 == 1) {
		m_mp3jake.EnableWindow(TRUE);
	}

}
#include <Shlwapi.h>
#include <stdio.h>

#pragma comment(lib, "Shlwapi.lib")
#include "rubberband/RubberBandStretcher.h"
void COggDlg::Modec() {
	int ret;
	ret = _tchdir(savedata.ed6sc);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_ed6sc.EnableWindow(FALSE); og->m_ed6sc.EnableWindow(FALSE); }
	else { og->d_ed6sc.EnableWindow(TRUE); og->m_ed6sc.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ed6fc);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_ed6fc.EnableWindow(FALSE); og->m_ed6fc.EnableWindow(FALSE); }
	else { og->d_ed6fc.EnableWindow(TRUE); og->m_ed6fc.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ysf);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { og->d_ys3.EnableWindow(FALSE); og->m_ysf.EnableWindow(FALSE); }
	else { og->d_ys3.EnableWindow(TRUE); og->m_ysf.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ys6);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { og->d_ys6.EnableWindow(FALSE); og->m_ys6.EnableWindow(FALSE); }
	else { og->d_ys6.EnableWindow(TRUE); og->m_ys6.EnableWindow(TRUE); }
	ret = _tchdir(savedata.yso);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { og->d_yso.EnableWindow(FALSE); og->m_yso.EnableWindow(FALSE); }
	else { og->d_yso.EnableWindow(TRUE); og->m_yso.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ed6tc);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_ed6tc.EnableWindow(FALSE); og->m_ed6tc.EnableWindow(FALSE); }
	else { og->d_ed6tc.EnableWindow(TRUE); og->m_ed6tc.EnableWindow(TRUE); }
	ret = _tchdir(savedata.zweiii);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_z2.EnableWindow(FALSE); og->m_zweiii.EnableWindow(FALSE); }
	else { og->d_z2.EnableWindow(TRUE); og->m_zweiii.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ysc);
	ret += _chdir("bgm\\ys1");
	if (ret != 0) { og->d_ysc1.EnableWindow(FALSE); og->m_ysc1.EnableWindow(FALSE); }
	else { og->d_ysc1.EnableWindow(TRUE); og->m_ysc1.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ysc);
	ret += _chdir("bgm\\ys2");
	if (ret != 0) { og->d_ysc2.EnableWindow(FALSE); og->m_ysc2.EnableWindow(FALSE); }
	else { og->d_ysc2.EnableWindow(TRUE); og->m_ysc2.EnableWindow(TRUE); }
	ret = _tchdir(savedata.xa);
	ret += _chdir("data\\bgm");
	if (ret != 0) { og->d_xa.EnableWindow(FALSE); og->m_xa.EnableWindow(FALSE); }
	else { og->d_xa.EnableWindow(TRUE); og->m_xa.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ys12);
	og->d_ys1.EnableWindow(TRUE); og->m_ys121.EnableWindow(TRUE);
	if (_chdir("wave\\wave_44") == -1) {
		if (_chdir("wave\\wave_22") == -1) { og->d_ys1.EnableWindow(FALSE); og->m_ys121.EnableWindow(FALSE); }
	}
	ret = _tchdir(savedata.ys122);
	og->d_ys2.EnableWindow(TRUE); og->m_ys122.EnableWindow(TRUE);
	if (_chdir("wave\\wave_44") == -1) {
		if (_chdir("wave\\wave_22") == -1) { og->d_ys2.EnableWindow(FALSE); og->m_ys122.EnableWindow(FALSE); }
	}
	ret = _tchdir(savedata.sor);
	og->d_sor.EnableWindow(TRUE); og->m_sor.EnableWindow(TRUE);
	if (_chdir("WAVE\\WAVE44") == -1) {
		if (_chdir("WAVE\\WAVE22") == -1) { og->d_sor.EnableWindow(FALSE); og->m_sor.EnableWindow(FALSE); }
	}
	og->d_z1.EnableWindow(TRUE); og->m_zwei.EnableWindow(TRUE);
	ret = _tchdir(savedata.zwei);
	{ CFile f; if (f.Open(_T("wav.dat"), CFile::modeRead, NULL) != TRUE) { og->d_z1.EnableWindow(FALSE); og->m_zwei.EnableWindow(FALSE); } else f.Close(); }
	ret = _tchdir(savedata.gurumin);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_guru.EnableWindow(FALSE); og->m_gurumin.EnableWindow(FALSE); }
	else { og->d_guru.EnableWindow(TRUE); og->m_gurumin.EnableWindow(TRUE); }
	og->d_dino.EnableWindow(TRUE); og->m_dino.EnableWindow(TRUE);
	ret = _tchdir(savedata.dino);
	{ CFile f; if (f.Open(_T("bgm.arc"), CFile::modeRead, NULL) != TRUE) { og->d_dino.EnableWindow(FALSE); og->m_dino.EnableWindow(FALSE); } else f.Close(); }
	ret = _tchdir(savedata.br4);
	ret += _chdir("wave");
	if (ret != 0) { og->d_br4.EnableWindow(FALSE); og->m_br4.EnableWindow(FALSE); }
	else { og->d_br4.EnableWindow(TRUE); og->m_br4.EnableWindow(TRUE); }
	ret = _tchdir(savedata.ed3);
	ret += _chdir("wave");
	if (ret != 0) { og->d_ed3.EnableWindow(FALSE); og->m_ed3.EnableWindow(FALSE); }
	else { og->d_ed3.EnableWindow(TRUE); og->m_ed3.EnableWindow(TRUE); }
	og->d_ed4.EnableWindow(TRUE); og->m_ed4.EnableWindow(TRUE);
	ret = _tchdir(savedata.ed4);
	if (_chdir("WAVEDV") == -1) {
		if (_chdir("WAVE") == -1) { og->d_ed4.EnableWindow(FALSE); og->m_ed4.EnableWindow(FALSE); }
	}
	og->d_ed5.EnableWindow(TRUE); og->d_ed5.EnableWindow(TRUE);
	ret = _tchdir(savedata.ed5);
	if (_chdir("WAVEDVD") == -1) {
		if (_chdir("WAVE") == -1) { og->d_ed5.EnableWindow(FALSE); og->m_ed5.EnableWindow(FALSE); }
	}
	ret = _tchdir(savedata.tuki);
	ret += _chdir("MUSIC");
	if (ret != 0) { og->d_tuki.EnableWindow(FALSE); }
	else { og->d_tuki.EnableWindow(TRUE); }
	ret = _tchdir(savedata.nishi);
	ret += _chdir("bgm");
	if (ret != 0) { og->d_nishi.EnableWindow(FALSE); }
	else { og->d_nishi.EnableWindow(TRUE); }
	og->d_arc.EnableWindow(TRUE);
	ret = _tchdir(savedata.arc);
	{ CFile f; if (f.Open(_T("music.pak"), CFile::modeRead, NULL) != TRUE) og->d_arc.EnableWindow(FALSE); else f.Close(); }
	ret = _tchdir(savedata.san1);
	ret += _chdir("music");
	if (ret != 0) { og->d_san1.EnableWindow(FALSE); }
	else { og->d_san1.EnableWindow(TRUE); }
	ret = _tchdir(savedata.san2);
	ret += _chdir("music");
	if (ret != 0) { og->d_san2.EnableWindow(FALSE); }
	else { og->d_san2.EnableWindow(TRUE); }
}
int rrr;
#define MUON 180
int stflg;
int flg0 = 0;
int gameon = 1;
extern CImageBase* playbase;
extern RubberBand::RubberBandStretcher* g_rubberBandStretcher;
BYTE bufkpi[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3];
BYTE bufkpi_[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3];
BYTE bufkpi2[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3];
BYTE bufkpi3[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3];
BYTE bufkpi4[OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3];

void COggDlg::play()
{
	stflg = FALSE;
	//	if (((modesub > 0 && modesub < 22) || (modesub > -16 && modesub < -10))) {
#if 0
	if (gameon == 1) {
		if (playbase)
			::SetWindowPos(playbase->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (pl)
			::SetWindowPos(pl->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (maini)
			::SetWindowPos(maini->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::SetWindowPos(og->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else {
		if (maini)
			::SetWindowPos(maini->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::SetWindowPos(og->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (playbase)
			::SetWindowPos(playbase->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (pl)
			::SetWindowPos(pl->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	gameon = 1;
#endif
	//	}
	muon = MUON;
	rrr = 1;
	m_ps.EnableWindow(TRUE);
	CWaitCursor rrr;
	m_mp3jake.EnableWindow(FALSE);
	mp3file = filen;
	sflg = FALSE;
	tagname = tagfile = tagalbum = "";
	//	m_rund.EnableWindow(FALSE);
	m_saisai.EnableWindow(FALSE);
	WAVDALen = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM; WAVDAStartLen = OUTPUT_BUFFER_SIZE;
	si1.dwSamplesPerSec = 0; sikpi.dwSamplesPerSec = 0;
	//LOOPSTART=
	//LOOPLENGTH=
	CString s, b;
	playf = 1;
	loopcnt = 0;
	CString fl;
	wavbit = 44100;
	loop3 = 0; fade1 = 0;
	playy = 0;
	cnt3 = 0;
	bufzero = 0;
	if (mi) {
		killw1 = 0;
		mi->DestroyWindow();
		for (; killw1 == 0;)
			DoEvent();
		mi = NULL;
	}
	//
	videoonly = FALSE;
	if (mode == 7) { fl = filen.Right(8); fl = fl.Left(3); }
	else { fl = filen.Right(7); fl = fl.Left(3); }
	int nn = _tstoi(fl);
	pl_no = nn;
	if (mode == 8) { pl_no = ret2; }//ysc1
	if (mode == 9) { pl_no = ret2; }//ysc2
	if (mode == 15) { pl_no = ret2; }//ysc2
	if (mode == 16) { pl_no = ret2; }//ysc2
	fade = 0;
	endflg = 0;
	stop1();

	CWaitCursor rrr1;
	wavwait = 0; thend = 1; stitle = "";
	playf = 1;
	int ret = 0;



	if (filen.Find(L"y8_logo.ogg") != -1) {
		ret2 = 1;
	}
	if (filen.Find(L"y8_op.ogg") != -1) {
		ret2 = 2;
	}
	if (filen.Find(L"y8_end.ogg") != -1) {
		ret2 = 3;
	}
	if (filen.Find(L"yc_logo.ogg") != -1) {
		ret2 = 4;
	}
	if (m_dou.GetCheck() == 1)
		gamen(ret2);

	switch (mode) {
	case 1://ED6SC
		ret = _tchdir(savedata.ed6sc);
		ret += _chdir("bgm");
		break;
	case 2://ED6FC
		ret = _tchdir(savedata.ed6fc);
		ret += _chdir("bgm");
		break;
	case 3:
		ret = _tchdir(savedata.ysf);
		ret += _chdir("RELEASE\\MUSIC");
		break;
	case 4:
		ret = _tchdir(savedata.ys6);
		ret += _chdir("RELEASE\\MUSIC");
		break;
	case 5:
		ret = _tchdir(savedata.yso);
		ret += _chdir("RELEASE\\MUSIC");
		break;
	case 6:
		ret = _tchdir(savedata.ed6tc);
		ret += _chdir("bgm");
		break;
	case 7:
		ret = _tchdir(savedata.zweiii);
		ret += _chdir("bgm");
		break;
	case 8:
		ret = _tchdir(savedata.ysc);
		ret += _chdir("bgm\\ys1");
		break;
	case 9:
		ret = _tchdir(savedata.ysc);
		ret += _chdir("bgm\\ys2");
		break;
	case 10:
		ret = _tchdir(savedata.xa);
		ret += _chdir("data\\bgm");
		break;
	case 11:
		ret = _tchdir(savedata.ys12);
		if (_chdir("wave\\wave_44") == -1) {
			if (_chdir("wave\\wave_22") == -1) { ret = -1; break; }
			wavbit = 22050;
		}
		else wavbit = 44100;
		{ CFile f; if (f.Open(filen, CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case 12:
		ret = _tchdir(savedata.ys122);
		if (_chdir("wave\\wave_44") == -1) {
			if (_chdir("wave\\wave_22") == -1) { ret = -1; break; }
			wavbit = 22050;
		}
		else wavbit = 44100;
		{ CFile f; if (f.Open(filen, CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case 13:
		ret = _tchdir(savedata.sor);
		if (_chdir("WAVE\\WAVE44") == -1) {
			if (_chdir("WAVE\\WAVE22") == -1) { ret = -1; break; }
			wavbit = 22050;
		}
		else wavbit = 44100;
		{ CFile f; if (f.Open(filen, CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case 14:
		ret = _tchdir(savedata.zwei);
		{ CFile f; if (f.Open(_T("wav.dat"), CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case 15:
		ret = _tchdir(savedata.gurumin);
		ret += _chdir("bgm");
		break;
	case 16:
		ret = _tchdir(savedata.dino);
		{ CFile f; if (f.Open(_T("bgm.arc"), CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case 17:
		ret = _tchdir(savedata.br4);
		wavbit = 22050;
		ret += _chdir("wave");
		break;
	case 18:
		ret = _tchdir(savedata.ed3);
		ret += _chdir("wave");
		break;
	case 19:
		ret = _tchdir(savedata.ed4);
		if (_chdir("WAVEDV") == -1) {
			if (_chdir("WAVE") == -1) { ret = -1; break; }
			filen += ".wav";
		}
		else filen += "DV.wav";
		break;
	case 20:
		ret = _tchdir(savedata.ed5);
		if (_chdir("WAVEDVD") == -1) {
			if (_chdir("WAVE") == -1) { ret = -1; break; }
		}
		break;
	case -11:
		ret = _tchdir(savedata.tuki);
		ret += _chdir("MUSIC");
		break;
	case -12:
		ret = _tchdir(savedata.nishi);
		ret += _chdir("bgm");
		break;
	case -13:
		ret = _tchdir(savedata.arc);
		{ CFile f; if (f.Open(_T("music.pak"), CFile::modeRead, NULL) != TRUE) ret = -1; else f.Close(); }
		break;
	case -14:
		ret = _tchdir(savedata.san1);
		ret += _chdir("music");
		break;
	case -15:
		ret = _tchdir(savedata.san2);
		ret += _chdir("music");
		break;
	}

	if (mode == -14) {
		int i;
		if (ret2 == 43 || ret2 == 45 || ret2 == 46 || ret2 == 47) {
			if (ret2 == 43)i = 124; if (ret2 == 45)i = 121; if (ret2 == 46)i = 122; if (ret2 == 47)i = 1;
			_chdir("..\\Image"); CFile f; if (ret2 != 47) f.Open(_T("Stage.BKS"), CFile::modeRead, NULL); else f.Open(_T("Stage.BKS4"), CFile::modeRead, NULL);
			_getcwd(kare, 255);	f.Seek(0x2c, CFile::begin);
			int len, st, j;	for (j = 0; j < i; j++) { f.Read(&st, 4);	f.Read(&len, 4); }
			f.Seek(st, CFile::begin); CString a; a.Format(_T("FS%2d.bik"), ret2);
			CFile ff; if (ff.Open(a, CFile::modeRead, NULL) == 0) {
				ff.Open(a, CFile::modeCreate | CFile::modeWrite, NULL);
				char* bu; bu = (char*)malloc(len);	f.Read(bu, len);	ff.Write(bu, len);	free(bu);
			}
			f.Close();	ff.Close();
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
			}
			endflg = 0;
			return;
		}
	}
	if (mode == -15) {
		int i;
		if (ret2 == 50 || ret2 == 51 || ret2 == 49) {
			if (ret2 == 49)i = 0; if (ret2 == 51)i = 163; if (ret2 == 50)i = 1;
			_chdir("..\\Image"); CFile f; if (ret2 == 50) f.Open(_T("FS2_STAGE.BKS"), CFile::modeRead, NULL); else f.Open(_T("FS2_STAGE_2.BKS"), CFile::modeRead, NULL);
			_getcwd(kare, 255);	f.Seek(0x2c, CFile::begin);
			int len, st = 0, j;	if (i != 0) for (j = 0; j < i; j++) { f.Read(&st, 4);	f.Read(&len, 4); }
			f.Seek(st, CFile::begin); CString a; a.Format(_T("FS2%2d.bik"), ret2);
			CFile ff; if (i != 0) if (ff.Open(a, CFile::modeRead, NULL) == 0) {
				ff.Open(a, CFile::modeCreate | CFile::modeWrite, NULL);
				char* bu; bu = (char*)malloc(len);	f.Read(bu, len);	ff.Write(bu, len);	free(bu);
				ff.Close();
			}
			else ff.Close();
			f.Close();
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
			}
			endflg = 0;
			return;
		}
	}
	if (mode == -13) {
		if (ret2 == 0)
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				return;
			}
	}
	if (mode == -11) {
		if (ret2 > 27)
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
	}
	if (mode == 1) {
		if (ret2 > 100)
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		if (ret2 == 98) filen = "ED6500.ogg";
		if (ret2 == 99) filen = "ED6011.ogg";
		if (ret2 == 100) filen = "ED6012.ogg";
	}
	if (mode == 19) {
		if (ret2 == 1 || ret2 == 2)
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}

	}
	if (mode == 15) {
		if (ret2 == 40) {
			filen = "bgm01.de2";
			loop1 = loop2 = 0;
		}
	}
	if (mode == 16) {
		if (ret2 == 33) {
			filen = "dinow_01(bgm.arc)";
			loop1 = loop2 = 0;
		}
	}
	if (mode == 10) {
		if (ret2 == 24) filen = "XANA300.dec";
		if (ret2 == 25) filen = "XANA000.dec";
	}
	if (mode == 7) {
		if (ret2 == 65) filen = "ZW2_002.ogg";
		if (ret2 == 66) filen = "ZW2_003.ogg";
	}
	if (mode == 8) {
		if (ret2 >= 72) {
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		}
	}
	if (mode == 9) {
		if (ret2 >= 93) {
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		}
	}
	if (mode == 11) {
		if (ret2 >= 25) {
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		}
	}
	if (mode == 12) {
		if (ret2 >= 31) {
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		}
	}
	if (mode == 6) {
		if (ret2 == 141 || ret2 > 143) {
			if (m_dou.GetCheck() == 1) {
				plf = 1;
				dougaplay(ret2);
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl)pMediaControl->Run();
				m_saisai.EnableWindow(TRUE); playy = 1;
				REFTIME aa;
				pMediaPosition->get_Duration(&aa);
				aa1 = oggsize2 = aa;
				m_time.SetRange(0, (int)(aa * 100), TRUE);
				m_time.SetSelection(0, (int)(aa * 100) - 1);
				m_time.Invalidate();
				videoonly = TRUE;
				if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
				endflg = 0;
				return;
			}
		}
		if (ret2 == 142) filen = "ED6021.ogg";
		if (ret2 == 143) filen = "ED6022.ogg";

	}
	if (mode == 5 && ret2 > 39) {
		if (ret2 == 40) filen = "YSO_020.ogg"; else
			if (ret2 == 41) filen = "YSO_019.ogg"; else
				if (ret2 == 43) filen = "YSO_037.ogg"; else
					if (ret2 == 44) filen = "YSO_038.ogg"; else
						if (ret2 == 45) filen = "YSO_039.ogg"; else
							if (ret2 == 46) filen = "YSO_033.ogg"; else
								if (ret2 == 47) filen = "YSO_034.ogg"; else
									if (ret2 == 42) filen = "YSO_032.ogg";
									else {
										plf = 1;
										dougaplay(ret2);
										if (pGraphBuilder)pMainFrame1->plays2();
										if (pMediaControl)pMediaControl->Run();
										m_saisai.EnableWindow(TRUE); playy = 1;
										REFTIME aa;
										pMediaPosition->get_Duration(&aa);
										aa1 = oggsize2 = aa;
										m_time.SetRange(0, (int)(aa * 100), TRUE);
										m_time.SetSelection(0, (int)(aa * 100) - 1);
										m_time.Invalidate();
										videoonly = TRUE;
										if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
										endflg = 0;
										return;
									}
	}
	if (ret2 > 54 && mode == 2)
		if (m_dou.GetCheck() == 1)
		{
			plf = 1;
			dougaplay(ret2);
			if (pGraphBuilder)pMainFrame1->plays2();
			if (pMediaControl)pMediaControl->Run();
			m_saisai.EnableWindow(TRUE); playy = 1;
			REFTIME aa;
			pMediaPosition->get_Duration(&aa);
			aa1 = oggsize2 = aa;
			m_time.SetRange(0, (int)(aa * 100), TRUE);
			m_time.SetSelection(0, (int)(aa * 100) - 1);
			m_time.Invalidate();
			videoonly = TRUE;
			if (pl && plw)SetAdd(fnn, mode, loop1, loop2, filen, ret2, aa);
			endflg = 0;
			return;
		}


	if (ret != 0) {
		fnn = "ファイル又はフォルダがありません"; filen = "";
		m_saisai.EnableWindow(TRUE); endflg = 0; return;
	}
	wl = 0;


	ss = filen.Left(filen.ReverseFind('\\'));
	ss = ss.Left(ss.ReverseFind('\\'));

	fade1 = 0; fade = 1.0f; fadeadd = 0.0f;
	m_mp3jake.EnableWindow(FALSE);
	if (m_dou.GetCheck() == 1)
		dougaplay(ret2, ss);

	CBitmap bbbb;
	HBITMAP bbbbb = bbbb;
	//	ReleaseOggVorbis(&ogg);
	//	CFile f;
	//	if(f.Open(filen,CFile::modeRead,NULL)!=TRUE)
	//		return;
	//	f.Close();
	wavch = 2;
	wavsam = 16;
	ZeroMemory(bufwav3, sizeof(bufwav3));
	if (((mode >= 10 && mode <= 21) || mode <= -10) && mode != -10 || mode == -6) {
		thend1 = FALSE;
		wavwait = 0;
		thend = 0;
		wav_start();
		//		m_thread1 = ::AfxBeginThread((AFX_THREADPROC)wavread, (LPVOID)NULL,THREAD_PRIORITY_ABOVE_NORMAL,0,0,0);
		//		::SetPriorityClass(m_thread1, HIGH_PRIORITY_CLASS);
		//CRuntimeClass *pRuntime = RUNTIME_CLASS(CWread);
		CWread* g_pThread;// = (CWread*)pRuntime->CreateObject();
		//g_pThread->CreateThread(0, 0, NULL);
		g_pThread = (CWread*)AfxBeginThread(RUNTIME_CLASS(CWread), THREAD_PRIORITY_ABOVE_NORMAL, NULL, 0, NULL);
		::SetPriorityClass(g_pThread, HIGH_PRIORITY_CLASS);
		g_pThread->PostThreadMessage(WM_APP + 100, NULL, NULL);
		for (int k = 0; k < 100; k++)
			DoEvent();
	}
	else if (mode == -3 || mode == -10 || mode == -9 || mode == -8 || mode == -7 || mode == -6) {

	}
	else {
		if (mode != -6) {
			oggsize = LoadOggVorbis(filen, 2, &ogg, m_time);
			if (oggsize < 0) {
				m_saisai.EnableWindow(TRUE);
				fnn = "ファイル又はフォルダがありません";
				endflg = 0;
				return;
			}
			loop1 = loop2 = 0; stitle = "";
			if (vf.vc->comments >= 2)
			{
				CString cc;
				for (int iii = 0; iii < vf.vc->comments; iii++) {
#if _UNICODE
					WCHAR* f; f = new WCHAR[0x300000];
					MultiByteToWideChar(CP_UTF8, 0, vf.vc->user_comments[iii], -1, f, 0x300000);
					cc = f;
					delete[] f;
#else
					cc = vf.vc->user_comments[iii];
#endif
					if (cc.Left(6).MakeUpper() == "TITLE=")
					{
#if _UNICODE
						ss = UTF8toUNI(cc.Mid(6));
#else
						ss = UTF8toSJIS(cc.Mid(6));
#endif
						stitle = ss;
					}
					if (cc.Left(10) == "LOOPSTART=")
					{
						loop1 = _tstoi(cc.Mid(10));
					}
					if (cc.Left(11) == "LOOPLENGTH=")
					{
						loop2 = _tstoi(cc.Mid(11));
					}
					if (cc.Left(23) == "METADATA_BLOCK_PICTURE=")
					{
						m_mp3jake.EnableWindow(TRUE);
					}
				}
			}
		}
		else {

		}
	}
	//ファイル保存用
	cc1 = 0;
	playb = 0;
	m_time.SetPos((int)playb);
	ov_pcm_seek(&vf, (ogg_int64_t)0); poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
	ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
	ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
	ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
	ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
	ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
	//wavoutで
	playb = 0;
	lo = loc = locs = 0;
	//Stereo 16bit 44kHz
	loc = 0;

	//ys8用
	CStdioFile f;
	char* buff;
	int looping = 0;
	int igg;
	ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
	ss = ss.Left(ss.ReverseFind('.'));
	char file[256];
	WCHAR outcm[1024];
	WideCharToMultiByte(CP_ACP, 0, ss, 1024, file, 256, NULL, NULL);
	FILE* fp;
	TRY{
	fp = _wfopen(filen.Left(filen.ReverseFind('\\')) + L"\\..\\text\\bgmtbl.tbl", L"r");
	}CATCH_ALL(e) {
		fp = NULL;
	}END_CATCH_ALL
		if (fp) {
			buff = (char*)calloc(256, 1);
			for (;;) {
				if (fgets(buff, 256, fp) == NULL) {
					free(buff); break;
				}
				char* p = strstr(buff, file);
				if (p == NULL) continue;
				if (buff[0] == '/') continue;
				p += strlen(file) + 1;
				for (; *p == 0x09; p++);
				if (*p == '1') looping = 1;
				p++;
				for (; *p == 0x09; p++);
				typedef struct {
					char st[8];
					char a[1];
					char ed[8];
				} aa;
				aa* aa1;
				aa1 = (aa*)p;
				int i, j;
				j = 0;
				for (i = 0; i < 8; i++) {
					switch (aa1->st[i])
					{
					case '0':
						j *= 10; j += 0;
						break;
					case '1':
						j *= 10; j += 1;
						break;
					case '2':
						j *= 10; j += 2;
						break;
					case '3':
						j *= 10; j += 3;
						break;
					case '4':
						j *= 10; j += 4;
						break;
					case '5':
						j *= 10; j += 5;
						break;
					case '6':
						j *= 10; j += 6;
						break;
					case '7':
						j *= 10; j += 7;
						break;
					case '8':
						j *= 10; j += 8;
						break;
					case '9':
						j *= 10; j += 9;
						break;
					}
				}
				loop1 = j;
				j = 0;
				for (i = 0; i < 8; i++) {
					switch (aa1->ed[i])
					{
					case '0':
						j *= 10; j += 0;
						break;
					case '1':
						j *= 10; j += 1;
						break;
					case '2':
						j *= 10; j += 2;
						break;
					case '3':
						j *= 10; j += 3;
						break;
					case '4':
						j *= 10; j += 4;
						break;
					case '5':
						j *= 10; j += 5;
						break;
					case '6':
						j *= 10; j += 6;
						break;
					case '7':
						j *= 10; j += 7;
						break;
					case '8':
						j *= 10; j += 8;
						break;
					case '9':
						j *= 10; j += 9;
						break;
					}
				}
				loop2 = j - loop1;
				p += sizeof(aa) + 1;
				for (; *p == 0x09; p++);
				p += 3;
				char* pp = p;
				for (; *p != 0xd; p++) {
					if (*p == 0x9) {
						*p = 0x20;
					}
				}
				p = pp;
				MultiByteToWideChar(CP_ACP, 0, p, -1, outcm, 1024);
				stitle = outcm;
				stitle.Trim();
				if (looping == 0) {
					loop1 = loop2 = 0;
				}
				free(buff); break;
			}
			fclose(fp);

		}
	//YSC
	ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
	if (ss == "yc_b001.ogg") {
		loop1 = 123438;
		loop2 = 4742104;
		stitle = "バトル#58";
	}
	if (ss == "yc_b002.ogg") {
		loop1 = 504378;
		loop2 = 5153813;
		stitle = "灼熱の炎の中で";
	}
	if (ss == "yc_b003.ogg") {
		loop1 = 32845;
		loop2 = 6955200;
		stitle = "最終決戦";
	}
	if (ss == "yc_b004.ogg") {
		loop1 = 53237;
		loop2 = 9737128;
		stitle = "黒き翼";
	}
	if (ss == "yc_b005.ogg") {
		loop1 = 1123422;
		loop2 = 7687672;
		stitle = "The False God of Causality";
	}
	if (ss == "yc_d101.ogg") {
		loop1 = 303237;
		loop2 = 2582426;
		stitle = "ダンジョン";
	}
	if (ss == "yc_d201.ogg") {
		loop1 = 447792;
		loop2 = 3479666;
		stitle = "道化師の誘い";
	}
	if (ss == "yc_d301.ogg") {
		loop1 = 351836;
		loop2 = 3969072;
		stitle = "地下遺跡";
	}
	if (ss == "yc_d401.ogg") {
		loop1 = 93865;
		loop2 = 4349569;
		stitle = "導きの塔～エルディールにくちづけを";
	}
	if (ss == "yc_d501.ogg") {
		loop1 = 832720;
		loop2 = 7219417;
		stitle = "失われし仮面を求めて";
	}
	if (ss == "yc_d701.ogg") {
		loop1 = 809264;
		loop2 = 6545498;
		stitle = "イリス";
	}
	if (ss == "yc_d702.ogg") {
		loop1 = 34816;
		loop2 = 1189171;
		stitle = "yc_d702";
	}
	if (ss == "yc_d703.ogg") {
		loop1 = 719876;
		loop2 = 2557197;
		stitle = "聖域";
	}
	if (ss == "yc_e001.ogg") {
		loop1 = 300048;
		loop2 = 3389821;
		stitle = "賢者";
	}
	if (ss == "yc_e002.ogg") {
		loop1 = 326209;
		loop2 = 3604271;
		stitle = "復活の儀式";
	}
	if (ss == "yc_e003.ogg") {
		loop1 = 806906;
		loop2 = 4275899;
		stitle = "レファンス";
	}
	if (ss == "yc_e004.ogg") {
		loop1 = 326209;
		loop2 = 4945888;
		stitle = "涙の少年剣士";
	}
	if (ss == "yc_e005.ogg") {
		loop1 = 24000;
		loop2 = 3605888;
		stitle = "エルディール";
	}
	if (ss == "yc_e006.ogg") {
		loop1 = 69040;
		loop2 = 1209633;
		stitle = "ロムン帝国 -嗚呼レオ団長-";
	}
	if (ss == "yc_e008.ogg") {
		loop1 = 275476;
		loop2 = 3609611;
		stitle = "yc_e008";
	}
	if (ss == "yc_e010.ogg") {
		loop1 = 807040;
		loop2 = 5159922;
		stitle = "冒険家、誕生";
	}
	if (ss == "yc_f101.ogg") {
		loop1 = 568926;
		loop2 = 5668207;
		stitle = "燃ゆる剣";
	}
	if (ss == "yc_f201.ogg") {
		loop1 = 588624;
		loop2 = 6209316;
		stitle = "セルセタの樹海";
	}
	if (ss == "yc_f301.ogg") {
		loop1 = 1145404;
		loop2 = 5960203;
		stitle = "クレーター";
	}
	if (ss == "yc_f401.ogg") {
		loop1 = 408974;
		loop2 = 3161454;
		stitle = "THE DAWN OF YS";
	}
	if (ss == "yc_f501.ogg") {
		loop1 = 2604464;
		loop2 = 4559688;
		stitle = "暁の森";
	}
	if (ss == "yc_f601.ogg") {
		loop1 = 581264;
		loop2 = 3661828;
		stitle = "一陣の風";
	}
	if (ss == "yc_f701.ogg") {
		loop1 = 324287;
		loop2 = 9010870;
		stitle = "神代の地";
	}
	if (ss == "yc_f801.ogg") {
		loop1 = 315435;
		loop2 = 4546653;
		stitle = "真実への序曲";
	}
	if (ss == "yc_f901.ogg") {
		loop1 = 178544;
		loop2 = 4786555;
		stitle = "雨上がりの朝に";
	}
	if (ss == "yc_over.ogg") {
		loop1 = 19200;
		loop2 = 4924407;
		stitle = "ゲームオーバー";
	}
	if (ss == "yc_t101.ogg") {
		loop1 = 865353;
		loop2 = 4409988;
		stitle = "辺境都市《キャスナン》";
	}
	if (ss == "yc_t201.ogg") {
		loop1 = 58906;
		loop2 = 6120526;
		stitle = "優しくなりたい";
	}
	if (ss == "yc_t301.ogg") {
		loop1 = 425910;
		loop2 = 9606150;
		stitle = "古代の伝承";
	}
	if (ss == "yc_t501.ogg") {
		loop1 = 782252;
		loop2 = 7781799;
		stitle = "RODA";
	}
	if (ss == "yc_title.ogg") {
		loop1 = 10000;
		loop2 = 4924407;
		stitle = "THEME OF ADOL 2012";
	}
	if (ss == "yc_op.ogg") {
		stitle = "The Foliage Ocean in CELCETA -Opening size-";
	}
	if (ss == "yc_end.ogg") {
		stitle = "新たな時代のステージへ";
	}

	//零の軌跡用
	fp = _wfsopen(filen.Left(filen.ReverseFind('\\')) + L"\\..\\text\\t_bgm._dt", L"rb", 0x40);
	if (fp) {
		struct a_ {
			long start;
			long end;
			long no;
			long w;
		};
		a_ a;
		ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		CString sss;
		sss = ss.Mid(2, 4);
		int no = _ttoi(sss);
		int fg = 0;
		for (;;) {
			fread(&a, 16, 1, fp);
			if (feof(fp)) break;
			if (no == a.no) {
				fg = 1;
				loop1 = a.start;
				loop2 = a.end;
				break;
			}
		}
		fclose(fp);
		sss = savedata.zero;
		if (fg == 0 && sss == L"") {
			int ret = MessageBox(L"おそらく碧の軌跡のbgmデータで、碧の軌跡のbgmテーブルに情報がありません。\n零の軌跡のbgmテーブルを参照しますか？\n(碧の軌跡には零の軌跡のbgmデータも入ってるため、ループ情報は零の軌跡側にあります)", L"bgmテーブルに情報がありません。", MB_YESNO);
			if (ret == IDYES) {
				CZeroFol d;
				if (d.DoModal() == IDOK) {
					FILE* fp = _wfsopen(savedata.zero, L"rb", 0x40);
					if (fp) {
						ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
						CString sss;
						sss = ss.Mid(2, 4);
						int no = _ttoi(sss);
						for (;;) {
							fread(&a, 16, 1, fp);
							if (feof(fp)) break;
							if (no == a.no) {
								loop1 = a.start;
								loop2 = a.end;
								break;
							}
						}
						fclose(fp);
					}
				}
			}
		}
		else if (sss != L"") {
			FILE* fp = _wfsopen(savedata.zero, L"rb", 0x40);
			if (fp) {
				ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
				CString sss;
				sss = ss.Mid(2, 4);
				int no = _ttoi(sss);
				for (;;) {
					fread(&a, 16, 1, fp);
					if (feof(fp)) break;
					if (no == a.no) {
						loop1 = a.start;
						loop2 = a.end;
						break;
					}
				}
				fclose(fp);
			}
		}
	}
	//-------------------------------------------------------------------
	if (m_dsb != NULL) m_dsb->Release();
	m_dsb = NULL;
	//	char bufdmy[10000];
	ZeroMemory(bufwav3, sizeof(bufwav3));
	DWORD  dwDataLen = WAVDALen / OUTPUT_BUFFER_NUM;
	if (((mode >= 10 && mode <= 21) || mode <= -10) && mode != -10 || mode == -6) {
		for (; wavwait == 0;) { CWaitCursor rrr2; DoEvent(); }
		if (adbuf2 == NULL) { endflg = 0; return; }
		//		if(mode!=-10)
		//			playwavadpcm(bufwav3,0,dwDataLen*4,0);
		//		else
		//			playwavadpcm(bufdmy,0,dwDataLen*4,0);
	}
	else if (mode == -10) { //mp123
		CString s, ss;
		s = filen.Left(filen.ReverseFind('\\')); ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		_tchdir(s);
		CFile ff;
		if (ff.Open(ss, CFile::modeRead | CFile::shareDenyNone, NULL) == FALSE) {
			MessageBox(_T("ファイルが存在しません。\n削除されたかフォルダまたはファイル名が変更された可能性があります。"), _T("ファイルが存在しません。"));
			m_saisai.EnableWindow(TRUE); endflg = 0; return;
		}ff.Close();

		BYTE buf[2005];
		ZeroMemory(buf, 2005);
		if (ff.Open(ss, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
			ff.Read(buf, 2000);
			int i;
			for (i = 0; i < 2000; i++) {
				if (buf[i] == 0x41 && buf[i + 1] == 0x50 && buf[i + 2] == 0x49 && buf[i + 3] == 0x43) {
					break;
				}
			}
			if (i != 2000) {
				m_mp3jake.EnableWindow(TRUE);
			}
		}ff.Close();
		mp3_.mp3init();
		si1.dwSamplesPerSec = savedata.samples;
		si1.dwChannels = 2;
		si1.dwBitsPerSample = 24;
		if (savedata.bit24 == 0) si1.dwBitsPerSample = 16;
		mp3_.Open(ss, &si1);
		CMp3Info mp3__;
		mp3__.Load(ss);

		wavch = si1.dwChannels;
		wavbit = si1.dwSamplesPerSec;
		wavsam = si1.dwBitsPerSample;
		loop1 = 0; stitle = "";
		//		loop2=(int)(((float)(((float)si1.dwLength)*44.1f))/(44100.0f/((float)((wavch==2)?wavbit:(wavbit/2)))));
		//		loop2=(int)((float)(mp3_.m_mp3info.total_samples)/(wavch==2?1.0f:2.0f));
		loop2 = (int)(((double)mp3__.GetMSec()) / 1000.0 * (double)mp3_.m_mp3info.freq);//*(44100.0/((double)((wavch==2)?(double)wavbit:((double)wavbit/2.0)))));
		//		if(loop2==0){
		if (mp3_.m_mp3info.hasVbrtag) {
			//			loop2 *= 2.29;
		}
		//			loop2=(int)(((float)(((float)si1.dwLength)*44.1f))/(44100.0f/((float)((wavch==2)?wavbit:(wavbit/2)))));
		//		}
		data_size = oggsize = loop2;
		loop3 = loop2; loop2 = 0;
		m_time.SetRange(0, ((data_size / 2.0) * (wavsam / 8.0)) / (100), TRUE);
		lenl = 0;
		if (mp3_.m_mp3info.hasVbrtag == 0)
			kbps = mp3_.m_mp3info.bitrate / 1000;
		else
			kbps = mp3_.m_mp3info.bitrate / 1000;
		//kbps=mp3_.m_mp3info.total_samples/mp3_.m_mp3info.freq;
		Vbr = mp3_.m_mp3info.hasVbrtag;
		savedata.mp3orig = 0;
		if (Vbr == 1) savedata.mp3orig = 1;
		CId3tagv1 ta1;
		CId3tagv2 ta2;
		int b = ta2.Load(ss);
		tagname = ta2.GetArtist(); if (b == -1) { ta1.Load(ss); tagname = ta1.GetArtist(); }
		tagfile = ta2.GetTitle(); if (b == -1) tagfile = ta1.GetTitle();
		tagalbum = ta2.GetAlbum(); if (b == -1) tagalbum = ta1.GetAlbum();
		if (tagfile == "") tagfile = ss;
		mp3file = ss;
		wav_start();
		//		playwavmp3(bufwav3,0,dwDataLen*4,0);
	}
	else if (mode == -7) { // dsd
		ULONGLONG po;
		dsdload(filen, tagfile, tagname, tagalbum, po, 1);
	}
	else if (mode == -8) { // flac
		CString ss;
		char buf[1024];
		ss = "";
		ZeroMemory(&sikpi, sizeof(sikpi));
		sikpi.dwSamplesPerSec = savedata.samples; sikpi.dwChannels = 8; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = ((savedata.bit24 == 1) ? 24 : 16);
		if (flg0 == 1) sikpi.dwSamplesPerSec = wavbit;


		if (1) {
			if (ss == "") {
				flacmode = 0;
				CFile pp; pp.Open(filen, CFile::shareDenyNone | CFile::modeRead);
				BYTE a; pp.Read(&a, 1); pp.Close();
				if (a == 0xBF) flacmode = 1;
#if UNICODE
				TCHAR* f = filen.GetBuffer();
				kmp = flac_.Open(f, &sikpi);
				filen.ReleaseBuffer();
#else
				kmp = flac_.Open(filen, &sikpi);
#endif
				if (kmp == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
			}
			else {
			}
		}
		wavbit = sikpi.dwSamplesPerSec;
		wavch = sikpi.dwChannels;
		loop1 = 0; oggsize = loop2 = (int)((double)sikpi.dwLength * (double)sikpi.dwSamplesPerSec / 1000.0 / (wavsam / 16.0));
		wavsam = sikpi.dwBitsPerSample;
		CString s; s.Format(L"%d", oggsize);
		//AfxMessageBox(s);
		si1.dwSamplesPerSec = wavbit;
		si1.dwChannels = wavch;
		si1.dwBitsPerSample = wavsam;
		if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
		data_size = oggsize = loop2 * (wavsam / 4);
		if (wavch == 1) oggsize /= 2;
		if (wavch == 1) data_size /= 2;
		m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
		flac_.SetPosition(kmp, 0);
		kbps = 0;
		CFile ff;
		ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL);
		int flg, read = ff.Read(bufimage, sizeof(bufimage));
		ff.Close();

		if (bufimage[0] == 0xBF) {
			CFile fff;
			if (fff.Open(filen, CFile::shareDenyNone | CFile::modeRead)) {
				fff.Seek(fff.GetLength() - 8, CFile::begin);
				struct data {
					int l1;
					int l2;
				};
				data d;
				fff.Read(&d, sizeof(d));
				loop1 = d.l1;
				loop2 = d.l2;
				fff.Close();
			}
		}

		if (bufimage[0] == 0xBF) {
			BYTE offenc[7] = { 0xd9,0x3F,0x86,0x7B,0xC7,0x61,0xaa };
			int off = 0;
			for (int ll = 0; ll < sizeof(bufimage); ll++) {
				bufimage[ll] ^= offenc[off];
				off++; off %= 7;
			}
		}
		tagfile = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		flg = 0;
		int i = 0, j;
		for (j = i; j < read - 6; j++) {
			if (bufimage[j] == 'A' && bufimage[j + 1] == 'L' && bufimage[j + 2] == 'B' && bufimage[j + 3] == 'U' && bufimage[j + 4] == 'M' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = 0;
				}
				tagalbum = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 3] == 'u' && bufimage[j + 4] == 'm' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = 0;
				}
				tagalbum = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'I' && bufimage[j + 4] == 'S' && bufimage[j + 5] == 'T' && bufimage[j + 6] == '=') {
				j += 7;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagname = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'r' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'i' && bufimage[j + 4] == 's' && bufimage[j + 5] == 't' && bufimage[j + 6] == '=') {
				j += 7;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagname = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 4; j++) {
			if (bufimage[j] == 'T' && bufimage[j + 1] == 'I' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'L' && bufimage[j + 4] == 'E' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagfile = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 4; j++) {
			if ((bufimage[j] == 'T' || bufimage[j] == 't') && bufimage[j + 1] == 'i' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'l' && bufimage[j + 4] == 'e' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagfile = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}

		for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
				break;
			}
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
				break;
			}
		}
		if (i != 0x300000) {
			m_mp3jake.EnableWindow(TRUE);
		}
		wav_start();
	}
	else if (mode == -9) { // M4a
		CString ss;
		char buf[1024];
		ss = "";
		ZeroMemory(&sikpi, sizeof(sikpi));
		sikpi.dwSamplesPerSec = savedata.samples; sikpi.dwChannels = 2; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = ((savedata.bit24 == 1) ? 24 : 16);
		if (savedata.bit32 == 1)sikpi.dwBitsPerSample = 16;
		if (flg0 == 1) sikpi.dwSamplesPerSec = wavbit;

		if (1) {
			if (ss == "") {
#if UNICODE
				TCHAR* f = filen.GetBuffer();
				kmp = m4a_.Open(f, &sikpi);
				filen.ReleaseBuffer();
#else
				kmp = m4a_.Open(filen, &sikpi);
#endif
				if (kmp == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
			}
			else {
			}
		}
		wavsam = sikpi.dwBitsPerSample;
		wavbit = sikpi.dwSamplesPerSec;	wavch = sikpi.dwChannels;	loop1 = 0; oggsize = loop2 = (int)((float)sikpi.dwLength / (wavsam / 4) /*/ (float)1000.0f* (float)sikpi.dwSamplesPerSec*/);
		CString s_; s_.Format(L"%d", wavbit);
		si1.dwSamplesPerSec = sikpi.dwSamplesPerSec;
		si1.dwChannels = wavch;
		si1.dwBitsPerSample = wavsam;
		Vbr = sikpi.vbr;
		if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
		data_size = oggsize = loop2 * (wavsam / 4);
		m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
		m4a_.SetPosition(kmp, 0);
		kbps = 0;
		CFile ff;
		ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL);
		int flg, read = ff.Read(bufimage, 4); read = sizeof(bufimage);
		tagfile = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		flg = 0;
		int i;
		for (;;) {
			if (read != sizeof(bufimage)) {
				break;
			}
			else {
				ff.Seek(-4, CFile::current);
				read = ff.Read(bufimage, sizeof(bufimage));
				for (i = 0; i < read - 4; i++) {
					if (bufimage[i] == 'u' && bufimage[i + 1] == 'd' && bufimage[i + 2] == 't' && bufimage[i + 3] == 'a') {
						int j;
						for (j = i + 4; j < read - 4; j++) {
							if (bufimage[j] == 'a' && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
								j += 19;
								for (int k = j; k < read - 4; k++) {
									if (bufimage[k] == 0) {
										flg = 1;
										buf[k - j] = 0;
										buf[k - j + 1] = 0;
										buf[k - j + 2] = 0;
										break;
									}
									buf[k - j] = bufimage[k];
								}
							}
							if (flg == 1) {
								const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
								TCHAR* buff = new TCHAR[wlen + 1];
								if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
								{
									buff[wlen] = _T('\0');
								}
								tagalbum = buff;
								delete[] buff;
								flg = 0;
								break;
							}
						}
						for (j = i + 4; j < read - 4; j++) {
							if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
								j += 19;
								for (int k = j; k < read - 4; k++) {
									if (bufimage[k] == 0) {
										flg = 1;
										buf[k - j] = 0;
										buf[k - j + 1] = 0;
										buf[k - j + 2] = 0;
										break;
									}
									buf[k - j] = bufimage[k];
								}
							}
							if (flg == 1) {
								const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
								TCHAR* buff = new TCHAR[wlen + 1];
								if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
								{
									buff[wlen] = _T('\0');
								}
								tagname = buff;
								delete[] buff;
								flg = 0;
								break;
							}
						}
						for (j = i + 4; j < read - 4; j++) {
							if (bufimage[j] == 'n' && bufimage[j + 1] == 'a' && bufimage[j + 2] == 'm' && bufimage[j + 7] == 'd' && bufimage[j + 8] == 'a' && bufimage[j + 9] == 't' && bufimage[j + 10] == 'a') {
								j += 19;
								for (int k = j; k < read - 4; k++) {
									if (bufimage[k] == 0) {
										flg = 1;
										buf[k - j] = 0;
										buf[k - j + 1] = 0;
										buf[k - j + 2] = 0;
										break;
									}
									buf[k - j] = bufimage[k];
								}
							}
							if (flg == 1) {
								const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0);
								TCHAR* buff = new TCHAR[wlen + 1];
								if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), buff, wlen))
								{
									buff[wlen] = _T('\0');
								}
								tagfile = buff;
								delete[] buff;
								flg = 0;
								break;
							}
						}
					}
				}
			}
		}
		for (i = 0; i < sizeof(bufimage); i++) {// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61) {
				break;
			}
		}
		if (i != sizeof(bufimage)) {
			m_mp3jake.EnableWindow(TRUE);
		}
		ff.Close();

		wav_start();

	}
	else if (mode == -8) { // flac
		CString ss;
		char buf[1024];
		ss = "";
		ZeroMemory(&sikpi, sizeof(sikpi));
		sikpi.dwSamplesPerSec = savedata.samples; sikpi.dwChannels = 8; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = ((savedata.bit24 == 1) ? 24 : 16);
		if (flg0 == 1) sikpi.dwSamplesPerSec = wavbit;


		if (1) {
			if (ss == "") {
#if UNICODE
				TCHAR* f = filen.GetBuffer();
				kmp = flac_.Open(f, &sikpi);
				filen.ReleaseBuffer();
#else
				kmp = flac_.Open(filen, &sikpi);
#endif
				if (kmp == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
			}
			else {
			}
		}
		wavbit = sikpi.dwSamplesPerSec;
		wavch = sikpi.dwChannels;
		loop1 = 0; oggsize = loop2 = (int)((double)sikpi.dwLength * (double)sikpi.dwSamplesPerSec / 1000.0 / (wavsam / 16.0));
		wavsam = sikpi.dwBitsPerSample;
		CString s; s.Format(L"%d", oggsize);
		//AfxMessageBox(s);
		si1.dwSamplesPerSec = wavbit;
		si1.dwChannels = wavch;
		si1.dwBitsPerSample = wavsam;
		if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
		data_size = oggsize = loop2 * (wavsam / 4);
		if (wavch == 1) oggsize /= 2;
		if (wavch == 1) data_size /= 2;
		m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
		flac_.SetPosition(kmp, 0);
		kbps = 0;
		CFile ff;
		ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL);
		int flg, read = ff.Read(bufimage, sizeof(bufimage));
		ff.Close();
		tagfile = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		flg = 0;
		int i = 0, j;
		for (j = i; j < read - 6; j++) {
			if (bufimage[j] == 'A' && bufimage[j + 1] == 'L' && bufimage[j + 2] == 'B' && bufimage[j + 3] == 'U' && bufimage[j + 4] == 'M' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = 0;
				}
				tagalbum = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'l' && bufimage[j + 2] == 'b' && bufimage[j + 3] == 'u' && bufimage[j + 4] == 'm' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = 0;
				}
				tagalbum = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if (bufimage[j] == 'A' && bufimage[j + 1] == 'R' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'I' && bufimage[j + 4] == 'S' && bufimage[j + 5] == 'T' && bufimage[j + 6] == '=') {
				j += 7;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagname = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 6; j++) {
			if ((bufimage[j] == 'A' || bufimage[j] == 'a') && bufimage[j + 1] == 'r' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'i' && bufimage[j + 4] == 's' && bufimage[j + 5] == 't' && bufimage[j + 6] == '=') {
				j += 7;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagname = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 4; j++) {
			if (bufimage[j] == 'T' && bufimage[j + 1] == 'I' && bufimage[j + 2] == 'T' && bufimage[j + 3] == 'L' && bufimage[j + 4] == 'E' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagfile = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}
		for (j = i; j < read - 4; j++) {
			if ((bufimage[j] == 'T' || bufimage[j] == 't') && bufimage[j + 1] == 'i' && bufimage[j + 2] == 't' && bufimage[j + 3] == 'l' && bufimage[j + 4] == 'e' && bufimage[j + 5] == '=') {
				j += 6;
				for (int k = j; k < read - 4; k++) {
					if (bufimage[k] == 0) {
						flg = 1;
						buf[k - j] = 0;
						buf[k - j + 1] = 0;
						buf[k - j + 2] = 0;
						break;
					}
					buf[k - j] = bufimage[k];
				}
			}
			if (flg == 1) {
				const int wlen = ::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf), NULL, 0) - 1;
				TCHAR* buff = new TCHAR[wlen + 1];
				if (::MultiByteToWideChar(CP_UTF8, 0, buf, strlen(buf) - 1, buff, wlen))
				{
					buff[wlen] = _T('\0');
				}
				tagfile = buff;
				delete[] buff;
				flg = 0;
				break;
			}
		}

		for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
				break;
			}
			if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
				break;
			}
		}
		if (i != 0x300000) {
			m_mp3jake.EnableWindow(TRUE);
		}
		wav_start();
	}
	//	else if (mode == -6) { // Opus
	//		CString ss;
	//		char buf[1024];
	//		ss = "";
	//		ZeroMemory(&sikpi, sizeof(sikpi));
	//		sikpi.dwSamplesPerSec = 48000; sikpi.dwChannels = 2; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = 16;
	//		//if (savedata.bit32 == 1)sikpi.dwBitsPerSample = 32;
	//		//if (flg0 == 1) sikpi.dwSamplesPerSec = wavbit;
	//
	//		if (1) {
	//			if (ss == "") {
	//#if UNICODE
	//				TCHAR *f = filen.GetBuffer();
	//				kmp = opus_.Open(f, &sikpi);
	//				filen.ReleaseBuffer();
	//#else
	//				kmp = m4a_.Open(filen, &sikpi);
	//#endif
	//				if (kmp == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
	//			}
	//			else {
	//			}
	//		}
	//		wavsam = sikpi.dwBitsPerSample;
	//		wavbit = sikpi.dwSamplesPerSec;	wavch = sikpi.dwChannels;	loop1 = 0; oggsize = loop2 = (int)((float)sikpi.dwLength / (wavsam / 4) /*/ (float)1000.0f* (float)sikpi.dwSamplesPerSec*/);
	//		CString s_; s_.Format(L"%d", wavbit);
	//		si1.dwSamplesPerSec = sikpi.dwSamplesPerSec;
	//		si1.dwChannels = wavch;
	//		si1.dwBitsPerSample = wavsam;
	//		Vbr = sikpi.vbr;
	//		if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
	//		data_size = oggsize = loop2*(wavsam / 4);
	//		m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
	//		opus_.SetPosition(kmp, 0);
	//		kbps = 0;
	//
	//		wav_start();
	//
	//	}
	else if (mode == -3) {
		ret2 = 0;
		//		st1();
//		mod = pFunck();
		hDLLk = LoadLibrary(kpi);
		pFunck = (pfnGetKMPModule)::GetProcAddress(hDLLk, SZ_KMP_GETMODULE);
		mod = pFunck();
		if (mod == NULL) {
			MessageBox(_T("なんらかの要因でkpiが開けませんでした。"), _T("ファイルが存在しません。"));
			fnn = "kpi構造体を獲得できませんでした。";
			FreeLibrary(hDLLk);
			m_saisai.EnableWindow(TRUE); endflg = 0; return;
		}
		CString ss;
		ss = filen.Left(filen.ReverseFind(':') - 1);
		ZeroMemory(&sikpi, sizeof(sikpi));
		sikpi.dwSamplesPerSec = savedata.samples; sikpi.dwChannels = 8; sikpi.dwSeekable = 1; sikpi.dwLength = -1; sikpi.dwBitsPerSample = 16;
		if (savedata.bit24 == 1)sikpi.dwBitsPerSample = 24;
		if (savedata.bit32 == 1)sikpi.dwBitsPerSample = 32;
		if (flg0 == 1) sikpi.dwSamplesPerSec = wavbit;
		if (mod) {
			if (ss == "") {
				if (mod->Init) mod->Init();
#if UNICODE
				TCHAR* f = filen.GetBuffer();
				char ff[2048];
				WideCharToMultiByte(CP_ACP, 0, f, -1, ff, filen.GetLength() * 2 + 2, 0, 0);
				if (mod->Open) kmp1 = mod->Open(ff, &sikpi);
#else
				if (mod->Open) kmp1 = mod->Open(filen, &sikpi);
#endif
				if (kmp1 == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
			}
			else {
				if (mod->Init) mod->Init();
#if UNICODE
				TCHAR* f = ss.GetBuffer();
				char ff[2048];
				WideCharToMultiByte(CP_ACP, 0, f, -1, ff, filen.GetLength() * 2 + 2, 0, 0);
				if (mod->Open) kmp1 = mod->Open(ff, &sikpi);
#else
				if (mod->Open) kmp1 = mod->Open(ss, &sikpi);
#endif
				if (kmp1 == NULL) { m_saisai.EnableWindow(TRUE); endflg = 0; return; }
				if (mod->SetPosition) mod->SetPosition(kmp1, _tstoi(filen.Right(4)) * 1000);
			}
		}
		wavbit = sikpi.dwSamplesPerSec;	wavch = sikpi.dwChannels;	loop1 = 0; loop2 = (int)((double)sikpi.dwLength * (double)sikpi.dwSamplesPerSec / 1000.0);
		wavsam = sikpi.dwBitsPerSample;

		if (sikpi.dwLength == (DWORD)-1) loop2 = 0;
		data_size = oggsize = loop2 * (wavsam / 4);
		m_time.SetRange(0, (data_size) / (wavsam / 4), TRUE);
		if (mod->SetPosition) mod->SetPosition(kmp1, 0);
		wav_start();
		//		playwavkpi(bufwav3,0,dwDataLen*4,0);
		CFile ff;
		CString ss11 = filen; ss11.MakeLower();
		if (ss11.Right(3) == "m4a") {
			if (ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
				mp3file = filen;
				ZeroMemory(bufimage, sizeof(bufimage));
				int i;
				ff.Read(bufimage, sizeof(bufimage));
				for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
					if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61) {
						break;
					}
				}
				if (i != 0x300000) {
					m_mp3jake.EnableWindow(TRUE);
				}
			}ff.Close();
		}
		if (ss11.Right(4) == "flac") {
			if (ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
				mp3file = filen;
				ZeroMemory(bufimage, sizeof(bufimage));
				int i;
				ff.Read(bufimage, sizeof(bufimage));
				for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
					if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'j' && bufimage[i + 7] == 'p' && bufimage[i + 8] == 'e' && bufimage[i + 9] == 'g') {
						break;
					}
					if (bufimage[i] == 'i' && bufimage[i + 1] == 'm' && bufimage[i + 2] == 'a' && bufimage[i + 3] == 'g' && bufimage[i + 4] == 'e' && bufimage[i + 5] == '/' && bufimage[i + 6] == 'p' && bufimage[i + 7] == 'n' && bufimage[i + 8] == 'g') {
						break;
					}
				}
				if (i != 0x300000) {
					m_mp3jake.EnableWindow(TRUE);
				}
			}ff.Close();
		}
	}
	else if (mode == -2) {
		CFile ff;
		CString ss11 = ss; ss11.MakeLower();
		if (ss11.Right(3) == "m4a") {
			if (ff.Open(ss, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
				mp3file = ss;
				ZeroMemory(bufimage, sizeof(bufimage));
				int i;
				ff.Read(bufimage, sizeof(bufimage));
				for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
					if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61) {
						break;
					}
				}
				if (i != 0x300000) {
					m_mp3jake.EnableWindow(TRUE);
				}
			}ff.Close();
		}
	}
	//	else
	//		playwavds2(bufwav3,0,dwDataLen*4,0);

	//lrc
	lrcnum = 0;
	int gg = filen.GetLength() * 2;
	int gg2 = filen.ReverseFind(L'.');
	CString filenll = filen.Left(gg2) + L".lrc";
	if (PathFileExistsW(filenll)) {
		CStdioFile a(_tfopen(filenll, _T("r, ccs=UTF-8")));
		CString buf;
		for (; a.ReadString(buf);) {
			//			char *hhh = (char*)buf.GetBuffer();
			//			int size = MultiByteToWideChar(CP_UTF8, 0, hhh, -1, nullptr, 0);
			//			wchar_t* utf16str = new wchar_t[size];
			//			MultiByteToWideChar(CP_UTF8, 0, hhh, -1, utf16str, size);
			//			buf.ReleaseBuffer();
			//			buf = utf16str;
			lrc[lrcnum] = buf.Mid(10);
			lrctm[lrcnum] = _wtoi(buf.Mid(1, 2)) * 60 * 100 + _wtoi(buf.Mid(4, 2)) * 100 + _wtoi(buf.Mid(7, 2));
			lrcnum++;
			//			delete utf16str;
		}
		a.Close();
		lrctm[lrcnum] = 99 * 60 * 100 + 99 * 100 * 99;
		lrcnum++;
	}



	if (mode == 21) {
		wavbit = 48000;
	}
	if (mode == -1) {
		// 零の軌跡用
		CString ss, sss;
		ss = filen.Right(filen.GetLength() - filen.ReverseFind(L'\\') - 1);
		sss = filen.Left(filen.ReverseFind('\\'));
		int fg = 0;
		CFile ffff; if (ffff.Open(sss + L"\\..\\text\\t_bgm._dt", CFile::modeRead)) { fg = 1; ffff.Close(); }
		if (ss.Mid(0, 3) == L"ed7" && fg == 1) {
			CString a;
			switch (_ttoi(ss.Mid(2, 4))) {
			case 7001:
				a = L"零の軌跡";
				break;
			case 7002:
				a = L"way of live -Opening Version-";
				break;
			case 7003:
				a = L"新しき日々～予兆";
				break;
			case 7005:
				a = L"想い破れて・・・";
				break;
			case 7052:
				a = L"碧い軌跡 -Opening size-";
				break;
			case 7053:
				a = L"それでも僕らは。";
				break;
			case 7100:
				a = L"街角の風景";
				break;
			case 7101:
				a = L"明日は明日の風が吹く";
				break;
			case 7102:
				a = L"クロスベルの午後";
				break;
			case 7103:
				a = L"During Mission Accomplishment";
				break;
			case 7104:
				a = L"創立記念祭";
				break;
			case 7105:
				a = L"降水確率10%";
				break;
			case 7106:
				a = L"風船と紙吹雪";
				break;
			case 7110:
				a = L"特務支援課";
				break;
			case 7111:
				a = L"C.S.P.D. -クロスベル警察";
				break;
			case 7113:
				a = L"Arc-en-ciel";
				break;
			case 7114:
				a = L"黒月貿易公司";
				break;
			case 7116:
				a = L"IGNIS";
				break;
			case 7117:
				a = L"TRINITY";
				break;
			case 7120:
				a = L"アルモリカ村";
				break;
			case 7121:
				a = L"鉱山町マインツ";
				break;
			case 7122:
				a = L"Killing Bear";
				break;
			case 7123:
				a = L"聖ウルスラ医科大学";
				break;
			case 7124:
				a = L"クロスベル大聖堂";
				break;
			case 7125:
				a = L"黒の競売会";
				break;
			case 7126:
				a = L"大国にはさまれて";
				break;
			case 7150:
				a = L"新たなる日常";
				break;
			case 7151:
				a = L"動き始めた事態";
				break;
			case 7160:
				a = L"ミシュラムワンダーランド";
				break;
			case 7161:
				a = L"束の間の休息";
				break;
			case 7162:
				a = L"ささやかな晩餐";
				break;
			case 7200:
				a = L"水と草木と青い空";
				break;
			case 7201:
				a = L"片手にはレモネード";
				break;
			case 7202:
				a = L"木霊の道";
				break;
			case 7203:
				a = L"古の鼓動";
				break;
			case 7204:
				a = L"On The Green Road";
				break;
			case 7205:
				a = L"鉄橋を越えて";
				break;
			case 7250:
				a = L"木洩れ日の中の静寂";
				break;
			case 7251:
				a = L"偽りの楽土を越えて";
				break;
			case 7300:
				a = L"ジオフロント";
				break;
			case 7301:
				a = L"七耀の煌き";
				break;
			case 7302:
				a = L"ルバーチェ商会";
				break;
			case 7303:
				a = L"鳴るはずのない鐘";
				break;
			case 7304:
				a = L"忘れられし幻夢の狭間";
				break;
			case 7305:
				a = L"A Light Illuminating The Depths";
				break;
			case 7350:
				a = L"Dの残影";
				break;
			case 7351:
				a = L"異変の兆し";
				break;
			case 7352:
				a = L"Mystic Core";
				break;
			case 7353:
				a = L"最果ての樹";
				break;
			case 7354:
				a = L"暴魔の呼び声";
				break;
			case 7356:
				a = L"不明";
				break;
			case 7400:
				a = L"Get Over The Barrier!";
				break;
			case 7401:
				a = L"Arrest The Criminal";
				break;
			case 7402:
				a = L"Formidable Enemy";
				break;
			case 7403:
				a = L"Stand Up Battle Formation Again!";
				break;
			case 7404:
				a = L"Inevitable Struggle";
				break;
			case 7405:
				a = L"Demonic Drive";
				break;
			case 7406:
				a = L"Arrival Existence";
				break;
			case 7408:
				a = L"これが俺たちの力だ!";
				break;
			case 7450:
				a = L"Seize The Truth!";
				break;
			case 7451:
				a = L"Concentrate All Firepower!!";
				break;
			case 7452:
				a = L"Conflicting Passions";
				break;
			case 7453:
				a = L"Unexpected Emergency";
				break;
			case 7454:
				a = L"Mythtic Roar";
				break;
			case 7455:
				a = L"Destruction Impulse";
				break;
			case 7458:
				a = L"Unfathomed Force";
				break;
			case 7459:
				a = L"The Azure Arbitrator";
				break;
			case 7460:
				a = L"効果音";
				break;
			case 7500:
				a = L"金の太陽、銀の月　-陽の熱情";
				break;
			case 7501:
				a = L"金の太陽、銀の月　-月の慕情";
				break;
			case 7502:
				a = L"金の太陽、銀の月　-童心";
				break;
			case 7503:
				a = L"金の太陽、銀の月　-運命の刻";
				break;
			case 7504:
				a = L"金の太陽、銀の月　-譲れぬ想い";
				break;
			case 7505:
				a = L"金の太陽、銀の月　-幾千の夜を越えて";
				break;
			case 7506:
				a = L"金の太陽、銀の月　-夜明け～大団円";
				break;
			case 7507:
				a = L"Intense Chase";
				break;
			case 7509:
				a = L"守りぬく意志";
				break;
			case 7510:
				a = L"叡智への誘い";
				break;
			case 7511:
				a = L"危地";
				break;
			case 7512:
				a = L"揺るぎない強さ";
				break;
			case 7513:
				a = L"夜景に霞む星空";
				break;
			case 7514:
				a = L"いつかきっと";
				break;
			case 7515:
				a = L"柔らかな心";
				break;
			case 7516:
				a = L"点と線";
				break;
			case 7517:
				a = L"一触即発";
				break;
			case 7518:
				a = L"Foolish Gig";
				break;
			case 7519:
				a = L"リベールからの風";
				break;
			case 7520:
				a = L"とどいた想い";
				break;
			case 7521:
				a = L"Underground Kids";
				break;
			case 7522:
				a = L"Terminal Room";
				break;
			case 7523:
				a = L"響きあう心";
				break;
			case 7524:
				a = L"Limit Break";
				break;
			case 7525:
				a = L"パラダイスミ☆";
				break;
			case 7526:
				a = L"Gnosis";
				break;
			case 7527:
				a = L"Get Over The Barrier! -Roaring Version-";
				break;
			case 7528:
				a = L"それぞれの明日";
				break;
			case 7529:
				a = L"効果音楽1";
				break;
			case 7530:
				a = L"効果音楽2";
				break;
			case 7531:
				a = L"効果音楽3";
				break;
			case 7532:
				a = L"効果音楽4";
				break;
			case 7533:
				a = L"踏み出す勇気";
				break;
			case 7534:
				a = L"その背中を見つめて";
				break;
			case 7540:
				a = L"不明";
				break;
			case 7541:
				a = L"不明";
				break;
			case 7542:
				a = L"不明";
				break;
			case 7543:
				a = L"不明";
				break;
			case 7544:
				a = L"不明";
				break;
			case 7550:
				a = L"オルキスタワー";
				break;
			case 7551:
				a = L"Catastrophe";
				break;
			case 7552:
				a = L"碧き雫";
				break;
			case 7553:
				a = L"神機降臨";
				break;
			case 7554:
				a = L"ふるわれる奇蹟";
				break;
			case 7555:
				a = L"予定外の奇蹟";
				break;
			case 7556:
				a = L"鋼鉄の咆哮 -脅威-";
				break;
			case 7560:
				a = L"雨の日の真実";
				break;
			case 7561:
				a = L"不穏";
				break;
			case 7562:
				a = L"効果音";
				break;
			case 7563:
				a = L"犠牲の先の希望";
				break;
			case 7564:
				a = L"Strange Feel";
				break;
			case 7565:
				a = L"Exhilarating Ride";
				break;
			case 7566:
				a = L"それぞれの正義";
				break;
			case 7567:
				a = L"乗り越えるべき壁";
				break;
			case 7568:
				a = L"月下の想い";
				break;
			case 7569:
				a = L"Miss You";
				break;
			case 7570:
				a = L"天の車";
				break;
			case 7571:
				a = L"突きつけられた現実";
				break;
			case 7572:
				a = L"効果音";
				break;
			case 7573:
				a = L"全てを識るもの";
				break;
			case 7574:
				a = L"想い、辿り着く場所";
				break;
			case 7575:
				a = L"揺れ動く心";
				break;
			case 7576:
				a = L"星降る夜に";
				break;
			case 7577:
				a = L"効果音";
				break;
			case 7578:
				a = L"効果音";
				break;
			case 7579:
				a = L"効果音";
				break;
			case 7580:
				a = L"効果音";
				break;
			case 7581:
				a = L"本当の絆";
				break;
			case 7582:
				a = L"猛き獣たち";
				break;
			case 7583:
				a = L"西ゼムリア通商会議";
				break;
			case 7584:
				a = L"効果音";
				break;
			case 7585:
				a = L"千年の妄執";
				break;
			case 7586:
				a = L"鋼鉄の咆哮 -死線-";
				break;
			case 7587:
				a = L"ポムっと! -お花見団子の逆襲-";
				break;
			case 7588:
				a = L"Fateful Confrontation -ポムっと! Ver.-";
				break;
			case 7589:
				a = L"ポムりますか";
				break;
			case 7590:
				a = L"エリィ絶叫コースター";
				break;
			case 7591:
				a = L"小さな英雄 -オルゴール-";
				break;
			case 7592:
				a = L"TOWER OF THE SHADOW OF DEATH -Jukebox-";
				break;
			}
			stitle = a;
		}
	}
	if (m_c2.GetCheck() == 1)
	{
		cc1 = 1;
		if (cc.Open(filen + _T(".wav"), CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary, NULL) != TRUE) {
			m_saisai.EnableWindow(TRUE);
			endflg = 0;
			return;
		}
		if (ogg)	cc.Write(ogg, whsize);
		if (wav) cc.Write(wav, whsize);
	}
	//if (mode == -6) { wavbit = 48000; }


	WAVEFORMATEX wfx1;
	if (wavsam < 0)
		wfx1.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
	else
		wfx1.wFormatTag = WAVE_FORMAT_PCM;
	wfx1.nChannels = wavch;
	wfx1.nSamplesPerSec = wavbit;
	wfx1.wBitsPerSample = abs(wavsam);
	wfx1.nBlockAlign = wfx1.nChannels * wfx1.wBitsPerSample / 8;
	wfx1.nAvgBytesPerSec = wfx1.nSamplesPerSec * wfx1.nBlockAlign;
	wfx1.cbSize = 0;

	static const GUID GUID_SUBTYPE_PCM = { 0x00000001, 0x0000, 0x0010,{ 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71 } };

	DWORD targetSpeakers = 0;
	switch (wavch) {
	case 1:
		targetSpeakers |= SPEAKER_FRONT_CENTER;
		break;
	case 2:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT;
		break;
	case 3:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			;
		break;
	case 4:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			;
		break;
	case 5:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			;
		break;
	case 6:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT | SPEAKER_LOW_FREQUENCY
			;
		break;
	case 7:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			| SPEAKER_SIDE_LEFT | SPEAKER_LOW_FREQUENCY
			;
		break;
	case 8:
		targetSpeakers |=
			SPEAKER_FRONT_LEFT
			| SPEAKER_FRONT_RIGHT
			| SPEAKER_FRONT_CENTER
			| SPEAKER_BACK_LEFT
			| SPEAKER_BACK_RIGHT
			| SPEAKER_SIDE_LEFT
			| SPEAKER_SIDE_RIGHT | SPEAKER_LOW_FREQUENCY
			;
		break;
	}
	int nChannels = __popcnt(targetSpeakers);
	WAVEFORMATEXTENSIBLE wfx = {};
	wfx.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
	wfx.Format.nChannels = nChannels;
	wfx.Format.nSamplesPerSec = wavbit;
	wfx.Format.wBitsPerSample = abs(wavsam);
	wfx.Format.nBlockAlign = (WORD)(wfx.Format.wBitsPerSample / 8 * wfx.Format.nChannels);
	wfx.Format.nAvgBytesPerSec = (DWORD)(wfx.Format.nSamplesPerSec * wfx.Format.nBlockAlign);
	wfx.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	wfx.dwChannelMask = targetSpeakers;
	if (wavsam < 0)
		wfx.SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
	else
		wfx.SubFormat = GUID_SUBTYPE_PCM;
	//if (wavbit2 != wavbit || wavsam == 24 || si1.dwBitsPerSample || sikpi.dwBitsPerSample) {
	ReleaseDXSound();
	if (WASAPIInit() == 0) init(m_hWnd, wavbit);
	//}
	wavsam = abs(wavsam);
	wavbit2 = wavbit;
	int i, iii = 0;
	double ik = 32.0;
	double d2 = 0;
	double il = 8.71712838;
	d2 = 0;

	for (i = 0; i <= 88; i++, iii++) { // 低音域用
		logtbl[i] = (int)(il * pow(2.0, (double)(iii) / ik));// / ((wavbit / 44100.0)*16.0);// *(double)BUFSZH1 / (double)192000 / 4.0 + 1.0);
		//		double tl = wavbit / 44100.0;
//		logtbl[i] = (int)((double)syuha[i]) / ((((87/tl) - (i/tl)) / (11.0) + 1.0)) / (tl);//(44100.0/ (double)wavbit) * ((double)wavsam / 8.0) *

		if (i < 20) {
			if (wavbit > 90000)
				ik -= (0.15 + d2);// -(((double)wavbit / 44100.0) / 50.0 - 0.02));
			else
				ik -= (0.20 + d2);// -(((double)wavbit / 44100.0) / 50.0 - 0.02));
		}
		else {
			if (wavbit > 90000)
				ik -= (0.14 + d2);// -(((double)wavbit / 44100.0) / 50.0 - 0.02));
			else
				ik -= (0.18 + d2);// -(((double)wavbit / 44100.0) / 50.0 - 0.02));
		}

		if (i != 0) {
			if (iii > 240) {
				break;
			}
			if (logtbl[i] <= logtbl[i - 1]) {
				i--; continue;
			}
		}
		//		if( logtbl[i] > BUFSZH1 -1 ) logtbl[i] = BUFSZH1 -1;

	}


	//    mmRes = waveOutOpen(&hwo,WAVE_MAPPER,&wfx1,(DWORD)(LPVOID)0,(DWORD)NULL,CALLBACK_NULL);

	fade1 = 0;
	//-------------------------------------------------------------------
	//if (pAudioClient == NULL) {
	DSBUFFERDESC dsbd;
	flg0 = 0;
	for (;;) {
		ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
		dsbd.dwSize = sizeof(DSBUFFERDESC);
		dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLVOLUME;// | DSBCAPS_CTRL3D;
		dsbd.dwBufferBytes = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM;
		if (wavch > 2)
			dsbd.lpwfxFormat = (LPWAVEFORMATEX)&wfx;
		else
			dsbd.lpwfxFormat = &wfx1;
		//dsbd.guid3DAlgorithm = DS3DALG_HRTF_LIGHT;
		HRESULT r;
		ReleaseDXSound();
		if (WASAPIInit() == 0) init(m_hWnd, wavbit);
		r = m_ds->CreateSoundBuffer(&dsbd, &m_dsb1, NULL);
		if (m_dsb1 == NULL || m_p == NULL) {
			if (flg0 == 0) {
				CString s; s.Format(L"%d", savedata.samples);
				MessageBox(s + L"Hzのサンプリングレートにサウンドカードが対応していません\n低いサンプリングレートを試みます。\n少々時間が掛かる場合があります。", _T("ogg/wav簡易プレイヤ"));
				flg0 = 1;
			}
			wavbit -= 1000;
			if (wavbit <= 0) {
				MessageBox(L"0Hzまで試みましたが、対応するサンプリングレートが存在しませんでした。\nサウンドボード(カード)が存在していない可能性があります。", _T("ogg/wav簡易プレイヤ"));
				tagfile = fnn;
				m_saisai.EnableWindow(TRUE);
				endflg = 0;
				return;
			}
			wfx.Format.nSamplesPerSec = wavbit;
			wfx.Format.nAvgBytesPerSec = (DWORD)(wfx.Format.nSamplesPerSec * wfx.Format.nBlockAlign);
			wfx1.nSamplesPerSec = wavbit;
			wfx1.nAvgBytesPerSec = wfx1.nSamplesPerSec * wfx1.nBlockAlign;
			continue;
			endflg = 0;
			return;
		}
		for (i = 0; i < 10; i++) {
			r = m_dsb1->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_dsb);

			if (m_dsb == NULL) { DoEvent(); Sleep(100); continue; }
			else break;
		}
		if (m_dsb == NULL) {
			AfxMessageBox(_T("DirectSoundが開けませんでした。"));
			if (r == DSERR_ALLOCATED) {
				AfxMessageBox(_T("優先レベルなどのリソースが他の呼び出しによって既に使用中であるため、要求は失敗した。"));
			}
			else if (r == DSERR_CONTROLUNAVAIL) {
				AfxMessageBox(_T("呼び出し元が要求するバッファ コントロール (ボリューム、パンなど) は利用できない。"));
			}
			else if (r == DSERR_BADFORMAT) {
				AfxMessageBox(_T("指定したウェーブ フォーマットはサポートされていない。"));
			}
			else if (r == DSERR_INVALIDPARAM) {
				AfxMessageBox(_T("無効なパラメータが関数に渡された。"));
			}
			else if (r == DSERR_NOAGGREGATION) {
				AfxMessageBox(_T("このオブジェクトは COM 集合化をサポートしない。"));
			}
			else if (r == DSERR_OUTOFMEMORY) {
				AfxMessageBox(_T("DirectSound サブシステムは、呼び出し元の要求を完了するための十分なメモリを割り当てられなかった。"));
			}
			else if (r == DSERR_UNINITIALIZED) {
				AfxMessageBox(_T("他のメソッドを呼び出す前に IDirectSound::Initialize メソッドを呼び出さなかったか、呼び出しが成功しなかった。"));
			}
			else if (r == DSERR_UNSUPPORTED) {
				AfxMessageBox(_T("呼び出した関数はこの時点ではサポートされていない。"));
			}
			else {}

			tagfile = fnn;
			m_saisai.EnableWindow(TRUE);
			endflg = 0;
			return;
		}
		if (m_dsb) {
			if (flg0 == 1) {
				CString s; s.Format(L"%d", wavbit);
				MessageBox(s + L"Hzのサンプリングレートでヒットしましたため、該当サンプリングレートで演奏します。", _T("ogg/wav簡易プレイヤ"));
				savedata.samples = wavbit;
				SetTimer(9100, 100, NULL);
				return;
			}
			break;
		}
	}
	//}
	//else {
	//		if (wavch > 2)
	//		WASAPIChange((LPWAVEFORMATEX)&wfx);
	//		else
	//			WASAPIChange(&wfx1);
	//}
	//m_dsb->QueryInterface(IID_IDirectSound3DBuffer, (LPVOID*)m_dsb3d);

	DWORD le = WAVDAStartLen;
	ttt = WAVDAStartLen;

	stf = 0;
	plf = 1; fade1 = 0; fade = 1.0f; fadeadd = 0.0f;
	poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
	mcnt = mcnt1 = mcnt2 = mcnt3 = mcnt4 = mcnt5 = mcnt6 = 0;
	char* pdsb;
	lo = 0; loc = 0;

	if (loop1 == 0 && loop2 == 0) {
		m_time.SetSelection(0, data_size / 4);
		m_time.Invalidate();
	}
	else {
		m_time.SetSelection(loop1, (loop1 + loop2));
		m_time.Invalidate();
	}

	int len1, len2, len3;
	if (true) {
		ULONG PlayCursor, WriteCursor = 0;
		if (m_dsb)m_dsb->GetCurrentPosition(&PlayCursor, &WriteCursor);//再生位置取得
		len1 = (int)WriteCursor;//書き込み範囲取得
		len2 = 0;
		if (len1 < 0) {
			len1 = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM / 24; len2 = WriteCursor;
		}
		if (len2 < 0)
			len2 = 0;
		if ((mode >= 10 && mode <= 21) || mode < -10 || mode == -6)
			playwavadpcm(bufwav3, 0, len1, len2);//データ獲得
		else if (mode == -10)
			playwavmp3(bufwav3, 0, len1, len2);//データ獲得
		else if (mode == -3)
			playwavkpi(bufwav3, 0, len1, len2);//データ獲得
		else if (mode == -7)
			playwavdsd(bufwav3, 0, len1, len2);//データ獲得
		else if (mode == -8)
			playwavflac(bufwav3, 0, len1, len2);//データ獲得
		else if (mode == -9)
			playwavm4a(bufwav3, 0, len1, len2);//データ獲得
		else
			playwavds2(bufwav3, 0, len1, len2);//データ獲得
		m_dsb->Lock(0, len1 + len2, (LPVOID*)&pdsb, (DWORD*)&len3, NULL, 0, 0);
		memcpy(pdsb, bufwav3, len3);
		m_dsb->Unlock(pdsb, len3, NULL, 0);
		m_dsb->SetVolume((savedata.dsvol - 1) * 10);
		CFile f123;
		int flggg = 0;
		if (mode != -1) {
			if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
				f123.Close();
				if (IDYES == MessageBox(_T("途中再生データが存在します。\n前回中断した部分から再生しますか？\nはい = 途中から再生\nいいえ = はじめから再生"), _T("再生確認"), MB_YESNO)) {
					flggg = 1;
				}
				else {
					CFile::Remove(filen + _T(".save"));
				}
			}
			if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE && flggg == 1) {
				f123.Close();
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl) { for (int y = 0; y < 45; y++) { Sleep(10); DoEvent(); }pMediaControl->Run(); }
				if (mode == -10) {
					if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
						f123.Read(&playb, sizeof(__int64));
						if (savedata.mp3orig) {
							mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch);
						}
						else {
							mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch);
						}
						f123.Close();
					}
				}
				if (mode == -2) {
					if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
						f123.Read(&aa1_, sizeof(double));
						pMainFrame1->seek((LONGLONG)(((float)((float)aa1_ * 100.0f * 100000.0f))));
						f123.Close();
					}
				}
			}
			else {
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl) { for (int y = 0; y < 45; y++) { Sleep(10); DoEvent(); }pMediaControl->Run(); }
				if (pMainFrame1) { pMainFrame1->seek(0); }
			}
		}
		else {
			if (pMainFrame1) pMainFrame1->plays2();
			if (pMediaControl) { for (int y = 0; y < 45; y++) { Sleep(10); DoEvent(); }pMediaControl->Run(); }
			if (pMainFrame1) { pMainFrame1->seek(0); }
		}
		syukai = 0;
		m_dsb->Play(0, 0, DSBPLAY_LOOPING);
		fade1 = 0;
		sflg = FALSE;
		DoEvent();
		for (;;) {
			if (sflg == FALSE) break;
			DoEvent();
		}
		AfxBeginThread((AFX_THREADPROC)HandleNotifications, NULL, THREAD_PRIORITY_TIME_CRITICAL);
	}
	endflg = 0;
	SetTimer(9000, 10, NULL);
	//	::SetPriorityClass(m_thread, HIGH_PRIORITY_CLASS);
	endf = 0;
	if (pl && plw) { if (pl->m_loop.GetCheck() == TRUE) { if (loop2 == 0)loop2 = oggsize / 4; } }
	if (loop2 == 0) endf = 1;
	if (mode == -3 || mode == -8 || mode == -9 || mode == -10) endf = 1;
	loopcnt = 0;
	if (pl && plw) {
		int plc = 1;
		if (mode == -10)
			plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, (oggsize / (2 * wavch * wavbit / 4) / ((mode == -9) ? 4 : 1)), 1);
		else if (mode == -9 || mode == -8 || mode == -7) {
			double wavv[] = { 0,1.0,2.0,2.0,2.0,2.0,2.0 };//(double)(wavbit2/wavv[wavch])
			plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, (int)(
				(double)oggsize / (double)(wavbit * 2 * wavv[wavch]) / (double)(wavsam / 16.0f)
				), 1);
		}
		else if (mode == -3) {
			if (oggsize == 0)
				if (mode == -3 && fnn.Find(L".hes") == -1)
					plc = pl->Add(fnn, mode, loop1, loop2, tagname, tagalbum, filen, 0, -1, 1);
				else
					plc = pl->chk(fnn, mode, tagname, filen, 0);
			else
				if (mode == -3 && fnn.Find(L".hes") == -1)
					plc = pl->Add(fnn, mode, loop1, loop2, tagname, tagalbum, filen, 0, oggsize / (2 * wavch * wavbit), 1);
				else
					plc = pl->chk(fnn, mode, tagname, filen, 0);
		}
		else if (!((pMainFrame1 && mode == -1) || mode == -3))
			plc = pl->Add(fnn, mode, loop1, loop2, stitle, tagalbum, filen, ret2, oggsize / (2 * wavch * wavbit));
		else
			plc = pl->chk(fnn, mode, tagname, filen, 0);

		if (plc == -1) {
			int i = pl->m_lc.GetItemCount() - 1;
			plcnt = i;
			pl->SIcon(i);
		}
		else {
			plcnt = plc;
			pl->SIcon(plc);
		}
	}
	m_saisai.EnableWindow(TRUE); playy = 1;
	ps = 0;
	m_ps.SetWindowText(_T("一時停止"));
	SetTimer(1250, 100, NULL);
	fade1 = 0;
	if (maini) maini->SetActiveWindow();
	SetActiveWindow();
}

void COggDlg::SetAdd(CString fnn, int mode, int loop1, int loop2, CString filen, int ret2, REFTIME time)
{
	if (pl && plw) {
		int plc;
		plc = pl->Add(fnn, mode, loop1, loop2, _T(""), _T(""), filen, ret2, (int)time);
		if (plc == -1) {
			int i = pl->m_lc.GetItemCount() - 1;
			plcnt = i;
			pl->SIcon(i);
		}
		else {
			plcnt = plc;
			pl->SIcon(plc);
		}
	}
}

HANDLE hp;
//スレッド
void CWread::wavread()
{
	DWORD dl, dwDataLen = (WAVDALen / OUTPUT_BUFFER_NUM) * 4; dl = dwDataLen;
	if (mode == 21) {
		CString a = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		switch (_ttoi(a.Mid(2, 4))) {
		case 8001:
			a = L"特科クラス《VII組》";
			break;
		case 8002:
			a = L"ただひたすらに、前へ";
			break;
		case 8100:
			a = L"近郊都市トリスタ";
			break;
		case 8101:
			a = L"交易町ケルディック";
			break;
		case 8102:
			a = L"翡翠の公都バリアハート";
			break;
		case 8103:
			a = L"湖畔の街レグラム";
			break;
		case 8104:
			a = L"黒銀の鋼都ルーレ";
			break;
		case 8106:
			a = L"遊牧民の集落";
			break;
		case 8107:
			a = L"緋の帝都ヘイムダル";
			break;
		case 8108:
			a = L"癒しの我が家";
			break;
		case 8109:
			a = L"ダイニングバー《F》";
			break;
		case 8110:
			a = L"常在戦場の気概";
			break;
		case 8111:
			a = L"ガレリアの巨壁";
			break;
		case 8120:
			a = L"足湯の温もり";
			break;
		case 8121:
			a = L"静寂の郷";
			break;
		case 8122:
			a = L"明日への休息";
			break;
		case 8123:
			a = L"春の陽射し";
			break;
		case 8125:
			a = L"カレイジャス発進！";
			break;
		case 8126:
			a = L"目覚める意志";
			break;
		case 8127:
			a = L"白銀の巨船";
			break;
		case 8150:
			a = L"放課後の時間";
			break;
		case 8152:
			a = L"さわやかな朝";
			break;
		case 8153:
			a = L"雨音の学院";
			break;
		case 8154:
			a = L"爽やかな陽射し";
			break;
		case 8156:
			a = L"トールズ士官学院祭";
			break;
		case 8158:
			a = L"青空の開放感";
			break;
		case 8159:
			a = L"自由行動日";
			break;
		case 8200:
			a = L"異郷の空";
			break;
		case 8201:
			a = L"峡谷道を往く";
			break;
		case 8202:
			a = L"精霊の小道";
			break;
		case 8203:
			a = L"蒼穹の大地";
			break;
		case 8210:
			a = L"戦火を越えて";
			break;
		case 8212:
			a = L"Trudge Along";
			break;
		case 8213:
			a = L"冬の訪れ";
			break;
		case 8300:
			a = L"旧校舎の謎";
			break;
		case 8301:
			a = L"探索";
			break;
		case 8302:
			a = L"深淵へ向かう";
			break;
		case 8303:
			a = L"聖女の城";
			break;
		case 8304:
			a = L"明日を掴むために";
			break;
		case 8305:
			a = L"地下に眠る遺構";
			break;
		case 8308:
			a = L"世の礎たるために";
			break;
		case 8310:
			a = L"精霊窟";
			break;
		case 8311:
			a = L"不明";
			break;
		case 8312:
			a = L"Phantasmal Blaze";
			break;
		case 8313:
			a = L"夢幻回廊";
			break;
		case 8315:
			a = L"幻煌";
			break;
		case 8400:
			a = L"The Glint of Cold Steel";
			break;
		case 8401:
			a = L"Tie a Link of ARCUS!";
			break;
		case 8402:
			a = L"Belief";
			break;
		case 8403:
			a = L"Even if Driven to the Wall";
			break;
		case 8404:
			a = L"Eliminate Crisis!";
			break;
		case 8405:
			a = L"Exceed!";
			break;
		case 8406:
			a = L"Don't be Defeated by a Friend!";
			break;
		case 8407:
			a = L"Machinery Attack";
			break;
		case 8408:
			a = L"巨イナルチカラ";
			break;
		case 8409:
			a = L"The Decisive Collision";
			break;
		case 8410:
			a = L"この手で道を切り拓く!";
			break;
		case 8411:
			a = L"赤点です...";
			break;
		case 8412:
			a = L"Unknown Threat";
			break;
		case 8413:
			a = L"不明";
			break;
		case 8420:
			a = L"Heated Mind";
			break;
		case 8421:
			a = L"不明";
			break;
		case 8423:
			a = L"Impatient";
			break;
		case 8424:
			a = L"Severe Blow";
			break;
		case 8426:
			a = L"Transcend Beat";
			break;
		case 8429:
			a = L"Blue Destination";
			break;
		case 8430:
			a = L"Heteromorphy";
			break;
		case 8431:
			a = L"輝ける明日へ";
			break;
		case 8435:
			a = L"迫る巨影";
			break;
		case 8441:
			a = L"E.O.V";
			break;
		case 8442:
			a = L"不明";
			break;
		case 8500:
			a = L"Strain";
			break;
		case 8501:
			a = L"夜のひととき";
			break;
		case 8502:
			a = L"トラブル発生";
			break;
		case 8503:
			a = L"鉄路遥々";
			break;
		case 8504:
			a = L"旅愁";
			break;
		case 8505:
			a = L"皇城にて";
			break;
		case 8506:
			a = L"Let's Study";
			break;
		case 8507:
			a = L"知恵を絞って";
			break;
		case 8508:
			a = L"実技教練";
			break;
		case 8509:
			a = L"寮に帰ろう";
			break;
		case 8510:
			a = L"アーベントタイム";
			break;
		case 8512:
			a = L"鉄の統率";
			break;
		case 8513:
			a = L"暗躍";
			break;
		case 8514:
			a = L"想いの行き先";
			break;
		case 8515:
			a = L"傷心";
			break;
		case 8516:
			a = L"揺らめく炎を見つめて";
			break;
		case 8517:
			a = L"一途な気持ち";
			break;
		case 8520:
			a = L"臨戦態勢";
			break;
		case 8521:
			a = L"Seriousness";
			break;
		case 8522:
			a = L"静かなる昂揚";
			break;
		case 8523:
			a = L"暖かな夕餉";
			break;
		case 8524:
			a = L"Atrocious Raid";
			break;
		case 8525:
			a = L"全てを賭して今、ここに立つ";
			break;
		case 8527:
			a = L"新しい仲間たち";
			break;
		case 8528:
			a = L"不透明な事態";
			break;
		case 8529:
			a = L"鉄血へのレクイエム";
			break;
		case 8530:
			a = L"幻想の唄 -PHANTASMAGORIA-";
			break;
		case 8531:
			a = L"刻ハ至レリ";
			break;
		case 8532:
			a = L"目覚めし伝承";
			break;
		case 8533:
			a = L"唯一の希望";
			break;
		case 8535:
			a = L"不明";
			break;
		case 8537:
			a = L"不明";
			break;
		case 8538:
			a = L"今はまだ...";
			break;
		case 8539:
			a = L"あの日に見た夜空";
			break;
		case 8540:
			a = L"偽りの時間";
			break;
		case 8541:
			a = L"紅き翼 -新たなる風-";
			break;
		case 8550:
			a = L"再会";
			break;
		case 8551:
			a = L"かけがえのない人へ";
			break;
		case 8552:
			a = L"惜しむように、愛おしむように";
			break;
		case 8553:
			a = L"ライノの花が咲く頃";
			break;
		case 8555:
			a = L"戦場の掟";
			break;
		case 8556:
			a = L"Remaining Glow";
			break;
		case 8557:
			a = L"深淵の魔女";
			break;
		case 8558:
			a = L"ALTINA";
			break;
		case 8559:
			a = L"威風";
			break;
		case 8560:
			a = L"一撃に賭ける";
			break;
		case 8561:
			a = L"ユミル渓谷道";
			break;
		case 8562:
			a = L"Awakening";
			break;
		case 8563:
			a = L"Blitzkrieg";
			break;
		case 8564:
			a = L"魔王の凱歌";
			break;
		case 8566:
			a = L"内なる黄昏";
			break;
		case 8567:
			a = L"蘇る記憶";
			break;
		case 8570:
			a = L"静かな決意";
			break;
		case 8571:
			a = L"乾坤一擲";
			break;
		case 8572:
			a = L"交戦";
			break;
		case 8573:
			a = L"効果音";
			break;
		case 8600:
			a = L"大市の賑わい";
			break;
		case 8601:
			a = L"剣の遊戯";
			break;
		case 8602:
			a = L"紙一重の攻防";
			break;
		case 8603:
			a = L"走れマッハ号!";
			break;
		case 8605:
			a = L"効果音";
			break;
		case 8606:
			a = L"効果音";
			break;
		case 8607:
			a = L"星屑のカンタータ";
			break;
		case 8608:
			a = L"効果音";
			break;
		case 8609:
			a = L"Sonata No.45";
			break;
		case 8610:
			a = L"効果音";
			break;
		case 8620:
			a = L"雪ウサギを追いかけて";
			break;
		case 8621:
			a = L"Take The Windward!";
			break;
		case 8622:
			a = L"効果音";
			break;
		case 8623:
			a = L"効果音";
			break;
		case 8624:
			a = L"効果音";
			break;
		case 8625:
			a = L"効果音";
			break;
		case 8627:
			a = L"効果音";
			break;
		case 8628:
			a = L"不明";
			break;
		case 8629:
			a = L"効果音";
			break;
		case 8700:
			a = L"音楽";
			break;
		case 8703:
			a = L"音楽";
			break;
		case 8704:
			a = L"音楽";
			break;
		case 8710:
			a = L"音楽";
			break;
		case 8711:
			a = L"音楽";
			break;
		}
		stitle = a;
		lenl = 0;
		FILE* fp = _wfsopen(filen, L"rb", 0x40);
		fseek(fp, 0, SEEK_END);
		long length = ftell(fp);
		fseek(fp, length - 10000, SEEK_SET);
		char* buffer = (char*)malloc(10000);
		fread(buffer, 1, 10000, fp);
		int jj;
		int flg = 0;
		for (jj = 0; jj < 9996; jj++) {
			if (*(buffer + jj) == 's' && *(buffer + jj + 1) == 'm' && *(buffer + jj + 2) == 'p' && *(buffer + jj + 3) == 'l') {
				flg = 1;
				break;
			}
		}
		char* p = buffer + jj;
		if (flg == 1) {
			p = p + 4;//smplをスキップ
			p = p + 0x30;
			loop1 = *(int*)p;
			loop2 = *(int*)(p + 4) - loop1;
		}
		else {
			loop1 = loop2 = 0;
		}
		fclose(fp);
		free(buffer);
		//----------
		CFile adpcmf;
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		long wavdata_length;
		adpcmf.Seek(0x28, CFile::begin);
		adpcmf.Read(&wavdata_length, 4);
		adbuf2 = (char*)calloc(wavdata_length * 2 + dl * 2, 1);
		adpcmf.Read(adbuf2, dwDataLen * 2);
		data_size = oggsize = wavdata_length;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		wavwait = 1;
		int si = wavdata_length + dl * 2;
		dwDataLen += dl;
		si -= dwDataLen * 2;
		for (; si > 0;) {
			adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
			dwDataLen += dl; si -= dl;
			if (thend1 == TRUE) { thend = 1; adpcmf.Close();  return; }
		}
		adpcmf.Close();
	}
	else if (mode == -6) {
		CString a = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		CString b = a.Mid(6, 1);
		int err;
		int fff = 0;
		//Ys X
		if (a == L"y_act_e002.opus") {
			a = L"Operation SANDRAS";
			fff = 1;
		}
		if (a == L"y_act_e002_s1.opus") {
			a = L"Operation SANDRAS(重低音)";
			fff = 1;
		}
		if (a == L"y_b100.opus") {
			a = L"Overblaze";
			fff = 1;
		}
		if (a == L"y_b100_s1.opus") {
			a = L"Overblaze(重低音)";
			fff = 1;
		}
		if (a == L"y_b200.opus") {
			a = L"Through the North Wind";
			fff = 1;
		}
		if (a == L"y_b200_s1.opus") {
			a = L"Through the North Wind(重低音)";
			fff = 1;
		}
		if (a == L"y_b210.opus") {
			a = L"高鳴る鼓動";
			fff = 1;
		}
		if (a == L"y_b210_s1.opus") {
			a = L"高鳴る鼓動(重低音)";
			fff = 1;
		}
		if (a == L"y_b300.opus") {
			a = L"石火の如く";
			fff = 1;
		}
		if (a == L"y_b300_s1.opus") {
			a = L"石火の如く(重低音)";
			fff = 1;
		}
		if (a == L"y_b400.opus") {
			a = L"Can You Do It";
			fff = 1;
		}
		if (a == L"y_b400_s1.opus") {
			a = L"Can You Do It(重低音)";
			fff = 1;
		}
		if (a == L"y_b500.opus") {
			a = L"BERSERK -戦斧の咆哮-";
			fff = 1;
		}
		if (a == L"y_b500_s1.opus") {
			a = L"BERSERK -戦斧の咆哮-(重低音)";
			fff = 1;
		}
		if (a == L"y_b510.opus") {
			a = L"悪意の洗礼";
			fff = 1;
		}
		if (a == L"y_b510_s1.opus") {
			a = L"悪意の洗礼(重低音)";
			fff = 1;
		}
		if (a == L"y_b520.opus") {
			a = L"The Ultimate Pleasure in My Hands";
			fff = 1;
		}
		if (a == L"y_b520_s1.opus") {
			a = L"The Ultimate Pleasure in My Hands(重低音)";
			fff = 1;
		}
		if (a == L"y_b610.opus") {
			a = L"辿り着いた極光の下で";
			fff = 1;
		}
		if (a == L"y_b610_s1.opus") {
			a = L"辿り着いた極光の下で(重低音)";
			fff = 1;
		}
		if (a == L"y_b620.opus") {
			a = L"Nordics Saga -The Endless Bloody Sea-";
			fff = 1;
		}
		if (a == L"y_b620_s1.opus") {
			a = L"Nordics Saga -The Endless Bloody Sea-(重低音)";
			fff = 1;
		}
		if (a == L"y_b700.opus") {
			a = L"Ready to Fire!";
			fff = 1;
		}
		if (a == L"y_b700_s1.opus") {
			a = L"Ready to Fire!(重低音)";
			fff = 1;
		}
		if (a == L"y_b710.opus") {
			a = L"Hello, Those Who Can't Die";
			fff = 1;
		}
		if (a == L"y_b710_s1.opus") {
			a = L"Hello, Those Who Can't Die(重低音)";
			fff = 1;
		}
		if (a == L"y_b720.opus") {
			a = L"Landing Warfare";
			fff = 1;
		}
		if (a == L"y_b720_s1.opus") {
			a = L"Landing Warfare(重低音)";
			fff = 1;
		}
		if (a == L"y_bgm_none.opus") {
			a = L"無音";
			fff = 1;
		}
		if (a == L"y_d100.opus") {
			a = L"光届かぬその奥に";
			fff = 1;
		}
		if (a == L"y_d100_s1.opus") {
			a = L"光届かぬその奥に(重低音)";
			fff = 1;
		}
		if (a == L"y_d200.opus") {
			a = L"Eerie Stillness";
			fff = 1;
		}
		if (a == L"y_d200_s1.opus") {
			a = L"Eerie Stillness(重低音)";
			fff = 1;
		}
		if (a == L"y_d400.opus") {
			a = L"飽くなき渇望";
			fff = 1;
		}
		if (a == L"y_d400_s1.opus") {
			a = L"飽くなき渇望(重低音)";
			fff = 1;
		}
		if (a == L"y_d410.opus") {
			a = L"The Inner Darkness";
			fff = 1;
		}
		if (a == L"y_d410_s1.opus") {
			a = L"The Inner Darkness(重低音)";
			fff = 1;
		}
		if (a == L"y_d500.opus") {
			a = L"Hardhearted Rock Line";
			fff = 1;
		}
		if (a == L"y_d500_s1.opus") {
			a = L"Hardhearted Rock Line(重低音)";
			fff = 1;
		}
		if (a == L"y_d600.opus") {
			a = L"夢の痕跡";
			fff = 1;
		}
		if (a == L"y_d600_s1.opus") {
			a = L"夢の痕跡(重低音)";
			fff = 1;
		}
		if (a == L"y_d710.opus") {
			a = L"甲鉄戦艦ナグルファ";
			fff = 1;
		}
		if (a == L"y_d710_s1.opus") {
			a = L"甲鉄戦艦ナグルファ(重低音)";
			fff = 1;
		}
		if (a == L"y_d800.opus") {
			a = L"LILA -Innocent Wish-";
			fff = 1;
		}
		if (a == L"y_d800_s1.opus") {
			a = L"LILA -Innocent Wish-(重低音)";
			fff = 1;
		}
		if (a == L"y_d900.opus") {
			a = L"エギル海底神殿";
			fff = 1;
		}
		if (a == L"y_d900_s1.opus") {
			a = L"エギル海底神殿(重低音)";
			fff = 1;
		}
		if (a == L"y_d1010.opus") {
			a = L"The Paradise Lost of Norman";
			fff = 1;
		}
		if (a == L"y_d1010_s1.opus") {
			a = L"The Paradise Lost of Norman(重低音)";
			fff = 1;
		}
		if (a == L"y_e001.opus") {
			a = L"Yesterday's Journey, Tomorrow's Dream";
			fff = 1;
		}
		if (a == L"y_e002.opus") {
			a = L"Surging Pressure";
			fff = 1;
		}
		if (a == L"y_e003.opus") {
			a = L"Turn of the Tide";
			fff = 1;
		}
		if (a == L"y_e004.opus") {
			a = L"あの時からずっと…";
			fff = 1;
		}
		if (a == L"y_e005.opus") {
			a = L"Waver as the Wave";
			fff = 1;
		}
		if (a == L"y_e006.opus") {
			a = L"切っても切れない絆";
			fff = 1;
		}
		if (a == L"y_e007.opus") {
			a = L"灰色の深層";
			fff = 1;
		}
		if (a == L"y_e007_s1.opus") {
			a = L"灰色の深層(重低音)";
			fff = 1;
		}
		if (a == L"y_e008.opus") {
			a = L"Premonition of Turmoil";
			fff = 1;
		}
		if (a == L"y_e009.opus") {
			a = L"歪な願望";
			fff = 1;
		}
		if (a == L"y_e010.opus") {
			a = L"The Road so Far, the Future Ahead";
			fff = 1;
		}
		if (a == L"y_e011.opus") {
			a = L"Violent Warriors";
			fff = 1;
		}
		if (a == L"y_e011_s1.opus") {
			a = L"Violent Warriors(重低音)";
			fff = 1;
		}
		if (a == L"y_e012.opus") {
			a = L"手筈通りに";
			fff = 1;
		}
		if (a == L"y_e013.opus") {
			a = L"不明";
			fff = 1;
		}
		if (a == L"y_e014.opus") {
			a = L"ROLLO -Because of Its Purity-";
			fff = 1;
		}
		if (a == L"y_e015.opus") {
			a = L"Deep Unconscious";
			fff = 1;
		}
		if (a == L"y_e015_s1.opus") {
			a = L"Deep Unconscious(重低音)";
			fff = 1;
		}
		if (a == L"y_f100.opus") {
			a = L"TO BE FREE";
			fff = 1;
		}
		if (a == L"y_f100_s1.opus") {
			a = L"TO BE FREE(重低音)";
			fff = 1;
		}
		if (a == L"y_f110.opus") {
			a = L"Brother's Footsteps on the Island";
			fff = 1;
		}
		if (a == L"y_f110_s1.opus") {
			a = L"Brother's Footsteps on the Island(重低音)";
			fff = 1;
		}
		if (a == L"y_f120.opus") {
			a = L"Burn with You";
			fff = 1;
		}
		if (a == L"y_f120_s1.opus") {
			a = L"Burn with You(重低音)";
			fff = 1;
		}
		if (a == L"y_f130.opus") {
			a = L"Destined to Keep Running";
			fff = 1;
		}
		if (a == L"y_f130_s1.opus") {
			a = L"Destined to Keep Running(重低音)";
			fff = 1;
		}
		if (a == L"y_f140.opus") {
			a = L"Ride on Mana!";
			fff = 1;
		}
		if (a == L"y_f140_s1.opus") {
			a = L"Ride on Mana!(重低音)";
			fff = 1;
		}
		if (a == L"y_f150.opus") {
			a = L"Heat Hazard";
			fff = 1;
		}
		if (a == L"y_f150_s1.opus") {
			a = L"Heat Hazard(重低音)";
			fff = 1;
		}
		if (a == L"y_f160.opus") {
			a = L"瞳の中の少年剣士";
			fff = 1;
		}
		if (a == L"y_f160_s1.opus") {
			a = L"瞳の中の少年剣士(重低音)";
			fff = 1;
		}
		if (a == L"y_f200.opus") {
			a = L"錨を揚げろ！";
			fff = 1;
		}
		if (a == L"y_f200_s1.opus") {
			a = L"錨を揚げろ！(重低音)";
			fff = 1;
		}
		if (a == L"y_f210.opus") {
			a = L"悠き海に生きる者";
			fff = 1;
		}
		if (a == L"y_f210_s1.opus") {
			a = L"悠き海に生きる者(重低音)";
			fff = 1;
		}
		if (a == L"y_f220.opus") {
			a = L"コンパスは踊る";
			fff = 1;
		}
		if (a == L"y_f220_s1.opus") {
			a = L"コンパスは踊る(重低音)";
			fff = 1;
		}
		if (a == L"y_f230.opus") {
			a = L"開闢の海";
			fff = 1;
		}
		if (a == L"y_f230_s1.opus") {
			a = L"開闢の海(重低音)";
			fff = 1;
		}
		if (a == L"y_f310.opus") {
			a = L"If I Could Go Back to Those Days";
			fff = 1;
		}
		if (a == L"y_f310_s1.opus") {
			a = L"If I Could Go Back to Those Days(重低音)";
			fff = 1;
		}
		if (a == L"y_gameover.opus") {
			a = L"SO MUCH FOR TODAY (Ys X Ver.)";
			fff = 1;
		}
		if (a == L"y_op.opus") {
			a = L"Facing the Distant Horizon";
			fff = 1;
		}
		if (a == L"y_op_lp.opus") {
			a = L"Facing the Distant Horizon(lp)";
			fff = 1;
		}
		if (a == L"y_t100.opus") {
			a = L"Our Hometown";
			fff = 1;
		}
		if (a == L"y_t100_s1.opus") {
			a = L"Our Hometown(重低音)";
			fff = 1;
		}
		if (a == L"y_t200.opus") {
			a = L"根ざすべき場所";
			fff = 1;
		}
		if (a == L"y_t200_s1.opus") {
			a = L"根ざすべき場所(重低音)";
			fff = 1;
		}
		if (a == L"y_t300.opus") {
			a = L"Sometime Siesta";
			fff = 1;
		}
		if (a == L"y_t300_s1.opus") {
			a = L"Sometime Siesta(重低音)";
			fff = 1;
		}
		if (a == L"y_t301.opus") {
			a = L"Innermost Feelings";
			fff = 1;
		}
		if (a == L"y_t301_s1.opus") {
			a = L"Innermost Feelings(重低音)";
			fff = 1;
		}
		if (a == L"y_t500.opus") {
			a = L"情景に揺蕩う";
			fff = 1;
		}
		if (a == L"y_t500_s1.opus") {
			a = L"情景に揺蕩う(重低音)";
			fff = 1;
		}
		if (a == L"y_t600.opus") {
			a = L"盾の兄弟";
			fff = 1;
		}
		if (a == L"y_t600_s1.opus") {
			a = L"盾の兄弟(重低音)";
			fff = 1;
		}
		if (a == L"y_title.opus") {
			a = L"その優しさは誰のため";
			fff = 1;
		}

		if (fff == 0)
			if (a.Left(2) == "y9") {
				if (a.Mid(4, 4) = "b001") { a = "FEEL FORCE"; }
				if (a.Mid(4, 4) = "b002") { a = "TROUBLEMAKER"; }
				if (a.Mid(4, 4) = "b003") { a = "MONSTRUM SPECTRUM"; }
				if (a.Mid(4, 4) = "b004") { a = "LACRIMA CRISIS"; }
				if (a.Mid(4, 4) = "b005") { a = "WELCOME TO CHAOS"; }
				if (a.Mid(4, 4) = "b006") { a = "JUDGEMENT TIME"; }
				if (a.Mid(4, 4) = "b007") { a = "KNOCK ON NOX"; }
				if (a.Mid(4, 4) = "b008") { a = "ANIMA ERGASTULUM"; }
				if (a.Mid(4, 5) = "b010b") { a = "URBAN TERROR"; }
				if (a.Mid(4, 4) = "b010") { a = "URBAN TERROR(イントロあり)"; }
				if (a.Mid(4, 5) = "b011b") { a = "DREAMING IN THE GRIMWALD"; }
				if (a.Mid(4, 4) = "b011") { a = "DREAMING IN THE GRIMWALD(イントロあり)"; }
				if (a.Mid(4, 4) = "b012") { a = "WILD CARD"; }
				if (a.Mid(4, 5) = "b014b") { a = "FULL MOON CEREMONY"; }
				if (a.Mid(4, 4) = "b014") { a = "FULL MOON CEREMONY(イントロあり)"; }
				if (a.Mid(4, 4) = "d101") { a = "HEART BEAT SHAKER"; }
				if (a.Mid(4, 4) = "d201") { a = "CLOACA MAXIMA"; }
				if (a.Mid(4, 4) = "d301") { a = "RUIN OF DRY MOAT"; }
				if (a.Mid(4, 4) = "d401") { a = "MARIONETTE, MARIONETTE"; }
				if (a.Mid(4, 4) = "d501") { a = "THE CAVE OF GROAN"; }
				if (a.Mid(4, 4) = "d601") { a = "EVAN MACHA"; }
				if (a.Mid(4, 4) = "d701") { a = "A QUARRY RUIN"; }
				if (a.Mid(4, 4) = "d702") { a = "CROSSING A/A"; }
				if (a.Mid(4, 4) = "d801") { a = "CATCH ME IF YOU CAN"; }
				if (a.Mid(4, 4) = "d901") { a = "ALCHEMY LAB"; }
				if (a.Mid(4, 4) = "d911") { a = "STRATEGIC ZONE"; }
				if (a.Mid(4, 5) = "d1001") { a = "FORTRESS UNDERGROUND"; }
				if (a.Mid(4, 5) = "d2001") { a = "DANCE WITH TRAPS"; }
				if (a.Mid(4, 4) = "e001") { a = "APRILIS"; }
				if (a.Mid(4, 4) = "e002") { a = "TAKE IT EASY!"; }
				if (a.Mid(4, 4) = "e003") { a = "PETITE FLEUR"; }
				if (a.Mid(4, 4) = "e004") { a = "EYES ON..."; }
				if (a.Mid(4, 4) = "e005") { a = "FORGOTTEN DAYS"; }
				if (a.Mid(4, 4) = "e006") { a = "PRISON OF BALDUQ -LIVE THE FUTURE-"; }
				if (a.Mid(4, 4) = "e007") { a = "PRISON OF BALDUQ -YEARNING-"; }
				if (a.Mid(4, 4) = "e008") { a = L"IL ETAIT UNE FOIS"; }
				if (a.Mid(4, 4) = "e009") { a = "WHO KNOWS THE TRUTH?"; }
				if (a.Mid(4, 4) = "e010") { a = "DECISION"; }
				if (a.Mid(4, 4) = "e011") { a = "STAGNANT POOL"; }
				if (a.Mid(4, 4) = "e013") { a = "INQUISITION"; }
				if (a.Mid(4, 4) = "e014") { a = "SILLY MEETING"; }
				if (a.Mid(4, 4) = "e016") { a = "MONSTRUM NOX"; }
				if (a.Mid(4, 4) = "e017") { a = "CHALLENGER'S ROAD"; }
				if (a.Mid(4, 4) = "e018") { a = "RED MULETA"; }
				if (a.Mid(4, 4) = "e019") { a = "NAB THE TAIL"; }
				if (a.Mid(4, 4) = "e020") { a = "THUS SPOKE AN ALCHEMIST"; }
				if (a.Mid(4, 4) = "e023") { a = "DENOUEMENT"; }
				if (a.Mid(4, 4) = "e024") { a = "INVITATION TO THE CRIMSON NIGHT"; }
				if (a.Mid(4, 4) = "f101") { a = "NORSE WIND"; }
				if (a.Mid(4, 4) = "f201") { a = "TRANQUIL SILENCE"; }
				if (a.Mid(4, 4) = "f301") { a = "GLESSING WAY!"; }
				if (a.Mid(4, 4) = "f501") { a = "DESERT AFTER TEARS"; }
				if (a.Mid(4, 4) = "muon") { a = "無音"; }
				if (a.Mid(4, 4) = "t101") { a = "PRISONCITY"; }
				if (a.Mid(4, 4) = "t102") { a = "IN PROFILE, ON BELFRY"; }
				if (a.Mid(4, 4) = "t103") { a = "NEW LIFE"; }
				if (a.Mid(4, 4) = "t104") { a = "GRIA RECOLLECTION"; }
				if (a.Mid(4, 4) = "t201") { a = "BAR \"DANDELION\""; }
				if (a.Mid(4, 4) = "t301") { a = "AMBIGUOUS TERRITORY"; }
				if (a.Mid(4, 4) = "t402") { a = "WALTZ FOR GRACE"; }
				if (a.Mid(4, 4) = "t501") { a = "HEAT AND SPLENDOR"; }
				if (a.Mid(4, 4) = "t901") { a = "ONLY THE CORPSE GOES OUT"; }
				if (a.Mid(4, 4) = "t902") { a = "A GOLDEN KEY CAN OPEN ANY DOOR"; }
				if (a.Mid(4, 4) = "tbox") { a = "TREASURE BOX -Ys IX-"; }
			}
			else {
				switch (_ttoi(a.Mid(2, 5))) {
				case 81004:
					a = "罪と罰と偽りと";
					break;
				case 81005:
					a = "昏き鐘の残響";
					break;
				case 81006:
					a = "Right on the Mark";
					break;
				case 81007:
					a = "悪夢ふたたび";
					break;
				case 81008:
					a = "Crossbell Nostalgia";
					break;
				case 81009:
					a = "創まりの円庭";
					break;
				case 81010:
					a = "Mysterious Element";
					break;
				case 81012:
					a = "Stand Up Again and Again!";
					break;
				case 81014:
					a = "Purgatory Scream";
					break;
				case 81015:
					a = "さざめきの途路";
					break;
				case 81016:
					a = "蒼の大地に生きる者";
					break;
				case 81017:
					a = "黎明の鐘";
					break;
				case 81018:
					a = "レメディファンタジア -仲間とともに-";
					break;
				case 81019:
					a = "Slight Suspicion";
					break;
				case 81020:
					a = "Maliciousness in the Mirror";
					break;
				case 81021:
					a = "暗澹たる世界";
					break;
				case 81022:
					a = "ひとときの温もり";
					break;
				case 81023:
					a = "今、創まりのとき";
					break;
				case 81024:
					a = "KERAUNOS -Fear and Hatred-";
					break;
				case 81025:
					a = "亡失われた魂";
					break;
				case 81026:
					a = "穏やかな時間";
					break;
				case 81027:
					break;
				case 81028:
					a = "運命という名の歯車";
					break;
				case 81200:
					a = "Crossing Causal Lines";
					break;
				case 81201:
					a = "Glittering Mirage";
					break;
				case 81202:
					a = "Like a Whirlwind";
					break;
				case 81203:
					a = "Hide and Seek by Myself";
					break;
				case 81315:
					a = "鉱山町マインツ -創Ver.-";
					break;
				case 81316:
					a = "木霊の道 -創Ver.-";
					break;
				case 81317:
					a = "Raindrops with the Wind";
					break;
				case 81319:
					a = "陽溜まりにただいまを";
					break;
				case 81320:
					a = "Wind-Up Yesterday!";
					break;
				case 81321:
					a = "零の邂逅";
					break;
				case 81322:
					a = "影の見えざる手";
					break;
				case 81950:
					break;
				case 81951:
					break;
				case 81952:
					break;
				case 81953:
					break;
				case 81954:
					break;
				case 81955:
					break;
				case 81956:
					break;
				case 81957:
					break;
				case 81958:
					break;
				case 81961:
					break;
				case 81962:
					break;
				case 81963:
					break;
				case 81964:
					break;
				case 81965:
					break;
				case 81966:
					break;
				case 81967:
					break;
				case 81968:
					break;
				case 81969:
					break;
				case 82065:
					a = "鋼鉄牙城";
					break;
				case 82113:
					a = "Zero Break Battle";
					break;
				case 82114:
					a = "Stake Everything Strategy";
					break;
				case 82123:
					break;
				case 82124:
					a = "POM's Paradise";
					break;
				case 82125:
					a = "波間に弾む心";
					break;
				case 82129:
					a = "Reverse Babel";
					break;
				case 82131:
					a = "Aim a Gun at the Bullet";
					break;
				case 82133:
					a = "Section G.F.S. II";
					break;
				case 82135:
					a = "Magical Revolt";
					break;
				case 82136:
					a = "流麗闘冴";
					break;
				case 82137:
					a = "The Road to All-Out War";
					break;
				case 82138:
					a = "LAPIS";
					break;
				case 82140:
					a = "Invisible Hilly Country";
					break;
				case 82141:
					a = "ひとかけらの光明";
					break;
				case 82143:
					a = "反攻の烽火";
					break;
				case 82147:
					a = "Rapid Wind";
					break;
				case 82148:
					a = "NO END NO WORLD -Instrumental Ver.-";
					break;
				case 82150:
					a = "Be Caught Up!";
					break;
				case 82151:
					a = "Breeding Innumerable Arms";
					break;
				case 82152:
					a = "The Destination of FATE";
					break;
				case 82154:
					a = "Twinkle Attack";
					break;
				case 82157:
					a = "Sword of Swords";
					break;
				case 82158:
					a = "今宵は宴と参りましょう";
					break;
				case 82159:
					a = "Flash Your Fighting Spirit";
					break;
				case 82161:
					a = "鈍色に這う";
					break;
				case 82163:
					a = "Pyro Labyrinth";
					break;
				case 82164:
					a = "優しさを未来に託して";
					break;
				case 82166:
					a = "高らかに、誇らしく";
					break;
				case 82170:
					a = "Infinity Rage";
					break;
				case 82171:
					a = "Heavy Violent Match";
					break;
				case 82173:
					a = "Roar of Evil Spirits";
					break;
				case 82174:
					a = "Bad Dream Invasion";
					break;
				case 82175:
					a = "Golden Fever";
					break;
				case 82177:
					a = "The Perfect Steel of ZERO";
					break;
				case 82178:
					a = "Twilight Hermitage";
					break;
				case 82179:
					a = "Something Luxury...?";
					break;
				case 82183:
					a = "Challenger Invigorated";
					break;
				case 82184:
					a = "このあと美味しくいただきました";
					break;
				case 82186:
					a = "Emergency Order";
					break;
				case 82188:
					a = "激烈! 撃滅! ミシュナイダー!!";
					break;
				case 82189:
					a = "Life Goes On";
					break;
				default:
					if (a == L"ed8_inf_ex.opus") {
						a = "夢幻の彼方へ";
					}
				}
				switch (_ttoi(a.Mid(2, 4))) {
				case 8001:
					a = "特科クラス《VII組》";
					break;
				case 8002:
					a = "スタートライン";
					break;
				case 8003:
					a = "不明";
					break;
				case 8004:
					a = "Youthful Victory";
					break;
				case 8006:
					a = "ただひたすらに、前へ";
					break;
				case 8007:
					a = "縁 -つなぐもの-";
					break;
				case 8102:
					a = "翡翠の公都バリアハート";;
					break;
				case 8104:
					a = "黒銀の鋼都ルーレ";
					break;
				case 8150:
					a = "下校途中にパンケーキ";
					break;
				case 8151:
					a = "可能性は無限大";
					break;
				case 8152:
					a = "夜のしじまに";
					break;
				case 8153:
					a = "夕景";
					break;
				case 8154:
					a = "新しい朝";
					break;
				case 8155:
					a = "束の間の里帰り";
					break;
				case 8156:
					a = "白亜の旧都セントアーク";
					break;
				case 8157:
					a = "紡績町パルム";
					break;
				case 8158:
					a = "籠の中のクロスベル";
					break;
				case 8159:
					a = "今、成すべきこと";
					break;
				case 8160:
					a = "歓楽都市ラクウェル";
					break;
				case 8161:
					a = "静かなる駆け引き";
					break;
				case 8162:
					a = "赫奕たるヘイムダル";
					break;
				case 8163:
					a = "紺碧の海都オルディス";
					break;
				case 8164:
					a = "最前線都市";
					break;
				case 8165:
					a = "Base Camp";
					break;
				case 8166:
					a = "精強なる兵たち";
					break;
				case 8168:
					a = "不明";
					break;
				case 8170:
					a = "隠れ里エリン";
					break;
				case 8171:
					a = "潜入調査";
					break;
				case 8172:
					a = "昏冥の中で";
					break;
				case 8173:
					a = "紅き閃影 -光まとう翼-";
					break;
				case 8174:
					a = "聖ウルスラ医科大学 -閃Ver.-";
					break;
				case 8175:
					a = "一抹の不安、一縷の望み";
					break;
				case 8176:
					a = "Lyrical Amber";
					break;
				case 8177:
					a = "水面を渡る風";
					break;
				case 8250:
					a = "流れる雲の彼方に";
					break;
				case 8251:
					a = "静寂の小路";
					break;
				case 8252:
					a = "崖谷の狭間";
					break;
				case 8253:
					a = "Weathering Road";
					break;
				case 8260:
					a = "彼の地へ向かって";
					break;
				case 8261:
					a = "終焉の途へ";
					break;
				case 8262:
					a = "全てを識るもの -閃Ver.-";
					break;
				case 8263:
					a = "たそがれ緑道";
					break;
				case 8311:
					a = "不明";
					break;
				case 8350:
					a = "アインヘル小要塞";
					break;
				case 8351:
					a = "伝承の裏で";
					break;
				case 8352:
					a = "Unplanned Residue";
					break;
				case 8353:
					a = "忘れられし幻夢の狭間 -閃Ver.-";
					break;
				case 8354:
					a = "幽世の気配";
					break;
				case 8355:
					a = "solid as the Rock of JUNO";
					break;
				case 8356:
					a = "地下に巣喰う";
					break;
				case 8359:
					a = "Spiral of Erebos";
					break;
				case 8360:
					a = "鋼の障壁";
					break;
				case 8363:
					a = "Break In";
					break;
				case 8365:
					a = "サングラール迷宮";
					break;
				case 8366:
					a = "静けき森の魔女";
					break;
				case 8367:
					a = "Mystic Core -閃Ver.-";
					break;
				case 8368:
					a = "斉いし舞台";
					break;
				case 8369:
					a = "シンクロニシティ #23";
					break;
				case 8371:
					a = "世界の命運を賭けて";
					break;
				case 8372:
					a = "The End of -SAGA-";
					break;
				case 8429:
					a = "不明";
					break;
				case 8450:
					a = "Brave Steel";
					break;
				case 8451:
					a = "Toughness!!";
					break;
				case 8452:
					a = "剣戟怒涛";
					break;
				case 8453:
					a = "Proud Grudge";
					break;
				case 8454:
					a = "チープ・トラップ";
					break;
				case 8455:
					a = "STEP AHEAD";
					break;
				case 8456:
					a = "劣勢を挽回せよ！";
					break;
				case 8457:
					a = "Abrupt Visitor";
					break;
				case 8458:
					a = "行き着く先 -Opening Size-";
					break;
				case 8460:
					a = "Lift-off!";
					break;
				case 8461:
					a = "Accursed Tycoon";
					break;
				case 8464:
					a = "One-Way to the Netherworld";
					break;
				case 8465:
					a = "不明";
					break;
				case 8466:
					a = "Erosion of Madness";
					break;
				case 8467:
					a = "DOOMSDAY TRANCE";
					break;
				case 8468:
					a = "不明";
					break;
				case 8472:
					a = "Malicious Fiend";
					break;
				case 8473:
					a = "Unlikely Combination";
					break;
				case 8474:
					a = "Robust One";
					break;
				case 8475:
					a = "古の盟約";
					break;
				case 8476:
					a = "七の相克 -EXCELLION KRIEG-";
					break;
				case 8477:
					a = "Burning Throb";
					break;
				case 8478:
					a = "Neck or Nothing";
					break;
				case 8479:
					a = "Majestic Roar";
					break;
				case 8480:
					a = "With Our Own Hands!!";
					break;
				case 8500:
					a = "授業は合同で";
					break;
				case 8501:
					a = "Power or Technique";
					break;
				case 8502:
					a = "Briefing Time";
					break;
				case 8503:
					a = "第II分校の日常";
					break;
				case 8504:
					a = "充実したひととき";
					break;
				case 8505:
					a = "異端の研究者";
					break;
				case 8506:
					a = "君に伝えたいこと";
					break;
				case 8507:
					a = "不明";
					break;
				case 8508:
					a = "不明";
					break;
				case 8509:
					a = "張り詰めた思惑";
					break;
				case 8510:
					a = "混迷の対立";
					break;
				case 8511:
					a = "急転直下";
					break;
				case 8512:
					a = "蠢く陰謀";
					break;
				case 8513:
					a = "託されたもの";
					break;
				case 8514:
					a = "羅刹の薫陶";
					break;
				case 8515:
					a = "ハーメル -遺されたもの-";
					break;
				case 8516:
					a = "Welcome Back! アーベントタイム(ラジオ)";
					break;
				case 8517:
					a = "夏至祭";
					break;
				case 8519:
					a = "夏至祭";
					break;
				case 8520:
					a = "翡翠庭園";
					break;
				case 8521:
					a = "初めての円舞曲";
					break;
				case 8522:
					a = "真打ち登場！";
					break;
				case 8524:
					a = "Tragedy";
					break;
				case 8528:
					a = "僅かな希望の先に";
					break;
				case 8530:
					a = "帰路へ";
					break;
				case 8532:
					a = "Roots of Scar";
					break;
				case 8534:
					a = "想い千里を走り";
					break;
				case 8536:
					a = "光射す空の下で";
					break;
				case 8539:
					a = "不明";
					break;
				case 8541:
					if (b == L"b")
						a = "空を見上げて -Eliot Ver.-";
					else
						a = "空を見上げて -Eliot Ver.-";
					break;
				case 8542:
					a = "不明";
					break;
				case 8543:
					a = "不明";
					break;
				case 8544:
					a = "Little Rain";
					break;
				case 8545:
					a = "暗雲";
					break;
				case 8546:
					a = "鐘、鳴り響く時";
					break;
				case 8547:
					a = "巨イナル黄昏";
					break;
				case 8548:
					a = "あの日の約束";
					break;
				case 8551:
					a = "不明";
					break;
				case 8553:
					a = "Sensitive Talk";
					break;
				case 8554:
					a = "哀花";
					break;
				case 8555:
					a = "Feel at Home";
					break;
				case 8556:
					a = "幾千万の夜を越えて";
					break;
				case 8557:
					a = "不明";
					break;
				case 8558:
					a = "不明";
					break;
				case 8559:
					a = "優しき微睡み";
					break;
				case 8560:
					a = "最悪の最善手";
					break;
				case 8562:
					a = "黒の真実";
					break;
				case 8563:
					a = "いつでもそばに";
					break;
				case 8564:
					a = "その温もりは小さいけれど。";
					break;
				case 8566:
					a = "それでも前へ";
					break;
				case 8570:
					a = "想いひとつに";
					break;
				case 8571:
					a = "千年要塞";
					break;
				case 8572:
					a = "不明";
					break;
				case 8573:
					a = "せめてこの夜に誓って";
					break;
				case 8574:
					a = "Constraint";
					break;
				case 8575:
					a = "過ぎ去りし日々";
					break;
				case 8576:
					a = "不明";
					break;
				case 8577:
					a = "それぞれの覚悟";
					break;
				case 8578:
					a = "無明の闇の中で";
					break;
				case 8579:
					a = "変わる世界 -闇の底から-";
					break;
				case 8600:
					a = "不明";
					break;
				case 8601:
					a = "ゲートイン";
					break;
				case 8602:
					a = "不明(空の軌跡)";
					break;
				case 8603:
					a = "女神はいつも見ています";
					break;
				case 8604:
					a = "不明(空の軌跡)";
					break;
				case 8605:
					a = "不明";
					break;
				case 8606:
					a = "不明";
					break;
				case 8608:
					a = "不明";
					break;
				case 8610:
					a = "不明";
					break;
				case 8611:
					a = "不明";
					break;
				case 8612:
					a = "不明";
					break;
				case 8613:
					a = "不明";
					break;
				case 8614:
					a = "不明";
					break;
				case 8616:
					a = "不明";
					break;
				case 8617:
					a = "不明";
					break;
				case 8618:
					a = "不明";
					break;
				case 8619:
					a = "不明";
					break;
				case 8620:
					a = "不明";
					break;
				case 8621:
					a = "不明";
					break;
				case 8702:
					a = "Master's Vertex";
					break;
				case 8706:
					a = "Endure Grief";
					break;
				case 8707:
					a = "Intuition and Insight";
					break;
				case 8708:
					a = "Bold Assailants";
					break;
				case 8709:
					a = "Seductive Shudder";
					break;
				case 8711:
					a = "Blue Stardust";
					break;
				case 8713:
					a = "Pleasure Smile";
					break;
				case 8714:
					a = "巨竜目覚める";
					break;
				case 8715:
					a = "未来へ。";
					break;
				case 8716:
					a = "明日への軌跡 -Instrumental Ver.-";
					break;
				case 8717:
					a = "Deep Carnival";
					break;
				case 8718:
					a = "不明";
					break;
				case 8719:
					a = "Chain Chain Chain!";
					break;
				case 8720:
					a = "明日への軌跡";
					break;
				case 8721:
					a = "愛の詩(歌)";
					break;
				case 8722:
					a = "Celestial Coalescence";
					break;
				case 8800:
					a = "Vantage Masters";
					break;
				case 8801:
					a = "Concept H.M.I.";
					break;
				case 8802:
					a = "風よりも駿く";
					break;
				case 8803:
					a = "Brilliant Escape";
					break;
				case 8810:
					a = "不明";
					break;
				case 8811:
					a = "不明";
					break;
				case 8812:
					a = "不明";
					break;
				case 8910:
					a = "不明";
					break;
				case 8911:
					a = "不明";
					break;
				case 8912:
					a = "不明";
					break;
				case 8913:
					a = "不明";
					break;
				case 8916:
					a = "不明";
					break;
				case 8917:
					a = "不明";
					break;
				case 8918:
					a = "不明";
					break;
				case 8919:
					a = "不明";
					break;
				case 8920:
					a = "不明";
					break;
				case 8921:
					a = "不明";
					break;
				}
			}

		if (a.Left(3) == L"ed7") {
			int b = _ttoi(a.Mid(3, 3));
			CString fil = filen.Left(filen.ReverseFind(L'\\')) + L"\\..\\..\\data\\bgm\\info.yaml";
			FILE* fp;
			errno_t ferr;
			ferr = _tfopen_s(&fp, fil, _T("r, ccs=UTF-8"));
			if (ferr == 0) {
				CStdioFile fzero(fp);
				fzero.SeekToBegin();
				CString stf, stl, stn;
				BOOL ck = FALSE;
				for (;;) {
					if (fzero.ReadString(stf) == FALSE) break;
					stl.Format(L"'%d'", b);
					if (stf.Find(stl) != -1) {
						ck = TRUE;
					}
					if (stf.Find(L"jp:") != -1 && ck == TRUE) {
						int k = stf.Find(L"jp:") + 4;
						stn = stf.Mid(k);
						break;
					}
				}
				if (stn != L"") {
					a = stn;
				}
				fzero.Close();
				fclose(fp);
			}
		}

		stitle = a;
		OggOpusFile* m_pOpusFile;
		int ret;
		OpusFileCallbacks cb = { NULL,NULL,NULL,NULL };
		CFile fi;
		fi.Open(filen, CFile::modeRead);
		char by[255], by2[255];
		fi.Read(by, 255);
		fi.Close();
		int l1 = 0, l2 = 0;
		CString g = L"";
		for (int l = 0; l < 240; l++) {
			if (by[l] == 'l' && by[l + 1] == 'o' && by[l + 2] == 'o' && by[l + 3] == 'p' && by[l + 4] == 's' && by[l + 5] == '=') {
				strcpy(by2, by + l + 6);
				int flg = 0;
				for (int i = 0;; i++) {
					if (by2[i] == 0) {
						break;
					}
					if (by2[i] == '-') {
						flg = 1;
						continue;
					}
					if (flg == 0) {
						l1 *= 10;
						l1 += by2[i] - '0';
					}
					else {
						l2 *= 10;
						l2 += by2[i] - '0';
					}
				}
			}
		}
		for (int l = 0; l < 240; l++) {
			if (by[l] == 'u' && by[l + 1] == 's' && by[l + 2] == 'H' && by[l + 3] == 'e' && by[l + 4] == 'a' && by[l + 5] == 'd') {
				struct abc
				{
					union {
						int a;
						char b[4];
					};
				};

				abc abc_;
				abc_.b[0] = abc_.b[1] = abc_.b[2] = abc_.b[3] = 0;
				abc_.b[0] = by[l + 10];
				abc_.b[1] = by[l + 11];
				wavbit = abc_.a;

			}
		}
		for (int l = 0; l < 240; l++) {
			if (by[l] == 'l' && by[l + 1] == 'o' && by[l + 2] == 'o' && by[l + 3] == 'p' && by[l + 4] == 's' && by[l + 5] == 't') {
				strcpy(by2, by + l + 10);
				int flg = 0;
				for (int i = 0;; i++) {
					if (by2[i] < 0x30) {
						break;
					}
					l1 *= 10;
					l1 += by2[i] - '0';
				}
			}
		}
		for (int l = 0; l < 240; l++) {
			if (by[l] == 'l' && by[l + 1] == 'o' && by[l + 2] == 'o' && by[l + 3] == 'p' && by[l + 4] == 'e' && by[l + 5] == 'n') {
				strcpy(by2, by + l + 8);
				int flg = 0;
				for (int i = 0;; i++) {
					if (by2[i] < 0x30) {
						break;
					}
					l2 *= 10;
					l2 += by2[i] - '0';
				}
			}
		}
		//		m_pOpusFile = op_open_callbacks(op_fopen(&cb, CStringA(filen), "rb"), &cb, NULL, 0, &ret);
		void* bbbb = filen.GetBuffer();
		m_pOpusFile = op_open_file((WCHAR*)bbbb, &err);
		filen.ReleaseBuffer();

		ogg_int64_t totalSamples = op_pcm_total(m_pOpusFile, -1);
		op_raw_seek(m_pOpusFile, 1);
		if (adbuf2) {
			free(adbuf2); adbuf2 = NULL;
		}
		adbuf2 = (char*)calloc((size_t)totalSamples * 6 * 2, 1);

		loop1 = l1;
		loop2 = l2 - l1;
		a = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		if (a.Left(3) == L"ed7") {
			int b = _ttoi(a.Mid(3, 3));
			CFile fzero;
			CString fil = filen.Left(filen.ReverseFind(L'\\')) + L"\\..\\..\\data\\text\\t_bgm._dt";
			if (fzero.Open(fil, CFile::modeRead | CFile::shareDenyNone, NULL)) {
				fzero.SeekToBegin();
				typedef struct
				{
					int start;
					int end;
					short dm;
					short dm2;
					short track;
					char loop;
					char dm3;
				} zero;
				zero zerobuf;
				for (;;) {
					ZeroMemory(&zerobuf, 16);
					UINT ret1 = fzero.Read(&zerobuf, 16);
					if (ret1 != 16) break;
					if (b == zerobuf.track) break;
				}
				if (zerobuf.track != 0) {
					loop1 = zerobuf.start * 1.08843537414966; //44.1kHz -> 48kHz
					loop2 = zerobuf.end * 1.08843537414966; //44.1kHz -> 48kHz
				}
			}
		}

		int i = 0;
		lenl = 0;
		data_size = oggsize = totalSamples * 4;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		og->m_time.SetSelection(loop1, loop2);
		wavwait = 1;
		if (wav)free(wav);
		wav_start();
		int iii = 0;
		for (;; iii++) {
			BYTE budf[5760 * 4];
			int ret = op_read_stereo(m_pOpusFile, (opus_int16*)budf, 5760);
			if (ret <= 0) {//デコード終了
				break;
			}
			memcpy(adbuf2 + i * 4, budf, ret * 4);
			if (thend1 == TRUE) { thend = 1; op_free(m_pOpusFile);  return; }
			if (i >= dl)
				wavwait = 0;
			i += ret;
		}
		op_free(m_pOpusFile);

	}
	else if (mode == 10) {
		lenl = 0;
		CFile adpcmf;
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 0x2c);
		int si = (int)bbuf[4] + (int)bbuf[5] * 256 + (int)bbuf[6] * 65536 + (int)bbuf[7] * 256 * 65536;
		adbuf2 = (char*)calloc((size_t)adpcmf.GetLength() * 4 * 2, 1);
		data_size = oggsize = (int)adpcmf.GetLength() * 4 - (int)(adpcmf.GetLength() * 14 * 4) / 2048 - (int)(adpcmf.GetLength() * 8 * 4) / 0x5000 - 0x2c;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		if (readadpcm(adpcmf, adbuf2, (int)adpcmf.GetLength())) { thend = 1; adpcmf.Close(); return; }
		adpcmf.Close();
	}
	else if (mode == 15) {
		lenl = 0;
		CFile adpcmf;
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 16);
		int si, jk, jk2;
		jk = (int)(BYTE)bbuf[12] + (int)(BYTE)bbuf[13] * 256 + (int)(BYTE)bbuf[14] * 65536 + (int)(BYTE)bbuf[15] * 256 * 65536;
		adpcmf.Seek(jk, CFile::begin);
		adpcmf.Read(bbuf, 0x7c);
		for (jk2 = 0;; jk2++) {
			if (bbuf[jk2] == 'd' && bbuf[jk2 + 1] == 'a' && bbuf[jk2 + 2] == 't' && bbuf[jk2 + 3] == 'a') { jk2 += 4; break; }
		}
		si = (int)(BYTE)bbuf[jk2] + (int)(BYTE)bbuf[jk2 + 1] * 256 + (int)(BYTE)bbuf[jk2 + 2] * 65536 + (int)(BYTE)bbuf[jk2 + 3] * 256 * 65536;
		si = si / 4 + jk / 4;
		data_size = oggsize = si * 4 - (si * 14 * 4) / 2048 - (si * 8 * 4) / 0x5000 - jk;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		adpcmf.Seek(jk + jk2 + 4, CFile::begin);
		adbuf2 = (char*)calloc(si * 6 * 2, 1);
		if (readadpcmgurumin(adpcmf, adbuf2, (int)(adpcmf.GetLength() - jk))) { thend = 1; adpcmf.Close(); return; }
		adpcmf.Close();
	}
	else if (mode == 16) {
		CWaitCursor aaaa;
		CFile adpcmf;
		char aaa[9];
		struct a {
			char aa[8];
			int p1;
			int p2;
		};
		a aa;
		int st, cnt;
		adpcmf.Open(_T("bgm.arc"), CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 5);
		if (bbuf[4] == 1) {//wav else adpcm
			CString sss, sss1;
			adpcmf.SeekToBegin();
			adpcmf.Read(bbuf, 0x14);
			for (;;) {
				adpcmf.Read(&aa, sizeof(a));	memcpy(aaa, aa.aa, 8); aaa[8] = 0; sss = aaa;	if (sss == filen.Left(8)) break;
			}
			adpcmf.SeekToBegin();
			adpcmf.Seek(aa.p2, CFile::begin);
			__int64 aa = adpcmf.GetPosition();
			adpcmf.Read(bbuf, 0x7f);
			for (st = 0;; st++)
				if (bbuf[st] == 'd' && bbuf[st + 1] == 'a' && bbuf[st + 2] == 't' && bbuf[st + 3] == 'a') { st += 4; break; }
			cnt = (int)(BYTE)bbuf[st] + (int)(BYTE)bbuf[st + 1] * 256 + (int)(BYTE)bbuf[st + 2] * 65536 + (int)(BYTE)bbuf[st + 3] * 256 * 65536;
			data_size = oggsize = cnt;
			adpcmf.Seek(aa + st + 4, CFile::begin);
			og->m_time.SetRange(0, (data_size) / 4, TRUE);
			lenl = 0;
			adbuf2 = (char*)calloc(cnt * 2 * 2, 1);
			//			memcpy(adbuf2,adbuf+st+4,cnt);
			adpcmf.Read(adbuf2, dl * 2);
			dwDataLen += dl;
			cnt -= dwDataLen * 2;
			wavwait = 1;
			for (; cnt > 0;) {
				adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
				dwDataLen += dl; cnt -= dl;
				if (thend1 == TRUE) { thend = 1;  return; }
			}
			adpcmf.Close();
		}
		else {
			CString sss, sss1;
			adpcmf.SeekToBegin();
			adpcmf.Read(bbuf, 0x20);
			for (;;) {
				adpcmf.Read(&aa, sizeof(a));	memcpy(aaa, aa.aa, 8); aaa[8] = 0; sss = aaa;	if (sss == filen.Left(8)) break;
			}
			adpcmf.SeekToBegin();
			adpcmf.Seek(aa.p2, CFile::begin);
			data_size = oggsize = aa.p1 * 4 - (aa.p1 * 14 * 4) / 2048 - (aa.p1 * 8 * 4) / 0x5000 - 0x2c;
			og->m_time.SetRange(0, (data_size) / 4, TRUE);
			lenl = 0;
			adbuf2 = (char*)calloc(aa.p1 * 6 * 2, 1);
			if (readadpcmzwei(adpcmf, adbuf2, aa.p1)) { thend = 1; adpcmf.Close();  return; }
			adpcmf.Close();
		}
	}
	else if (mode == 19) {
		CWaitCursor aaaa;
		CFile adpcmf;
		if (adpcmf.Open(filen.Left(filen.ReverseFind('.')) + _T(".pos"), CFile::modeRead | CFile::typeBinary, NULL) == 0) {
			loop1 = loop2 = 0;
		}
		else {
			adpcmf.Read(&loop1, 4);
			adpcmf.Read(&loop2, 4); loop2 = loop2 - loop1;
			adpcmf.Close();
		}
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 0x80);
		wavbit = (UINT)(int)bbuf[0x18] + (int)(BYTE)bbuf[0x19] * 256;
		if (wav)free(wav);
		wav_start();
		int si, jk;
		for (jk = 0; jk < 0x7c; jk++) {
			if (bbuf[jk] == 'd' && bbuf[jk + 1] == 'a' && bbuf[jk + 2] == 't' && bbuf[jk + 3] == 'a') { jk += 4; break; }
		}
		si = (int)(BYTE)bbuf[jk] + (int)(BYTE)bbuf[jk + 1] * 256 + (int)(BYTE)bbuf[jk + 2] * 65536 + (int)(BYTE)bbuf[jk + 3] * 256 * 65536;
		adpcmf.SeekToBegin();
		adpcmf.Seek(jk + 4, CFile::begin);
		adbuf2 = (char*)calloc(si * 2 * 2, 1);
		data_size = oggsize = si;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		lenl = 0;
		dwDataLen += dl;
		adpcmf.Read(adbuf2, dwDataLen);
		wavwait = 1;
		si -= dwDataLen;
		for (; si > 0;) {
			adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
			dwDataLen += dl; si -= dl;
			if (thend1 == TRUE) { thend = 1; adpcmf.Close();  return; }
		}
		adpcmf.Close();
	}
	else if (mode == 18 || mode == 20) {
		CWaitCursor aaaa;
		BOOL ff = FALSE;
		CFile adpcmf;
		if (adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL) == 0) {
			if (filen.Left(8) == "ED3119DA") { _chdir(".."); filen = "ED3_DT09.DAT"; ff = TRUE; }
			if (filen.Left(8) == "ED3603DA") { _chdir(".."); filen = "ED3_DT10.DAT"; ff = TRUE; }
			adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		}

		adpcmf.Seek(-32, CFile::end);
		adpcmf.Read(&loop1, 4);
		adpcmf.Read(&loop2, 4); loop2 = loop2 - loop1;
		BYTE a[2], b[5]; b[4] = 0; CString tep;
		adpcmf.Seek(-68, CFile::end);
		adpcmf.Read(a, 2);
		if (!(a[0] == 0x93 && a[1] == 0x58)) loop1 = loop2 = 0; if (loop2 == 0) loop1 = 0;
		adpcmf.Seek(-16, CFile::end);
		adpcmf.Read(b, 4); tep = b;
		adpcmf.SeekToBegin();
		adpcmf.Read(bbuf, 0x80);
		wavbit = (UINT)(int)bbuf[0x18] + (int)(BYTE)bbuf[0x19] * 256;
		if (wav)free(wav);
		wav_start();
		int si, jk;
		if (ff == FALSE)
			for (jk = 0; jk < 0x7c; jk++) {
				if (bbuf[jk] == 'd' && bbuf[jk + 1] == 'a' && bbuf[jk + 2] == 't' && bbuf[jk + 3] == 'a') { jk += 4; break; }
			}
		else
			jk = 0x28;
		si = (int)(BYTE)bbuf[jk] + (int)(BYTE)bbuf[jk + 1] * 256 + (int)(BYTE)bbuf[jk + 2] * 65536 + (int)(BYTE)bbuf[jk + 3] * 256 * 65536;
		if (filen.Left(8) == "ED5WV001")loop2 = si / 4;
		if (loop1 < 0 || loop2 < 0) { loop1 = 0; loop2 = si / 4; }
		if (filen.Left(8) == "ED3940DA" && fnn.Left(2) == "白") {
			si = 14332500 * 2 * 2;
			if (wavbit == 22050) { si /= 2; }
		}
		if (filen.Left(8) == "ED3940DA" && fnn.Left(2) == "も") {
			jk = 14376600 * 2 * 2;
			si = 19668600 * 2 * 2;
			if (wavbit == 22050) { jk /= 2; si /= 2; }
		}
		adpcmf.SeekToBegin();
		adpcmf.Seek(jk + 4, CFile::begin);
		adbuf2 = (char*)calloc((si - jk) * 2 * 2, 1);
		data_size = oggsize = si - jk;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		lenl = 0;
		dwDataLen += dl;
		adpcmf.Read(adbuf2, dwDataLen);
		wavwait = 1;
		si -= dwDataLen;
		for (; (si - jk) > 0;) {
			adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
			dwDataLen += dl; si -= dl;
			if (thend1 == TRUE) { thend = 1; adpcmf.Close(); return; }
		}
		adpcmf.Close();
	}
	else if (mode == 17 || mode == -12 || (mode == -14 && filen.Right(3) == "wav")) {
		CWaitCursor aaaa;
		CFile adpcmf;
		if (filen == "49music.wav" || filen == "50music.wav" || filen == "51music.wav") _chdir("..\\Cmusic");
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 0x80);
		int si, jk;
		wavbit = (UINT)(int)bbuf[0x18] + (int)(BYTE)bbuf[0x19] * 256;
		if (wav)free(wav);
		wav_start();
		for (jk = 0; jk < 0x7c; jk++) {
			if (bbuf[jk] == 'd' && bbuf[jk + 1] == 'a' && bbuf[jk + 2] == 't' && bbuf[jk + 3] == 'a') { jk += 4; break; }
		}
		si = (int)(BYTE)bbuf[jk] + (int)(BYTE)bbuf[jk + 1] * 256 + (int)(BYTE)bbuf[jk + 2] * 65536 + (int)(BYTE)bbuf[jk + 3] * 256 * 65536;
		adpcmf.SeekToBegin();
		adpcmf.Read(bbuf, jk + 4);
		adbuf2 = (char*)calloc(si * 2 * 2, 1);
		data_size = oggsize = si;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		lenl = 0;
		dwDataLen += dl;
		adpcmf.Read(adbuf2, dwDataLen);
		loop1 = 0;
		if (filen == "VT01DA.wav" || filen == "VT02DA.wav" || filen == "VT21DA.wav" ||
			filen == "VT22DA.wav" || filen == "VT31DA.wav" || filen == "VT35DA.wav" ||
			filen == "VT39DA.wav" || filen == "VT40DA.wav" || filen == "VT41DA.wav" ||
			filen == "VT43DA.wav" || filen == "VT44DA.wav" || filen == "VT45DA.wav" ||
			filen == "VT46DA.wav" || filen == "VT47DA.wav" || filen == "VT48DA.wav" ||
			filen == "VT39DA.wav" || filen == "42music.wav") {
			loop2 = 0;
		}
		else {
			loop2 = oggsize / 4;
		}
		wavwait = 1;
		si -= dwDataLen;
		for (; si > 0;) {
			adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
			dwDataLen += dl; si -= dl;
			if (thend1 == TRUE) { thend = 1; adpcmf.Close();  return; }
		}
		adpcmf.Close();
	}
	else if (mode == 11 || mode == 12 || mode == 13) {
		CWaitCursor aaaa;
		CFile adpcmf;
		adpcmf.Open(filen, CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 0x80);
		int si, jk;
		for (jk = 0; jk < 0x7c; jk++) {
			if (bbuf[jk] == 'd' && bbuf[jk + 1] == 'a' && bbuf[jk + 2] == 't' && bbuf[jk + 3] == 'a') { jk += 4; break; }
		}
		si = (int)(BYTE)bbuf[jk] + (int)(BYTE)bbuf[jk + 1] * 256 + (int)(BYTE)bbuf[jk + 2] * 65536 + (int)(BYTE)bbuf[jk + 3] * 256 * 65536;
		adpcmf.SeekToBegin();
		adpcmf.Read(bbuf, jk + 4);
		adbuf2 = (char*)calloc(si * 2 * 2 + 44100 * 30,1);
		data_size = oggsize = si;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		lenl = 0;
		dwDataLen += dl;
		adpcmf.Read(adbuf2, dwDataLen);
		wavwait = 1;
		si -= dwDataLen;
		for (; si > 0;) {
			adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
			dwDataLen += dl; si -= dl;
			if (thend1 == TRUE) { thend = 1; adpcmf.Close();  return; }
		}
		adpcmf.Close();
	}
	else if (mode == 14) {
		CWaitCursor aaaa;
		CFile adpcmf;
		struct a {
			char aa[8];
			int p1;
			int p2;
		};
		a aa;
		int st, cnt;
		adpcmf.Open(_T("wav.dat"), CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.Read(bbuf, 5);
		if (bbuf[4] == 2) {//wav else adpcm
			adpcmf.SeekToBegin();
			adpcmf.Read(bbuf, 0x20);
			CString sss, sss1;
			for (;;) {
				adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == "bgm") break;
			}
			adpcmf.SeekToBegin();
			adpcmf.Seek(aa.p2, CFile::begin);
			adbuf = (char*)malloc(aa.p1 + 1);
			adpcmf.Read(adbuf, aa.p1);
			adbuf[aa.p1] = 0;
			sss = adbuf;
			loop1 = loop2 = 0;
			if (filen.Mid(4, 1) == "(")
				cnt = sss.Find(filen.Left(4));
			else
				cnt = sss.Find(filen.Left(5));
			st = sss.Find(',', cnt);//bgm00.wav,st,end;
			cnt = sss.Find(',', st + 1);		sss1 = sss.Mid(st + 1, (cnt - 1) - (st));		loop1 = _tstoi(sss1);
			st = sss.Find(';', cnt + 1);		sss1 = sss.Mid(cnt + 1, (st - 1) - (cnt));		loop2 = _tstoi(sss1) - loop1;
			if (loop1 == 1)loop1 = loop2 = 0;
			free(adbuf);
			adbuf = NULL;
			if (filen.Left(5) == "bgm75" || filen.Left(5) == "bgm76") {
				filen = filen.Left(5) + _T("(data.dat)");
				adpcmf.Close();
				adpcmf.Open(_T("Plugins\\data.dat"), CFile::modeRead | CFile::typeBinary, NULL);
				adpcmf.SeekToBegin();
				adpcmf.Read(bbuf, 0x44);
				for (;;) {
					adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == filen.Left(5)) break; if (sss.GetLength() == 4 && sss == filen.Left(4)) break;
				}
				adpcmf.SeekToBegin();
				adpcmf.Seek(aa.p2, CFile::begin);
				adbuf2 = (char*)calloc(aa.p1 * 6 * 2, 1);
				data_size = oggsize = aa.p1 * 4 - (aa.p1 * 14 * 4) / 2048 - (aa.p1 * 8 * 4) / 0x5000 - 0x2c;
				og->m_time.SetRange(0, (data_size) / 4, TRUE);
				lenl = 0;
				if (readadpcmzwei(adpcmf, adbuf2, aa.p1)) { thend = 1; adpcmf.Close(); return; }
				adpcmf.Close();
			}
			else {
				adpcmf.SeekToBegin();
				adpcmf.Read(bbuf, 0x20);
				for (;;) {
					adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == filen.Left(5)) break; if (sss.GetLength() == 4 && sss == filen.Left(4)) break;
				}
				adpcmf.SeekToBegin();
				adpcmf.Seek(aa.p2, CFile::begin);
				adpcmf.Read(bbuf, 0x81);
				for (st = 0;; st++)
					if (bbuf[st] == 'd' && bbuf[st + 1] == 'a' && bbuf[st + 2] == 't' && bbuf[st + 3] == 'a') { st += 4; break; }
				cnt = (int)(BYTE)bbuf[st] + (int)(BYTE)bbuf[st + 1] * 256 + (int)(BYTE)bbuf[st + 2] * 65536 + (int)(BYTE)bbuf[st + 3] * 256 * 65536;
				adbuf2 = (char*)calloc(cnt * 2 * 2, 1);
				adpcmf.Seek(aa.p2 + st + 4, CFile::begin);
				dwDataLen += dl;
				adpcmf.Read(adbuf2, dwDataLen);
				data_size = oggsize = cnt;
				og->m_time.SetRange(0, (data_size) / 4, TRUE);
				lenl = 0;
				wavwait = 1;
				cnt -= dwDataLen;
				for (; cnt > 0;) {
					adpcmf.Read(adbuf2 + (int)dwDataLen, dl);
					dwDataLen += dl; cnt -= dl;
					if (thend1 == TRUE) { thend = 1; adpcmf.Close();  return; }
				}
				adpcmf.Close();
			}
		}
		else {//adpcm
			adpcmf.SeekToBegin();
			adpcmf.Read(bbuf, 0x2c);
			CString sss, sss1;
			for (;;) {
				adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == "bgm") break;
			}
			adpcmf.SeekToBegin();
			adpcmf.Seek(aa.p2, CFile::begin);
			adbuf = (char*)malloc(aa.p1 + 1);
			adpcmf.Read(adbuf, aa.p1);
			adbuf[aa.p1] = 0;
			sss = adbuf;
			loop1 = loop2 = 0;
			if (filen.Mid(4, 1) == "(")
				cnt = sss.Find(filen.Left(4));
			else
				cnt = sss.Find(filen.Left(5));
			st = sss.Find(',', cnt);//bgm00.wav,st,end;
			cnt = sss.Find(',', st + 1);		sss1 = sss.Mid(st + 1, (cnt - 1) - (st));		loop1 = _tstoi(sss1);
			st = sss.Find(';', cnt + 1);		sss1 = sss.Mid(cnt + 1, (st - 1) - (cnt));		loop2 = _tstoi(sss1) - loop1;
			if (loop1 == 1)loop1 = loop2 = 0;
			delete[] adbuf;
			adbuf = NULL;
			if (filen.Left(5) == "bgm75" || filen.Left(5) == "bgm76") {
				filen = filen.Left(5) + _T("(data.dat)");
				adpcmf.Close();
				adpcmf.Open(_T("Plugins\\data.dat"), CFile::modeRead | CFile::typeBinary, NULL);
				adpcmf.SeekToBegin();
				adpcmf.Read(bbuf, 0x44);
				for (;;) {
					adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == filen.Left(5)) break; if (sss.GetLength() == 4 && sss == filen.Left(4)) break;
				}
				adpcmf.SeekToBegin();
				adpcmf.Seek(aa.p2, CFile::begin);
				adbuf2 = (char*)calloc(aa.p1 * 6 * 2, 1);
				data_size = oggsize = aa.p1 * 4 - (aa.p1 * 14 * 4) / 2048 - (aa.p1 * 8 * 4) / 0x5000 - 0x2c;
				og->m_time.SetRange(0, (data_size) / 4, TRUE);
				lenl = 0;
				if (readadpcmzwei(adpcmf, adbuf2, aa.p1)) { thend = 1; adpcmf.Close(); return; }
				adpcmf.Close();
			}
			else {
				adpcmf.SeekToBegin();
				adpcmf.Read(bbuf, 0x2c);
				for (;;) {
					adpcmf.Read(&aa, sizeof(a));	sss = aa.aa;	if (sss == filen.Left(5)) break; if (sss.GetLength() == 4 && sss == filen.Left(4)) break;
				}
				adpcmf.SeekToBegin();
				adpcmf.Seek(aa.p2, CFile::begin);
				adbuf2 = (char*)calloc(aa.p1 * 6, 1);
				data_size = oggsize = aa.p1 * 4 - (aa.p1 * 14 * 4) / 2048 - (aa.p1 * 8 * 4) / 0x5000 - 0x2c;
				og->m_time.SetRange(0, (data_size) / 4, TRUE);
				lenl = 0;
				if (readadpcmzwei(adpcmf, adbuf2, aa.p1)) { thend = 1; adpcmf.Close(); return; }
				adpcmf.Close();
			}
		}
		/*	}else if(mode==-100){//なし
		si1.dwSamplesPerSec=44100;
		si1.dwChannels=2;
		si1.dwBitsPerSample=16;
		CString s,ss;
		s=filen.Left(filen.ReverseFind('\\')); ss=filen.Right(filen.GetLength()-filen.ReverseFind('\\')-1);
		_tchdir(s);
		CMp3Info *si2; si2=new CMp3Info;
		si2->Load(ss,TRUE);
		kbps=si2->GetBps();
		Vbr=si2->IsVbr();
		delete si2;
		CId3tagv1 ta1;
		CId3tagv2 ta2;
		int b=ta2.Load(ss);
		tagname=ta2.GetArtist();if(b==-1){ta1.Load(ss); tagname=ta1.GetArtist();}
		tagfile=ta2.GetTitle();if(b==-1) tagfile=ta1.GetTitle();
		tagalbum=ta2.GetAlbum();if(b==-1) tagalbum=ta1.GetAlbum();
		if(Open(ss,&si1)==true){
		loop1=0;stitle="";
		loop2=(int)(((float)si1.dwLength)/1000.0f*44100.0f);
		wavch=si1.dwChannels;
		wavbit=si1.dwSamplesPerSec;
		loop2=(int)(((float)loop2)/(44100.0f/((float)((wavch==2)?wavbit:(wavbit/2)))));
		data_size=oggsize=loop2*4;
		loop3=loop2;loop2=0;
		adbuf2=(char*)malloc(data_size+44100*10);
		if(adbuf2==0){wavwait=1;thend=1; fnn="メモリの確保に失敗しました。";return;}
		og->m_time.SetRange(0,(data_size)/4,TRUE);
		lenl= 0;
		if(wav)free(wav);
		wav_start();
		Render();
		}else{wavwait=1;thend=1; fnn="ファイルが開けませんでした。";return;}
		*/
	}
	else if (mode == -11 || (mode == -14 && filen.Right(3) == "mp3") || mode == -15) {
		if (mode == -14 && (filen == "49music.mp3" || filen == "50music.mp3" || filen == "51music.mp3")) _chdir("..\\Cmusic");
		int san2 = 0;
		if (filen == "041music.mp3" && fnn.Find(_T("日本語")) > 0) san2 = 1;
		if (filen == "041music.mp3" && fnn.Find(_T("中国")) > 0) san2 = 2;
		SOUNDINFO si;
		si.dwSamplesPerSec = 44100;
		si.dwChannels = 2;
		si.dwBitsPerSample = 16;
		CString s, ss;
		s = filen.Left(filen.ReverseFind('\\')); ss = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		_tchdir(s);
		Open(ss, &si);
		loop1 = 0; stitle = "";
		loop2 = (int)(((float)si.dwLength) / 1000.0f * 44100.0f);
		wavbit = si.dwSamplesPerSec;
		loop2 = loop2 / (44100 / wavbit);
		data_size = oggsize = loop2 * 4;
		adbuf2 = (char*)calloc(data_size * 2 + 44100 * 30, 1);
		if (san2 == 1) loop2 = 225 * 44100;
		if (san2 == 2) loop2 = 247 * 44100;
		loop3 = loop2;
		if (san2)data_size = oggsize = loop2 * 4 + 44100 * 7;
		if (mode == -14 && filen == "42music.mp3")	loop2 = 0;
		if (adbuf2 == 0) { wavwait = 1; thend = 1; fnn = "メモリの確保に失敗しました。"; return; }
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		lenl = 0;
		if (wav)free(wav);
		wav_start();
		Render((san2 == 2) ? data_size - 44100 * 21 * 4 : 0);
	}
	else if (mode == -13) {
		lenl = 0;
		CFile adpcmf;
		adpcmf.Open(_T("music.pak"), CFile::modeRead | CFile::typeBinary, NULL);
		adpcmf.SeekToEnd();
		adpcmf.Seek(-0x3d - 12, CFile::end);
		//		adpcmf.Open("C:\\FALCOM\\Arcturus\\music.pak",CFile::modeRead|CFile::typeBinary,NULL);
		char file[19];
		char n[2];
		int st;
		int size;
		int ex;
		for (;;) {
			adpcmf.Read(&st, 4);
			adpcmf.Read(&size, 4);
			adpcmf.Read(&ex, 4);
			adpcmf.Read(file, 19);
			adpcmf.Read(n, 2);
			adpcmf.Seek(-(19 + 2 + 4 + 4 + 4) * 2, CFile::current);
			CString s;
			s = file; if (s.Find(filen.Left(6)) > 0) break;
		}

		adpcmf.Seek(st + 5, CFile::begin);
		adpcmf.Read(&wavbit, 2);
		data_size = oggsize = (ex) * 4;
		og->m_time.SetRange(0, (data_size) / 4, TRUE);
		adbuf = (char*)malloc(size * 10);
		adbuf2 = (char*)calloc(size * 6 * 2, 1);
		ZeroMemory(adbuf2, size * 6);
		ZeroMemory(adbuf, size * 6);
		loop1 = 0;
		loop2 = ex;
		adpcmf.Seek(st, CFile::begin);
		if (readadpcmarc(adpcmf, adbuf, (int)(size))) { thend = 1; free(adbuf); adpcmf.Close(); return; }
		free(adbuf);
		adpcmf.Close();
	}
	thend = 1;
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////ADPCM DATA+READ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

int lbuf = 0;
static int MS_Delta[] =
{
	230, 230, 230, 230, 307, 409, 512, 614,
	768, 614, 512, 409, 307, 230, 230, 230
};

static ADPCMCOEFSET MSADPCM_CoeffSet[] =
{
	{ 256, 0 },{ 512, -256 },{ 0, 0 },{ 192, 64 },{ 240, 0 },{ 460, -208 },{ 392, -232 }
};

int                 ideltaL, ideltaR;
int                 sample1L, sample2L;
int                 sample1R, sample2R;
ADPCMCOEFSET        coeffL, coeffR;
int                 nsamp;

int readadpcm2(char* bw, int cnt);
int seekadpcm(int pos);

BOOL playwavadpcm(BYTE* bw, int old, int l1, int l2)
{
	//	playb+=(l1+l2)/4;
	int rrr = readadpcm2((char*)bw + old, l1);
	if (l1 != rrr) {
		if (endf == 1) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = loop1 * 4; poss6 = 0;
			seekadpcm(loop1);
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readadpcm2((char*)bw + old + rrr, (int)l1 - rrr);
		}
	}
	if (l2) {
		rrr = readadpcm2((char*)bw, l2);
		if (l2 != rrr) {
			if (endf == 1) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = loop1 * 4; poss6 = 0;
				seekadpcm(loop1);
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readadpcm2((char*)bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return FALSE;
}

std::vector<uint8_t> outputRawBytesData;
int readtempo(BYTE* data, int len)
{
	//テンポ
	m_bufwav3_1.clear();
	m_bufwav3_1.resize(len);
	memcpy(m_bufwav3_1.data(), (data), len);
	ProcessAudioWithRubberBand(100.0f / tempo);
	ConvertFloatToRawBytes(m_convertedPcmFloatData, wavsam, wavch, outputRawBytesData);
	return outputRawBytesData.size();
}
using namespace std;

int readadpcm2(char* bw, int cnt)
{
	int r = cnt, rr = cnt;
	int cnt2;
	if (rr == 0)return 0;

	int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
	if (poss4 <= cnt) {
		while (true) {
			int f = 0;
			if (adbuf2 == NULL) return 0;
			if (rrr == 1)
				memcpy((void*)bufkpi, (void*)(adbuf2 + lenl), cnt);
			else
			{
				ZeroMemory(bufkpi, cnt);
				muon--;
			}

			if (playb > (data_size + 100000) / 4 && muon != 0) {
				rrr = 0;
			}
			if (muon <= 0) {
				endf = 1;
				return 0;
			}

			int len2 = readtempo(bufkpi, cnt);
			lenl += cnt;

			if (len2 > 0) {
				// 書き込み
				if (poss2 + len2 > max_buffer_size) {
					int first = max_buffer_size - poss2;
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
					memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
					poss2 = (poss2 + len2) % max_buffer_size;
				}
				else {
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
					poss2 += len2;
				}
				poss4 += len2;
			}
			playb += (len2 / 4);
			if (poss4 > cnt) break;
		}
	}
	
	int cnt0 = cnt;
	if (loop1 * 4 + loop2 * 4 < poss5 + cnt0 && endf == 0) {
		cnt0 = (loop1 * 4 + loop2 * 4) - poss5;
	}
	cnt2 = cnt0;
	
	if (cnt2 > 0) {
		if (poss3 + cnt0 > max_buffer_size) {
			int first = max_buffer_size - poss3;
			memcpy(bw, bufkpi3 + poss3, first);
			memcpy(bw + first, bufkpi3, cnt0 - first);
			poss3 = (poss3 + cnt0) % max_buffer_size;
		}
		else {
			memcpy(bw, bufkpi3 + poss3, cnt0);
			poss3 += cnt0;
		}
		poss4 -= cnt0;
	}

	short* b, c;
	b = (short*)bw;
	fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
	//fadeを三乗して計算密度を変更
	for (int i = 0; i < cnt0 / 2; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }

	if ((UINT)wl < (UINT)0x7fff0000) {
		//				if (cc1 == 1)	cc.Write(bw, cnt);
		if (cc1 == 1)	cc.Write(bw, cnt0);
		//				if (cc1 == 1)	cc.Write(bufkpi, r);
		wl += cnt0;
	}


	poss5 += cnt0 * (tempo / 100.0f);

	return cnt0;
}

int seekadpcm(int pos)
{
	lenl = pos * 4;
	playb = pos;
	poss5 = lenl;
	return 0;
}

static inline short  R16(const unsigned char* src)
{
	return (short)((unsigned short)src[0] | ((unsigned short)src[1] << 8));
}

static inline void  W16(unsigned char* dst, short s)
{
	dst[0] = LOBYTE(s);
	dst[1] = HIBYTE(s);
}

static inline void clamp_sample(int* sample)
{
	if (*sample < -32768) *sample = -32768;
	if (*sample > 32767) *sample = 32767;
}

static inline void process_nibble(unsigned nibble, int* idelta,
	int* sample1, int* sample2,
	const ADPCMCOEFSET* coeff)
{
	int sample;
	int snibble;

	/* nibble is in fact a signed 4 bit integer => propagate sign if needed */
	snibble = (nibble & 0x08) ? (nibble - 16) : nibble;
	sample = ((*sample1 * coeff->iCoef1) + (*sample2 * coeff->iCoef2)) / 256 +
		snibble * *idelta;
	clamp_sample(&sample);

	*sample2 = *sample1;
	*sample1 = sample;
	*idelta = ((MS_Delta[nibble] * *idelta) / 256);
	if (*idelta < 16) *idelta = 16;
}

unsigned char* bbuf1;
unsigned char* bw2;

int readadpcm(CFile& adpcmf, char* bw, int len)
{
	int c = 0;
	adpcmf.SeekToBegin();
	adpcmf.Read(bbuf, 0x2c);
	int cnt = 2048;
	int ak = 0, lbuf = 0;
	bw2 = (unsigned char*)bw;
	for (;;) {
		if (lbuf == 0) {
			adpcmf.Read(abuf, 0x8);
			lbuf = 0x5000;
		}

		if (ak == 0) {
			cnt = adpcmf.Read(bbuf, 2048);
			if (cnt == 0) {
				wavwait = 1;
				return 0;
			}
			bbuf1 = (unsigned char*)bbuf;
			coeffL = MSADPCM_CoeffSet[*bbuf1++];
			coeffR = MSADPCM_CoeffSet[*bbuf1++];
			ideltaL = R16(bbuf1);    bbuf1 += 2;
			ideltaR = R16(bbuf1);    bbuf1 += 2;
			sample1L = R16(bbuf1);    bbuf1 += 2;
			sample1R = R16(bbuf1);    bbuf1 += 2;
			sample2L = R16(bbuf1);    bbuf1 += 2;
			sample2R = R16(bbuf1);    bbuf1 += 2;
			sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
			sample2L = (int)((float)sample2L * (float)savedata.kakuVal / 100.0f);
			sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
			sample2R = (int)((float)sample2R * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample2L);      bw2 += 2;
			W16(bw2, sample2R);      bw2 += 2;
			W16(bw2, sample1L);      bw2 += 2;
			W16(bw2, sample1R);      bw2 += 2;
			lbuf -= 14;
		}
		for (int k = ak; k < (cnt - 14); k++) {
			process_nibble(*bbuf1 >> 4, &ideltaL, &sample1L, &sample2L, &coeffL);
			sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample1L);	bw2 += 2;
			process_nibble(*bbuf1++ & 0x0F, &ideltaR, &sample1R, &sample2R, &coeffR);
			sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample1R);	bw2 += 2;	lbuf--;
			c += 4; if (c >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
			if (thend1 == TRUE) return 1;
		}
		ak = 0;
	}
}

int readadpcmzwei(CFile& adpcmf, char* bw, int len)
{
	adpcmf.Read(bbuf, 0x2c);
	//	adpcmf.Read(bbuf,0x800);
	//	adpcmf.Read(abuf,0x8);
	int c = 0;
	int cnt = 2048;
	int ak = 0, lbuf = 0, o = 0;
	bw2 = (unsigned char*)bw;
	for (;;) {
		if (lbuf == 0) {
			adpcmf.Read(abuf, 0x8);
			lbuf = 0x5000;
		}
		if (ak == 0) {
			cnt = adpcmf.Read(bbuf, 2048);
			if (cnt == 0)
				return 0;
			bbuf1 = (unsigned char*)bbuf;
			coeffL = MSADPCM_CoeffSet[*bbuf1++];
			coeffR = MSADPCM_CoeffSet[*bbuf1++];
			ideltaL = R16(bbuf1);    bbuf1 += 2;
			ideltaR = R16(bbuf1);    bbuf1 += 2;
			sample1L = R16(bbuf1);    bbuf1 += 2;
			sample1R = R16(bbuf1);    bbuf1 += 2;
			sample2L = R16(bbuf1);    bbuf1 += 2;
			sample2R = R16(bbuf1);    bbuf1 += 2;
			sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
			sample2L = (int)((float)sample2L * (float)savedata.kakuVal / 100.0f);
			sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
			sample2R = (int)((float)sample2R * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample2L);      bw2 += 2;
			W16(bw2, sample2R);      bw2 += 2;
			W16(bw2, sample1L);      bw2 += 2;
			W16(bw2, sample1R);      bw2 += 2;
			len -= 14; lbuf -= 14;
		}
		for (int k = ak; k < (cnt - 14); k++) {
			process_nibble(*bbuf1 >> 4, &ideltaL, &sample1L, &sample2L, &coeffL);
			if (o == 0) {
				W16(bw2, 0);	bw2 += 2;
			}
			else {
				sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
				W16(bw2, sample1L);	bw2 += 2;
			}
			process_nibble(*bbuf1++ & 0x0F, &ideltaR, &sample1R, &sample2R, &coeffR);
			if (o == 0) {
				W16(bw2, 0);	bw2 += 2;
			}
			else {
				sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
				W16(bw2, sample1R);	bw2 += 2;
			}
			len--; lbuf--;
			c += 4; if (c >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
			if (len <= 0) return 0;
			if (thend1 == TRUE) return 1;
		}
		ak = 0;
		o = 1;
	}
}

int readadpcmgurumin(CFile& adpcmf, char* bw, int len)
{
	int c = 0;
	int cnt = 2048;
	int ak = 0, lbuf = 0;
	bw2 = (unsigned char*)bw;
	for (;;) {
		if (lbuf == 0) {
			adpcmf.Read(abuf, 0x8);
			lbuf = 0x5000;
		}
		if (ak == 0) {
			cnt = adpcmf.Read(bbuf, 2048);
			if (cnt == 0)
				return 0;
			bbuf1 = (unsigned char*)bbuf;
			coeffL = MSADPCM_CoeffSet[*bbuf1++];
			coeffR = MSADPCM_CoeffSet[*bbuf1++];
			ideltaL = R16(bbuf1);    bbuf1 += 2;
			ideltaR = R16(bbuf1);    bbuf1 += 2;
			sample1L = R16(bbuf1);    bbuf1 += 2;
			sample1R = R16(bbuf1);    bbuf1 += 2;
			sample2L = R16(bbuf1);    bbuf1 += 2;
			sample2R = R16(bbuf1);    bbuf1 += 2;
			sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
			sample2L = (int)((float)sample2L * (float)savedata.kakuVal / 100.0f);
			sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
			sample2R = (int)((float)sample2R * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample2L);      bw2 += 2;
			W16(bw2, sample2R);      bw2 += 2;
			W16(bw2, sample1L);      bw2 += 2;
			W16(bw2, sample1R);      bw2 += 2;
			len -= 14; lbuf -= 14;
		}
		for (int k = ak; k < (cnt - 14); k++) {
			process_nibble(*bbuf1 >> 4, &ideltaL, &sample1L, &sample2L, &coeffL);
			sample1L = (int)((float)sample1L * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample1L);	bw2 += 2;
			process_nibble(*bbuf1++ & 0x0F, &ideltaR, &sample1R, &sample2R, &coeffR);
			sample1R = (int)((float)sample1R * (float)savedata.kakuVal / 100.0f);
			W16(bw2, sample1R);	bw2 += 2;
			len--; lbuf--;
			c += 4; if (c >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
			if (len <= 0) return 0;
			if (thend1 == TRUE) return 1;
		}
		ak = 0;
	}
}


typedef struct ADPCMChannelStatus {
	int predictor;
	short int step_index;
	int step;
} ADPCMChannelStatus;

typedef struct ADPCMContext {
	ADPCMChannelStatus status[2];
} ADPCMContext;

static const int index_table[16] = {
	-1, -1, -1, -1, 2, 4, 6, 8,
	-1, -1, -1, -1, 2, 4, 6, 8,
};

static const int step_table[89] = {
	7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
	19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
	50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
	130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
	337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
	876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
	2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
	5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
	15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

int adpcm_decode_init(ADPCMContext* c);
short adpcm_ima_expand_nibble(ADPCMChannelStatus* c, char nibble);
int adpcm_decode_frame_file(ADPCMContext* c, int channels, CFile& fd, char* fdo, int maxsize, char* bw);
int adpcm_decode_init(ADPCMContext* c) {
	memset(c, 0, sizeof(ADPCMContext));
	return 0;
}

short adpcm_ima_expand_nibble(ADPCMChannelStatus* c, char nibble) {
	int     diff,
		step;

	step = step_table[c->step_index];
	c->step_index += index_table[(unsigned)nibble];
	if (c->step_index < 0) c->step_index = 0;
	else if (c->step_index > 88) c->step_index = 88;
	diff = 0;
	if (nibble & 4) diff = step << 2;
	if (nibble & 2) diff += step << 1;
	if (nibble & 1) diff += step;
	diff >>= 2;
	if (nibble & 8) c->predictor -= diff;
	else c->predictor += diff;
	if (c->predictor < -32768) c->predictor = -32768;
	else if (c->predictor > 32767) c->predictor = 32767;
	return((short)c->predictor);
}


static unsigned int get_word(unsigned char* p) {
	return (p[0] + (p[1] << 8));
}

static unsigned long get_dword(unsigned char* p) {
	return (p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24));
}


static char flag_tbl[256][8];

static void make_flag_tbl(void) {
	int k, n, m;
	int c;
	for (n = 0; 256 > n; ++n) {
		c = -1;
		flag_tbl[n][0] = -1;
		m = n;
		for (k = 0; 8 > k; ++k) {
			if (0 != (m & 1)) {
				c += 1;
				flag_tbl[n][c] = 0;
			}
			else {
				if ((0 > c) || (0 == flag_tbl[n][c])) {
					c += 1;
					flag_tbl[n][c] = 0;
				}
				flag_tbl[n][c] += 1;
			}
			m >>= 1;
		}
		if (7 > c) {
			c += 1;
			flag_tbl[n][c] = -1;
		}
	}
}



static int expand(unsigned char* dest, long dest_size, unsigned char* src, long src_size, ADPCMContext* c, CFile& f) {
	long ofs = 0, d_ofs = 0;
	int mae = 0, cc = 0, rs = 0, rss = 0;
	short   samples[2];
	bw2 = (unsigned char*)adbuf2;
	ofs = 0;
	d_ofs = 0;
	while (ofs < src_size) {
		if (rs < src_size) {
			rss = f.Read(src + rs, 8096); rs += rss;
		}
		char* flag;
		int k;

		flag = flag_tbl[src[ofs]];
		ofs += 1;

		for (k = 0; 8 > k; ++k) {
			long t_ofs, t_len, t;

			if (src_size <= ofs) {
				break;
			}

			t_len = flag[k];
			if (0 > t_len) {
				break;
			}

			if (0 < t_len) {
				memcpy((dest + d_ofs), (src + ofs), t_len);
				d_ofs += t_len;
				ofs += t_len;
				continue;
			}

			t_ofs = get_word(src + ofs);
			t_len = ((t_ofs >> 12) + 2);
			t_ofs = (t_ofs & 0xfff);
			ofs += 2;

			t = t_ofs;
			t_ofs = (d_ofs - t_ofs);
			while (0 < t_len) {
				if (t_len < t) {
					t = t_len;
				}
				memcpy((dest + d_ofs), (dest + t_ofs), t);
				d_ofs += t;
				t_len -= t;
				t += t;
			}
			if (d_ofs > 0x10) {
				samples[0] = adpcm_ima_expand_nibble(&c->status[0], (dest[mae + 0x10] >> 4) & 0x0F);
				samples[1] = adpcm_ima_expand_nibble(&c->status[1], dest[mae + 0x10] & 0x0F);
				memcpy(bw2, &samples, sizeof(samples)); bw2 += sizeof(samples);
				cc += 4; if (cc >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
				if (thend1 == TRUE) return 0;
				mae++;
			}
		}
	}
	for (; mae < d_ofs - 16 - 44100;) {
		samples[0] = adpcm_ima_expand_nibble(&c->status[0], (dest[mae + 0x10] >> 4) & 0x0F);
		samples[1] = adpcm_ima_expand_nibble(&c->status[1], dest[mae + 0x10] & 0x0F);
		memcpy(bw2, &samples, sizeof(samples)); bw2 += sizeof(samples);
		cc += 4; if (cc >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
		if (thend1 == TRUE) return 0;
		mae++;
	}
	float fa = 1.0f; int cnt;//プチっとノイズは最後の最後をフェードアウトさせて消す(誤魔化す)
	for (cnt = 0; mae < d_ofs - 16; cnt++) {
		samples[0] = adpcm_ima_expand_nibble(&c->status[0], (dest[mae + 0x10] >> 4) & 0x0F);
		samples[1] = adpcm_ima_expand_nibble(&c->status[1], dest[mae + 0x10] & 0x0F);
		samples[0] = (short)((float)samples[0] * fa);
		samples[1] = (short)((float)samples[1] * fa);
		memcpy(bw2, &samples, sizeof(samples)); bw2 += sizeof(samples);
		cc += 4; if (cc >= (int)(WAVDALen / OUTPUT_BUFFER_NUM) * 8)	wavwait = 1;
		if (thend1 == TRUE) return 0;
		mae++;
		fa = (44100.0f - (float)cnt) / 44100.0f;
	}
	return d_ofs;
}


int readadpcmarc(CFile& adpcmf, char* bw, int len)
{
	ADPCMContext    ctx;

	adpcm_decode_init(&ctx);
	make_flag_tbl();
	BYTE* b; b = new BYTE[len * 2];
	//    expand(&ctx, 2, adpcmf, bw, len,bw);
	expand(b, 4096, (BYTE*)bw, len, &ctx, adpcmf);
	delete[] b;

	wavwait = 1;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////DirectSond Read///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


int playwavkpi(BYTE* bw, int old, int l1, int l2)
{
	if (og->mod == NULL) return 0;
	playb += (l1 + l2) / (wavsam / 4);
	//データ読み込み
	int rrr = readkpi(bw + old, l1);
	if (l1 != rrr) {
		if (endf == 1) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;

		}
		else {
			loopcnt++;
			playb = loop1;
			og->mod->SetPosition(og->kmp1, 0);
			poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readkpi(bw + old + rrr, l1 - rrr);
		}
	}
	if (l2) {
		rrr = readkpi(bw, l2);
		if (l2 != rrr) {
			if (endf == 1) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;

			}
			else {
				loopcnt++;
				playb = loop1;
				og->mod->SetPosition(og->kmp1, 0);
				poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readkpi(bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return l1 + l2;
}



int readkpi(BYTE* bw, int cnt)
{
	if (cnt == 0) return 0;
	_set_se_translator(trans_func);
	DWORD cnt1 = og->sikpi.dwUnitRender * 2, cnt2 = (DWORD)cnt, cnt4; if (cnt1 == 0) cnt1 = 1024;
	DWORD r = cnt;
	try {
		int len3 = 0, len4 = 0;
		int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
		if (poss4 <= cnt) {
			r = 0;
			while(true) {
				for (;;) {
					if (cnt2 <= cnt3) { r = 1; break; }
					if (IsBadCodePtr((FARPROC)og->mod->Render) == 0)
						r = og->mod->Render(og->kmp1, (BYTE*)bufkpi + cnt3, cnt1);
					if (r == 0) break;
					//		mod->Render(kmp,(BYTE*)bw,cnt);
					cnt3 += r;
				}
				int len2 = readtempo(bufkpi, cnt);
				if (cnt2 <= cnt3) {
					cnt3 -= cnt2;
					if (cnt3 != 0)	memcpy(bufkpi, bufkpi + cnt2, cnt3);
				}

				if (len2 > 0) {
					// 書き込み
					if (poss2 + len2 > max_buffer_size) {
						int first = max_buffer_size - poss2;
						memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
						memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
						poss2 = (poss2 + len2) % max_buffer_size;
					}
					else {
						memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
						poss2 += len2;
					}
					poss4 += len2;
					if (poss4 > cnt) break;
					//if (cnt4 < cnt) return  cnt4;
				}
			}
		}

		cnt2 = cnt;

		if (cnt2 > 0) {
			int to_read = cnt;
			if (poss3 + to_read > max_buffer_size) {
				int first = max_buffer_size - poss3;
				memcpy(bw, bufkpi3 + poss3, first);
				memcpy(bw + first, bufkpi3, to_read - first);
				poss3 = (poss3 + to_read) % max_buffer_size;
			}
			else {
				memcpy(bw, bufkpi3 + poss3, to_read);
				poss3 += to_read;
			}
			poss4 -= to_read;
		}

		cnt4 = cnt3;
		if (r == 0) cnt = 0;
		__int64 bfc, bc2;
		bfc = 0;
		if (wavsam == 24) {
			Int24* bf1; bf1 = (Int24*)bw;
			bc2 = (int)(Int24)bf1[0] / 256;
			for (int i = 0; i < cnt / 2; i++) {
				bfc += (__int64)(int)(Int24)bf1[i] / 256;
			}
			if (cnt)
				bfc /= (cnt / 2);
			if ((short)bc2 >= (short)bfc - 10 && (short)bc2 <= (short)bfc + 10) bufzero++; else bufzero = 0;
		}
		else {
			unsigned short* bf1; bf1 = (unsigned short*)bw;
			bc2 = (short)bf1[0];
			for (int i = 0; i < cnt / 2; i++) {
				bfc += (__int64)(short)bf1[i];
			}
			if (cnt)
				bfc /= (cnt / 2);
			if ((short)bc2 >= (short)bfc - 10 && (short)bc2 <= (short)bfc + 10) bufzero++; else bufzero = 0;
		}
		int looping = loop2 / 100000;
		if (looping < 20) looping = 20;
		if (looping > 80) looping = 80;

		short* b, c;
		b = (short*)bw;
		Int24* b24c;
		b24c = (Int24*)bw;
		//	CString sss=og->kpi;
		CString sss;
		sss = filen.Right(filen.GetLength() - filen.ReverseFind('.') - 1);
		sss.MakeLower();
		if (wavsam == 24) {
			for (int i = 0; i < cnt / 3; i++) {
				int c4 = b24c[i];
				c4 = (int)((float)c4 * ((float)savedata.kakuVal / 100.0f));
				b24c[i] = c4;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) {
				int c = (int)b[i];
				c = (int)((float)c * ((float)savedata.kakuVal / 100.0f));
				b[i] = (short)c;
			}
		}
		if (sss == "spc" || sss.Left(3) == "hes") {
			if (savedata.spc != 1)
				if (wavsam == 24) {
					for (int i = 0; i < cnt / 3; i++) {
						int c4 = b24c[i];
						if (savedata.spc == 2)	c4 = (int)((float)c4 * 2.0f);
						else if (savedata.spc == 4) c4 = (int)((float)c4 * 3.0f);
						else if (savedata.spc == 8) c4 = (int)((float)c4 * 4.0f);
						else if (savedata.spc == 16) c4 = (int)((float)c4 * 5.0f);
						if (c4 > 8388607)c4 = 8388607;
						if (c4 < -8388608)c4 = -8388608;
						b24c[i] = c4;
					}
				}
				else {
					for (int i = 0; i < cnt / 2; i++) {
						int c = (int)b[i];
						if (savedata.spc == 2)	c = (int)((float)b[i] * 2.0f);
						else if (savedata.spc == 4) c = (int)((float)b[i] * 3.0f);
						else if (savedata.spc == 8) c = (int)((float)b[i] * 4.0f);
						else if (savedata.spc == 16) c = (int)((float)b[i] * 5.0f);
						if (c >= 32768)c = 32767;
						if (c < -32768)c = -32768;
						b[i] = (short)c;
					}
				}
		}
		if (savedata.kpivol != 1) {
			if (wavsam == 24) {
				for (int i = 0; i < cnt / 3; i++) {
					int c4 = b24c[i];
					if (savedata.kpivol == 2)	c4 = (int)((float)c4 * 2.0f);
					else if (savedata.kpivol == 4) c4 = (int)((float)c4 * 3.0f);
					else if (savedata.kpivol == 8) c4 = (int)((float)c4 * 4.0f);
					else if (savedata.kpivol == 16) c4 = (int)((float)c4 * 5.0f);
					if (c4 > 8388607)c4 = 8388607;
					if (c4 < -8388608)c4 = -8388608;
					b24c[i] = c4;
				}
			}
			else {
				for (int i = 0; i < cnt / 2; i++) {
					int c = (int)b[i];
					if (savedata.kpivol == 2)	c = (int)((float)b[i] * 2.0f);
					else if (savedata.kpivol == 3) c = (int)((float)b[i] * 3.0f);
					else if (savedata.kpivol == 4) c = (int)((float)b[i] * 4.0f);
					else if (savedata.kpivol == 5) c = (int)((float)b[i] * 5.0f);
					if (c >= 32768.0f)c = 32767;
					if (c < -32768.0f)c = -32768;
					b[i] = (short)c;
				}
			}
		}
		fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
		//fadeを三乗して計算密度を変更
		if (wavsam == 24) {
			float c4;
			int c5;
			for (int i = 0; i < cnt / 3; i++) {
				c5 = b24c[i]; c4 = (float)c5;
				c4 = c4 * fade * fade; c5 = (int)c4;
				b24c[i] = c5;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }
		}
		if ((UINT)wl < (UINT)0x7fff0000) {
			if (cc1 == 1)	cc.Write(bw, cnt);
			wl += cnt;
		}
		lenl += cnt;
		//	playb+=cnt/4;
	}
	catch (SE_Exception e) {
	}
	catch (_EXCEPTION_POINTERS* ep) {
	}
	catch (...) {}
	
	return cnt;
}

int playwavm4a(BYTE* bw, int old, int l1, int l2)
{
	//データ読み込み
	int rrr = readm4a(bw + old, l1);
	playb += (int)((float)(l1 + l2) / ((wavch == 1 || wavch == 2) ? (float)4 : (float)(wavch * 2)) / ((float)wavsam / (float)16));
	//	if (oggsize / ((wavch == 1) ? 1 : 1) - 44100 <= playb * 4) {
	//	if (savedata.saveloop == FALSE) {
	//	l1 = rrr;  fade1 = 1;
	//			return l1;
	//	}
	//}
/*	if (oggsize / ((wavch == 1) ? 2 : 1)- 50000 <= (int)(playb * wavch * 2 * (wavsam / 16.0))) {
		if (savedata.saveloop == FALSE) {
			l1 = rrr; fade1 = 1;
			return l1;
		}
	}*/

	if (l1 != rrr) {
		if (savedata.saveloop == 0 && endf == 1) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			m4a_.SetPosition(og->kmp, 0);
			poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readm4a(bw + old + rrr, l1 - rrr);
		}
	}
	if (l2) {
		rrr = readm4a(bw, l2);
		if (l2 != rrr) {
			if (savedata.saveloop == 0 && endf == 1) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				m4a_.SetPosition(og->kmp, 0);
				poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readm4a(bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return l1 + l2;
}

int readm4a(BYTE* bw, int cnt)
{
	if (cnt == 0) return 0;
	_set_se_translator(trans_func);
	DWORD cnt1 = og->sikpi.dwUnitRender, cnt2 = (DWORD)cnt, cnt4 = 0; if (cnt1 == 0) cnt1 = 4096;
	DWORD r = 0;
	{
		int len3 = 0, len4 = 0;
		int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
		if (poss4 <= cnt) {
			while (true) {
				if (rrr == 1) {
					for (;;) {
						if (cnt2 <= cnt3) break;
						r = m4a_.Render(og->kmp, (BYTE*)bufkpi + cnt3, cnt1);
						cnt3 += r;
						if (r == 0) break;
					}
					if (rrr == 0 && muon != 0) {
						r = cnt;
						ZeroMemory(bufkpi, r);
						muon--;
					}
					if (rrr == 0 && muon == MUON) {
						ZeroMemory(bufkpi + r, cnt - r);
						r = cnt;
						muon--;
					}
					if (muon == 0) r = 0;

					int len2 = readtempo(bufkpi, cnt);

					if (len2 > 0) {
						// 書き込み
						if (poss2 + len2 > max_buffer_size) {
							int first = max_buffer_size - poss2;
							memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
							memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
							poss2 = (poss2 + len2) % max_buffer_size;
						}
						else {
							memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
							poss2 += len2;
						}
						poss4 += len2;
						if (cnt3 < cnt) return cnt4;
						if (cnt2 <= cnt3) {
							cnt3 -= cnt2;
							if (cnt3 != 0)	memcpy(bufkpi, bufkpi + cnt2, cnt3);
						}
					}
					if (poss4 > cnt) break;
				}
			}
		}

		cnt2 = cnt;

		if (cnt2 > 0) {
			int to_read = cnt;
			if (poss3 + to_read > max_buffer_size) {
				int first = max_buffer_size - poss3;
				memcpy(bw, bufkpi3 + poss3, first);
				memcpy(bw + first, bufkpi3, to_read - first);
				poss3 = (poss3 + to_read) % max_buffer_size;
			}
			else {
				memcpy(bw, bufkpi3 + poss3, to_read);
				poss3 += to_read;
			}
			poss4 -= to_read;
		}


		cnt4 = cnt3;
		//if (r == 0) cnt = 0;
		memcpy(bufkpi2, bw, cnt);
		unsigned short* bf1, * bf2; bf1 = (unsigned short*)bw; bf2 = (unsigned short*)bufkpi2;
		int cnt1 = cnt / 2;
		switch (wavch)
		{
		case 1:
		case 2:
			break;
		case 3: // 2.1   
			for (int sample = 0; sample < cnt1; sample += wavch)
			{
				int ChannelMap[3] = { 2,3,1 };
				for (int ch = 0; ch < wavch; ch++)
				{
					*bf1++ = bf2[ChannelMap[ch] - 1];
				}
				bf2 += wavch;
			}
			break;
		case 4: // Quad   
			for (int sample = 0; sample < cnt1; sample += wavch)
			{
				int ChannelMap[4] = { 2,3,1,4 };
				for (int ch = 0; ch < wavch; ch++)
				{
					*bf1++ = bf2[ChannelMap[ch] - 1];
				}
				bf2 += wavch;
			}
			break;
		case 5: // Surround   
			for (int sample = 0; sample < cnt1; sample += wavch)
			{
				int ChannelMap[5] = { 2,3,1,4,5 };
				for (int ch = 0; ch < wavch; ch++)
				{
					*bf1++ = bf2[ChannelMap[ch] - 1];
				}
				bf2 += wavch;
			}
			break;
		case 6: // 5.1   
			for (int sample = 0; sample < cnt1; sample += wavch)
			{
				int ChannelMap[6] = { 2,3,1,6,4,5 };
				for (int ch = 0; ch < wavch; ch++)
				{
					*bf1++ = bf2[ChannelMap[ch] - 1];
				}
				bf2 += wavch;
			}
			break;
		}
		Int24* b24c;
		b24c = (Int24*)bw;
		short* b, c;
		b = (short*)bw;
		if (wavsam == 24) {
			for (int i = 0; i < cnt / 3; i++) {
				int c4 = b24c[i];
				c4 = (int)((float)c4 * ((float)savedata.kakuVal / 100.0f));
				b24c[i] = c4;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) {
				int c = (int)b[i];
				c = (int)((float)c * ((float)savedata.kakuVal / 100.0f));
				b[i] = (short)c;
			}
		}
		if (wavsam == 24) {
			for (int i = 0; i < cnt / 3; i++) {
				int c4 = b24c[i];
				if (savedata.mp3 == 2)	c4 = (int)((float)c4 * 2.0f);
				else if (savedata.mp3 == 4) c4 = (int)((float)c4 * 3.0f);
				else if (savedata.mp3 == 8) c4 = (int)((float)c4 * 4.0f);
				else if (savedata.mp3 == 16) c4 = (int)((float)c4 * 5.0f);
				if (c4 > 8388607)c4 = 8388607;
				if (c4 < -8388608)c4 = -8388608;
				b24c[i] = c4;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) {
				int c = (int)b[i];
				if (savedata.mp3 == 2)	c = (int)((float)b[i] * 1.5f);
				else if (savedata.mp3 == 3) c = (int)((float)b[i] * 2.0f);
				else if (savedata.mp3 == 4) c = (int)((float)b[i] * 2.5f);
				else if (savedata.mp3 == 5) c = (int)((float)b[i] * 3.0f);
				if (c >= 32768)c = 32767;
				if (c <= -32767)c = -32766;
				b[i] = (short)c;
			}
		}
		fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
		//fadeを三乗して計算密度を変更
		if (wavsam == 24) {
			float c4;
			int c5;
			for (int i = 0; i < cnt / 3; i++) {
				c5 = b24c[i]; c4 = (float)c5;
				c4 = c4 * fade * fade; c5 = (int)c4;
				b24c[i] = c5;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }
		}
		if ((UINT)wl < (UINT)0x7fff0000) {
			if (cc1 == 1)	cc.Write(bw, cnt);
			wl += cnt;
		}
		lenl += cnt;
	}
	return cnt;
}

int playwavflac(BYTE* bw, int old, int l1, int l2)
{
	//データ読み込み
	int rrr = readflac(bw + old, l1);
	if (flacmode == 0)
		playb += (l1 + l2) / (wavsam / 4);
	if (l1 != rrr) {
		if (savedata.saveloop == 0 && endf == 1 && flacmode == 0) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			rrr /= 6;
			rrr *= 6;
			flac_.SetPosition(og->kmp, loop1);
			poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readflac(bw + old + rrr, l1 - rrr);
		}
	}
	if (l2) {
		rrr = readflac(bw, l2);
		if (l2 != rrr) {
			if (savedata.saveloop == 0 && endf == 1 && flacmode == 0) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				rrr /= 6;
				rrr *= 6;
				flac_.SetPosition(og->kmp, loop1);
				poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readflac(bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return l1 + l2;
}

int readflac(BYTE* bw, int cnt)
{
	if (cnt == 0)return 0;
	_set_se_translator(trans_func);
	DWORD cnt1 = og->sikpi.dwUnitRender * 2, cnt2 = (DWORD)cnt, cnt4 = 0, lenl = cnt; if (cnt1 == 0) cnt1 = 1024;
	DWORD r = 0;
	if (flacmode == 1)
		if (playb + lenl / 6 > (loop1 + loop2)) lenl = ((loop1 + loop2) - playb) * 6;
	try {
		int len3 = 0, len4 = 0;
		int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
		if (poss4 <= cnt) {
			while (true) {

				if (rrr == 1)
					r = flac_.Render(og->kmp, (BYTE*)bufkpi, lenl);
				if (r != lenl && savedata.saveloop == 0)
					rrr = 0;
				if (rrr == 0 && muon != 0) {
					r = lenl;
					ZeroMemory(bufkpi, r);
					muon--;
				}
				if (rrr == 0 && muon == MUON) {
					ZeroMemory(bufkpi + r, lenl - r);
					r = lenl;
					muon--;
				}
				if (muon == 0) r = 0;
				cnt4 = r;
				if (r == 0) lenl = 0;
				if (r == 0) break;

				int len2 = readtempo(bufkpi, lenl);
				if (len2 > 0) {
					// 書き込み
					if (poss2 + len2 > max_buffer_size) {
						int first = max_buffer_size - poss2;
						memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
						memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
						poss2 = (poss2 + len2) % max_buffer_size;
					}
					else {
						memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
						poss2 += len2;
					}
					poss4 += len2;
					if (cnt4 != lenl) return cnt4;
					if (poss4 > cnt) break;
				}
			}
		}

		cnt2 = lenl;

		if (cnt2 > 0) {
			int to_read = cnt;
			if (poss3 + to_read > max_buffer_size) {
				int first = max_buffer_size - poss3;
				memcpy(bw, bufkpi3 + poss3, first);
				memcpy(bw + first, bufkpi3, to_read - first);
				poss3 = (poss3 + to_read) % max_buffer_size;
			}
			else {
				memcpy(bw, bufkpi3 + poss3, to_read);
				poss3 += to_read;
			}
			poss4 -= to_read;
		}
		cnt4 = lenl;
		unsigned short* bf1, * bf2; bf1 = (unsigned short*)bw; bf2 = (unsigned short*)bufkpi2;
		//		int fw = playb % (wavch);
		//		bf2 += fw;
		int lenl1 = lenl / 2;
		Int24* b24c;
		b24c = (Int24*)bw;
		short* b, c;
		b = (short*)bw;
		if (wavsam == 24) {
			for (int i = 0; i < lenl / 3; i++) {
				int c4 = b24c[i];
				if (savedata.mp3 == 2)	c4 = (int)((float)c4 * 2.0f);
				else if (savedata.mp3 == 4) c4 = (int)((float)c4 * 3.0f);
				else if (savedata.mp3 == 8) c4 = (int)((float)c4 * 4.0f);
				else if (savedata.mp3 == 16) c4 = (int)((float)c4 * 5.0f);
				if (c4 > 8388607)c4 = 8388607;
				if (c4 < -8388608)c4 = -8388608;
				b24c[i] = c4;
			}
		}
		else {
			for (int i = 0; i < lenl / 2; i++) {
				int c = (int)b[i];
				if (savedata.mp3 == 2)	c = (int)((float)b[i] * 1.5f);
				else if (savedata.mp3 == 3) c = (int)((float)b[i] * 2.0f);
				else if (savedata.mp3 == 4) c = (int)((float)b[i] * 2.5f);
				else if (savedata.mp3 == 5) c = (int)((float)b[i] * 3.0f);
				if (c >= 32768)c = 32767;
				if (c <= -32767)c = -32766;
				b[i] = (short)c;
			}
		}
		fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
		//fadeを三乗して計算密度を変更
		if (wavsam == 24) {
			float c4;
			int c5;
			for (int i = 0; i < lenl / 3; i++) {
				c5 = b24c[i]; c4 = (float)c5;
				c4 = c4 * fade * fade; c5 = (int)c4;
				b24c[i] = c5;
			}
		}
		else {
			for (int i = 0; i < lenl / 2; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }
		}
		if ((UINT)wl < (UINT)0x7fff0000) {
			if (cc1 == 1)	cc.Write(bw, lenl);
			wl += lenl;
		}
		//lenl += lenl;
		//	playb+=lenl/4;
	}
	catch (SE_Exception e) {
	}
	catch (_EXCEPTION_POINTERS* ep) {
	}
	catch (...) {}
	if (cnt4 < lenl) lenl = cnt4;
	if (flacmode == 1) playb += (lenl / 6);
	return lenl;
}

int playwavopus(BYTE* bw, int old, int l1, int l2)
{
	//データ読み込み
	int rrr = readopus(bw + old, l1);
	playb += (l1 + l2) / (wavsam / 4);
	if (l1 != rrr) {
		if (savedata.saveloop == 0 && endf == 1) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			opus_.SetPosition(og->kmp, 0);
			readopus(bw + old + rrr, l1 - rrr);
		}
	}
	if (l2) {
		rrr = readopus(bw, l2);
		if (l2 != rrr) {
			if (savedata.saveloop == 0 && endf == 1) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				opus_.SetPosition(og->kmp, 0);
				readopus(bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return l1 + l2;
}

int readopus(BYTE* bw, int cnt)
{
	if (cnt == 0)return 0;
	_set_se_translator(trans_func);
	DWORD cnt1 = og->sikpi.dwUnitRender * 2, cnt2 = (DWORD)cnt, cnt4; if (cnt1 == 0) cnt1 = 1024;
	DWORD r = 0;
	try {
		int len3 = 0, len4 = 0;
		int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
		if (poss4 <= cnt) {
			for (int k = 0; k < 3; k++) {
				if (rrr == 1) {
					r = opus_.Render(og->kmp, (BYTE*)bufkpi, cnt);
					if (r != cnt && savedata.saveloop == 0)
						rrr = 0;
					if (rrr == 0 && muon != 0) {
						r = cnt;
						ZeroMemory(bufkpi, r);
						muon--;
					}
					if (rrr == 0 && muon == MUON) {
						ZeroMemory(bufkpi + r, cnt - r);
						r = cnt;
						muon--;
					}
					if (muon == 0) r = 0;

					int len2 = readtempo(bufkpi, r);
					if ((UINT)wl < (UINT)0x7fff0000) {
						//				if (cc1 == 1)	cc.Write(bw, cnt);
						if (cc1 == 1)	cc.Write(outputRawBytesData.data(), len2);
						//				if (cc1 == 1)	cc.Write(bufkpi, r);
						wl += len2;
					}

					if (len2 > 0) {
						// 書き込み
						if (poss2 + len2 > max_buffer_size) {
							int first = max_buffer_size - poss2;
							memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
							memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
							poss2 = (poss2 + len2) % max_buffer_size;
						}
						else {
							memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
							poss2 += len2;
						}
						poss4 += len2;
						if (r < cnt) return cnt4;

					}
				}
			}

			cnt2 = lenl;

			if (cnt2 > 0) {
				int to_read = cnt;
				if (poss3 + to_read > max_buffer_size) {
					int first = max_buffer_size - poss3;
					memcpy(bw, bufkpi3 + poss3, first);
					memcpy(bw + first, bufkpi3, to_read - first);
					poss3 = (poss3 + to_read) % max_buffer_size;
				}
				else {
					memcpy(bw, bufkpi3 + poss3, to_read);
					poss3 += to_read;
				}
				poss4 -= to_read;
			}
		}


		cnt4 = r;
		if (r == 0) cnt = 0;
		unsigned short* bf1, * bf2; bf1 = (unsigned short*)bw; bf2 = (unsigned short*)bufkpi2;
		//		int fw = playb % (wavch);
		//		bf2 += fw;
		int cnt1 = cnt / 2;
		Int24* b24c;
		b24c = (Int24*)bw;
		short* b, c;
		b = (short*)bw;
		if (wavsam == 24) {
			for (int i = 0; i < cnt / 3; i++) {
				int c4 = b24c[i];
				if (savedata.mp3 == 2)	c4 = (int)((float)c4 * 2.0f);
				else if (savedata.mp3 == 4) c4 = (int)((float)c4 * 3.0f);
				else if (savedata.mp3 == 8) c4 = (int)((float)c4 * 4.0f);
				else if (savedata.mp3 == 16) c4 = (int)((float)c4 * 5.0f);
				if (c4 > 8388607)c4 = 8388607;
				if (c4 < -8388608)c4 = -8388608;
				b24c[i] = c4;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) {
				int c = (int)b[i];
				if (savedata.mp3 == 2)	c = (int)((float)b[i] * 1.5f);
				else if (savedata.mp3 == 3) c = (int)((float)b[i] * 2.0f);
				else if (savedata.mp3 == 4) c = (int)((float)b[i] * 2.5f);
				else if (savedata.mp3 == 5) c = (int)((float)b[i] * 3.0f);
				if (c >= 32768)c = 32767;
				if (c <= -32767)c = -32766;
				b[i] = (short)c;
			}
		}
		fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
		//fadeを三乗して計算密度を変更
		if (wavsam == 24) {
			float c4;
			int c5;
			for (int i = 0; i < cnt / 3; i++) {
				c5 = b24c[i]; c4 = (float)c5;
				c4 = c4 * fade * fade; c5 = (int)c4;
				b24c[i] = c5;
			}
		}
		else {
			for (int i = 0; i < cnt / 2; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }
		}
//		if ((UINT)wl < (UINT)0x7fff0000) {
//			if (cc1 == 1)	cc.Write(bw, cnt);
//			wl += cnt;
//		}
		lenl += cnt;
		//	playb+=cnt/4;
	}
	catch (SE_Exception e) {
	}
	catch (_EXCEPTION_POINTERS* ep) {
	}
	catch (...) {}
	return cnt;
}


int playwavdsd(BYTE* bw, int old, int l1, int l2)
{
	//データ読み込み
	if (l1 == 0) return 0;
	int rrr = readdsd(bw + old, l1);
	playb += (l1 + l2) / (wavsam / 4);
	if (oggsize / ((wavch == 1) ? 2 : 1) - 192 * 20 <= (int)(playb * wavch * 2 * (wavsam / 16.0))) {
		if (savedata.saveloop == FALSE) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
			return l1;
		}
	}
	if (l1 != rrr) {
		if (savedata.saveloop == 0) {
			l1 = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;

		}
		else if (savedata.saveloop == 1) {
			loopcnt++;
			playb = loop1;
			dsd_.kpiSetPosition(og->kmp, 0);
			poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readdsd(bw + old + rrr, l1 - rrr);
		}
		else {
			endflg = 1;
		}
	}
	if (l2) {
		rrr = readdsd(bw, l2);
		if (l2 != rrr) {
			if (savedata.saveloop == 0) {
				l2 = rrr;
				if (savedata.saverenzoku == 0)
					fade1 = 1;
				else
					endflg = 1;
			}
			else if (savedata.saveloop == 1) {
				loopcnt++;
				playb = loop1;
				dsd_.kpiSetPosition(og->kmp, 0);
				poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readdsd(bw + rrr, (int)l2 - rrr);
			}
			else {
				endflg = 1;
			}
		}
	}
	return l1 + l2;
}
extern int sek;
extern int flg3;
int readdsd(BYTE* bw, int cnt)
{
	if (cnt == 0)return 0;
	//_set_se_translator(trans_func);
	DWORD cnt2 = (DWORD)cnt;
	DWORD r = 0;
	int len3 = 0, len4 = 0;
	int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
	if (poss4 <= cnt) {
		while (true) {
			cnt3 = dsd_.kpiRender(og->kmp, (BYTE*)bufkpi, cnt / (wavch * wavsam / 8)) * (wavch * wavsam / 8);
			int len2 = readtempo(bufkpi, cnt);
			if (sek == 0) {
				if (cnt2 <= cnt3) {
					cnt3 -= cnt2;
					if (cnt3 != 0)	memcpy(bufkpi, bufkpi + cnt2, cnt3);
				}
			}

			if (len2 > 0) {
				// 書き込み
				if (poss2 + len2 > max_buffer_size) {
					int first = max_buffer_size - poss2;
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
					memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
					poss2 = (poss2 + len2) % max_buffer_size;
				}
				else {
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
					poss2 += len2;
				}
				poss4 += len2;
			}
			if (len4 != 0) break;
			if (poss4 > cnt) break;
		}
	}

	cnt2 = cnt;
	int to_read = cnt;
	if (len4 != 0) {
		cnt2 = len4;
		to_read = len4;
	}

	if (cnt2 > 0) {
		if (poss3 + to_read > max_buffer_size) {
			int first = max_buffer_size - poss3;
			memcpy(bw, bufkpi3 + poss3, first);
			memcpy(bw + first, bufkpi3, to_read - first);
			poss3 = (poss3 + to_read) % max_buffer_size;
		}
		else {
			memcpy(bw, bufkpi3 + poss3, to_read);
			poss3 += to_read;
		}
		poss4 -= to_read;
	}


	if ((UINT)wl < (UINT)0x7fff0000) {
		if (cc1 == 1)	cc.Write(bw, cnt2);
		wl += cnt2;
	}


	return cnt;
}


int playwavmp3(BYTE* bw, int old, int l1, int l2)
{
	playb += (l1 + l2);
	//データ読み込み
	int rrr = 0, rrr2 = 0;
	rrr = readmp3(bw + old, l1);
	if (l1 != rrr) {
		if (savedata.saveloop == 0 && endf == 1) {
			l1 = rrr;
			if (savedata.saverenzoku == 0) {
				fade1 = 1;
			}
			else	endflg = 1;

		}
		else {
			loopcnt++;
			playb = loop1;
			mp3_.seek(10, wavch); poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			readmp3(bw + old + rrr, l1 - rrr);
		}
	}
	if (l2) {
		rrr2 = readmp3(bw, l2);
		if (l2 != rrr2) {
			if (savedata.saveloop == 0 && endf == 1) {
				l2 = rrr2;
				if (savedata.saverenzoku == 0) {
					fade1 = 1;
				}
				else endflg = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				mp3_.seek(10, wavch); poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				readmp3(bw + rrr2, (int)l2 - rrr2);
			}
		}
	}
	return l1 + l2;
}

int readmp3(BYTE* bw, int cnt)
{
	int r = cnt, rr = cnt;
	int cnt2;
	if (rr == 0)return 0;
	int len3 = 0, len4 = 0;
	int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
	if (poss4 <= cnt) {
		while (true) {
			if (savedata.mp3orig)
				r = mp3_.Render2(bufkpi, rr, kbps);
			else
				r = mp3_.Render(bufkpi, rr);

			if (r <= 0) {
				if (muon != 0) {
					if (savedata.saverenzoku == 0) {
						ZeroMemory(bufkpi, rr);
						muon--;
					}
					else {
						endflg = 1;
					}
					break;
				}
			}
			int len2 = readtempo(bufkpi, r);

			if (len2 > 0) {
				// 書き込み
				if (poss2 + len2 > max_buffer_size) {
					int first = max_buffer_size - poss2;
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
					memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
					poss2 = (poss2 + len2) % max_buffer_size;
				}
				else {
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
					poss2 += len2;
				}
				poss4 += len2;
				if (rr > r) return 1;
				if (poss4 > cnt) break;
			}
		}
	}

	cnt2 = cnt;

	if (cnt2 > 0) {
		int to_read = cnt;
		if (poss3 + to_read > max_buffer_size) {
			int first = max_buffer_size - poss3;
			memcpy(bw, bufkpi3 + poss3, first);
			memcpy(bw + first, bufkpi3, to_read - first);
			poss3 = (poss3 + to_read) % max_buffer_size;
		}
		else {
			memcpy(bw, bufkpi3 + poss3, to_read);
			poss3 += to_read;
		}
		poss4 -= to_read;
	}



	Int24* b24c;
	b24c = (Int24*)bw;
	short* b, c;
	b = (short*)bw;
	fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
	if (wavsam == 24) {
		for (int i = 0; i < cnt / 3; i++) {
			int c4 = b24c[i];
			c4 = (int)((float)c4 * ((float)savedata.kakuVal / 100.0f));
			b24c[i] = c4;
			c4 = b24c[i];
			if (savedata.mp3 == 2)	c4 = (int)((float)c4 * 2.0f);
			else if (savedata.mp3 == 4) c4 = (int)((float)c4 * 3.0f);
			else if (savedata.mp3 == 8) c4 = (int)((float)c4 * 4.0f);
			else if (savedata.mp3 == 16) c4 = (int)((float)c4 * 5.0f);
			if (c4 > 8388607)c4 = 8388607;
			if (c4 < -8388608)c4 = -8388608;
			b24c[i] = c4;
			{
				float c4;
				int c5;
				c5 = b24c[i]; c4 = (float)c5;
				c4 = c4 * fade * fade; c5 = (int)c4;
				b24c[i] = c5;
			}
		}
	}
	else {
		for (int i = 0; i < cnt / 2; i++) {
			int c = (int)b[i];
			c = (int)((float)c * ((float)savedata.kakuVal / 100.0f));
			b[i] = (short)c;
			c = (int)b[i];
			if (savedata.mp3 == 2)	c = (int)((float)b[i] * 1.5f);
			else if (savedata.mp3 == 3) c = (int)((float)b[i] * 2.0f);
			else if (savedata.mp3 == 4) c = (int)((float)b[i] * 2.5f);
			else if (savedata.mp3 == 5) c = (int)((float)b[i] * 3.0f);
			if (c >= 32768)c = 32767;
			if (c <= -32767)c = -32766;
			b[i] = (short)c;
			c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; 
		}
	}

	if ((UINT)wl < (UINT)0x7fff0000) {
		if (cc1 == 1)	cc.Write(bw, cnt2);
		wl += cnt2;
	}

	lenl += cnt;
	//	playb+=cnt;
	return cnt;
}
void playwavds2(BYTE* bw, int old, int l1, int l2)
{
	//	return;
	//	playb+=(l1+l2)/4;
	//データ読み込み
	if (l1 == 0)return;
	int rrr = mcopy((char*)bw + old, l1);
	if (l1 != rrr) {
		if (savedata.saveloop == 0 && endf == 1) {
			l1 = rrr; fade1 = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			ov_pcm_seek(&vf, (ogg_int64_t)loop1); poss = 0; poss2 = poss3 = poss4 = poss5 = poss6 = 0;
			poss5 = loop1;
			if (g_rubberBandStretcher) {
				delete g_rubberBandStretcher;
				g_rubberBandStretcher = NULL;
			}
			mcopy((char*)bw + old + rrr, (int)l1 - rrr);
		}
	}
	if (l2) {
		rrr = mcopy((char*)bw, l2);
		if (l2 != rrr) {
			if (savedata.saveloop == 0 && endf == 1) {
				l2 = rrr; fade1 = 1;
			}
			else {
				loopcnt++;
				playb = loop1;
				ov_pcm_seek(&vf, (ogg_int64_t)loop1); poss = 0; poss2 = poss3 = poss4 = poss5 = poss6 = 0;
				poss5 = loop1;
				if (g_rubberBandStretcher) {
					delete g_rubberBandStretcher;
					g_rubberBandStretcher = NULL;
				}
				mcopy((char*)bw + rrr, (int)l2 - rrr);
			}
		}
	}
	return;
}

void playwavds(BYTE* bw)
{
	//データ読み込み
	loc++;
	if (loc == OUTPUT_BUFFER_NUM) loc = 0;
	lo++;
	if (lo == OUTPUT_BUFFER_NUM) lo = 0;
	DWORD dwDataLen = OUTPUT_BUFFER_SIZE;
	int rrr = mcopy((char*)buf[lo], dwDataLen);
	if ((int)dwDataLen != rrr)
	{
		if (savedata.saveloop == 0 && endf == 1)
		{
			dwDataLen = rrr;
			if (savedata.saverenzoku == 0)
				fade1 = 1;
			else
				endflg = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			ov_pcm_seek(&vf, (ogg_int64_t)loop1); poss = 0;
			mcopy((char*)buf[lo] + rrr, (int)dwDataLen - rrr);
		}
	}
	memcpy(bw, buf[lo], dwDataLen);
}

void playwav()
{
	//データ読み込み
	lo++;
	if (lo == OUTPUT_BUFFER_NUM) lo = 0;
	DWORD dwDataLen = OUTPUT_BUFFER_SIZE;
	int rrr = mcopy((char*)buf[lo], dwDataLen);
	if ((int)dwDataLen != rrr)
	{
		if (endf == 1)
		{
			dwDataLen = rrr;
			stf = 1;
		}
		else {
			loopcnt++;
			playb = loop1;
			ov_pcm_seek(&vf, (ogg_int64_t)loop1); poss = 0;
			mcopy((char*)buf[lo] + rrr, (int)dwDataLen - rrr);
		}
	}

	memcpy(g_OutputBuffer[lo]->lpData, buf[lo], dwDataLen);
}

LRESULT COggDlg::dp1(WPARAM a, LPARAM b) {
	dp(filen);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//複数起動時の方から飛んでいるデータ
BOOL COggDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	CString filen_;
	TCHAR* aa = (TCHAR*)pCopyDataStruct->lpData;
	filen_ = aa;
	if (filen_ == "*1") OnRestart();
	else if (filen_ == "*2") OnPause();
	else if (filen_ == "*3") stop();
	else if (filen_ == "*4") OnPlayList();
	else if (filen_ == "*5") OnButton21();
	else if (filen_ == "*6") OnButton9_Folder();
	else filen = filen_;
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void COggDlg::dp(CString a)
{
	if (a.Left(1) == "*") {
		if (a == "*1") OnRestart();
		else if (a == "*2") OnPause();
		else if (a == "*3") stop();
		else if (a == "*4") OnPlayList();
		else if (a == "*5") OnButton21();
		else if (a == "*6") OnButton9_Folder();
		return;
	}
	filen = a;
	if (filen.Left(1) == "\"") filen = filen.Right(filen.GetLength() - 1);
	if (filen.Right(1) == "\"") filen = filen.Left(filen.GetLength() - 1);
	ti = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
	stop1();
	if (filen.Right(5).MakeLower() == ".opus") {
		fnn = ti;
		mode = -6; modesub = -6;
		playb = 0;
		play();
	}
	else if (filen.Right(4).MakeLower() == ".ogg" || filen.Right(4) == ".OGG" || filen.Right(6).MakeLower() == ".qull3") {
		fnn = ti;
		mode = -1; modesub = -1;
		play();
	}
	else if (filen.Right(5).MakeLower() == ".flac" || filen.Right(5) == ".FLAC" || filen.Right(7).MakeLower() == L".qull3h") {
		fnn = ti;
		mode = -8; modesub = -8;
		play();
	}
	else if ((filen.Right(4).MakeLower() == ".dsf" || filen.Right(5) == ".DSF" || filen.Right(4).MakeLower() == ".dff" || filen.Right(4) == ".DFF" || filen.Right(4).MakeLower() == ".wsd" || filen.Right(4) == ".WSD")) {
		fnn = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		mode = -7; modesub = -7;
		play();
	}
	else if (filen.Right(4).MakeLower() == ".m4a" || filen.Right(4) == ".M4A" || filen.Right(4).MakeLower() == ".aac" || filen.Right(4) == ".AAC") {
		fnn = ti;
		mode = -9; modesub = -9;
		play();
	}
	else if ((filen.Right(4).MakeLower() == ".mp3" || filen.Right(4) == ".MP3" || filen.Right(4).MakeLower() == ".mp2" || filen.Right(4) == ".MP2" ||
		filen.Right(4).MakeLower() == ".mp1" || filen.Right(4) == ".MP1" || filen.Right(4).MakeLower() == ".rmp" || filen.Right(4) == ".RMP")) {
		fnn = ti;
		mode = -10; modesub = -10;
		play();
	}
	else {//DirectShow
		stflg = FALSE;
		CFile ff;
		CString ss11 = filen; ss11.MakeLower();
		if (ss11.Right(3) == "m4a") {
			if (ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
				mp3file = filen;
				ZeroMemory(bufimage, sizeof(bufimage));
				int i;
				ff.Read(bufimage, sizeof(bufimage));
				for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61 // 63 6f 76 72 xx xx xx xx 64 61 74 61
					if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61) {
						break;
					}
				}
				m_mp3jake.EnableWindow(FALSE);
				if (i != 0x300000) {
					m_mp3jake.EnableWindow(TRUE);
				}
			}ff.Close();
		}
		playlistdata p;
		if (mode == 21) {
			play();
			return;
		}
		if (pl && plw) {
			p.sub = 0;
			CString ss, s;
			s = filen;
			ss = s.Left(s.ReverseFind(':') - 1);
			if (ss != "") s = ss;
			kpi[0] = 0;
			pl->plugs(s, &p, kpi);
			if (p.sub == -3) {//kb medua player
				//				hDLLk = LoadLibrary(kpi);
				//				pFunck = (pfnGetKMPModule)::GetProcAddress(hDLLk, "kmp_GetTestModule");
				modesub = -3;
				play();
				return;
			}
		}
		fnn = ti;
		mode = -2; modesub = -2;
		pMainFrame1 = new CDouga;
		pMainFrame1->Create(GetSafeHwnd());
		pMainFrame1->ShowWindow(SW_HIDE);
		pMainFrame1->play(0);
		CFile f123;
		int flggg = 0;
		if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
			f123.Close();
			if (IDYES == MessageBox(_T("途中再生データが存在します。\n前回中断した部分から再生しますか？\nはい = 途中から再生\nいいえ = はじめから再生"), _T("再生確認"), MB_YESNO)) {
				flggg = 1;
			}
			else {
				CFile::Remove(filen + _T(".save"));
			}
		}
		if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE && flggg == 1) {
			f123.Close();
			if (pGraphBuilder)pMainFrame1->plays2();
			if (pMediaControl) { for (int y = 0; y < 45; y++) { Sleep(10); DoEvent(); }pMediaControl->Run(); }
			if (mode == -10) {
				if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
					f123.Read(&playb, sizeof(__int64));
					if (savedata.mp3orig) {
						mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch);
					}
					else {
						mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch);
					}
					f123.Close();
				}
			}
			if (mode == -2) {
				if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
					f123.Read(&aa1_, sizeof(double));
					pMainFrame1->seek((LONGLONG)(((float)((float)aa1_ * 100.0f * 100000.0f))));
					f123.Close();
				}
			}
		}
		else {
			if (pGraphBuilder)pMainFrame1->plays2();
			if (pMediaControl) { for (int y = 0; y < 45; y++) { Sleep(10); DoEvent(); }pMediaControl->Run(); }
			if (pMainFrame1) { pMainFrame1->seek(0); }
		}
		//		if(pGraphBuilder)pMainFrame1->plays2();
		//		if(pMediaControl)pMediaControl->Run();
		int a = 0; aa2 = 0;
		REFTIME aa = 0;
		aa2 = 0;
		ps = 0; m_ps.SetWindowText(_T("一時停止"));
		if (pMediaPosition)pMediaPosition->get_StopTime(&aa);
		aa1 = oggsize2 = aa;
		m_time.SetRange(0, (int)((REFTIME)aa * 100.0), TRUE);
		m_time.SetSelection(0, (int)((REFTIME)aa * 100.0) - 1);
		m_time.Invalidate();
		if (pl && plw) {
			int plc;
			plc = pl->Add(fnn, mode, 0, 0, _T(""), _T(""), filen, 0, (int)aa, 1);
			if (plc == -1) {
				int i = pl->m_lc.GetItemCount() - 1;
				plcnt = i;
				pl->SIcon(i);
			}
			else {
				plcnt = plc;
				pl->SIcon(plc);
			}
		}

		plf = 1;
	}

}

void COggDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if (pl && plw) {
		pl->OnDropFiles(hDropInfo);
		return;
	}

	TCHAR filen_c[1024];
	UINT cnt = DragQueryFile(hDropInfo, (UINT)-1, filen_c, sizeof(filen_c));
	if (cnt != 1)
	{
		MessageBox(_T("ファイルは1つだけドロップしてください。\nプレイリストが開いている時は複数でもokです。"), _T("ogg/wav簡易プレイヤ"), MB_ICONEXCLAMATION);
		CDialog::OnDropFiles(hDropInfo);
		return;
	}
	DragQueryFile(hDropInfo, (UINT)0, filen_c, sizeof(filen_c));
	CString ff;
	ff = filen;
	filen = (CString)filen_c;
	CFile f;
	if (f.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL) == FALSE) {
		filen = ff;
		MessageBox(_T("ほかのプログラムで開かれているためファイルが開けません"), _T("ogg/wav簡易プレイヤ"), MB_ICONEXCLAMATION);
		CDialog::OnDropFiles(hDropInfo);
		return;
	}
	f.Close();
	dp(filen);
	CDialog::OnDropFiles(hDropInfo);
}

BOOL thn = TRUE;
BOOL thn1 = FALSE;

BOOL CALLBACK pp(HWND hwnd, LPARAM p);
BOOL CALLBACK pp(HWND hwnd, LPARAM p)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == (LPARAM)p) {
		::PostMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return FALSE;
	}
	return TRUE;
}

CString filenback;
void COggDlg::stop()
{
	stflg = TRUE;
	KillTimer(1250);
	gamenkill();
	videoonly = FALSE;
	fade1 = 1;
	if (savedata.savecheck == 1 && (mode == -10 || mode == -2) && filenback == filen) {
		try {
			int flg = 0;
			if (mode == -10) {
				if (oggsize <= playb && oggsize != 0) {
					try {
						CFile::Remove(filen + _T(".save"));
					}
					catch (...) {
					}
					flg = 1;
				}
				if (playb == 0)
					flg = 1;
			}
			if (mode == -2) {
				if (oggsize2 <= aa1_ && oggsize2 != 0.0) {
					try {
						CFile::Remove(filen + _T(".save"));
					}
					catch (...) {
					}
					flg = 1;
				}
				if (aa1_ == 0.0) {
					flg = 1;
				}
			}
			if (flg == 0) {
				if ((savedata.savecheck_mp3 == 1 && mode == -10) || (savedata.savecheck_dshow == 1 && mode == -2)) {
					CFile f;
					if (f.Open(filen + _T(".save"), CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
						if (mode == -10)
							f.Write(&playb, sizeof(__int64));
						if (mode == -2)
							f.Write(&aa1_, sizeof(double));
						f.Close();
					}
				}
			}
			else {
			}
		}
		catch (...) {
		}
	}
	filenback = filen;
	playb = 0;
	if (ptl)ptl->SetProgressValue(m_hWnd, (LONGLONG)0, (LONGLONG)1);
	if (ptl)ptl->SetProgressState(m_hWnd, TBPF_NOPROGRESS);
	if ((ogg || adbuf2 || mod || wav) && mode != -2)
	{
		thn1 = TRUE;
		if (m_dsb)m_dsb->SetVolume(DSBVOLUME_MIN);
		if (ps == 1) {
			OnPause();
		}
		m_ps.SetWindowText(_T("一時停止"));
		ps = 0;
		if (m_dsb)m_dsb->Stop();
		if (pAudioClient) pAudioClient->Stop();
		if (m_dou.GetCheck() == 1)
			if (cc1 == 1) {
				cc.SeekToBegin();
				WAVEFILEHEADER wh1;
				cc.Read(&wh1, sizeof(wh1));
				wh1.ckSizeRIFF = wl + 44 - 8;
				wh1.ckSizeData = wl;
				cc.SeekToBegin();
				cc.Write(&wh1, sizeof(wh1));
				cc.Close();
				cc1 = 0;
			}
		CCriticalLock _ccl(&cs);
		stf = 1;
		_ccl.Leave();
		timer.SetEvent();
		if (thn == FALSE) {
			for (int i = 0; i < 100; i++) {
				if (thn == TRUE) break;
				DoEvent();
				Sleep(10);
			}
		}


		Closeds();
		//		FreeOutputBuffer();
		plf = 0;

		if (ogg)ReleaseOggVorbis(&ogg);

		ogg = NULL;

		//		for(int l=0;l<20;l++){Sleep(50);DoEvent();}
		if (adbuf2)free(adbuf2);//delete [] adbuf2;
		adbuf2 = NULL;
		if (mode == -10) mp3_.Close();
		if (mode == -8) flac_.Close(og->kmp);
		if (mode == -9) m4a_.Close(og->kmp);
		if (mode == -7) dsd_.kpiClose(og->kmp);
		kmp = NULL;
		if (mod) {
			if (mod->Close) mod->Close(kmp1);
			if (mod->Deinit) mod->Deinit();
			FreeLibrary(hDLLk);
			mod = NULL; kmp1 = NULL; hDLLk = NULL;
		}

		DoEvent();
		thend = 1;
		fadeadd = 0; fade = 1.0;
	}
	if (wav) free(wav);
	wav = NULL;
	playf = 0;
	mode = modesub;
	stflg = FALSE;
	SetTimer(4923, 30, NULL);
	m_lrc.SetWindowText(L"");
	m_lrc2.SetWindowText(L"歌詞(.lrc)が表示されます");
	m_lrc3.SetWindowText(L"");
}

void COggDlg::stop1()
{
	//	for(int i=0;i<10;i++){DoEvent();Sleep(10);}
	gamenkill();
	videoonly = FALSE;
	if (ptl)ptl->SetProgressValue(m_hWnd, (LONGLONG)0, (LONGLONG)1);
	if (ptl)ptl->SetProgressState(m_hWnd, TBPF_NOPROGRESS);
	if (ogg != NULL || adbuf2 != NULL || wav)
	{
		thn1 = TRUE;
		timer.SetEvent();
		if (m_dsb)m_dsb->SetVolume(DSBVOLUME_MIN);
		if (ps == 1) {
			OnPause();
		}
		if (m_dou.GetCheck() == 1)
			if (cc1 == 1) {
				cc.SeekToBegin();
				WAVEFILEHEADER wh1;
				cc.Read(&wh1, sizeof(wh1));
				wh1.ckSizeRIFF = wl + 44 - 8;
				wh1.ckSizeData = wl;
				cc.SeekToBegin();
				cc.Write(&wh1, sizeof(wh1));
				cc.Close();
				cc1 = 0;
			}
		CCriticalLock _ccl(&cs);
		stf = 1;
		_ccl.Leave();
		if (thn == FALSE)
			for (;;) {
				if (thn == TRUE) break;
				DoEvent();
			}
		Closeds();
		//		FreeOutputBuffer();
		plf = 0;
		if (ogg)ReleaseOggVorbis(&ogg);
		ogg = NULL;

		if (thend == FALSE) {
			thend1 = TRUE;
			for (int kk = 0;kk<50;kk++) {
				if (thend == 1) break;
				DoEvent();
			}
		}
		Sleep(50);
		playb = 0;
		if (adbuf2)free(adbuf2);//delete [] adbuf2;
		adbuf2 = NULL;
		if (mode == -10) mp3_.Close();
		if (mode == -8) flac_.Close(og->kmp);
		if (mode == -9) m4a_.Close(og->kmp);
		if (mode == -7) dsd_.kpiClose(og->kmp);
		kmp = NULL;
		if (mod) {
			if (mod->Close) mod->Close(kmp1);
			if (mod->Deinit) mod->Deinit();
			FreeLibrary(hDLLk);
			mod = NULL; kmp1 = NULL; hDLLk = NULL;
		}
		DoEvent();
		thend = 1;
		fadeadd = 0; fade = 1.0;
	}
	if (wav) free(wav);
	wav = NULL;
	playf = 0;
	mode = modesub;
	m_lrc.SetWindowText(L"");
	m_lrc2.SetWindowText(L"歌詞(.lrc)が表示されます");
	m_lrc3.SetWindowText(L"");
}


BOOL COggDlg::DestroyWindow()
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	//	ReleaseOggVorbis(&ogg);
	stop();
	waveOutReset(hwo);
	waveOutClose(hwo);
	if (deve) {
		audio->Release();
		dev->Release();
		deve->Release();
	}
	if (pl && plw) {
		killw1 = 0;
		pl->DestroyWindow();
		for (; killw1 == 0;)
			DoEvent();
		pl = NULL;
		savedata.pl = 1;
	}
	else savedata.pl = 0;
	if (mi) {
		killw1 = 0;
		mi->DestroyWindow();
		for (; killw1 == 0;)
			DoEvent();
		mi = NULL;
	}
	if (m_pDlgColor)delete m_pDlgColor;
	if (ptl) ptl->Release();
	if (pcdl) pcdl->Release();
	CoUninitialize();
	//	timeKillEvent(uTimerId);
	KillTimer(5656);
	KillTimer(5657);
	KillTimer(1233);
	timeEndPeriod(1);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY0);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY1);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY2);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY3);
	ReleaseDXSound();
	CString s;
	m_kaisuu.GetWindowText(s);
	savedata.kaisuu = _tstoi(s);
	savedata.gameflg[0] = m_ys6.GetCheck();
	savedata.gameflg[1] = m_ysf.GetCheck();
	savedata.gameflg[2] = m_ed6fc.GetCheck();
	savedata.gameflg[3] = m_ed6sc.GetCheck();
	savedata.gameflg[3] = m_ed6sc.GetCheck();
	savedata.gameflg2 = m_yso.GetCheck();
	savedata.gameflg3 = m_ed6tc.GetCheck();
	savedata.gameflg4 = m_zweiii.GetCheck();
	savedata.gameflg5 = m_ysc1.GetCheck();
	savedata.gameflg6 = m_ysc2.GetCheck();
	savedata.gameflg7 = m_xa.GetCheck();
	savedata.gameflg8 = m_ys121.GetCheck();
	savedata.gameflg9 = m_ys122.GetCheck();
	savedata.gameflg10 = m_sor.GetCheck();
	savedata.gameflg11 = m_zwei.GetCheck();
	savedata.gameflg12 = m_gurumin.GetCheck();
	savedata.gameflg13 = m_dino.GetCheck();
	savedata.gameflg14 = m_br4.GetCheck();
	savedata.gameflg15 = m_ed3.GetCheck();
	savedata.gameflg16 = m_ed4.GetCheck();
	savedata.gameflg17 = m_ed5.GetCheck();
	savedata.supe = m_supe.GetCheck();
	savedata.supe2 = m_st.GetCheck();
	RECT r;
	ShowWindow(SW_SHOWNORMAL);
	GetWindowRect(&r);
	savedata.xx = r.left;
	savedata.yy = r.top;
	DeleteObject(hFont);
	bmp.DeleteObject();
	dc.DeleteDC();
	bmpsub.DeleteObject();
	dcsub.DeleteDC();
	return CDialog::DestroyWindow();
}
//oggから実際にデータを獲得する
int mcopy(char* a, int len)
{
	if (len == 0) return 0;
	int ch = (wavch == 2 ? 1 : 2);
	//poss = 0;
	int ret = 0, lenl = len / (wavch * 2),cnt2;
	//ret=ov_pcm_seek(&vf,playb+poss);

	int len3 = 0, len4 = 0;
	int max_buffer_size = OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3;
	if (poss4 <= len) {
		while(true) {
			ret = 0;
			if ((int)playb > (data_size + 20000) / (wavch * 2) && endf == 1) {
				playb += lenl;
				if (muon != 0) {
					muon--;
					ZeroMemory(a, len);
				}
				if (muon == MUON) {
					ZeroMemory(a, len);
					muon--;
					rrr = 0;
				}
				if (muon == 0) return 0;
				return len;
			}

			int read = len / 4096;
			int read2 = len % 4096;
			int i = 0;
			for (;;) {
				ret = ov_read(&vf, (char*)(bufwav + poss * 4), 4096, 0, 2, 1, &current_section) / 4;
				poss += ret;
				if (ret == 0) break;
				if (lenl <= poss)	break;
			}

			int len2 = readtempo(bufwav, lenl * 4);
			playb += len2 / 4;

			if (len2 > 0) {
				// 書き込み
				if (poss2 + len2 > max_buffer_size) {
					int first = max_buffer_size - poss2;
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), first);
					memcpy(bufkpi3, outputRawBytesData.data() + first, len2 - first);
					poss2 = (poss2 + len2) % max_buffer_size;
				}
				else {
					memcpy(bufkpi3 + poss2, outputRawBytesData.data(), len2);
					poss2 += len2;
				}
				poss4 += len2;
			}
			if (lenl <= poss) {
				poss -= lenl;
				if (poss != 0)	memcpy(bufwav, bufwav + lenl * 4, poss * 4);
			}
			if (len4 != 0) break;
			if (poss4 > len) break;
		}
	}

	int cnt0 = len / 4;
	if (loop1 + loop2 < poss5 + cnt0 && endf == 0) {
		cnt0 = (loop1 + loop2) - poss5;
	}

	poss5 += cnt0 * (tempo / 100.0f);
	cnt0 *= 4;


	cnt2 = cnt0;
	int to_read = cnt0;

	if (cnt2 > 0) {
		if (poss3 + to_read > max_buffer_size) {
			int first = max_buffer_size - poss3;
			memcpy(a, bufkpi3 + poss3, first);
			memcpy(a + first, bufkpi3, to_read - first);
			poss3 = (poss3 + to_read) % max_buffer_size;
		}
		else {
			memcpy(a, bufkpi3 + poss3, to_read);
			poss3 += to_read;
		}
		poss4 -= to_read;
	}

	//fade計算
	short* b, c;
	b = (short*)a;
	CString sss;
	sss = filen.Right(filen.GetLength() - filen.ReverseFind('.') - 1);
	sss.MakeLower();
	fade += fadeadd; if (fade < 0.0001) { fade = 0.0; fadeadd = 0; }
	//fadeを三乗して計算密度を変更
	for (int i = 0; i < (cnt0 * wavch) / 4; i++) { c = b[i]; c = (short)(((float)c) * fade * fade); b[i] = c; }

	if ((UINT)wl < (UINT)0x7fff0000) {
		//				if (cc1 == 1)	cc.Write(bw, cnt);
		if (cc1 == 1)	cc.Write(a, cnt0);
		//				if (cc1 == 1)	cc.Write(bufkpi, r);
		wl += cnt0;
	}

	return cnt0;
}

/*
int li=0;
void CALLBACK TimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
timingf++;
if(timingf==16&&timerf1==0){
timerf1++;
timingf=0;
if(li==0){
li=1;
og->timerp();
li=0;
}
}
if(timingf==17&&timerf1>0){
timingf=0;
timerf1++;
if(li==0){
li=1;
og->timerp();
li=0;
}
}
if(timerf1==3)timerf1=0;

}
*/

CString wavb(int d);
CString wavb(int d) {
	CString wavbit1;
	if (d == (int)((int)d / 1000) * 1000) {
		wavbit1.Format(L"%dk", d / 1000);
	}
	else if (d == (int)((int)d / 100) * 100) {
		wavbit1.Format(L"%3.1fk", (float)d / 1000);
	}
	else {
		wavbit1.Format(L"%d", d);
	}
	return wavbit1;
}

extern IBasicAudio* pBasicAudio;
extern IBaseFilter* prend;
extern double rate;
extern int rateflg;
extern RECT rcm;
extern long height, width;
DWORD videocnt = 0, videocnt2 = 0, videocnt3;
void COggDlg::timerp()
{
	if (playy == 0)return;
	ms2++;
	CString s, ss, sss;
	if (voldsf) {
		voldsf = 0;
		m_dsval.SetPos(savedata.dsvol);
		m_dsval.ShowWindow(SW_SHOWNA);
	}

	if (mode == -2) loop1 = loop2 = loopcnt = wl = 0;
	//時間
	int t1, ta, tb, tc, ta1, tb1, tc1, tag = 0, tbg = 0, tcg = 0, ttt;
	tt++;
	//	if(tt==4)
	//	{
	//		tt=0;
	double t3;
	if ((mode == -2 || (mode != -2 && videoonly == TRUE))) {
		t3 = (double)oggsize2;
		tt = (int)(t3 * 100.0);
		t1 = tt / 100;
		ta = t1 / 60;
		tb = t1 % 60;
		tc = tt % 100;
		if (videocnt > 7) {
			REFTIME aa;
			aa = 0;
			if (pMediaPosition)pMediaPosition->get_CurrentPosition(&aa);
			if (pMediaPosition && (oggsize2 < aa) && plf == 1) {
				aa = 0; plf = 0;
				if (pMainFrame1 != NULL && (mode == -2 || (mode > 0 && videoonly == TRUE))) {
					pMainFrame1->pause(0);
				}
			}
			aa1_ = aa;
			videocnt = 0;
		}
		t3 = (double)aa1_;
		tt = (int)(t3 * 100.0);
		t1 = tt / 100;
		ta1 = t1 / 60;
		tb1 = t1 % 60;
		tc1 = tt % 100;
		ttt = tt;
	}
	else {
		double wavv[] = { 0,1.0,2.0,3.0 / 0.75,4.0 / 0.75,5.0 / 0.75,6.0 / 0.75 };//(double)(wavbit2/wavv[wavch])
		double wavv2[] = { 0,2.0,1.0,2.0 / 3.0,2.0 / 4.0,2.0 / 5.0,2.0 / 6.0 };//(double)(wavbit2/wavv[wavch])
		t3 = (double)oggsize / (double)(wavbit * 2.0 * wavv[wavch]) / (double)(wavsam / 16.0f);
		if (mode == -10) t3 *= (wavsam / 16.0f) * 4.0;
		if ((mode == -9) && wavch > 2) t3 *= wavch / 2.0;
		tt = (int)(t3 * 100.0);
		if (tt < 0) tt = 0;
		t1 = tt / 100;
		ta = t1 / 60;
		tb = t1 % 60;
		tc = tt % 100;
		t3 = (double)playb / (double)(wavbit / wavv2[wavch]);// / (double)(wavsam / 16.0f);
		if (mode == -10) t3 /= (wavsam / 16.0f) * 4.0;
		if ((mode == -9) && wavch > 2) t3 *= wavch / 2.0;
		if (m_dsb && !(mode == -8 || mode >= 1)) {
			//t3 -= 1.0;
		}
		if (t3 < 0.0) t3 = 0.0;
		tt = (int)(t3 * 100.0);
		if (tt < 0) tt = 0;
		t1 = tt / 100;
		ta1 = t1 / 60;
		tb1 = t1 % 60;
		tc1 = tt % 100;
		ttt = tt;
		t3 = (double)wl / (double)(wavbit * 2 * wavv[wavch]) / (double)(wavsam / 16.0f);
		tt = (int)(t3 * 100.0);
		t1 = tt / 100;
		tag = t1 / 60;
		tbg = t1 % 60;
		tcg = tt % 100;
	}
	videocnt++;

	t3 = (double)loop1 / (double)(wavbit);
	tt = (int)(t3 * 100.0);
	t1 = tt / 100;
	int tal1 = t1 / 60;
	int tbl1 = t1 % 60;
	int tcl1 = tt % 100;
	t3 = (double)(loop2 + loop1) / (double)(wavbit);
	tt = (int)(t3 * 100.0);
	t1 = tt / 100;
	int tal2 = t1 / 60;
	int tbl2 = t1 % 60;
	int tcl2 = tt % 100;

	dc.FillSolidRect(0, 0, 3000, 2000, RGB(0, 0, 0));
	//		dcsub.FillSolidRect(0,0,3000,30,RGB(1,1,1));

	if (jx != -1) {
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;

		// Initialize GDI+.
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		Gdiplus::Bitmap clImage(img, NULL);
		Gdiplus::Bitmap* pImage = NULL;
		pImage = Gdiplus::Bitmap::FromHBITMAP(img, NULL);

		// GDI+による描画
		Gdiplus::Graphics graphics(dc);
		graphics.DrawImage(&clImage, 10000, 10000);

		// HBITMAPによるBitBlt描画
		Gdiplus::Color bkcolor(0x0, 0x0, 0xff);
		HBITMAP hBmp;
		HBITMAP hOld;
		HDC hMem;

		clImage.GetHBITMAP(bkcolor, &hBmp);
		hMem = CreateCompatibleDC(dc);
		hOld = (HBITMAP)SelectObject(hMem, hBmp);
		CRect r;
		GetClientRect(&r);
		//			r.right = r.bottom * xy;
		SetStretchBltMode(dc.m_hDC, HALFTONE); //高画質モード
		SetBrushOrgEx(dc.m_hDC, 0, 0, NULL); //ブラシのずれを防止
		if ((r.right - 100) * (jxy) > jx) {
			//			StretchBlt(dc, MDC - 60, 0, (60), 60 / (jxy), hMem, 0, 0, jx, jy, SRCPAINT); //伸縮
		}
		else {
			//			StretchBlt(dc, MDC - 60, 0, (60) * (jxy), 60, hMem, 0, 0, jx, jy, SRCPAINT); //伸縮
		}
		//	BitBlt(dcc, 0, 0, clImage.GetWidth(), clImage.GetHeight(), hMem, 0, 0, SRCCOPY);
		SelectObject(hMem, hOld);

		DeleteDC(hMem);

		// Finalize GDI+
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

	for (int lp = 0; lp < lrcnum - 1; lp++) {
		if (lrctm[lp] <= ttt && lrctm[lp + 1] > ttt) {
			CString s;
			m_lrc2.GetWindowText(s);
			if (lrc[lp] == lrc_backup) continue;
			if (lp != 0) m_lrc.SetWindowText(lrc[lp - 1]);
			m_lrc2.SetWindowText(lrc[lp]);
			m_lrc3.SetWindowText(lrc[lp + 1]);
			lrc_backup = lrc[lp];
		}
	}


	if (m_supe.GetCheck() == TRUE && plf == 1 && (wav || ogg)) Speana();
	s = L""; ss = L"";
	s = "name:";
	moji(s, 1, 0, 0xffffff);
	if (fnn != L"")		sss = fnn;
	if (mode == -10 || mode == -9 || mode == -8 || mode == -7) sss = tagfile;
	if (stitle != "" && mode == -1 || mode == 21 || mode == -6)	sss = stitle;
	int si = mojisub(sss, 1, 0, 0xffffff);
	if (si > MDC) {
		ss = sss + _T("》---《");
		if (mode == -10) ss = sss + _T("》---《");
		si = mojisub(ss, 1, 0, 0xffffff);
	}
	//枠はみ出し時スクロール処理
	if (si > MDC) {
		dc.BitBlt(8 * 5 * 4, 0, 88 * 2 * 4 + 1000, (24 * 4) * 4, &dcsub, mcnt, 0, SRCCOPY);
		if (si - mcnt < MDC) {
			mcnt2++;
			mcnt2++;
			mcnt2++;
			mcnt2++;
			dc.BitBlt(MDC - mcnt2 + 8 * 5 * 4, 0, 88 * 2 * 4 + 1000, (24 * 4) * 4, &dcsub, 0, 0, SRCCOPY);
			if (MDC - mcnt2 <= 0) { mcnt2 = 0; mcnt = 0; }
		}
		else mcnt2 = 0;
		mcnt++;
		mcnt++;
		mcnt++;
		mcnt++;
	}
	else {
		dc.BitBlt(8 * 5 * 4, 0, 88 * 2 * 4 + 1000, (24 * 4) * 4, &dcsub, 0, 0, SRCCOPY);
	}

	//mcnt1++;
	if (modesub == 5 || modesub == 7 || modesub == 8 || modesub == 9 || modesub == 10)	s.Format(_T("file:%s"), filen);
	else if (mode == 21)
		s.Format(_T("file:%s"), filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1));
	else			s.Format(_T("file:%s"), filen);
	//		if(fnn.Right(4)=="動画"||fnn.Right(5).Left(4)=="動画")		s.Format("file:動画");
	if (filen.Left(2) == L"★")		s.Format(_T("file:動画"));
	if (mode == -10 || mode == -9 || mode == -8 || mode == -7 || mode == -6) {
		CString g; g = L""; g = filen; g.MakeLower();
		if (g.Right(4) == L".mp3") g = L"(mp3)";
		if (g.Right(4) == L".rmp") g = L"(rmp)";
		if (g.Right(4) == L".mp2") g = L"(mp2)";
		if (g.Right(4) == L".mp1") g = L"(mp1)";
		if (g.Right(4) == L".m4a") g = L"(m4a)";
		if (g.Right(4) == L".aac") g = "L(aac)";
		if (g.Right(5) == L".flac") g = L"(flac)";
		if (g.Right(7).MakeLower() == L".qull3h") g = L"(flac)";
		if (g.Right(5) == L".opus") g = L"(opus)";
		if (g.Right(4) == L".dsf") g = L"(DSD(dsf))";
		if (g.Right(4) == L".dff") g = L"(DSD(dff))";
		if (g.Right(4) == L".wsd") g = L"(DSD(wsd))";
		s.Format(_T("file:音声ファイル%s"), g);
	}
	if (mode == -2 || mode == -3) sss = filen.Right(filen.GetLength() - filen.ReverseFind('.') - 1);
	if (mode == -3) s.Format(_T("file:kpiファイル(%s)"), sss);
	if (mode == -1) s.Format(_T("file:oggファイル"), sss);
	if (mode == -2 && rate == 0.0) s.Format(_T("file:音声ファイル(%s)"), sss);
	if (mode == -2 && rate != 0.0) s.Format(_T("file:動画ファイル(%s)"), sss);
	moji(s, 1, 16, 0xffffff);
	if (tc1 < 50)
		s.Format(_T("time:%2d:%02d.%02d/%2d:%02d.%02d"), ta1, tb1, tc1, ta, tb, tc);
	else
		s.Format(_T("time:%2d:%02d %02d/%2d:%02d.%02d"), ta1, tb1, tc1, ta, tb, tc);
	if (ta > 59) {
		if (tc1 < 50)
			s.Format(_T("time:%2d:%02d.%02d/%2d:%02d:%02d"), ta1, tb1, tc1, ta / 60, (ta % 60), tb);
		else
			s.Format(_T("time:%2d:%02d %02d/%2d:%02d:%02d"), ta1, tb1, tc1, ta / 60, (ta % 60), tb);
	}
	if (ta1 > 59) {
		if (tc < 50)
			s.Format(_T("time:%2d:%02d:%02d/%2d:%02d.%02d"), ta1 / 60, (ta1 % 60), tb1, ta, tb, tc);
		else
			s.Format(_T("time:%2d:%02d:%02d/%2d:%02d.%02d"), ta1 / 60, (ta1 % 60), tb1, ta, tb, tc);
	}
	if (ta > 59 && ta1 > 59) {
		s.Format(_T("time:%2d:%02d:%02d/%2d:%02d:%02d"), ta1 / 60, (ta1 % 60), tb1, ta / 60, (ta % 60), tb);
	}
	moji(s, 1, 32, 0xffffff);

	if (rateflg)
		if (videocnt2 > 30) {
			videocnt2 = 0;
			if (prend && ps == 0) {
				int framerate;
				CComQIPtr< IQualProp, &IID_IQualProp > ptr(prend);
				ptr->get_AvgFrameRate(&framerate);
				rate = ((double)framerate) / 100.0;
			}
		}
	videocnt2++;
	videocnt3++;


	CString wavbit1 = wavb(wavbit);

	if ((mode == -2 || videoonly) && rate != 0.0 && height != 0) {
		s.Format(_T("size:%d x %d"), rcm.right, rcm.bottom);
		moji(s, 1, 48, 0x7fffff);
		s.Format(_T("rate:%3.3ffps"), rate);
		moji(s, 1, 64, 0x7fffff);
	}
	else if ((mode == -2 || videoonly) && rcm.right > 1) {
		s.Format(_T("size:%d x %d"), rcm.right, rcm.bottom);
		moji(s, 1, 48, 0x7fffff);
		s.Format(_T("rate:算出中……"));
		moji(s, 1, 64, 0x7fffff);
	}
	else if (mode == -2 && wavbit != 0) {
		s.Format(_T("sample:%sHz"), wavbit1);
		moji(s, 1, 48, 0x7fffff);
		s.Format(_T("channel:%dch"), wavch);
		if (wavch == 3)s.Format(_T("channel:%s"), _T("2.1ch"));
		if (wavch == 4)s.Format(_T("channel:%s"), _T("3.1ch"));
		if (wavch == 5)s.Format(_T("channel:%s"), _T("4.1ch"));
		if (wavch == 6)s.Format(_T("channel:%s"), _T("5.1ch"));
		if (wavch == 7)s.Format(_T("channel:%s"), _T("6.1ch"));
		if (wavch == 8)s.Format(_T("channel:%s"), _T("7.1ch"));
		moji(s, 1, 64, 0x7fffff);
	}
	else if (mode == -2 && wavbit == 0) {
		s.Format(_T("sample:不明"), wavbit);
		moji(s, 1, 48, 0x7fffff);
		s.Format(_T("channel:不明"), wavch);
		moji(s, 1, 64, 0x7fffff);
	}
	else if (mode == -3) {
		s.Format(_T("data:%sHz %s %dbit"), wavbit1, (wavch == 1) ? _T("mono") : _T("stereo"), wavsam);
		if (wavch == 3)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("3ch"), wavsam);
		if (wavch == 4)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("4ch"), wavsam);
		if (wavch == 5)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("4.1ch"), wavsam);
		if (wavch == 6)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("5.1ch"), wavsam);
		if (wavch == 7)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("6.1ch"), wavsam);
		if (wavch == 8)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("7.1ch"), wavsam);
		moji(s, 1, 48, 0x7fffff);
		sss = kpi;
		s.Format(_T("kpi :%s"), sss.Right(sss.GetLength() - sss.ReverseFind('\\') - 1));
		moji(s, 1, 64, 0x7fffff);
	}
	else if (mode == -8 || mode == -7) {
		s.Format(_T("data:%sHz %s %dbit"), wavbit1, (wavch == 1) ? _T("mono") : _T("stereo"), wavsam);
		if (wavch == 3)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("3ch"), wavsam);
		if (wavch == 4)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("4ch"), wavsam);
		if (wavch == 5)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("4.1ch"), wavsam);
		if (wavch == 6)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("5.1ch"), wavsam);
		if (wavch == 7)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("6.1ch"), wavsam);
		if (wavch == 8)s.Format(_T("data:%sHz %s %dbit"), wavbit1, _T("7.1ch"), wavsam);
		moji(s, 1, 48, 0x7fffff);
		s = "Arti:";
		moji(s, 1, 64, 0x7fffff);
		int si = mojisub(tagname, 1, 0, 0x7fffff);
		if (si > MDC) {
			ss = fnn + _T("》---《");
			if (mode == -8 || mode == -7) ss = tagname + _T("》---《");
			si = mojisub(ss, 1, 0, 0x7fffff);
		}
		//枠はみ出し時スクロール処理
		if (si > MDC) {
			dc.BitBlt(8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, mcnt4, 0, SRCINVERT);
			if (si - mcnt4 < MDC) {
				mcnt3++;
				mcnt3++;
				mcnt3++;
				mcnt3++;
				dc.BitBlt(MDC - mcnt3 + 8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, 0, 0, SRCINVERT);
				if (MDC - mcnt3 <= 0) { mcnt3 = 0; mcnt4 = 0; }
			}
			else mcnt3 = 0;
			mcnt4++;
			mcnt4++;
			mcnt4++;
			mcnt4++;
		}
		else {
			dc.BitBlt(8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, 0, 0, SRCINVERT);
		}
	}
	else if (mode == -10 || mode == -9) {
		if (Vbr & mode == -10)
			s.Format(_T("data:%3dk(VBR) %sHz %dbit"), (kbps == 0) ? mkps : kbps, wavb(si1.dwSamplesPerSec), wavsam);
		else
			if (mode == -9)
				if (((kbps == 0) ? mkps : kbps) == 0)
					s.Format(_T("data:%sHz %dch %dbit (ALAC)"), wavb(si1.dwSamplesPerSec), wavch, wavsam);
				else
					if (Vbr)
						s.Format(_T("data:%3dk(VBR) %sHz %dch %dbit (AAC)"), mkps, wavb(si1.dwSamplesPerSec), wavch, wavsam);
					else
						s.Format(_T("data:%3dk(CBR) %sHz %dch %dbit (AAC)"), mkps, wavb(si1.dwSamplesPerSec), wavch, wavsam);
			else
				s.Format(_T("data:%3dk %sHz %dbit"), (kbps == 0) ? mkps : kbps, wavb(si1.dwSamplesPerSec), wavsam);
		moji(s, 1, 48, 0x7fffff);
		s = "Arti:";
		moji(s, 1, 64, 0x7fffff);
		//			dcsub.FillSolidRect(0,0,3000,30,RGB(1,1,1));
		int si = mojisub(tagname, 1, 0, 0x7fffff);
		if (si > MDC) {
			ss = fnn + _T("》---《");
			if (mode == -10 || mode == -9) ss = tagname + _T("》---《");
			si = mojisub(ss, 1, 0, 0x7fffff);
		}
		//枠はみ出し時スクロール処理
		if (si > MDC) {
			dc.BitBlt(8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, mcnt4, 0, SRCINVERT);
			if (si - mcnt4 < MDC) {
				mcnt3++;
				mcnt3++;
				mcnt3++;
				mcnt3++;
				dc.BitBlt(MDC - mcnt3 + 8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, 0, 0, SRCINVERT);
				if (MDC - mcnt3 <= 0) { mcnt3 = 0; mcnt4 = 0; }
			}
			else mcnt3 = 0;
			mcnt4++;
			mcnt4++;
			mcnt4++;
			mcnt4++;
		}
		else {
			dc.BitBlt(8 * 5 * 4, 0 + 64 * 4, 88 * 2 * 4 + 1000, (16 + 64) * 4, &dcsub, 0, 0, SRCINVERT);
		}
	}
	else {
		s.Format(_T("Loop:%2d:%02d.%02d %2d:%02d.%02d"), tal1, tbl1, tcl1, tal2, tbl2, tcl2);
		moji(s, 1, 48, 0x7fffff);
		if (loop1 < 10000000000)
			s.Format(_T("    :%10d-%6d"), loop1, loop2);
		if (loop1 < 1000000000)
			s.Format(_T("    :%9d-%7d"), loop1, loop2);
		if (loop1 < 100000000)
			s.Format(_T("    :%8d-%8d"), loop1, loop2);
		if (loop1 < 10000000)
			s.Format(_T("    :%7d-%9d"), loop1, loop2);
		moji(s, 1, 64, 0x7fefef);
	}
	if (mode == -10 || mode == -9 || mode == -8 || mode == -7) {
		s = "Albu:";
		moji(s, 1, 80, 0x7fffff);
		//			dcsub.FillSolidRect(0,0,3000,30,RGB(1,1,1));
		int si = mojisub(tagalbum, 1, 0, 0x7fffff);
		if (si > MDC) {
			ss = tagalbum + _T("》---《");
			si = mojisub(ss, 1, 0, 0x7fffff);
		}
		//枠はみ出し時スクロール処理
		if (si > MDC) {
			dc.BitBlt(8 * 5 * 4, 0 + 80 * 4, 88 * 2 * 4 + 1000, (16 + 80) * 4, &dcsub, mcnt6, 0, SRCINVERT);
			if (si - mcnt6 < MDC) {
				mcnt5++;
				mcnt5++;
				mcnt5++;
				mcnt5++;
				dc.BitBlt(MDC - mcnt5 + 8 * 5 * 4, 0 + 80 * 4, 88 * 2 * 4 + 1000, (16 + 80) * 4, &dcsub, 0, 0, SRCINVERT);
				if (MDC - mcnt5 <= 0) { mcnt5 = 0; mcnt6 = 0; }
			}
			else mcnt5 = 0;
			mcnt6++;
			mcnt6++;
			mcnt6++;
			mcnt6++;
		}
		else {
			dc.BitBlt(8 * 5 * 4, 0 + 80 * 4, 88 * 2 * 4 + 1000, (16 + 80) * 4, &dcsub, 0, 0, SRCINVERT);
		}
	}
	else {
		if (tcg < 50)
			s.Format(_T("Loop数:%3d G:%3d:%02d.%02d"), loopcnt, tag, tbg, tcg);
		else
			s.Format(_T("Loop数:%3d G:%3d:%02d %02d"), loopcnt, tag, tbg, tcg);
		moji(s, 1, 80, 0xefefef);
	}
	if (ss != s)
	{
		ss = s;
		//			m_11.SetWindowText(s);
	}

	//	}




	if (pl && plw) {
		if (pl->m_renzoku.GetCheck()) {
			if (plf == 1 && fade == 0.0f && playy == 1) {
				thn = FALSE;
				fade1 = 1;
			}
		}
		else {
			if (plf == 1 && fade == 0.0f && playy == 1) {
				stop1(); fade = 1;
			}
		}
	}
	else {
		if (plf == 1 && fade == 0.0f && playy == 1) {
			stop1(); fade = 1;
		}
	}

	if (pl && plw) {
		if (pl->m_renzoku.GetCheck() == TRUE) {
			CString s; m_kaisuu.GetWindowText(s);
			if (loopcnt >= _tstoi(s)) OnButton5();
		}
	}

	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = (LONG)((101) * hD * 4);
	rect.right = (LONG)((180 + 88 * 2 + 50) * hD * 4);
	if (savedata.ms2 <= ms2) {
		InvalidateRect(&rect, FALSE);
	}
	//音量
	//	if(tt>=4){
	float vol = (float)m_sl.GetPos();
	vol /= 1000.0f;
	if (plf == 1) {
		if (deve == NULL) {
			WORD leftv = (WORD)(0xFFFF * vol);
			WORD rightv = (WORD)(0xFFFF * vol);
			waveOutSetVolume(hwo, MAKELONG(leftv, rightv));
		}
		else {
			audio->SetMasterVolumeLevelScalar(vol / 100.0f, &GUID_NULL);
		}
	}
	if (deve)
		s.Format(_T("%3.1f%%"), vol);
	else
		s.Format(_T("%3.1f%%"), vol * 100);
	m_vol.GetWindowText(ss);
	if (s != ss)
		m_vol.SetWindowText(s);
	//時間表示
	if (pMediaPosition && ((mode == -2 && hsc == 0) || ((mode > 0 || mode < -10) && videoonly == TRUE && hsc == 0))) {
		REFTIME aa;
		pMediaPosition->get_CurrentPosition(&aa);
		m_time.SetPos((int)(aa * 100));
		if (ptl) {
			ptl->SetProgressState(m_hWnd, TBPF_NORMAL);
			ptl->SetProgressValue(m_hWnd, (LONGLONG)aa, (LONGLONG)aa1);
		}
	}
	else if (plf && hsc == 0) {
		if (mode == -10) {
			m_time.SetPos((int)playb / 400);
			if (ptl) {
				ptl->SetProgressState(m_hWnd, TBPF_NORMAL);
				ptl->SetProgressValue(m_hWnd, (LONGLONG)playb / 4, (LONGLONG)oggsize);
			}
		}
		else {
			m_time.SetPos((int)playb);
			if (ptl) {
				ptl->SetProgressState(m_hWnd, TBPF_NORMAL);
				ptl->SetProgressValue(m_hWnd, (LONGLONG)playb, (LONGLONG)oggsize / (wavsam / 4));
			}
		}
	}

	tempo = m_tempo_sl.GetPos();
	s.Format(L"%03d", tempo);
	m_temp_num.SetWindowText(s);
	s.Format(L"%03d", m_pitch_sl.GetPos());
	m_pitch.SetWindowText(s);
	pitch = m_pitch_sl.GetPos();

	tt = 0;
	//	}
	//	m_time.Invalidate();

	savedata.kakuVol = m_kakuVol.GetPos();
	savedata.kakuVal = savedata.kakuVol;
	s.Format(_T("%3d%%"), savedata.kakuVal);
	m_kakuVolval.SetWindowText(s);

	//ランダム演奏用
	if (randomf) {
		if (playf == 0) {//演奏が止まっている
			switch (savedata.random) {
			case 0://ランダム
			{
				//					fnn="ランダム演奏中";
				if (m_yso.GetCheck() == 0 && m_ys6.GetCheck() == 0 && m_ysf.GetCheck() == 0 && m_ed6fc.GetCheck() == 0 && m_ed6sc.GetCheck() == 0 && m_ed6tc.GetCheck() == 0 && m_zweiii.GetCheck() == 0 && m_ysc1.GetCheck() == 0 && m_ysc2.GetCheck() == 0 && m_xa.GetCheck() == 0 && m_ys121.GetCheck() == 0 && m_ys122.GetCheck() == 0 && m_sor.GetCheck() == 0 && m_zwei.GetCheck() == 0 && m_gurumin.GetCheck() == 0 && m_dino.GetCheck() == 0 && m_br4.GetCheck() == 0 && m_ed3.GetCheck() == 0 && m_ed4.GetCheck() == 0 && m_ed5.GetCheck() == 0) { randomf = 0; break; }
				for (;;) {
					int a, b; CString s;
					CString ex;
					char buffer[_MAX_DIR];

					a = rand() % 20;
					if (a == 0 && m_ys6.GetCheck()) {
						b = rand() % 30 + 1; filen.Format(_T("Ys6_%02d.ogg"), b); Citiran_YS6 a; a.Gett(b - 1);
						modesub = 4; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 1 && m_ysf.GetCheck()) {
						b = rand() % 34 + 1; if (b == 22)filen.Format(_T("y3bg22a.ogg")); else filen.Format(_T("y3bg%02d.ogg"), b); Citiran_YSF a; a.Gett(b - 1);
						modesub = 3; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 2 && m_ed6fc.GetCheck()) {
						Citiran_FC a;
						b = rand() % 55; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
						modesub = 2; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 3 && m_ed6sc.GetCheck()) {
						itiran a;
						b = rand() % 97; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
						modesub = 1; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 4 && m_yso.GetCheck()) {
						Citiran_YSO a;
						b = rand() % 40; s = a.Gett(b); filen.Format(_T("YSO_%s.ogg"), s.Left(3));
						modesub = 5; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 5 && m_ed6tc.GetCheck()) {
						CED63rd a;
						b = rand() % 141; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
						modesub = 6; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 6 && m_zweiii.GetCheck()) {
						CZWEIII a;
						b = rand() % 65; s = a.Gett(b); filen.Format(_T("ZW2_%s.ogg"), s.Left(3));
						modesub = 7; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 7 && m_ysc1.GetCheck()) {
						CYsC1 a;
						b = rand() % 72; s = a.Gett(b); filen.Format(_T("%s.ogg"), s);
						modesub = 8; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 8 && m_ysc2.GetCheck()) {
						CYsC2 a;
						b = rand() % 92; s = a.Gett(b); filen.Format(_T("%s.ogg"), s);
						modesub = 9; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 9 && m_xa.GetCheck()) {
						CXA a;
						b = rand() % 24; s = a.Gett(b); filen.Format(_T("XANA%s.dec"), s.Left(3)); loop1 = a.loop1; loop2 = a.loop2 - loop1;
						modesub = 10; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 10 && m_ys121.GetCheck()) {
						CYs12_1 a;
						_getcwd(buffer, _MAX_DIR);
						_tchdir(savedata.ys12);
						if (_chdir("wave\\wave_44") == -1) {
							if (_chdir("wave\\wave_22") == -1) { break; }
							ex = "_22";
						}
						else ex = "_44";
						b = rand() % 24; s = a.Gett(b); filen.Format(_T("%s%s.wav"), s, ex);
						CString sf;
						sf.Format(_T("%s%s.pos"), s, ex);
						loop1 = loop2 = 0;
						struct a_ {
							int l1;
							int l2;
						};
						a_ aa;
						CFile f;
						if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
							f.Read(&aa, 8);
							f.Close();
							if (aa.l1 == 0)aa.l2 = 0;
							loop1 = aa.l1;
							loop2 = aa.l2 - loop1;
						}
						_chdir(buffer);
						modesub = 11; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 11 && m_ys122.GetCheck()) {
						CYs12_2 a;
						_getcwd(buffer, _MAX_DIR);
						_tchdir(savedata.ys122);
						if (_chdir("wave\\wave_44") == -1) {
							if (_chdir("wave\\wave_22") == -1) { break; }
							ex = "_22";
						}
						else ex = "_44";
						b = rand() % 31; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
						CString sf;
						sf.Format(_T("%s.pos"), s);
						loop1 = loop2 = 0;
						struct a_ {
							int l1;
							int l2;
						};
						a_ aa;
						CFile f;
						if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
							f.Read(&aa, 8);
							f.Close();
							if (aa.l1 == 0)aa.l2 = 0;
							loop1 = aa.l1;
							loop2 = aa.l2 - loop1;
						}
						_chdir(buffer);
						modesub = 12; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 12 && m_sor.GetCheck()) {
						CSor a;
						_getcwd(buffer, _MAX_DIR);
						_tchdir(savedata.sor);
						if (_chdir("WAVE\\WAVE44") == -1) {
							if (_chdir("WAVE\\WAVE22") == -1) { break; }
							ex = "_22";
						}
						else ex = "_44";
						b = rand() % 76; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
						CStdioFile f;
						CString sf;
						if (ex == "_22")
							sf = "..\\..\\WAVE_CD.DAT";
						else
							sf = "..\\..\\WAVE_DVD.DAT";
						loop1 = loop2 = 0;
						if (f.Open(sf, CFile::modeRead | CFile::typeText, NULL)) {
							for (int j = 0;; j++) {
								f.ReadString(sf);
								if (sf.Left(6) == s)break;
							}
							f.Close();
							CString sff;
							sff = sf.Mid(8, 10);//開始ms
							if (sf.Right(1) == "N") {
								loop1 = loop2 = 0;
							}
							else {
								float a, b;
								if (ex == "_22") b = 22.05f; else b = 44.1f;
								loop1 = _tstoi(sff);
								loop2 = _tstoi(sf.Mid(18, 10));
								a = (float)loop1;
								a = a * b;
								loop1 = (int)a;
								a = (float)loop2;
								a = a * b;
								loop2 = (int)a - loop1;
							}
						}
						_chdir(buffer);
						modesub = 13; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 13 && m_zwei.GetCheck()) {
						CZwei a;
						b = rand() % 36; s = a.Gett(b); filen.Format(_T("%s(wav.dat)"), s);
						modesub = 14; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 14 && m_gurumin.GetCheck()) {
						CGurumin a;
						b = rand() % 39; s = a.Gett(b); filen.Format(_T("%s.de2"), s); loop1 = a.loop1; loop2 = a.loop2 - loop1;
						modesub = 15; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 15 && m_dino.GetCheck()) {
						CDino a;
						b = rand() % 33; s = a.Gett(b); filen.Format(_T("%s(bgm.arc)"), s); loop1 = a.loop1; loop2 = a.loop2;
						modesub = 16; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 16 && m_br4.GetCheck()) {
						CBr4 a;
						b = rand() % 42; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
						modesub = 17; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 17 && m_ed3.GetCheck()) {
						CED3 a;
						b = rand() % 67; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
						modesub = 18; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 18 && m_ed4.GetCheck()) {
						CED4 a;
						b = rand() % 66; if (b == 1 || b == 2) b = 0; s = a.Gett(b); filen.Format(_T("%s"), s);
						modesub = 19; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					if (a == 19 && m_ed5.GetCheck()) {
						CED5 a;
						b = rand() % 98; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
						modesub = 20; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
				}
			}
			break;
			case 1://順次
				//				fnn="順次演奏中";
				if (m_yso.GetCheck() == 0 && m_ys6.GetCheck() == 0 && m_ysf.GetCheck() == 0 && m_ed6fc.GetCheck() == 0 && m_ed6sc.GetCheck() == 0 && m_ed6tc.GetCheck() == 0 && m_zweiii.GetCheck() == 0 && m_ysc1.GetCheck() == 0 && m_ysc2.GetCheck() == 0 && m_xa.GetCheck() == 0 && m_ys121.GetCheck() == 0 && m_ys122.GetCheck() == 0 && m_sor.GetCheck() == 0 && m_zwei.GetCheck() == 0 && m_gurumin.GetCheck() == 0 && m_dino.GetCheck() == 0 && m_br4.GetCheck() == 0 && m_ed3.GetCheck() == 0 && m_ed4.GetCheck() == 0 && m_ed5.GetCheck() == 0) { randomf = 0; break; }
				for (;;) {
					randomno++;
					int b; CString s;
					CString ex;
					char buffer[_MAX_DIR];
					if (randomno < 30 + 1) {
						if (!m_ys6.GetCheck())continue;
						b = randomno; filen.Format(_T("Ys6_%02d.ogg"), b); Citiran_YS6 a; a.Gett(b - 1);
						modesub = 4; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
						break;
					}
					else
						if (randomno < 34 + 30 + 1) {
							if (!m_ysf.GetCheck())continue;
							b = randomno - 30; if (b > 34)b = 34; if (b == 22)filen.Format(_T("y3bg22a.ogg")); else filen.Format(_T("y3bg%02d.ogg"), b); Citiran_YSF a; a.Gett(b - 1);
							modesub = 3; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
							break;
						}
						else
							if (randomno < 56 + 34 + 30 + 1) {
								if (!m_ed6fc.GetCheck())continue; Citiran_FC a;
								b = randomno - 34 - 31; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
								modesub = 2; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
								break;
							}
							else
								if (randomno < 98 + 56 + 34 + 30 + 1) {
									if (!m_ed6sc.GetCheck())continue; itiran a;
									b = randomno - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
									modesub = 1; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
									break;
								}
								else
									if (randomno < 40 + 98 + 56 + 34 + 30 + 1) {
										if (!m_yso.GetCheck())continue; Citiran_YSO a;
										b = randomno - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("YSO_%s.ogg"), s.Left(3));
										modesub = 5; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
										break;
									}
									else
										if (randomno < 141 + 40 + 98 + 56 + 34 + 30 + 1) {
											if (!m_ed6tc.GetCheck())continue; CED63rd a;
											b = randomno - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("ED6%s.ogg"), s.Left(3));
											modesub = 6; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
											break;
										}
										else
											if (randomno < 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
												if (!m_zweiii.GetCheck())continue; CZWEIII a;
												b = randomno - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("ZW2_%s.ogg"), s.Left(3));
												modesub = 7; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
												break;
											}
											else
												if (randomno < 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
													if (!m_ysc1.GetCheck())continue; CYsC1 a;
													b = randomno - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.ogg"), s);
													modesub = 8; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
													break;
												}
												else
													if (randomno < 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
														if (!m_ysc2.GetCheck())continue; CYsC2 a;
														b = randomno - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.ogg"), s);
														modesub = 9; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
														break;
													}
													else
														if (randomno < 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
															if (!m_xa.GetCheck())continue; CXA a;
															b = randomno - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("XANA%s.dec"), s.Left(3)); loop1 = a.loop1; loop2 = a.loop2 - loop1;
															modesub = 10; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
															break;
														}
														else
															if (randomno < 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																if (!m_ys121.GetCheck())continue; CYs12_1 a;
																_getcwd(buffer, _MAX_DIR);
																_tchdir(savedata.ys12);
																if (_chdir("wave\\wave_44") == -1) {
																	if (_chdir("wave\\wave_22") == -1) { break; }
																	ex = "_22";
																}
																else ex = "_44";
																b = randomno - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s%s.wav"), s, ex);
																CString sf;
																sf.Format(_T("%s%s.pos"), s, ex);
																loop1 = loop2 = 0;
																struct a_ {
																	int l1;
																	int l2;
																};
																a_ aa;
																CFile f;
																if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
																	f.Read(&aa, 8);
																	f.Close();
																	if (aa.l1 == 0)aa.l2 = 0;
																	loop1 = aa.l1;
																	loop2 = aa.l2 - loop1;
																}
																_chdir(buffer);
																modesub = 11; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																break;
															}
															else
																if (randomno < 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																	if (!m_ys122.GetCheck())continue; CYs12_2 a;
																	_getcwd(buffer, _MAX_DIR);
																	_tchdir(savedata.ys122);
																	if (_chdir("wave\\wave_44") == -1) {
																		if (_chdir("wave\\wave_22") == -1) { break; }
																		ex = "_22";
																	}
																	else ex = "_44";
																	b = randomno - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
																	CString sf;
																	sf.Format(_T("%s.pos"), s);
																	loop1 = loop2 = 0;
																	struct a_ {
																		int l1;
																		int l2;
																	};
																	a_ aa;
																	CFile f;
																	if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
																		f.Read(&aa, 8);
																		f.Close();
																		if (aa.l1 == 0)aa.l2 = 0;
																		loop1 = aa.l1;
																		loop2 = aa.l2 - loop1;
																	}
																	_chdir(buffer);
																	modesub = 12; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																	break;
																}
																else
																	if (randomno < 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																		if (!m_sor.GetCheck())continue; CSor a;
																		char buffer[_MAX_DIR];
																		_getcwd(buffer, _MAX_DIR);
																		_tchdir(savedata.sor);
																		if (_chdir("WAVE\\WAVE44") == -1) {
																			if (_chdir("WAVE\\WAVE22") == -1) { break; }
																			ex = "_22";
																		}
																		else ex = "_44";
																		b = randomno - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
																		CStdioFile f;
																		CString sf;
																		if (ex == "_22")
																			sf = "..\\..\\WAVE_CD.DAT";
																		else
																			sf = "..\\..\\WAVE_DVD.DAT";
																		loop1 = loop2 = 0;
																		if (f.Open(sf, CFile::modeRead | CFile::typeText, NULL)) {
																			for (int j = 0;; j++) {
																				f.ReadString(sf);
																				if (sf.Left(6) == s)break;
																			}
																			f.Close();
																			CString sff;
																			sff = sf.Mid(8, 10);//開始ms
																			if (sf.Right(1) == "N") {
																				loop1 = loop2 = 0;
																			}
																			else {
																				float a, b;
																				if (ex == "_22") b = 22.05f; else b = 44.1f;
																				loop1 = _tstoi(sff);
																				loop2 = _tstoi(sf.Mid(18, 10));
																				a = (float)loop1;
																				a = a * b;
																				loop1 = (int)a;
																				a = (float)loop2;
																				a = a * b;
																				loop2 = (int)a - loop1;
																			}
																		}
																		_chdir(buffer);
																		modesub = 13; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																		break;
																	}
																	else
																		if (randomno < 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																			if (!m_zwei.GetCheck())continue; CZwei a;
																			b = randomno - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s(wav.dat)"), s);
																			modesub = 14; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																			break;
																		}
																		else
																			if (randomno < 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																				if (!m_gurumin.GetCheck())continue; CGurumin a;
																				b = randomno - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.de2"), s); loop1 = a.loop1; loop2 = a.loop2 - loop1;
																				modesub = 15; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																				break;
																			}
																			else
																				if (randomno < 33 + 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																					if (!m_dino.GetCheck())continue; CDino a;
																					b = randomno - 39 - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s(bgm.arc)"), s); loop1 = a.loop1; loop2 = a.loop2;
																					modesub = 16; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																					break;
																				}
																				else
																					if (randomno < 42 + 33 + 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																						if (!m_br4.GetCheck())continue; CBr4 a;
																						b = randomno - 33 - 39 - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
																						modesub = 17; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																						break;
																					}
																					else
																						if (randomno < 67 + 42 + 33 + 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																							if (!m_ed3.GetCheck())continue; CED3 a;
																							b = randomno - 42 - 33 - 39 - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
																							modesub = 18; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																							break;
																						}
																						else
																							if (randomno < 66 + 67 + 42 + 33 + 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																								if (!m_ed4.GetCheck())continue; CED4 a;
																								b = randomno - 67 - 42 - 33 - 39 - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; if (b == 1 || b == 2) { b = 3; randomno += 2; } s = a.Gett(b); filen.Format(_T("%s"), s);
																								modesub = 19; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																								break;
																							}
																							else
																								if (randomno < 98 + 66 + 67 + 42 + 33 + 39 + 36 + 76 + 31 + 24 + 24 + 92 + 72 + 65 + 141 + 40 + 98 + 56 + 34 + 30 + 1) {
																									if (!m_ed5.GetCheck())continue; CED5 a;
																									b = randomno - 66 - 67 - 42 - 33 - 39 - 36 - 76 - 31 - 24 - 24 - 92 - 72 - 65 - 141 - 40 - 98 - 56 - 34 - 30 - 1; s = a.Gett(b); filen.Format(_T("%s.wav"), s);
																									modesub = 20; ret2 = b; b = m_dou.GetCheck(); m_dou.SetCheck(0); playf = 1; play(); m_dou.SetCheck(b);
																									break;
																								}
																								else
																									randomno = 0;
				}
				break;
			}
		}
		else {
			CString s; m_kaisuu.GetWindowText(s);
			if (loopcnt >= _tstoi(s)) OnButton5();
		}
	}

	savedata.dsvol = m_dsval.GetPos();
	if (savedata.dsvol == 0)savedata.dsvol = 1;
	s.Format(_T("%3d%%"), (savedata.dsvol + 499) * 2 / 10);
	m_dsvols.GetWindowText(ss);
	if (s != ss)
		m_dsvols.SetWindowText(s);
	if (m_dsb && thn1 == FALSE) {
		if (savedata.dsvol == -498)
			m_dsb->SetVolume(DSBVOLUME_MIN);
		else
			m_dsb->SetVolume((savedata.dsvol - 1) * 7);
	}
	if (pBasicAudio) {
		if (savedata.dsvol == -498)
			pBasicAudio->put_Volume(-10000);
		else
			pBasicAudio->put_Volume((savedata.dsvol - 1) * 7);
	}

}

int timerr = 0;
int tim = 0;
int SC1 = 0;
int ip = 0;
int aaaa = 0, aaaa1 = 0;

void timerog(UINT nIDEvent);
void timerog1(UINT nIDEvent);
void timerog1(UINT nIDEvent)
{
	if (nIDEvent == 4923) {
		og->KillTimer(4923);
		if (ip != 0) return;
		if (maini)
			::SetWindowPos(maini->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::SetWindowPos(og->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		og->SetTimer(4930, 10, NULL);
		RegisterHotKey(og->GetSafeHwnd(), ID_HOTKEY0, 0, VK_UP);
		RegisterHotKey(og->GetSafeHwnd(), ID_HOTKEY1, 0, VK_DOWN);
		RegisterHotKey(og->GetSafeHwnd(), ID_HOTKEY2, 0, VK_RIGHT);
		RegisterHotKey(og->GetSafeHwnd(), ID_HOTKEY3, 0, VK_LEFT);
		ip = 3;
	}
	if (nIDEvent == 4924) {
		og->KillTimer(4924);
		UnregisterHotKey(og->GetSafeHwnd(), ID_HOTKEY0);
		UnregisterHotKey(og->GetSafeHwnd(), ID_HOTKEY1);
		UnregisterHotKey(og->GetSafeHwnd(), ID_HOTKEY2);
		UnregisterHotKey(og->GetSafeHwnd(), ID_HOTKEY3);
	}
	if (nIDEvent == 4930) {
		ip--;
		if (ip == 0) {
			aaaa1 = 0;
			og->KillTimer(4930);
		}
	}

	if (nIDEvent == 9100) {
		og->KillTimer(9100);
		og->OnRestart();
		og->OnRestart();
	}

	if (nIDEvent == 9998) {
		og->KillTimer(9998);
		if (ndd != "") {
			if (pl) {
				for (; plw == 0;) { DoEvent(); }
			}
			og->dp(ndd);
		}
	}
	if (nIDEvent == 9000) {
		if (savedata.saverenzoku == 1 && endflg == 1) {
			plcnt++;
			if (plcnt < pl->m_lc.GetItemCount()) {
				pl->Get(plcnt);
				pl->SIcon(plcnt);
				fade1 = 0; lenl = 0;
				fade = 1.0f; plf = 0;
				og->KillTimer(9000);
				og->play();
			}
		}
	}
	if (nIDEvent == 6555) {
		if (pl)
			pl->SIconTimer(SC1);
		SC1++; SC1 = SC1 % 2;
	}
	if (nIDEvent == 5211) {
		og->KillTimer(5211);
		if (savedata.pl == 1) {
			pl = new CPlayList;
			pl->Create(og);
			if (!plw) {
				for (;;) { if (plw) break; DoEvent(); }
			}
			if (pl && plw && filen != "") {
				int plc;
				if (mode == -10)
					plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, oggsize / (2 * wavch * wavbit / 4), 1);
				else if (mode == -9 || mode == -8) {
					double wavv[] = { 0,1.0,2.0,2.0,2.0,2.0,2.0 };//(double)(wavbit2/wavv[wavch])
					plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, (int)(
						(double)oggsize / (double)(wavbit * 2 * wavv[wavch]) / (double)(wavsam / 16.0f)
						), 1);
				}
				else if (mode == -3) {
					if (oggsize == 0)
						plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, -1, 1);
					else
						plc = pl->Add(tagfile, mode, loop1, loop2, tagname, tagalbum, filen, 0, oggsize / (2 * wavch * wavbit), 1);
				}
				else
					plc = pl->Add(fnn, mode, loop1, loop2, tagname, tagalbum, filen, ret2, oggsize / (2 * wavch * wavbit));
				if (plc == -1) {
					int i = pl->m_lc.GetItemCount() - 1;
					plcnt = i;
					pl->SIcon(i);
				}
				else {
					plcnt = plc;
					pl->SIcon(plc);
				}
			}
		}
	}

	if (nIDEvent == 5219) {
		og->KillTimer(5219);
		THUMBBUTTON b[4];
		b[0].hIcon = ::AfxGetApp()->LoadIcon(IDI_T1);	b[0].dwMask = THB_ICON | THB_TOOLTIP | THB_FLAGS;
		b[0].dwFlags = THBF_ENABLED;	b[0].iId = 0;
		wcscpy(b[0].szTip, L"再演奏");
		b[1].hIcon = ::AfxGetApp()->LoadIcon(IDI_T2);	b[1].dwMask = THB_ICON | THB_TOOLTIP | THB_FLAGS;
		b[1].dwFlags = THBF_ENABLED;	b[1].iId = 1;
		wcscpy(b[1].szTip, L"一時停止");
		b[2].hIcon = ::AfxGetApp()->LoadIcon(IDI_T3);	b[2].dwMask = THB_ICON | THB_TOOLTIP | THB_FLAGS;
		b[2].dwFlags = THBF_ENABLED;	b[2].iId = 2;
		wcscpy(b[2].szTip, L"停止");
		b[3].hIcon = ::AfxGetApp()->LoadIcon(IDI_T4);	b[3].dwMask = THB_ICON | THB_TOOLTIP | THB_FLAGS;
		b[3].dwFlags = THBF_ENABLED;	b[3].iId = 3;
		wcscpy(b[3].szTip, L"プレイリスト開閉");
		if (ptl)ptl->ThumbBarAddButtons(og->m_hWnd, 4, b);

	}
	if (nIDEvent == 5656) {
		for (int i = 0; i < 300; i++)spetm[i] = 1;
	}

	if (nIDEvent == 5657) {
		int i;
		for (i = 0; i < 300; i++)
			if (spetm[i] == 1) spelv[i]--;
		if (spelv[i] < 0) spelv[i] = 0;
	}

	if (nIDEvent == 1233) {
		if (tim == 0) {
			tim = 1;
			og->timerp();
			tim = 0;
		}
	}

	if (nIDEvent == 11251) {
		ttt_++;
		if (ttt_ == 1) {
			og->KillTimer(11251);
			og->OnRestart();
		}
	}

	if (nIDEvent == 15011) {
		og->KillTimer(15011);
		maini = NULL;
		if (savedata.aero) {
			maini = new CImageBase;
			maini->Create(og);
			maini->oya = og;
		}
		RECT r;
		og->GetWindowRect(&r);
		if (maini)
			maini->MoveWindow(&r);
		if (maini)
			::SetWindowPos(maini->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		::SetWindowPos(og->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	if (nIDEvent == 1251) {
		if (pMediaPosition && pl && plw) {
			if ((mode == -2 || videoonly == TRUE)) {
				REFTIME aa, bb;
				pMediaPosition->get_CurrentPosition(&aa);
				pMediaPosition->get_Duration(&bb);
				if (aa >= bb) {
					if (pl->m_renzoku.GetCheck() == TRUE) {
						plcnt++;
						if (plcnt < pl->m_lc.GetItemCount()) {
							pl->Get(plcnt);
							pl->SIcon(plcnt);
							og->KillTimer(1250);
							fade1 = 0; lenl = 0;
							fade = 1.0f; plf = 0;
							int m = mode;
							og->OnRestart();
						}
					}
				}
			}
		}

		if ((fade1 == 1 && pl && plw)) {
			if (pl->m_renzoku.GetCheck() == TRUE) {
				plcnt++;
				if (plcnt < pl->m_lc.GetItemCount()) {
					og->KillTimer(1250);
					pl->Get(plcnt);
					pl->SIcon(plcnt);
					thn = FALSE;
					for (int j = 0; j < 200; j++) {
						DoEvent();
						Sleep(10);
						if (thn == TRUE) {
							break;
						}
					}
					og->stop();
					fade1 = 0; lenl = 0;
					og->OnRestart();
					//					if(mode==-2){og->SetTimer(11251,300,NULL); ttt_=0;}
					//SendMessage(WM_USER+2,0,0);//OnRestart();
				}
			}
		}
	}
}
void timerog(UINT nIDEvent)
{
	_set_se_translator(trans_func);
	try {
		timerog1(nIDEvent);
		//	}__except(EXCEPTION_EXECUTE_HANDLER){}
	}
	catch (SE_Exception e) {
	}
	catch (_EXCEPTION_POINTERS* ep) {
	}
	catch (...) {}
}
#if WIN64
void COggDlg::OnTimer(UINT_PTR nIDEvent)
#else
void COggDlg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	timerog(nIDEvent);
	CDialog::OnTimer(nIDEvent);
}
LRESULT COggDlg::dp2(WPARAM, LPARAM)
{
	OnRestart();
	return 0;
}

void COggDlg::OnButton1()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	randomf = 0;
	m_rund.EnableWindow(TRUE);
	stop();
}

CString COggDlg::UTF8toSJIS(const char* a)
{
	WCHAR f[1024];
	char ff[1024];
	int rr = MultiByteToWideChar(CP_UTF8, 0, a, -1, f, 1024);
	int rr2 = WideCharToMultiByte(CP_ACP, 0, f, rr, ff, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, f, rr, ff, rr2, NULL, NULL);
	CString s; s = f;
	return s;
	//	return _T("");
}

CString COggDlg::UTF8toUNI(const TCHAR* a)
{
	//	WCHAR f[1024];
	//	char ff[1024];
	//	int rr2=WideCharToMultiByte(CP_ACP,0,a,-1,ff,0,NULL,NULL);
	//	int rr=MultiByteToWideChar(CP_UTF8,0,ff,-1,f,1024);
	//	WideCharToMultiByte(CP_ACP,0,f,rr,ff,rr2,NULL,NULL);
	CString s; s = a;
	return s;
	//	return _T("");
}

//画面表示
void COggDlg::gamen(int uu)
{
	switch (mode) {
	case -1://ogg
		if (filen.Find(L"y8_logo.ogg") != -1) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}
		if (filen.Find(L"y8_op.ogg") != -1) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}
		if (filen.Find(L"y8_end.ogg") != -1) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}
		if (filen.Find(L"yc_logo.ogg") != -1) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}
		break;
	case 1://ED6SC
		if (uu > 97) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 2://ED6FC
		if (uu > 54) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 3://YSF
		if (uu == 32 || uu == 33 || uu == 25) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 4://YS6
		if (uu > 24 && uu < 29 || uu == 1) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 5://YSO
		if (uu > 39) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 6://YSO
		if (uu > 140) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 7://YSO
		if (uu > 64) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 8://YSC1
		if (uu >= 72) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 9://YSC1
		if (uu >= 93) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 10://XANADU
		if (uu >= 24) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 11://ys1
		if (uu >= 25) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 12://ys2
		if (uu >= 31) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 15://gurumin
		if (uu == 40) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 16://dino
		if (uu == 33) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case 19://ed4
		if (uu == 1 || uu == 2) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case -11://ed4
		if (uu >= 28) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case -13://arc
		if (uu == 0) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case -14://san1
		if (uu == 43 || uu == 45 || uu == 46 || uu == 47) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	case -15://san1
		if (uu == 50 || uu == 51 || uu == 49) {
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
		}break;
	}
}

void COggDlg::gamenkill()
{
	if (pMainFrame1 != NULL) {
		killw = 0;
		RECT r;
		pMainFrame1->GetWindowRect(&r);
		savedata.gx = r.left;
		savedata.gy = r.top;
		//		pMainFrame1->stop();
		//		pMainFrame1->DestroyWindow(); 
		::SendMessage(pMainFrame1->m_hWnd, WM_CLOSE, NULL, NULL);
		//		delete pMainFrame1;
		//動画画面が閉じるのを待つ
		for (; killw == 0;)
			DoEvent();
		//		delete pMainFrame1;
		pMainFrame1 = NULL;
		//		for(int i=0;i<20;i++){DoEvent();Sleep(5);};
	}
}

void COggDlg::dougaplay(int uu, CString ss)
{
	if (pMainFrame1 == NULL) return;
	switch (mode) {
	case -1://ED6SC
		if (filen.Find(L"y8_logo.ogg") != -1) {
			pMainFrame1->play(1, ss);
		}
		if (filen.Find(L"y8_op.ogg") != -1) {

			pMainFrame1->play(2, ss);
		}
		if (filen.Find(L"y8_end.ogg") != -1) {
			;
			pMainFrame1->play(3, ss);
		}
		if (filen.Find(L"yc_logo.ogg") != -1) {
			;
			pMainFrame1->play(4, ss);
		}
		break;
	case 1://ED6SC
		if (uu > 97) {
			pMainFrame1->play(uu);
		}break;
	case 2://ED6FC
		if (uu > 54) {
			pMainFrame1->play(uu);
		}break;
	case 3://YSF
		if (uu == 32 || uu == 33 || uu == 25) {
			pMainFrame1->play(uu);
		}break;
	case 4://YS6
		if (uu > 24 && uu < 29 || uu == 1) {
			pMainFrame1->play(uu);
		}
	case 5://YSO
		if (uu > 39) {
			pMainFrame1->play(uu);
		}break;
	case 6://YSO
		if (uu > 140) {
			pMainFrame1->play(uu);
		}break;
	case 7://YSO
		if (uu > 64) {
			pMainFrame1->play(uu);
		}break;
	case 8://YSC1
		if (uu >= 72) {
			pMainFrame1->play(uu);
		}break;
	case 9://YSC1
		if (uu >= 93) {
			pMainFrame1->play(uu);
		}break;
	case 10://XANADU
		if (uu >= 24) {
			pMainFrame1->play(uu);
		}break;
	case 11://ys1
		if (uu >= 25) {
			pMainFrame1->play(uu);
		}break;
	case 12://ys2
		if (uu >= 31) {
			pMainFrame1->play(uu);
		}break;
	case 15://gurumin
		if (uu == 40) {
			pMainFrame1->play(uu);
		}break;
	case 16://dino
		if (uu == 33) {
			pMainFrame1->play(uu);
		}break;
	case 19://ed4
		if (uu == 1 || uu == 2) {
			pMainFrame1->play(uu);
		}break;
	case -11://ed4
		if (uu >= 28) {
			pMainFrame1->play(uu);
		}break;
	case -13://arc
		if (uu == 0) {
			pMainFrame1->play(uu);
		}break;
	case -14://arc
		if (uu == 43 || uu == 45 || uu == 46 || uu == 47) {
			pMainFrame1->play(uu);
		}break;
	case -15://arc
		if (uu == 50 || uu == 51 || uu == 49) {
			pMainFrame1->play(uu);
		}break;
	}
}

void COggDlg::OnButton2()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed6sc);
	ret += _chdir("bgm");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	itiran* a = new itiran(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = pl_no;
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567) {
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ed6sc);
		ret += _chdir("bgm");
		filen.Format(_T("ED6%03d.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 1;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);
}

void COggDlg::OnButton6_FC()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed6fc);
	ret += _chdir("bgm");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	Citiran_FC* a = new Citiran_FC(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = pl_no;
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		filen.Format(_T("ED6%03d.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 2;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnButton7_YSF()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ysf);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	Citiran_YSF* a = new Citiran_YSF(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567) {
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ysf);
		ret += _chdir("RELEASE\\MUSIC");
		if (a->ret == 21) {
			filen.Format(_T("y3bg22a.ogg"));
		}
		else
			filen.Format(_T("y3bg%02d.ogg"), a->ret + 1);
		modesub = 3;
		ret2 = a->ret;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnButton8_YS6()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ys6);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	Citiran_YS6* a = new Citiran_YS6(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567) {
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ys6);
		ret += _chdir("RELEASE\\MUSIC");
		filen.Format(_T("Ys6_%02d.ogg"), a->ret + 1);
		modesub = 4;
		ret2 = a->ret;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnYso()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.yso);
	ret += _chdir("RELEASE\\MUSIC");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	Citiran_YSO* a = new Citiran_YSO(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.yso);
		ret += _chdir("RELEASE\\MUSIC");
		filen.Format(_T("YSO_%03d.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 5;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnButton17_ED6TC()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed6tc);
	ret += _chdir("bgm");
	if (ret != 0) return;
	CED63rd* a = new CED63rd(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = pl_no;
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ed6tc);
		ret += _chdir("bgm");
		filen.Format(_T("ED6%03d.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 6;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}


void COggDlg::OnZWEIII()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.zweiii);
	ret += _chdir("bgm");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CZWEIII* a = new CZWEIII(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.zweiii);
		ret += _chdir("bgm");
		filen.Format(_T("ZW2_%03d.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 7;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnYsC1()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ysc);
	ret += _chdir("bgm\\ys1");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CYsC1* a = new CYsC1(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ysc);
		ret += _chdir("bgm\\ys1");
		filen.Format(_T("%s.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 8;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnYsC2()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ysc);
	ret += _chdir("bgm\\ys2");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CYsC2* a = new CYsC2(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ysc);
		ret += _chdir("bgm\\ys2");
		filen.Format(_T("%s.ogg"), a->ret);
		ret2 = a->ret2;
		modesub = 9;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton25()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.xa);
	ret += _chdir("data\\bgm");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CXA* a = new CXA(CWnd::FromHandle(GetSafeHwnd()));
	a->ret = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.xa);
		ret += _chdir("data\\bgm");
		filen.Format(_T("XANA%03d.dec"), a->ret);
		ret2 = a->ret;
		loop1 = a->loop1;
		loop2 = a->loop2 - loop1;
		modesub = 10;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton27()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	CString ex;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ys12);
	if (_chdir("wave\\wave_44") == -1) {
		if (_chdir("wave\\wave_22") == -1) { fnn = "ファイル又はフォルダがありません"; return; }
		ex = "_22";
	}
	else ex = "_44";
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CYs12_1* a = new CYs12_1(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ys12);
		if (_chdir("wave\\wave_44") == -1) {
			if (_chdir("wave\\wave_22") == -1) { return; }
			ex = "_22";
		}
		else ex = "_44";
		filen.Format(_T("%s%s.wav"), a->ret, ex);
		ret2 = a->ret2;
		CFile f;
		CString sf;
		sf.Format(_T("%s%s.pos"), a->ret, ex);
		loop1 = loop2 = 0;
		struct a1 {
			int l1;
			int l2;
		};
		a1 aa;
		if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
			f.Read(&aa, 8);
			f.Close();
			if (aa.l1 == 0)aa.l2 = 0;
			loop1 = aa.l1;
			loop2 = aa.l2 - loop1;
		}
		modesub = 11;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton28()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	CString ex;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ys122);
	if (_chdir("wave\\wave_44") == -1) {
		if (_chdir("wave\\wave_22") == -1) { fnn = "ファイル又はフォルダがありません"; return; }
		ex = "_22";
	}
	else ex = "_44";
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CYs12_2* a = new CYs12_2(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ys122);
		if (_chdir("wave\\wave_44") == -1) {
			if (_chdir("wave\\wave_22") == -1) { return; }
			ex = "_22";
		}
		else ex = "_44";
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		CFile f;
		CString sf;
		sf.Format(_T("%s.pos"), a->ret);
		loop1 = loop2 = 0;
		struct a1 {
			int l1;
			int l2;
		};
		a1 aa;
		if (f.Open(sf, CFile::modeRead | CFile::typeBinary, NULL)) {
			f.Read(&aa, 8);
			f.Close();
			if (aa.l1 == 0)aa.l2 = 0;
			loop1 = aa.l1;
			loop2 = aa.l2 - loop1;
		}
		modesub = 12;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton31()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	CString ex;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.sor);
	if (_chdir("WAVE\\WAVE44") == -1) {
		if (_chdir("WAVE\\WAVE22") == -1) { fnn = "ファイル又はフォルダがありません"; return; }
		ex = "_22";
	}
	else ex = "_44";
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CSor* a = new CSor(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.sor);
		if (_chdir("WAVE\\WAVE44") == -1) {
			if (_chdir("WAVE\\WAVE22") == -1) { return; }
			ex = "_22";
		}
		else ex = "_44";
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		CStdioFile f;
		CString sf;
		if (ex == "_22")
			sf = "..\\..\\WAVE_CD.DAT";
		else
			sf = "..\\..\\WAVE_DVD.DAT";
		loop1 = loop2 = 0;
		if (f.Open(sf, CFile::modeRead | CFile::typeText, NULL)) {
			for (int j = 0;; j++) {
				f.ReadString(sf);
				if (sf.Left(6) == a->ret)break;
			}
			f.Close();
			CString sff;
			sff = sf.Mid(8, 10);//開始ms
			if (sf.Right(1) == "N") {
				loop1 = loop2 = 0;
			}
			else {
				float a, b;
				if (ex == "_22") b = 22.05f; else b = 44.1f;
				loop1 = _tstoi(sff);
				loop2 = _tstoi(sf.Mid(18, 10));
				a = (float)loop1;
				a = a * b;
				loop1 = (int)a;
				a = (float)loop2;
				a = a * b;
				loop2 = (int)a - loop1;
			}
		}
		modesub = 13;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton33()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.zwei);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CZwei* a = new CZwei(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.zwei);
		filen.Format(_T("%s(wav.dat)"), a->ret);
		ret2 = a->ret2;
		modesub = 14;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton35()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.gurumin);
	ret += _chdir("bgm");
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CGurumin* a = new CGurumin(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.gurumin);
		ret += _chdir("bgm");
		filen.Format(_T("%s.de2"), a->ret);
		ret2 = a->ret2;
		loop1 = a->loop1;
		loop2 = a->loop2 - loop1;
		modesub = 15;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton37()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.dino);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CDino* a = new CDino(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.dino);
		filen.Format(_T("%s(bgm.arc)"), a->ret);
		ret2 = a->ret2;
		loop1 = a->loop1;
		loop2 = a->loop2;
		modesub = 16;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton39()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.br4);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CBr4* a = new CBr4(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.br4);
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		modesub = 17;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton44()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed3);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CED3* a = new CED3(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ed3);
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		modesub = 18;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton45()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed4);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CED4* a = new CED4(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ed4);
		filen.Format(_T("%s"), a->ret);
		ret2 = a->ret2;
		modesub = 19;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton46()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.ed5);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CED5* a = new CED5(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.ed5);
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		modesub = 20;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton47()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.tuki);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CTUKI* a = new CTUKI(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.tuki);
		filen.Format(_T("%s.mp3"), a->ret);
		ret2 = a->ret2;
		modesub = -11;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton48()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.nishi);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CNishi* a = new CNishi(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.nishi);
		filen.Format(_T("%s.wav"), a->ret);
		ret2 = a->ret2;
		modesub = -12;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton51()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.arc);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CArc* a = new CArc(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		loopcnt = 0;
		ret = _tchdir(savedata.arc);
		filen.Format(_T("%s.adp(music.pak)"), a->ret);
		ret2 = a->ret2;
		modesub = -13;
		delete a;
		play();
	}
	else
		delete a;
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton53()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.san1);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CSan1* a = new CSan1(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.san1);
		if (a->ret == "★") {
			filen = "★";
		}
		else {
			filen.Format(_T("%smusic.wav"), a->ret);
			if (filen == "49music.wav" || filen == "50music.wav" || filen == "51music.wav") _chdir("Cmusic"); else _chdir("music");
			CFile f;
			if (f.Open(filen, CFile::modeRead, NULL) == 0) {
				filen.Format(_T("%smusic.mp3"), a->ret);
				if (f.Open(filen, CFile::modeRead, NULL) == 0) { fnn = "ファイル又はフォルダがありません"; return; }
				else f.Close();
			}
			else f.Close();
		}
		ret2 = a->ret2;
		modesub = -14;
		delete a;
		play();
	}
	SetTimer(4923, 20, NULL);

}

void COggDlg::OnBnClickedButton54()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int ret;
	char buffer[_MAX_DIR];
	_getcwd(buffer, _MAX_DIR);
	ret = _tchdir(savedata.san2);
	if (ret != 0) { fnn = "ファイル又はフォルダがありません"; return; }
	CSan2* a = new CSan2(CWnd::FromHandle(GetSafeHwnd()));
	a->ret2 = ret2;
	CWnd::PostMessage(0x118);
	if (a->DoModal() == 1567)
	{
		_chdir(buffer);
		stop();
		ret = _tchdir(savedata.san2);
		if (a->ret == "★") {
			filen = "★";
		}
		else {
			filen.Format(_T("0%smusic.mp3"), a->ret);
		}
		ret2 = a->ret2;
		modesub = -15;
		delete a;
		play();
	}
}

void COggDlg::OnPause()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (plf == 0) return;
	if (ps == 0)
	{
		if (pMainFrame1 != NULL && (mode == -2 || (mode > 0 && videoonly == TRUE)))
		{
			pMainFrame1->pause(0);
		}
		if (ogg != NULL || adbuf2 != NULL || mod != NULL || wav != NULL || mode == -9)
			if (m_dsb && thn == FALSE) {
				m_dsb->GetCurrentPosition(&PlayCursora, &WriteCursora);
				m_dsb->Stop();
			}
		//			waveOutPause(hwo);
		m_ps.SetWindowText(_T("再開"));
		ps = 1;
	}
	else {
		if (ogg != NULL || adbuf2 != NULL || mod != NULL || wav != NULL || mode == -9) {
			//			DSBPOSITIONNOTIFY dsn[20];
			//			ttt = WAVDAStartLen;
			//			hNotifyEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
			//			hNotifyEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
			// setup the first one.
			//			for(int y =0;y<10;y++){
			//				dsn[y].dwOffset = y*(WAVDALen/10);
			//				dsn[y].hEventNotify = hNotifyEvent[0];
			//			}
			//			dsn[y].dwOffset = DSBPN_OFFSETSTOP;
			//			dsn[y].hEventNotify = hNotifyEvent[1];
			//			AfxBeginThread(HandleNotifications,(LPVOID)this);
			//			dsnf1->SetNotificationPositions(10+1,dsn);
			if (m_dsb && thn == FALSE)m_dsb->Play(0, 0, DSBPLAY_LOOPING);
			if (m_dsb && thn == FALSE)m_dsb->SetCurrentPosition(PlayCursora);
		}
		//			waveOutRestart(hwo);
		m_ps.SetWindowText(_T("一時停止"));
		if (pMainFrame1 != NULL && (mode == -2 || (mode > 0 && videoonly == TRUE)))
		{
			pMainFrame1->pause(1);
		}
		ps = 0;
	}
}

BOOL COggDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: 以下のブロックはツールヒント コンポーネントによって追加されました
	{
		// ツールヒントにこのメッセージを処理させます
		m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: 以下のブロックはツールヒント コンポーネントによって追加されました
}

void COggDlg::OnOK()
{
	// TODO: この位置にその他の検証用のコードを追加してください
	stop();
	CDialog::OnOK();
}
extern IMediaEvent* pMediaEvent;
void COggDlg::OnRestart()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CString ti;
	stop();
	m_ps.EnableWindow(TRUE);
	if (filen != "") {
		ti = filen.Right(filen.GetLength() - filen.ReverseFind('\\') - 1);
		int sub_ = mode;
		if ((filen.Right(4).MakeLower() == ".ogg" || filen.Right(4) == ".OGG" || filen.Right(6).MakeLower() == ".qull3") && mode < 1) {
			modesub = -1;
			play();
		}
		else if ((filen.Right(4).MakeLower() == ".dsf" || filen.Right(5) == ".DSF" || filen.Right(4).MakeLower() == ".dff" || filen.Right(4) == ".DFF" || filen.Right(4).MakeLower() == ".wsd" || filen.Right(4) == ".WSD") && mode < 1) {
			modesub = -7;
			play();
		}
		else if ((filen.Right(5).MakeLower() == ".flac" || filen.Right(5) == ".FLAC" || filen.Right(7).MakeLower() == L".qull3h") && mode < 1) {
			modesub = -8;
			play();
		}
		else if ((filen.Right(4).MakeLower() == ".m4a" || filen.Right(4) == ".M4A" || filen.Right(4).MakeLower() == ".aac" || filen.Right(4) == ".AAC") && mode < 1) {
			modesub = -9;
			play();
		}
		else if (mode == -10 && (filen.Right(4).MakeLower() == ".mp3" || filen.Right(4) == ".MP3" || filen.Right(4).MakeLower() == ".mp2" || filen.Right(4) == ".MP2" ||
			filen.Right(4).MakeLower() == ".mp1" || filen.Right(4) == ".MP1" || filen.Right(4).MakeLower() == ".rmp" || filen.Right(4) == ".RMP")) {
			modesub = -10;
			play();
		}
		else if (mode == -2 || mode == -3) {
			playlistdata p;
			kpi[0] = 0;
			if (pl && plw) {
				p.sub = 0;
				CString ss, s;
				s = filen;
				ss = s.Left(s.ReverseFind(':') - 1);
				if (ss != "") s = ss;
				pl->plugs(s, &p, kpi);
				if (p.sub == -3) {//kb medua player
					s = kpi;
					ss = s.Left(s.ReverseFind('\\'));
					_tchdir(ss);
					//					hDLLk = LoadLibrary(kpi);
					//					pFunck = (pfnGetKMPModule)::GetProcAddress(hDLLk, "kmp_GetTestModule");
					modesub = -3;
					play();
					return;
				}
			}
			fnn = ti;
			stflg = FALSE;
			modesub = -2; mode = -2;
			pMainFrame1 = new CDouga;
			pMainFrame1->Create(GetSafeHwnd());
			pMainFrame1->ShowWindow(SW_HIDE);
			pMainFrame1->play(0);
			CFile f123;
			int flggg = 0;
			if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
				f123.Close();
				if (IDYES == MessageBox(_T("途中再生データが存在します。\n前回中断した部分から再生しますか？\nはい = 途中から再生\nいいえ = はじめから再生"), _T("再生確認"), MB_YESNO)) {
					flggg = 1;
				}
				else {
					CFile::Remove(filen + _T(".save"));
				}
			}
			if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE && flggg == 1) {
				f123.Close();
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl) {
					for (int y = 0; y < 45; y++) {
						Sleep(10); DoEvent();
						long eventCode;
						pMediaEvent->WaitForCompletion(-1, &eventCode);
						HRESULT hr = pMediaControl->Run();
						if (hr == S_OK) break;
					}
				}
				if (mode == -10) {
					if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
						f123.Read(&playb, sizeof(__int64));
						if (savedata.mp3orig) {
							mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch);
						}
						else {
							mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch);
						}
						f123.Close();
					}
				}
				if (mode == -2) {
					if (f123.Open(filen + _T(".save"), CFile::modeRead, NULL) == TRUE) {
						f123.Read(&aa1_, sizeof(double));
						pMainFrame1->seek((LONGLONG)(((float)((float)aa1_ * 100.0f * 100000.0f))));
						f123.Close();
					}
				}
			}
			else {
				if (pGraphBuilder)pMainFrame1->plays2();
				if (pMediaControl) {
					for (int y = 0; y < 45; y++) {
						Sleep(10); DoEvent();
						HRESULT hr = pMediaControl->Run();
						if (hr == S_OK) break;
					}
				}
				if (pMainFrame1) { pMainFrame1->seek(0); }
			}
			//			if(pGraphBuilder)pMainFrame1->plays2();
			//			if(pMediaControl)pMediaControl->Run();
			//			if(pMediaPosition)pMediaPosition->put_CurrentPosition(0);
			int a = 0; aa2 = 0;
			REFTIME aa = 0;
			aa2 = 0;
			ps = 0; m_ps.SetWindowText(_T("一時停止"));
			if (pMediaPosition)pMediaPosition->get_StopTime(&aa);
			aa1 = oggsize2 = aa;
			m_time.SetRange(0, (int)((REFTIME)aa * 100.0), TRUE);
			m_time.SetSelection(0, (int)((REFTIME)aa * 100.0) - 1);
			m_time.Invalidate();
			if (pl && plw) {
				int plc = -1;
				plc = pl->Add(fnn, mode, 0, 0, _T(""), _T(""), filen, 0, (int)aa, 1);
				if (plc == -1) {
					int i = pl->m_lc.GetItemCount() - 1;
					plcnt = i;
					pl->SIcon(i);
				}
				else {
					plcnt = plc;
					pl->SIcon(plc);
				}
			}
			SetTimer(1250, 100, NULL);
			plf = 1;
			CFile ff;
			CString ss11 = filen; ss11.MakeLower();
			if (ss11.Right(3) == "m4a") {
				if (ff.Open(filen, CFile::modeRead | CFile::shareDenyNone, NULL) == TRUE) {
					mp3file = filen;
					ZeroMemory(bufimage, sizeof(bufimage));
					int i;
					ff.Read(bufimage, sizeof(bufimage));
					for (i = 0; i < 0x300000; i++) {// 00 06 5D 6A 64 61 74 61
						if (bufimage[i] == 0x63 && bufimage[i + 1] == 0x6f && bufimage[i + 2] == 0x76 && bufimage[i + 3] == 0x72 && bufimage[i + 8] == 0x64 && bufimage[i + 9] == 0x61 && bufimage[i + 10] == 0x74 && bufimage[i + 11] == 0x61) {
							break;
						}
					}
					m_mp3jake.EnableWindow(FALSE);
					if (i != 0x300000) {
						m_mp3jake.EnableWindow(TRUE);
					}
				}ff.Close();
			}
		}
		else {
			if (mode == 19)filen = filen.Left(5);
			play();
		}

	}
}


template<int Radius>
static inline float Lanczos(float x)
{
	if (x == 0.0) return 1.0;
	if (x <= -Radius || x >= Radius) return 0.0;
	float pi_x = x * M_PI;
	return Radius * sin(pi_x) * sin(pi_x / Radius) / (pi_x * pi_x);
}

const int FilterRadius = 3;

static inline void Resample(const float* source, size_t src_len, float* result, size_t dest_len) {
	if (src_len == dest_len) {
		memcpy(result, source, src_len * sizeof(float));
		return;
	}

	float scale = (float)src_len / (float)dest_len;
	for (size_t i = 0; i < dest_len; i++) {
		float src_pos = i * scale;
		size_t src_idx = (size_t)src_pos;
		float frac = src_pos - src_idx;

		if (src_idx >= src_len - 1) {
			result[i] = source[src_len - 1];
		}
		else {
			result[i] = source[src_idx] * (1.0f - frac) + source[src_idx + 1] * frac;
		}
	}
}

double hanWindow(double in, double i, double minIndex, double maxIndex) {
	if (i < minIndex || i > maxIndex) return 0.0;
	double window = 0.5 * (1.0 - cos(2.0 * 3.14159265359 * (i - minIndex) / (maxIndex - minIndex)));
	return in * window;
}

//スペアナ表示
ULONG PlayCursor = 0, WriteCursor = 0, PlayCursor2 = 0;

double goertzel(const float* data, int N, double target_freq, double sample_rate) {
	double s_prev = 0.0, s_prev2 = 0.0;
	double normalized_freq = 2.0 * M_PI * target_freq / sample_rate;
	double coeff = 2.0 * cos(normalized_freq);
	for (int i = 0; i < N; ++i) {
		double s = data[i] + coeff * s_prev - s_prev2;
		s_prev2 = s_prev;
		s_prev = s;
	}
	return s_prev2 * s_prev2 + s_prev * s_prev - coeff * s_prev * s_prev2;
}

#define BUFSZ1_2 (BUFSZ1 * 4)

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}
void COggDlg::Speana()
{
	if (savedata.speanamode && savedata.speananum == 2) {

		int i, j, d;
		double dt, dta;
		locs = loc;

		int maxBufferSize = (int)(BUFSZ1_2 * (384000 / 44100.0));
		int actualBufferSize = (int)(BUFSZ1_2 * (wavbit / 44100.0));
		int bufferSize = min(actualBufferSize, maxBufferSize);

		if (bufferSize <= 0) bufferSize = BUFSZ1_2;
		if (bufferSize > maxBufferSize) bufferSize = maxBufferSize;

		float* buf2 = nullptr;
		float* bufL = nullptr;
		float* bufR = nullptr;
		short* buf3 = nullptr;
		float* buf3f = nullptr;
		float* buf3f0 = nullptr;

		try {
			buf2 = new float[bufferSize * 2];
			bufL = new float[bufferSize * 2];
			bufR = new float[bufferSize * 2];
			buf3 = new short[bufferSize * 2];
			buf3f = new float[bufferSize * 2];
			buf3f0 = new float[bufferSize * 2];
		}
		catch (std::bad_alloc&) {
			if (buf2) delete[] buf2;
			if (bufL) delete[] bufL;
			if (bufR) delete[] bufR;
			if (buf3) delete[] buf3;
			if (buf3f) delete[] buf3f;
			if (buf3f0) delete[] buf3f0;
			bufferSize = BUFSZ1_2;
			buf2 = new float[bufferSize * 2];
			bufL = new float[bufferSize * 2];
			bufR = new float[bufferSize * 2];
			buf3 = new short[bufferSize * 2];
			buf3f = new float[bufferSize * 2];
			buf3f0 = new float[bufferSize * 2];
		}

		Int24* buf324;
		DWORD* buf332;
		LONGLONG* buf364;
		short* buf4; buf4 = (short*)buf3;
		int bui;

		HRESULT rett;
		if (m_dsb) rett = m_dsb->GetCurrentPosition(&PlayCursor, &WriteCursor);
		if (rett == DS_OK) { PlayCursor2 = PlayCursor; }
		else { PlayCursor = PlayCursor2; }
		if (PlayCursor > OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM) PlayCursor = 0;

		memcpy(bufwav3 + (OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM), bufwav3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM);
		memcpy((char*)buf3, bufwav3 + PlayCursor, bufferSize * (wavsam / 8));

		buf324 = (Int24*)buf3;
		buf332 = (DWORD*)buf3;
		buf364 = (LONGLONG*)buf3;
		double lll = 1;

		switch (wavsam) {
		case 64:
			for (i = 0; i < bufferSize / 8; i++) {
				buf3[i] = (short)(buf364[i] / ((LONGLONG)65536L * (LONGLONG)65536L));
			}
			lll = 8;
			break;
		case 32:
			for (i = 0; i < bufferSize / 4; i++) {
				buf3[i] = (short)(buf332[i] / ((ULONG)65536L));
			}
			lll = 4;
			break;
		case 24:
			for (i = 0; i < bufferSize / 3; i++) {
				buf3[i] = (short)(((int)buf324[i]) / 256);
			}
			lll = 3;
			break;
		case 16:
			lll = 2;
			break;
		}

		int sourceSamples = (int)(bufferSize / lll);
		for (int kl = 0; kl < sourceSamples && kl < BUFSZ1_2 * 3; kl++) {
			buf3f0[kl] = (float)buf3[kl];
		}

		Resample(buf3f0, sourceSamples, buf3f, BUFSZ1_2);
		for (int kl = 0; kl < BUFSZ1_2; kl++) {
			buf3[kl] = (short)buf3f[kl];
		}

		for (i = 0; i < BUFSZ1_2 / 2; i++) {
			bui = buf3[i * 2];
			bui += buf3[i * 2 + 1];
			bui /= 2;
			buf2[i] = bui;
			bufL[i] = buf3[i * 2];
			bufR[i] = buf3[i * 2 + 1];
		}

		// 音程ごとに波形を描画するための処理
		static const double noteFrequencies[89] = {
			27.50, 29.14, 30.87, 32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91,
			55.00, 58.27, 61.74, 65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83,
			110.00, 116.54, 123.47, 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65,
			220.00, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30,
			440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61,
			880.00, 932.33, 987.77, 1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22,
			1760.00, 1864.66, 1975.53, 2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44,
			3520.00, 3729.31, 3951.07, 4186.01
		};

		const int NUM_NOTES = 88;
		int N = BUFSZ1_2;
		std::vector<float> goertzelInputL(N);
		std::vector<float> goertzelInputR(N);
		if (m_st.GetCheck() == FALSE) {
			for (int n = 0; n < N; ++n) {
				double w = 0.5 - 0.5 * cos(2.0 * M_PI * n / (N - 1));
				goertzelInputL[n] = (float)(buf2[n] * w / 32768.0f);
			}
		}
		else {
			for (int n = 0; n < N; ++n) {
				double w = 0.5 - 0.5 * cos(2.0 * M_PI * n / (N - 1));
				goertzelInputL[n] = (float)(bufL[n] * w / 32768.0f);
			}
			for (int n = 0; n < N; ++n) {
				double w = 0.5 - 0.5 * cos(2.0 * M_PI * n / (N - 1));
				goertzelInputR[n] = (float)(bufR[n] * w / 32768.0f);
			}
		}
		double sampleRate = (double)wavbit;

		for (i = 0; i < 88; i++) {
			d = (int)(goertzelInputL[i]);
			int dm1 = d / 2;
			int dm2 = d / 3;
			int dm3 = d / 4;
			int dp1 = d / 2;
			int dp2 = d / 3;
			int dp3 = d / 4;
			if (i - 3 >= 0 && i - 3 < 88) goertzelInputL[i - 3] = goertzelInputL[i - 3] > dm3 ? goertzelInputL[i - 3] : dm3;
			if (i - 2 >= 0 && i - 2 < 88) goertzelInputL[i - 2] = goertzelInputL[i - 2] > dm2 ? goertzelInputL[i - 2] : dm2;
			if (i - 1 >= 0 && i - 1 < 88) goertzelInputL[i - 1] = goertzelInputL[i - 1] > dm1 ? goertzelInputL[i - 1] : dm1;
			if (i >= 0 && i < 88) goertzelInputL[i] = goertzelInputL[i] > d ? goertzelInputL[i] : d;
			if (i + 3 >= 0 && i + 3 < 88) goertzelInputL[i + 3] = goertzelInputL[i + 3] > dp3 ? goertzelInputL[i + 3] : dp3;
			if (i + 2 >= 0 && i + 2 < 88) goertzelInputL[i + 2] = goertzelInputL[i + 2] > dp2 ? goertzelInputL[i + 2] : dp2;
			if (i + 1 >= 0 && i + 1 < 88) goertzelInputL[i + 1] = goertzelInputL[i + 1] > dp1 ? goertzelInputL[i + 1] : dp1;
			if (m_st.GetCheck() == TRUE) {
				d = goertzelInputR[i];
				int dm1 = d / 2;
				int dm2 = d / 3;
				int dm3 = d / 4;
				int dp1 = d / 2;
				int dp2 = d / 3;
				int dp3 = d / 4;
				if (i - 3 >= 0 && i - 3 < 88) goertzelInputR[i - 3] = goertzelInputR[i - 3] > dm3 ? goertzelInputR[i - 3] : dm3;
				if (i - 2 >= 0 && i - 2 < 88) goertzelInputR[i - 2] = goertzelInputR[i - 2] > dm2 ? goertzelInputR[i - 2] : dm2;
				if (i - 1 >= 0 && i - 1 < 88) goertzelInputR[i - 1] = goertzelInputR[i - 1] > dm1 ? goertzelInputR[i - 1] : dm1;
				if (i >= 0 && i < 88) goertzelInputR[i] = goertzelInputR[i] > d ? goertzelInputR[i] : d;
				if (i + 3 >= 0 && i + 3 < 88) goertzelInputR[i + 3] = goertzelInputR[i + 3] > dp3 ? goertzelInputR[i + 3] : dp3;
				if (i + 2 >= 0 && i + 2 < 88) goertzelInputR[i + 2] = goertzelInputR[i + 2] > dp2 ? goertzelInputR[i + 2] : dp2;
				if (i + 1 >= 0 && i + 1 < 88) goertzelInputR[i + 1] = goertzelInputR[i + 1] > dp1 ? goertzelInputR[i + 1] : dp1;
			}
		}

		for (i = 0; i < 88; i++) {
			if (m_st.GetCheck() == FALSE) {
				double freq = noteFrequencies[i];
				double power = goertzel(goertzelInputL.data(), N, freq, sampleRate);
				power *= pow(freq, 1.2);
				int d = (int)(10.0 * log10(power + 1e-12));
				if (d > 80) d = 80; else if (d < 0) d = 0;
				if (spelv[i] < d) { spelv[i] = d; spetm[i] = 0; }
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, 2 * 4, (spelv[i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - d) * 4, 2 * 4, (d + 1) * 4, RGB(0, 255, 0));
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, 2 * 4, 1 * 4, RGB(0, 255, 0));
			}
			else {
				double freq = noteFrequencies[i];
				double power = goertzel(goertzelInputL.data(), N, freq, sampleRate);
				power *= pow(freq, 1.2);
				int d = (int)(10.0 * log10(power + 1e-12));
				if (d > 80) d = 80; else if (d < 0) d = 0;
				if (spelv[100 + i] < d) { spelv[100 + i] = d; spetm[100 + i] = 0; }
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, (spelv[100 + i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, RGB(0, 255, 0));
				freq = noteFrequencies[i];
				power = goertzel(goertzelInputR.data(), N, freq, sampleRate);
				power *= pow(freq, 1.2);
				d = (int)(10.0 * log10(power + 1e-12));
				if (d > 80) d = 80; else if (d < 0) d = 0;
				if (spelv[200 + i] < d) { spelv[200 + i] = d; spetm[200 + i] = 0; }
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, (spelv[200 + i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, RGB(0, 255, 0));

				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, 1 * 4, RGB(0, 255, 0));
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, 1 * 4, RGB(0, 255, 0));

				dc.FillSolidRect((21 * 8 + 88) * 4, 16 * 4, 1 * 4, 81 * 4, RGB(0, 255, 255));
			}
		}
		// メモリ解放
		delete[] buf2;
		delete[] bufL;
		delete[] bufR;
		delete[] buf3;
		delete[] buf3f;
		delete[] buf3f0;
	}
	else if (savedata.speanamode && savedata.speananum == 1) {
		int i, j, d;
		double dt, dta;
		//	if(loc==locs) return;
		locs = loc;

		//ステレオ44.1k(char)→モノラル44.1k(short)へ
		short buf2[BUFSZ1 * 5], bufL[BUFSZ1 * 5], bufR[BUFSZ1 * 5], buf3[BUFSZ1 * 5];
		float buf3f[BUFSZ1 * 3], buf3f0[BUFSZ1 * 3];
		Int24* buf324;
		DWORD* buf332;
		LONGLONG* buf364;
		short* buf4; buf4 = (short*)buf3;
		int bui;
		//プレイ位置から獲得
		HRESULT rett;
		if (m_dsb)rett = m_dsb->GetCurrentPosition(&PlayCursor, &WriteCursor);//再生位置取得
		if (rett == DS_OK) { PlayCursor2 = PlayCursor; }
		else { PlayCursor = PlayCursor2; }
		if (PlayCursor > OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM) PlayCursor = 0;
		memcpy(bufwav3 + (OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM), bufwav3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM);
		memcpy((char*)buf3, bufwav3 + PlayCursor, ((double)BUFSZ1) * (wavbit / 44100.0));

		buf324 = (Int24*)buf3;
		buf332 = (DWORD*)buf3;
		buf364 = (LONGLONG*)buf3;
		double lll = 1;
		switch (wavsam) {
		case 64:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 4.0; i++) {
				buf3[i] = buf364[i] / ((LONGLONG)65536L * (LONGLONG)65556L);
			}
			lll = 4;
			break;
		case 32:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 2.0; i++) {
				buf3[i] = buf332[i] / ((ULONG)65536L);
			}
			lll = 2;
			break;
		case 24:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 1.5; i++) {
				buf3[i] = buf324[i] / 256;
			}
			lll = 1.5;
			break;
		}

		for (int kl = 0; kl < BUFSZ1 * (wavbit / 44100.0) / lll; kl++) {
			buf3f0[kl] = buf3[kl];
		}
		Resample(buf3f0, BUFSZ1 * (wavbit / 44100.0) / lll, buf3f, (double)BUFSZ1);
		for (int kl = 0; kl < BUFSZ1; kl++) {
			buf3[kl] = buf3f[kl];
		}

		//ステレオ→モノラル変換
		for (i = 0; i < BUFSZ1 / 2; i++) {
			bui = buf3[i * 2];
			bui += buf3[i * 2 + 1];
			bui /= 2;
			buf2[i] = bui;
			bufL[i] = buf3[i * 2];
			bufR[i] = buf3[i * 2 + 1];
		}

		//FFTの準備 - より高精度なFFT処理
		if (m_st.GetCheck() == FALSE) {
			// モノラル処理
			for (i = 0; i < BUFSZ1; i++) {
				aFFT2[i] = hanWindow(((int)buf2[i]), i, 0, BUFSZH1) * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZ1, -1, aFFT2, ipTab2, wTab2); // 高速離散サイン変換
		}
		else {
			// ステレオ処理 - 左チャンネル
			for (i = 0; i < BUFSZH1; i++) {
				aFFT2[i] = hanWindow(((int)bufL[i]), i, 0, BUFSZH1) * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZH1, -1, aFFT2, ipTab2, wTab2);

			// ステレオ処理 - 右チャンネル
			for (i = 0; i < BUFSZH1; i++) {
				aFFT2a[i] = hanWindow(((int)bufR[i]), i, 0, BUFSZH1) * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZH1, -1, aFFT2a, ipTab2, wTab2);
		}

		// 直流成分＆低周波ノイズをカット
		for (i = 0; i < 3; i++) {
			aFFT2[i] = 0;
			aFFT2a[i] = 0;
		}

		// 88鍵ピアノの改良された周波数帯域設計
		const int NUM_KEYS = 88;
		double fs = wavbit; // サンプリングレート
		int N = BUFSZ1;     // FFTサイズ
		double key_freqs[NUM_KEYS];
		double band_edges[NUM_KEYS + 1];
		int band_bins[NUM_KEYS + 1];
		double band_widths[NUM_KEYS];

		// 音階中心周波数計算 (A0=27.5Hz から C8=4186Hz)
		for (int i = 0; i < NUM_KEYS; ++i) {
			key_freqs[i] = 27.5 * pow(2.0, i / 12.0);
		}

		// 改良された帯域境界計算 - 低周波域で細かい、高周波域で広い
		band_edges[0] = 20.0; // 最低周波数20Hz
		for (int i = 1; i < NUM_KEYS; ++i) {
			// 低周波域（最初の24鍵）では細かい帯域
			if (i < 24) {
				band_edges[i] = key_freqs[i - 1] + (key_freqs[i] - key_freqs[i - 1]) * 0.3;
			}
			// 中周波域（24-60鍵）では標準的な帯域
			else if (i < 60) {
				band_edges[i] = (key_freqs[i - 1] + key_freqs[i]) / 2.0;
			}
			// 高周波域（60鍵以降）では広い帯域でカット
			else {
				band_edges[i] = key_freqs[i - 1] + (key_freqs[i] - key_freqs[i - 1]) * 0.8;
			}
		}
		band_edges[NUM_KEYS] = fs / 2.0; // ナイキスト周波数

		// 境界をbin番号に変換
		for (int i = 0; i <= NUM_KEYS; ++i) {
			int bin = (int)floor(band_edges[i] * N / fs);
			if (bin < 0) bin = 0;
			if (bin > N / 2 - 1) bin = N / 2 - 1;
			band_bins[i] = bin;
		}

		// 帯域幅を計算
		for (int i = 0; i < NUM_KEYS; ++i) {
			band_widths[i] = band_edges[i + 1] - band_edges[i];
		}

		// スペクトル解析と描画データ生成
		double dd = 1;
		int dtbl[NUM_KEYS], dtatbl[NUM_KEYS];

		// 最大値を追跡して正規化用に使用
		double max_spectrum_value = 1e-10;

		for (i = 0; i < NUM_KEYS; i++) {
			dt = dta = 0;
			d = 0;
			int bin_start = band_bins[i];
			int bin_end = band_bins[i + 1];
			if (bin_end > N / 2) bin_end = N / 2;
			if (bin_start < 0) bin_start = 0;

			// 帯域内の最大値を取得
			if (m_st.GetCheck() == FALSE) {
				// モノラル処理
				for (j = bin_start; j < bin_end; j++) {
					if (dt < fabs(aFFT2[j])) {
						dt = fabs(aFFT2[j]);
					}
				}

				// 周波数帯域に応じたゲイン調整 - 低周波域のゲインを大幅に削減
				double freq_gain = 1.0;
				if (i < 24) {
					freq_gain = 1.0 + (24 - i) * 0.03; // さらに低く
				}
				else if (i < 60) {
					freq_gain = 1.0 + (60 - i) * 0.02;
				}
				else {
					freq_gain = 0.2 + (88 - i) * 0.01;
				}

				dt *= freq_gain * (double)HIGHDIV * 2.0;
				dt = dt / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;

				// 最大値を更新
				if (dt > max_spectrum_value) {
					max_spectrum_value = dt;
				}
			}
			else {
				// ステレオ処理 - 左チャンネル
				for (j = bin_start; j < bin_end; j++) {
					if (dt < fabs(aFFT2[j])) { dt = fabs(aFFT2[j]); }
					if (dta < fabs(aFFT2a[j])) { dta = fabs(aFFT2a[j]); }
				}

				// 周波数帯域に応じたゲイン調整
				double freq_gain = 1.0;
				if (i < 24) {
					freq_gain = 3.0 + (24 - i) * 0.15;
				}
				else if (i < 60) {
					freq_gain = 1.0 + (60 - i) * 0.03;
				}
				else {
					freq_gain = 0.2 + (88 - i) * 0.015;
				}

				dt *= freq_gain * (double)HIGHDIV * 2.0;
				dta *= freq_gain * (double)HIGHDIV * 2.0;
				dt = dt / (BUFSZ1 / 2048 / 2);
				dta = dta / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;
				dta = dta * savedata.wup;

				// 最大値を更新
				if (dt > max_spectrum_value) {
					max_spectrum_value = dt;
				}
				if (dta > max_spectrum_value) {
					max_spectrum_value = dta;
				}
			}
		}

		// 正規化係数を計算（グラフの高さ96を超えないように）
		double normalization_factor = 1.0;
		if (max_spectrum_value > 0) {
			normalization_factor = 85.0 / max_spectrum_value; // より安全なマージンで95以下に制限
		}

		// 正規化してdtblとdtatblに格納
		for (i = 0; i < NUM_KEYS; i++) {
			dt = dta = 0;
			d = 0;
			int bin_start = band_bins[i];
			int bin_end = band_bins[i + 1];
			if (bin_end > N / 2) bin_end = N / 2;
			if (bin_start < 0) bin_start = 0;

			if (m_st.GetCheck() == FALSE) {
				// モノラル処理
				for (j = bin_start; j < bin_end; j++) {
					if (dt < fabs(aFFT2[j])) {
						dt = fabs(aFFT2[j]);
					}
				}

				// 周波数帯域に応じたゲイン調整
				double freq_gain = 1.0;
				if (i < 24) {
					freq_gain = 1.0 + (24 - i) * 0.03; // さらに低く
				}
				else if (i < 60) {
					freq_gain = 1.0 + (60 - i) * 0.02;
				}
				else {
					freq_gain = 0.2 + (88 - i) * 0.01;
				}

				dt *= freq_gain * (double)HIGHDIV * 2.0;
				dt = dt / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;

				// 正規化適用
				dt *= normalization_factor;

				if (dt > 0) {
					// 改良された対数変換 - スケーリング係数を調整して95以下に制限
					d = (int)(log10(dt * dt + 1e-10) * (75 / 5)); // 80から75に変更
				}
				d = d * dd;
				if (d > 95) d = 95; else if (d < 0) d = 0; // 96から95に変更
				dtbl[i] = d;
			}
			else {
				// ステレオ処理 - 左チャンネル
				for (j = bin_start; j < bin_end; j++) {
					if (dt < fabs(aFFT2[j])) { dt = fabs(aFFT2[j]); }
					if (dta < fabs(aFFT2a[j])) { dta = fabs(aFFT2a[j]); }
				}

				// 周波数帯域に応じたゲイン調整
				double freq_gain = 1.0;
				if (i < 24) {
					freq_gain = 1.0 + (24 - i) * 0.03; // さらに低く
				}
				else if (i < 60) {
					freq_gain = 1.0 + (60 - i) * 0.02;
				}
				else {
					freq_gain = 0.2 + (88 - i) * 0.01;
				}

				dt *= freq_gain * (double)HIGHDIV * 2.0;
				dta *= freq_gain * (double)HIGHDIV * 2.0;
				dt = dt / (BUFSZ1 / 2048 / 2);
				dta = dta / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;
				dta = dta * savedata.wup;

				// 正規化適用
				dt *= normalization_factor;
				dta *= normalization_factor;

				// 左チャンネル
				d = 0;
				if (dt > 0) {
					d = (int)(log10(dt * dt + 1e-10) * (75 / 5)); // 80から75に変更
				}
				d = d * dd;
				if (d > 95) d = 95; else if (d < 0) d = 0; // 96から95に変更
				dtbl[i] = d;

				// 右チャンネル
				d = 0;
				if (dta > 0) {
					d = (int)(log10(dta * dta + 1e-10) * (75 / 5)); // 80から75に変更
				}
				d = d * dd;
				if (d > 95) d = 95; else if (d < 0) d = 0; // 96から95に変更
				dtatbl[i] = d;
			}
		}

		// スムージング処理
		for (i = 0; i < NUM_KEYS; i++) {
			d = dtbl[i];
			double d2 = 1.0;

			// 周波数帯域に応じたスムージング強度調整
			if (i < 24) {
				// 低周波域：強いスムージングで細かい波形を強調
				d2 = 1.0;
			}
			else if (i < 60) {
				// 中周波域：標準スムージング
				d2 = 1.0;
			}
			else {
				// 高周波域：弱いスムージングでカット効果
				d2 = 1.0;
			}

			d = (int)((double)d * d2);
			dtbl[i] = d;
			d = dtbl[i];

			// 改良されたスムージング係数
			int dm1 = d / 2;
			int dm2 = d / 3;
			int dm3 = d / 4;
			int dp1 = d / 2;
			int dp2 = d / 3;
			int dp3 = d / 4;

			// スムージング適用
			if (i - 3 >= 0 && i - 3 < NUM_KEYS) dtbl[i - 3] = dtbl[i - 3] > dm3 ? dtbl[i - 3] : dm3;
			if (i - 2 >= 0 && i - 2 < NUM_KEYS) dtbl[i - 2] = dtbl[i - 2] > dm2 ? dtbl[i - 2] : dm2;
			if (i - 1 >= 0 && i - 1 < NUM_KEYS) dtbl[i - 1] = dtbl[i - 1] > dm1 ? dtbl[i - 1] : dm1;
			if (i >= 0 && i < NUM_KEYS) dtbl[i] = dtbl[i] > d ? dtbl[i] : d;
			if (i + 3 >= 0 && i + 3 < NUM_KEYS) dtbl[i + 3] = dtbl[i + 3] > dp3 ? dtbl[i + 3] : dp3;
			if (i + 2 >= 0 && i + 2 < NUM_KEYS) dtbl[i + 2] = dtbl[i + 2] > dp2 ? dtbl[i + 2] : dp2;
			if (i + 1 >= 0 && i + 1 < NUM_KEYS) dtbl[i + 1] = dtbl[i + 1] > dp1 ? dtbl[i + 1] : dp1;

			if (m_st.GetCheck() == TRUE) {
				// ステレオ右チャンネルのスムージング
				d = dtatbl[i];
				d = (int)((double)d * d2);
				dtatbl[i] = d;
				d = dtatbl[i];

				int dm1 = d / 2;
				int dm2 = d / 3;
				int dm3 = d / 4;
				int dp1 = d / 2;
				int dp2 = d / 3;
				int dp3 = d / 4;

				if (i - 3 >= 0 && i - 3 < NUM_KEYS) dtatbl[i - 3] = dtatbl[i - 3] > dm3 ? dtatbl[i - 3] : dm3;
				if (i - 2 >= 0 && i - 2 < NUM_KEYS) dtatbl[i - 2] = dtatbl[i - 2] > dm2 ? dtatbl[i - 2] : dm2;
				if (i - 1 >= 0 && i - 1 < NUM_KEYS) dtatbl[i - 1] = dtatbl[i - 1] > dm1 ? dtatbl[i - 1] : dm1;
				if (i >= 0 && i < NUM_KEYS) dtatbl[i] = dtatbl[i] > d ? dtatbl[i] : d;
				if (i + 3 >= 0 && i + 3 < NUM_KEYS) dtatbl[i + 3] = dtatbl[i + 3] > dp3 ? dtatbl[i + 3] : dp3;
				if (i + 2 >= 0 && i + 2 < NUM_KEYS) dtatbl[i + 2] = dtatbl[i + 2] > dp2 ? dtatbl[i + 2] : dp2;
				if (i + 1 >= 0 && i + 1 < NUM_KEYS) dtatbl[i + 1] = dtatbl[i + 1] > dp1 ? dtatbl[i + 1] : dp1;
			}
		}

		// 改良された描画処理
		for (i = 0; i < NUM_KEYS; i++) {
			if (m_st.GetCheck() == FALSE) {
				// モノラル描画
				d = dtbl[i];
				if (spelv[i] < d) { spelv[i] = d; spetm[i] = 0; }

				COLORREF peak_color, hold_color;
				peak_color = RGB(0, 255, 0);
				hold_color = RGB(0, 128, 0);

				// 帯域幅に応じた描画幅調整
				int bar_width = 2;
				if (i < 24) bar_width = 3; // 低周波域は太く
				else if (i > 60) bar_width = 1; // 高周波域は細く

				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, bar_width * 4, (spelv[i] + 1) * 4, hold_color);
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - d) * 4, bar_width * 4, (d + 1) * 4, peak_color);
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, bar_width * 4, 1 * 4, peak_color);
			}
			else {
				// ステレオ描画 - 左チャンネル
				d = dtbl[i];
				if (spelv[100 + i] < d) { spelv[100 + i] = d; spetm[100 + i] = 0; }

				// 左チャンネル用色
				COLORREF left_peak = RGB(0, 255, 0);
				COLORREF left_hold = RGB(0, 128, 0);

				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, (spelv[100 + i] + 1) * 4, left_hold);
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, left_peak);

				// ステレオ描画 - 右チャンネル
				d = dtatbl[i];
				if (spelv[200 + i] < d) { spelv[200 + i] = d; spetm[200 + i] = 0; }

				// 右チャンネル用色
				COLORREF right_peak = RGB(0, 255, 0);
				COLORREF right_hold = RGB(0, 128, 0);

				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, (spelv[200 + i] + 1) * 4, right_hold);
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, right_peak);

				// ピークライン
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, 1 * 4, left_peak);
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, 1 * 4, right_peak);

				// 中央区切り線
				dc.FillSolidRect((21 * 8 + 88) * 4, 16 * 4, 1 * 4, 81 * 4, RGB(0, 255, 255));
			}
		}
	}
	else {
		int i, j, d;
		double dt, dta;
		//	if(loc==locs) return;
		locs = loc;

		//ステレオ44.1k(char)→モノラル44.1k(short)へ
		short buf2[BUFSZ1 * 5], bufL[BUFSZ1 * 5], bufR[BUFSZ1 * 5], buf3[BUFSZ1 * 5];
		float buf3f[BUFSZ1 * 3], buf3f0[BUFSZ1 * 3];
		Int24* buf324;
		DWORD* buf332;
		LONGLONG* buf364;
		short* buf4; buf4 = (short*)buf3;
		int bui;
		//プレイ位置から獲得
		HRESULT rett;
		if (m_dsb)rett = m_dsb->GetCurrentPosition(&PlayCursor, &WriteCursor);//再生位置取得
		if (rett == DS_OK) { PlayCursor2 = PlayCursor; }
		else { PlayCursor = PlayCursor2; }
		if (PlayCursor > OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM) PlayCursor = 0;
		memcpy(bufwav3 + (OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM), bufwav3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM);
		memcpy((char*)buf3, bufwav3 + PlayCursor, ((double)BUFSZ1) * (wavbit / 44100.0));


		buf324 = (Int24*)buf3;
		buf332 = (DWORD*)buf3;
		buf364 = (LONGLONG*)buf3;
		double lll = 1;
		switch (wavsam) {
		case 64:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 4.0; i++) {
				buf3[i] = buf364[i] / ((LONGLONG)65536L * (LONGLONG)65556L);
			}
			lll = 4;
			break;
		case 32:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 2.0; i++) {
				buf3[i] = buf332[i] / ((ULONG)65536L);
			}
			lll = 2;
			break;
		case 24:
			for (i = 0; i < ((double)BUFSZ1) * (wavbit / 44100.0) / 1.5; i++) {
				buf3[i] = buf324[i] / 256;
			}
			lll = 1.5;
			break;
		}

		for (int kl = 0; kl < BUFSZ1 * (wavbit / 44100.0) / lll; kl++) {
			buf3f0[kl] = buf3[kl];
		}
		Resample(buf3f0, BUFSZ1 * (wavbit / 44100.0) / lll, buf3f, (double)BUFSZ1);
		for (int kl = 0; kl < BUFSZ1; kl++) {
			buf3[kl] = buf3f[kl];
		}

		//	default:
		for (i = 0; i < BUFSZ1 / 2; i++) {
			bui = buf3[i * 2];
			bui += buf3[i * 2 + 1];
			bui /= 2;
			buf2[i] = bui;
			bufL[i] = buf3[i * 2];
			bufR[i] = buf3[i * 2 + 1];
		}
		;
		//	}
			//FFTの準備
		if (m_st.GetCheck() == FALSE) {
			for (i = 0; i < BUFSZ1 / 2; i++) {
				aFFT2[i] = ((int)buf2[i]) * fnWFilter[i * HIGHDIV * 2] * (1.0 / 32768);
				aFFT2[i + BUFSZ1 / 2] = ((int)buf2[i + BUFSZ1 / 8]) * fnWFilter[BUFSZ1 / 2 - (i + 1) * HIGHDIV * 2] * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZ1, -1, aFFT2, ipTab2, wTab2); // 高速離散サイン変換
		}
		else {
			for (i = 0; i < BUFSZH1 / 2; i++) { //2048 /4 512
				aFFT2[i] = hanWindow(((int)bufL[i]), i, 0, BUFSZH1 / 2) * (1.0 / 32768);
				aFFT2[i + BUFSZH1 / 2] = hanWindow(((int)bufL[i + BUFSZH1 / 8]), i, 0, BUFSZH1 / 2) * (1.0 / 32768);;// *fnWFilter[BUFSZ1 / 2 - (i + 1) * HIGHDIV * 2] * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZH1, -1, aFFT2, ipTab2, wTab2); // 高速離散サイン変換
			for (i = 0; i < BUFSZH1 / 2; i++) { //2048 /4 512
				aFFT2a[i] = hanWindow(((int)bufR[i]), i, 0, BUFSZ1 / 2) * (1.0 / 32768);;
				aFFT2a[i + BUFSZH1 / 2] = hanWindow(((int)bufR[i + BUFSZH1 / 8]), i, 0, BUFSZH1 / 2) * (1.0 / 32768);;// *fnWFilter[BUFSZ1 / 2 - (i + 1) * HIGHDIV * 2] * (1.0 / 32768);
			}
			ipTab2[0] = 0;
			ddst(BUFSZH1, -1, aFFT2a, ipTab2, wTab2); // 高速離散サイン変換
		}
		// 直流成分＆低周波ノイズをカット
		for (i = 0; i < 2; i++) {
			aFFT2[i] = 0;
			aFFT2a[i] = 0;
		}

		// スペクトル描画
		//	dc.FillSolidRect(0,0,300,100,RGB(0,0,0));
		double dd = 1;
		double d4 = 1;//wavbit / 44100.0;
		int dtbl[88], dtatbl[88];
		for (i = 0; i < 88; i++) {
			dt = dta = 0;
			d = 0;
			if (m_st.GetCheck() == FALSE) {
				for (j = logtbl[i] / d4; j < logtbl[i + 1] / d4; j++)
					if (dt < (aFFT2[j])) {
						dt = (aFFT2[j]); if (dt < 0) dt = 0;
					}// 区間内の最大値を採用
				dt *= (double)HIGHDIV * ((double)(28 + i / 4) / 100.0) * 2.0;
				// 単位を dB に
				dt = dt / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;
				if (dt > 0) d = (int)(log10(dt * dt) * (80 / 5));
				d = d * dd;
				if (d > 80) d = 80; else if (d < 0) d = 0;
				dtbl[i] = d;
			}
			else {
				for (j = logtbl[i] / d4; j < logtbl[i + 1] / d4; j++) {
					if (dt < (aFFT2[j])) { dt = (aFFT2[j]); if (dt < 0) dt = 0; } // 区間内の最大値を採用
					if (dta < (aFFT2a[j])) { dta = (aFFT2a[j]); if (dta < 0) dta = 0; } // 区間内の最大値を採用
				}
				dt *= (double)HIGHDIV * ((double)(28 + i / 4) / 100.0) * 2.0;
				dta *= (double)HIGHDIV * ((double)(28 + i / 4) / 100.0) * 2.0;
				// 単位を dB に
				dt = dt / (BUFSZ1 / 2048 / 2);
				dta = dta / (BUFSZ1 / 2048 / 2);
				dt = dt * savedata.wup;
				dta = dta * savedata.wup;
				d = 0;
				if (dt > 0) d = (int)(log10(dt * dt) * (80 / 5));
				d = d * dd;
				if (d > 80) d = 80; else if (d < 0) d = 0;
				dtbl[i] = d;
				d = 0;
				if (dta > 0) d = (int)(log10(dta * dta) * (80 / 5));
				d = d * dd;
				if (d > 80) d = 80; else if (d < 0) d = 0;
				dtatbl[i] = d;
			}
			dd += 0.0005;
		}

		for (i = 0; i < 88; i++) {
			d = dtbl[i];
			double d2 = 1.0;

			d = (int)((double)d * d2);
			dtbl[i] = d;
			d = dtbl[i];
			int dm1 = d / 2;
			int dm2 = d / 3;
			int dm3 = d / 4;
			int dp1 = d / 2;
			int dp2 = d / 3;
			int dp3 = d / 4;
			if (i - 3 >= 0 && i - 3 < 88) dtbl[i - 3] = dtbl[i - 3] > dm3 ? dtbl[i - 3] : dm3;
			if (i - 2 >= 0 && i - 2 < 88) dtbl[i - 2] = dtbl[i - 2] > dm2 ? dtbl[i - 2] : dm2;
			if (i - 1 >= 0 && i - 1 < 88) dtbl[i - 1] = dtbl[i - 1] > dm1 ? dtbl[i - 1] : dm1;
			if (i >= 0 && i < 88) dtbl[i] = dtbl[i] > d ? dtbl[i] : d;
			if (i + 3 >= 0 && i + 3 < 88) dtbl[i + 3] = dtbl[i + 3] > dp3 ? dtbl[i + 3] : dp3;
			if (i + 2 >= 0 && i + 2 < 88) dtbl[i + 2] = dtbl[i + 2] > dp2 ? dtbl[i + 2] : dp2;
			if (i + 1 >= 0 && i + 1 < 88) dtbl[i + 1] = dtbl[i + 1] > dp1 ? dtbl[i + 1] : dp1;
			if (m_st.GetCheck() == TRUE) {
				d = dtatbl[i];
				d = (int)((double)d * d2);
				dtatbl[i] = d;
				d = dtatbl[i];
				int dm1 = d / 2;
				int dm2 = d / 3;
				int dm3 = d / 4;
				int dp1 = d / 2;
				int dp2 = d / 3;
				int dp3 = d / 4;
				if (i - 3 >= 0 && i - 3 < 88) dtatbl[i - 3] = dtatbl[i - 3] > dm3 ? dtatbl[i - 3] : dm3;
				if (i - 2 >= 0 && i - 2 < 88) dtatbl[i - 2] = dtatbl[i - 2] > dm2 ? dtatbl[i - 2] : dm2;
				if (i - 1 >= 0 && i - 1 < 88) dtatbl[i - 1] = dtatbl[i - 1] > dm1 ? dtatbl[i - 1] : dm1;
				if (i >= 0 && i < 88) dtatbl[i] = dtatbl[i] > d ? dtatbl[i] : d;
				if (i + 3 >= 0 && i + 3 < 88) dtatbl[i + 3] = dtatbl[i + 3] > dp3 ? dtatbl[i + 3] : dp3;
				if (i + 2 >= 0 && i + 2 < 88) dtatbl[i + 2] = dtatbl[i + 2] > dp2 ? dtatbl[i + 2] : dp2;
				if (i + 1 >= 0 && i + 1 < 88) dtatbl[i + 1] = dtatbl[i + 1] > dp1 ? dtatbl[i + 1] : dp1;
			}
		}

		for (i = 0; i < 88; i++) {
			if (m_st.GetCheck() == FALSE) {
				d = dtbl[i];
				if (spelv[i] < d) { spelv[i] = d; spetm[i] = 0; }
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, 2 * 4, (spelv[i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - d) * 4, 2 * 4, (d + 1) * 4, RGB(0, 255, 0));
				dc.FillSolidRect((21 * 8 + i * 2) * 4, (96 - spelv[i]) * 4, 2 * 4, 1 * 4, RGB(0, 255, 0));
			}
			else {
				d = dtbl[i];
				if (spelv[100 + i] < d) { spelv[100 + i] = d; spetm[100 + i] = 0; }
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, (spelv[100 + i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, RGB(0, 255, 0));
				d = dtatbl[i];
				if (spelv[200 + i] < d) { spelv[200 + i] = d; spetm[200 + i] = 0; }
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, (spelv[200 + i] + 1) * 4, RGB(0, 128, 0));
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - d) * 4, 1 * 4, (d + 1) * 4, RGB(0, 255, 0));

				dc.FillSolidRect((21 * 8 + i) * 4, (96 - spelv[100 + i]) * 4, 1 * 4, 1 * 4, RGB(0, 255, 0));
				dc.FillSolidRect((21 * 8 + 89 + i) * 4, (96 - spelv[200 + i]) * 4, 1 * 4, 1 * 4, RGB(0, 255, 0));

				dc.FillSolidRect((21 * 8 + 88) * 4, 16 * 4, 1 * 4, 81 * 4, RGB(0, 255, 255));
			}
		}
	}
}

void COggDlg::OnButton5()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	if (fadeadd == 0.0)
	{
		fadeadd = -0.005f;
		fade = 1.0f;
	}
}


void COggDlg::moji(CString s, int x, int y, COLORREF rgb)
{
	CRect rect;
	HFONT fo;
	SIZE szinfo;
	fo = (HFONT)SelectObject(dc, hFont);
	SetTextColor(dc, rgb);
	SetBkColor(dc, RGB(0, 0, 0));
	dc.SetBkMode(TRANSPARENT);
	GetTextExtentPoint32(dc, s, s.GetLength(), &szinfo);
	if (savedata.ms2 <= ms2) {
		dc.TextOut(x * 4, y * 4, s, s.GetLength());
	}
	SelectObject(dc, fo);
}

int COggDlg::mojisub(CString s, int x, int y, COLORREF rgb)
{
	CRect rect;
	HFONT fo;
	CSize szinfo;
	fo = (HFONT)SelectObject(dcsub, hFont);
	SetTextColor(dcsub, rgb);
	SetBkColor(dcsub, RGB(0, 0, 0));
	SetBkMode(dcsub, TRANSPARENT);
	szinfo = dcsub.GetOutputTextExtent(s);
	if (savedata.ms2 <= ms2) {
		if (szinfo.cx < (MDC + 8) * 4)
			dcsub.FillSolidRect(0, 0, (MDC + 8) * 4, 30 * 4, RGB(0, 0, 0));
		else
			dcsub.FillSolidRect(0, 0, (szinfo.cx + MDC + 8) * 4, 30 * 4, RGB(0, 0, 0));
		dcsub.TextOut(x * 4, y * 4, s, s.GetLength());
		SelectObject(dcsub, fo);
	}
	return szinfo.cx;
}

void COggDlg::OnButton9_Folder()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CFolder* a = new CFolder(CWnd::FromHandle(GetSafeHwnd()));
	if (savedata.aero) {
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if (maini)::SetWindowPos(maini->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	CWnd::PostMessage(0x118);
	a->DoModal();
	Modec();
	char tmp[1024];
	_getcwd(tmp, 1000);
	_tchdir(karento2);
	CFile ab;
#if _UNICODE
	if (ab.Open(L"oggYSEDbgmu.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#else
	if (ab.Open("oggYSEDbgm.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#endif
		ab.Write(&savedata, sizeof(save));
		ab.Close();
	}
	_chdir(tmp);
	delete a;
	}

void COggDlg::OnButton12()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	Resize();
}

void COggDlg::OnCheck5()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_junji.SetCheck(0);
	m_random.SetCheck(1);
	savedata.random = 0;
}

void COggDlg::OnCheck6()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_junji.SetCheck(1);
	m_random.SetCheck(0);
	savedata.random = 1;
}

void COggDlg::OnButton14()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	randomf = 1;
	randomno = 0;
	playf = 0;
	loopcnt = 0;
	//	m_rund.EnableWindow(FALSE);
}

BOOL sek = FALSE;
extern int sek4;
extern int syukai, syukai2;
void COggDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar)
{
	for (;;) {
		if (sflg == FALSE) break;
		DoEvent();
	}

	int minpos;
	int maxpos;
	int curpos;
	double aa;
	if (wavsam == 32) aa = 2000.0;
	if (wavsam == 24) aa = 2000.0;
	if (wavsam == 16) aa = 2000.0;
	if (wavsam == 8) aa = 2000.0;

	if (nSBCode == SB_THUMBTRACK) {
		CSliderCtrl* r = (CSliderCtrl*)pScrollBar;
		r->GetRange(minpos, maxpos);
		switch (r->GetDlgCtrlID()) {
		case IDC_SLIDER2:
			hsc = 1; sflg = FALSE; return;
			break;
		}
	}
		if (nSBCode == SB_PAGELEFT) {
			CSliderCtrl* r = (CSliderCtrl*)pScrollBar;
			r->GetRange(minpos, maxpos);
			switch (r->GetDlgCtrlID()) {
			case IDC_SLIDER2:
				CCriticalLock _ccl(&cs);
				int info;
				info = r->GetLineSize();
				curpos = r->GetPos();
				if (curpos > minpos) curpos = max(minpos, curpos - info);
				//			playb=curpos;
				if (pMediaPosition && (mode == -2 || (mode > 0 && videoonly == TRUE))) {
					r->SetPos((int)curpos);
					if (aa2 == 0) {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * 100000.0f)));
					}
					else {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * (100000.0f))));
					}
				}
				else {
					if ((loop1 + loop2) < curpos && endf == 0) curpos = (loop1 + loop2);
					r->SetPos((int)curpos);
					if (pMainFrame1) {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * 10000000.0f) / (float)wavbit));
						//				pMainFrame1->seek((long)(((float)((float)playb)*29.97f)/(44100.0f)));
					}
					if ((mode >= 10 && mode <= 21) || mode <= -10) {
						if (mode == -10) {
							hsc = 2;
							//						return;
							//						playb*=4;
							//						r->SetPos((int)playb/4);
							//						playb-=wavbit*40;
							playb = curpos * 400;
							if (playb < 0)playb = 0;
							if (ps == 0) {
								OnPause();
								ZeroMemory(bufwav3, sizeof(bufwav3));
								syukai = 1; syukai2 = 0;
								if (thn == FALSE) for (;;) { if (syukai2 == 1)break; DoEvent(); }
								if (savedata.mp3orig) {
									if (mp3_.seek2(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								else {
									if (mp3_.seek(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								poss = 0; sek = TRUE;
								cnt3 = 0;
								timer.SetEvent();
								syukai = 0;
								OnPause();
							}
							else
								if (savedata.mp3orig) {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
								else {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
						}
						else {
							playb = curpos;
							seekadpcm((int)playb);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}

					}
					else if (mode == -3) {
						playb = curpos;
						if (mod) {
							if (mod->SetPosition && sikpi.dwSeekable) mod->SetPosition(kmp1, (DWORD)((double)playb / (((double)wavbit * (double)wavch) / 2000.0)));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -7) {
						playb = curpos;
						if (1) {
							if (m_dsb)m_dsb->Stop();
							dsd_.kpiSetPosition(kmp, (DWORD)((double)playb / ((((double)wavbit) * (double)wavch) / 2000.0)));							sek = TRUE;
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -8) {
						playb = curpos;
						if (1) {
							sek4 = TRUE;
							if (flacmode == 1)
								flac_.SetPosition(kmp, playb);
							else
								flac_.SetPosition(kmp, (((LONGLONG)((double)playb / (((double)wavbit * (double)wavch) / (aa))))));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek4 = FALSE;
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -6) {
						playb = curpos;
						seekadpcm((int)playb);
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					else if (mode == -9) {
						playb = curpos;
						if (1) {
							double wavv2[] = { 0,2.0,1.0,1.0 / 2.0,1.0 / 2.0,1.0 / 2.0,1.0 / 2.0 };
							DWORD pla = (DWORD)((double)playb / ((((double)(wavbit2 / wavv2[wavch]))) / ((wavch > 2) ? (1069.1 * wavch) : 1000.0)));
							pla = ((pla / (wavch * 2) * (wavch * 2)));
							m4a_.SetPosition(kmp, pla);
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else {
						playb = curpos;
						ov_pcm_seek(&vf, (ogg_int64_t)playb);
						poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
						poss5 = curpos;
						ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					poss = 0;
					//			playl+=whsize;
					hsc = 0;
				}
				_ccl.Leave();
				break;
			}
			return;
		}
		if (nSBCode == SB_PAGERIGHT) {
			CSliderCtrl* r = (CSliderCtrl*)pScrollBar;
			r->GetRange(minpos, maxpos);
			switch (r->GetDlgCtrlID()) {
			case IDC_SLIDER2:
				CCriticalLock _ccl(&cs);
				int info;
				info = r->GetLineSize();
				curpos = r->GetPos();
				if (curpos < maxpos) { curpos = min(maxpos, curpos + info); }
				else { hsc = 2; sflg = FALSE; return; }//
				//			playb=curpos;
				if (pMediaPosition && (mode == -2 || (mode > 0 && videoonly == TRUE))) {
					r->SetPos((int)curpos);
					if (aa2 == 0) {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * 100000.0f)));
					}
					else {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * (100000.0f))));
					}
				}
				else {
					if ((loop1 + loop2) < curpos && endf == 0) curpos = (loop1 + loop2);
					r->SetPos((int)curpos);
					if (pMainFrame1) {
						pMainFrame1->seek((LONGLONG)(((float)((float)curpos) * 10000000.0f) / (float)wavbit));
						//				pMainFrame1->seek((long)(((float)((float)playb)*29.97f)/(44100.0f)));
					}
					if ((mode >= 10 && mode <= 21) || mode <= -10) {
						if (mode == -10) {
							hsc = 2;
							//						return;
							playb = curpos * 400;
							//						playb*=4;
							//						playb+=wavbit*40;
							//r->SetPos((int)playb/4);
							if (ps == 0) {
								OnPause();
								ZeroMemory(bufwav3, sizeof(bufwav3));
								syukai = 1; syukai2 = 0;
								if (thn == FALSE) for (;;) { if (syukai2 == 1)break; DoEvent(); }
								if (savedata.mp3orig) {
									if (mp3_.seek2(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								else {
									if (mp3_.seek(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								poss = 0; sek = TRUE;
								cnt3 = 0;
								timer.SetEvent();
								syukai = 0;
								OnPause();
							}
							else
								if (savedata.mp3orig) {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
								else {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
						}
						else {
							playb = curpos;
							seekadpcm((int)playb);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -3) {
						playb = curpos;
						if (mod) {
							if (mod->SetPosition && sikpi.dwSeekable) mod->SetPosition(kmp1, (DWORD)((double)playb / (((double)wavbit * (double)wavch) / 2000.0)));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -7) {
						playb = curpos;
						if (1) {
							if (m_dsb)m_dsb->Stop();
							dsd_.kpiSetPosition(kmp, (DWORD)((double)playb / ((((double)wavbit) * (double)wavch) / 2000.0)));							sek = TRUE;
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -6) {
						playb = curpos;
						seekadpcm((int)playb);
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					else if (mode == -8) {
						playb = curpos;
						if (1) {
							sek4 = TRUE;
							if (flacmode == 1)
								flac_.SetPosition(kmp, playb);
							else
								flac_.SetPosition(kmp, (((LONGLONG)((double)playb / (((double)wavbit * (double)wavch) / (aa))))));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
							sek4 = FALSE;
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -9) {
						playb = curpos;
						if (1) {
							double wavv2[] = { 0,2.0,1.0,1.0 / 2.0,1.0 / 2.0,1.0 / 2.0,1.0 / 2.0 };
							DWORD pla = (DWORD)((double)playb / ((((double)(wavbit2 / wavv2[wavch]))) / ((wavch > 2) ? (1069.1 * wavch) : 1000.0)));
							pla = ((pla / (wavch * 2) * (wavch * 2)));
							m4a_.SetPosition(kmp, pla);
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else {
						playb = curpos;
						ov_pcm_seek(&vf, (ogg_int64_t)playb);
						poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
						ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						poss5 = curpos;
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					poss = 0;
					//			playl+=whsize;
					hsc = 0;
				}
				_ccl.Leave();
				break;
			}
			return;
		}

		if (nSBCode == SB_ENDSCROLL) {
			//if (hsc == 2) { hsc = 0; sflg = FALSE; return; }
			CSliderCtrl* r = (CSliderCtrl*)pScrollBar;
			switch (r->GetDlgCtrlID()) {
			case IDC_SLIDER2:
				CCriticalLock _ccl(&cs);
				playb = r->GetPos();
				if (pMediaPosition && (mode == -2 || (mode > 0 && videoonly == TRUE))) {
					r->SetPos((int)playb);
					if (aa2 == 0) {
						pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 100000.0f)));
					}
					else {
						pMainFrame1->seek((LONGLONG)(((float)((float)playb) * (100000.0f))));
					}
					hsc = 0;
				}
				else {
					if ((loop1 + loop2) < playb && endf == 0) playb = (loop1 + loop2);
					r->SetPos((int)playb);
					if (pMainFrame1) {
						pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 10000000.0f) / (float)wavbit));
						//				pMainFrame1->seek((long)(((float)((float)playb)*29.97f)/(44100.0f)));
					}
					if ((mode >= 10 && mode <= 21) || mode <= -10) {
						if (mode == -10) {
							playb *= 400;
							r->SetPos((int)playb / 400);
							if (ps == 0) {
								OnPause();
								ZeroMemory(bufwav3, sizeof(bufwav3));
								syukai = 1; syukai2 = 0;
								if (thn == FALSE) for (;;) { if (syukai2 == 1)break; DoEvent(); }
								if (savedata.mp3orig) {
									if (mp3_.seek2(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								else {
									if (mp3_.seek(playb / ((wavch == 2 ? 4 : 1) * (wavsam / 16.0f)), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return; }
								}
								poss = 0; sek = TRUE;
								cnt3 = 0;
								timer.SetEvent();
								syukai = 0;
								OnPause();
							}
							else
								if (savedata.mp3orig) {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
								else {
									poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
									ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
									if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return; }
								}
						}
						else {
							seekadpcm((int)playb);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -3) {
						if (mod) {
							if (mod->SetPosition && sikpi.dwSeekable) mod->SetPosition(kmp1, (DWORD)((double)playb / ((((double)wavbit) * (double)wavch) / 2000.0)));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -7) {

						if (sek == FALSE) {
							if (m_dsb)m_dsb->Stop();
							dsd_.kpiSetPosition(kmp, (DWORD)((double)playb / ((((double)wavbit) * (double)wavch) / 2000.0)));							sek = TRUE;
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -6) {

						seekadpcm((int)playb);
						poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
						ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE * OUTPUT_BUFFER_NUM * 3);
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					else if (mode == -8) {
						if (1) {
							sek4 = TRUE;
							if (flacmode == 1)
								flac_.SetPosition(kmp, playb);
							else
								flac_.SetPosition(kmp, (((LONGLONG)((double)playb / (((double)wavbit * (double)wavch) / (aa))))));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							sek4 = FALSE;
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else if (mode == -9) {
						if (1) {
							double wavv2[] = { 0,2.0,1.0,1.0 / 3.0,1.0 / 4.0,1.0 / 5.0,1.0 / 6.0 };
							DWORD pla = (DWORD)((double)playb / ((((double)(wavbit2 / wavv2[wavch]))) / ((wavch > 2) ? (1069.1 * wavch) : 1000.0)));
							pla = ((pla / (wavch * 2) * (wavch * 2)));
							poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
							ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
							m4a_.SetPosition(kmp, pla);
							sek = TRUE;
							cnt3 = 0;
							timer.SetEvent();
						}
					}
					else {
						ov_pcm_seek(&vf, (ogg_int64_t)playb);
						poss = 0; poss2 = 0; poss3 = 0; poss4 = 0; poss5 = 0; poss6 = 0;
						ZeroMemory(bufkpi, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi_, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi2, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi3, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						ZeroMemory(bufkpi4, OUTPUT_BUFFER_SIZE* OUTPUT_BUFFER_NUM * 3);
						poss5 = playb;
						sek = TRUE;
						cnt3 = 0;
						timer.SetEvent();
					}
					poss = 0;
					//			playl+=whsize;
					hsc = 0;
				}
				_ccl.Leave();
				break;
			}
		}
		sflg = FALSE;
	}

void COggDlg::OnButton21()
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CRender* r = new CRender(CWnd::FromHandle(GetSafeHwnd()));
	CWnd::PostMessage(0x118);
	int ret = r->DoModal();
	char tmp[1024];
	_getcwd(tmp, 1000);
	_tchdir(karento2);
	CFile ab;
#if _UNICODE
	if (ab.Open(L"oggYSEDbgmu.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#else
	if (ab.Open("oggYSEDbgm.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#endif
		ab.Write(&savedata, sizeof(save));
		ab.Close();
	}
	_chdir(tmp);
	delete r;
	}


void COggDlg::OnNMReleasedcaptureSlider2(NMHDR * pNMHDR, LRESULT * pResult)
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	*pResult = 0;
}



void COggDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT COggDlg::OnHotKey(WPARAM wp, LPARAM a)
{
	switch (wp) {
	case 8000:
		m_dsval.SetPos(m_dsval.GetPos() + 5);
		break;
	case 8001:
		m_dsval.SetPos(m_dsval.GetPos() - 5);
		break;
	case 8002:
		if (!((ogg || adbuf2 || mod || wav) || mode == -2)) break;
		playb = m_time.GetPos();
		if (pMediaPosition && ((mode == -2 && hsc == 0) || ((mode > 0 || mode < -10) && videoonly == TRUE && hsc == 0))) {
			playb += 10 * 100;
			m_time.SetPos((int)playb);
			if (aa2 == 0) {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 100000.0f)));
			}
			else {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * (100000.0f))));
			}
			hsc = 0;
		}
		else {
			playb += wavbit * (wavch == 2 ? 10 : 5);
			if ((loop1 + loop2) < (int)playb && endf == 0) playb = (loop1 + loop2);
			if (mode != -10)m_time.SetPos((int)playb);
			if (pMainFrame1) {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 10000000.0f) / (float)wavbit));
			}
			if ((mode >= 10 && mode <= 21) || mode <= -10) {
				if (mode == -10) {
					playb -= wavbit * (wavch == 2 ? 10 : 5);
					playb *= 400;
					playb += wavbit * (wavch == 2 ? 40 : 20);
					if (ps == 0) {
						OnPause();
						ZeroMemory(bufwav3, sizeof(bufwav3));
						syukai = 1; syukai2 = 0;
						if (thn == FALSE) for (;;) { if (syukai2 == 1)break; DoEvent(); }
						if (savedata.mp3orig) {
							if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return 0; }
						}
						else {
							if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return 0; }
						}
						poss = 0; sek = TRUE;
						timer.SetEvent();
						syukai = 0;
						OnPause();
					}
					else
						if (savedata.mp3orig) {
							if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return 0; }
						}
						else {
							if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return 0; }
						}
					//						m_time.SetPos((int)playb/400);
				}
				else {
					seekadpcm((int)playb);
					sek = TRUE;
					timer.SetEvent();
				}
			}
			else if (mode == -3) {
				if (mod) {
					if (mod->SetPosition && sikpi.dwSeekable) mod->SetPosition(kmp1, (DWORD)((double)playb / (((double)wavbit * (double)wavch) / 2000.0)));
					sek = TRUE;
					timer.SetEvent();
				}
			}
			else {
				ov_pcm_seek(&vf, (ogg_int64_t)playb);
				sek = TRUE;
				timer.SetEvent();
			}
			poss = 0;
		}
		break;
	case 8003:
		if (!((ogg || adbuf2 || mod || wav) || mode == -2)) break;
		playb = m_time.GetPos();
		if (pMediaPosition && ((mode == -2 && hsc == 0) || ((mode > 0 || mode < -10) && videoonly == TRUE && hsc == 0))) {
			playb -= 10 * 100;
			m_time.SetPos((int)playb);
			if (aa2 == 0) {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 100000.0f)));
			}
			else {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * (100000.0f))));
			}
			hsc = 0;
		}
		else {
			playb -= wavbit * (wavch == 2 ? 10 : 5);
			if ((loop1 + loop2) < (int)playb && endf == 0) playb = (loop1 + loop2);
			if (mode != -10)m_time.SetPos((int)playb);
			if (pMainFrame1) {
				pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 10000000.0f) / (float)wavbit));
			}
			if ((mode >= 10 && mode <= 21) || mode <= -10) {
				if (mode == -10) {
					playb += wavbit * (wavch == 2 ? 10 : 5);
					playb *= 400;
					playb -= wavbit * (wavch == 2 ? 40 : 20);
					if (playb < 0)playb = 0;
					if (ps == 0) {
						OnPause();
						ZeroMemory(bufwav3, sizeof(bufwav3));
						syukai = 1; syukai2 = 0;
						if (thn == FALSE) for (;;) { if (syukai2 == 1)break; DoEvent(); }
						if (savedata.mp3orig) {
							if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return 0; }
						}
						else {
							if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { fade1 = 1; if (thn == FALSE) { if (m_dsb)m_dsb->Stop(); }return 0; }
						}
						poss = 0; sek = TRUE;
						timer.SetEvent();
						syukai = 0;
						OnPause();
					}
					else
						if (savedata.mp3orig) {
							if (mp3_.seek2(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return 0; }
						}
						else {
							if (mp3_.seek(playb / (wavch == 2 ? 4 : 1), wavch) == FALSE) { return 0; }
						}
					//						m_time.SetPos((int)playb/400);
				}
				else {
					seekadpcm((int)playb);
					sek = TRUE;
					timer.SetEvent();
				}
			}
			else if (mode == -3) {
				if (mod) {
					if (mod->SetPosition && sikpi.dwSeekable) mod->SetPosition(kmp1, (DWORD)((double)playb / (((double)wavbit * (double)wavch) / 2000.0)));
					sek = TRUE;
					timer.SetEvent();
				}
			}
			else {
				ov_pcm_seek(&vf, (ogg_int64_t)playb);
				sek = TRUE;
				timer.SetEvent();
			}
			poss = 0;
		}
		break;
	}
	return 0;
}

void COggDlg::rl(int a)
{
	playb += wavbit * 10 * a;
	if ((loop1 + loop2) < (int)playb && endf == 0) playb = (loop1 + loop2);
	m_time.SetPos((int)playb);
	if (pMainFrame1) {
		pMainFrame1->seek((LONGLONG)(((float)((float)playb) * 10000000.0f) / (float)wavbit));
	}
	if ((mode >= 10 && mode <= 21) || mode <= -10) {
		seekadpcm((int)playb);
		sek = TRUE;
		timer.SetEvent();
	}
	else {
		ov_pcm_seek(&vf, (ogg_int64_t)playb);
		sek = TRUE;
		timer.SetEvent();
	}
	poss = 0;
}

void COggDlg::OnActivate(UINT nState, CWnd * pWndOther, BOOL bMinimized)
{

	CDialog::OnActivate(nState, pWndOther, bMinimized);
	int l = 5;
	if (plw) {
		if ((nState == WA_ACTIVE || nState == WA_CLICKACTIVE) && bMinimized == 0 && pl->m_saisyo.GetCheck()) {
			ogpl0 = 1;
			pl->ShowWindow(SW_RESTORE);
		}
	}
	if (nState == WA_INACTIVE) //非アクティブ
	{
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY0);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY1);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY2);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY3);
	}
	else {
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY0, 0, VK_UP);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY1, 0, VK_DOWN);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY2, 0, VK_RIGHT);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY3, 0, VK_LEFT);
		if (nState == WA_ACTIVE) {
		}
	}
	// TODO: ここにメッセージ ハンドラ コードを追加します。
}

void COggDlg::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDialog::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void COggDlg::OnKillFocus(CWnd * pNewWnd)
{

	CDialog::OnKillFocus(pNewWnd);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY0);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY1);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY2);
	UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY3);
	//	if (maini)
	//		::SetWindowPos(maini->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//	extern CImageBase* playbase;
	//	if (playbase)
	//		::SetWindowPos(playbase->m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//	::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void COggDlg::OnSize(UINT nType, int cx, int cy)
{
	extern CImageBase* playbase;
	CDialog::OnSize(nType, cx, cy);
	if (nType == SIZE_MINIMIZED) {
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY0);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY1);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY2);
		UnregisterHotKey(GetSafeHwnd(), ID_HOTKEY3);
		//		if (playbase)
		//			playbase->ShowWindow(SW_MINIMIZE);
		if (pl) {
			if (pl->m_saisyo.GetCheck())
				pl->ShowWindow(SW_MINIMIZE);
		}
		if (pMainFrame1) {
			pMainFrame1->ShowWindow(SW_HIDE);
		}
		if (maini)
			maini->ShowWindow(SW_MINIMIZE);
		SetTimer(4924, 100, NULL);
	}
	if (nType == SIZE_RESTORED) {
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY0, 0, VK_UP);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY1, 0, VK_DOWN);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY2, 0, VK_RIGHT);
		RegisterHotKey(GetSafeHwnd(), ID_HOTKEY3, 0, VK_LEFT);
		if (ogpl0 == 1) {
			ogpl0 = 0;
			//			return;
		}
		//		if (playbase)
			//		playbase->ShowWindow(SW_RESTORE);
		if (pl) {
			if (pl->m_saisyo.GetCheck()) {
				//pl->ShowWindow(SW_RESTORE);
//				::SetWindowPos(pl->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
		}
		if (pMainFrame1 && height != 0) {
			pMainFrame1->ShowWindow(SW_SHOWNORMAL);
		}
		CRect r;
		GetWindowRect(&r);
		if (maini)
			maini->ShowWindow(SW_RESTORE);
	}

}
#if _UNICODE
void COggDlg::_CreateShellLink(LPWSTR pszArguments, LPWSTR pszTitle, IShellLink * *ppsl, int iconindex, bool WA, BOOL wa2)
#else
void COggDlg::_CreateShellLink(LPSTR pszArguments, LPSTR pszTitle, IShellLink * *ppsl, int iconindex, bool WA, BOOL wa2)
#endif
{
	IShellLink* psl;
	HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&psl));
	if (SUCCEEDED(hr)) {
		if (WA) {
			TCHAR fname[MAX_PATH];
			TCHAR shortfname[MAX_PATH];
			GetModuleFileName(0, fname, MAX_PATH);
			GetShortPathName(fname, shortfname, MAX_PATH);
			CString s = pszArguments;
			if (s == "*4")
				psl->SetIconLocation(fname, 6);
			else
				psl->SetIconLocation(shortfname, 0);
			hr = psl->SetPath(shortfname);
		}
		else
			hr = psl->SetPath(_T("rundll32.exe"));

		if (SUCCEEDED(hr)) {
			hr = psl->SetArguments(pszArguments);
			if (SUCCEEDED(hr)) {
				IPropertyStore* pps;
				hr = psl->QueryInterface(IID_PPV_ARGS(&pps));
				if (SUCCEEDED(hr)) {
					PROPVARIANT propvar;
					WCHAR ss[2050];
					LPWSTR ss1; ss1 = ss;
#if UNICODE
					_tcscpy(ss1, pszTitle);
#else
					MultiByteToWideChar(CP_ACP, 0, pszTitle, -1, ss1, 2000);
#endif
					//propvar.vt=VT_LPWSTR;
					//propvar.pwszVal=ss1;
					if (SUCCEEDED(hr)) {
						if (wa2) {
							hr = InitPropVariantFromString(ss1, &propvar);
							hr = pps->SetValue(PKEY_Title, propvar);
						}
						else {
							InitPropVariantFromBoolean(TRUE, &propvar);
							hr = pps->SetValue(PKEY_AppUserModel_IsDestListSeparator, propvar);
						}
						if (SUCCEEDED(hr)) {
							hr = pps->Commit();
							if (SUCCEEDED(hr)) {
								hr = psl->QueryInterface(IID_PPV_ARGS(ppsl));
							}
						}
						PropVariantClear(&propvar);
					}
					pps->Release();
				}
			}
		}
		else {
			hr = HRESULT_FROM_WIN32(GetLastError());
		}
		psl->Release();
	}
	return;
}

HBRUSH COggDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ここで DC の属性を変更してください。
	if (savedata.aero == 1) {
		if (nCtlColor == CTLCOLOR_DLG)
		{
			return m_brDlg;
		}
		if (nCtlColor == CTLCOLOR_STATIC)
		{
			SetBkMode(pDC->m_hDC, TRANSPARENT);
			return m_brDlg;
		}
	}
	// TODO:  既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}


void COggDlg::OnPlayList()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if (plw == 0) pl = NULL;
	if (pl) {
		if (plw)
			plw = 0;
		killw1 = 0;
		if (pl) {
			pl->nnn = 1;
			//			pl->DestroyWindow();
			pl->OnClose();
			for (; killw1 == 0;)
				DoEvent();
			delete pl;
			pl = NULL;
		}
	}
	else {
		plw = 1;
		pl = new CPlayList;
		pl->Create(this);
		plw = 1;
	}
	if (pl)
		savedata.pl = 1;
	else
		savedata.pl = 0;

	char tmp[1024];
	_getcwd(tmp, 1000);
	_tchdir(karento2);
	CFile ab;
#if _UNICODE
	if (ab.Open(L"oggYSEDbgmu.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#else
	if (ab.Open("oggYSEDbgm.dat", CFile::modeCreate | CFile::modeWrite, NULL) == TRUE) {
#endif
		ab.Write(&savedata, sizeof(save));
		ab.Close();
	}
	_chdir(tmp);
	}

void plus1(int& c);
void plus2(int& c);
CString sswk;
HINSTANCE hDLLk1[500];
KMPMODULE* mod1[500];
pfnGetKMPModule pFunck[500];

void plus1(int& c)
{
ab:
	try {
		_set_se_translator(trans_func);
		plus2(c);
		if (hDLLk1[kpicnt])FreeLibrary(hDLLk1[kpicnt]);
	}
	catch (SE_Exception e) {
		if (hDLLk1[kpicnt])FreeLibrary(hDLLk1[kpicnt]);
		c = 0;
		goto ab;
	}
	catch (_EXCEPTION_POINTERS* ep) {
		if (hDLLk1[kpicnt])FreeLibrary(hDLLk1[kpicnt]);
		c = 0;
		goto ab;
	}
	catch (...) {
		if (hDLLk1[kpicnt])FreeLibrary(hDLLk1[kpicnt]);
		c = 0;
		goto ab;
	}
}

void plus2(int& c)
{
	CString ss = sswk;
	hDLLk1[kpicnt] = LoadLibrary(ss);
	if (hDLLk1[kpicnt]) {
		pFunck[kpicnt] = (pfnGetKMPModule)GetProcAddress(hDLLk1[kpicnt], SZ_KMP_GETMODULE);
		if (pFunck[kpicnt]) {
			{
				mod1[kpicnt] = pFunck[kpicnt]();
				kpif[kpicnt] = ss;
				for (int i = 0; i < 299; i++) {
					if (mod1[kpicnt] == NULL) break;
					if (mod1[kpicnt]->ppszSupportExts) {
						if (mod1[kpicnt]->ppszSupportExts[i] == NULL ||
							mod1[kpicnt]->ppszSupportExts[i][0] == NULL) {
							ext[kpicnt][i] == ""; break;
						}
						ext[kpicnt][i] = mod1[kpicnt]->ppszSupportExts[i];
						ext[kpicnt][i].MakeLower();
					}
					else { ext[kpicnt][i] == ""; break; }
				}
				ext[kpicnt][299] = "";
				if (mod1[kpicnt]) {
					if (mod1[kpicnt]->Init)mod1[kpicnt]->Init();
					if (mod1[kpicnt]->Deinit)mod1[kpicnt]->Deinit();
				}
			}
			if (c && mod1[kpicnt])kpicnt++;
		}
	}
}

void COggDlg::plug(CString ff, KMPMODULE * mod)
{
	kpicnt = 0;
	for (int i = 0; i < 500; i++)
		hDLLk1[i] = NULL;
	plugloop(ff);
	for (int i = kpicnt - 1; i >= 0; i--)
		FreeLibrary(hDLLk1[i]);
}
void COggDlg::plugloop(CString ff)
{
	CString s, ss;
	_tchdir(ff);
	CFileFind f;
	if (f.FindFile(_T("*.kpi"))) {
		int b, c = 1;
		do {
			if (c)
				b = f.FindNextFile();
			c = 1;
			if (f.IsDirectory() == 0) {
				s = f.GetFileName();
				if (!(s == "." || s == "..") && s.Right(4) == ".kpi") {
					ss = f.GetFilePath();
					sswk = ss;
					plus1(c);
				}
			}
		} while (b);
	}
	f.Close();
	CFileFind cf1;
	if (cf1.FindFile(_T("*.*")) != 0) {
		int h = 1;
		for (; h;) {
			h = cf1.FindNextFile();
			ss = cf1.GetFileName();
			if (!(ss == "." || ss == "..")) {
				if (cf1.IsDirectory() != 0) { //フォルダ？
					if (ff.Right(1) == "\\")
						plugloop(ff + cf1.GetFileName());
					else
						plugloop(ff + _T("\\") + cf1.GetFileName());
				}
			}
		}
	}
	cf1.Close();
}
CImageBase* jake = NULL;
void COggDlg::OnBnmp3jake()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	if (mi) {
		delete mi;
		delete jake;
	}
	mi = new CMp3Image;
	mi->Create(og);
	if (savedata.aero == 1) {
		jake = new CImageBase;
		if (jake->Create(og) == FALSE) {
			AfxMessageBox(L"Baseの起動に失敗しました");
		}
		jake->ShowWindow(SW_HIDE);
		jake->oya = mi;
	}
	else {
		jake = NULL;
	}
	mi->Load(mp3file);

}


void COggDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	m_newFont->DeleteObject();
	delete m_newFont;
	m_newFont1->DeleteObject();
	delete m_newFont1;

}


BOOL COggDlg::Create(LPCTSTR lpszTemplateName, CWnd * pParentWnd)
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	return CDialog::Create(lpszTemplateName, pParentWnd);
}


int COggDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: ここに特定な作成コードを追加してください。
	if (savedata.aero == 1) {
		ModifyStyleEx(0, WS_EX_LAYERED);

		// レイヤードウィンドウの不透明度と透明のカラーキー
		SetLayeredWindowAttributes(RGB(255, 0, 0), 0, LWA_COLORKEY);

		// 赤色のブラシを作成する．
		m_brDlg.CreateSolidBrush(RGB(255, 0, 0));
	}


	return 0;
}


void COggDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialog::OnMoving(fwSide, pRect);
	CRect r;
	GetWindowRect(&r);
	if (maini)
		maini->MoveWindow(&r);
	//if (maini)
//		::SetWindowPos(maini->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//	::SetWindowPos(og->m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


void COggDlg::OnSetFocus(CWnd * pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
}


int COggDlg::OnMouseActivate(CWnd * pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

int npap = 0;
void COggDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CDialog::OnActivateApp(bActive, dwThreadID);

	// TODO: ここにメッセージ ハンドラー コードを追加します。
	if (bActive) {
	}
}


BOOL COggDlg::OnNcActivate(BOOL bActive)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (plw) {
		if (bActive && pl->m_saisyo.GetCheck()) {
			//	pl->ShowWindow(SW_RESTORE);
		}
	}
	if (bActive) {
		SetTimer(4923, 20, NULL);
	}
	else {
		SetTimer(4924, 10, NULL);
	}
	return CDialog::OnNcActivate(bActive);
}
