#if 0
#include <iostream>
#include <Windows.h>
using namespace std;
// ��װ����
BOOL installDvr(CONST WCHAR drvPath[50], CONST WCHAR serviceName[20]) {

    // �򿪷�����ƹ��������ݿ�
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // Ŀ������������,NULL�����ӱ��ؼ�����ϵķ�����ƹ�����
        NULL,                   // ������ƹ��������ݿ�����ƣ�NULL���� SERVICES_ACTIVE_DATABASE ���ݿ�
        SC_MANAGER_ALL_ACCESS   // ����Ȩ��
    );
    if (schSCManager == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // ����������������������ƹ��������ݿ�
    SC_HANDLE schService = CreateService(
        schSCManager,               // ����ؼ����������ݿ�ľ��
        serviceName,                // Ҫ��װ�ķ��������
        serviceName,                // �û��������������ʶ�������ʾ����
        SERVICE_ALL_ACCESS,         // �Է���ķ���Ȩ�ޣ�����ȫȨ��
        SERVICE_KERNEL_DRIVER,      // �������ͣ���������
        SERVICE_DEMAND_START,       // ��������ѡ����̵��� StartService ʱ����
        SERVICE_ERROR_IGNORE,       // ����޷����������Դ����������
        drvPath,                    // �����ļ�����·������������ո���Ҫ���˫����
        NULL,                       // ���������ĸ��ض����飺��������ĳ����
        NULL,                       // ���ն�����Ψһ���ֵ��������
        NULL,                       // �������˳�����飺����û��������
        NULL,                       // ���з�����˻�����ʹ�� LocalSystem �˻�
        NULL                        // LocalSystem �˻�����
    );
    if (schService == NULL) {
        CloseServiceHandle(schService);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// ��������
BOOL startDvr(CONST WCHAR serviceName[20]) {

    // �򿪷�����ƹ��������ݿ�
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // Ŀ������������,NULL�����ӱ��ؼ�����ϵķ�����ƹ�����
        NULL,                   // ������ƹ��������ݿ�����ƣ�NULL���� SERVICES_ACTIVE_DATABASE ���ݿ�
        SC_MANAGER_ALL_ACCESS   // ����Ȩ��
    );
    if (schSCManager == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // �򿪷���
    SC_HANDLE hs = OpenService(
        schSCManager,           // ����ؼ����������ݿ�ľ��
        serviceName,            // Ҫ�򿪵ķ�����
        SERVICE_ALL_ACCESS      // �������Ȩ�ޣ�����Ȩ��
    );
    if (hs == NULL) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }
    if (StartService(hs, 0, 0) == 0) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }


    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// ֹͣ����
BOOL stopDvr(CONST WCHAR serviceName[20]) {

    // �򿪷�����ƹ��������ݿ�
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // Ŀ������������,NULL�����ӱ��ؼ�����ϵķ�����ƹ�����
        NULL,                   // ������ƹ��������ݿ�����ƣ�NULL���� SERVICES_ACTIVE_DATABASE ���ݿ�
        SC_MANAGER_ALL_ACCESS   // ����Ȩ��
    );
    if (schSCManager == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // �򿪷���
    SC_HANDLE hs = OpenService(
        schSCManager,           // ����ؼ����������ݿ�ľ��
        serviceName,            // Ҫ�򿪵ķ�����
        SERVICE_ALL_ACCESS      // �������Ȩ�ޣ�����Ȩ��
    );
    if (hs == NULL) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }

    // ���������������
    SERVICE_STATUS status;
    if (QueryServiceStatus(hs, &status) == 0) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }
    if (status.dwCurrentState != SERVICE_STOPPED &&
        status.dwCurrentState != SERVICE_STOP_PENDING
        ) {
        // ���͹رշ�������
        if (ControlService(
            hs,                         // ������
            SERVICE_CONTROL_STOP,       // �����룺֪ͨ����Ӧ��ֹͣ
            &status                     // �������µķ���״̬��Ϣ
        ) == 0) {
            CloseServiceHandle(hs);
            CloseServiceHandle(schSCManager);
            return FALSE;
        }

        // �жϳ�ʱ
        INT timeOut = 0;
        while (status.dwCurrentState != SERVICE_STOPPED) {
            timeOut++;
            QueryServiceStatus(hs, &status);
            Sleep(50);
        }
        if (timeOut > 80) {
            CloseServiceHandle(hs);
            CloseServiceHandle(schSCManager);
            return FALSE;
        }
    }

    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

// ж������
BOOL unloadDvr(CONST WCHAR serviceName[20]) {
    // �򿪷�����ƹ��������ݿ�
    SC_HANDLE schSCManager = OpenSCManager(
        NULL,                   // Ŀ������������,NULL�����ӱ��ؼ�����ϵķ�����ƹ�����
        NULL,                   // ������ƹ��������ݿ�����ƣ�NULL���� SERVICES_ACTIVE_DATABASE ���ݿ�
        SC_MANAGER_ALL_ACCESS   // ����Ȩ��
    );
    if (schSCManager == NULL) {
        CloseServiceHandle(schSCManager);
        return FALSE;
    }
    // �򿪷���
    SC_HANDLE hs = OpenService(
        schSCManager,           // ����ؼ����������ݿ�ľ��
        serviceName,            // Ҫ�򿪵ķ�����
        SERVICE_ALL_ACCESS      // �������Ȩ�ޣ�����Ȩ��
    );
    if (hs == NULL) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }
    // ɾ������
    if (DeleteService(hs) == 0) {
        CloseServiceHandle(hs);
        CloseServiceHandle(schSCManager);
        return FALSE;
    }
    CloseServiceHandle(hs);
    CloseServiceHandle(schSCManager);
    return TRUE;
}

int main()
{
    if (installDvr(L"C:\\Test_Driver_1.sys", L"LYSM_service") == TRUE) {
        cout << "installDvr success." << endl;
    }
    if (startDvr(L"LYSM_service") == TRUE) {
        cout << "startDvr success." << endl;
    }
    if (stopDvr(L"LYSM_service") == TRUE) {
        cout << "stopDvr success." << endl;
    }
    if (unloadDvr(L"LYSM_service") == TRUE) {
        cout << "unloadDvr success." << endl;
    }
    getchar();
    return 0;
}
#endif // 0
