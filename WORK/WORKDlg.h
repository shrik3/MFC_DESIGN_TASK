
// WORKDlg.h : ͷ�ļ�
//
#include"stdafx.h"
#pragma once


// CWORKDlg �Ի���
class CWORKDlg : public CDialogEx
{
// ����
public:
	CWORKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	_ConnectionPtr m_pConnection;
	afx_msg void OnBnClickedLogin();
};
