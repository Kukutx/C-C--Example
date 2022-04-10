#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class QtDirDlg;
}

class QtDirDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QtDirDlg(QWidget *parent = nullptr);
    ~QtDirDlg();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::QtDirDlg *ui;
};

#endif // DIALOG_H
