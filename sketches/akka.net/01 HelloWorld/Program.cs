using System;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using Akka.Actor;

namespace HelloWorld
{
	class Greet
	{
		public string Who { get; private set; }

		public Greet(string who)
		{
			Who = who;
		}
	}

	public class GreetingActor : ReceiveActor
	{
		public GreetingActor()
		{
			Receive<Greet>(async greet =>
			{
                await Task.Delay(50);
			    Console.WriteLine("Hello, {0}!", greet.Who);
			});
		}
	}

    class Wave {}

    class VocalGreeting
    {
        public string Greeting { get; private set; }

        public VocalGreeting(string greeting)
        {
            Greeting = greeting;
        }
    }

    class PersonActor : ReceiveActor
    {
        private int _peopleMet = 0;

        public PersonActor()
        {
            Receive<VocalGreeting>(x =>
            {
                _peopleMet += 1;
                Console.WriteLine("I've met {0} people today", _peopleMet);
                Context.Sender.Tell(new VocalGreeting("Hello!!!"));
            });
        }
    }

	class Program
	{
		static void Main(string[] args)
		{
			var system = ActorSystem.Create("HelloSystem");

			var greeter = system.ActorOf<GreetingActor>("greeter");
			greeter.Tell(new Greet("World"));

			var meeter = system.ActorOf<PersonActor>("meeter");
			meeter.Tell(new VocalGreeting("World"));

			Console.ReadLine();
		}
	}
}
