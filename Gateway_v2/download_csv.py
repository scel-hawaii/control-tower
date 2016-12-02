import psycopg2
import sys
import datetime
import csv
import os.path

#some table name, must get table name from user
table_name = raw_input("Enter name of table you would like to download: ")

filename = raw_input("Enter name of output file (include .csv extension): ")
# check if file already exists
while(os.path.isfile(filename) == True):
	filename = raw_input("That file already exists, enter a new filename: ") 	

#make connection to db
con = psycopg2.connect("dbname='control_tower' user='control_tower' password='password'")
cur = con.cursor()

# select the appropriate table
cur.execute("SELECT * FROM %s;" %(table_name))
table = cur.fetchall()
# get names of columns
colnames = [desc[0] for desc in cur.description]
# add new columns for time/date to colnames
colnames.remove("time_received")
colnames.insert(0, "time")
colnames.insert(0, "day")
colnames.insert(0, "month")
colnames.insert(0, "year")

"""
setup output csv file
"""
with open(filename, 'a') as csvfile:
	headerString = ""
	for value in colnames:
		headerString += str(value) + ','
	headerString = headerString[:-1]
	headerString += '\n'
	csvfile.write(headerString)

	# write data to csv file
	for line in table:
		# clean up data ine
		data = str(line)
		data = data.replace("(", "")
		data = data.replace(")", "")
		data = data.replace(" ", "")
		data = data.replace("datetime.datetime", "")
		data = data.split(",")
		time = datetime.time(int(data[3]), int(data.pop(4)), int(data.pop(4)), int(data.pop(4)))
		data[3] = str(time)
		

		dataString = ''
    		for value in data:
        		dataString += str(value)
        		dataString += ','
    		dataString = dataString[:-1]
		dataString += '\n'
		csvfile.write(dataString)

