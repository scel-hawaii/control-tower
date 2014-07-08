#Import proper Libraries
import csv
import numpy
import operator
import datetime

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

def get_date(data, field):
	
	#Establish a Variable
	t = []

	#Loop through the data
	for row in data:	
		#Store the date
		t.append(datetime.datetime.strptime(row[field], "%Y-%m-%d %H:%M:%S.%f-%z"))

	#Return the dates
	return t

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

datafile.seek(0) #Reset iterator
y = get_date(dataorganized, "db_time")

#Print the data
print(y)

#Number of entries from data
print(len(x))

#Close file
datafile.close()
