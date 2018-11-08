// chess.h : main header file for the CHESS application
//                     

#define CURSOR_MOVED 123
#define PIECE_MOVED 124
#define PIECE_MOVING 125
#define REFRESH 126
#define CASTLED 127
#define BLACK_MOVED 128
#define MESSAGE_BAR 129
#define SHOW_THINKING 130

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChessApp:
// See chess.cpp for the implementation of this class
//

class CChessDoc;

class CChessApp : public CWinApp
{
public:
	CChessApp();
	
	CChessDoc * m_pDocument;

// Overrides
	virtual BOOL InitInstance();
	virtual BOOL OnIdle( LONG lCount);
	void RunMessageLoop();
	
// Implementation

	//{{AFX_MSG(CChessApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
