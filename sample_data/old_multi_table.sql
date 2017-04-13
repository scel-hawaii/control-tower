--
-- PostgreSQL database dump
--

--
-- Name: heartbeat; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE heartbeat_old (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER
);


--
-- Name: apple; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE apple_old (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    press_pa INTEGER,
    temp_c INTEGER,
    humidity_centi_pct INTEGER,
    apogee_w_m2 INTEGER    
);


--
-- Name: cranberry; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE cranberry_old (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    apogee_w_m2 INTEGER,
    temp_cK INTEGER,
    humidity_pct INTEGER,
    press_pa INTEGER    
);


--
-- Name: dragonfruit; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE dragonfruit_old (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms BIGINT,
    batt_mv INTEGER,
    panel_mv INTEGER,
    apogee_sp215 INTEGER,
    temp_cK INTEGER,
    humidity_pct INTEGER,
    press_pa INTEGER    
);



--
-- PostgreSQL database dump complete
--

