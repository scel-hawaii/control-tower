# data_grapher

Kenny Luong <luong97@hawaii.edu>  
2016-12-01  

This is a basic grapher and web-based interface that allows
students in SCEL easily inspect weather sensors.

# Setup

* Make sure that you setup nginx using the sample configuration in
config/data_grapher.nginx
* Install the crontab to your system so that it re-renders the graphs
    with a certain period

# Development

* You can use PHP to serve the pages easily in development: `php -S localhost:8000`


