#ifndef DATAREADER_H
#define DATAREADER_H
//#include <QObject>

class QDomElement;

class DataReader
{
public:
    DataReader();
    bool read();
    void parseBuildingElement(QDomElement& root);
};

#endif // DATAREADER_H
