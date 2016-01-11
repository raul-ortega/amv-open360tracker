# amv-open60tracker-32bits v1.1.0
---------------------------------
# EXPERIMENTAL (Úsala bajo tu propio riesgo/Use it under your own risk).

Esta es la versión de 32bits del Seguidor de Antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530).

Por favor, antes de usar este software, lea atentamente las siguientes notas y las instrucciones de instalación que se detallan más abajo.

# Plataforma Hardware

Esta nueva versión, completamente experimental, soporta controladoras de 32bits basadas en **Naze32**. Actualmente se ha probado el firmware sobre la popular controladora **Flip32**, que incorpora su propio magnetómetro.

También es posible que pueda funcionar sobre otras controladoras basadas en Naze32 sin magnetómetro, siendo necesario por tanto la conexión de un magnetómetro externo. Bajo estas circustancias el firmware aún no ha sido testado.

En esta versión preliminar, no se hace uso de LCD ni de GPS Local. Además, los botones de calibración y home no han sido implementados aún.

# Protocolos de telemetría soportados

En estos momentos, el único protocolo de telemetría implementado es el protocolo **MFD**.

El protocol **SERVOTEST no está implementado** aún, aunque en breve habrá una nueva versión disponible que implementará algunas de sus funciones. No obstante, por las nuevas características que incorpora la versión actual, algunas de las funciones de SERVOTEST ya no serán necesarias, pues están implícitas en en algunas de sus nuevas funcionalidades.

# Interfaz de Línea de Comandos: modo CLI 

A efectos de configuración, ésta es la principal **novedad** que incorpora esta nueva versión, característica que se ya se había implemetnado en una de las versiones del firmware para plataformas basadas en Arduino, la cual no tuvo continuidad por falta de memoria en los procesadores atmega328p.

La **mejora** tras la incorporación de esta interfaz de línea de comandos es que **ya no será necesario compilar el código y subirlo a la controladora** cada vez que se modifique un parámetro, con todas las ventajas que ello conlleva. Tan sólo será necesario subir una única vez el firmware, o cuando haya alguna actualización importante.

Además, los parámetros de configuración pueden ser guardados en un archivo de texto, los cuales pueden ser transferidos en cualquier momento a la controladora a través de consola serie, sin necesidad de teclear un solo comando, salvo que queramos modificar algún parámetro de forma puntual o en el caso de la primera instalación.

Este CLI está inspirado en el CLI basefilght y cleanflight para Naze32, si estás familiarizado con él te será más fácil usarlo.

# Instrucciones de intalación

**Preparación**

- Para esta versión reliminar la instalación de la controladora es muy sencilla, en especial si ya eres usuario de la versión de 8bits.

- El firm se subirá a la controladora usando el programa [Flash Loader Demonstrator](https://code.google.com/p/afrodevices/downloads/detail?name=stm32-stm8_flash_loader_demo.zip&can=2&q=) de STMicroelectronics, tal y como se explica en el [manual de la NAZE32](http://www.abusemark.com/downloads/naze32_rev3.pdf).

- Para comunicarnos con la controladora en modo CLI, podemos usar cualquier software de consola serie. Podemos usar [Hércules](http://new.hwg.cz/files/download/sw/version/hercules_3-2-8.exe), que ya lo conoce nuestra comunidad y que nos permite copiar, pegar, volcar hacia/desde un archivo... 

- En cualquier caso, vamos a necesitar un **cable Micro USB** para **subir por primera vez el firmware a la controladora**, y para comunicarnos vía interfaz de línea de comandos para la **primera configuración**.

- Necesitarás **soldar los pines** para **motores/servos**, **boot** y **uart1**, según se indica en la imagen.

- Ten a mano un jumper para colocar en los pines boot, pues lo necesitarás para subir por primera vez el firware.

- La controladora se alimentará por los pines GND y +5V a donde mismo se conectan los motores/servos de la controladora.

- En esta versión tan sólo necesitaremos **conectar los dos servos** de 360º con giro contínuo, y conectar al **puerto uart1** el dispositivo serie a través del cual se recibirán los datos de telemetría.

**Se recomienda no conectar los servos la primera vez, hasta que no nos hayamos familiarizado con la forma de configurar los parámetros**.

- Una vez configurada instalada la controladora, conectados los servos y el dispositivo serie para la recepción de telemetría, el cable Micro USB ya no será necesario, salvo que necesitemos subir nuevamente el firmware.

- Si eres usuario de de la versión de 8 bits, y vas a probar esta versión de 32bits, **ten a mano los valores de los parámetros de configuración del config.h.**, pues vamos a usar algunos de esos valores.

![Flip32](https://github.com/raul-ortega/amv-open360tracker/blob/master/32bits/amv-open360tracker-Flip32.png)

**Parámetros de configuración**

Antes de continuar, tómate tu tiempo y copia todas estos comandos e instrucciones en un archivo de texto y sálvalo.

Luego sustituye los valores de los parametros por los equivalentes del archivo config.h de la versión de 8bits (Si es la primera vez que te acercas al proyecto, más abajo se explica que es cada parámetro):

```
# dump configuration

# feature
feature EASING

set p = 2500
set i = 20
set d = 250
set max_pid_error = 10
set pan0 = 1528
set min_pan_speed = 0
set offset =  90
set tilt0 = 1125
set tilt90 = 2025
set easing = 1
set easing_steps = 10
set easing_min_angle = 4
set easing_milis = 15
```

Cuando la controladora se inicia por primera vez tras la carga del firmware, los valores por defecto son cargados automáticamente y podría provocar que los servos se activen, sobre todo si no son los mismos con los que se diseñó el software, en especial el PAN, que podría provocar que el servo se pusiera a girar a alta velocidad sin parar.

Si preparamos los valores para cada parámetro y los cargamos a través del CLI antes de conectar los servos, una vez conectados y conectar alimentación sólo debería moverse el servo pan un instante y pararse, quedando el tracker a espera de telemetría MFD u órdenes vía CLI.

# Carga del firmware

Sigue con exactitud estos pasos para instalar el firmware en la controladora.

El firmware puedes descargarlos desde aquí: [amv-open360tracker-32bits-v1.1.0]()

```
1.- Coloca el jumper en los pines boot
2.- Conecta el cable Micro USB a la controladora y al PC
3.- Abre el programa Flash Loader Demonstrator
4.- Sigue las instrucciones del modo boot del manual de la NAZE32
5.- Cierra el programa Flash Loader Demonstrator
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

    Name(Puerto): **COM8**
    Baud: **9600**
	Data size: **8**
    Parity: **none**
    Handshake: **OFF**
    Mode: **Free**

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
	
	¡Enhorabuena, tu tracker ha sido configurado!.

# Comandos del modo CLI

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

# Efecto Easing en Servo Tilt
	
* set easing=**1** para usar la función **out- quart**
* set easing=**2** para usar la función **out-circ**
* set easing=**0** para **desactivarlo** (además es necesario ejecutar feature -easing) 
	
# Parámetros configurables

Esta es la lista completa de los parámetros que pueden ser configurado mediante el comando set:

* **P,I,D:** El valor de los valores PID (admite solo múltipos de 10, de 0 a 2550).
* **tilt0:** Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 0 (admite solo múltipos de 10, de 0 a 2550).
* **tilt90:** Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 90 (admite solo múltipos de 10, de 0 a 2550).
* **easing:** Puede tomar valores 0 (desactivado), 1 (efecto easing out-quart) ó 2 (efecto easing out-circ). Cuando está activo (valores 1 ó 2) el servo de tilt se mueve acelerando al principio del movimiento, y desacelarando al alcanzar el ángulo final, consiguiendo así un efecto de amortiguación. Muy útil si usas antenas muy pesadas.
* **easing_steps:** Número de pasos (movimientos) para alcanzar el ángulo final aplicando el efecto de amortiguación.
* **easing_min_angle:** Es el valor en grados del ángulo mínimo a partir del cual se aplicará el efecto easing cuando está activado.
* **easing_milis:** es el tiempo en milisegundos que el sistema se espera entre paso y paso cuando el efecto easing está ctivado.
* **pan0:** Valor del pulso en milisegundos para que el servo pan se detenga (admite solo múltipos de 10, de 0 a 2550).
* **min_pan_speed:** Si el servo de pan tiene problemas para iniciar la rotación cuando la velociad es baja, ajusta este valor hasta que el tracker se mueva de forma directa desde cada posición (acepta valores de -199 a 199).
* **declination:** es el valor de la declinación magnética. Visita [http://magnetic-declination.com/](http://magnetic-declination.com/), introduce tu ciudad y obtendrás el valor de la declinación magnética. Por ejemplo, 3° 2' Este, lo pasamos a formato grados.minutos *10 -> 3.2 * 10 = 32. Si no sabes el valor exacto déja esta parámetro a 0 (adminte valores entre 0 y 255).
* **offset:** Si montas la placa controladora de modo que no apunte hacia el frente, ajusta este valor tantos grados como sea necesario. Para indicar 90 grados, es necesario introducir el valor 900 (adminte valores múltipos de 10 entre 0 y 2550).
* **gps:** Puede tomar valores 0 (desactivado) o 1 (activado).
* **gps_model:** Pude tomar los valores 0 (gps genérico), 1 (gps MTK), 2 (DIY gps).
* **gps_bauds:** Los valores recomendados son 4800 ó 9600 (admite valores entre 0 y 25500).
* **start_track_dist:** es la distancia a partir de la cual el tracker empieza a apuntar al aeromodelo (adminte valores entre 0 y 255).
* **lcd:** Puede tomar valores 0 (desactivado) o 1 (activado). Tras hacer un save el tracker se reinicia y el display se apagará o encenderá en función de su valor.
* **lcd_rows:** número de filas del LCD display (valores admitidos 2 ó 4).
* **lcd_addr:** es la dirección I2C del LCD display. Sólo admite valores en sistema dedicmal (base 10). Para los valores hexadecimales típicos usad:
	- 0x20 --> 32
	- 0x27 --> 39
	- 0x3F --> 63
* **lcd_model:** Este parámetro no se usa.
* **bat:** Puede tomar los valores 0 (desactivado) ó 1 (activado). Cuando está activo, el tracker monitorizará el voltaje de la batería.
* **bat_res1:** Valor de la resistencia R1 del divisor de tensión. Sólo admite valores múltipos de 100 entre 0 y 25500. Ejemplo, 18000 = 18 Kohmios.
* **bat_res2:** Valor de la resistencia R2 del divisor de tensión. Sólo admite valores múltipos de 100 entre 0 y 25500. Ejemplo,  1000 =  1 Kohmios.
* **bat_corr:** Valor de correción para ajustar el divisor de tensión. Admite valores entre 0 y 255. El valor introducido será divido entre 10. Por ejemplo para indicar un factor de correción 1.1 introducir set bat_corr=11.
* **servotest:** Puede tomar valores 0 (desactivado) o 1 (activado). Tras hacer un save, el tracker entrará en un modo que permite enviar comandos para mover los servos (ángulos o pulsos) y testear distiontos valores de PIDs.

---------------------
Para obtener más información visita el foro:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


