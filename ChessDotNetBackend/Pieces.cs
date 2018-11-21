using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public enum PieceType
    {
        WhitePawn,
        WhiteRook,
        WhiteKnight,
        WhiteBishop,
        WhiteQueen,
        WhiteKing,
        BlackPawn,
        BlackRook,
        BlackKnight,
        BlackBishop,
        BlackQueen,
        BlackKing
    }

    public interface IPieceVisitor
    {
        void Visit(Pawn pawn, object data);
        void Visit(Rook rook, object data);
        void Visit(Knight knight, object data);
        void Visit(Bishop bishop, object data);
        void Visit(Queen queen, object data);
        void Visit(King king, object data);
    }

    public interface IPiece
    {
        Square CurrentPosition { get; set; }
        bool White { get; }
        string Name { get; }

        void Accept(IPieceVisitor visitor, object data);
        IPiece Copy();
        IEnumerable<Square> GetAllMoves(Board m_board);
        bool IsMoveValid(Board board, Square destination);
        double Value { get; }
        PieceType PieceType { get; }
        bool IsPawn { get; }
    }

    static class Piece
    {
        public static bool addMove(IPiece piece, Board board, List<Square> moves, Square destination)
        {
            if (destination == piece.CurrentPosition)
            {
                return true;
            }
            if (piece.IsMoveValid(board, destination))
            {
                moves.Add(destination);
                return true;
            }
            return false;
        }

        public static bool IsMoveValid(IPiece piece, Board board, Square destination)
        {
            if (!destination.InBounds)
            {
                return false;
            }
            IPiece capturedPiece = board.GetPieceOnSquare(destination);
            bool correctCapture = capturedPiece == null || capturedPiece.White != piece.White;
            return correctCapture;
        }
    }

    public class Pawn : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Pawn(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White Pawn" : "Black Pawn";
            PieceType = white ? PieceType.WhitePawn : PieceType.BlackPawn;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            var dir = White ? -1 : 1;
            Piece.addMove(this, board, moves, CurrentPosition.Offset(0, dir * 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(0, dir * 2));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, dir * 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, dir * 1));
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            int nDir = White ? -1 : 1;  // which way can this pawn move?
            if ((destination.y - CurrentPosition.y) * nDir > 2)   // can never go further than two spaces
                return false;
            if ((destination.y - CurrentPosition.y) * nDir <= 0)  // mustn't go backwards
                return false;
            if (((destination.y - CurrentPosition.y) * nDir > 1) && (CurrentPosition.y != (White ? 6 : 1)))  // can go two spaces if we haven't moved
                return false;
            if ((destination.x == CurrentPosition.x) && board.GetPieceOnSquare(destination) != null)  // can't take forwards
                return false;
            if (destination.x != CurrentPosition.x)
            {
                if (board.GetPieceOnSquare(destination) == null)
                {
                    return false;
                }
                if (Math.Abs(destination.x - CurrentPosition.x) > 1)  // can take diagonally
                {
                    return false;
                }
            }
            return board.IsNothingInTheWay(this, destination);

        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new Pawn(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Pawn p = (Pawn)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 1;

        public PieceType PieceType { get; }

        public bool IsPawn => true;
    }

    public class Rook : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Rook(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White Rook" : "Black Rook";
            PieceType = white ? PieceType.WhiteRook : PieceType.BlackRook;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            int x = CurrentPosition.x;
            int y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y)))
            { }
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y)))
            { }
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x, y++)))
            { }
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x, y--)))
            { }
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            if (CurrentPosition.x != destination.x && CurrentPosition.y != destination.y)
            {
                return false;
            }
            return board.IsNothingInTheWay(this, destination);
        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new Rook(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Rook p = (Rook)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 5;

        public PieceType PieceType { get; }

        public bool IsPawn => false;
    }

    public class Knight : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Knight(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White Knight" : "Black Knight";
            PieceType = white ? PieceType.WhiteKnight : PieceType.BlackKnight;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            Piece.addMove(this, board, moves, CurrentPosition.Offset(2, 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(2, -1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-2, 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-2, -1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, 2));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, 2));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, -2));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, -2));
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            var dx = destination.x - CurrentPosition.x;
            var dy = destination.y - CurrentPosition.y;
            //  two spaces forward, one to either side...
            return (Math.Abs(dy) == 2 && Math.Abs(dx) == 1) || (Math.Abs(dy) == 1 && Math.Abs(dx) == 2);
        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new Knight(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Knight p = (Knight)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 3;

        public PieceType PieceType { get; }

        public bool IsPawn => false;
    }

    public class Bishop : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Bishop(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White Bishop" : "Black Bishop";
            PieceType = white ? PieceType.WhiteBishop: PieceType.BlackBishop;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            int x = CurrentPosition.x;
            int y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y++)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y++)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y--)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y--))) ;
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            if (Math.Abs(destination.x - CurrentPosition.x) != Math.Abs(destination.y - CurrentPosition.y))
            {
                return false;
            }
            return board.IsNothingInTheWay(this, destination);
        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new Bishop(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Bishop p = (Bishop)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 3;

        public PieceType PieceType { get; }

        public bool IsPawn => false;
    }

    public class Queen : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Queen(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White Queen" : "Black Queen";
            PieceType = white ? PieceType.WhiteQueen : PieceType.BlackQueen;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            int x = CurrentPosition.x;
            int y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y++)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y++)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y--)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y--)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x++, y)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x--, y)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x, y++)))
                ;
            x = CurrentPosition.x;
            y = CurrentPosition.y;
            while (Piece.addMove(this, board, moves, new Square(x, y--)))
                ;
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            if (CurrentPosition.x != destination.x && CurrentPosition.y != destination.y)
            {
                if (Math.Abs(destination.x - CurrentPosition.x) != Math.Abs(destination.y - CurrentPosition.y))
                {
                    return false;
                }
            }
            return board.IsNothingInTheWay(this, destination);
        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new Queen(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Queen p = (Queen)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 9;

        public PieceType PieceType { get; }

        public bool IsPawn => false;
    }

    public class King : IPiece
    {
        public Square CurrentPosition { get; set; }
        public bool White { get; }
        public string Name { get; }

        public King(Square currentPosition, bool white)
        {
            CurrentPosition = currentPosition;
            White = white;
            Name = White ? "White King" : "Black King";
            PieceType = white ? PieceType.WhiteKing : PieceType.BlackKing;
        }

        public void Accept(IPieceVisitor visitor, object data) => visitor.Visit(this, data);

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            Piece.addMove(this, board, moves, CurrentPosition.Offset(0, 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(0, -1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, 0));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(1, -1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, 1));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, 0));
            Piece.addMove(this, board, moves, CurrentPosition.Offset(-1, -1));
            return moves;
        }

        public bool IsMoveValid(Board board, Square destination)
        {
            if (!Piece.IsMoveValid(this, board, destination))
            {
                return false;
            }
            if (Math.Abs(destination.x - CurrentPosition.x) > 1)
            {
                return false;
            }
            if (Math.Abs(destination.y - CurrentPosition.y) > 1)
            {
                return false;
            }
            return true;
        }

        public override string ToString() => Name + " " + CurrentPosition.ToString();

        public IPiece Copy() => new King(CurrentPosition, White);

        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            King p = (King)obj;
            return p.White == White && p.CurrentPosition == CurrentPosition;
        }

        public double Value => 1000;

        public PieceType PieceType { get; }

        public bool IsPawn => false;
    }

}
