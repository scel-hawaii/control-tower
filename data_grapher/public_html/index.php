<DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
  </head>
  <body>
<div class="container-fluid">

<h1>
   SCEL Weatherbox Data
   <small>
   <strong>Last Generated: </strong>
   <?php echo file_get_contents( "last_run.txt" ); ?>
   </small>
</h1>
<hr />

<div class="row">
<div class="col-md-4">
<div class="panel panel-default">
<div class="panel-body">
<?php
function tailShell($filepath, $lines = 1) {
  ob_start();
  passthru('tail -'  . $lines . ' ' . escapeshellarg($filepath));
  return trim(ob_get_clean());
}
?>
<?php
function headShell($filepath, $lines = 1) {
  ob_start();
  passthru('head -'  . $lines . ' ' . escapeshellarg($filepath));
  return trim(ob_get_clean());
}
?>

<h3> Graphs </h3>
<ul>
  <li>
    <a href="/apple/" target="_blank">Apple</a>
  </li>
  <li>
    <a href="/cranberry/" target="_blank">Cranberry</a>
  </li>
</ul>


<h3>Reset Logs (recent 5)</h3>
<p>
<?php
echo nl2br(tailShell("reset_log.txt", 5));
?>
</p>

<h3>Data Files</h3>

<p>
<a href="/apple_data.csv">Apple Data File</a><br />
<a href="/cranberry_data.csv">Cranberry Data File</a><br />
<a href="/dragonfruit_data.csv">Dragonfruit Data File</a><br />
</p>

</div> <!-- end panel body -->
</div> <!-- end panel -->
</div> <!-- end col-md-6 -->
<div class="col-md-8">

<h3>Apple Data (recent 5)</h3>
<?php
echo nl2br(headShell("apple_data.csv", 1));
?>
<br />
<?php
echo nl2br(tailShell("apple_data.csv", 5));
?>

<h3>Cranberry Data (recent 5)</h3>
<?php
echo nl2br(headShell("cranberry_data.csv", 1));
?>
<br />
<?php
echo nl2br(tailShell("cranberry_data.csv", 5));
?>

<h3>Dragonfruit Data (recent 5)</h3>
<?php
echo nl2br(headShell("dragonfruit_data.csv", 1));
?>
<br />
<?php
echo nl2br(tailShell("dragonfruit_data.csv", 5));
?>

</div>
</div>
</div>


  </body>
</html>

