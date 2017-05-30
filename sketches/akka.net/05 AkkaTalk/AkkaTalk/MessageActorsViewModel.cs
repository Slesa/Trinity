using System;
using System.Collections.Generic;
using Akka.Actor;
using AkkaTalk.Models;

namespace AkkaTalk
{
    public class MessageActor : ReceiveActor
    {
        List<Action<string>> _handlers = new List<Action<string>>();

        public MessageActor()
        {
            Receive<Message>(msg =>
            {
                foreach (var handler in _handlers)
                    handler(msg.Text);
            });
        }

        public void AddHandler(Action<string> handler)
        {
            _handlers.Add(handler);
        }
    }

}