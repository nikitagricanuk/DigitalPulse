const client = mqtt.connect("ws://test.mosquitto.org:8080"); 

client.on('connect', () => {
  console.log('Подключение к MQTT-брокеру успешно выполнено');
  
  client.subscribe('digitalpulse/temperature', (err) => {
    if (!err) {
      console.log('Подписка на тему  успешна');
    } else {
      console.error('Ошибка подписки:', err);
    }
  });
});

client.on('message', (topic, message) => {
  if (topic === 'digitalpulse/temperature') { // Убедитесь, что тема совпадает
    document.getElementById('SensorValue').innerText = message.toString();
  }
});
