// chessdoc.h : interface of the CChessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#define BLACK 0
#define WHITE 1

#define KING 1
#define KNIGHT 2
#define PAWN 3
#define QUEEN 4
#define BISHOP 5
#define ROOK 6

class CPiece;
class CKing;

class CBoard : public CObject
{
friend class CChessDoc;
protected:
	~CBoard();
	CBoard( CBoard * pBoard);	// this constructor duplicates pBoard
public:
	CBoard(){
		m_bCheckMate[WHITE]=FALSE;
		m_bCheckMate[BLACK]=FALSE;
	};
	CObList m_BlackPieces;
	CObList m_WhitePieces;
	
	CWordArray m_MovesArray;	// array of possible moves on this board

	BYTE m_FromRow, m_FromCol, m_ToRow, m_ToCol;	// best move

	CPiece * m_pOccupants[8][8];
	BOOL m_bInCheck[2];
	BOOL m_bCheckMate[2];
	BYTE m_WhosGo;
	
	float m_lScore;

	CChessDoc * m_pOwnerDoc;

	float MakeMove(int nDepth);	// play computer's move
	float MakeMoveAB2(int nDepth, float a, float b);
	void QuietMove(CPiece * pMover, BYTE row, BYTE column);	// move a piece
	BOOL Move(CPiece * pMover, BYTE row, BYTE column);	// move a piece
	void DeletePieces();
	void NewBoard();
	void EvaluatePosition();
	void IsInCheck();
	float CalcScore(CObList * pPieces,BYTE color);	// calculate the score for color's side
	BOOL Threatens(BYTE row, BYTE column, BYTE color);
	BOOL CheckNotInCheck(CPiece * pMover, BYTE row, BYTE col);
//	BOOL IsItCheckMate(BYTE color, CPiece * pPiece, BYTE row, BYTE col);
	BOOL CanIMove();
	BOOL IsKingThreatend();
	void MakeThisBoard(CBoard * pBoard);	// the undo mechanism
};

class CChessDoc : public CDocument
{
protected: // create from serialization only
	CChessDoc();
	DECLARE_DYNCREATE(CChessDoc)

	CBoard m_CurrentBoard;	// the current state of play and tree to future positions
	CObList m_UndoList;	
	
	BOOL m_bMoving;
	BOOL m_bQuiet;
	BOOL m_bStopThinking;
	BOOL m_bUndoListed;

	CString m_sCheckMe;	// string containing message for user in check
	CString m_sCheckYou;	// string containing message for computer in check
	CString m_sMateMe;	// string containing message for user in check
	CString m_sMateYou;	// string containing message for computer in check

	CPiece * m_pMover;	// pointer to currently selected piece
	
	BOOL m_bDirty;	// is this game saved?
	
	BYTE m_CurRow;
	BYTE m_CurCol;
	BYTE m_LastRow;
	BYTE m_LastCol;
	
	// all the pictures of the pieces, with their masks
	CBitmap m_wPawnPic;
	CBitmap m_bPawnPic;
	CBitmap m_PawnMask;
	CBitmap m_wRookPic;
	CBitmap m_bRookPic;
	CBitmap m_RookMask;
	CBitmap m_wBishopPic;
	CBitmap m_bBishopPic;
	CBitmap m_BishopMask;
	CBitmap m_wKingPic;
	CBitmap m_bKingPic;
	CBitmap m_KingMask;
	CBitmap m_wKnightPic;
	CBitmap m_bKnightPic;
	CBitmap m_KnightMask;
	CBitmap m_wQueenPic;
	CBitmap m_bQueenPic;
	CBitmap m_QueenMask;

// Operations
public:
	void ClearName();
	void AttachPiece(CPiece *);
	void Think();
	
// Implementation
public:
	virtual ~CChessDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
	BOOL WipeUnsavedGame();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL OnNewDocument();
	virtual BOOL OnOpenDocument( const char* pszPathName);
	virtual void DeleteContents();
// Generated message map functions
protected:
	//{{AFX_MSG(CChessDoc)
	afx_msg void OnDown();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnUp();
	afx_msg void OnViewRefresh();
	afx_msg void OnViewGamestatistics();
	afx_msg void OnLevelDepth1();
	afx_msg void OnLevelDepth2();
	afx_msg void OnLevelDepth3();
	afx_msg void OnLevelDepth4();
	afx_msg void OnLevelDepth5();
	afx_msg void OnLevelDepth6();
	afx_msg void OnUpdateLevelDepth1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevelDepth2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevelDepth3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevelDepth4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevelDepth5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevelDepth6(CCmdUI* pCmdUI);
	afx_msg void OnAlgorithmMinimax();
	afx_msg void OnAlgorithmMinimaxwithalphabeta();
	afx_msg void OnUpdateAlgorithmMinimax(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlgorithmMinimaxwithalphabeta(CCmdUI* pCmdUI);
	afx_msg void OnLevelForcemove();
	afx_msg void OnUpdateLevelForcemove(CCmdUI* pCmdUI);
	afx_msg void OnGameRestoresaved();
	afx_msg void OnUpdateGameRestoresaved(CCmdUI* pCmdUI);
	afx_msg void OnMoveUndo();
	afx_msg void OnUpdateMoveUndo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateStartPos(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEndPos(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheckStatus(CCmdUI* pCmdUI);
};

/////////////////////////////////////////////////////////////////////////////
