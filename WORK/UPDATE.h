#pragma once


// UPDATE 对话框

class UPDATE : public CDialog
{
	DECLARE_DYNAMIC(UPDATE)

public:
	UPDATE(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~UPDATE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
