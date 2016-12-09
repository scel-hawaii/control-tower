<DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title></title>
  </head>
  <body>

   <p> <strong>Last Generated: </strong>
<?php
echo file_get_contents( "last_run.txt" ); // get the contents, and echo it out.
?>
   </p>
    <h1>Solar Irr</h1>
    <p><img src="solar_irr.png"></img></p>

    <h1>Panel Voltage</h1>
    <p><img src="panel_mv.png"></img></p>

    <h1>Battery Voltage</h1>
    <p><img src="batt_mv.png"></img></p>

    <h1>Uptime</h1>
    <p><img src="uptime_ms.png"></img></p>

    <h1>Temperature</h1>
    <p><img src="temperature.png"></img></p>

    <h1>Humidity</h1>
    <p><img src="humidity.png"></img></p>

    <h1>Pressure</h1>
    <p><img src="pressure.png"></img></p>

  </body>
</html>

