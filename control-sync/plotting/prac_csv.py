import csv
import numpy

x = []

with open('215_data.csv', 'r') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		x.append(row)
