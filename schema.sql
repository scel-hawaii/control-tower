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
-- Name: raaargh; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE raaargh (
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
-- Name: min_max_avg; Type: VIEW; Schema: public; Owner: -
--

CREATE VIEW min_max_avg AS
    SELECT raaargh.address, date_trunc('minute'::text, raaargh.db_time) AS db_time_min, count(*) AS n, min(raaargh.bmp085_temp_decic) AS min_bmp085_temp_decic, (avg(raaargh.bmp085_temp_decic))::integer AS avg_bmp085_temp_decic, max(raaargh.bmp085_temp_decic) AS max_bmp085_temp_decic, min(raaargh.bmp085_press_pa) AS min_bmp085_press_pa, (avg(raaargh.bmp085_press_pa))::integer AS avg_bmp085_press_pa, max(raaargh.bmp085_press_pa) AS max_bmp085_press_pa, min(raaargh.batt_mv) AS min_batt_mv, (avg(raaargh.batt_mv))::integer AS avg_batt_mv, max(raaargh.batt_mv) AS max_batt_mv, min(raaargh.panel_mv) AS min_panel_mv, (avg(raaargh.panel_mv))::integer AS avg_panel_mv, max(raaargh.panel_mv) AS max_panel_mv, min(raaargh.uptime_ms) AS min_uptime_ms, (avg(raaargh.uptime_ms))::integer AS avg_uptime_ms, max(raaargh.uptime_ms) AS max_uptime_ms, min(raaargh.apogee_w_m2) AS min_apogee_w_m2, (avg(raaargh.apogee_w_m2))::integer AS avg_apogee_w_m2, max(raaargh.apogee_w_m2) AS max_apogee_w_m2 FROM raaargh GROUP BY raaargh.address, date_trunc('minute'::text, raaargh.db_time);


--
-- Name: min_max_avg_5min; Type: VIEW; Schema: public; Owner: -
--

CREATE VIEW min_max_avg_5min AS
    SELECT raaargh.address, round_time_5min(raaargh.db_time) AS db_time_5min, count(*) AS n, min(raaargh.bmp085_temp_decic) AS min_bmp085_temp_decic, (avg(raaargh.bmp085_temp_decic))::integer AS avg_bmp085_temp_decic, max(raaargh.bmp085_temp_decic) AS max_bmp085_temp_decic, min(raaargh.bmp085_press_pa) AS min_bmp085_press_pa, (avg(raaargh.bmp085_press_pa))::integer AS avg_bmp085_press_pa, max(raaargh.bmp085_press_pa) AS max_bmp085_press_pa, min(raaargh.batt_mv) AS min_batt_mv, (avg(raaargh.batt_mv))::integer AS avg_batt_mv, max(raaargh.batt_mv) AS max_batt_mv, min(raaargh.panel_mv) AS min_panel_mv, (avg(raaargh.panel_mv))::integer AS avg_panel_mv, max(raaargh.panel_mv) AS max_panel_mv, min(raaargh.uptime_ms) AS min_uptime_ms, (avg(raaargh.uptime_ms))::integer AS avg_uptime_ms, max(raaargh.uptime_ms) AS max_uptime_ms, min(raaargh.apogee_w_m2) AS min_apogee_w_m2, (avg(raaargh.apogee_w_m2))::integer AS avg_apogee_w_m2, max(raaargh.apogee_w_m2) AS max_apogee_w_m2 FROM raaargh GROUP BY raaargh.address, round_time_5min(raaargh.db_time);


--
-- Name: raaargh_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY raaargh
    ADD CONSTRAINT raaargh_pkey PRIMARY KEY (address, db_time);


--
-- Name: raaargh_address_idx; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX raaargh_address_idx ON raaargh USING btree (address);


--
-- Name: raaargh_date_trunc_idx; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX raaargh_date_trunc_idx ON raaargh USING btree (date_trunc('hour'::text, timezone('HST'::text, db_time)));


--
-- Name: raaargh_db_time_idx; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX raaargh_db_time_idx ON raaargh USING btree (db_time);


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

