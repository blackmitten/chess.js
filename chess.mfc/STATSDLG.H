// statsdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg dialog

class CStatsDlg : public CDialog
{
// Construction
public:
	CStatsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStatsDlg)
	enum { IDD = IDD_POSITION_STATS };
	float	m_lScore;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CStatsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
