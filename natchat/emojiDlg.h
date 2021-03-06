#pragma once

#include "resource.h"
#include <vector>
// emojiDlg 对话框

extern std::vector<CString> emoji_vec;
extern CString sel_emoji;

class emojiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(emojiDlg)

public:
	virtual BOOL OnInitDialog();
	emojiDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~emojiDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMOJI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEmojiadd();
	void refresh_emoji_vec();
	afx_msg void OnNMDblclkEmojilist(NMHDR *pNMHDR, LRESULT *pResult);
};
