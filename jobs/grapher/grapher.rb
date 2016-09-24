# ===========================================
#
# A simple script to generate the graphs and
# sync them with a website.
#
# ===========================================

require 'pg'
require 'fileutils'

# Grab a csv file
def csv_dump(addr, root_dir)
  filename = "full.csv"
  dump_dir = File.join(root_dir)
  filepath = File.join(dump_dir, filename)

  cmd = "psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC) To #{filepath} With CSV header\'"
  run_command(cmd)
end

def csv_dump_threeday(addr, root_dir)
  filename = "threeday.csv"
  dump_dir = File.join(root_dir)
  filepath = File.join(dump_dir, filename)

  command = " psql -c '\\copy (SELECT * FROM outdoor_env WHERE (apogee_w_m2 IS NOT NULL AND address=#{addr}) ORDER BY db_time DESC LIMIT 14400) To
                #{filepath} With CSV header\'"
  run_command(command)
end

# Create create a graph
def create_graph(box_addr)
  data_path = File.join("data", box_addr, "full.csv")
  plot_path = File.join("data", box_addr, "full.png")

  command = "./graph_box.sh #{data_path} #{plot_path}"
  run_command(command)

  data_path = File.join("data", box_addr, "threeday.csv")
  plot_path = File.join("data", box_addr, "threeday.png")

  command = "./graph_box.sh #{data_path} #{plot_path}"
  run_command(command)
end

# Run a command
# TODO: Explore a better way to run commands (we can't pipe commands back now)
def run_command(command)
  `#{command}`
end

puts "START sync at: #{Time.new.inspect}"

# Create the connection
db = PGconn.open(:dbname => 'control_tower')
result = db.exec('SELECT DISTINCT address FROM outdoor_env')

box_addrs = []
result.each do |item|
  box_addrs.push(item['address'])
end
puts "Fetched node addresses"
puts box_addrs


# Double check that the file directory is there, if it's not there, create it.
puts "Creating data directory"
data_dir = File.join("./data")
data_dir = File.join(Dir.pwd(), data_dir)
root_dir = Dir.pwd()

if not File.directory?(data_dir)
  Dir.mkdir(data_dir)
end

box_addrs.each do |addr|
  puts "Graphing box #{addr}"
  dir = File.join("./data", addr)
  if not File.directory?(dir)
    Dir.mkdir(dir)
  end
  csv_dump(addr, dir)
  csv_dump_threeday(addr, dir)
  create_graph(addr)
  puts "Done Graphing box #{addr}"
end

puts "END sync at: #{Time.new.inspect}"
