#!/bin/bash
# A simple script that displays the results from the outdoor_env 
# table. 

psql -c "SELECT * FROM outdoor_env;"
