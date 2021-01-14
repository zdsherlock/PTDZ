#pragma once
#include "resource.h"

// CDlgMsg_Ptdz 对话框

class CDlgMsg_Ptdz : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg_Ptdz)
private:
	//初始comtype,comtype定义来自业务需求
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

	//工程导出数据路径
	CString m_strDataBasePath;

	//工程压缩文件路径
	CString m_strGongChenZipPath;

	//当前工程project.pmdb路径
	CString m_strPMDB;

	//客户端通信的窗口句柄
	CString m_strHwnd_PTDZ;
	//业务定义的构件类型的枚举
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
	CDlgMsg_Ptdz(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMsg_Ptdz();

// 对话框数据
	enum { IDD = IDD_DIALOG_PTDZ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	/**
	* @brief :通过中介ini获取maininfo.ini路径
	*
	*          
	* @note  : 
	* @param : 
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/12/2021]
	*/
	CString GetMainIniPath();
	/**
	* @brief :封装所有表单的导出
	*
	*          
	* @note  : 
	* @param : 
			   
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/4/2021]
	*/
	void ExportTable(const CString& strFilePathNew, const CString& strFilePathOld);
	/**
	* @brief :从数据库中获取基础部分业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/4/2021]
	*/
	void ExportTable_JiChu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取柱大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Zhu(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取板大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Ban(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取梁大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Liang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的建筑墙大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JZ(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的结构墙大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据，钢筋数据单独取
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Wall_JG(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的门和窗两大类业务所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_MenChuang(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的楼梯和梯板业务自定义类别所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据表，钢筋数据单独取
			   包括楼梯和梯板
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Louti(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取自定义的装饰、零星、土方等业务自定义类别所需的数据并存入新的数据库，用于下一步业务分析和计算
	*
	*          
	* @note  : 仅限工程量数据表，钢筋数据单独取
			   因表单结构一致放在一起
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/5/2021]
	*/
	void ExportTable_Other(const CString& filePathNew, const CString& filePathOld);
	/**
	* @brief :从数据库中获取钢精表单的所需数据，适用所有大类
	*
	*          
	* @note  : 
	* @param : filePathNew：新建的数据库路径
			   filePathOld：工程中的project数据库路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/6/2021]
	*/
	void ExportTable_GJ(const CString& filePathNew, const CString& filePathOld, const GJLX eGjlx);
	/**
	* @brief :压缩当前工程并输出为zip格式
	*
	*          
	* @note  : 输出工程的runmode重置为零，不影响当前工程
	* @param : strDesPath 指定压缩文件保存路径
	* @defenc: 
	* @return: 
	* @author: 章东
	* @date  : [1/8/2021]
	*/
	void ExportGongChen(const CString& strDesPath);
};
