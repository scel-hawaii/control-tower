# Import Libraries
import csv
import numpy
import operator
import datetime

# Establish variable to hold date
t = []

# Set test date
date = "2014-06-18 12:10:09.999999-10"

# Modify date to proper string
date = date + "00"

# Print date
print(date)

# Strip time into proper format
t.append(datetime.datetime.strptime(date, "%Y-%m-%d %H:%M:%S.%f%z"))

# Print date string
print(t)

# Converting timedelta to hours, minutes, and seconds
t1 = datetime.timedelta(-1, 50400)

# Get days and seconds and print
days, seconds = t1.days, t1.seconds
print(days, seconds)

# Calculate hours, minutes, and seconds and print them
hours = days*24 + seconds // 3600
minutes = (seconds%3600) // 60
seconds = (seconds%60)
print(hours, minutes, seconds)
