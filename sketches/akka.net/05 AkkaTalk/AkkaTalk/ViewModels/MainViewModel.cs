using Akka.Actor;
using AkkaTalk.Helpers;

namespace AkkaTalk
{
    public class MainViewModel : IViewModel
    {
        private readonly ActorSystem _actorSystem;

        public MainViewModel(ActorSystem actorSystem)
        {
            _actorSystem = actorSystem;
        }
    }
}