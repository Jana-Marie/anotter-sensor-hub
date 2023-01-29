# anotter-sensor-hub

An ESP32 based environment sensor hub with prometheus interface. It pairs perfectly with Sensirion SEN05x (depictured SEN055) sensors, which provide PM1, PM2.5, PM4, PM10, Temperature, Humidity, VOC and NOC index. Furthermore other I2C, SPI or PWM sensors can be added to the designated connectors. All ESP32 pins are broken out to offer bodging all sensors imaginable to the host board.

The PCB and components (w/o SEN055) are about ~5$, with SEN055 it comes up to ~40€/sensor node. 

<p display="inline-block">
  <img src="/sen01.jpg" height="410"/>
  <img src="/sen02.jpg" height="410"/> 
</p>

![](/grafana.png)
