using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ChessDotNetBackend
{
    public class Game
    {
        IUserInterface m_userInterface;
        Board m_currentBoard;
        bool m_whiteHuman;
        bool m_blackHuman;

        public Game(bool whiteHuman, bool blackHuman, IUserInterface userInterface)
        {
            m_whiteHuman = whiteHuman;
            m_blackHuman = blackHuman;
            m_userInterface = userInterface;
            m_currentBoard = Board.InitNewGame();

            userInterface.Board = m_currentBoard;
            userInterface.BoardUpdated += BoardUpdated;

            Play();
        }

        private void Play()
        {
            Thread thread = new Thread(() =>
            {
                if (m_currentBoard.WhitesTurn && !m_whiteHuman)
                {
                    m_userInterface.Thinking = true;
                    Board newBoard = m_currentBoard.ThinkAndMove();
                    m_userInterface.Update(newBoard);
                    m_userInterface.Thinking = false;
                }
                else if (!m_currentBoard.WhitesTurn && !m_blackHuman)
                {
                    m_userInterface.Thinking = true;
                    Board newBoard = m_currentBoard.ThinkAndMove();
                    m_userInterface.Update(newBoard);
                    m_userInterface.Thinking = false;
                }
            });
            thread.Start();
        }

        private void BoardUpdated(object sender, BoardUpdateEventArgs e)
        {
            m_currentBoard = e.Board;
            Play();
        }


    }
}
