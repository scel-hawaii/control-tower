#!/bin/bash
pip install virtualenv --user
python2 -m virtualenv env
source env/bin/activate
pip install -r requirements.txt
