from os import write

from pynput.keyboard import Controller
import easygui
import time

# 创建键盘控制器
keyboard = Controller()

text =  easygui.enterbox('请输入你在3秒后键盘一次性输出的文字','快速输出文字','请输入文本')
if text == None:
    easygui.msgbox('你关闭了程序','程序关闭',ok_button='知道了')
else:
    time.sleep(3)
    keyboard.type(text)

