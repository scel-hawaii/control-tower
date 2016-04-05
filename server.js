var restify = require('restify');
var models = require(__dirname + '/models.js');
var battery = require(__dirname + '/battery.js');

var server = restify.createServer({
  name: 'scel-server',
  version: '0.0.1'
});

server.use(restify.acceptParser(server.acceptable));
server.use(restify.queryParser());
server.use(restify.bodyParser());
server.use(restify.CORS());

// =======================
// Routes
// =======================
server.get('/test-stuff', models.testStuff);
server.get('/stuff', models.grabData);
server.get('/fetchVoltage', models.grabVoltage);
server.get('/fetchTemperature', models.grabTemperature);
server.get('/fetchSmoothData', models.grabSmoothData);
server.get('/battery/:address', battery.fetch);
server.get('/', models.sayHello);


server.listen(16906, function () {
  console.log('%s listening at %s', server.name, server.url);
});
