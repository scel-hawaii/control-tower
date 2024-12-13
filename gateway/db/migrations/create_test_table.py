from yoyo import step
 
steps = [
    step(
        """
        CREATE TABLE placeholder_name (
            time_received TIMESTAMP NOT NULL,  -- Added missing comma here
            schema INTEGER,
            node_addr INTEGER,
            uptime_ms BIGINT,
            batt_mv INTEGER
        )
        """,
        "DROP TABLE placeholder_name"  # Added rollback statement
    )
]
