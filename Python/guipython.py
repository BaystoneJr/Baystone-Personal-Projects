from tkinter import *

payCalcTexts = ("Welcome to PayCalc, software to calculate your pay.", "Please fill the input fields below to calculate your pay.")
payCalcFormTexts = ("Calculate pay", "Pay per hour", 'Worked hours', 'Calculate pay')
payCalcSetupText = ("Fill your info below", "Name")


class appWindow(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master = master
        self.init_window()

    def init_window(self):
        self.master.title("PayCalc")

        self.pack(fill=BOTH, expand=1)

        menu = Menu(self.master)
        self.master.config(menu=menu)

        file = Menu(menu)
        file.add_command(label="Exit", command=self.client_exit)
        
        menu.add_cascade(label="File", menu=file)
        self.createInfo()
        self.createPayCalcForm()

    @staticmethod
    def client_exit():
        exit()

    def createInfo(self):
        softwareInfo = Label(self, text=payCalcTexts[0])
        useOfInfo = Label(self, text=payCalcTexts[1])

        softwareInfo.pack()
        useOfInfo.pack()
    def createPayCalcForm(self):
        def calculatePay():
            payPerHour = payPerHourEntry.get()
            workedHours = hoursWorkedEntry.get()

            try:
                payPerHourNumber = float(payPerHour)
                workedHoursNumber = float(workedHours)
            except ValueError:
                errorText = "Invalid input, please try again"
                calculatedPayText['text'] = errorText
                return
            except:
                errorText = "Something went wrong, please try again later or contact software creator if this repeats"
                calculatedPayText['text'] = errorText
                return

            usersPay = payPerHourNumber * workedHoursNumber

            payStr = "Your pay: " + str(round(usersPay, 2))

            calculatedPayText['text'] = payStr

        formLabelFrame = LabelFrame(self, text = payCalcFormTexts[0])
        
        payPerHourEntry =  Entry(formLabelFrame)
        pPHText = Label(formLabelFrame, text=payCalcFormTexts[1])
        hoursWorkedEntry = Entry(formLabelFrame)
        hWEText = Label(formLabelFrame, text = payCalcFormTexts[2])
        calculatePayButton = Button(formLabelFrame, text = payCalcFormTexts[3], command = calculatePay)
        calculatedPayText = Label(formLabelFrame, text="")
        
        pPHText.pack()
        payPerHourEntry.pack()
        hWEText.pack()
        hoursWorkedEntry.pack()
        calculatePayButton.pack()
        calculatedPayText.pack()
        

        formLabelFrame.pack(fill = BOTH, expand=1)


root = Tk()

root.geometry("400x300")

app = appWindow(root)
root.mainloop()

