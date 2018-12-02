#!/bin/bash

socat -d -d pty,link=./ttyIN,raw,echo=0 pty,link=./ttyOUT,raw,echo=0
./gateway
