from tkinter import *
import serial as pys
from time import sleep

s=pys.Serial("com3",9600)

def zcom():
    s.write(f'z-{zAngle_Entry.get()}'.encode())
    sleep(1)
def xcom():
    s.write(f'x-{xLength_Entry.get()}-{xAngle_Entry.get()}-{dir}'.encode())
    sleep(1)
root = Tk()
root.title('Arduino Bending Machine')
root.geometry('700x450')
root.configure(background='white')
root.minsize(width = 480, height = 360)

header_label = Label(root, text = 'Arduino Wire Bending Machine',font=('Arial', 30))
header_label.pack(side = TOP)

zFrame = Frame(root)
zAngle_Entry = Entry(zFrame,font =('Arial',18))
zAngle_Entry.pack(side = LEFT)
z_Label = Label(zFrame, text = '轉動角度(度)')
z_Label.pack(side = LEFT)
zFrame.pack()
zAxis = Button(root,text = 'Turn the z-axis',command = zcom)
zAxis.pack()

xFrame = Frame(root)
xLength_Entry = Entry(xFrame,font =('Arial',18))
xLength_Entry.pack(side = LEFT)
x_l_Label = Label(xFrame, text = '餵線長度(mm)')
x_l_Label.pack(side = LEFT)
xFrame.pack()

xFrame_2 = Frame(root)
xAngle_Entry = Entry(xFrame_2,font =('Arial',18))
xAngle_Entry.pack(side = LEFT)
x_a_Label = Label(xFrame_2, text = '轉動角度(度)')
x_a_Label.pack(side = LEFT)
xFrame_2.pack()

Button_frame = Frame(root)
xAxis = Button(Button_frame,text = 'Bend the wire',command = xcom)
xAxis.pack(side = LEFT)
x_dir = Checkbutton(Button_frame,text = '正摺',variable=dir,onvalue=1, offvalue=0)
x_dir.pack(side = LEFT)
Button_frame.pack()


root.mainloop()