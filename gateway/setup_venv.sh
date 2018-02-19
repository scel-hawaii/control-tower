#!/bin/bash
pip install virtualenv
python2 -m virtualenv env
source env/bin/activate
pip install -r requirements.txt
