# ===========================================
#
# A simple script to generate the graphs and 
# sync them with a website.
#
# ===========================================
require 'pg'
require 'fileutils'


class ControlSyncer

  def initialize()
    @conn = PGconn.open(:dbname => 'kenny')
    @res  = @conn.exec('SELECT DISTINCT address FROM outdoor_env')
    @data_dir = File.join("data")
    @data_dir = File.join(Dir.pwd(), @data_dir)
    @root_dir = Dir.pwd()

    @box_addr =[]

    get_weatherbox_addresses()
    init_data_dir()
  end

  def init_data_dir()
    if not File.directory?(@data_dir)
      Dir.mkdir(@data_dir)
    end
  end

  def init_dir(dir)
    if not File.directory?(dir)
      Dir.mkdir(dir)
    end
  end

  # Grab a csv file 
  def csv_dump(addr, root_dir)
    filename = "#{addr}-data.csv"
    dump_dir = File.join(root_dir, "full-data")
    filepath = File.join(dump_dir, filename)


    init_dir(dump_dir)
    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC) To #{filepath} With CSV header\'"
    run_command(command)
  end

  def csv_dump_threeday(addr, root_dir)
    filename = "#{addr}-threeday-data.csv"
    dump_dir = File.join(root_dir, "threeday-data")
    filepath = File.join(dump_dir, filename)

    init_dir(dump_dir)

    command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC LIMIT 14400) To 
                  #{filepath} With CSV header\'"
    run_command(command)
  end

  # Run a command
  # TODO: Explore a better way to run commands (we can't pipe commands back now)
  def run_command(command)
    `#{command}`
  end

  # Fetch the list of weatherbox addresses from the DB
  def get_weatherbox_addresses
    @res.each do |item|
      @box_addr.push(item['address'])
    end
  end

  # Do a dump of all our csv files
  def csv_dump_all()
    @box_addr.each do |addr|
      csv_dump(addr, @data_dir)
    end
  end

  # Do a dump of all our csv files (limiting to three days of datapoints)
  def csv_dump_all_threeday()
    @box_addr.each do |addr|
      csv_dump_threeday(addr, @data_dir)
    end
  end

  # Sync the files up..
  def rsync_files()
    puts `rsync -raz --progress -h #{@data_dir} webfaction:~/webapps/scel_application/`
  end

  # Create create a graph
  def create_graph(data_path, plot_path)
    command = "./graph_box.sh #{data_path} #{plot_path}"
    run_command(command)
  end

  def create_all_graphs()
    csv_dump_all()
    csv_dump_all_threeday()
    print @root_dir
    data_folder_threeday = File.join(@data_dir, "threeday-data")
    plot_folder_threeday = File.join(@data_dir, "threeday-plot")
    init_dir(data_folder_threeday)
    init_dir(plot_folder_threeday)

    data_folder = File.join(@data_dir, "full-data")
    plot_folder = File.join(@data_dir, "full-plot")
    init_dir(data_folder)
    init_dir(plot_folder)
    @box_addr.each do |addr|
      data_path_threeday = File.join(data_folder_threeday, addr + "-threeday-data.csv")
      plot_path_threeday = File.join(plot_folder_threeday, addr + "-threeday-plot.png")
      data_path = File.join(data_folder, addr + "-data.csv")
      plot_path = File.join(plot_folder, addr + "-plot.png")
      create_graph(data_path, plot_path)
      create_graph(data_path_threeday, plot_path_threeday)
      # create_graph(dir, "#{addr}-data", "#{addr}-plot")
    end
  end

end

# Dump and sync every 15 minutes
sync_period = 60*15
sync_number = 0;

while true do
  puts "START sync #{sync_number} at: #{Time.new.inspect}"
  syncer = ControlSyncer.new()
  syncer.csv_dump_all()
  syncer.csv_dump_all_threeday()
  syncer.create_all_graphs()
  syncer.rsync_files()
  puts "END sync #{sync_number} at: #{Time.new.inspect}"
  sync_number =  sync_number + 1
  sleep(sync_period)
end
