--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: heartbeat; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE heartbeat (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms INTEGER,
    batt_mv INTEGER,
);


--
-- Name: apple; Type: TABLE; Schema: public; Owner: control_tower; Tablespace: 
--

CREATE TABLE apple (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms INTEGER,
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

CREATE TABLE cranberry (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms INTEGER,
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

CREATE TABLE dragonfruit (
    time_received TIMESTAMP NOT NULL,
    schema INTEGER,
    node_addr INTEGER,
    uptime_ms INTEGER,
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

