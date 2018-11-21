using ChessDotNetBackend;
using System;
using System.Collections.Generic;
using System.Text;

namespace ChessTests
{
    class MockUI : IUserInterface
    {
        public Board Board { get; set; }

        public bool MachineThinking { get; set; }

        public event EventHandler<BoardUpdateEventArgs> BoardUpdated;

        public void Update(Board newBoard)
        {
            Board = newBoard;
        }
    }
}
