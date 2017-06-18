using System;
using Akka.Actor;
using Prism.Events;

namespace AkkaTalk.Actors
{
    class OpenDrawerCommand { }
    class CloseDrawerCommand { }


    interface ICashDrawerState { }

    class DrawerOpen : ICashDrawerState
    {
        public static readonly DrawerOpen Instance = new DrawerOpen();
    }

    class DrawerClosed : ICashDrawerState
    {
        public static readonly DrawerClosed Instance = new DrawerClosed();
    }

    interface ICashDrawerData { }
    class CashDrawerData : ICashDrawerData { }

    class CashDrawerStateMachine : FSM<ICashDrawerState, ICashDrawerData>
    {
        private readonly IEventAggregator _eventAggregator;

        public CashDrawerStateMachine(IEventAggregator eventAggregator)
        {
            _eventAggregator = eventAggregator;

            When(DrawerClosed.Instance, @event =>
            {
                if (@event.FsmEvent is OpenDrawerCommand)
                {
                    System.Diagnostics.Debug.WriteLine("I shall open the drawer");
                    return GoTo(DrawerOpen.Instance);
                }
                if (@event.FsmEvent is CloseDrawerCommand)
                {
                    System.Diagnostics.Debug.WriteLine("R u sure to close a closed drawer?");
                    return GoTo(DrawerClosed.Instance);
                }
                return Stay();
            });

            When(DrawerOpen.Instance, @event =>
            {
                if (@event.FsmEvent is CloseDrawerCommand || @event.FsmEvent is StateTimeout)
                {
                    System.Diagnostics.Debug.WriteLine("I shall close the drawer");
                    return GoTo(DrawerClosed.Instance);
                }
                if (@event.FsmEvent is OpenDrawerCommand)
                {
                    System.Diagnostics.Debug.WriteLine("R u sure to open an opened drawer?");
                    return GoTo(DrawerOpen.Instance);
                }
                return Stay();
            }, TimeSpan.FromSeconds(3.0));

            StartWith(DrawerClosed.Instance, new CashDrawerData());
            OnTransition(OnTransition);

            Initialize();
        }

        void OnTransition(ICashDrawerState fromState, ICashDrawerState newState)
        {
            if (fromState is DrawerOpen && newState is DrawerClosed)
            {
                _eventAggregator.GetEvent<DrawerClosedEvent>().Publish();
                return;
            }
            if (fromState is DrawerClosed && newState is DrawerOpen)
            {
                _eventAggregator.GetEvent<DrawerOpenedEvent>().Publish();
                return;
            }
            if (fromState is DrawerOpen && newState is DrawerOpen)
            {
                _eventAggregator.GetEvent<DrawerAlreadyOpenEvent>().Publish();
                return;
            }
            if (fromState is DrawerClosed && newState is DrawerClosed)
            {
                _eventAggregator.GetEvent<DrawerAlreadyClosedEvent>().Publish();
            }
        }
    }

    class DrawerOpenedEvent : PubSubEvent { }
    class DrawerClosedEvent : PubSubEvent { }
    class DrawerAlreadyOpenEvent : PubSubEvent { }
    class DrawerAlreadyClosedEvent : PubSubEvent { }
}