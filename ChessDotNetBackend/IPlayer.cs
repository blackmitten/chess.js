using System;
using System.Collections.Generic;
using System.Text;

namespace ChessDotNetBackend
{
    /*
    public class MoveEventArgs : EventArgs
    {

    }
    */

    public interface IPlayer
    {
        bool White { get; }
        void Play();
//        void StartPlayerThinking();
//        event EventHandler<BoardUpdateEventArgs> Moved;
    }
}
