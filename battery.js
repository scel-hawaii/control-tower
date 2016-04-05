var pg = require('pg').native
var gauss = require('gauss')
var _ = require('underscore')
/*
 * Given: An SQL query
 * Returns: The result of the SQL query
 *
 */
function pgQuery(qString, callback){
	var connectionString = process.env.DATABASE_URL || 'pg://kluong:hello@localhost:5432/kluong';
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

function fetch(address, callback){
    q = "SELECT db_time, batt_mv FROM outdoor_env " +
        "WHERE address=" +
        address + " " +
        "AND batt_mv IS NOT NULL " +
        "ORDER BY db_time DESC " +
        "LIMIT 1000";
    console.log(q);
    pgQuery(q, function(results){
        callback(results.rows);
    });
}

module.exports = {
    fetch: function(req, res, next){
        fetch(req.params.address, function(results){
            res.send(results);
            return next();
        });
    }
}
