下载 qtwinmigrate：https://github.com/qtproject/qt-solutions（此工程是用于QT&MFC混编的，当然也可以用于其他平台）

解压，找到 \qtwinmigrate\examples\qtdll\qtdll.pro，使用QtCreator打开(也可以直接提取内部单个工程)

然后编译后，生成qtdialog.dll

新建控制台程序项目名Call_qtdll（用来调用qtdialog.dll）

使用 windeployqt 拉取 qtdialog.dll 所依赖的文件，并将其一同放置在控制台生成的目录下，运行控制台程序，即可看到控制台程序调起了qt的dll。

![](D:\Project\C-C++\QT\Qt_ExternalExtension\Call_qtdll\1.png)