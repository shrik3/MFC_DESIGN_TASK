// ADD.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WORK.h"
#include "ADD.h"
#include "afxdialogex.h"


// ADD �Ի���

IMPLEMENT_DYNAMIC(ADD, CDialog)

ADD::ADD(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ADD, pParent)
{

}

ADD::~ADD()
{
}

void ADD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ADD, CDialog)
	ON_BN_CLICKED(IDOK, &ADD::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ADD::OnBnClickedCancel)
END_MESSAGE_MAP()


// ADD ��Ϣ�������


void ADD::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		CString strSQL2;
		CString strSQL3;
	
		GetDlgItem(IDC_EDIT2)->GetWindowText(name);
		GetDlgItem(IDC_EDIT3)->GetWindowText(id);
		GetDlgItem(IDC_EDIT4)->GetWindowText(remarks);
		GetDlgItem(IDC_EDIT5)->GetWindowText(count);


		if (name.IsEmpty() || id.IsEmpty() || remarks.IsEmpty() || count.IsEmpty()) {
			MessageBox(_T("PLEASE COMPLETE THE INFO"));
			return;
		}

		//strSQL.Format(_T("insert into schools(AME,ID,COUNT,REMARKS) values('%s','%s','%s','%s')"), name, id, count, remarks);
		//strSQL.Format(_T("insert into schools(AME,REMARKS) values('test1','testttt')"));
		// QUERY!

		strSQL2.Format(_T("insert into schools(AME,ID,OUNT,REMARKS) values('%s',%s,%s,'%s')"),name,id,count,remarks );
		
		
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL2), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);

		MessageBox(_T("����ɹ�"));


	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(e.Description());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}
	CDialog::OnOK();
}


void ADD::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_ConnectionPtr m_pConnection;
	CDialog::OnCancel();

}
