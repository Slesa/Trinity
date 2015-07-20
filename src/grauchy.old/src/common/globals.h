#ifndef GLOBALS_H
#define GLOBALS_H

#include <QSettings>

#define GRAUCHY_VERSION	001
#define GRAUCHY_VERSION_STRING "0.0.1"

class PlatformBase;
class GrauchyWidget;

extern PlatformBase* g_platform;
extern GrauchyWidget* g_mainWidget;
extern QSettings* g_settings;

#endif // GLOBALS_H

