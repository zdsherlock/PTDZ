#pragma once
#include "resource.h"

// CDlgMsg_Ptdz �Ի���

class CDlgMsg_Ptdz : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg_Ptdz)
public:
	CDlgMsg_Ptdz(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMsg_Ptdz();

// �Ի�������
	enum { IDD = IDD_DIALOG_PTDZ };

private:
	//ҵ����Ĺ������͵�ö��
	enum GJLX
	{
		eJiChu,
		eZhu,
		eLiang,
		eBan,
		eLouti,
		eWall_JG,
	};

public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	/**
	* @brief :ͨ��simProjectInfo.ini��ȡmaininfo.ini·��
	*
	*          
	* @note  : 
	* @param : 
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/12/2021]
	*/
	CString GetMainIniPath();
	/**
	* @brief :��װ���б��ĵ���
	*
	*          
	* @note  : 
	* @param : 
			   
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/4/2021]
	*/
	void ExportTable(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ��������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/4/2021]
	*/
	void ExportTable_JiChu(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Zhu(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Ban(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Liang(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľ���ǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JZ(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľṹǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JG(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�Զ�����źʹ�������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : 
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_MenChuang(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����¥�ݺ��ݰ�ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݱ��ֽ����ݵ���ȡ
			   ����¥�ݺ��ݰ�
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Louti(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����װ�Ρ����ǡ�������ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݱ��ֽ����ݵ���ȡ
			   ����ṹһ�·���һ��
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Other(const CString& strAnswerDBPath, const CString& strProjectDB);
	/**
	* @brief :�����ݿ��л�ȡ�־������������ݣ��������д���
	*
	*          
	* @note  : 
	* @param : strAnswerDBPath���½������ݿ�·��
			   strProjectDB�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/6/2021]
	*/
	void ExportTable_GJ(const CString& strAnswerDBPath, const CString& strProjectDB, const GJLX eGjlx);
	/**
	* @brief :ѹ����ǰ���̲����Ϊzip��ʽ
	*
	*          
	* @note  : ������̵�runmode����Ϊ�㣬��Ӱ�쵱ǰ����
	* @param : strDesPath ָ��ѹ���ļ�����·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/8/2021]
	*/
	void ExportGongChen(const CString& strDesPath);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	//��ʼcomtype,comtype��������ҵ������
	CString m_strComtypeJichu;
	CString m_strComtypeZhu;
	CString m_strComtypeLiang;
	CString m_strComtypeBan;
	CString m_strComtypeWall_JZ;
	CString m_strComtypeWall_JG;
	CString m_strComtypeLouti;
	CString m_strComtypeDoor;
	CString m_strComtypeWindow;
	CString m_strComtypeDecorate;
	CString m_strComtypeScatter;
	CString m_strComtypeTufang;

	//���̵�������·��
	CString m_strAnswerDBPath;

	//����ѹ���ļ�·��
	CString m_strGongChenZipPath;

	//�ͻ���ͨ�ŵĴ��ھ��
	CString m_strHwnd_PTDZ;

	CString m_strErrorMsg;

	CString m_strMainIniPath;
};
