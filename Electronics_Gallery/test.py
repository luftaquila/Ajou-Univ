import Tkinter as tk
from Tkinter import *
from pytesseract import *
import RPi.GPIO as GPIO
import picamera
import Image, ImageTk
import time
import serial
import subprocess
import webbrowser

SRL = serial.Serial('/dev/ttyACM0', 9600)

win = Tk()
win.title("RPi UI")
win.geometry('800x460+0+0')
win.resizable(0, 0)

angry = PhotoImage(file = "angry.gif")
smile = PhotoImage(file = "smile.gif")
tired = PhotoImage(file = "tired.gif")
loading = PhotoImage(file = "loading.gif")

CV = Canvas(win, width = 800, height = 460)
CV.create_image(400, 230, image = smile)
CV.pack()

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.IN, pull_up_down = GPIO.PUD_UP)

while True:
    input = SRL.readline()

    if(int(input) == 1):
        CV.delete(ALL)
        CV.create_image(400, 230, image = smile)
        CV.pack()

    elif(int(input) == 2):
        CV.delete(ALL)
        CV.create_image(400, 230, image = tired)
        CV.pack()

    elif(int(input) == 3):
        CV.delete(ALL)
        CV.create_image(400, 230, image = angry)
        CV.pack()

    if not GPIO.input(17) :
        CV.delete(ALL)
        with picamera.PiCamera() as camera :
            CV.create_image(400, 230, image = loading)
            CV.pack()
            camera.start_preview()
            time.sleep(7)
            camera.capture('/home/pi/test/image.jpg')
            camera.stop_preview()
            TRS = image_to_string(Image.open('image.jpg'), lang='kor+eng')
            print(TRS)
            url = 'https://translate.google.com/#auto/ko/' + TRS
            webbrowser.open(url)

    win.update()
