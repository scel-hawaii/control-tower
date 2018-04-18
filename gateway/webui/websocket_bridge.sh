#!/bin/bash

cd ../test
../webui/websocketd --port 8001 python ../src/sub.py
