using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    public class BoardUpdateEventArgs : EventArgs
    {
        public Board Board { get; }

        public BoardUpdateEventArgs(Board board)
        {
            Board = board;
        }
    }

    public interface IUserInterface
    {
        Board Board { set; }
        bool MachineThinking {  set; }

        event EventHandler<BoardUpdateEventArgs> BoardUpdated;

        void Update(Board newBoard);
    }
}
