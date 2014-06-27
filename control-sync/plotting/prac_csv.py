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
x = []

#Open Data File
data = open('215_data.csv', 'r')

#Gather the Data
data1 = csv.DictReader(data)

#Examine data 
for row in data1:
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
	x.append(row)

#Print the data
print(x)

#Number of fields from data
print(len(x))

#Close file
data.close()
