#include "afxdialogex.h"
#include <sql.h>    
#include <sqltypes.h> 
#include <sqlext.h>  
#include "odbcinst.h"
#include "afxdb.h"
#include "pch.h"
/*void ConnectDB(CString sqlStmt) {
	CDatabase database;
	CString sDsn;
	//build ODBC connection string
	sDsn.Format(L"DRIVER={SQL Server};SERVER=SM89\\SQLEXPRESS12;DATABASE=QLSV;UID=sa;PWD=123;");
	TRY{
		database.Open(NULL,false,false,sDsn);
		CRecordset recset(&database);
		recset.Open(CRecordset::forwardOnly, sqlStmt,CRecordset::readOnly);
		
	} CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
	} END_CATCH
}*/
