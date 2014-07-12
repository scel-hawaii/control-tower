#Import proper Libraries
import csv
import numpy
import operator
import datetime
import matplotlib.pyplot as plt

#Test functions
def convert_to_float(row, field):

	#Check if there is data
	if(row[field] == ''):

		#No data = nan
		row[field] = float('nan')
		return row[field]
	else:
		#Convert value and return
		row[field] = float(row[field])
		return row[field]

def get_data(data, field):

	#Establish a Variable
	value = []

	#Loop through the data
	for row in data:
		#Store the seeked data
		value.append(convert_to_float(row, field))
	
	#Return the desired data
	return value

def convert_date(data):
	
	#Establish a Variable
	field = "db_time"

	#Loop through the data
	for row in data:	

		#Store the date
<<<<<<< HEAD
		converted = datetime.datetime.strptime(row[field]+"00", "%Y-%m-%d %H:%M:%S.%f%z")
		row[field] = converted
=======
		t.append(datetime.datetime.strptime(row[field]+"00", "%Y-%m-%d %H:%M:%S.%f%z"))
>>>>>>> 5a99f5fcbe0882634d48656888dd60d7c8bc862f

	return row

#Establish variables
x = []
y = []

#Open Data File
datafile = open('215_data.csv', 'r')

#Gather the Data
dataorganized = csv.DictReader(datafile)

#Get chosen data
datafile.seek(0) #Reset iterator
x = get_data(dataorganized, "overflow_num")

#Regather the Data
dataorganized = csv.DictReader(datafile)
datafile.seek(0) #Reset iterator

#Convert time
y = convert_date(dataorganized)

#Print the data
print(y)

#Number of entries from data
print(len(x))

#Close file
datafile.close()
