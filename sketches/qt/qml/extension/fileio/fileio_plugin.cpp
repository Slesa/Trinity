#include "fileio_plugin.h"
#include "fileio.h"

#include <qqml.h>

void FileioPlugin::registerTypes(const char *uri)
{
    // @uri de.slesa.qmlcomponents
    qmlRegisterType<FileIO>(uri, 1, 0, "FileIO");
}


