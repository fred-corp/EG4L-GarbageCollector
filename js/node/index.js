const connectUrl = `mqtt://eu1.cloud.thethings.network`
const mqtt = require('mqtt')

const client = mqtt.connect(connectUrl, {
clean: true,
connectTimeout: 4000,
username: 'garbage-collector@ttn',
password: 'NNSXS.2EYH4ABI5Z2BG2G3FTXU5RHWQBB24DWG6VOJBKI.LIKCMLTXFDKA7D7JRAKPHIF3U6A4HMEFHY5HHTLRO4IV7CNO23SA',
reconnectPeriod: 1000,
})

client.on('connect', () => {
var topic = "v3/garbage-collector@ttn/devices/eui-a8610a3335369606/up";
console.log('Connected')
client.subscribe(topic); //single topic
console.log("connected +subscribed");
});

//handle errors
client.on("error", function (error) {
console.log("Can't connect" + error);
process.exit(1)
});

//handle incoming messages
client.on("message", function (topic, message, packet) {
var getDataFromTTN = JSON.parse(message);
data = getDataFromTTN.uplink_message.decoded_payload;
console.log("message is " + message);
console.log("topic is " + topic);
console.log("data is " + data.bat);
})