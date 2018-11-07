import Tkinter as tk
from Tkinter import *
import Image, ImageTk
import time
import serial

SRL = serial.Serial('/dev/ttyACM0', 9600)

win = Tk()
win.title("RPi UI")
win.geometry('800x460+0+0')
win.resizable(0, 0)

angry = PhotoImage(file = "angry.gif")
smile = PhotoImage(file = "smile.gif")
tired = PhotoImage(file = "tired.gif")

CV = Canvas(win, width = 800, height = 460)

CV.create_image(400, 230, image = smile)
CV.pack()

while True:
    if(SRL.readline() < 0.5)



    while (time.time() - start_time < 5):
        win.update()

    CV.delete(ALL)
    CV.create_image(400, 230, image = smile)
    CV.pack()

    while True:
        win.update()
