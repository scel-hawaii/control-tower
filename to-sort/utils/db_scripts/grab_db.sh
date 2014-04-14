#!/bin/bash
psql -c 'SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL) ORDER BY db_time DESC'

