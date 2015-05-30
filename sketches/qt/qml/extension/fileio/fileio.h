#ifndef FILEIO_H
#define FILEIO_H

#include <QQuickItem>

class FileIO : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(FileIO)

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:

    FileIO(QQuickItem *parent = 0);
    ~FileIO();

    Q_INVOKABLE void read();
    Q_INVOKABLE void write();

    QUrl source() const;
    QString text() const;

public slots:
    void setSource(const QUrl& source);
    void setText(const QString& text);

signals:
    void sourceChanged(QUrl source);
    void textChanged(QString text);

private:
    QUrl m_source;
    QString m_text;
};

#endif // FILEIO_H

