# Fetch seed data
wget http://static.scel-hawaii.org/data/outdoor_env.csv.zip
unzip outdoor_env.csv.zip

# Missing step: import the database schema

# Import to docker instance
# psql --host=localhost -p 8083 -U postgres -W secure_password -c "\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER"

# Import to machine db
psql -c "\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER"
