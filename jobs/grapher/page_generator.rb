require 'erb'
require 'pg'

index_template =
  %{
<html>
<head>
</head>
<body>
    <h1>Sensor Nodes</h1>
    <table>
    <% box_addrs.each do |addr| %>
    <tr>
        <td><a href="/<%=addr%>"><%=addr%></a></td>
    </tr>
    <% end %>
    </table>
</body>
</html>
  }

box_template =
  %{
<html>
<head>
</head>

<body>
    <h1>Node <%=addr%></h1>
    <img src="/<%=addr%>/threeday.png">
    <img src="/<%=addr%>/full.png">
</body>

</html>
  }

# Create the connection
db = PGconn.open(:dbname => 'kluong')
result = db.exec('SELECT DISTINCT address FROM outdoor_env')

box_addrs = []
result.each do |item|
  box_addrs.push(item['address'])
end
puts "Fetched node addresses"
puts box_addrs


result = ERB.new(index_template).result(binding)

file = "data/index.html"
File.open(file, "w+") do |f|
        f.write(result)
end


box_addrs.each do |addr|
  result = ERB.new(box_template).result(binding)
  file = "data/#{addr}/index.html"
  File.open(file, "w+") do |f|
        f.write(result)
  end

end

