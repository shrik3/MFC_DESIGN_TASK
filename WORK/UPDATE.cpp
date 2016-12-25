// UPDATE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WORK.h"
#include "UPDATE.h"
#include "afxdialogex.h"


// UPDATE �Ի���

IMPLEMENT_DYNAMIC(UPDATE, CDialog)

UPDATE::UPDATE(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UPDATE, pParent)
{

}

UPDATE::~UPDATE()
{
}

void UPDATE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(UPDATE, CDialog)
	ON_BN_CLICKED(IDOK, &UPDATE::OnBnClickedOk)
END_MESSAGE_MAP()


// UPDATE ��Ϣ�������


void UPDATE::OnBnClickedOk()
{
	extern CString eUID;
	// TODO: �ڴ���ӿؼ�֪ͨ����������


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
			//MessageBox(_T("���ӳɹ�"));
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

		strSQL2.Format(_T("Update schools Set ID=%s , AME='%s',OUNT=%s,REMARKS='%s' where UID =%s"), id,name,count,remarks,eUID); 

		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_pRecordset->Open(_variant_t(strSQL2), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdUnknown);

		MessageBox(_T("UPDATE SUCCEED!"));


	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(e.Description());
		AfxMessageBox(errormessage);///��ʾ������Ϣ
		return;
	}

	CDialog::OnOK();


}


BOOL UPDATE::OnInitDialog()
{
	extern CString eNAME, eID, eUID, eCOUNT, eREMARKS;
	CDialog::OnInitDialog();

	GetDlgItem(IDC_EDIT2)->SetWindowText(eNAME);
	GetDlgItem(IDC_EDIT3)->SetWindowText(eID);
	GetDlgItem(IDC_EDIT4)->SetWindowText(eREMARKS);
	GetDlgItem(IDC_EDIT5)->SetWindowText(eCOUNT);

	// TO

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
