using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ChessDotNetBackend
{
    public class HumanPlayer : IPlayer
    {
        IUserInterface m_userInterface;

        public HumanPlayer(bool white, IUserInterface userInterface)
        {
            White = white;
            m_userInterface = userInterface;
        }

        public bool White { get; }

        public void Play()
        {
            Thread.Sleep(1000);
        }
    }
}
