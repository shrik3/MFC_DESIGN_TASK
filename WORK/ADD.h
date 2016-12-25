#pragma once


// ADD 对话框

class ADD : public CDialog
{
	DECLARE_DYNAMIC(ADD)

public:
	ADD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ADD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
