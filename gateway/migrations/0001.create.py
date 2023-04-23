from yoyo import step

steps = [
   # The heartbeat table was created prior to the migrations, so
   # to get this to run in production, we need to check if the table
   # already exists or not
   step(
       """
        CREATE TABLE heartbeat (
            time_received TIMESTAMP WITH TIME ZONE NOT NULL,
            schema INTEGER,
            node_addr INTEGER,
            uptime_ms BIGINT,
            batt_mv INTEGER
        );
        """
       ),
   step(
       """
       CREATE TABLE weather_node_data (
            time_received TIMESTAMP NOT NULL,
            node_addr INTEGER,
            overflow_num INTEGER,
            uptime_ms BIGINT,
            batt_mv INTEGER,
            panel_mv INTEGER,
            pressure_pascals INTEGER,
            temperature_kelvin INTEGER,
            humidity_percent INTEGER,
            irradiance_watts_per_square_meter BIGINT
        )
       """
   )
]
