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
    public class CashDrawerViewModel : BindableBase, IViewModel
    {
        private readonly ActorSystem _actorSystem;
        static readonly string IconOpen = "/AkkaTalk;component/Resources/DrawerOpen.png";
        static readonly string IconClosed = "/AkkaTalk;component/Resources/DrawerClosed.png";

        public CashDrawerViewModel(ActorSystem actorSystem, IEventAggregator eventAggregator)
        {
            _actorSystem = actorSystem;
            eventAggregator.GetEvent<DrawerOpenedEvent>().Subscribe(OnOpenedEvent);
            eventAggregator.GetEvent<DrawerClosedEvent>().Subscribe(OnClosedEvent);
            eventAggregator.GetEvent<DrawerAlreadyOpenEvent>().Subscribe(OnAlreadyThereEvent);
            eventAggregator.GetEvent<DrawerAlreadyClosedEvent>().Subscribe(OnAlreadyThereEvent);

            OpenDrawerCommand = new DelegateCommand(OnOpenDrawer); //, () => !IsOpen); //.ObservesProperty(() => IsOpen);
            CloseDrawerCommand = new DelegateCommand(OnCloseDrawer); //, () => IsOpen); //.ObservesProperty(() => IOpen);

            IconFilename = IconClosed; // Not sure in which order the bootstrapping runs
            ResetBackground();
        }

        private void ResetBackground()
        {
            Application.Current.Dispatcher.BeginInvoke(new Action(() => Background = new SolidColorBrush(Colors.Transparent)));
        }


        #region Commands

        public ICommand OpenDrawerCommand { get; set; }

        private void OnOpenDrawer()
        {
            var drawer = _actorSystem.ActorSelection("/user/cashdrawer");
            drawer.Tell(new OpenDrawerCommand());
        }

        public ICommand CloseDrawerCommand { get; set; }

        private void OnCloseDrawer()
        {
            var drawer = _actorSystem.ActorSelection("/user/cashdrawer");
            drawer.Tell(new CloseDrawerCommand());
        }

        #endregion Commands

        private void OnOpenedEvent()
        {
            ResetBackground();
            IsOpen = true;
            IconFilename = IconOpen;
        }

        private void OnClosedEvent()
        {
            ResetBackground();
            IsOpen = false;
            IconFilename = IconClosed;
        }

        private void OnAlreadyThereEvent()
        {
            Application.Current.Dispatcher.BeginInvoke(new Action(() => Background = new SolidColorBrush(Colors.Red)));
        }

        private Brush _background;
        public Brush Background
        {
            get { return _background; }
            set { SetProperty(ref _background, value); }
        }

        private bool _isOpen;
        public bool IsOpen
        {
            get { return _isOpen; }
            set { SetProperty(ref _isOpen, value); }
        }

        private string _iconFilename;
        public string IconFilename
        {
            get { return _iconFilename; }
            set { SetProperty(ref _iconFilename, value); }
        }
    }
}