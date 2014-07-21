from decode import PacketDecoder
import csv
import struct


def hex_string_to_dict(raw_string):
	hex_string = raw_string['rf_data']
	hex_string = hex_string[2:]

	# Convert the hex string to a struct
	hexdigits = [int(x, 16) for x in hex_string]
	data = ''.join(struct.pack('B', (high <<4) + low) 
		for high, low in zip(hexdigits[::2], hexdigits[1::2]))

	decoder = PacketDecoder()
	return decoder.decode(data)



header_keys = []
with open('outdoor_env_unrecognized.csv','rb') as csvfile:
	reader = csv.DictReader(csvfile, delimiter=',')
	for row in reader:
		item = hex_string_to_dict(row)[0]['values']
		header_keys = ['db_time']
		header_keys = header_keys + item.keys()
		print header_keys
		break


done = False

csvwritefile = open('outdoor_env_convert.csv','w+') 

writer = csv.DictWriter(csvwritefile, header_keys, delimiter=',')
with open('outdoor_env_unrecognized.csv','rb') as csvfile:
	reader = csv.DictReader(csvfile, delimiter=',')
	for row in reader:
		item = hex_string_to_dict(row)[0]['values']
		item['db_time'] = row['db_time']
		if (done == False):
			writer.writeheader()
		done = True
		writer.writerow(item)
		'''INSERT INTO outdoor_env (db_time, %s) VALUES (now() + '%s seconds'::interval, %s)''' % (column_names, v['time_offset_s'], placeholders)


