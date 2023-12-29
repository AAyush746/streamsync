#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void searchNetflix();
    void setupUi();

private:
    Ui::Dialog *ui;
    QLineEdit *movieNameEdit;
    QPushButton *searchButton;
    QLabel *resultLabel;
};

#endif // DIALOG_H
