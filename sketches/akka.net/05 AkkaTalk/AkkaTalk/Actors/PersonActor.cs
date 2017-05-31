using Akka.Actor;
using Akka.Event;
using AkkaTalk.Models;

namespace AkkaTalk.Actors
{
    class Greeting
    {
        public string Msg { get; private set; }

        public Greeting(string msg)
        {
            Msg = msg;
        }
    }

    public class PersonActor : ReceiveActor
    {
        private readonly ILoggingAdapter log = Context.GetLogger();

        public PersonActor()
        {
            Receive<Greeting>(x =>
            {
                log.Info("Received greeting: " + x.Msg);
                System.Diagnostics.Debug.WriteLine(x.Msg);
            });
            Receive<Message>(x =>
            {
                log.Info("Received message: " + x.Text);
                System.Diagnostics.Debug.WriteLine(x.Text);
            });
        }
    }
}