# amv-open360tracker v0.8
---------------------
# Novedades

Se ha añadido soporte para el protocolo Light Telemetry (LTM). 
  
# Mejoras desde v0.7 y anteriores incluídas

* Se ha mejorado el protocolo FRSKY_D para el escenario [NAZE32 + Cleanflight + módulo tx DJT FrSKY](https://github.com/raul-ortega/amv-open360tracker/blob/master/docs/NAZE32%2BCleanflight%2BGPS%2BFrSkyD.pdf) + MOD. BLUETOOTH.
* [Sistema de Control de Servo PAN sin PIDs](https://github.com/raul-ortega/amv-open360tracker/blob/master/docs/NO-PID-Control-PAN-Servo.md) (Opcional y experimental).
* El parámetro OFFSET corregido para Crius SE.
* OFFSET toma ahora valores entre 0 y 359 grados.
* [Efecto de amortiguación (Easing Effect)](https://github.com/raul-ortega/amv-open360tracker/blob/master/docs/Efecto-Easing-en-Servo-TILT-para-antenas-pesadas.pdf) para el servo tilt.
* La telemetría RVSOD ahora funciona.
* Problemas de compilación con LCD sin GPS local resueltos.
* Problemas de visualización de datos resueltos.

---------------------

# What's new

Light Telemetry protocol supported now.

# Improvements also included (from  v0.8 and older)

* FRSKY_D parser improved for scenario: [NAZE32 + Cleanflight + módulo tx DJT FrSKY](https://github.com/raul-ortega/amv-open360tracker/blob/master/docs/NAZE32%2BCleanflight%2BGPS%2BFrSkyD.pdf) + BLUETOOTH mod.
* experimentally control system for PAN servo
* Parameter OFFSET has been corrected for Crius SE board.
* Range of values for OFFSET: 0 to 359.
* Easing effect added to tilt servo movement.
* RVSOD telemetry now works.
* Some compilation issues solved.
* Some data visualization issues solved.

---------------------
# Seguidor de Antena de 360º Open Source

Seguidor de antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

Este proyecto, que se deriva del proyecto original de  [open360tracker](https://github.com/SamuelBrucksch/open360tracker) creado por SamuelBrucksch, ha sido adoptado como sistema seguidor de antena por un grupo de usuarios de la comunidad FPV de Aeromodelismo Virtual, resolviendo algunas deficiencias del proyecto original y añadiendo nuevas características:

* Se han resuelto los errores de compilación con el uso del LCD cuando no se usa GPS Local.
* Se han corregido errores de visualización de datos y deficiencias en el funcionamiento cuando no usa GPS Local.
* Se ha corregido y completado el algoritmo para la decodifiación de la telemetría de RVSOD, que no funcionaba en la veresión original.
* Se ha añadido efecto de amortiguación en el servo de TILT, pudiendo elegir entre tres funciones distintas de amortiguación.
* Resuelto el problema del valor del parámetro OFFSET.

Actualmente se está trabajando en la nueva [versión con interfaz de línea de comandos (CLI)](https://github.com/raul-ortega/amv-open360tracker/blob/remote-settings/README.md) para modificar los parámetros de configuraicón desde consola serie. En el futuro se desarrollará una aplicación android para interactuar con el tracker vía Bluetooth.

# Basado en Plataforma Arduino

El firmware está basado en la familia de microprocesadores de 8-bit de Atmel, presente en la plataforma Arduino. Es capaz de controlar un antenna tracker de fabricación casera que ofrece completa rotación continua de 360º, soporando varios prococolos de telemetría y comunicaciones, así como poder ejecutarse sobre diferentes controladoras de vuelo: FrSky, Hott, Mavlink, MultiWii, Naza, Ardupilot, Arducopter y Rangevideo OSD, OrangeRX (OpenLRS).

En la comunidad de usuarios de FPV de Aeromodelismo Virtual, se ha montado y testado el firm sobre Arduino Uno y controladora de vuelo Crius SE V2.5, que poseen el microprocesador Atmega328p. También es posible ejecutar el código en controladoras dotadas con Atmega2560, habiendo sido testado por un compañero sobre Arduino Mega. Otra posibilidad es usar como plataforma hardware FQR-MAX, también todado con atmega328, que están desarrolando usuarios de la comunidad.

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

A continuación un vídeo realizado por el compañero Simba, en el que se ve su antenna tracker en plena acción:

[![ScreenShot](https://i.ytimg.com/vi/7mY_J5hPdOo/mqdefault.jpg)](https://www.youtube.com/watch?v=7mY_J5hPdOo)

Vista el hilo del foro para más información:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

# amv-open360tracker v0.6 (English)

The AMV spanish community version (fork) of the open source antenna tracker for FPV with continuous 360 degree rotation. This project is a fork of the original firmware of the [open360tracker](https://github.com/SamuelBrucksch/open360tracker) created by SamuelBrucksch.

# Improvements

There are many improvements in this version:

* Solved compilation issues regarding when using LCD Display, and a local GPS is not present.
* Solved issues when displaying data and bad functioning when a local GPS device is not present.
* The telemetry parser algorithm for decoding the RVOSD frames has been debugged and improved, and now it works.
* The tilt servo movement has been improved by adding easing effects at the beginning and smoothing at the end. This will avoid damaging the tilt servo and other mechanisms when using heavy and larger antennas.
* Solved the issues with parameter OFFSET.

We are now working on a [new version with a Command Line Interface (CLI)](https://github.com/raul-ortega/amv-open360tracker/tree/remote-settings) which will facilitate setting parameters using a remote console, for example some Android app over Bluetooth.

# Platform
	
The firmware is based on the 8-bit atmel microcontrollers and manage an DIY antenna tracker which offers full 360° continuous rotation and support for lots of different telemetry protocols and flight controllers like FrSky, HoTT, Mavlink, MultiWii, Naza, ArduPilot, Arducopter and Rangevideo.

More info about this projet at [http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


