#include "fileio.h"

FileIO::FileIO(QQuickItem *parent):
    QObject(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

FileIO::~FileIO()
{
}

void FileIO::read()
{
    if( m_source.isEmpty() )
        return;

    QFile file(m_source.toLocalFile());
    if(!file.exists()) {
        qWarning() << "Does not exist: " << m_source.toLocalFile();
        return;
    }
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream st(&file);
        m_text = st.readAll();
        emit textChanged(m_text);
    }
}

void FileIO::write()
{
    if( m_source.isEmpty() )
        return;

    QFile file(m_source.toLocalFile());
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream st(&file);
        st << m_text;
    }
}
QUrl FileIO::source() const
{
    return m_source;
}

QString FileIO::text() const
{
    return m_text;
}

void FileIO::setSource(const QUrl& source)
{
    if(m_source==source)
        return;
    m_source = source;
    emit sourceChanged(source);
}

void FileIO::setText(const QString& text)
{
    if(m_text==text)
        return;
    m_text = text;
    emit textChanged(text);
}

