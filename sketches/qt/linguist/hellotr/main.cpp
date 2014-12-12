#include <QApplication>
#include <QTranslator>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("hellotr_la");
    app.installTranslator(&translator);

    QPushButton button(QPushButton::tr("Hello world!"));
    button.resize(200, 30);
    button.show();

    return app.exec();
}
