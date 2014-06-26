import csv
import numpy
import operator

x = []

#with open('215_data.csv', 'r') as csvfile:
#	reader = csv.DictReader(csvfile)
#	for row in reader:
#		x.append(row)

data = open('215_data.csv', 'r')

data1 = csv.reader(data, delimiter = '\n')

for row in data1:
	print(row)

data.close()
