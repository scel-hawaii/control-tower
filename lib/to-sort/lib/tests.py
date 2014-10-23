#!/usr/bin/env python

import unittest

import decode

class TestDecode(unittest.TestCase):
    def test_json_decode_correct(self):
        # jacked from 396 paper
        rf_data = '{"address": 544, "uptime_ms": 242934985, "bmp085_temp_decic": 473, "bmp085_press_pa": 100957, "batt_mv": 3812, "panel_mv": 4750, "apogee_mv": 46, "apogee_w_m2": 230}'
        expected_series = \
            [{'time_offset_s': 0,
              'values': {'address': 544, 'uptime_ms': 242934985,
                         'bmp085_temp_decic': 473, 'bmp085_press_pa': 100957,
                         'batt_mv': 3812, 'panel_mv': 4750,
                         'apogee_mv': 46, 'apogee_w_m2': 230}}]
        self.assertEqual(decode.decode(rf_data), expected_series)

    def test_json_reject_junk(self):
        self.assertRaises(ValueError, decode.decode, 
                          '{"this": isn\'t quite right}')
        # this is actually an "unknown schema" 32123
        self.assertRaises(ValueError, decode.decode,
                          '{}')
        self.assertRaises(ValueError, decode.decode,
                          '{"address": 12345')

    def test_reject_length_mismatch(self):
        self.assertRaises(Exception, decode.decode, '\x00\x00')

    def test_reject_unknown_schema(self):
        # there shouldn't be a schema 65535
        self.assertRaises(ValueError, decode.decode, '\xff\xff')

    def test_create_query(self):
        series_element = {'time_offset_s': -12,
                          'values': {'address': 12345,
                                     'uptime_ms': 15000}}
        self.assertEqual(decode.create_query(series_element), 
                         "INSERT INTO outdoor_env (db_time, address, uptime_ms) VALUES (now() + '-12 seconds'::interval, %(address)s, %(uptime_ms)s)")

    def test_create_query_reject_unreasonable_columns(self):
        series_element = {'time_offset_s': -12,
                          'values': {';--address': 12345,
                                     'uptime_ms': 15000}}
        self.assertRaises(ValueError, decode.create_query, series_element)


if __name__ == '__main__':
    unittest.main()
