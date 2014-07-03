#Import proper Libraries
import csv
import numpy
import operator

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
		
#Establish variables
x = []
y = []

#Open Data File
datafile = open('215_data.csv', 'r')

#Gather the Data
dataorganized = csv.DictReader(datafile)

#Get chosen data
x = get_data(dataorganized, "overflow_num")

#Print the data
print(x)

#Number of entries from data
print(len(x))

#Close file
datafile.close()
