﻿using Akka.Actor;
using Prism.Events;

namespace AkkaTalk.Actors
{
    class TicketValidated { }
    class BarrierPushed { }

    public class TurnstileActor : ReceiveActor
    {
        private readonly IEventAggregator _eventAggregator;

        public TurnstileActor(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;
            Become(Locked);
        }

        void Locked()
        {
            System.Diagnostics.Debug.WriteLine("Barrier is locked");
            _eventAggregator.GetEvent<TurnstileLockedEvent>().Publish();
            Receive<TicketValidated>(msg => Become(Unlocked));
            Receive<BarrierPushed>(msg => Blocked());
        }

        void Unlocked()
        {
            System.Diagnostics.Debug.WriteLine("Barrier is unlocked");
            _eventAggregator.GetEvent<TurnstileUnlockedEvent>().Publish();

            Receive<BarrierPushed>(msg => Become(Locked));
            Receive<TicketValidated>(msg => { });
        }

        void Blocked()
        {
            System.Diagnostics.Debug.WriteLine("You cannot walkthrough while barrier is locked");
            _eventAggregator.GetEvent<TurnstileBlockedEvent>().Publish();
        }
    }

    class TurnstileLockedEvent : PubSubEvent { }
    class TurnstileUnlockedEvent : PubSubEvent { }
    class TurnstileBlockedEvent : PubSubEvent { }
}