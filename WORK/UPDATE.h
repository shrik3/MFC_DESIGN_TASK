#pragma once


// UPDATE �Ի���

class UPDATE : public CDialog
{
	DECLARE_DYNAMIC(UPDATE)

public:
	UPDATE(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UPDATE();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
