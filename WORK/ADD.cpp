// ADD.cpp : 实现文件
//

#include "stdafx.h"
#include "WORK.h"
#include "ADD.h"
#include "afxdialogex.h"


// ADD 对话框

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


// ADD 消息处理程序


void ADD::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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

		MessageBox(_T("插入成功"));


	}

	catch (_com_error e) {
		CString errormessage;
		errormessage.Format(e.Description());
		AfxMessageBox(errormessage);///显示错误信息
		return;
	}
	CDialog::OnOK();
}


void ADD::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	_ConnectionPtr m_pConnection;
	CDialog::OnCancel();

}
