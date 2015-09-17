# amv-open360tracker v0.6
---------------------
# EXPERIMENTAL
#Command Line Interface added. Use this version in your opent360tracker under your own risk.

* To enter in CLI mode key in ### and press enter.
* Key in help and press Enter to see a list of available commands.
* Only a few commands will take effect if you set them:
	set P=value
	set I=value
	set D=value
	set max_pid_error=value
	set tilt0=value
	set tilt90=value
	set pan0=value
	set min_pan_speed=value
	set offset
Please, be quite carefully using this feature, it is only for experimental use.


---------------------
Seguidor de antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

Este proyecto deriva del proyecto original de  [open360tracker](https://github.com/SamuelBrucksch/open360tracker) creado por SamuelBrucksch.

El firmware está basado en la familia de microprocesadores de 8-bit de atmel presente en la plataforma Arduino. Es capaz de controlar un antenna tracker de fabricación casera que ofrece completa rotación continua de 360º, y soporta varios prococolos de telemetría y comunicaciones de diferentes controladoras de vuelo, como FrSky, Hott, Mavlink, MultiWii, Naza, Ardupilot, Arducopter y Rangevideo.

# Rotación continua de 360°

La rotación contínua se consigue con la utlización de un servo normal, una vez desprovisto de su potenciómetro y tope que le impiden seguir girando, y añadiendo un sencillo divisor de tensión. También existe la posibildiad de usar servos específicos para rotación continua de 360º.

Para eliminar el cruce y trenzado de cables entre las dos secciones del tracker, se emplea un "slip ring", un anillo de giro contínuo 360 ° con coletor de conexiones.

# Heading (Azimut)

La dirección hacia la que apunta el seguidor de antena se controla mediante un compás electrónico, que elimina la necesidad de apuntar hacia la dirección correcta de forma manual, como se venía haciendo en los seguidores de antena tradicionales.

# Telemetría y Sistemas de Comunicaciones

En esta versión inicial se soporta diversos protocolos y sistemas de comunicaciones:

* Descodificación de datos de telemetría desde la salida de datos de los módulos TX FrSky.
* Transmisión de tramas NMEA 0183 directas desde GPS por comunicación series "transparente"", sobre el enlace de de telemetría de los TX/RX basados en Open LRS (testado por la comunidad).
* Protocolo de comunicaciones Mavlink desde la salida de datos desde OSD my MyFlyDream o desde controladoras de vuelo basadas en APM, sobre enlaces de telemetría TX/RX Open LRS, o modulación demodulación sobre canal de vídeo video 1.2/2.4/5.8 Ghz (testado por la comunidad).
* Decodificación de datos de telemetría de Rangevideo OSD enviados vía enlace TX/RX de vídeo, y extraídos directament desde el módulo decodificador RVGS de tierra (en fase de pruebas).

Aquí encontrarás una lista de los protocolos soportados: [Protocolos](https://github.com/SamuelBrucksch/open360tracker/wiki/Protocols)

# Comunidad FPV AMV:

Vista el hilo del foro para más información:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

# amv-open360tracker (english)

The AMV spanish community version (fork) of the open source antenna tracker for FPV for continuous 360 degree rotation.

This project is a fork of the original firmware of the [open360tracker](https://github.com/SamuelBrucksch/open360tracker) created by SamuelBrucksch.

The firmware is based on the 8-bit atmel microcontrollers and manage an DIY antenna tracker which offers full 360° continuous rotation and support for lots of different telemetry protocols and flight controllers like FrSky, HoTT, Mavlink, MultiWii, Naza, ArduPilot, Arducopter and Rangevideo.

More info about this projet at [http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


