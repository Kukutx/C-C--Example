/********************************************************************************
** Form generated from reading UI file 'QtDirDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDIRDLG_H
#define UI_QTDIRDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_QtDirDlg
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *QtDirDlg)
    {
        if (QtDirDlg->objectName().isEmpty())
            QtDirDlg->setObjectName(QString::fromUtf8("QtDirDlg"));
        QtDirDlg->resize(400, 300);
        buttonBox = new QDialogButtonBox(QtDirDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(QtDirDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), QtDirDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), QtDirDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(QtDirDlg);
    } // setupUi

    void retranslateUi(QDialog *QtDirDlg)
    {
        QtDirDlg->setWindowTitle(QCoreApplication::translate("QtDirDlg", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDirDlg: public Ui_QtDirDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDIRDLG_H
