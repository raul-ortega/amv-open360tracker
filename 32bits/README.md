# amv-open60tracker-32bits v1.6.0
---------------------------------
# EXPERIMENTAL

**Úsala bajo tu propio riesgo/Use it under your own risk.**

Esta es la versión de 32bits del seguidor de antena para FPV con rotación contínua de 360º de la [comunidad española de aeromodelismo virtual](http://www.aeromodelismovirtual.com/showthread.php?t=34530).

Por favor, antes de usar este software lea atentamente esta guía, aquí encontrará detallada toda la información necesaria para poner en marcha su seguirdor de antena con esta versión del firmware. Preste especial atención a las las instrucciones de instalación y las notas de recomendación para no dañar sus dispositivos.

# Plataforma Hardware

Esta nueva versión es completamente experimental, y da soporte a controladoras con microprocesadores STM32F de 32bits basadas en la popular plataforma hardware **Naze32**. Actualmente se ha probado el firmware en la controladora **Flip32** que incorpora su propio magnetómetro.

También es posible que pueda funcionar sobre otras controladoras basadas en Naze32 que no dispongan de magnetómetro integrado en placa, siendo indispensable por tanto la conexión de un magnetómetro externo. Bajo estas circustancias el firmware aún no ha sido testado.

En esta versión preliminar no se hace uso de dispositivo LCD, ni de receptor GPS Local. Además, los botones de calibración y home no han sido implementados aún (la calibración se puede realizar en modo CLI como se explica más adelante).

El objetivo que se persigue con esta primera versión es la realización de pruebas por parte de los usuarios de la comunidad, con el fin de recopilar información derivada de la experiencia en su uso que sirva para determinar la viabilidad del proyecto.

Si decides usar este firmware, hazlo bajo tu propia responsabilidad, pues los dispositivos usados podrían terminar dañados, especialmente si no se siguen las instrucciones y recomendaciones que se dan en este documento.

# Protocolos de telemetría soportados

En estos momentos los protocolos de telemetría implementados son:

- **MFD** 
- **GPS TELEMETRY**
- **MAVLINK**

El resto de protocolos soportados en la versión 8 bits, están en fase de integración en esta nueva versión de 32bits.

**Nota**: El uso de GPS Local aún no está implementado y es necesario activar el botón HOME para iniciar el seguimiento del aeromodelo.

Las funciones equivalentes al procolo **SERVOTEST** están disponibles **desde el modo CLI**, pero ahora se ejecutan de forma distinta.

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
# dump configuration

feature EASING

set p = 2500
set i = 20
set d = 250
set max_pid_error = 10
set pan0 = 1528
set pan0_calibrated = 0
set min_pan_speed = 0
set offset =  90.000
set tilt0 = 1050
set tilt90 = 2025
set easing = 1
set easing_steps = 40
set easing_min_angle = 4
set easing_milis = 15
set telemetry_baud = 2
set telemetry_protocol = 8
set start_tracking_distance = 10
set mag_declination = 0
set init_servos = 0
```

Cuando la controladora se inicia por primera vez tras la carga del firmware, los valores por defecto son cargados automáticamente y podría provocar que los servos se activen, sobre todo si no son los mismos con los que se diseñó el software, en especial el PAN, que podría provocar que el servo se pusiera a girar a alta velocidad sin parar.

Si preparamos los valores para cada parámetro y los cargamos a través del CLI antes de conectar los servos, una vez conectados y conectar alimentación sólo debería moverse el servo PAN un instante y pararse, quedando el tracker a espera de telemetría u órdenes vía CLI.

# Carga del firmware

Sigue con exactitud estos pasos para instalar el firmware en la controladora.

El firmware puedes descargarlo desde aquí: [amv-open360tracker-32bits-v1.3.0](https://github.com/raul-ortega/amv-open360tracker/blob/master/32bits/amv-open360tracker_NAZE-v1.3.0.hex)

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
    Baud: 9600
	Data size: 8
    Parity: none
    Handshake: OFF
    Mode: Free

3.- Pulsamos Open

    Debería aparecer el mensaje "Serial por COM opened" en color verde.

4.- Tecleamos el caracter % y pulsamos enter

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

El tracker girará durante no más de un segundo, y no muy rápido, tras lo que debería detenerse, justo cuando el led azul se queda fijo, indicando que la secuencia de arranque ha finalizado.

Si el tracker continua girando, no debería hacerlo muy rápido, pues hemos configurado el parámetro pan0 a un valor que conocíamos como el centro, es cuestión de ir ajustando ese valor. Para ello:

```
1.- Entrar al modo CLI
2.- Ejecutar comando set pan0=valor
3.- Si el servo no se detiene, volvemso al paso 2 ajustando nuevamente el valor.
4.- Si el servo se detiene, ejecutamos el comando set pan0_calibrated=1
5.- Guardamos con save 
```

**Notas:** 

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

# Selección del protocolo de telemetría

Por defecto, nuestro tracker está configurado con el protocolo GPS TELEMETRY.

Para cambiar de protocolo:

```
1.- Entrar al modo CLI
2.- Ejecutar comando set telemtry_protocol=valor (4 para MFD, y 8 para GPS TELEMETRY)
3.- Configurar los bauidos para la telemetría con set telemetry_baud=valor (ver lista de parámetros al final de este documento)
4.- Guardamos con save 
```

Una vez seleccionado el protocolo, no olvides configurar la uart1 a los bauidos necesarios. Al final de esta lista 

# Comandos del modo CLI
---------------------------------

**Modificar parámetros**

Si tecleamos **set** y pulsamos **enter**, mostrará un listado de todos los parámetros disponibles y su valor en la forma:

* **set parámetro=valor**

Por ejemplo, para configuar el parámetro P de los PIDs a 400:

* set p=400

y pulsamos enter.

Para ver si el parámetro se ha modificado, tecleamos set y pulsamos enter, mostrándose todos los parámetros nuevamente.

Al final de este REAME está la lista completa de parámetros detallada.

**Salvar los cambios**

Para que los cambios realizados en la configuraicón tengan efecto, hay que salvarlos primero. Para ello tecleamos **save** y pulsamos **enter**. Todos los parámetros serán guardados permanentemente en la EEPROM, así que, aunque quitemos la alimentación, estos se cargarán en el próximo inicio.

Al salvar la controladora hace un reinicio, realiza la carga de los parámetros, e inicia todo el hardware, incluidos los servos.

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
	
# Parámetros configurables
---------------------------------

Esta es la lista completa de los parámetros que pueden ser configurados mediante el comando set:

* **p,i,d:** El valor de los valores PID.
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
* **telemetry_protocol:** Inicamos el valor 4 para activar el protocolo MFD, 8 para el protocolo GPS TELEMETRY, y 16 para MAVLINK. 
* **telemetry_baud:** Es el valor de los baudios a los que se va a recibir los datos de telemetría, o los baudios a los que nos comunicamos con el tracker en modo CLI. Por defecto tiene el valor 2 (9600 bauds) y acepta valores entre 1 (4800 bauds) y 6 (250000 bauds).
* **start_tracking_distance:** Es la distancia mínima a partir de la cual el tracker empieza a realizar el seguimiento del aeromodelo.
* **init_servos:** Permite activar/desactivar el inicio de los servos durante el arranque. Si está activado, durante el inicio enviará al servo PAN el pulso de parada (pan0), y en el caso del servo TILT, enviará el pulso para que se mueva ala posición horizontal 0º (tilt0). Por defecto el valor de este parámetro es 0. Si usas una antena muy pesada no se recomienda la activación de este parámetro, salvo que hayas activado y configurado previamente el efecto easing para el servo tilt, y hayas ajustado el valor de pan0.
---------------------
Para obtener más información visita el foro:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


