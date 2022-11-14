const mqtt = require('mqtt')
const express = require('express')
const app = express()

const secrets = require('./secrets.json')

const host = 'eu1.cloud.thethings.network'
const MQTTport = '1883'

var MQTTdata = { 
  "0": {
    "bat": 255,
    "garbage_h": 0,
    "garbage_w": 0,
    "hum": 12,
    "pres": 1013,
    "temp": 21,
    "timestamp": 0
  }
}

const connectUrl = `mqtt://${host}:${MQTTport}`
const client = mqtt.connect(connectUrl, {
  clean: true,
  connectTimeout: 4000,
  username: 'garbage-collector@ttn',
  password: secrets.apikey,
  reconnectPeriod: 1000,
})

client.on('connect', () => {
  var topic = "v3/garbage-collector@ttn/devices/eui-a8610a3335369606/up"
  console.log('Connected')
  client.subscribe(topic) //single topic
  console.log("connected +subscribed")
})
//handle errors
client.on("error", function (error) {
  console.log("Can't connect" + error);
  process.exit(1)
})
//handle incoming messages
client.on("message", function (topic, message, packet) {
  var getDataFromTTN = JSON.parse(message)
  data = getDataFromTTN.uplink_message.decoded_payload
  MQTTdata[data.id] = data
  // console.log("message is " + message)
  // console.log("topic is " + topic)
  console.log("payload is " + JSON.stringify(data, null, 2));
  console.log("MQTTdata is " + JSON.stringify(MQTTdata, null, 2));
})

const port = 3000

app.use(express.urlencoded({ extended: true }))
app.use(express.static('public'))


app.listen(port, function () {
  console.log('server is listening on port ' + port)
})


app.get('/api', function (req, res) {
  res.json(MQTTdata)
})

app.get('/', function (req, res) {
  res.render('index.ejs', { data: MQTTdata })
})

// respond with css file
app.get('/style.css', function (req, res) {
  res.sendFile(__dirname + '/styles/style.css')
})