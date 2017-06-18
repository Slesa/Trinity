using System;
using System.IO;
using System.Windows;
using Akka.Actor;
using Akka.Configuration;
using Akka.DI.Core;
using Akka.DI.Unity;
using AkkaTalk.Actors;
using AkkaTalk.ViewModels;
using AkkaTalk.Views;
using Microsoft.Practices.ServiceLocation;
using Microsoft.Practices.Unity;
using Prism.Events;
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

            var propsResolver = new UnityDependencyResolver(Container, ActorSystem);

            var eventAggregator = Container.Resolve<IEventAggregator>();
            var messageActorProps = ActorSystem.DI().Props<MessageActor>();
            //var messageActorProps = Props.Create<MessageActor>(() => new MessageActor(eventAggregator) );
            /*var messageActor =*/
            ActorSystem.ActorOf(messageActorProps, "message");

            var turnstileActorProps = ActorSystem.DI().Props<TurnstileActor>();
            //var turnstileActorProps = Props.Create<TurnstileActor>(() => new TurnstileActor(eventAggregator));
            /*var messageActor =*/
            ActorSystem.ActorOf(turnstileActorProps, "turnstile");

            var drawerActorProps = ActorSystem.DI().Props<CashDrawerStateMachine>();
            //var drawerActorProps = Props.Create<CashDrawerStateMachine>(() => new CashDrawerStateMachine(eventAggregator));
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