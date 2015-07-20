#include "tableinitializer.h"


TableInitializer::TableInitializer()
{
}

TableInitializers::TableInitializers()
{
}

TableInitializers& TableInitializers::getInstance()
{
    static TableInitializers s_tableInitializers;
    return s_tableInitializers;
}

void TableInitializers::doRegister(TableInitializer* initializer)
{
    _initializers.append(initializer);
}

QList<TableInitializer*> TableInitializers::getInitializers()
{
    return _initializers;
}

