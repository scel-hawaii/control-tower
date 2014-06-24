import csv
import numpy

out = csv.reader(open("215_data.csv","rb"))

for row in out:
	print(row[2])
