FROM ubuntu

# Clean and update or else we may get connection errors
RUN apt-get clean
RUN apt-get update
RUN apt-get install -y postgresql
RUN apt-get install -y wget
RUN apt-get install -y sudo

ADD . db/

RUN /etc/init.d/postgresql start &&\
    cd db/ &&\
    bash setup_postgres_user.sh

# Seed Database
USER postgres
WORKDIR /var/lib/postgresql
RUN wget http://static.scel-hawaii.org/data/outdoor_env_small.csv.gz
RUN gzip -d outdoor_env_small.csv.gz
RUN chmod 777 outdoor_env_small.csv

USER postgres
RUN /etc/init.d/postgresql start &&\
    sleep 10 &&\
    psql -d control_tower -c "\\copy outdoor_env FROM 'outdoor_env_small.csv' CSV HEADER"

# Adjust PostgreSQL configuration so that remote connections to the
# database are possible.
RUN echo "host all  all    0.0.0.0/0  trust" >> /etc/postgresql/9.5/main/pg_hba.conf

# And add ``listen_addresses`` to ``/etc/postgresql/9.3/main/postgresql.conf``
RUN echo "listen_addresses='*'" >> /etc/postgresql/9.5/main/postgresql.conf

# Add VOLUMEs to allow backup of config, logs and databases
# VOLUME  ["/etc/postgresql", "/var/log/postgresql", "/var/lib/postgresql"]

# End Installation
EXPOSE 5432
CMD ["/usr/lib/postgresql/9.5/bin/postgres", "-D", "/var/lib/postgresql/9.5/main", "-c", "config_file=/etc/postgresql/9.5/main/postgresql.conf"]
# CMD ["postgres"]
