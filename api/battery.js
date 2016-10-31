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

	pg.connect(connectionString, function(err, client, done) {
	  if(err) {
	    return console.error('error fetching client from pool', err);
	  } client.query(qString, function(err, result) {
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

function fetch(req, res, next){
    var address = req.params.address;

    if( typeof req.query.start_time === 'undefined') {
        q = "SELECT db_time, batt_mv FROM outdoor_env " +
            "WHERE address=" +
            address + " " +
            "AND batt_mv IS NOT NULL " +
            "ORDER BY db_time DESC " +
            "LIMIT 20000";
        console.log(q);
        pgQuery(q, function(results){
            res.send(results.rows);
            return next();
        });
    }
    else{
        if( typeof req.query.end_time === 'undefined'){
            res.send(400);
            return next();
        }
        console.log(req.query);
        q = "SELECT db_time, batt_mv FROM outdoor_env " +
            "WHERE address=" +
            address + " " +
            "AND db_time >= " + "'" + req.query.start_time + "'" + " " +
            "AND db_time < " + "'" + req.query.end_time + "'" + " " +
            "AND batt_mv IS NOT NULL " +
            "ORDER BY db_time DESC " +
            "LIMIT 20000";
        console.log(q);
        pgQuery(q, function(results){
            res.send(results.rows);
            return next();
        });


    }
}

module.exports = {
    fetch: fetch
}
