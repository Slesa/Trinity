using System.ComponentModel;
using System.Runtime.CompilerServices;
using Akka.Actor;
using AkkaTalk.Actors;
using AkkaTalk.Helpers;
using AkkaTalk.Models;
using Microsoft.Practices.Prism.Commands;

namespace AkkaTalk.ViewModels
{
    public class MessageSenderViewModel : INotifyPropertyChanged, IViewModel
    {
        private readonly ActorSystem _actorSystem;
        private string _message;

        public MessageSenderViewModel(ActorSystem actorSystem)
        {
            _actorSystem = actorSystem;
            SendCommand = new DelegateCommand(Send, CanSend);
        }

        public DelegateCommand SendCommand { get; set; }

        public string Message
        {
            get { return _message; }
            set
            {
                _message = value;
                SendCommand.RaiseCanExecuteChanged();
            }
        }

        private void Send()
        {
            var greeter = _actorSystem.ActorSelection("/user/message");
            greeter.Tell(new Message(Message));
        }

        private bool CanSend()
        {
            return !string.IsNullOrEmpty(Message);
        }

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion

    }
}