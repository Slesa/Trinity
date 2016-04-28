#include "data/datareader.h"
#include <QFile>
#include <QDomDocument>
#include <QQmlApplicationEngine>
#include <QDebug>

DataReader::DataReader()
{
}

bool DataReader::read() {
    const QString fileName = QStringLiteral(":/highrise.xml");
    const QString tagRoot = "highrise";
    const QString tagName = "name";

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file " << fileName << ":\n" << file.errorString();
/*        QMessageBox::warning(NULL, tr("DataReader"),
            tr("Cannot read file %1:\n%2.")
                .arg(fileName)
                .arg(file.errorString()));*/
        return false;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument domDocument;
    if (!domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        qDebug() << "Parse error at line " << errorLine << ", column " << errorColumn << ":\n" << errorStr;
/*        QMessageBox::information(NULL, tr("DataReader"),
            tr("Parse error at line %1, column %2:\n%3")
                .arg(errorLine)
                .arg(errorColumn)
                .arg(errorStr));*/
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName() != tagRoot) {
        qDebug() << "The file is not an HighRise file.";
/*        QMessageBox::information(NULL, tr("DataReader"),
            tr("The file is not an HighRise file."));*/
        return false;
    }
    if (root.hasAttribute("version") && root.attribute("version") != "1.0") {
        qDebug() << "The file is not an HighRise version 1.0 file.";
/*        QMessageBox::information(NULL, tr("DataReader"),
            tr("The file is not an HighRise version 1.0 file."));*/
        return false;
    }

    QDomElement child = root.firstChildElement("building");
    if(!child.isNull()) {
        parseBuildingElement(child);
        // child = child.nextSiblingElement("building");
    }

    return true;
}

void DataReader::parseBuildingElement(QDomElement& root) {
    QString name = (element.attribute(tagName);
    QDomElement child = root.firstChildElement();
    while (!child.isNull()) {
        if (child.tagName() == tagFloor) {
            qDebug() << "Invalid building element " << child.tagName() << ", skipping";
            continue;
        }
        child = child.nextSiblingElement();
    }
}
