# amv-open60tracker-32bits v2.1
---------------------------------
# EXPERIMENTAL

**Úsala bajo tu propio riesgo/Use it under your own risk.**

Esta es la versión de 32bits del seguidor de antena para FPV con rotación contínua de 360º de la [comunidad española de aeromodelismo virtual](http://www.aeromodelismovirtual.com/showthread.php?t=34530).

Por favor, antes de usar este software lea atentamente esta guía, aquí encontrará detallada toda la información necesaria para poner en marcha su seguirdor de antena con esta versión del firmware. Preste especial atención a las las instrucciones de instalación y las notas de recomendación para no dañar sus dispositivos.

# Novedades de la vesión 2.1

* Monitorización del voltaje y consumo de la batería del tracker.

# Novedades de la vesión 2.0

* Soporta hasta 4 puertos series: uarts 1 y 2 y softserial 1 y 2.
* Posiblidad de reasingnación de funciones de los puertos serie.
* Conversión y reenvío hacia puerto de salida de datos de posición a formatos Mavlink, FrSKY D, FrSKY X (SmartPort), Hott Telemetry y Light Telemetry.
* Conversión y reenvío hacia puerto de salida de datos de Distancia, Altitud y Azimuth a formato MFD (MFD Tracker).
* Nuevo sistema de activación de la posición HOME del tracker.
* Visualización en el display del estado y la fuente de la posición HOME.
* Nuevos perámetros para un mejor ajuste del control PIDs.


# Plataforma Hardware

Esta nueva versión es completamente experimental, y da soporte a controladoras con microprocesadores STM32F de 32bits basadas en la popular plataforma hardware **Naze32**. Actualmente se ha probado el firmware en la controladora **Flip32** que incorpora su propio magnetómetro.

También es posible que pueda funcionar sobre otras controladoras basadas en Naze32 que no dispongan de magnetómetro integrado en placa, siendo indispensable por tanto la conexión de un magnetómetro externo. Bajo estas circustancias el firmware aún no ha sido testado.

En esta versión se hace el uso de display OLED para mostrar los datos de telemetría, y otros datos de información (más adelante, en este mismo documento, encontrará más información sobre los dispositivos OLED compatibles). No es compatible con el uso de dispositivos LCD. 

El GPS Local ya está integrado de forma experimental, y está implementada la funcionalidad de activación automática del seguimiento tras obtener la posición de HOME.

El objetivo que se persigue con esta primera versión es la realización de pruebas por parte de los usuarios de la comunidad, con el fin de recopilar información derivada de la experiencia en su uso que sirva para determinar la viabilidad del proyecto.

Si decides usar este firmware, hazlo bajo tu propia responsabilidad, pues los dispositivos usados podrían terminar dañados, especialmente si no se siguen las instrucciones y recomendaciones que se dan en este documento.

# Protocolos de telemetría de entrada soportados

En estos momentos los protocolos de telemetría implementados son:

- **MFD** 
- **GPS TELEMETRY (direct NMEA from GPS)**
- **MAVLINK**
- **RVOSD**
- **FRSKY D**
- **LTM**

El resto de protocolos soportados en la versión 8 bits están en fase de integración en esta nueva versión de 32bits.

# Protocolos de telemetría de salida soportados

En estos momentos los protocolos de telemetría implementados son:

- **MAVLINK** 
- **MFD**
- **FRSKY D**
- **FRSKY X (Smartport)**
- **HOTT**
- **LTM**

# Interfaz de Línea de Comandos: modo CLI 

A efectos de configuración ésta es la principal **novedad** que incorpora esta nueva versión, característica que ya se había implemetnado en una [versión del firmware](https://github.com/raul-ortega/amv-open360tracker/tree/remote-settings) para plataformas basadas en Arduino, la cual no ha tenido continuidad por falta de memoria en los procesadores atmega328p.

La **mejora** tras la incorporación de esta interfaz de línea de comandos es que **ya no será necesario compilar el código y subirlo a la controladora** cada vez que se modifique un parámetro, con todas las ventajas que ello conlleva. Tan sólo será necesario subir el firmware una vez, o cuando haya alguna actualización importante.

Además, los parámetros de configuración pueden ser guardados en un archivo de texto, los cuales pueden ser transferidos en cualquier momento a la controladora a través de consola serie sin necesidad de teclear un solo comando, salvo que queramos modificar algún parámetro de forma puntual, o en el caso de la primera instalación.

Este CLI está inspirado en el CLI basefilght y cleanflight para Naze32, si estás familiarizado con él te será más fácil usarlo.

# Instalación
---------------------------------

**Preparación**

- Para esta versión preliminar la instalación de la controladora es muy sencilla, en especial si ya eres usuario de la versión de 8bits.

- El firm se subirá a la controladora usando el programa [Flash Loader Demonstrator](https://code.google.com/p/afrodevices/downloads/detail?name=stm32-stm8_flash_loader_demo.zip&can=2&q=) de STMicroelectronics, tal y como se explica en el [manual de la NAZE32](http://www.abusemark.com/downloads/naze32_rev3.pdf).

- Para comunicarnos con la controladora en modo CLI podemos usar cualquier software de consola serie. Podemos usar [Hércules](http://new.hwg.cz/files/download/sw/version/hercules_3-2-8.exe), que ya lo conoce nuestra comunidad y que nos permite copiar, pegar, volcar hacia/desde un archivo... 

- En cualquier caso, vamos a necesitar un **cable Micro USB** para **subir por primera vez el firmware a la controladora**, y para comunicarnos vía interfaz de línea de comandos durante la **primera configuración**.

- Necesitarás **soldar los pines** para **motores/servos**, **boot** y **uart1**, según se indica en la imagen.

- Ten a mano un jumper para colocar en los pines boot, pues lo necesitarás para subir por primera vez el firmware.

- La controladora se alimentará por los pines GND y +5V a donde mismo se conectan los motores/servos.

- En esta versión tan sólo necesitaremos **conectar los dos servos**, y conectar al **puerto uart1** el dispositivo serie a través del cual se recibirán los datos de telemetría.

**Se recomienda no conectar los servos la primera vez, al menos hasta que no nos hayamos familiarizado con la forma de configurar los parámetros**.

- Una vez que esté configurada la controladora, conectados los servos y el dispositivo serie para la recepción de telemetría, el cable Micro USB ya no será necesario, salvo que necesitemos subir nuevamente el firmware.

- Si eres usuario de la versión de 8 bits, y vas a probar esta versión de 32bits, **ten a mano los valores de los parámetros de configuración del config.h.**, pues vamos a esos mismos valores.

![Flip32](https://github.com/raul-ortega/amv-open360tracker/blob/master/32bits/Flip32-montaje.png)

**Parámetros de configuración**

Antes de continuar, tómate tu tiempo y copia todos estos comandos y parámetros de configuración en un archivo de texto y sálvalo.

Luego sustituye los valores de los parametros por los equivalentes del archivo config.h de la versión de 8bits (Si es la primera vez que te acercas al proyecto, más abajo se explica que es cada parámetro):

```
# PID CONTROL
set p = 2500
set i = 20
set d = 250
set max_pid_error = 10

# PAN SERVO
set pan0 = 1500
set pan0_calibrated = 0
set min_pan_speed = 0
# TILT SERVO
set tilt0 = 1050
set tilt90 = 2025

# TILT EASING
feature EASING
set easing = 1
set easing_steps = 20
set easing_min_angle = 1
set easing_milis = 15

# INIT SERVOS
set init_servos = 0

# MAGNETOMETER
set offset =  90.000
set mag_declination = 0

# TELEMETRY (GPS TELEMETRY 9600 BAUDS)
set telemetry_baud = 2
set telemetry_protocol = 8
set start_tracking_distance = 10

# GPS
feature GPS
set gps_baud = 2
set gps_provider = NMEA
```

Cuando la controladora se inicia por primera vez tras la carga del firmware, los valores por defecto son cargados automáticamente y podría provocar que los servos se activen, sobre todo si no son los mismos con los que se diseñó el software, en especial el PAN, que podría provocar que el servo se pusiera a girar a alta velocidad sin parar. 

El valor 0 en parámetro init_servos, por defecto, impide que los servos giren durante el arranque. Si ese parámetro lo configuramos a valor 0, una vez conectados los servos y suministres alimentación, sólo debería moverse el servo PAN un instante y pararse, y el servo tilt debería moverse hasta alcanzar la posición horizontal, cero grados de inclinación, quedando el tracker a espera de telemetría u órdenes vía CLI.

**Nota:** Consulta al final de este documento la lista de parámetros disponibles, es posible que haya parámetros nuevos, o modificaciones que no se contemplan aquí .

# Carga del firmware

Sigue con exactitud estos pasos para instalar el firmware en la controladora.

Para descargar el firmware utiliza el botón [Download ZIP]((https://github.com/raul-ortega/amv-open360tracker) que encontrarás en la página principal del proyecto. El firmware compilado y listo para subir a la controladora es el archivo con extensión .hex.

```
1.- Coloca el jumper en los pines boot.
2.- Conecta el cable Micro USB a la controladora y al PC.
3.- Abre el programa Flash Loader Demonstrator.
4.- Sigue las instrucciones del modo boot del manual de la NAZE32.
5.- Cierra el programa Flash Loader Demonstrator.
6.- Desconecta el cable Micro USB.
7.- Quita el Jumper.
8.- Vuelve a conectar el cable Micro USB.
```

**Arranque**

Los leds verde y rojo deberían parpadear siguiendo esta secuencia de arranque:

```
1.- Varios parpadeos del rojo y el verde, pero alternándose entre ellos mismos
2.- Varios parpadeos sólo del led rojo
3.- Tres parpadeos de ambos leds a la vez
4.- A continuación parpadearán juntos 3 veces y se apagan.
5.- Se enciende el led azul, la secuencia de arranque ha finalizado.
```

# Primer inicio: modo CLI

Ahora debemos entrar en modo CLI, para ello:

```
1.- Iniciamos el programa Hércules
2.- Seleccionamos los parámetros de comunicaciones:

    Name(Puerto): COM8
    Baud: 115200
	Data size: 8
    Parity: none
    Handshake: OFF
    Mode: Free

3.- Pulsamos Open

    Debería aparecer el mensaje "Serial por COM opened" en color verde.

4.- Tecleamos 3 VECES la letra R (en mayúsculas) y pulsamos enter.

    Aparecerá el mensaje Entering CLI Mode, type 'exit' to return, or 'help'.
	¡Enhorabuena, ya has entrado al modo CLI!.

5.- Abre el archivo con los parámetros de configuración y copia su contenido.

6.- Pega los parámetros de configuración en el interior de la ventana y pulsa 
    enter para que también acepte la última línea.

7.- Teclea save y pulsa enter

    Se mostrará un mensaje saving seguido de rebooting.
```
	
	Tu tracker ha sido configurado, pero aún nos faltan algunos detalles para que funcione correctamente:
	
* A justar el valor de pan0 para que el servo se detenga.
* Realizar la calibración del magentómetro.
* Ajustar el parámetro offset para que apunte al norte.
	
	Continúa leyendo...
	
# Ajustando pan0 

Es el momento de **conectar los servos**, y el adaptador serie a través del cual se recibirá la telemetría, por ejemplo el módulo bluetooth.

Conectamos la baetía al tracker, iniciándose la secuencia de arranque.

Si configuraste el parámetro init_servos a valor 1, el tracker girará durante no más de un segundo, y no muy rápido, tras lo que debería detenerse, justo cuando el led azul se queda fijo, indicando que la secuencia de arranque ha finalizado.

Si configuraste el parámetro init_servos a valor 0, durante la secuencia de arranque ninguno de los servos debería moverse.

En cualquier caso, si tras la sercuencai de arranque el tracker continua girando, no debería hacerlo muy rápido, pues hemos configurado el parámetro pan0 a un valor que conocíamos como el centro, es cuestión de ir ajustando ese valor. Para ello:

```
1.- Entrar al modo CLI
2.- Ejecutar comando set pan0=valor
3.- Si el servo no se detiene, volvemso al paso 2 ajustando nuevamente el valor.
4.- Si el servo se detiene, ejecutamos el comando set pan0_calibrated=1
5.- Guardamos con save 
```

**Notas:** 

* Tras ajuar el valor de pan0, debemos configurar el valor pan0_calibrated=1, de lo contrario, el tracker no se moverá cuando esté recibiendo telemetria.
* Al entrar en modo CLI, el tracker se orienta a 0 grados (Norte) por defecto. Pero como aún no hemos calibrado ni ajustado el offset, es posible que no esté apuntando a la dirección correcta.
* Puedes guardar la configuración si lo deseas, pero como vamos a realizar la calibración a continuación, y después ajustar algunos valores, podemos dejarlo para el final.

# Calibración

Una vez ajustado el valor de pan0, es necesario calibrar el magnetómetro:

```
1.- Entrar al modo CLI
2.- Ejecutar comando calibrate
3.- Guardamos con save 

Durante el proceso de calibración el tracker girará durante 30 segundos en un único sentido, tras lo cual se parará.
```

Tras la calibración, procedemos a ajustar el valor del offset.

**Notas:** 

* Si no calibramos el magnetómetro, el tracker no se moverá cuando esté recibiendo telemetría.

# Ajustar OFFSET

Este paso podríamos hacerlo después del ajuste de PIDs.

Cuando entramos en modo CLI, el tracker intenta apuntar a los 0 grados (norte). Si no lo hace, y ajustastes convenientemente los parámetros y calibraste, tendrás que ajustar el offset.

Si montaste la controladora con el magnetómetro alineado con el norte, es posible que no necesites tocar este parámetro, salvo que desees ajustarlo aún mejor.

Pero si montaste la controladora en una posición distinta, porque necesitabas sacar el conector micro usb hacia un lado de la caja del tracker, entonces necesitas ajustar este parámetro.

```
1.- Entrar al modo CLI
2.- Ejecutar comando set offset=90 (si giraste la controladora 90 grados, por ejemplo).
3.- Guardamos con save 
```

Nos queda ajustar los PIDs.

# Ajustar PIDs

Los valores de p, i y d por defecto, al igual que el resto de parámetros de configuración, están ajustados para un servo TowerPro MG996R modificado para que gire 360º. Éstos valores van a depender de muchos factores: las resistencias que hayamos usado, la mecánica usada en el tracker, cuan ajustados estén todos los elementos, holguras, etc... 

Si tu tracker oscila para alcancar el objetivo, se pasa del objetivo ligeramente, o no llega necesitas ajustar estos parámetros.

Aquí una explicación práctica de como ajustar los PIDs, por el compañero Simba:

```
La técnica consiste en aumentar la P hasta que cuando llegue al final tienda a oscilar.
Una vez conseguido, se baja el valor hasta que cesen las oscilaciones con margen de seguridad.
Luego aumentas la I hasta que veas que rebota sobre el final pero se amortigua.
Luego aumentas la D para conseguir que reaccione con viveza pero siempre sin que oscile sobre el final.
```

# Configuración de la telemetría de entrada

**Configuración del puerto serie 0 (UART1)**

Tras el primer arranque, nuestra controladora sólo puede trabajar con el puerto serie 0 (UART1) a 115200 baudios, dedicado inialmente a la telemetría de entrada.

Para cambiar los baudios del puerto serie 0 (UART1) puede emplear cualquiera de los siguietnes comandos:

	* set telemetry_baud=**valor**

	* serial 0 1 **baudios** **baudios** 0 **bauidos**

Si utilizas el primero, en la sección de parámetros encontrarás los valores y sus correpsondientes baudios.

Si optas por la segunda opcion ,debes sustituir **bauidos** por el valor deseado. El comando serial debe ir acompañado de los 6 parámetros, no se puede omitir ninguno. Por ejemplo, si queremos usar la uart1 a 9600 bauidos:

```
set telemetry_baud=2
```

O también.

```
serial 0 1 9600 9600 0 9600
```

En este último caso estamos configurando a 9600 baudios la uart1, indpendientemente de la función a la que se esté asignando.

El valor 0 indica puerto serie número 0 (uart1)

El valor 1 indica que se destina a telemetría.

El primer valor 9600 indica que la telemetría funcionará a 9600 baudios.

El resto de valores no son tenidos en cuenta para la telemetría, pero son necesarios para ejecutar con éxito el comando.
	

Para poder utilizar el puerto serie 1 (UART2) para gestionar el GPS local, es necesario 

**Selección del protocolo de telemetría de entrada**

Por defecto, nuestro tracker está configurado con el protocolo que hemos llamado GPS TELEMETRY. No es más que la telemetría directa en formato NMEA que puede suministrar cualquier módulo GPS compatible. En el aeromodelo puede tener un módulo GPS y hacer las tramas al tracker a través de un enlace sería de telemetría, como por ejemplo la que proporcionan los sistemas OpenLRS.

Para cambiar de protocolo:

```
1.- Entrar al modo CLI
2.- Ejecutar comando set telemtry_protocol=valor (ver valores en la sección de parámetros de este documento).
3.- Configurar los bauidos para la telemetría con set telemetry_baud=valor (ver lista de parámetros al final de este documento)
4.- Guardamos con save 
```

Una vez seleccionado el protocolo, no olvides configurar la uart1 a los bauidos necesarios (la lista completa de valores está al final de este documento).

# Comandos del modo CLI
---------------------------------

**Modificar parámetros**

Si tecleamos **set** y pulsamos **enter**, mostrará un listado de todos los parámetros disponibles y su valor en la forma:

* **set parámetro=valor**

Por ejemplo, para configuar el parámetro P de los PIDs a 400:

* set p=400

y pulsamos enter.

Para ver si el parámetro se ha modificado, tecleamos set y pulsamos enter, mostrándose todos los parámetros nuevamente.

Al final de este docuemtno está la lista completa de parámetros detallada.

**Salvar los cambios**

Para que los cambios realizados en la configuraicón tengan efecto, hay que salvarlos primero. Para ello tecleamos **save** y pulsamos **enter**. Todos los parámetros serán guardados permanentemente en la EEPROM, así que, aunque quitemos la alimentación, estos se cargarán en el próximo inicio.

Al salvar la configuración, la controladora hace un reinicio, realiza la carga de los parámetros, e inicia todo el hardware (los servos se inician sólo si configuraste el parámetro init_servos a valor 1).

La controladora queda a la espera de recibir datos de telemetría, o entrar nuevamente en modo CLI.

**Configuración por defecto**

Para volver a los valores por defecto de los parámetros de configuración, teclear **defaults** y pulsar **enter**.

La controladora se reinicia y se vuelven a cargar los parámetros por defecto, por lo que el tracker podría empezar a moverse sin control. La configuración que hubiésemos realizado se pierde si no la hemos guardado en un archivo de texto previamente.

**Comando feature**

Este comando tiene triple función:

* Mostrar el listado de características activadas.
* Activar una característica
* Desactivar una característica.

Tecleando **feature** y pulsando **enter**, muestra la lista de las que están activadas.

Tecleando **feature** y el **nombre de la característica** y pulsando **enter**, esta se activará si no lo estaba, o bien se desactivará si lo estaba.

Por ejemplo, para activar easing en el servo tilt:

* feature esaing

suponiendo que esté desactivada.

Para desactivarla:

* feature -esaing

**Efecto Easing en Servo Tilt**

* set easing=**1** para usar la función **out- quart**
* set easing=**2** para usar la función **out-circ**

Para desactivarlo basta con emplear el comando **featurea -easing**.

# Display OLED

Si instalamso un dispositivo OLDED, podremos visualizar bastante información relativa a la telemetría de entrada, datos del GPS Local, estado de la batería del tracker, y en versiones futuras incluso interactuar con el antena tracker para taréas básicas de configuración y ajuste.

Para activarla la utilización del display:

* feature display

Para desactivarla:

* feature -display

La característica se está usando con los siguientes displays OLED:

* [0.96 Inch 4Pin White IIC I2C OLED Display Module 12864 LED For Arduino](http://www.banggood.com/0_96-Inch-4Pin-White-IIC-I2C-OLED-Display-Module-12864-LED-For-Arduino-p-958196.html)
* [0.96 Inch 4Pin IIC I2C Blue OLED Display Module For Arduino](http://www.banggood.com/0_96-Inch-4Pin-IIC-I2C-Blue-OLED-Display-Module-For-Arduino-p-969147.html)

Cuando el tracker está a la espera de telemetría, la barrita que hay a la derecha del título de la página está quieta. Una vez que se reciben datos por el puerto serie asignado a la telemetría de entrada, la barrita empieza a girar, y se detiene si deja de recibir datos.

** Páginas **

En función de las características que se tengan activadas, el tracker mostrará distintas páginas de datos, que se irán alternando de forma cílical. Si no se activa ninguna característica, únicamente se mostrarán la página de inicio durante el arranque, y la página datos de Telemetría.

Las páginas mostradas son:

 * Página de inicio, con la versión del firmware.
 * Página de datos de telemetría.
 * Página de estado del GPS local.
 * Página del monitorización de la batería del tracker.

# GPS Local

Para mejorar la calidad del seguimiento, a la vez que hacer más cómodo establecer la posición de HOME, puede instalar un módulo GPS en el interior del tracker.

Para los protocolos de telemetría, **excepto para MFD**, se establece la posición HOME con los datos de posición obtenidos del GPS local, empezando el seguimiento de forma automática una vez que el aeromodelo se aleja la distancia mínica configurada, sin necesidad de pulsar el botón HOME. El display del tracker mostrará bastante información útil para monitorizar su estado, y determinar la calidad de la señal de los satélites, lo que nos ayudará a decidir si es o no un buen momento para lanzar nuestro aeromodelo al aire.

En el esquema de conexiones se describe como debe ir conectado el GPS. Para recibir datos de GPS sólo es necesario conectar en el pin RX de la controladora (pin nº 4) el cable TX del GPS, así como el cable de alimentación +5V y GND. No obstante, con el objetivo de poder configurar el GPS de forma automática, también es necesario conectar el pin TX de la controladora al cable RX del GPS.

**Parámetros de configuración**

Inicialmente estos son los parámetros a tener en cuenta para su correcto funcionamiento:

* **feature GPS** para activar la característica GPS

* **set gps_baud=valor** para configurar los baudios (tecleando el comando help podemos ver la lista de valores y los baudios que le corresponden).

* **set gps_provider=protocolo** para configurar el formato de tramas, que puede ser NMEA o UBLOX.

* **set home_min_sats=valor** asegura tener un número de satélites mínimo a partir del cual se establece la posición HOME. Si el número de satélites es menor que ese número, no se activará la posición HOME.

Los protocolos GPS soportados son NMEA y UBLOX. Para más información sobre los modelos de GPS soportados, consulte la información reportada por los usuarios de nuestra comunidad: [http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

** Configuración de del puerto serie 1 (UART2) para GPS Local

Desde la versión 1.12, es necesario ejecutar el siguiente comando en el modo cli para activar la función de gps local a través del puerto serie 1 (UART2)

serial 1 2 115200 **9600** 0 115200

Todos los parámetros del comando son necesarios, y únicamente basta con modificar el valor marcado en negrita para adecuarlo a los baudios a los que tengas configurado tu GPS local. Por ejemplo, para configurarlo a 57600 baudios:

```
serial 1 2 115200 57600 0 115200
```
Una vez asignado el puerto serie al GPS, es posible cabiar los baudios con set gps_baud, el formato de tramas con set gps_provider, y el número mínimo de satélites para establecer el home con set home_min_sats, como se ha explicado en la sección anterior.

# Telemetría de salida: Conversión de protocolos

Nuestro sistema tracker incorpora una funcionalidad que permite la conversión de tramas, desde los distintos protocolos de entrada soprotados, a otros formatos de tramas para enviarlos por un puerto de salida. Veamos un par de ejemplos de las posibles aplicaciones:

* El aeromodelo envía al tracker telemetría mavlink, y éste saca por un puerto serie la telemetría en formato MFD que es inyectado a la mecánica de otro tracker MFD.
* El aeromodelo envía telemetría NMEA Directa al tracker, y ésta es enviada a travmés de un módulo bluetooth en formato MAVLINK a la aplcación Droid Planner.

Son sólo dos ejemplos, pero son posibles otras combinaciones y aplicaciones.

Para activar esta funcionalidad, es necesario activar las características softserial y telemetría, y asignar un puerto serie a través del cual enviar las tramas de salida, según la siguietne secuencia:

```
feature softserial

save

feature telemetry

save

serial puerto tipotelemetria 115200 57600 baudios 115200

save
```

El comando serial es similar a los comandos utilziados para activar el GPS o la telemetría de entrada. La diferencia está en el número de puerto, y la posición de campos a modificar.

# Puertos serie virtuales: Softserial.

Para activar los puertos serie virtuales, debemos activar la característica softserial:

```
feature softserial

save
```

Al ejecutar el comando feature softserial y salvar, en el siguiente arranque se configuran y activan pines de propósito general de la controladora como puertos series virtuales.

Para comprobar el número de puerto correspondiente, tecleamos el comando:

```
serial
```

que muestra la lista completa de puertos disponibles. Dos puertos virtuales son añadidos junto a los puertos serial 0 (urat1) y srial 1 (uart2). En nuestro ejemplo, la lista completa es:

serial 0 1 9600 57600 0 115200
serial 1 2 115200 9600 0 115200
**serial 30 256 115200 57600 9600 115200**
serial 31 0 115200 57600 0 115200

El puerto serie 0 se asigna a la función 1 (telemetría de entrada) a 9600 baudios.
El puerto serie 1 se asigna a la función 2 (gps local) a 9600 baudios.
El puerto serie 30 se asigna a la función 256 (telemetría de salida MFD) a 9600 bauidos.
El puerto serie 31 está sin asignar, valor 0.

# Posición HOME

**HOME automático con GPS local**

Anteriormente se ha describo la funcionalidad de establecimiento automático de la posición HOME cuando tenemos instalado un GPS en nuestro antena tracker. Cuando el GPS recibe señal de más de un número de satélites que hemos prefijado en la configuración, la posición HOME es establecida sin necesidad de accionar el botón HOME.

**HOME Manual con GPS local**

En versiones anteriores del firmware, al incorporar un GPS local no era posible activar la posición HOME de forma manual, pues su presencia ocasionaba la activación de forma completamente automática. Si por algún motivo el GPS no recibía señal de suficientes satélites, o no se superaba el valor mínimo fijado a través de la configuración, no era posible iniciar el seguimiento del aeromodelo. Este problema se ha solucionado en las versionres resiente incorporando un nuevo algoritmo que permite el establecimiento de la posición home tanto de forma automática como manual.

Imaginemos que tenemos GPS LOCAL, y que el gps no coge los satélites preconfigurados, 8 por ejemplo, porque hay una mala recepción de satélites hoy. Pero resulta coge 5 o 6, que podríamos considerar suficientes, y no tenemos ganas de esperar a que coja 8 o más, o porque puede que con el cielo nublado sea imposible.

En una situación como la descrita es posible establecer la posición home mediante una pulsación simple del botón HOME. Con esa pulsación del botón, acpeto los 5 o 6 satélites que  está recibiendo el GPS local, fijándose la posición.

**Resetear posición HOME **

# Parámetros configurables en modo CLI
--------------------------------------

Esta es la lista completa de los parámetros que pueden ser configurados mediante el comando set:

* **p,i,d:** El valor de los valores PID (más información de como ajustarlo en la sección "Ajustar PIDs").
* **max_pid_error:** Es el valor máximo permitido de la componente de Error en el cálculo de PIDs. Por debajo de ese valor el pulso pwm resultante se envía al servo.
* **max_pid_accumulator:** Valor máximo del error acumulado en el cálculo de PIDs. En algunos casos en los que no se consigue ajustar los PIDs, al subir este valor es posible realizar un ajuste más fino.
* **max_pid_gain:** El valor máximo de ganancia de PIDs aplicado al pulso pwm del servo pan. Este valor por defecto está a 500, y es considerado como óptimo.
* **tilt0:** Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 0.
* **tilt90:** Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 90.
* **easing:** Puede tomar valores 1 (efecto easing out-quart) ó 2 (efecto easing out-circ). Para activar el efecto amortiguación es obligatorio ejecutar el comando **feature easing** durante la configuración. Cuando está activo el servo de tilt se mueve acelerando al principio del movimiento, y desacelarando al alcanzar el ángulo final, consiguiendo así un efecto de amortiguación. Muy útil si usas antenas muy pesadas.
* **easing_steps:** Número de pasos (movimientos) para alcanzar el ángulo final aplicando el efecto de amortiguación. Usa un valor entre 40 y 60 para comprobar su efecto.
* **easing_min_angle:** Es el valor en grados del ángulo mínimo a partir del cual se aplicará el efecto easing cuando está activado.
* **easing_milis:** es el tiempo en milisegundos que el sistema se espera entre paso y paso cuando el efecto easing está ctivado.
* **pan0:** Valor del pulso en milisegundos para que el servo pan se detenga. Es fundamental tener este parámetro bien ajustado para que el tracker funciona de forma óptima.
* **pan0_calibrated:** Al cargar el firmware, por defect este parámetro está a 0, los PIDs no actuan sobre el movimiento del servo PAN, de este modo podemos probar distintos valores de set pan0 para encontrar el pulso en el que el servo se detiene. Una vez que conseguimos deter el servo, debemos poner este parámetro pan0_calibrated a valor 1. Si no lo hacemos nuestro tracker no va a responder a ningún comando de heading desde modo CLI, ni a ningún cambio ordenado por la telemetría.
* **min_pan_speed:** Si el servo de pan tiene problemas para iniciar la rotación cuando la velociad es baja, ajusta este valor hasta que el tracker se mueva de forma directa desde cada posición.
* **offset:** Si montas la placa controladora de modo que no apunte hacia el frente, ajusta este valor tantos grados como sea necesario (de 1 a 360º).
* **mag_declination:** Consulta el valor que se corresponde con tu zona de vuelo en [http://www.magnetic-declination.com/](http://www.magnetic-declination.com/). Ejemplo, si la declinación magnética es 2º7 el valor a introducier es 207. Para 6º24 es 624.
* **telemetry_protocol:** Establece el protocolo de telemetría de entrada, desde el cual se suministra al tracker la posición del aeromodelo. Los posibles valores soportados son:
     - 4:   MFD
	 - 8:   GPS TELEMETRY
	 - 16:  MAVLINK
	 - 32:  RVOSD
	 - 64:  FrSKY D
	 - 128: FrSKY X (Smart Port)
	 - 256:	LTM
* **telemetry_baud:** Es el valor de los baudios a los que se va a recibir los datos de telemetría, o los baudios a los que nos comunicamos con el tracker en modo CLI. Por defecto tiene el valor 2 (9600 bauds) y acepta valores entre 1 (4800 bauds) y 6 (250000 bauds).
* **start_tracking_distance:** Es la distancia mínima a partir de la cual el tracker empieza a realizar el seguimiento del aeromodelo.
* **init_servos:** Permite activar/desactivar el inicio de los servos durante el arranque. Si está activado, durante el inicio enviará al servo PAN el pulso de parada (pan0), y en el caso del servo TILT, enviará el pulso para que se mueva ala posición horizontal 0º (tilt0). Por defecto el valor de este parámetro es 0. Si usas una antena muy pesada no se recomienda la activación de este parámetro, salvo que hayas activado y configurado previamente el efecto easing para el servo tilt, y hayas ajustado el valor de pan0.
* **gps_baud:** Es el valor de los baudios a los que se va a recibir los datos del GPS local. Los valores soportados son los mismos que para telemetry_baud.
* **gps_provider:** Puede tomar los valroes NMEA o UBLOX.
* **home_min_sats:** Es el número de satélites mínimo a partir del cual se establece la posición HOME. Si el número de satélites es menor que ese número, no se activará la posición HOME. Este parámetro afecta tanto si la posición HOME es tomada a partir de los datos de telemetría de entrada, como si se toma del GPS local cuando está activado.

# Documentos gráficos
---------------------------------
Vídeos realizados por el compañero Guillesan, realizando las primeras pruebas de campo con protocolo Mavlink (a bordo del aeromodelo un autopiloto MyFlyDream transmitiendo telemetría Mavlink con OpelrsGitsly sobre enlace de 868 Mhz a 9600 baudios):

[![ScreenShot](http://i.ytimg.com/vi/ApSv6SFkbRE/mqdefault.jpg)](https://www.youtube.com/watch?v=BrhzeVH2iJo)
[![ScreenShot](http://i.ytimg.com/vi/BrhzeVH2iJo/mqdefault.jpg)](https://www.youtube.com/watch?v=ApSv6SFkbRE)
---------------------------------
Para obtener más información visita el foro:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


