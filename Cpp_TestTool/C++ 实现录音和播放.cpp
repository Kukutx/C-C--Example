#if 0
#include <iostream>
#include <windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

static BYTE* file = (BYTE*)malloc(sizeof(BYTE) * 512);
static DWORD hasRecorded = 0;
static BOOL recurr = TRUE;
class USER
{
public:
    int a = 0;
    char b = 'a';
};

void CALLBACK callback(HWAVEIN hwi,          // �豸���
    UINT uMsg,            // ��Ϣ
    DWORD_PTR dwInstance, // ����
    DWORD_PTR dwParam1,   // ����1
    DWORD_PTR dwParam2);  // ����2

int main()
{
    HWAVEIN hWaveIn;           //�����豸
    HWAVEOUT hWaveOut;         //����豸
    WAVEFORMATEX waveform;     //������Ƶ����ʽ
    BYTE* pBuffer1, * pBuffer2; //������Ƶ������������������
    WAVEHDR whdr_i1, whdr_i2;  //������Ƶͷ
    WAVEHDR whdr_o;            //�����Ƶͷ
    USER* user = new USER();   //�����û�

    // �豸����
    int count = waveInGetNumDevs();
    printf("\n��Ƶ����������%d\n", count);

    // �豸����
    WAVEINCAPS waveIncaps;
    MMRESULT mmResult = waveInGetDevCaps(0, &waveIncaps, sizeof(WAVEINCAPS)); // 2
    std::cout << "�豸���ƣ�" << waveIncaps.szPname << std::endl;

    // ������Ƶ����ʽ
    waveform.nSamplesPerSec = 44100;                                           // ������
    waveform.wBitsPerSample = 16;                                              // ��������
    waveform.nChannels = 2;                                                    // ��������
    waveform.cbSize = 0;                                                       // ����ռ�
    waveform.wFormatTag = WAVE_FORMAT_PCM;                                     // ��Ƶ��ʽ
    waveform.nBlockAlign = (waveform.wBitsPerSample * waveform.nChannels) / 8; // �����
    waveform.nAvgBytesPerSec = waveform.nBlockAlign * waveform.nSamplesPerSec; // ��������

    //�����ڴ�
    pBuffer1 = new BYTE[1024 * 10000];
    pBuffer2 = new BYTE[1024 * 10000];
    memset(pBuffer1, 0, 1024 * 10000); // �ڴ���0
    memset(pBuffer2, 0, 1024 * 10000); // �ڴ���0

    // ������Ƶͷ
    whdr_i1.lpData = (LPSTR)pBuffer1;      // ָ��buffer
    whdr_i1.dwBufferLength = 1024 * 10000; // buffer��С
    whdr_i1.dwBytesRecorded = 0;           // buffer��Ŵ�С
    whdr_i1.dwUser = 0;
    whdr_i1.dwFlags = 0;
    whdr_i1.dwLoops = 1;
    whdr_i2.lpData = (LPSTR)pBuffer1;      // ָ��buffer
    whdr_i2.dwBufferLength = 1024 * 10000; // buffer��С
    whdr_i2.dwBytesRecorded = 0;           // buffer��Ŵ�С
    whdr_i2.dwUser = 0;
    whdr_i2.dwFlags = 0;
    whdr_i2.dwLoops = 1;

    // ����¼��
    MMRESULT mRet = waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD_PTR)callback, (DWORD_PTR)user, CALLBACK_FUNCTION);
    waveInPrepareHeader(hWaveIn, &whdr_i1, sizeof(WAVEHDR)); //׼��buffer
    waveInPrepareHeader(hWaveIn, &whdr_i2, sizeof(WAVEHDR)); //׼��buffer
    waveInAddBuffer(hWaveIn, &whdr_i1, sizeof(WAVEHDR));     //���buffer
    waveInAddBuffer(hWaveIn, &whdr_i2, sizeof(WAVEHDR));     //���buffer

    waveInStart(hWaveIn);
    getchar();
    recurr = FALSE;
    // waveInStop(hWaveIn);
    waveInReset(hWaveIn);
    waveInClose(hWaveIn);

    HANDLE wait = CreateEvent(NULL, 0, 0, NULL);
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);

    // ����¼��
    whdr_o.lpData = (LPSTR)file;         // ָ��buffer
    whdr_o.dwBufferLength = hasRecorded; // buffer��С
    whdr_o.dwBytesRecorded = hasRecorded;
    whdr_o.dwFlags = 0;
    whdr_o.dwLoops = 1;

    ResetEvent(wait);
    waveOutPrepareHeader(hWaveOut, &whdr_o, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &whdr_o, sizeof(WAVEHDR));
    /*Sleep(5000);*/
    DWORD dw = WaitForSingleObject(wait, INFINITE);
    if (dw == WAIT_OBJECT_0)
    {
        std::cout << "jieshu" << std::endl;
        return 0;
    }
}

void CALLBACK callback(HWAVEIN hwi,          // �豸���
    UINT uMsg,            // ��Ϣ
    DWORD_PTR dwInstance, // ����
    DWORD_PTR dwParam1,   // ����1
    DWORD_PTR dwParam2)   // ����2
{
    // ��ȡ����
    USER* user2 = (USER*)dwInstance;
    // ��ȡ��Ƶͷ
    PWAVEHDR pwhdr = (PWAVEHDR)dwParam1;
    // ������Ϣ
    switch (uMsg)
    {
    case WIM_OPEN: // ��¼���豸
        printf("�ɹ����豸..\n");
        break;

    case WIM_DATA: // ����������
    {
        printf("���������..\n");
        printf("a:%d , b:%c \n", user2->a, user2->b);
        // �������Ϣ
        DWORD buflen = pwhdr->dwBufferLength;
        DWORD bytrecd = pwhdr->dwBytesRecorded;
        hasRecorded += bytrecd;

        // ��������
        file = (BYTE*)realloc(file, hasRecorded * sizeof(BYTE));
        // �洢������
        if (file)
        {
            memcpy(&file[hasRecorded - bytrecd], pwhdr->lpData, bytrecd);
            printf("�Ѵ洢:%d byte\n", hasRecorded);
        }
        // ѭ��
        if (recurr)
        {
            // ���뻺��
            waveInAddBuffer(hwi, pwhdr, sizeof(WAVEHDR));
        }
    }
    break;
    case WIM_CLOSE: // �ر�¼���豸
        printf("ֹͣ¼��..\n");
        break;
    default:
        break;
    }
}
#endif // 0
