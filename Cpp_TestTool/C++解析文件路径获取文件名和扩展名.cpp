#if 0
#include <stdlib.h>
#include <stdio.h>
#include <string>
#pragma warning(disable : 4996)
int main()
{
    char path_buffer[_MAX_PATH] = "D:\\soft\\programming\\vmware.exe";
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath(path_buffer, drive, dir, fname, ext);
    /*
    _splitpath函数
　　在c或者c++编程中，常常会用到获取程序或文件的路径，比对路径做分解和合并处理，_splitpath和_makepath就可以完成这样的功能。
　　函数的声明
　　void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
　　功能是分解路径，把你的完整路径给分割开来，就是一个对字符串进行分割的函数。
    */
    printf("Drive:%s\n file name: %s\n file type: %s\n", drive, fname, ext);
    strcat(fname, ext);
    printf("File name with extension :%s\n", fname);
    return 0;
}
#endif // 0
