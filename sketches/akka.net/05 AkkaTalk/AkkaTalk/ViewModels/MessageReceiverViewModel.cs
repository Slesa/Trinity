using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
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

    public static class DispatcherExtensions
    {
        public static void AddOnUI<T>(this ICollection<T> collection, T item)
        {
            Action<T> addMethod = collection.Add;
            Application.Current.Dispatcher.BeginInvoke(addMethod, item);
        }
    }
}