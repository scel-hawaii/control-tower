task :default do
  system("docker build -t kenny/scel .")
  system("docker run -t -i -p 16906:16906 kenny/scel")
end
