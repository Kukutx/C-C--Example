#include "QtDirDlg.h"
#include "ui_QtDirDlg.h"

QtDirDlg::QtDirDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtDirDlg)
{
    ui->setupUi(this);
}

QtDirDlg::~QtDirDlg()
{
    delete ui;
}

void QtDirDlg::on_buttonBox_clicked(QAbstractButton *button)
{
    QString filePath = QFileDialog::getExistingDirectory(this,"请选择文件保存路径",".");
    QFileInfo base(filePath);
    QString basename = base.baseName();   //打开的文件文件名,xx。不包含文件后缀
    QMessageBox::question(this,
           tr("弹窗标题"),
           basename,
           QMessageBox::Ok | QMessageBox::Cancel,
           QMessageBox::Ok);
}
