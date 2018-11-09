using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
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
        Square Square { get; }
        bool White { get; }
        string Name { get; }

        void Accept(IPieceVisitor visitor, object data);
        IEnumerable<Square> GetAllMoves(Board m_board);
        bool IsMoveValid(Board board, Square square);
    }

    static class Piece
    {
        public static bool addMove(IPiece piece, Board board, List<Square> moves, Square square)
        {
            if (square == piece.Square)
            {
                return true;
            }
            if (piece.IsMoveValid(board, square))
            {
                moves.Add(square);
                return true;
            }
            return false;
        }

        public static bool IsMoveValid(IPiece piece, Board board, Square square)
        {
            if (!square.InBounds)
            {
                return false;
            }
            IPiece capturedPiece = board.GetPieceOnSquare(square);
            bool correctCapture = capturedPiece == null || capturedPiece.White != piece.White;
            return correctCapture;
        }

    }

    public class Pawn : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Pawn(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Pawn" : "Black Pawn";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board board)
        {
            var moves = new List<Square>();
            var dir = White ? -1 : 1;
            Piece.addMove(this, board, moves, Square.Offset(0, dir * 1));
            Piece.addMove(this, board, moves, Square.Offset(0, dir * 2));
            Piece.addMove(this, board, moves, Square.Offset(1, dir * 1));
            Piece.addMove(this, board, moves, Square.Offset(-1, dir * 1));
            return moves;
        }

        public bool IsMoveValid(Board board, Square square)
        {
            if (!Piece.IsMoveValid(this, board, square))
            {
                return false;
            }
            int nDir = White ? -1 : 1;  // which way can this pawn move?
            if ((square.y - Square.y) * nDir > 2)   // can never go further than two spaces
                return false;
            if ((square.y - Square.y) * nDir <= 0)  // mustn't go backwards
                return false;
            if (((square.y - Square.y) * nDir > 1) && (Square.y != (White ? 6 : 1)))  // can go two spaces if we haven't moved
                return false;
            if ((square.x == Square.x) && board.GetPieceOnSquare(square) != null)  // can't take forwards
                return false;
            if (square.x != Square.x)
            {
                if (board.GetPieceOnSquare(square) == null)
                {
                    return false;
                }
                if (Math.Abs(square.x - Square.x) > 1)  // can take diagonally
                {
                    return false;
                }
            }
            return board.IsNothingInTheWay(this, square);

        }

        public override string ToString() => Name + " " + Square.ToString();
    }

    public class Rook : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Rook(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Rook" : "Black Rook";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board m_board)
        {
            throw new NotImplementedException();
        }

        public bool IsMoveValid(Board board, Square square)
        {
            return true;
        }

        public override string ToString() => Name + " " + Square.ToString();
    }

    public class Knight : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Knight(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Knight" : "Black Knight";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board m_board)
        {
            throw new NotImplementedException();
        }

        public bool IsMoveValid(Board board, Square square)
        {
            return true;
        }

        public override string ToString() => Name + " " + Square.ToString();
    }

    public class Bishop : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Bishop(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Bishop" : "Black Bishop";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board m_board)
        {
            throw new NotImplementedException();
        }

        public bool IsMoveValid(Board board, Square square)
        {
            return true;
        }

        public override string ToString() => Name + " " + Square.ToString();
    }

    public class Queen : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public Queen(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White Queen" : "Black Queen";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board m_board)
        {
            throw new NotImplementedException();
        }

        public bool IsMoveValid(Board board, Square square)
        {
            return true;
        }

        public override string ToString() => Name + " " + Square.ToString();
    }

    public class King : IPiece
    {
        public Square Square { get; set; }
        public bool White { get; }
        public string Name { get; }

        public King(Square square, bool white)
        {
            Square = square;
            White = white;
            Name = White ? "White King" : "Black King";
        }

        public void Accept(IPieceVisitor visitor, object data)
        {
            visitor.Visit(this, data);
        }

        public IEnumerable<Square> GetAllMoves(Board m_board)
        {
            throw new NotImplementedException();
        }

        public bool IsMoveValid(Board board, Square square)
        {
            return true;
        }

        public override string ToString() => Name + " " + Square.ToString();
    }

}
