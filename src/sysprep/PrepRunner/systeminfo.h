#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>

class SystemInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString osName MEMBER _osName READ osName NOTIFY dataChanged)
    Q_PROPERTY(QString kernelType MEMBER _kernelType READ kernelType NOTIFY dataChanged)
    Q_PROPERTY(QString distribution MEMBER _distribution READ distribution NOTIFY dataChanged)
    Q_PROPERTY(QString wmName MEMBER _wmName READ wmName NOTIFY dataChanged)

    static const char* strLinux;
    static const char* wmWindows;
    static const char* wmXfce;
    static const char* wmKde;
    static const char* wmUnknown;
    static const char* appXfce;
    static const char* appKde;
public:
    SystemInfo();

    QString osName() const { return _osName; }
    QString kernelType() const { return _kernelType; }
    QString distribution() const { return _distribution; }
    QString wmName() const { return _wmName; }

    bool isLinux() const;

signals:
    void dataChanged();

private:
    QString determineWm() const;
    bool isProcessRunning(const char* app) const;

    QString _osName;
    QString _kernelType;
    QString _distribution;
    QString _wmName;
};

#endif // SYSTEMINFO_H
