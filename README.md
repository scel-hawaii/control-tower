Weather API
-------------

Basic REST API server for accessing weatherbox data. Eventually to be used
for inputting data as well (with proper tokens).

# Endpoints

## battery

### battery/[address]

**Optional Query Parameters**
* Start Date: A UTC string with a start datetime.
* End Date: A UTC string with an end date.

Returns the last 50k samples. Given the start and end date query parameters,
the endpoint will return the last 50k samples with those dates as constraints.

**Example:**

`curl http://localhost/battery/151`



