#ifndef KEYSTROKEDIALOG_H
#define KEYSTROKEDIALOG_H

#include <QDialog>

namespace Ui {
class KeyStrokeDialog;
}

class KeyStrokeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyStrokeDialog(QWidget *parent = 0);
    ~KeyStrokeDialog();

    QString getKeyStrokes() const;

private:
    Ui::KeyStrokeDialog *ui;
};

#endif // KEYSTROKEDIALOG_H
