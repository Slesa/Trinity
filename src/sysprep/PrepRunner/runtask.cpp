#include "runtask.h"

RunTask::RunTask(Settings& settings, Logger& logger, QObject* parent) : QObject(parent)
  , _settings(settings)
  , _logger(logger)
{
}
