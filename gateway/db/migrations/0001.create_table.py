from yoyo import step

steps = [
	step(
		#Change table name, and adjust the columns.
		"""
		CREATE TABLE placeholder_name (
			time_received TIMESTAMP NOT NULL
			schema INTEGER,
			node_addr INTEGER,
			uptime_ms BIGINT,
			batt_mv INTEGER
		)
		"""
	)
]