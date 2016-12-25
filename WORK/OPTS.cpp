// OPTS.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WORK.h"
#include "OPTS.h"
#include "afxdialogex.h"
#include "ADD.h"
#include "UPDATE.h"

// GLOBAL HERE
CString eNAME, eID, eCOUNT, eREMARKS,eUID;
// OPTS �Ի���

IMPLEMENT_DYNAMIC(OPTS, CDialog)

OPTS::OPTS(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPTS, pParent)
{

}

OPTS::~OPTS()
{
}

void OPTS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OPTS, CDialog)
	ON_BN_CLICKED(IDC_Query, &OPTS::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_Delete, &OPTS::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_Add, &OPTS::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_Change, &OPTS::OnBnClickedChange)
END_MESSAGE_MAP()





void OPTS::OnBnClickedQuery()
{
	_RecordsetPtr  m_pRecordset;//���ݼ�����
	_variant_t vNAME, vID, vCOUNT, vREMARKS;	//���ȡ���������ݵı���
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			MessageBox(_T("���ӳɹ�"));
			///�������ݿ�
		}
	}
	catch (_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format(_T("�������ݿ�ʧ��!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// ��������ID��NAME�е�һ�����������Ĭ��ȡNAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///��ʾ������Ϣ
			return;
		}
		else {
			if (!name.IsEmpty()) {
				strSQL.Format(_T("SELECT * FROM schools where AME ='%s'"), name);
			}
			else {
				strSQL.Format(_T("SELECT * FROM schools where ID =%s"), id);
			}
		}

		// QUERY!
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);

		if (m_pRecordset->EndOfFile) {
			CString message;
			message.Format(_T("NO SUCH AN ENTRY!"));
			AfxMessageBox(message);///��ʾ������Ϣ
			return;
		}
		else {

			//entry exists
			vID = m_pRecordset->GetCollect("ID");
			vNAME = m_pRecordset->GetCollect("AME");
			vCOUNT = m_pRecordset->GetCollect("OUNT");
			vREMARKS = m_pRecordset->GetCollect("REMARKS");
			id = vID;
			name = vNAME;
			count = vCOUNT;
			remarks = vREMARKS;
			// SHOW RESULT !
			CString result;
			result.Format(_T("ID: %s\nNAME: %s\nCOUNT: %s\nREMARKS: %s\n"), id, name, count, remarks);
			MessageBox(result);///��ʾ������Ϣ
			return;
		}
	}

	catch (_com_error e) {
		MessageBox(e.ErrorMessage());///��ʾ������Ϣ
		return;
	}

}


void OPTS::OnBnClickedDelete()
{
	_RecordsetPtr  m_pRecordset;//���ݼ�����
	_variant_t vNAME, vID, vCOUNT, vREMARKS;	//���ȡ���������ݵı���
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			MessageBox(_T("���ӳɹ�"));
			///�������ݿ�
		}
	}
	catch (_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format(_T("�������ݿ�ʧ��!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// ��������ID��NAME�е�һ�����������Ĭ��ȡNAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///��ʾ������Ϣ
			return;
		}
		else {
			if (!name.IsEmpty()) {
				strSQL.Format(_T("DELETE  FROM schools where AME ='%s'"), name);
			}
			else {
				strSQL.Format(_T("DELETE FROM schools where ID =%s"), id);
			}
		}

		// QUERY!
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);

		MessageBox(_T("SUCCEED"));///��ʾ������Ϣ
		return;
	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(_T("FAILED!"));
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}

}



void OPTS::OnBnClickedAdd()
{
	ADD DLG;
	DLG.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void OPTS::OnBnClickedChange()
{


	_RecordsetPtr  m_pRecordset;//���ݼ�����
	_variant_t vNAME, vID, vCOUNT, vREMARKS,vUID;	//���ȡ���������ݵı���
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			///�������ݿ�
		}
	}
	catch (_com_error e)///��׽�쳣
	{
		CString errormessage;
		errormessage.Format(_T("�������ݿ�ʧ��!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// ��������ID��NAME�е�һ�����������Ĭ��ȡNAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///��ʾ������Ϣ
			return;
		}
		else {
			if (!name.IsEmpty()) {
				strSQL.Format(_T("SELECT * FROM schools where AME ='%s'"), name);
			}
			else {
				strSQL.Format(_T("SELECT * FROM schools where ID =%s"), id);
			}
		}

		// QUERY!
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);

		if (m_pRecordset->EndOfFile) {
			CString message;
			message.Format(_T("NO SUCH AN ENTRY!"));
			AfxMessageBox(message);///��ʾ������Ϣ
			return;
		}
		else {
			//entry exists
			vID = m_pRecordset->GetCollect("ID");
			vNAME = m_pRecordset->GetCollect("AME");
			vCOUNT = m_pRecordset->GetCollect("OUNT");
			vREMARKS = m_pRecordset->GetCollect("REMARKS");
			vUID = m_pRecordset->GetCollect("UID");
			
			eID = vID;
			eNAME = vNAME;
			eCOUNT = vCOUNT;
			eREMARKS = vREMARKS;
			eUID = vUID;

		}
	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(_T("��ѯ���ݿ�ʧ��!\r\n������:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UPDATE DLG;
	DLG.DoModal();

}
