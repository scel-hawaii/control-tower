#!/bin/bash
socat -d -d pty,link=./ttyV1,raw,echo=0 pty,link=./ttyV2,raw,echo=0
