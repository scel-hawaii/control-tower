#Import proper Libraries
import csv
import numpy
import operator

#Test function
def convert_to_int(field):
	row[field] = int(row[field])

#Establish variables
x = []

#Open Data File
data = open('215_data.csv', 'r')

#Gather the Data
data1 = csv.DictReader(data)

#Examine data 
for row in data1:
	#Create proper types
	convert_to_int("address")
	#convert_to_int("uptime_ms")
	#convert_to_int("bmp085_temp_decic")
	#convert_to_int("bmp085_press_pa")
	#convert_to_int("batt_mv")
	x.append(row)

#Print the data
print(x)

#Number of fields from data
print(len(x))

#Close file
data.close()
