#!/usr/bin/env python

import array
import glob
import sys
import zipfile

def arrayify_one_string(s):
    a = array.array('d')
    a.fromstring(s)
    a.byteswap()
    return a

def arrayify_one_zip(filename):
    z = zipfile.ZipFile(filename)
    s = z.read(z.namelist()[0])
    z.close()
    return arrayify_one_string(s)

def read_all(prefix):
    data = {}
    lengths = set()
    filelist = glob.glob('%s*.Dev*' % prefix)
    filelist.extend(glob.glob('%s*.Time*' % prefix))
    for f in filelist:
        device = f.split('.')[1]
        data[device] = arrayify_one_zip(f)
        lengths.add(len(data[device]))
    if len(lengths) > 1:
        raise ValueError, 'data length mismatch'
    return data

def schema_of_data(d, f=None):
    l = []
    l.append('DROP TABLE IF EXISTS sunny_webbox_flat_import;\n')
    l.append('CREATE TABLE sunny_webbox_flat_import (\n')
    l.append('  time TIMESTAMP WITH TIME ZONE PRIMARY KEY,\n')
    for k in [x for x in sorted(d) if x != 'Time']:
        l.append('  %s DOUBLE PRECISION' % k)
        l.append(',\n')
    l.pop()
    l.append('\n);')
    return ''.join(l)

def sql_of_data(d, f=None):
    lines = []
    device_data = []
    line = ['time']
    for device in [x for x in sorted(d) if x != 'Time']:
        device_data.append(d[device])
        line.append(device)
    columns = ', '.join(line)
    n_devices = len(device_data)

    i = 0
    for i in xrange(len(d['Time'])):
        line = []
        t_ms = d['Time'][i]
        line.append("'1970-01-01T00:00:00 +0000'::TIMESTAMP WITH TIME ZONE + '%.3f seconds'::INTERVAL" % (t_ms/1000))
        for j in xrange(n_devices):
            datum = str(device_data[j][i])
            if datum == 'nan':
                line.append('NULL')
            else:
                line.append(datum)
        query = '''INSERT INTO sunny_webbox_flat_import (%s) VALUES (%s);''' % (columns, ', '.join(line))

        # lines.append(query)
        print query

        i += 1

    # return lines

if __name__ == '__main__':
    try:
        d = read_all(prefix=sys.argv[1])
    except IndexError:
        d = read_all(prefix='')
    print schema_of_data(d)
    sql_of_data(d)
