#include <qmfcapp.h>
#include <qwinwidget.h>

#include <QMessageBox>
#include <windows.h>

#include "QtDirDlg.h"
//DLL主函数
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/ )
{
    static bool ownApplication = FALSE;

    if ( dwReason == DLL_PROCESS_ATTACH )
	ownApplication = QMfcApp::pluginInstance( hInstance );
    if ( dwReason == DLL_PROCESS_DETACH && ownApplication )
	delete qApp;

    return TRUE;
}
//弹窗
extern "C" __declspec(dllexport) bool showDialog( HWND parent )
{
    QWinWidget win( parent );
    win.showCentered();
    QMessageBox::about( &win, "About QtMfc", "QtMfc Version 1.0\nCopyright (C) 2003" );

    return TRUE;
}
//自定义窗口
extern "C" __declspec(dllexport) bool ShowDirDialog(HWND parent)
{
    QWinWidget win(parent);
    win.center();
    QtDirDlg dlg(&win);
    dlg.exec();

    return TRUE;
}
