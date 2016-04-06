
/* Accepts the following options:
 *      element
 *      text
 *      endpoint
 */
function createBatteryChart(options){
    getData(options);

}

function getData(options){
  $.get("http://192.168.1.98:16906" + options.endpoint, function(data){
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


function render_boxes(){
    var databoxes = [
        {
            element: "batt_151",
            text: "Apple_v1: 151",
            endpoint: "/battery/151"
        },
        {
            element: "batt_888",
            text: "Dragonfruit: 888",
            endpoint: "/battery/888"
        },
        {
            element: "batt_889",
            text: "Cranberry: 889",
            endpoint: "/battery/889"
        }
    ]
    databoxes.forEach(function(d){
        createBatteryChart(d);
    });
}

$(document).ready(function(){
    render_boxes();
    setInterval(function(){
        render_boxes();
    }, 30*1000);
});
