using System;
using System.Collections.Generic;
using System.Windows;

namespace AkkaTalk.Helpers
{
    public static class DispatcherExtensions
    {
        public static void AddOnUI<T>(this ICollection<T> collection, T item)
        {
            Action<T> addMethod = collection.Add;
            Application.Current.Dispatcher.BeginInvoke(addMethod, item);
        }
        public static void SetOnUI(this DependencyObject obj, Action action)
        {
            Application.Current.Dispatcher.BeginInvoke(action);
        }
    }
}