#pragma once


// OPTS �Ի���

class OPTS : public CDialog
{
	DECLARE_DYNAMIC(OPTS)

public:
	OPTS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~OPTS();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedChange();
};
