class CPiece : public CObject
{
protected:
	DECLARE_SERIAL(CPiece)
public:
	void InitialiseMe(BYTE row, BYTE column, BYTE color, 
			CBitmap *, CBitmap *,CObList *,CBoard *);
	CPiece(){m_bCapturing=FALSE;};
	virtual ~CPiece();
	virtual CPiece * Clone(CBoard * pBoard);  // clone piece on pBoard
	void CopyPiece(CPiece * pPiece, CBoard * pOwnerBoard);
	virtual void Serialize(CArchive& ar);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves(){};
	BOOL AddMove(BYTE row, BYTE column);
	BOOL IsNothingInTheWay(BYTE row, BYTE column);
	void DrawMe(CDC * pDC);
	virtual BOOL MoveTo(BYTE row, BYTE column);
	CBitmap * m_pPic;	// pointer to picture of piece
	CBitmap * m_pMask;	// pointer to picture of piece's mask
	BYTE m_row, m_column;
	BYTE m_color;
	BYTE m_type;
	CObList * m_pOwnerList;
	CBoard * m_pOwnerBoard;
	long m_value;
	BOOL m_bCapturing;
};

class CPawn : public CPiece
{
protected:
	DECLARE_SERIAL(CPawn)
	CPawn(){
		m_value=10;
		m_type=3;
		m_pPromoted=NULL;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves();
	virtual BOOL MoveTo(BYTE row, BYTE column);
	CPiece * m_pPromoted;	// pointer to the new queen when pawn is promoted
};

class CRook : public CPiece
{
protected:
	DECLARE_SERIAL(CRook)
	CRook(){
		m_value=50;
		m_type=6;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves();
	virtual BOOL MoveTo(BYTE row, BYTE column);
	virtual void Serialize(CArchive& ar);
	WORD m_bMoved;
};

class CBishop : public CPiece
{
protected:
	DECLARE_SERIAL(CBishop)
	CBishop(){
		m_value=30;
		m_type=5;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);                                          
	virtual void GetAllMoves();
};

class CKnight : public CPiece
{
protected:
	DECLARE_SERIAL(CKnight)
	CKnight(){
		m_value=30;
		m_type=2;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves();
};

class CQueen : public CPiece
{
protected:
	DECLARE_SERIAL(CQueen)
	CQueen(){
		m_value=90;
		m_type=4;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves();
};

class CKing : public CPiece
{
protected:
	DECLARE_SERIAL(CKing)
	CKing(){
		m_value=1000;
		m_type=1;
	};
public:
	virtual CPiece * Clone(CBoard *);
	virtual BOOL IsMoveValid(BYTE row, BYTE column);
	virtual void GetAllMoves();
	virtual BOOL MoveTo(BYTE row, BYTE column);
	virtual void Serialize(CArchive& ar);
	WORD m_bMoved;
};