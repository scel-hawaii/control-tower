# Script to setup a postgres docker container
docker pull postgres

# Default port for postgres is 5432
docker run --name some-postgres -e POSTGRES_PASSWORD=secure_password -p 8083:5432 -d postgres
