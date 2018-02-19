#!/bin/bash
( cd api/ && docker build -t scel-weatherbox-api . )
( cd db/ && docker build -t scel-weatherbox-db . )
