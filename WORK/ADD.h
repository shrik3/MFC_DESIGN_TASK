#pragma once


// ADD �Ի���

class ADD : public CDialog
{
	DECLARE_DYNAMIC(ADD)

public:
	ADD(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ADD();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
