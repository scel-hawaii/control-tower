# Fetch seed data
echo 'Fetching dataset...'
wget http://static.scel-hawaii.org/data/outdoor_env.csv.zip
unzip outdoor_env.csv.zip
echo 'Done fetching dataset.'

# Missing step: import the database schema

# Import to docker instance
# psql --host=localhost -p 8083 -U postgres -W secure_password -c "\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER"

# Import to machine db

echo 'Importing dataset into database...'
psql -c "\\copy outdoor_env FROM 'outdoor_env.csv' CSV HEADER"
echo 'Done importing dataset.'
