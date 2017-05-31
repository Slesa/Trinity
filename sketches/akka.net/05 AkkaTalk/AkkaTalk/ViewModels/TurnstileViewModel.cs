using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using Akka.Actor;
using AkkaTalk.Actors;
using AkkaTalk.Helpers;
using Microsoft.Practices.Prism.Commands;
using Prism.Events;
using Prism.Mvvm;

namespace AkkaTalk.ViewModels
{
    public class TurnstileViewModel : BindableBase, IViewModel
    {
        private readonly ActorSystem _actorSystem;
        static readonly string IconGreen = "/AkkaTalk;component/Resources/GreenLight.png";
        static readonly string IconRed = "/AkkaTalk;component/Resources/RedLight.png";

        public TurnstileViewModel(ActorSystem actorSystem, IEventAggregator eventAggregator)
        {
            _actorSystem = actorSystem;
            eventAggregator.GetEvent<TurnstileLockedEvent>().Subscribe(OnLockedEvent);
            eventAggregator.GetEvent<TurnstileUnlockedEvent>().Subscribe(OnUnlockedEvent);
            eventAggregator.GetEvent<TurnstileBlockedEvent>().Subscribe(OnBlockedEvent);

            GetTicketCommand = new DelegateCommand(OnGetTicket); //, () => IsLocked); //.ObservesProperty(() => IsLocked);
            WalkThroughCommand = new DelegateCommand(OnWalkThrough); //, () => !IsLocked); //.ObservesProperty(() => IsLocked);

            IconFilename = IconRed; // Not sure in which order the bootstrapping runs
            ResetBackground();
        }

        private void ResetBackground()
        {
            Application.Current.Dispatcher.BeginInvoke(new Action(() => Background = new SolidColorBrush(Colors.Transparent)));
        }

        #region Commands

        public ICommand GetTicketCommand { get; set; }

        private void OnGetTicket()
        {
            ResetBackground();
            var turnstile = _actorSystem.ActorSelection("/user/turnstile");
            turnstile.Tell(new TicketValidated());
        }

        public ICommand WalkThroughCommand { get; set; }

        private void OnWalkThrough()
        {
            ResetBackground();
            var turnstile = _actorSystem.ActorSelection("/user/turnstile");
            turnstile.Tell(new BarrierPushed());
        }

        #endregion Commands

        private void OnUnlockedEvent()
        {
            IsLocked = false;
            IconFilename = IconGreen;
        }

        private void OnLockedEvent()
        {
            IsLocked = true;
            IconFilename = IconRed;
        }

        private void OnBlockedEvent()
        {
            Application.Current.Dispatcher.BeginInvoke(new Action(() => Background = new SolidColorBrush(Colors.Red)));
        }


        private Brush _background;
        public Brush Background
        {
            get { return _background; }
            set { SetProperty(ref _background, value); }
        }

        private bool _isLocked;
        public bool IsLocked
        {
            get { return _isLocked; }
            set { SetProperty(ref _isLocked, value); }
        }

        private string _iconFilename;
        public string IconFilename
        {
            get { return _iconFilename; }
            set { SetProperty(ref _iconFilename, value); }
        }
    }
}