from yoyo import step

steps = [
   step(
       """
       CREATE TABLE weather_node_data (
            time_received INTEGER,
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
