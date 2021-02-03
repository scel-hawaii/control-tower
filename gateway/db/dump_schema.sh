#!/bin/bash
# Dump the current schema from the database
HOST=192.168.1.98
pg_dump -h $HOST --schema-only -d control_tower > control_tower_db.sql
