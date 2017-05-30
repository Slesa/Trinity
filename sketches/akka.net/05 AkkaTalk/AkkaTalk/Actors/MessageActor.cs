using Akka.Actor;
using Akka.Event;
using AkkaTalk.Models;
using Microsoft.Practices.ServiceLocation;
using Prism.Events;

namespace AkkaTalk.Actors
{
    public class MessageActor : ReceiveActor
    {
        private readonly ILoggingAdapter log = Context.GetLogger();

        public MessageActor()
        {
            Receive<Message>(/*async*/ msg =>
            {
                log.Info("Received message: " + msg.Text);
                //await Task.Delay(50);
                var eventAggregator = ServiceLocator.Current.GetInstance<IEventAggregator>();
                eventAggregator.GetEvent<MessageEvent>().Publish(string.Format("Message from {0}: {1}", Context.Sender.ToString(), msg.Text));
            });
        }
    }
}