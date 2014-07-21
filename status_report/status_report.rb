# Status report of the current REIS services

require 'pg'
require 'active_support/all'
require 'pp'

def execute_database(command)
  conn = PGconn.open(:host=> 'localhost', :dbname => 'kenny', :user=>'kenny',  :password=>'tran1992')
  res =  conn.exec(command)
  output = [];
  res.each do |row|
    output << row
  end
  conn.close()
  return output 
end


def get_weatherbox_addr()
  q = 'SELECT DISTINCT address FROM outdoor_env'
  res  = execute_database(q)
  output = []
  res.each do |row|
    output << row["address"]
  end
  return output
end

def get_latest_sample(address)
  q = "SELECT * FROM outdoor_env WHERE address=#{address} ORDER BY db_time DESC LIMIT 1"
  res  = execute_database(q)
  output = [];
  res.each do |row|
    output << row
  end
  return output
end

def get_latest_sample_time(address)
  sample = get_latest_sample(address)
  return Time.parse(sample[0]["db_time"])
end

=begin
latest_time =  res[0]["db_time"]
time_box = Time.parse(latest_time)
time_now = Time.now

puts time_box
puts time_now

(time_now - time_box).to_i

=end

box_addr =  get_weatherbox_addr
puts box_addr
box_addr.each do |box|
  puts get_latest_sample_time(box)
end
