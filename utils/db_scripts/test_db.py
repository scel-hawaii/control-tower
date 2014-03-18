import pprint
import psycopg2 
import csv
def main():
	conn_string = "dbname='kenny'"
	# print the connection string we will use to connect
	print "Connecting to database\n	->%s" % (conn_string)
 
	# get a connection, if a connect cannot be made an exception will be raised here
	conn = psycopg2.connect(conn_string)
 
	# conn.cursor will return a cursor object, you can use this cursor to perform queries
	cursor = conn.cursor()

	cursor.execute('SELECT db_time, uptime_ms FROM outdoor_env;')
	with open('books.csv', 'wb') as csvfile:
		csvwriter = csv.writer(csvfile,delimiter=',',quotechar='|', quoting=csv.QUOTE_MINIMAL)
		csvwriter.writerow(['db_time, uptime_ms'])
		for record in cursor:
			csvwriter.writerow(record) 
 
	# retrieve the records from the database
	records = cursor.fetchall()
	print records
	for item in records:
		print type(item[0])
		print item[0]

	cursor.execute("SELECT * FROM outdoor_env WHERE address=151")
	records = cursor.fetchone()
	pprint.pprint(records)

 
	# print out the records using pretty print
	# note that the NAMES of the columns are not shown, instead just indexes.
	# for most people this isn't very useful so we'll show you how to return
	# columns as a dictionary (hash) in the next example.
 
if __name__ == "__main__":
	main()
