

require 'pg'
@conn = PGconn.open(:dbname => 'kenny')
@res  = @conn.exec('SELECT DISTINCT address FROM outdoor_env')
@box_addr =[]

def get_weatherbox_addresses
  @res.each do |item|
    @box_addr.push(item['address'])
  end
end

def create_csv_from_addresses(dir)
  @box_addr.each do |addr|
    ## Export the entire raw database for each node id
    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC) To #{dir}#{addr}-data.csv With CSV header\'"
    `#{command}`
  end
end

def create_threeday_csv(dir)
  @box_addr.each do |addr|
    ## Same as above, but with a limit of 3 days. 
    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC LIMIT 129600) To #{dir}#{addr}-data-threeday.csv With CSV header\'"
    `#{command}`
  end
end

def rsync_files(dir)
  puts `rsync -raz --delete  --progress -h #{dir} webfaction:~/homepage/scel/#{dir}`
end

def create_graph(dir, input_file, output_file)
  `./graph_box.sh #{dir}#{input_file}.csv #{"data/plots/"}#{output_file}.png`
end

def create_all_graphs(dir)
  @box_addr.each do |addr|
    create_graph(dir, "#{addr}-data-threeday", "#{addr}-plot-threeday")
  end
end


while true
  get_weatherbox_addresses()
  create_csv_from_addresses("data/full/")
  create_threeday_csv("data/threeday/")
  create_all_graphs("data/threeday/")
  rsync_files("data/")
  sleep 600
end


