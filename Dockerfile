FROM debian
# sudo apt-get update
# sudo apt-get -y install git gzip zip
# git clone https://github.com/scel-hawaii/control-tower.git
# cd /home/vagrant/control-tower/setup/ && bash setup_server_req.sh
# cd /home/vagrant/control-tower/setup/ && bash setup_python_reqs.sh
# cd /home/vagrant/control-tower/db/ && bash setup_postgres_user.sh

# sudo su control_tower -c \
# 'cd /home/control_tower/ && git clone \
# https://github.com/scel-hawaii/control-tower.git'

# sudo su control_tower -c \
# 'cd /home/control_tower/control-tower/tasks/ &&
# bash seed.sh'

# Start Installation

RUN apt-get update
RUN apt-get -y install git gzip zip sudo
RUN apt-get -y install nodejs nodejs-legacy build-essential npm
RUN apt-get -y install python python-dev python-pip \
    postgresql libpq-dev make
RUN apt-get -y install wget

RUN git clone https://github.com/scel-hawaii/control-tower.git
RUN cd control-tower/setup/ && bash setup_server_req.sh
RUN cd control-tower/setup/ && bash setup_python_reqs.sh

RUN /etc/init.d/postgresql start &&\
    cd control-tower/db &&\
    bash setup_postgres_user.sh


RUN npm install -g npm

RUN cd control-tower/api && npm install

# Seed Database
RUN wget http://static.scel-hawaii.org/data/outdoor_env.csv.zip
RUN unzip outdoor_env.csv.zip
RUN chmod 775 outdoor_env.csv
RUN /etc/init.d/postgresql start &&\
    sudo su postgres -c "psql -d control_tower -c \"\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER\""
# End installation

# EXPOSE 16906

WORKDIR control-tower/api
CMD /etc/init.d/postgresql start && npm start
