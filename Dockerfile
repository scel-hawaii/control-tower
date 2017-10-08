FROM ubuntu

# Start Installation

# Clean and update or else we may get connection errors
RUN apt-get clean
RUN apt-get update

RUN apt-get -y install python python-dev python-pip \
    postgresql libpq-dev make \
    wget git gzip \
    build-essential npm \
    sudo curl

# RUN curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
RUN curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
RUN sudo apt-get install -y nodejs

# Check if npm and node are installed correctly
RUN npm --version
RUN nodejs --version

RUN npm update -g

ADD . control-tower/

RUN cd control-tower/setup/ && bash setup_python_reqs.sh

RUN /etc/init.d/postgresql start &&\
    cd control-tower/db &&\
    bash setup_postgres_user.sh


# WORKDIR /control-tower/api
# RUN npm install

# Seed Database
USER postgres
WORKDIR /var/lib/postgresql
RUN wget http://static.scel-hawaii.org/data/outdoor_env_small.csv.gz
RUN gzip -d outdoor_env_small.csv.gz
RUN chmod 775 outdoor_env_small.csv

USER postgres
RUN /etc/init.d/postgresql start &&\
    sleep 3 &&\
    psql -d control_tower -c "\\copy outdoor_env FROM 'outdoor_env_small.csv' CSV HEADER"

# End Installation

EXPOSE 16906

WORKDIR /control-tower/api
CMD /etc/init.d/postgresql start && npm start
