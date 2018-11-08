// chessvw.h : interface of the CChessView class
//
/////////////////////////////////////////////////////////////////////////////

class CChessView : public CView
{
protected: // create from serialization only
	CChessView();
	DECLARE_DYNCREATE(CChessView)

	CString m_sStartPos;
	CString m_sEndPos;
	BOOL m_bOnceThrough;

// Attributes
public:
	CChessDoc* GetDocument();
	void DrawCursor(CDC * pDC);
	void EraseOldCursor(CDC * pDC);
	void RemoveMarker();
	void OnUpdate(CView * pSender, LPARAM lHint, CObject * pHint);
	CPiece * GetOccupant(BYTE row, BYTE column);
	void Box(CDC * pDC, BYTE row, BYTE col);
	void DrawSquare(CDC* pDC, int j, int i, BOOL bDrawPiece);
	void UpdateMessageBar();

// Operations
public:

// Implementation
public:
	virtual ~CChessView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
public:
	//{{AFX_MSG(CChessView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSpacebar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in chessvw.cpp
inline CChessDoc* CChessView::GetDocument()
   { return (CChessDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
