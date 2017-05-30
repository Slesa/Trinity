using System;
using Akka.Actor;
using Akka.Event;
using NLog;
using NLogger = global::NLog.Logger;

namespace AkkaTalk.Actors
{
    public class NLogLogger : ReceiveActor
    {
        private ILoggingAdapter log = Context.GetLogger();

        private static void Log(LogEvent logEvent, Action<NLogger> logStatement)
        {
            var logger = LogManager.GetLogger(logEvent.LogClass.FullName);
            logStatement(logger);
        }

        public NLogLogger()
        {
            Receive<Error>(m => Log(m, logger => logger.ErrorException(m.Message.ToString(), m.Cause)));
            Receive<Warning>(m => Log(m, logger => logger.Warn(m.Message.ToString)));
            Receive<Info>(m => Log(m, logger => logger.Info(m.Message.ToString)));
            Receive<Debug>(m => Log(m, logger => logger.Debug(m.Message.ToString)));

            Receive<InitializeLogger>(m =>
            {
                log.Info("NLogLogger started");
                Sender.Tell(new LoggerInitialized());
            });
        }
    }
}