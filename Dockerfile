# Simple dockerfile for scel data REST API
#
# build with: docker build -t scel_server
# run with: docker run -p 16906:16906 scel_server
#

FROM ubuntu:latest

# Dependencies
RUN apt-get update 
RUN apt-get install -y postgresql screen make git python postgresql-server-dev-9.3 curl
RUN curl -sL https://deb.nodesource.com/setup | sudo bash -
RUN apt-get install -y nodejs build-essential


USER root
# Copy source application
COPY . /src

WORKDIR /src
RUN /etc/init.d/postgresql start && /src/setup_postgres_user.sh && sudo -u control_tower /src/import_db_to_csv.sh

USER root

RUN npm install
# Expose and run script

EXPOSE 16906
CMD ["/bin/bash", "run_server"]


