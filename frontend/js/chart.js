function getData(){
  $.get('http://localhost:16906/fetchVoltage', function(data){
    createChart(data);
  });
}

function createChart(data){
    d = JSON.parse(data);

    var chart = new CanvasJS.Chart("SCELChart",
    {
      title:{
      text: "SCELData"
      },
      data: [
      {
        type: "line",
        dataPoints: d
      }
      ]
    });
    chart.render();
}

$(document).ready(function(){
    getData();
});
