using System;
using System.Windows;
using AkkaTalk.ViewModels;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;

namespace AkkaTalk.Helpers
{
    public class ViewModelLocator<TViewModel>
        where TViewModel : IViewModel
    {
        readonly Lazy<IUnityContainer> _container;
        readonly bool _inDesignTime = System.ComponentModel.DesignerProperties.GetIsInDesignMode(new DependencyObject());

        public ViewModelLocator()
        {
            if (!_inDesignTime)
            {
                _container = new Lazy<IUnityContainer>( () => ServiceLocator.Current.GetInstance<IUnityContainer>());
            }
        }

        public IViewModel ViewModel
        {
            get
            {
                if (_inDesignTime) return null;
                return _container.Value.Resolve<TViewModel>();
            }
        }
    }

    public class MainViewModelLocator : ViewModelLocator<MainViewModel> {}
    public class MessageReceiverViewModelLocator : ViewModelLocator<MessageReceiverViewModel> {}
    public class MessageSenderViewModelLocator : ViewModelLocator<MessageSenderViewModel> {}
    public class TurnstileViewModelLocator : ViewModelLocator<TurnstileViewModel> {}
    public class CashDrawerViewModelLocator : ViewModelLocator<CashDrawerViewModel> {}
}