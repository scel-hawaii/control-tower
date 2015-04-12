# Simple dockerfile for scel data REST API
#
#
#

FROM ubuntu:latest

RUN apt-get update 
RUN apt-get install -y postgresql screen make vim tig git


# Setup node, npm
RUN apt-get install -y curl
RUN curl -sL https://deb.nodesource.com/setup | sudo bash -
RUN apt-get install -y nodejs build-essential

USER postgres
RUN /etc/init.d/postgresql start && \ 
psql --command "CREATE USER control_tower WITH PASSWORD 'renewable123'" && \ 
psql --command "CREATE DATABASE control_tower" && \
psql --command "GRANT ALL PRIVILEGES ON DATABASE control_tower to control_tower" && \
psql --command "\list+" 

USER root

# Copy source application
COPY . /src

# Expose and run script
EXPOSE 16906
CMD ["node", "/src/server.js"]

