import Tkinter as tk
from Tkinter import *
import Image, ImageTk
import time

win = Tk()
win.title("RPi UI")
win.geometry('800x460+0+0')
win.resizable(0, 0)

# smile = Image.open("/home/pi/test/smile.gif")
# angry = Image.open("/home/pi/test/angry.gif")
# tired = Image.open("/home/pi/test/tired.gif")

angry = PhotoImage(file = "angry.gif")
smile = PhotoImage(file = "smile.gif")
tired = PhotoImage(file = "tired.gif")

CV = Canvas(win, width = 800, height = 460)

CV.create_image(400, 230, image = angry)
CV.pack()

start_time = time.time()

while (time.time() - start_time < 5):
    win.update()

#CV.delete(ALL)
CV.create_image(400, 230, image = smile)
CV.pack()

while True:
    win.update()
