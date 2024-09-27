CREATE TABLE heartbeat (
    time_received TIMESTAMP WITH TIME ZONE NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER
);

CREATE TABLE apple (
    time_received TIMESTAMP WITH TIME ZONE NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    press_pa INTEGER,
    temp_c INTEGER,
    humidity_centi_pct INTEGER,
    apogee_w_m2 FLOAT
);

CREATE TABLE cranberry (
    time_received TIMESTAMP WITH TIME ZONE NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    apogee_w_m2 FLOAT,
    temp_cK INTEGER,
    humidity_pct INTEGER,
    press_pa INTEGER
);

CREATE TABLE dragonfruit (
    time_received TIMESTAMP WITH TIME ZONE NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    apogee_w_m2 FLOAT,
    temp_cK INTEGER,
    humidity_pct INTEGER,
    press_pa INTEGER
);
