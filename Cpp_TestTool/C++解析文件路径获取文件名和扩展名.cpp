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
    _splitpath����
������c����c++����У��������õ���ȡ������ļ���·�����ȶ�·�����ֽ�ͺϲ�����_splitpath��_makepath�Ϳ�����������Ĺ��ܡ�
��������������
����void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
���������Ƿֽ�·�������������·�����ָ��������һ�����ַ������зָ�ĺ�����
    */
    printf("Drive:%s\n file name: %s\n file type: %s\n", drive, fname, ext);
    strcat(fname, ext);
    printf("File name with extension :%s\n", fname);
    return 0;
}
#endif // 0
