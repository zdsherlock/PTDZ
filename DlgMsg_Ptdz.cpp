// DlgMsg_Ptdz.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgMsg_Ptdz.h"
#include "afxdialogex.h"


// CDlgMsg_Ptdz �Ի���

IMPLEMENT_DYNAMIC(CDlgMsg_Ptdz, CDialog)

CDlgMsg_Ptdz::CDlgMsg_Ptdz(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsg_Ptdz::IDD, pParent)
{
	//��ʼcomtype,comtype��������ҵ������
	m_strComtypeJichu = _T("'503','504','507','501','512','510','511','513','505','506','509','502'");
	m_strComtypeZhu = _T("'201','202','203','204','205'");
	m_strComtypeLiang = _T("'101','102','104','105','106','107','109','111','112','113','114'");
	m_strComtypeBan = _T("'401','402','404','405'");
	m_strComtypeWall_JZ = _T("'304','305','306','307','309'");
	m_strComtypeWall_JG = _T("'302','303','308','317'");
	m_strComtypeLouti = _T("'403','408'");
	m_strComtypeDoor = _T("'601'");
	m_strComtypeWindow = _T("'602'");
	m_strComtypeDecorate = _T("'702','703','704','705','706','707','710','711','712','713'");
	m_strComtypeScatter = _T("'801','802','803','804','805','807','808','811','813','814','815','816','817'");
	m_strComtypeTufang = _T("'1301','1302','1303'");
}

CDlgMsg_Ptdz::~CDlgMsg_Ptdz()
{
}

void CDlgMsg_Ptdz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDlgMsg_Ptdz::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strMainIniPath = GetMainIniPath();
	if (m_strMainIniPath.IsEmpty())
	{
		AfxMessageBox(_T("maininfo.ini�ļ���FilePath��ȡΪ��!"));
		return TRUE;
	}

	//���幤�����ݿ�·��,ҵ��ָ��
	m_strAnswerDBPath = PmMfc::Fun::SplitFileDir(m_strMainIniPath) + _T("\\answerData.db");	

	//���幤��ѹ���ļ�·����ҵ��ָ��
	m_strGongChenZipPath = PmMfc::Fun::SplitFileDir(m_strMainIniPath) + _T("\\result.zip");   

	//��ȡmaininfo.ini�еĶԷ��ͻ��˾��
	PmMfc::Fun::ReadIniFileInfo(_T("AppInfo"),_T("fatherHWnd"), m_strHwnd_PTDZ ,m_strMainIniPath);	

	//��дslHWnd��slProcessId�ֶ�
	DWORD dwProcessId = GetCurrentProcessId();
	CString strProcessId;
	strProcessId.Format(_T("%d"), dwProcessId);
	PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("tjProcessId"), strProcessId ,m_strMainIniPath);	

	HWND hWnd = GetSafeHwnd();
	CString strHwnd;
	strHwnd.Format(_T("%d"), hWnd);
	PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("tjHWnd"), strHwnd ,m_strMainIniPath);	

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgMsg_Ptdz, CDialog)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

CString CDlgMsg_Ptdz::GetMainIniPath()	
{
	//��ȡimProjectInfo.ini·��
	CString strMainIniPath;
	CString strIniPath = _T("C:\\TEMP\\simProjectInfo.ini");

	//���н�ini·����ȡmaininfo.ini·��
	PmMfc::Fun::ReadIniFileInfo(_T("AppInfo"),_T("FilePath"), strMainIniPath ,strIniPath);
	return strMainIniPath;
}

void CDlgMsg_Ptdz::ExportGongChen(const CString& strDesPath)
{
	try
	{
		CZipFileManager zip;
		CString strKeyValue;
		CString strProjDir = CConnectManager::Instance()->GetFileDir(CPmDataBase::Project);		
		CString strIniFilePath = CConnectManager::Instance()->GetIniPath(CPmDataBase::Project);	

		PmMfc::Fun::ReadIniFileInfo(_T("Project"),_T("RunMode"), strKeyValue ,strIniFilePath);	

		PmMfc::Fun::WriteIniFileInfo(_T("Project"),_T("RunMode"), _T("0") ,strIniFilePath);		

		BOOL bOk = zip.ZipFolder(strDesPath, strProjDir, FALSE);								

		PmMfc::Fun::WriteIniFileInfo(_T("Project"),_T("RunMode"), strKeyValue ,strIniFilePath);	
	}
	catch(...)
	{
		m_strErrorMsg += _T("����ѹ���쳣;");
	}
}

void CDlgMsg_Ptdz::ExportTable(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	try
	{
		//����������
		ExportTable_JiChu(strAnswerDBPath, strProjectDBPath);
		ExportTable_Liang(strAnswerDBPath, strProjectDBPath);
		ExportTable_Zhu(strAnswerDBPath, strProjectDBPath);
		ExportTable_Ban(strAnswerDBPath, strProjectDBPath);
		ExportTable_Wall_JZ(strAnswerDBPath, strProjectDBPath);
		ExportTable_Wall_JG(strAnswerDBPath, strProjectDBPath);
		ExportTable_MenChuang(strAnswerDBPath, strProjectDBPath);
		ExportTable_Louti(strAnswerDBPath, strProjectDBPath);
		ExportTable_Other(strAnswerDBPath, strProjectDBPath);

		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eJiChu);
		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eZhu);
		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eLiang);
		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eBan);
		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eLouti);
		ExportTable_GJ(strAnswerDBPath, strProjectDBPath, eWall_JG);
	}
	catch(...)
	{
		m_strErrorMsg += _T("���ݿ⵼���쳣;");
	}
}

void CDlgMsg_Ptdz::ExportTable_JiChu(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase answerDB(strAnswerDBPath);
	CSqliteDBStmt answerStmt(&answerDB);
	answerStmt.Begin();

	//������ݱ�
	CString strSQL = _T("DROP TABLE IF EXISTS jichu");
	answerStmt.Exec(strSQL);

	//�����µı�
	strSQL = (_T("CREATE TABLE jichu(\n\
									 id INTEGER,\n\
									 comtype INTEGER,--����\n\
									 calitemname TEXT,--ɸѡʵ��\n\
									 unit TEXT,--ɸѡm3\n\
									 mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
									 vectorparms BLOB,--��������\n\
									 tqd TEXT,--���������\n\
									 gcl REAL,--������\n\
									 PRIMARY KEY (id))"));
	answerStmt.Exec(strSQL);


	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase projectDB(strProjectDBPath);
	CSqliteDBStmt projectStmt(&projectDB);

	//��ȡresult������
	strSQL.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							FROM result AS R\
								LEFT OUTER JOIN components AS C\
									ON R.comid = C.id\
							WHERE C.comtype IN (%s)"), m_strComtypeJichu);

	projectStmt.Prepare(strSQL);
	int rc = projectStmt.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSQLNew_Insert = _T("INSERT INTO jichu(comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
										  VALUES (:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	answerStmt.Prepare(strSQLNew_Insert);

	while(SQLITE_ROW == rc)
	{
		projectStmt.Column_Int(_T("comtype"), iComtype);
		answerStmt.Bind_Int(_T(":comtype"),iComtype);

		projectStmt.Column_Text(_T("calitemname"), strCalitemname);
		answerStmt.Bind_Text(_T(":calitemname"),strCalitemname);

		projectStmt.Column_Text(_T("unit"), strUnit);
		answerStmt.Bind_Text(_T(":unit"),strUnit);

		projectStmt.Column_Int(_T("mainmode"), imainmode);
		answerStmt.Bind_Int(_T(":mainmode"),imainmode);

		projectStmt.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		answerStmt.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		projectStmt.Column_Int(_T("comid"), iComid);
		projectStmt.Column_Text(_T("cadhandle"), strHandle);
		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		answerStmt.Bind_Text(_T(":tqd"), strTqd);

		projectStmt.Column_Double(_T("quantity"), dQuantity);
		answerStmt.Bind_Double(_T(":gcl"), dQuantity);

		answerStmt.Step();
		answerStmt.Reset();

		rc = projectStmt.Step();
	}
	answerStmt.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Zhu(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS zhu");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
	CString strSqlNew = (_T("CREATE TABLE zhu(id INTEGER,\
											  comid INTEGER,--��cadhandle����ͳ�Ƹ���\n\
											  comtype INTEGER,--����\n\
											  cadhandle TEXT,--��comid����ͳ�Ƹ���\n\
											  calitemname TEXT,--ɸѡʵ��\n\
											  unit TEXT,--ɸѡm3\n\
											  mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
											  vectorparms BLOB,--��������\n\
											  tqd TEXT,--���������\n\
											  gcl REAL,--������\n\
											  PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						 FROM result AS R\
							  LEFT OUTER JOIN components AS C\
							       ON R.comid = C.id\
						 WHERE C.comtype IN (%s)"), m_strComtypeZhu);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	int iComid = 0;
	int iComtype = 0;
	CString strHandle;
	CString strCalitem;
	CString strUnit;
	int iMainmode = 0;
	const void *pBuffer = NULL;
	long lBufferSize = 0;
	CString strTqd;
	double dQuantity = 0.0;

	CString strSQLNew_Insert = _T("INSERT INTO zhu(comid,comtype,cadhandle,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
										  VALUES (:comid,:comtype,:cadhandle,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");
	stmtNew.Prepare(strSQLNew_Insert);
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"), iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitem);
		stmtNew.Bind_Text(_T(":calitemname"), strCalitem);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"), strUnit);

		stmtOld.Column_Int(_T("mainmode"), iMainmode);
		stmtNew.Bind_Int(_T(":mainmode"), iMainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer, lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"), pBuffer, lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();

}

void CDlgMsg_Ptdz::ExportTable_Ban(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS ban");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
	CString strSqlNew = (_T("CREATE TABLE ban(id INTEGER,\
											  comtype INTEGER,--����\n\
											  width TEXT,--���\n\
											  calitemname TEXT,--ɸѡʵ��\n\
											  unit TEXT,--ɸѡm3\n\
											  mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
											  tqd TEXT,--���������\n\
											  gcl REAL,--������\n\
											  PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						 FROM result AS R\
							  LEFT OUTER JOIN components AS C\
								   ON R.comid = C.id\
						 WHERE C.comtype IN (%s)"), m_strComtypeBan);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	int iComid = 0;
	int iComtype = 0;
	CString strHandle;
	CString strCalitem;
	CString strUnit;
	int iMainmode = 0;
	const void *pBuffer = NULL;
	long lBufferSize = 0;
	CString strTqd;
	double dQuantity = 0.0;
	CString strWidth;
	CString strSQLNew_Insert = _T("INSERT INTO ban(comtype,width,calitemname,unit,mainmode,tqd,gcl)\
										  VALUES (:comtype,:width,:calitemname,:unit,:mainmode,:tqd,:gcl)");
	stmtNew.Prepare(strSQLNew_Insert);
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"), iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitem);
		stmtNew.Bind_Text(_T(":calitemname"), strCalitem);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"), strUnit);

		stmtOld.Column_Int(_T("mainmode"), iMainmode);
		stmtNew.Bind_Int(_T(":mainmode"), iMainmode);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		stmtOld.Column_Int(_T("comid"), iComid);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("Width") , strWidth ) ;
		stmtNew.Bind_Text(_T(":width"), strWidth);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();

}

void CDlgMsg_Ptdz::ExportTable_Liang(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS liang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew = (_T("CREATE TABLE liang(\n\
												id INTEGER,\n\
												comtype INTEGER,--����\n\
												calitemname TEXT,--ɸѡʵ��\n\
												unit TEXT,--ɸѡm3\n\
												mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
												vectorparms BLOB,--��������\n\
												tqd TEXT,--���������\n\
												gcl REAL,--������\n\
												PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld;
	strSqlOld.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							FROM result AS R\
								LEFT OUTER JOIN components AS C\
									ON R.comid = C.id\
							WHERE C.comtype IN (%s)"), m_strComtypeLiang);

	stmtOld.Prepare(strSqlOld);
	rc = stmtOld.Step();
		
	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSqlInsert = _T("INSERT INTO liang(comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
									  VALUES (:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		stmtOld.Column_Int(_T("comid"), iComid);
		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Wall_JZ(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{

	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jz");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jz(id INTEGER,\
													  comtype INTEGER,--����\n\
													  width TEXT,--ǽ��\n\
													  calitemname TEXT,--ɸѡʵ��\n\
													  unit TEXT,--ɸѡm3\n\
													  mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
													  tqd TEXT,--���������\n\
													  gcl REAL,--������\n\
													  PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
								  LEFT OUTER JOIN components AS C\
									   ON R.comid = C.id\
							 WHERE C.comtype IN (%s)"), m_strComtypeWall_JZ);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	CString strWidth;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSqlInsert = _T("INSERT INTO wall_jz(comtype,width,calitemname,unit,mainmode,tqd,gcl)\
									  VALUES (:comtype,:width,:calitemname,:unit,:mainmode,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		stmtOld.Column_Int(_T("comid"), iComid);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("Width") , strWidth ) ;
		stmtNew.Bind_Text(_T(":width"), strWidth);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Wall_JG(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jg");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jg(id INTEGER,\
													  comtype INTEGER,--����\n\
													  calitemname TEXT,--ɸѡʵ��\n\
													  unit TEXT,--ɸѡm3\n\
													  mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
													  vectorparms BLOB,--��������\n\
													  tqd TEXT,--���������\n\
													  gcl REAL,--������\n\
													  PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
								  LEFT OUTER JOIN components AS C\
									   ON R.comid = C.id\
							 WHERE C.comtype IN (%s)"), m_strComtypeWall_JG);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSqlInsert = _T("INSERT INTO wall_jg(comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
									  VALUES (:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Louti(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS louti");

	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE louti(id INTEGER,\
													comtype INTEGER,--����\n\
													calitemname TEXT,--ɸѡʵ��\n\
													unit TEXT,--ɸѡm3\n\
													mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
													vectorparms BLOB,--��������\n\
													tqd TEXT,--���������\n\
													gcl REAL,--������\n\
													PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.transformula\
							 FROM result AS R\
								  LEFT OUTER JOIN components AS C\
									   ON R.comid = C.id\
							 WHERE C.comtype IN (%s)"), m_strComtypeLouti);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dtransformula = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSqlInsert = _T("INSERT INTO louti(comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
									  VALUES (:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("transformula"), dtransformula);
		stmtNew.Bind_Double(_T(":gcl"), dtransformula);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_MenChuang(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS menchuang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew = (_T("CREATE TABLE menchuang(id INTEGER,\
													comid INTEGER,--��cadhandle����ͳ�Ƹ���\n\
													comtype INTEGER,--����\n\
													cadhandle TEXT,--��comid����ͳ�Ƹ���\n\
													vectorparms BLOB,--��������\n\
													PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld;
	strSqlOld.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,C.vectorparms\
						 FROM result AS R\
							  LEFT OUTER JOIN components AS C\
								   ON R.comid = C.id\
						 WHERE C.comtype IN (%s) OR\
						 C.comtype IN (%s)"), m_strComtypeDoor,m_strComtypeWindow);

	stmtOld.Prepare(strSqlOld);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSQLNew_Insert = _T("INSERT INTO menchuang(comid,comtype,cadhandle,vectorparms)\
										  VALUES (:comid,:comtype,:cadhandle,:vectorparms)");

	stmtNew.Prepare(strSQLNew_Insert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Other(const CString& strAnswerDBPath, const CString& strProjectDBPath)
{
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS other");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE other(id INTEGER,\
													comtype INTEGER,--���Ϳ�����ɸѡ\n\
													calitemname TEXT,--ɸѡʵ��\n\
													unit TEXT,--ɸѡm3\n\
													mainmode INTEGER,--ɸѡ�嵥����ģʽ\n\
													vectorparms BLOB,--��������\n\
													tqd TEXT,--���������\n\
													gcl REAL,--������\n\
													PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							 FROM result AS R\
								  LEFT OUTER JOIN components AS C\
									   ON R.comid = C.id\
							 WHERE C.comtype IN (%s) OR\
							 C.comtype IN (%s) OR\
							 C.comtype IN (%s)"), m_strComtypeDecorate, m_strComtypeLouti, m_strComtypeTufang);

	stmtOld.Prepare(strSqlOld_gcl);
	rc = stmtOld.Step();

	int iComtype = 0;
	int iComid = 0;
	int imainmode = 0;
	long lBufferSize = 0;
	const void* pBuffer = NULL;
	CString strMainmode;
	CString strHandle;
	CString strCalitemname;
	CString strUnit;
	double dQuantity = 0.0;
	//�ӹ������ݿ��ȡ���ݲ������½����ݿ�
	CString strSqlInsert = _T("INSERT INTO other(comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
								      VALUES (:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);

		stmtOld.Column_Text(_T("calitemname"), strCalitemname);
		stmtNew.Bind_Text(_T(":calitemname"),strCalitemname);

		stmtOld.Column_Text(_T("unit"), strUnit);
		stmtNew.Bind_Text(_T(":unit"),strUnit);

		stmtOld.Column_Int(_T("mainmode"), imainmode);
		stmtNew.Bind_Int(_T(":mainmode"),imainmode);

		stmtOld.Column_Blob(_T("vectorparms"), pBuffer,lBufferSize);
		stmtNew.Bind_Blob(_T(":vectorparms"),pBuffer,lBufferSize);

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

		CString strTqd = CUICommonCallBack::CallGetTqd(iComid, strHandle);
		stmtNew.Bind_Text(_T(":tqd"), strTqd);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_GJ(const CString& strAnswerDBPath, const CString& strProjectDBPath, const GJLX eGjlx)
{
	CString strComtypes;
	CSqliteDataBase dbNew(strAnswerDBPath);
	CSqliteDBStmt stmtNew(&dbNew);
	CSqliteDataBase dbOld(strProjectDBPath);
	CSqliteDBStmt stmtOld(&dbOld);
	stmtNew.Begin();

	//����comtype���зֱ�
	CString strTableName;

	switch (eGjlx)
	{
	case eJiChu:
		{
			strTableName = _T("jichu_gj");
			strComtypes = m_strComtypeJichu;
			break;
		}
	case eZhu:
		{
			strTableName = _T("zhu_gj");
			strComtypes = m_strComtypeZhu;
			break;
		}
	case eLiang:
		{
			strTableName = _T("liang_gj");
			strComtypes = m_strComtypeLiang;
			break;
		}
	case eBan:
		{
			strTableName = _T("ban_gj");
			strComtypes = m_strComtypeBan;
			break;
		}
	case eWall_JG:
		{
			strTableName = _T("wall_jg_gj");
			strComtypes = m_strComtypeWall_JG;
			break;
		}
	case eLouti:
		{
			strTableName = _T("louti_gj");
			strComtypes = m_strComtypeLouti;
			break;
		}
	default:
		break;
	}

	CString strSQL_Del;
	strSQL_Del.Format(_T("DROP TABLE IF EXISTS %s"), strTableName);
	stmtNew.Exec(strSQL_Del);

	//��ԭ����ȡ���ݴ��뵽�±����
	CString strSQLNew;
	strSQLNew.Format(_T("CREATE TABLE %s(id INTEGER,\
										 comtype INTEGER,--����\n\
										 gjjb TEXT,--�ֽ��\n\
										 zj REAL,--�ֽ�ֱ��\n\
										 zz_gj REAL,--�ֽ�����\n\
										 PRIMARY KEY (id))"), strTableName);
	stmtNew.Exec(strSQLNew);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT G.comid,C.comtype,G.gjjb,G.zj,G.zz*G.cc_count AS zz_gj\
						 FROM graphicsresultv2 AS G\
						      LEFT OUTER JOIN components AS C\
						           ON G.comid = C.id\
						 WHERE C.comtype IN (%s)"), strComtypes);
	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	CString strSQLNew_Insert;
	strSQLNew_Insert.Format(_T("INSERT INTO %s(comtype,gjjb,zj,zz_gj)\
							           VALUES (:comtype,:gjjb,:zj,:zz_gj)"), strTableName);
	stmtNew.Prepare(strSQLNew_Insert);

	int iComid = 0;
	int icomtype = 0;
	CString strGjjb;
	double dzj = 0.0;
	double dzz = 0.0;
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);

		stmtOld.Column_Int(_T("comtype"), icomtype);
		stmtNew.Bind_Int(_T(":comtype"), icomtype);

		stmtOld.Column_Text(_T("gjjb"), strGjjb);
		stmtNew.Bind_Text(_T(":gjjb"), strGjjb);

		stmtOld.Column_Double(_T("zj"), dzj);
		stmtNew.Bind_Double(_T(":zj"), dzj);

		stmtOld.Column_Double(_T("zz_gj"), dzz);
		stmtNew.Bind_Double(_T(":zz_gj"), dzz);

		stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}

	stmtNew.Commit();
}

// CDlgMsg_Ptdz ��Ϣ�������
BOOL CDlgMsg_Ptdz::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	try
	{
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		WCHAR* pwChar = static_cast<WCHAR*>(pCopyDataStruct->lpData);

		CString strAutoCmp = _T("{\"command\":\"autoCmp\"}");
		CString strQuit = _T("{\"command\":\"quit\"}");
		CString strSendMsg;
		//��ȡ��ǰ����·��
		CString strFilePath = CConnectManager::Instance()->GetFileDir(CPmDataBase::Project);

		//���嵱ǰ����project��
		CString strFilePathDBProject = strFilePath + _T("\\project.pmdb");

		if (0 == strAutoCmp.CompareNoCase(pwChar))
		{
			//��ָ��·���������ݿ�͹���ѹ���ļ���

				ExportTable(m_strAnswerDBPath, strFilePathDBProject);
				ExportGongChen(m_strGongChenZipPath);

			//��maininfo.ini�ļ��е�newAnswer��resultFile�ֶ�����д��Ӧ�ļ�·��
			BOOL bAnswer = PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("newAnswer"), m_strGongChenZipPath, m_strMainIniPath);	
			BOOL bResult = PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("resultFile"), m_strAnswerDBPath, m_strMainIniPath);	

			if (FALSE == bAnswer)
			{
				m_strErrorMsg += _T("maininfo.ini�ļ���newAnswer�ֶ�д��ʧ��;");
			}

			if (FALSE == bResult)
			{
				m_strErrorMsg += _T("maininfo.ini�ļ���resultFile�ֶ�д��ʧ��;");
			}

			//ͨ�������ȡ���������������
			if (m_strErrorMsg.IsEmpty())	
			{	
				strSendMsg =_T("{\"result\":0,\"message\":\"\"}");
			}
			else
			{
				//���û��������ȡ��ini�ļ�
				strSendMsg.Format(_T("{\"result\":1,\"message\":\"%s\"}"), m_strErrorMsg);
			}
	
			//����ȡ��cstring��� ת��Ϊ hwnd;
			HWND hwnd_PTDZ = reinterpret_cast<HWND>(_ttoi(m_strHwnd_PTDZ));

			if (pWnd)
			{
				COPYDATASTRUCT cpd;

				cpd.dwData = 0;
				cpd.cbData = (strSendMsg.GetLength()+1)*sizeof(TCHAR);
				cpd.lpData = strSendMsg.GetBuffer();

				::SendMessage(hwnd_PTDZ, WM_COPYDATA, NULL, reinterpret_cast<LPARAM>(&cpd));
			}
		}
		else if (0 == strQuit.CompareNoCase(pwChar))
		{
			SL_UIFunction::sendCmdLine(_T("PMSaveProject"));
			SL_UIFunction::sendCmdLine(_T("quit"));
		}
	}
	catch (...)
	{
		//��ֹ����
	}
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}