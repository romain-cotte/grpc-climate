import datetime

now = datetime.datetime.now()
print("date and time:", now.strftime("%d/%m/%Y, %H:%M:%S"))

today = datetime.date.today()
print(f"today = {today}")
