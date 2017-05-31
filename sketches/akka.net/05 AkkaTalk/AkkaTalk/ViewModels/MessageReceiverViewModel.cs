using System.Collections.ObjectModel;
using AkkaTalk.Helpers;
using Prism.Events;

namespace AkkaTalk.ViewModels
{
    public class MessageReceiverViewModel : IViewModel
    {
        public MessageReceiverViewModel(IEventAggregator eventAggregator)
        {
            Messages = new ObservableCollection<string>();
            eventAggregator.GetEvent<MessageEvent>().Subscribe(x => Messages.AddOnUI(x));
        }

        public ObservableCollection<string> Messages { get; set; }
    }
}