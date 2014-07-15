##########Import proper Libraries##########
import csv
import numpy
import operator
import datetime
import matplotlib.pyplot as plt

##########Test functions##########
#Convert Data String  -> Float
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

#Pull out the non-date data
def get_data(data, field):

	#Establish a Variable
	value = []

	#Loop through the data
	for row in data:
		#Store the seeked data
		value.append(convert_to_float(row, field))
	
	#Return the desired data
	return value

#Convert the date String -> Datetime
def convert_date(data):
	
	#Establish a Variable
	t = []
	field = "db_time"

	#Loop through the data
	for row in data:	

		#Store the date
		t.append(datetime.datetime.strptime(row[field]+"00", "%Y-%m-%d %H:%M:%S.%f%z"))

	return t

#Find the index of data
def find_index(InputDate, ConvertedSet):

	#Establish a variable
	index = 0

	#Begin looping
	for row in ConvertedSet:
		#Check for a match
		if(InputDate.year == row.year):
			if(InputDate.month == row.month):
				if(InputDate.day == row.day):
					if(InputDate.hour == row.hour):
						if(InputDate.minute == row.minute):
							if(InputDate.second == row.second):
								return index
							else:
								index += 1
						else:
							index += 1
					else:
						index += 1
				else:
					index += 1
			else:
				index += 1
		else:
			index += 1

#Gather the chosen data in the range
def gather_chosen(ChosenData, BeginIndex, EndIndex):
	
	#Establish a storing variable
	chosen = []

	#Esablish a while Loop
	while(BeginIndex >= EndIndex):
	
		#Begin gathering
		chosen.append(ChosenData[BeginIndex])

		#Decrement
		BeginIndex -= 1

	#Return the data
	return chosen

########## Main ##########
#Establish variables
ChosenData = []
ConvertedTimed = []
x = []  #Plot storage for Dates
y = []  #Plot storage for Data

#Open Data File
datafile = open('215_data.csv', 'r')

#Gather the Data
dataorganized = csv.DictReader(datafile)

#Ask for input
field = input('Enter data field: ')
BeginDateIn = input('Enter beginning date and time(Y-m-d H:M:S.mS-GMT): ')
EndDateIn = input('Enter end date and time(Y-m-d H:M:S.mS-GMT): ')

#Convert input dates
BeginDate = datetime.datetime.strptime(BeginDateIn + "00", "%Y-%m-%d %H:%M:%S.%f%z")
EndDate = datetime.datetime.strptime(EndDateIn + "00", "%Y-%m-%d %H:%M:%S.%f%z")

#Get chosen data
datafile.seek(0) #Reset iterator
ChosenData = get_data(dataorganized, field)

#Regather the Data
dataorganized = csv.DictReader(datafile)
datafile.seek(0) #Reset iterator

#Convert time
ConvertedTime = convert_date(dataorganized)

#Find Index for begin time
BeginIndex = find_index(BeginDate, ConvertedTime)
EndIndex = find_index(EndDate, ConvertedTime)

#Obtain the chosen data in the specified range
y = gather_chosen(ChosenData, BeginIndex, EndIndex)

#Print the data
print(y)

#Number of entries from data
print(len(y))

#Close file
datafile.close()
