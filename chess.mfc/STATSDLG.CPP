// statsdlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "statsdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg dialog

CStatsDlg::CStatsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatsDlg)
	m_lScore = 0;
	//}}AFX_DATA_INIT
}

void CStatsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatsDlg)
	DDX_Text(pDX, IDC_BLACK_SCORE, m_lScore);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatsDlg, CDialog)
	//{{AFX_MSG_MAP(CStatsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg message handlers
