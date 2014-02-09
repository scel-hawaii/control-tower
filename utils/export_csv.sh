echo "==================================="
echo "Database table to CSV export script"
echo "==================================="
echo 


echo "Please enter the table name:"
read table_name

echo "Please enter the file path-name to save to:"
read file_path


echo "Are you sure this is correct?? (Y/N)"
echo "Table name: $table_name"
echo "file_path: $table_name"

read user_confirm

psql -c "\COPY $table_name TO '/tmp/products_199.csv' DELIMITER ',' CSV HEADER;"
