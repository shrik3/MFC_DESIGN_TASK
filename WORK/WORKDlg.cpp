
// WORKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WORK.h"
#include "WORKDlg.h"
#include "afxdialogex.h"
#include "OPTS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWORKDlg �Ի���



CWORKDlg::CWORKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWORKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWORKDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CWORKDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_Login, &CWORKDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CWORKDlg ��Ϣ�������

BOOL CWORKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWORKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWORKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWORKDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CWORKDlg::OnBnClickedLogin()
{
	_RecordsetPtr  m_pRecordset;//���ݼ�����
	_variant_t vPassword;	//���ȡ���������ݵı���

	// ESTABLISH CONNECTION
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");//����Connection����
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			//�������ݿ�
		}
	}
	catch (_com_error e)//��׽�쳣
	{
		CString errormessage;
		errormessage.Format(_T("�������ݿ�ʧ��!\r\n������:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);//��ʾ������Ϣ
		return;
	}

	// CHECK LOGIN INFO

	CString CPassword;
	try
	{
		CString strSQL;
		CString name,password;
		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(password);
		strSQL.Format(_T("SELECT * FROM login where USERNAME ='%s'"), name); // ����������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);
		if (m_pRecordset->EndOfFile) {    // INPUT USERNAME DOESN'T EXIST
			CString message;
			message.Format(_T("USER DOESN'T EXIST!"));
		}
		else {

			vPassword = m_pRecordset->GetCollect("PASSWORD");
			CPassword = vPassword;
			if (CPassword == password) {
				// AUTH PASSED, INIT DLG2
				this->ShowWindow(SW_HIDE);
				OPTS DLG;
				DLG.DoModal();

			}
		}


	}
	catch (_com_error e)
	{
		CString message;
		message.Format(_T("��ȡ���ݿ�ʧ��!\n ������ϢΪ:%s"), e.Description());
		AfxMessageBox(message);///��ʾ������Ϣ
	}// TODO: �ڴ���ӿؼ�֪ͨ����������ѡ���ȡǰ1�� ���������Զ����ٵ�

	
	m_pConnection->Close();
}
