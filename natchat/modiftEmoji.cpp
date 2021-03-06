// modiftEmoji.cpp: 实现文件
//

#include "stdafx.h"
#include "modiftEmoji.h"
#include "afxdialogex.h"
#include "resource.h"

CString modified_emoji;
// CmodiftEmoji 对话框

IMPLEMENT_DYNAMIC(CmodiftEmoji, CDialogEx)

CmodiftEmoji::CmodiftEmoji(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODIFYEMOJIDLG, pParent)
{

}

CmodiftEmoji::~CmodiftEmoji()
{
}

void CmodiftEmoji::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CmodiftEmoji, CDialogEx)
	ON_BN_CLICKED(IDC_MODIFYCANCEL, &CmodiftEmoji::OnBnClickedModifycancel)
	ON_BN_CLICKED(IDOK, &CmodiftEmoji::OnBnClickedOk)
END_MESSAGE_MAP()


// CmodiftEmoji 消息处理程序


void CmodiftEmoji::OnBnClickedModifycancel()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

BOOL CmodiftEmoji::OnInitDialog() {
	CMenu *pMenu = this->GetSystemMenu(FALSE);
	pMenu->EnableMenuItem(SC_CLOSE, MF_DISABLED);
	SetDlgItemText(IDC_MODIFYEDIT, modified_emoji);
	return TRUE;
}

void CmodiftEmoji::OnBnClickedOk()
{
	CString tmp;
	GetDlgItemText(IDC_MODIFYEDIT, tmp);
	// TODO: 在此添加控件通知处理程序代码
	if (tmp == L"") {
		MessageBox(L"Please enter an emoji");
		return;
	}
	modified_emoji = tmp;
	CDialogEx::OnOK();
}
