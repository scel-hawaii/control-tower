# Status report of the current REIS services

require 'pg'
require 'active_support/all'
require 'pp'

class SensorReport

  def initialize()
  end


  def execute_database(command)
    conn = PGconn.open(:host=> 'localhost', :dbname => 'control_tower', :user=>'control_tower',  :password=>'password')
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

  def get_number_samples(address)
    q = "SELECT COUNT(*) FROM outdoor_env WHERE (uptime_ms IS NOT NULL AND address=#{address})"
    res  = execute_database(q)
    return res[0]["count"]
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

  def check_boxes()
    box_addrs =  get_weatherbox_addr
    puts "Box \t | Packets  \t | Last Time Recv \t\t | Min Since\t | Status \t |"
    puts "--------------------------------------------------------------------------------------------\n"
    box_addrs.each do |box|
      num_packets = get_number_samples(box)
      current_time = Time.now()
      last_box_time = get_latest_sample_time(box)
      time_difference = current_time - last_box_time
      if(time_difference < 3*60)
        status = "GOOD"
      else
        status = "BAD"
      end
      puts "#{box} \t | #{num_packets}  \t | #{last_box_time} \t | #{(time_difference/60).round(2)} \t |  #{status} \t |"
    end
  end


  def print_splash()
    puts "===================================================="
    puts "SCEL Weatherbox Status Report Script" 
    puts "Script run date: #{Time.now}"
    puts "===================================================="
  end

end

reporter = SensorReport.new
reporter.print_splash
reporter.check_boxes
