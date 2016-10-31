var pg = require('pg')
var gauss = require('gauss')
var _ = require('underscore')

/*
 * Given: An SQL query
 * Returns: The result of the SQL query
 *
 */
function pgQuery(qString, callback){
    var username = process.env.USER;
    var password = username + '123';

	// Example URL string: 'pg://control_tower:password@localhost:5432/control_tower'
    var defaultUrl = 'pg://' + username + ":" + password + "@localhost:5432/" + username;
	var connectionString = process.env.DATABASE_URL || defaultUrl;

    console.log(connectionString);


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


/*
 * 
 * TODO: Document this crap better please
 *
 */

function constructSensorQuery(options){
    var selector = options.sensors.join(" ") + " ";
    var sourceTable = 'outdoor_env '; 
    var sampleConditional = "";
    if( ('sampleInter' in options) && ('sampleSelector' in options)){
        sourceTable = '( SELECT db_time, ' + options.sampleSelector + ', ' + 
                      'row_number() OVER(ORDER BY db_time DESC) ' + 
                      'AS row FROM outdoor_env WHERE ' + 
                      options.sampleSelector + ' ' + 
                      'IS NOT NULL ' + 
                      ') t ';
        sampleConditional = 'AND t.row % ' + options.sampleInter + ' = 0 ';
    }

    var nullConditional = 'apogee_w_m2 IS NOT NULL ';
    var dateConditional = "";
    if( ("startDate" in options) && ("endDate" in options) ){
        var start = options.startDate.toISOString();
        var end = options.endDate.toISOString();
        var dateConditional = 'AND (db_time >= ' + '\'' + start+ '\'' + ' AND ' + 'db_time <= ' + '\'' + end + '\'' + ') '; 
    }
    var conditional = nullConditional + dateConditional + sampleConditional;
    var order = 'db_time DESC ';
    var limit = '2000';
    if("rowLimit" in options){
        limit = options.rowLimit;
    }


    return 'SELECT db_time, ' + selector + 
           'FROM ' + sourceTable + 
           'WHERE (' + conditional + ') ' + 
           'ORDER BY '  + order +
           'LIMIT ' + limit;
}

function insertRow(){
    // Example
    // INSERT INTO outdoor_env (db_time, address, apogee_w_m2) VALUES (now(),5000,502038);
}

function xyTransform(dataRows, callback){
    var tracker = 0;
    var filtered = gauss.Vector(dataRows.map(function(row){return row.apogee_w_m2})).ema(1).reverse();
    var timeStamps = dataRows.map(function(row){return (new Date(String(row.db_time))).getTime()}).reverse();
    var dataSet = [];
    var tmp = {};
    for(var i = 0; i < filtered.length ; i ++ ){
        tmp.x = timeStamps[i];
        tmp.y = filtered[i];
        dataSet.push(tmp);
        tmp = {};
    } 
    return JSON.stringify(dataSet);
}

// TODO: Name this crap better
function fetchSensorData(options, callback){ 
    var start = new Date();
    var limitQuery = "";
    var query;
    var queryOptions;

    start.setDate(start.getDate() - 60);

    queryOptions = {
        sensors: ["apogee_w_m2"],
        sampleSelector: "apogee_w_m2",
        sampleInter: "1",
        rowLimit: "1000"
    };
    query = constructSensorQuery(queryOptions);
    console.log("Running query: ");
    console.log(query);
    pgQuery(query, function(result){
      console.log("Done with query");
      callback(xyTransform(result.rows));
    });
}
function fetchFunStuff(options, callback){ 
    var q = "SELECT * FROM outdoor_env LIMIT 100"
    pgQuery(q, function(result){
      callback(result.rows);
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
    fetchSensorData: fetchSensorData,
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
    testStuff: function(req, res, next){
        fetchFunStuff({}, function(results){
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

/*
var start = new Date();
start.setDate(start.getDate() - 60);
start = start;
end = new Date();

var options = {
    sensors: ["apogee_w_m2"],
    startDate: start,
    sampleSelector: "apogee_w_m2",
    sampleInter: "100",
    endDate: (new Date())
}
var q = constructSensorQuery(options);
console.log(q);

var options = {
    sensors: ["apogee_w_m2"],
    sampleSelector: "apogee_w_m2",
    sampleInter: "100"
}
var q = constructSensorQuery(options);
console.log(q);
*/
