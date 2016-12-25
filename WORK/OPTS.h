#pragma once


// OPTS 对话框

class OPTS : public CDialog
{
	DECLARE_DYNAMIC(OPTS)

public:
	OPTS(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~OPTS();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
};
