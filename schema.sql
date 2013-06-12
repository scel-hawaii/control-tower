--
-- PostgreSQL database dump
--

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: -
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: round_time_5min(timestamp with time zone); Type: FUNCTION; Schema: public; Owner: -
--

CREATE FUNCTION round_time_5min(timestamp with time zone) RETURNS timestamp with time zone
    LANGUAGE sql
    AS $_$ select date_trunc('hour', $1) + '1 minute'::interval * 5 * round(date_part('minute', $1) / 5.0); $_$;


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: greenbox; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE greenbox (
    addr integer NOT NULL,
    db_time timestamp with time zone NOT NULL,
    up_ms integer,
    bmp_c integer,
    bmp_pa integer,
    sht_pct integer,
    ds20_c integer,
    tsl_m2 integer,
    solar_v integer,
    shunt_mv integer,
    solar_ma integer,
    batt_v integer,
    batt_mv integer,
    batt_ma integer
);


--
-- Name: outdoor_env; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE outdoor_env (
    address integer NOT NULL,
    db_time timestamp with time zone NOT NULL,
    uptime_ms integer,
    bmp085_temp_decic integer,
    bmp085_press_pa integer,
    batt_mv integer,
    panel_mv integer,
    apogee_mv integer,
    apogee_w_m2 integer
);


--
-- Name: outdoor_env_5min; Type: VIEW; Schema: public; Owner: -
--

CREATE VIEW outdoor_env_5min AS
    SELECT outdoor_env.address, round_time_5min(outdoor_env.db_time) AS db_time_5min, count(*) AS n, min(outdoor_env.bmp085_temp_decic) AS min_bmp085_temp_decic, (avg(outdoor_env.bmp085_temp_decic))::integer AS avg_bmp085_temp_decic, max(outdoor_env.bmp085_temp_decic) AS max_bmp085_temp_decic, min(outdoor_env.bmp085_press_pa) AS min_bmp085_press_pa, (avg(outdoor_env.bmp085_press_pa))::integer AS avg_bmp085_press_pa, max(outdoor_env.bmp085_press_pa) AS max_bmp085_press_pa, min(outdoor_env.batt_mv) AS min_batt_mv, (avg(outdoor_env.batt_mv))::integer AS avg_batt_mv, max(outdoor_env.batt_mv) AS max_batt_mv, min(outdoor_env.panel_mv) AS min_panel_mv, (avg(outdoor_env.panel_mv))::integer AS avg_panel_mv, max(outdoor_env.panel_mv) AS max_panel_mv, min(outdoor_env.uptime_ms) AS min_uptime_ms, (avg(outdoor_env.uptime_ms))::integer AS avg_uptime_ms, max(outdoor_env.uptime_ms) AS max_uptime_ms, min(outdoor_env.apogee_w_m2) AS min_apogee_w_m2, (avg(outdoor_env.apogee_w_m2))::integer AS avg_apogee_w_m2, max(outdoor_env.apogee_w_m2) AS max_apogee_w_m2 FROM outdoor_env GROUP BY outdoor_env.address, round_time_5min(outdoor_env.db_time) ORDER BY round_time_5min(outdoor_env.db_time);


--
-- Name: outdoor_env_binary_log; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE outdoor_env_binary_log (
    db_time timestamp with time zone NOT NULL,
    rf_data bytea
);


--
-- Name: outdoor_env_unrecognized; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE outdoor_env_unrecognized (
    db_time timestamp with time zone,
    rf_data bytea,
    exception character varying
);


--
-- Name: sunny_webbox_flat; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE sunny_webbox_flat (
    "time" timestamp with time zone NOT NULL,
    dev1exlsolirr double precision,
    dev1intsolirr double precision,
    dev1optm double precision,
    dev1tmpamb double precision,
    dev1tmpmdul double precision,
    dev1windvel double precision,
    dev2etotal double precision,
    dev2iac double precision,
    dev2ipv double precision,
    dev2pac double precision,
    dev2temperature double precision,
    dev2vac double precision,
    dev3etotal double precision,
    dev3iac double precision,
    dev3ipv double precision,
    dev3pac double precision,
    dev3temperature double precision,
    dev3vac double precision
);


--
-- Name: sunny_webbox_flat_import; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE sunny_webbox_flat_import (
    "time" timestamp with time zone NOT NULL,
    dev1exlsolirr double precision,
    dev1intsolirr double precision,
    dev1optm double precision,
    dev1tmpamb double precision,
    dev1tmpmdul double precision,
    dev1windvel double precision,
    dev2etotal double precision,
    dev2iac double precision,
    dev2ipv double precision,
    dev2pac double precision,
    dev2temperature double precision,
    dev2vac double precision,
    dev3etotal double precision,
    dev3iac double precision,
    dev3ipv double precision,
    dev3pac double precision,
    dev3temperature double precision,
    dev3vac double precision
);


--
-- Name: outdoor_env_binary_log_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY outdoor_env_binary_log
    ADD CONSTRAINT outdoor_env_binary_log_pkey PRIMARY KEY (db_time);


--
-- Name: outdoor_env_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY outdoor_env
    ADD CONSTRAINT outdoor_env_pkey PRIMARY KEY (address, db_time);


--
-- Name: sunny_webbox_flat_import_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY sunny_webbox_flat_import
    ADD CONSTRAINT sunny_webbox_flat_import_pkey PRIMARY KEY ("time");


--
-- Name: sunny_webbox_flat_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY sunny_webbox_flat
    ADD CONSTRAINT sunny_webbox_flat_pkey PRIMARY KEY ("time");


--
-- Name: outdoor_env_db_time_idx; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX outdoor_env_db_time_idx ON outdoor_env USING btree (db_time);


--
-- Name: public; Type: ACL; Schema: -; Owner: -
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

