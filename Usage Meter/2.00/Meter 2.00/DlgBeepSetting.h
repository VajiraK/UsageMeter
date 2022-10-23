#if !defined(AFX_DLGBEEPSETTING_H__9155CB2E_FA25_4A38_B90A_65F7738AC5AB__INCLUDED_)
#define AFX_DLGBEEPSETTING_H__9155CB2E_FA25_4A38_B90A_65F7738AC5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBeepSetting.h : header file
/////////////////////////////////////////////////////////////////////////////
// CDlgBeepSetting dialog

#include "MyBeep.h"

class CDlgBeepSetting : public CDialog
{
// Construction
public:
	CDlgBeepSetting(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CDlgBeepSetting)
	enum { IDD = IDD_BEEP_DLG };
	CEdit	m_win_inter;
	CEdit	m_win_free;
	CEdit	m_win_dur;
	CEdit	m_int_inter;
	CEdit	m_int_free;
	CEdit	m_int_dur;
	CButton	m_win_chk;
	CButton	m_int_chk;
	CStatic	m_fram;
	CTabCtrl	m_Tab_Beep;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBeepSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgBeepSetting)
	afx_msg void OnTestBeep();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangingTabBeep(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	bool m_reset_int_count, m_reset_win_count;
private:
	CMyBeep	m_beep_cls;
	int		m_old_int_interval, m_old_win_interval;
	int		m_old_int_chkstate, m_old_win_chkstate;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_DLGBEEPSETTING_H__9155CB2E_FA25_4A38_B90A_65F7738AC5AB__INCLUDED_)
