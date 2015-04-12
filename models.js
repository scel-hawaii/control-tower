var pg = require('pg').native
var gauss = require('gauss')
var _ = require('underscore')

function combine(keys, vals) {
    return keys.reduce (
        function(prev, val, i) { prev[val] = vals[i]; return prev; }, 
        {}
    ); }

// Run a pg query from a pool of clients
function pgQuery(qString, callback){
	var connectionString = process.env.DATABASE_URL || 'pg://control_tower:salty8814pilot@192.168.1.38:5432/control_tower';
	pg.connect(connectionString, function(err, client, done) {
	  if(err) {
	    return console.error('error fetching client from pool', err);
	  }
	  client.query(qString, function(err, result) {
	    //call `done()` to release the client back to the pool
	    done();
	    if(err) {
	      return console.error('error running query', err);
	    }
      callback(result)
      client.end();
	  });
  });

}

function fetchSensorData(options, callback){ 
	  var queryString = 'SELECT db_time, apogee_w_m2 FROM outdoor_env WHERE apogee_w_m2 IS NOT NULL ORDER BY db_time DESC LIMIT 20000 ';
    var today = new Date();
    var limitQuery = "";
    today.setDate(today.getDate() - 60);
    options.startDate = today.toISOString();
    options.endDate = (new Date()).toISOString();
    if(!("sampleOffset" in options)) options.sampleOffset = 20;
    if(!("limitValue" in options)) limitQuery = 'LIMIT 10000'; 
    if(!("startDate" in options) && !("endDate" in options)){
      var dateQuery = '';
    }
    else{
      var dateQuery = '(db_time >= ' + '\'' + options.startDate + '\'' + ' AND ' + 'db_time <= ' + '\'' + options.endDate + '\'' + ')';
    }
	  var queryString2 = 'SELECT db_time, apogee_w_m2 ' + 
                       'FROM( SELECT db_time, apogee_w_m2, row_number() OVER(ORDER BY db_time DESC) AS row FROM outdoor_env) t ' + 
                       'WHERE(t.row % ' + options.sampleOffset + ' = 0 ' + 'AND ' + dateQuery + ') AND apogee_w_m2 IS NOT NULL ' + limitQuery;

    console.log(queryString2);
    pgQuery(queryString2, function(result){
      var tracker = 0;
      var filtered = gauss.Vector(result.rows.map(function(row){return row.apogee_w_m2})).sma(1).reverse();
      var timeStamps = result.rows.map(function(row){return (new Date(String(row.db_time))).getTime()}).reverse();
      var dataSet = [];
      var tmp = {};
      for(var i = 0; i < filtered.length ; i ++ ){
        tmp.x = timeStamps[i];
        tmp.y = filtered[i];
        dataSet.push(tmp);
        tmp = {};
      } 
      callback(JSON.stringify(dataSet));
    });
}
function fetchSmoothData(options, callback){ 
	  var queryString = 'SELECT db_time, apogee_w_m2 FROM outdoor_env WHERE apogee_w_m2 IS NOT NULL ORDER BY db_time DESC LIMIT 20000 ';
    var today = new Date();
    var limitQuery = "";
    today.setDate(today.getDate() - 60);
    options.startDate = today.toISOString();
    options.endDate = (new Date()).toISOString();
    if(!("sampleOffset" in options)) options.sampleOffset = 20;
    if(!("limitValue" in options)) limitQuery = 'LIMIT 10000'; 
    if(!("startDate" in options) && !("endDate" in options)){
      var dateQuery = '';
    }
    else{
      var dateQuery = '(db_time >= ' + '\'' + options.startDate + '\'' + ' AND ' + 'db_time <= ' + '\'' + options.endDate + '\'' + ')';
    }
	  var queryString2 = 'SELECT db_time, apogee_w_m2 ' + 
                       'FROM( SELECT db_time, apogee_w_m2, row_number() OVER(ORDER BY db_time DESC) AS row FROM outdoor_env) t ' + 
                       'WHERE(t.row % ' + options.sampleOffset + ' = 0 ' + 'AND ' + dateQuery + ') AND apogee_w_m2 IS NOT NULL ' + limitQuery;

    console.log(queryString2);
    pgQuery(queryString2, function(result){
      var tracker = 0;
      var filtered = gauss.Vector(result.rows.map(function(row){return row.apogee_w_m2})).ema(25).reverse();
      var timeStamps = result.rows.map(function(row){return (new Date(String(row.db_time))).getTime()}).reverse();
      var dataSet = [];
      var tmp = {};
      for(var i = 0; i < filtered.length ; i ++ ){
        tmp.x = timeStamps[i];
        tmp.y = filtered[i];
        dataSet.push(tmp);
        tmp = {};
      } 
      callback(JSON.stringify(dataSet));
    });
}

function fetchVoltage(options, callback){ 
	  var queryString = 'SELECT db_time, apogee_w_m2 FROM outdoor_env WHERE apogee_w_m2 IS NOT NULL ORDER BY db_time DESC LIMIT 20000 ';
    var today = new Date();
    var limitQuery = "";
    today.setDate(today.getDate() - 60);
    options.startDate = today.toISOString();
    options.endDate = (new Date()).toISOString();
    if(!("sampleOffset" in options)) options.sampleOffset = 1;
    if(!("limitValue" in options)) limitQuery = 'LIMIT 10000'; 
    if(!("startDate" in options) && !("endDate" in options)){
      var dateQuery = '';
    }
    else{
      var dateQuery = '(db_time >= ' + '\'' + options.startDate + '\'' + ' AND ' + 'db_time <= ' + '\'' + options.endDate + '\'' + ')';
    }
	  var queryString2 = 'SELECT db_time, batt_mv ' + 
                       'FROM( SELECT db_time, batt_mv, row_number() OVER(ORDER BY db_time DESC) AS row FROM outdoor_env) t ' + 
                       'WHERE(t.row % ' + options.sampleOffset + ' = 0 ' + 'AND ' + dateQuery + ') AND batt_mv IS NOT NULL ' + limitQuery;

    console.log(queryString2);
    pgQuery(queryString2, function(result){
      var tracker = 0;
      var filtered = gauss.Vector(result.rows.map(function(row){return row.batt_mv})).sma(1).reverse();
      var timeStamps = result.rows.map(function(row){return (new Date(String(row.db_time))).getTime()}).reverse();
      var dataSet = [];
      var tmp = {};
      for(var i = 0; i < filtered.length ; i ++ ){
        tmp.x = timeStamps[i];
        tmp.y = filtered[i];
        dataSet.push(tmp);
        tmp = {};
      } 
      callback(JSON.stringify(dataSet));
    });
}

function fetchTemperature(options, callback){ 
	  var queryString = 'SELECT db_time, bmp085_temp_decic FROM outdoor_env WHERE bmp085_temp_decic IS NOT NULL ORDER BY db_time DESC LIMIT 5000 ';
    var today = new Date();
    var limitQuery = "";
    today.setDate(today.getDate() - 60);
    options.startDate = today.toISOString();
    options.endDate = (new Date()).toISOString();
    if(!("sampleOffset" in options)) options.sampleOffset = 1;
    if(!("limitValue" in options)) limitQuery = 'LIMIT 1500'; 
    if(!("startDate" in options) && !("endDate" in options)){
      var dateQuery = '';
    }
    else{
      var dateQuery = '(db_time >= ' + '\'' + options.startDate + '\'' + ' AND ' + 'db_time <= ' + '\'' + options.endDate + '\'' + ')';
    }
	  var queryString2 = 'SELECT db_time, bmp085_temp_decic ' + 
                       'FROM( SELECT db_time, bmp085_temp_decic, row_number() OVER(ORDER BY db_time DESC) AS row FROM outdoor_env) t ' + 
                       'WHERE(t.row % ' + options.sampleOffset + ' = 0 ' + 'AND ' + dateQuery + ') AND bmp085_temp_decic IS NOT NULL ' + limitQuery;

    console.log(queryString2);
    pgQuery(queryString2, function(result){
      var tracker = 0;
      var filtered = gauss.Vector(result.rows.map(function(row){return row.bmp085_temp_decic*5})).sma(1).reverse();
      var timeStamps = result.rows.map(function(row){return (new Date(String(row.db_time))).getTime()}).reverse();
      var dataSet = [];
      var tmp = {};
      for(var i = 0; i < filtered.length ; i ++ ){
        tmp.x = timeStamps[i];
        tmp.y = filtered[i];
        dataSet.push(tmp);
        tmp = {};
      } 
      callback(JSON.stringify(dataSet));
    });
}

module.exports = {
    // =======================
    // Descriptions
    // =======================
    sayHello: function(req, res, next){
      res.send("Hello, World!");
      return next();
    },
    grabData: function(req, res, next){
        fetchSensorData({}, function(results){
	    res.send(results);
 	    return next();
        });
    },
    grabSmoothData: function(req, res, next){
        fetchSmoothData({}, function(results){
	    res.send(results);
 	    return next();
        });
    },
    grabVoltage: function(req, res, next){
        fetchVoltage({}, function(results){
	    res.send(results);
 	    return next();
        });
    },
    grabTemperature: function(req, res, next){
        fetchTemperature({}, function(results){
	    res.send(results);
 	    return next();
        });
    }
}

