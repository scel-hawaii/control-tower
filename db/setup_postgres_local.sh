## Sets up a control_tower databse on the local user
# TODO: Merge this with the normal script

function postgres_command(){
    sudo -u postgres psql -U postgres -d template1 -c "$1"
    exit_status=$?
    if [ $exit_status != 0 ]; then
        echo "ERROR PSQL FAILED WITH COMMAND: $1"
        # exit $exit_status
    fi
}

function import_db_dump(){
    sudo -u $USER psql -U $USER < "control_tower_db.sql"
}

postgres_command "CREATE DATABASE $USER"
postgres_command "GRANT ALL PRIVILEGES ON DATABASE $USER to $USER"
import_db_dump
