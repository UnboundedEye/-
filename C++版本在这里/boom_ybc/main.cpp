#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

// 模拟键盘按键函数（优化版，速度更快）
void simulateKeyPress(char c) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    // 处理需要Shift键的特殊字符
    bool needShift = false;

    switch (c) {
    case ' ': // 空格
        input.ki.wVk = VK_SPACE;
        break;
    case ',': // 逗号
        input.ki.wVk = VK_OEM_COMMA;
        break;
    case '.': // 句号
        input.ki.wVk = VK_OEM_PERIOD;
        break;
    case '!': // 感叹号
        input.ki.wVk = '1';
        needShift = true;
        break;
    case '?': // 问号
        input.ki.wVk = VK_OEM_2; // 对于美式键盘，/键
        needShift = true;
        break;
    case ';': // 分号
        input.ki.wVk = VK_OEM_1;
        break;
    case '\'': // 单引号
        input.ki.wVk = VK_OEM_7;
        break;
    case '\"': // 双引号 (需要Shift+')
        input.ki.wVk = VK_OEM_7;
        needShift = true;
        break;
    default:
        // 处理字母（大小写）
        if (isalpha(c)) {
            input.ki.wVk = toupper(c);
            needShift = isupper(c);
        }
        break;
    }

    // 如果需要Shift键，先按下Shift
    if (needShift) {
        INPUT shiftInput = { 0 };
        shiftInput.type = INPUT_KEYBOARD;
        shiftInput.ki.wVk = VK_SHIFT;
        shiftInput.ki.wScan = 0;
        shiftInput.ki.time = 0;
        shiftInput.ki.dwExtraInfo = 0;
        SendInput(1, &shiftInput, sizeof(INPUT));
    }

    // 按下键
    SendInput(1, &input, sizeof(INPUT));

    // 释放键
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));

    // 如果需要Shift键，释放Shift
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
    // 所有要输出的字符
    string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!-?;'\"";

    while (1) {
        cout << "快速打字练习脚本" << endl;
        cout << "请输入估计字符数: ";

        int num;
        cin >> num;
        cout << "请输入 'start' 开始快速打字 (3秒后开始): ";

        string input;
        cin >> input;


        if (input == "start") {
            // 给用户3秒时间切换到目标窗口
            for (int i = 3; i > 0; i--) {
                cout << "倒计时: " << i << " 秒" << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            cout << "开始快速打字..." << endl;

            // 循环输出所有字符
            for (int i = 0; i < num; i++) {
                for (char c : characters) {
                    simulateKeyPress(c);
                    // 极短的延迟以确保系统能处理每个按键
                }
            }

            cout << endl << "打字完成!" << endl;
        }
        else {
            cout << "输入错误，程序退出。" << endl;
        }
    }

    return 0;
}