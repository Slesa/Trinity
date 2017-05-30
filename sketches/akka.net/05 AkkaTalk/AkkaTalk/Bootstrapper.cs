using System;
using System.IO;
using System.Windows;
using Akka.Actor;
using Akka.Configuration;
using AkkaTalk.ViewModels;
using AkkaTalk.Views;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;
using Prism.Unity;

namespace AkkaTalk
{
    public class Bootstrapper : UnityBootstrapper
    {
        protected override DependencyObject CreateShell()
        {
            return ServiceLocator.Current.GetInstance<MainWindow>();
        }

        protected override void InitializeShell()
        {
            base.InitializeShell();
            Application.Current.MainWindow = (Window) Shell;
            Application.Current.MainWindow.Show();
        }

        protected override void ConfigureContainer()
        {
            base.ConfigureContainer();

            ActorSystem = CreateActorSystem();
            //var messageActorProps = Props.Create<MessageActor>();
            //var messageActor = ActorSystem.ActorOf(messageActorProps, "messenger");
            var messageActor = ActorSystem.ActorOf<MessageActor>("messenger");

            Container.RegisterType<ActorSystem>(new InjectionFactory(_ => ActorSystem));
            Container.RegisterType<MainViewModel>();
            Container.RegisterType<MessageReceiverViewModel>();
            Container.RegisterType<MessageSenderViewModel>();
        }

        private ActorSystem ActorSystem { get; set; }

        private ActorSystem CreateActorSystem()
        {
            var config =
                ConfigurationFactory.ParseString(
                    File.ReadAllText(Path.Combine(Environment.CurrentDirectory, "akka.config")));
            return ActorSystem.Create("MessageSystem", config);
        }
    }
}