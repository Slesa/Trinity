﻿using Akka.Actor;
using Akka.Event;
using AkkaTalk.Models;
using Prism.Events;

namespace AkkaTalk.Actors
{
    public class MessageActor : ReceiveActor
    {
        private readonly ILoggingAdapter log = Context.GetLogger();

        public MessageActor(IEventAggregator eventAggregator)
        {
            Receive<Message>(msg =>
            {
                log.Info("Received message: " + msg.Text);
                //var eventAggregator = ServiceLocator.Current.GetInstance<IEventAggregator>();
                eventAggregator.GetEvent<MessageEvent>().Publish(string.Format("Message from {0}: {1}", Context.Sender.ToString(), msg.Text));
            });
        }
    }
}