#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

// ģ����̰����������Ż��棬�ٶȸ��죩
void simulateKeyPress(char c) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // ������ҪShift���������ַ�
    bool needShift = false;

    switch (c) {
    case ' ': // �ո�
        input.ki.wVk = VK_SPACE;
        break;
    case ',': // ����
        input.ki.wVk = VK_OEM_COMMA;
        break;
    case '.': // ���
        input.ki.wVk = VK_OEM_PERIOD;
        break;
    case '!': // ��̾��
        input.ki.wVk = '1';
        needShift = true;
        break;
    case '?': // �ʺ�
        input.ki.wVk = VK_OEM_2; // ������ʽ���̣�/��
        needShift = true;
        break;
    case ';': // �ֺ�
        input.ki.wVk = VK_OEM_1;
        break;
    case '\'': // ������
        input.ki.wVk = VK_OEM_7;
        break;
    case '\"': // ˫���� (��ҪShift+')
        input.ki.wVk = VK_OEM_7;
        needShift = true;
        break;
    default:
        // ������ĸ����Сд��
        if (isalpha(c)) {
            input.ki.wVk = toupper(c);
            needShift = isupper(c);
        }
        break;
    }

    // �����ҪShift�����Ȱ���Shift
    if (needShift) {
        INPUT shiftInput = { 0 };
        shiftInput.type = INPUT_KEYBOARD;
        shiftInput.ki.wVk = VK_SHIFT;
        shiftInput.ki.wScan = 0;
        shiftInput.ki.time = 0;
        shiftInput.ki.dwExtraInfo = 0;
        SendInput(1, &shiftInput, sizeof(INPUT));
    }

    // ���¼�
    SendInput(1, &input, sizeof(INPUT));

    // �ͷż�
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

    // �����ҪShift�����ͷ�Shift
    if (needShift) {
        INPUT shiftInput = { 0 };
        shiftInput.type = INPUT_KEYBOARD;
        shiftInput.ki.wVk = VK_SHIFT;
        shiftInput.ki.wScan = 0;
        shiftInput.ki.dwFlags = KEYEVENTF_KEYUP;
        shiftInput.ki.time = 0;
        shiftInput.ki.dwExtraInfo = 0;
        SendInput(1, &shiftInput, sizeof(INPUT));
    }
}

int main() {
    // ����Ҫ������ַ�
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!-?;'\"";

    while (1) {
        cout << "���ٴ�����ϰ�ű�" << endl;
        cout << "����������ַ���: ";

        int num;
        cin >> num;
        cout << "������ 'start' ��ʼ���ٴ��� (3���ʼ): ";

        string input;
        cin >> input;


        if (input == "start") {
            // ���û�3��ʱ���л���Ŀ�괰��
            for (int i = 3; i > 0; i--) {
                cout << "����ʱ: " << i << " ��" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            cout << "��ʼ���ٴ���..." << endl;

            // ѭ����������ַ�
            for (int i = 0; i < num; i++) {
                for (char c : characters) {
                    simulateKeyPress(c);
                    // ���̵��ӳ���ȷ��ϵͳ�ܴ���ÿ������
                }
            }

            cout << endl << "�������!" << endl;
        }
        else {
            cout << "������󣬳����˳���" << endl;
        }
    }

    return 0;
}