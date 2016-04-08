
/* Accepts the following options:
 *      element
 *      text
 *      endpoint
 */
function createBatteryChart(options){
    getData(options);

}

function getData(options){
  $.get(options.endpoint, function(data){
    createChart(data, options);
  });
}


function createChart(data, options){
    d = data.map(function(datapoint){
        var o = {
            x: new Date(Date.parse(datapoint.db_time)),
            y: datapoint.batt_mv
        }
        return o;
    });

    var chart = new CanvasJS.Chart(options.element,
    {
    zoomEnabled: true,
      title:{
      text: options.text,
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
    var options = {
        element: "batt_888",
        text: "Dragonfruit - Address 888",
        endpoint: "http://localhost:16906/battery/888"
    }
    createBatteryChart(options);
    var options = {
        element: "batt_889",
        text: "Cranberry - Address 889",
        endpoint: "http://localhost:16906/battery/889"
    }
    createBatteryChart(options);
    var options = {
        element: "batt_151",
        text: "Apple - Address 151",
        endpoint: "http://localhost:16906/battery/151"
    }
    createBatteryChart(options);

    setInterval(function(){
        var options = {
            element: "batt_888",
            text: "Dragonfruit - Address 888",
            endpoint: "http://localhost:16906/battery/888"
        }
        createBatteryChart(options);
        var options = {
            element: "batt_889",
            text: "Cranberry - Address 889",
            endpoint: "http://localhost:16906/battery/889"
        }
        createBatteryChart(options);
    var options = {
        element: "batt_151",
        text: "Apple - Address 151",
        endpoint: "http://localhost:16906/battery/151"
    }
    createBatteryChart(options);
        console.log("Updating GUI");
    }, 30*1000);
});
