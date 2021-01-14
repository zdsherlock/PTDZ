#pragma once
#include "resource.h"

// CDlgMsg_Ptdz �Ի���

class CDlgMsg_Ptdz : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg_Ptdz)
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
	CString m_strDataBasePath;

	//����ѹ���ļ�·��
	CString m_strGongChenZipPath;

	//��ǰ����project.pmdb·��
	CString m_strPMDB;

	//�ͻ���ͨ�ŵĴ��ھ��
	CString m_strHwnd_PTDZ;
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
	CDlgMsg_Ptdz(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMsg_Ptdz();

// �Ի�������
	enum { IDD = IDD_DIALOG_PTDZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	/**
	* @brief :ͨ���н�ini��ȡmaininfo.ini·��
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
	void ExportTable(const CString& strFilePathNew, const CString& strFilePathOld);
	/**
	* @brief :�����ݿ��л�ȡ��������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/4/2021]
	*/
	void ExportTable_JiChu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Zhu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Ban(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Liang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľ���ǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JZ(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ���Ľṹǽ����ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݣ��ֽ����ݵ���ȡ
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JG(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ�����źʹ�������ҵ����������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : 
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_MenChuang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����¥�ݺ��ݰ�ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݱ��ֽ����ݵ���ȡ
			   ����¥�ݺ��ݰ�
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Louti(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�Զ����װ�Ρ����ǡ�������ҵ���Զ��������������ݲ������µ����ݿ⣬������һ��ҵ������ͼ���
	*
	*          
	* @note  : ���޹��������ݱ��ֽ����ݵ���ȡ
			   ����ṹһ�·���һ��
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/5/2021]
	*/
	void ExportTable_Other(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :�����ݿ��л�ȡ�־������������ݣ��������д���
	*
	*          
	* @note  : 
	* @param : filePathNew���½������ݿ�·��
			   filePathOld�������е�project���ݿ�·��
	* @defenc: 
	* @return: 
	* @author: �¶�
	* @date  : [1/6/2021]
	*/
	void ExportTable_GJ(const CString& filePathNew, const CString& filePathOld, const GJLX eGjlx);
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
};
