// OPTS.cpp : 实现文件
//

#include "stdafx.h"
#include "WORK.h"
#include "OPTS.h"
#include "afxdialogex.h"
#include "ADD.h"
#include "UPDATE.h"

// GLOBAL HERE
CString eNAME, eID, eCOUNT, eREMARKS,eUID;
// OPTS 对话框

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
	_RecordsetPtr  m_pRecordset;//数据集连接
	_variant_t vNAME, vID, vCOUNT, vREMARKS;	//存放取出来的数据的变量
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			MessageBox(_T("连接成功"));
			///连接数据库
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// 至少输入ID和NAME中的一项，若均输入则默认取NAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///显示错误信息
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
			AfxMessageBox(message);///显示错误信息
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
			MessageBox(result);///显示错误信息
			return;
		}
	}

	catch (_com_error e) {
		MessageBox(e.ErrorMessage());///显示错误信息
		return;
	}

}


void OPTS::OnBnClickedDelete()
{
	_RecordsetPtr  m_pRecordset;//数据集连接
	_variant_t vNAME, vID, vCOUNT, vREMARKS;	//存放取出来的数据的变量
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			MessageBox(_T("连接成功"));
			///连接数据库
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// 至少输入ID和NAME中的一项，若均输入则默认取NAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///显示错误信息
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

		MessageBox(_T("SUCCEED"));///显示错误信息
		return;
	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(_T("FAILED!"));
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}

}



void OPTS::OnBnClickedAdd()
{
	ADD DLG;
	DLG.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void OPTS::OnBnClickedChange()
{


	_RecordsetPtr  m_pRecordset;//数据集连接
	_variant_t vNAME, vID, vCOUNT, vREMARKS,vUID;	//存放取出来的数据的变量
	CString name, id, count, remarks;

	// establishing connection
	_ConnectionPtr m_pConnection;
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if (SUCCEEDED(hr))
		{
			hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= test1.mdb", "", "", adModeUnknown);
			///连接数据库
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format(_T("连接数据库失败!\r\n:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}


	// this is the QUERY SECTION
	try {
		CString strSQL;

		GetDlgItem(IDC_EDIT1)->GetWindowText(name);
		GetDlgItem(IDC_EDIT2)->GetWindowText(id);

		// 至少输入ID和NAME中的一项，若均输入则默认取NAME
		if (name.IsEmpty() && id.IsEmpty()) {
			CString errormessage;
			errormessage.Format(_T("ENTER 1 ENTRY AT LEAST"));
			AfxMessageBox(errormessage);///显示错误信息
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
			AfxMessageBox(message);///显示错误信息
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
		errormessage.Format(_T("查询数据库失败!\r\n错误信:%s", e.ErrorMessage()));
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	
	UPDATE DLG;
	DLG.DoModal();

}
