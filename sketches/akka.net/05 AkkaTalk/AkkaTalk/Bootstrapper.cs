using System;
using System.IO;
using System.Windows;
using Akka.Actor;
using Akka.Configuration;
using AkkaTalk.Actors;
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

            Container.RegisterType<ActorSystem>(new InjectionFactory(_ => ActorSystem));
            Container.RegisterType<MainViewModel>();
            Container.RegisterType<MessageReceiverViewModel>();
            Container.RegisterType<MessageSenderViewModel>();


            ActorSystem = CreateActorSystem();
            var personActorProps = Props.Create<PersonActor>();
            /*var personActor =*/
            ActorSystem.ActorOf(personActorProps, "person");

            var messageActorProps = Props.Create<MessageActor>();
            /*var messageActor =*/
            ActorSystem.ActorOf(messageActorProps, "message");

            var turnstileActorProps = Props.Create<TurnstileActor>();
            /*var messageActor =*/
            ActorSystem.ActorOf(turnstileActorProps, "turnstile");

            var drawerActorProps = Props.Create<CashDrawerStateMachine>();
            /*var messageActor =*/
            ActorSystem.ActorOf(drawerActorProps, "cashdrawer");
        }

        private ActorSystem _actorSystem;

        private ActorSystem ActorSystem
        {
            get { return _actorSystem ?? (_actorSystem = CreateActorSystem()); }
            set { _actorSystem = value; }
        }

        private ActorSystem CreateActorSystem()
        {
            var config =
                ConfigurationFactory.ParseString(
                    File.ReadAllText(Path.Combine(Environment.CurrentDirectory, "akka.config")));
            return ActorSystem.Create("MessageSystem", config);
        }
    }
}