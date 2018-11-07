import Tkinter as tk
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)

win = tk.Tk()
win.title("Using Tkinter")
GPIO.output(18, GPIO.LOW)
stat = False

def ledToggle():
    global stat
    if stat:
        GPIO.output(18, GPIO.LOW)
        ledButton["text"] = "LED OFF"
        stat = False
    else:
        GPIO.output(18, GPIO.HIGH)
        ledButton["text"] = "LED ON"
        stat = True

def exitProgram():
    GPIO.cleanup()
    win.quit()

ledButton = tk.Button(win, text = 'LED OFF', command = ledToggle, bg = 'bisque2', height = 1, width = 24)
ledButton.grid(row = 0, sticky = tk.NSEW)
exitButton = tk.Button(win, text = 'EXIT', command = exitProgram, bg = 'cyan', height = 1, width = 6)
exitButton.grid(row = 1, sticky = tk.E)

tk.mainloop()
