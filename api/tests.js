var models = require('./models.js')
models.fetchSensorData({}, function(results){
    console.log(results);
});
