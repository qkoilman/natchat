// emojiDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "emojiDlg.h"
#include "afxdialogex.h"
#include "addemojiDlg.h"
#include "modiftEmoji.h"


std::vector<CString> emoji_vec;
CString sel_emoji;

// emojiDlg 对话框

IMPLEMENT_DYNAMIC(emojiDlg, CDialogEx)

emojiDlg::emojiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EMOJI, pParent)
{

}

emojiDlg::~emojiDlg()
{
}

void emojiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(emojiDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &emojiDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_EMOJIADD, &emojiDlg::OnBnClickedEmojiadd)
	ON_NOTIFY(NM_DBLCLK, IDC_EMOJILIST, &emojiDlg::OnNMDblclkEmojilist)
END_MESSAGE_MAP()


// emojiDlg 消息处理程序
BOOL emojiDlg::OnInitDialog() {
	CString emoji_mover;
	CRect rect;
	std::vector<CString>::iterator e_itor = emoji_vec.begin();
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_EMOJILIST);
	lst->SetExtendedStyle(lst->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	lst->GetClientRect(&rect);
	lst->InsertColumn(0, L"A", LVCFMT_CENTER, 100);
	lst->InsertColumn(1, _T("Emoji"), LVCFMT_CENTER, rect.Width());
	lst->DeleteColumn(0);
	while (e_itor != emoji_vec.end()) {
		int cur_row = lst->GetItemCount();
		lst->InsertItem(cur_row, *e_itor);
		++e_itor;
	}
	return TRUE;
}


void emojiDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_EMOJILIST);
	int sel_col = lst->GetSelectionMark();
	if (sel_col == -1) {
		MessageBox(L"Please select a emoji");
		return;
	}
	sel_emoji = lst->GetItemText(sel_col, 0);
	CDialogEx::OnOK();
}


void emojiDlg::OnBnClickedEmojiadd()
{
	// TODO: 在此添加控件通知处理程序代码
	CaddemojiDlg add_emoji_dlg;
	if (IDOK == add_emoji_dlg.DoModal()) {
		CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_EMOJILIST);
		int cur_row = lst->GetItemCount();
		lst->InsertItem(cur_row, new_emoji);
		refresh_emoji_vec();
	}
}

void emojiDlg::refresh_emoji_vec() {
	emoji_vec.clear();
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_EMOJILIST);
	int lineCount = lst->GetItemCount();
	for (int i = 0;i < lineCount; i++) {
		emoji_vec.push_back(lst->GetItemText(i, 0));
	}
}

void emojiDlg::OnNMDblclkEmojilist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	CListCtrl* lst = (CListCtrl*)GetDlgItem(IDC_EMOJILIST);

	if (-1 != pNMListView->iItem) {
		modified_emoji = lst->GetItemText(pNMListView->iItem, 0);
		CmodiftEmoji me;
		INT_PTR mo_flag = me.DoModal();
		if (mo_flag == IDOK) {
			lst->SetItemText(pNMListView->iItem, 0, modified_emoji);
			refresh_emoji_vec();
		}
		else if (mo_flag == IDCANCEL) {
			// 删除
			lst->DeleteItem(pNMListView->iItem);
			refresh_emoji_vec();
		}
	}
	*pResult = 0;
}
