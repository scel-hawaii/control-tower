

require 'pg'
@conn = PGconn.open(:dbname => 'kenny')
@res  = @conn.exec('SELECT DISTINCT address FROM outdoor_env')
@box_addr =[]

# Fetch the list of weatherbox addresses from the DB
def get_weatherbox_addresses
  puts "Getting weatherbox addresses..." 
  @res.each do |item|
    @box_addr.push(item['address'])
  end
  puts "Finished getting weatherbox addresses." 
end

# Create the CSV files from the addresses 
def create_csv_from_addresses(dir)
  puts "Creating CSV files from address..."
  @box_addr.each do |addr|
    ## Export the entire raw database for each node id
    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC) To #{dir}#{addr}-data.csv With CSV header\'"
    `#{command}`
  end
  puts "Finished getting CSV files from addresses."
end

# Create 3-day CSVs from the DB
def create_threeday_csv(dir)
  puts "Creating threeday_csv files..."
  @box_addr.each do |addr|
    ## Same as above, but with a limit of 3 days. 
    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC LIMIT 129600) To #{dir}#{addr}-data-threeday.csv With CSV header\'"
    `#{command}`
  end
  puts "Finished creating threeday_csv files."
end

# Sync the files up..
def rsync_files(dir)
  puts `rsync -raz --delete  --progress -h #{dir} webfaction:~/homepage/scel/#{dir}`
end

# Create create a graph
def create_graph(dir, input_file, output_file)
  `./graph_box.sh #{dir}#{input_file}.csv #{"data/plots/"}#{output_file}.png`
end

def create_all_graphs(dir)
  @box_addr.each do |addr|
    create_graph(dir, "#{addr}-data-threeday", "#{addr}-plot-threeday")
    create_graph(dir, "#{addr}-data", "#{addr}-plot")
  end
end


while true
  get_weatherbox_addresses()
  create_csv_from_addresses("data/full/")
  create_threeday_csv("data/threeday/")
  create_all_graphs("data/threeday/")
  create_all_graphs("data/full/")
  rsync_files("data/")
  sleep 600
end


