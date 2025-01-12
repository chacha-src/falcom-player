// CPlayListNew.cpp : 実装ファイル
//

#include "stdafx.h"
#include "ogg.h"
#include "afxdialogex.h"
#include "CPlayListNew.h"


// CPlayListNew ダイアログ

IMPLEMENT_DYNAMIC(CPlayListNew, CDialogEx)

CPlayListNew::CPlayListNew(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAYLIST_NEW, pParent)
{

}

CPlayListNew::~CPlayListNew()
{
}

void CPlayListNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
}


BEGIN_MESSAGE_MAP(CPlayListNew, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPlayListNew::OnBnClickedOk)
END_MESSAGE_MAP()


// CPlayListNew メッセージ ハンドラー


void CPlayListNew::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	m_name.GetWindowText(name);
	if (name.GetLength() > 200) {
		MessageBox(L"文字数が長すぎます", L"ogg簡易プレイヤ");
		return;
	}
	CDialogEx::OnOK();
}


BOOL CPlayListNew::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	m_name.SetWindowText(name);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
