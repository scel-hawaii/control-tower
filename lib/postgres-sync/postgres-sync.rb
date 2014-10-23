# 
# pull from the website 

class PostgresSyncer

  def initialize()
    @data_url = "http://kennyluong.com/scel/data/full-data/"
    @data_dir = "full-data"
    @sync_period = 60*15 
  end

  def sync_files()
    puts `rsync -raz --delete  --progress -h webfaction:~/homepage/scel/data/full-data .`
  end

  # Returns the current files in the directory
  def get_csv_filenames(dir)
    return Dir.entries(dir).select{ |f| !File.directory? f}
  end

  # import each file into postgres
  def postgres_import(dir, filenames)
    filenames.each do |file|
      command = "psql -c \"\\copy outdoor_env FROM \'#{File.join(dir, file)}\' DELIMITER ',' CSV HEADER\""
      puts "Running command: #{command}"
      `#{command}`
    end
  end


  # main routine
  def main_routine()
    dir_name = "full-data"
    sync_files()
    filenames = get_csv_filenames(dir_name)
    while true do
      puts "Start postgres sync at #{Time.new.inspect}"
      sync_files()
      postgres_import(dir_name, filenames)
      puts "End postgres sync at #{Time.new.inspect}"
      sleep(@sync_period)
    end

  end

end

syncer = PostgresSyncer.new
syncer.main_routine()

