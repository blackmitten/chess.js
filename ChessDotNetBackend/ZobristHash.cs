using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public struct ZobristHash
    {
        long Hash;

        public ZobristHash(Board board)
        {
            Hash = 0;
            foreach (var piece in board.Pieces)
            {
                Square s = piece.CurrentPosition;
                Hash ^= ZobristTable.Instance.Table[s.x, s.y, (int)piece.PieceType];
            }
        }
    }
}
