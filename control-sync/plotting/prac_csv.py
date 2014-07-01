#Import proper Libraries
import csv
import numpy
import operator

#Test function
def convert_to_float(field):
	#Check if there is data
	if(row[field] == ''):
		#No data = nan
		row[field] = float('nan')
		return
	row[field] = float(row[field])

#Establish variables
data = []
x = []
y = []


#Open Data File
datafile = open('215_data.csv', 'r')

#Gather the Data
dataorganized = csv.DictReader(datafile)

#Examine data 
for row in dataorganized:

	#Create proper types
	convert_to_float("address")
	convert_to_float("uptime_ms")
	convert_to_float("bmp085_temp_decic")
	convert_to_float("bmp085_press_pa")
	convert_to_float("batt_mv")
	convert_to_float("panel_mv")
	convert_to_float("apogee_mv")
	convert_to_float("apogee_w_m2")
	convert_to_float("dallas_amb_c")
	convert_to_float("dallas_roof_c")
	convert_to_float("panel_ua")
	convert_to_float("humidity_centi_pct")
	convert_to_float("indicator")
	data.append(row) #ERROR: Currently storing data randomly

#Pull pull specific field values

#Print the data
print(data[0])

#Number of fields from data
print(len(data))

#Close file
datafile.close()
