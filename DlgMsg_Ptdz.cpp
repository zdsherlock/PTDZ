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

	//��ȡ��ǰ����·��
	CString strFilePath = CConnectManager::Instance()->GetFileDir(CPmDataBase::Project);

	//���嵱ǰ����project��
	m_strPMDB = strFilePath + _T("\\project.pmdb");

	//���幤�����ݿ�·��,ҵ��ָ��
	m_strDataBasePath = PmMfc::Fun::SplitFileDir(GetMainIniPath()) + _T("\\newAnswerData.db");	

	//���幤��ѹ���ļ�·����ҵ��ָ��
	m_strGongChenZipPath = PmMfc::Fun::SplitFileDir(GetMainIniPath()) + _T("\\result.zip");   

	//��ȡmaininfo.ini�еĶԷ��ͻ��˾��
	PmMfc::Fun::ReadIniFileInfo(_T("AppInfo"),_T("fatherHWnd"), m_strHwnd_PTDZ ,GetMainIniPath());	

	//��дslHWnd��slProcessId�ֶ�
	DWORD dwProcessId = GetCurrentProcessId();
	CString strProcessId;
	strProcessId.Format(_T("%d"), dwProcessId);
	PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("slProcessId"), strProcessId ,GetMainIniPath());	

	HWND hWnd = GetSafeHwnd();
	CString strHwnd;
	strHwnd.Format(_T("%d"), hWnd);
	PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("slHWnd"), strHwnd ,GetMainIniPath());	

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgMsg_Ptdz, CDialog)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

CString CDlgMsg_Ptdz::GetMainIniPath()	
{
	//��ȡimProjectInfo.ini·��
	CString strIniPath = _T("C:\\TEMP\\simProjectInfo.ini");
	CString strMainIniPath;

	//���н�ini·����ȡmaininfo.ini·��
	BOOL bOk = PmMfc::Fun::ReadIniFileInfo(_T("AppInfo"),_T("FilePath"), strMainIniPath ,strIniPath);	

	return strMainIniPath;
}

void CDlgMsg_Ptdz::ExportTable(const CString& strFilePathNew, const CString& strFilePathOld)
{
	//����������
	ExportTable_JiChu(strFilePathNew, strFilePathOld);
	ExportTable_Liang(strFilePathNew, strFilePathOld);
	ExportTable_Zhu(strFilePathNew, strFilePathOld);
	ExportTable_Ban(strFilePathNew, strFilePathOld);
	ExportTable_Wall_JZ(strFilePathNew, strFilePathOld);
	ExportTable_Wall_JG(strFilePathNew, strFilePathOld);
	ExportTable_MenChuang(strFilePathNew, strFilePathOld);
	ExportTable_Louti(strFilePathNew, strFilePathOld);
	ExportTable_Other(strFilePathNew, strFilePathOld);

	ExportTable_GJ(strFilePathNew, strFilePathOld, eJiChu);
	ExportTable_GJ(strFilePathNew, strFilePathOld, eZhu);
	ExportTable_GJ(strFilePathNew, strFilePathOld, eLiang);
	ExportTable_GJ(strFilePathNew, strFilePathOld, eBan);
	ExportTable_GJ(strFilePathNew, strFilePathOld, eLouti);
	ExportTable_GJ(strFilePathNew, strFilePathOld, eWall_JG);
}

void CDlgMsg_Ptdz::ExportTable_JiChu(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS jichu");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew = (_T("CREATE TABLE jichu(\n\
												id INTEGER,\n\
												comid INTEGER,--����Զ���ID���湹������\n\
												comtype INTEGER,--��������\n\
												calitemname TEXT,--��Ŀ����\n\
												unit TEXT,--��λ\n\
												mainmode INTEGER,--�嵥����ģʽ\n\
												vectorparms BLOB,--��������\n\
												tqd TEXT,--���������\n\
												gcl REAL,--������\n\
												PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld;
	strSqlOld.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
						 FROM result AS R\
							  LEFT OUTER JOIN components AS C\
								   ON R.comid = C.id\
						 WHERE C.comtype IN (%s)"), m_strComtypeJichu);

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
	CString strSQLNew_Insert = _T("INSERT INTO jichu(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
										  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSQLNew_Insert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

void CDlgMsg_Ptdz::ExportTable_Zhu(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS zhu");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
	CString strSqlNew = (_T("CREATE TABLE zhu(id INTEGER,\
											  comid INTEGER,\
											  comtype INTEGER,\
											  cadhandle TEXT,\
											  calitemname TEXT,\
											  unit TEXT,\
											  mainmode INTEGER,\
											  vectorparms BLOB,\
											  tqd TEXT,\
											  gcl REAL,\
											  PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						FROM result AS R\
						LEFT OUTER JOIN components AS C\
						ON R.comid = C.id\
						WHERE C.comtype IN (%s)"), m_strComtypeZhu);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	if (SQLITE_ROW != rc)
	{
		AfxMessageBox(stmtOld.ErrMsg());
	}

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

void CDlgMsg_Ptdz::ExportTable_Ban(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);

	//���������ݿ��-��������
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS ban");
	stmtNew.Exec(strSQL_DEL);

	//�����µĹ������͸ֽ��
	CString strSqlNew = (_T("CREATE TABLE ban(id INTEGER,\
							comid INTEGER,\
							comtype INTEGER,\
							width TEXT,\
							cadhandle TEXT,\
							calitemname TEXT,\
							unit TEXT,\
							mainmode INTEGER,\
							tqd TEXT,\
							gcl REAL,\
							PRIMARY KEY (id))"));
	stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	CString strSQLOld;
	strSQLOld.Format(_T("SELECT *\
						FROM result AS R\
						LEFT OUTER JOIN components AS C\
						ON R.comid = C.id\
						WHERE C.comtype IN (%s)"), m_strComtypeBan);

	stmtOld.Prepare(strSQLOld);
	int rc = stmtOld.Step();

	if (SQLITE_ROW != rc)
	{
		AfxMessageBox(stmtOld.ErrMsg());
	}

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
	CString strSQLNew_Insert = _T("INSERT INTO ban(comid,comtype,width,cadhandle,calitemname,unit,mainmode,tqd,gcl)\
								  VALUES (:comid,:comtype,:width,:cadhandle,:calitemname,:unit,:mainmode,:tqd,:gcl)");
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

		stmtOld.Column_Double(_T("quantity"), dQuantity);
		stmtNew.Bind_Double(_T(":gcl"), dQuantity);

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

void CDlgMsg_Ptdz::ExportTable_Liang(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS liang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE liang(id INTEGER,\
								comid INTEGER,\
								comtype INTEGER,\
								calitemname TEXT,\
								unit TEXT,\
								mainmode INTEGER,\
								vectorparms BLOB,\
								tqd TEXT,\
								gcl REAL,\
								PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
	CSqliteDBStmt stmtOld(&dbOld);

	//��ȡresult������
	CString strSqlOld_gcl;
	strSqlOld_gcl.Format(_T("SELECT R.comid,C.comtype,R.cadhandle,R.calitemname,R.unit,R.mainmode,C.vectorparms,R.quantity\
							FROM result AS R\
							LEFT OUTER JOIN components AS C\
							ON R.comid = C.id\
							WHERE C.comtype IN (%s)"), m_strComtypeJichu);

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
	CString strSqlInsert = _T("INSERT INTO liang(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
							  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

void CDlgMsg_Ptdz::ExportTable_Wall_JZ(const CString& strFilePathNew, const CString& strFilePathOld)
{

	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jz");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jz(id INTEGER,\
								comid INTEGER,\
								comtype INTEGER,\
								width TEXT,\
								calitemname TEXT,\
								unit TEXT,\
								mainmode INTEGER,\
								tqd TEXT,\
								gcl REAL,\
								PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
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
	CString strSqlInsert = _T("INSERT INTO wall_jz(comid,comtype,width,calitemname,unit,mainmode,tqd,gcl)\
							  VALUES (:comid,:comtype,:width,:calitemname,:unit,:mainmode,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

		CComponentsContainer::GetComAttribute( iComid , CComParmsSet_ParmName::SL_ParmType , _T("Width") , strWidth ) ;
		stmtNew.Bind_Text(_T(":width"), strWidth);

		rc = stmtNew.Step();
		stmtNew.Reset();

		rc = stmtOld.Step();
	}
	stmtNew.Commit();
}

void CDlgMsg_Ptdz::ExportTable_Wall_JG(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS wall_jg");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE wall_jg(id INTEGER,\
								comid INTEGER,\
								comtype INTEGER,\
								calitemname TEXT,\
								unit TEXT,\
								mainmode INTEGER,\
								vectorparms BLOB,\
								tqd TEXT,\
								gcl REAL,\
								PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
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
	CString strSqlInsert = _T("INSERT INTO wall_jg(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
							  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

void CDlgMsg_Ptdz::ExportTable_Louti(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS louti");

	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE louti(id INTEGER,\
								comid INTEGER,\
								comtype INTEGER,\
								calitemname TEXT,\
								unit TEXT,\
								mainmode INTEGER,\
								vectorparms BLOB,\
								tqd TEXT,\
								gcl REAL,\
								PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
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
	CString strSqlInsert = _T("INSERT INTO louti(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
							  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

void CDlgMsg_Ptdz::ExportTable_MenChuang(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS menchuang");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew = (_T("CREATE TABLE menchuang(id INTEGER,\
							comid INTEGER,\
							comtype INTEGER,\
							cadhandle TEXT,\
							vectorparms BLOB,\
							PRIMARY KEY (id))"));
	int rc = stmtNew.Exec(strSqlNew);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
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

void CDlgMsg_Ptdz::ExportTable_Other(const CString& strFilePathNew, const CString& strFilePathOld)
{
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	stmtNew.Begin();

	//������ݱ�
	CString strSQL_DEL = _T("DROP TABLE IF EXISTS other");
	stmtNew.Exec(strSQL_DEL);

	//�����µı�
	CString strSqlNew_GCL = (_T("CREATE TABLE other(id INTEGER,\
													comid INTEGER,\
													comtype INTEGER,\
													calitemname TEXT,\
													unit TEXT,\
													mainmode INTEGER,\
													vectorparms BLOB,\
													tqd TEXT,\
													gcl REAL,\
													PRIMARY KEY (id))"));

	int rc = stmtNew.Exec(strSqlNew_GCL);

	//�򿪹���project���ݿ�������ݻ�ȡ
	CSqliteDataBase dbOld(strFilePathOld);
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
	CString strSqlInsert = _T("INSERT INTO other(comid,comtype,calitemname,unit,mainmode,vectorparms,tqd,gcl)\
							  VALUES (:comid,:comtype,:calitemname,:unit,:mainmode,:vectorparms,:tqd,:gcl)");

	stmtNew.Prepare(strSqlInsert);

	while(SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"),iComid);

		stmtOld.Column_Int(_T("comtype"), iComtype);
		stmtNew.Bind_Int(_T(":comtype"),iComtype);

		stmtOld.Column_Text(_T("cadhandle"), strHandle);
		stmtNew.Bind_Text(_T(":cadhandle"), strHandle);

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

void CDlgMsg_Ptdz::ExportTable_GJ(const CString& strFilePathNew, const CString& strFilePathOld, const GJLX eGjlx)
{
	CString strComtypes;
	CSqliteDataBase dbNew(strFilePathNew);
	CSqliteDBStmt stmtNew(&dbNew);
	CSqliteDataBase dbOld(strFilePathOld);
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
						comid INTEGER,\
						comtype INTEGER,\
						gjjb TEXT,\
						zj REAL,\
						zz_gj REAL,\
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
	strSQLNew_Insert.Format(_T("INSERT INTO %s(comid,comtype,gjjb,zj,zz_gj)\
							   VALUES (:comid,:comtype,:gjjb,:zj,:zz_gj)"), strTableName);
	stmtNew.Prepare(strSQLNew_Insert);

	int iComid = 0;
	int icomtype = 0;
	CString strGjjb;
	double dzj = 0.0;
	double dzz = 0.0;
	while (SQLITE_ROW == rc)
	{
		stmtOld.Column_Int(_T("comid"), iComid);
		stmtNew.Bind_Int(_T(":comid"), iComid);

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

void CDlgMsg_Ptdz::ExportGongChen(const CString& strDesPath)
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

// CDlgMsg_Ptdz ��Ϣ�������
BOOL CDlgMsg_Ptdz::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WCHAR* pwChar = static_cast<WCHAR*>(pCopyDataStruct->lpData);

	CString strAutoCmp = _T("\"command\":\"autoCmp\"");
	CString strQuit = _T("\"command\":\"quit\"");
	CString strSendData;

	if (0 == strAutoCmp.CompareNoCase(pwChar))
	{
		//��ָ��·���������ݿ�͹���ѹ���ļ���
		ExportTable(m_strDataBasePath, m_strPMDB);
		ExportGongChen(m_strGongChenZipPath);

		//��maininfo.ini�ļ��е�newAnswer��resultFile�ֶ�����д��Ӧ�ļ�·��
		BOOL bAnswer = PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("newAnswer"), m_strGongChenZipPath ,GetMainIniPath());	
		BOOL bResult = PmMfc::Fun::WriteIniFileInfo(_T("AppInfo"),_T("resultFile"), m_strDataBasePath ,GetMainIniPath());	

		//ͨ�������ȡ���������������
		if (bAnswer && bResult)
		{
			strSendData =_T("{\"result\":0,\"message\":\"\"}");
		}
		else
		{
			//���û��������ȡ��ini�ļ�
			strSendData =_T("{\"result\":1,\"message\":\"�޷���ȡini�ļ�\"}");
		}

		//����ȡ��cstring��� ת��Ϊ hwnd;

		HWND hwnd_PTDZ = reinterpret_cast<HWND>(_ttoi(m_strHwnd_PTDZ));

		if (pWnd)
		{
			COPYDATASTRUCT cpd;

			cpd.dwData = 0;
			cpd.cbData = (strSendData.GetLength()+1)*sizeof(TCHAR);
			cpd.lpData = strSendData.GetBuffer();

			::SendMessage(pWnd->GetSafeHwnd(), WM_COPYDATA, NULL, reinterpret_cast<LPARAM>(&cpd));//���ԣ����������1���滻��hwnd_PTDZ����޸ġ�
		}
	}
	else if (0 == strQuit.CompareNoCase(pwChar))
	{
		SL_UIFunction::sendCmdLine(_T("PMSaveProject"));
		SL_UIFunction::sendCmdLine(_T("quit"));
	}

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}