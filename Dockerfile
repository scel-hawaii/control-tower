FROM debian

# Start Installation

# Clean and update or else we may get connection errors
RUN apt-get clean
RUN apt-get update

RUN apt-get -y install python python-dev python-pip \
    postgresql libpq-dev make \
    wget git gzip \
    nodejs nodejs-legacy build-essential npm \
    sudo

RUN git clone https://github.com/scel-hawaii/control-tower.git
RUN cd control-tower/setup/ && bash setup_server_req.sh
RUN cd control-tower/setup/ && bash setup_python_reqs.sh

RUN /etc/init.d/postgresql start &&\
    cd control-tower/db &&\
    bash setup_postgres_user.sh

RUN npm install -g npm

WORKDIR /control-tower/api
RUN npm install

# Seed Database
USER postgres
WORKDIR /var/lib/postgresql
RUN wget http://static.scel-hawaii.org/data/outdoor_env_small.csv.gz
RUN gzip -d outdoor_env_small.csv.gz
RUN chmod 775 outdoor_env_small.csv

USER postgres
RUN /etc/init.d/postgresql start &&\
    sleep 1 &&\
    psql -d control_tower -c "\\copy outdoor_env FROM 'outdoor_env_small.csv' CSV HEADER"

# End Installation

EXPOSE 16906

WORKDIR /control-tower/api
CMD /etc/init.d/postgresql start && npm start
