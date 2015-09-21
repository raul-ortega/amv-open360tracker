# amv-open360tracker v0.7
---------------------
# EXPERIMENTAL (Úsala bajo tu propio riesgo/Use it under your own risk).

Versión derivada de la [versión master](https://github.com/raul-ortega/amv-open360tracker) del Seguidor de Antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530).

# Nueva Interfaz de Línea de Comandos (Command Line Interface, o CLI)

Permite la modificación de los parámetros de configuración desde consola serie.

---------------------
New CLI feature (Command Line Interface) added. It allows setting up the parámeters throught the serial com terminal.
Pleas, use this version in your opent360tracker under your own risk.

* To enter in CLI mode key in ### and press enter
* Key in help and press Enter to see a list of available commands
* Settings on LOCAL GPS and BATTERY MONITORING, will not take effect in this release.

Please, be quite carefully using this feature, it is only for experimental use.

---------------------
# Instrucciones de Uso:

Antes de su utilización, tenga en cuenta lo siguiente:

* El número de versión es 0.7 para que no haya confusión con la versión master (v0.5). 
* Se recomienda subir el firm a la controladora con los servos desconectados.
* Al cargarse los parámetros por defecto, éstos podrían no ser adecuados para sus servos, podría haber una respuesta no esperada al inicio.
* Este CLI está inspierado en el de Basefilght para Naze32, si estás familiarizado con él te será más fácil usarlo.
* Algunos parámetros no están implementados en el config.h. Estos son: DEBUG, MEGA, los protocolos y BAUDS (bauidos para el puerto serie). Es por tanto necesario modificar el config.h para modificarlos.
* Se puede interactuar con el CLI con la herramienta Monitor serie del IDE de Arduino. La consola espera nuestras órdenes, pero antes de se recomienda activar el retorno de carro y nueva línea en la consola. También es posible interactuar con el CLI utilizando otras herramientas, como por ejemplo Hércules.
* Esta versión solo soporta tipo LCD Display de tipo I2C, ya no está soportado el tipo SPI.

# Primer Inicio

La primera vez que se inicia la controladora tras la carga del firmware, entrará automáticamente en modo CLI. El motivo es simple, los valores por defecto son cargados automáticamente y podría provocar que los servos se activen, sobre todo si no son los mismos con los que se diseñó el software, en especial el PAN, que se pondría poner a girar sin parar.

Así que lo primero es teclear help y luego pulsar enter. Nos aparecerá un listado con todos los comandos disponibles. Los que lleven un asterisco delante no funcionan.

# Modificar parámetros

Si tecleamos set y pulsamos enter, mostrará un listado de todos los parámetros disponibles y su valor en la forma:

* set parámetro=valor

No hay mucho que explicar aquí, basta con teclear exactamente el comando completo del parámetro que queremos configurar, cambiando únicamente el valor (los comandos se teclean en minúsculas siempre).

Por ejemplo, si quiero poner la P de los PIDs a 400:

* set P=400

y pulsamos enter.

Para ver si el parámetro se ha modificado, tecleamos set y pulsamos enter, mostrándose todos los parámetros nuevamente.

# Salvar los cambios

Para que los cambios realizados en la configuraicón tengan efecto, hay que salvarlos primero. Para ello tecleamos save y pulsamos enter. Todos los parámetros serán guardados permanentemente en la EEPROM, así que, aunque quitemos la alimentación, estos se cargarán en el próximo inicio.
Al salvar la controladora hace un pseudo reinicio, realiza la carga de los parámetros, e inicia el LCD (si está habilidada la característica), los servos, etc... En este inicio ya no entramos en el modo CLI, dejándose de mostrar información por la consola.

# Entrar en modo CLI

Para volver a entrar en el modo CLI, tenemos que teclear ### y pulsar enter. La consola espera nuevamente a que enviemos comandos.

Estando en este modo por segunda vez, y en sucesivas veces, el tracker no dejará de realizar su cometido, seguirá en funcionamiento.

Los cambios no tendrá efecto sobre el tracker hasta que no hagamos save nuevamente, tras lo cual se producirá un reinicio. No es por tanto neceario recalcar la importancia de:

No salvar los cambios mientras se está haciendo uso del tracker y tenemos el avión en vuelo.

# Configuración por defecto

Para volver a los valores por defecto de los parámetros de configuración, teclear defaults y pulsar enter.

Si hacemos uso a continuación del comando set, veremos que los parámetros por defecto se han cargado.

Una vez más, es necesario hacer un save para que los parámetros por defecto se guarden, el tracker se reinicie y tengan efecto sobre él.

# Comando feature

Este comando tiene triple función:

* Mostrar el listado de características activadas.
* Activar una característica
* Desactivar una característica.

Tecleando feature y pulsando enter, muestra la lista de las que están activadas.

Tecleando feature y el nombre de la característica y pulsando enter, esta se activará si no lo estaba, o bien se desactivará si lo estaba.

Esta función de activar/esactivar la característica también se puede realizar con el correspondiente comando set, por ejemplo, los siguientes dos comandos son equivalentes:

* set servotest=1
* feature servotest

suponiendo que esté desactivada.

Para desactivarla podemos ejecutar cualquiera de los dos siguientes:

* set servotest=0
* feature servotest

Las características que se pueden activar y desactivar con el comando feature son:

* bat
* easing
* gps
* lcd
* servotest

# Efecto Easing en Servo Tilt
	
* set easing=1 para usar la función out- quart
* set easing=2 para usar la función out-circ
* set easing=0 para desactivarlo (o también feature easing) 
	
# Parámetros configurables

Esta es la lista completa de los parámetros que pueden ser configurado mediante el comando set:

* servotest: Puede tomar valores 0 (desactivado) o 1 (activado). Tras hacer un save, el tracker entrará en un modo que permite enviar comandos para mover los servos (ángulos o pulsos) y testear distiontos valores de PIDs.
* P,I,D: El valor de los valores PID (admite solo múltipos de 10, de 0 a 2550).
* tilt0: Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 0 (admite solo múltipos de 10, de 0 a 2550).
* tilt90: Valor del pulso en milisegundos para que el servo tilt se posicione en el ángulo 90 (admite solo múltipos de 10, de 0 a 2550).
* easing: Puede tomar valores 0 (desactivado), 1 (efecto easing out-quart) ó 2 (efecto easing out-circ). Cuando está activo (valores 1 ó 2) el servo de tilt se mueve acelerando al principio del movimiento, y desacelarando al alcanzar el ángulo final, consiguiendo así un efecto de amortiguación. Muy útil si usas antenas muy pesadas.
* easing_steps: Número de pasos (movimientos) para alcanzar el ángulo final aplicando el efecto de amortiguación.
* easing_min_angle: Es el valor en grados del ángulo mínimo a partir del cual se aplicará el efecto easing cuando está activado.
* easing_milis: es el tiempo en milisegundos que el sistema se espera entre paso y paso cuando el efecto easing está ctivado.
* pan0: Valor del pulso en milisegundos para que el servo pan se detenga (admite solo múltipos de 10, de 0 a 2550).
* min_pan_speed: Si el servo de pan tiene problemas para iniciar la rotación cuando la velociad es baja, ajusta este valor hasta que el tracker se mueva de forma directa desde cada posición (acepta valores de -199 a 199).
* offset: Si montas la placa controladora de modo que no apunte hacia el frente, ajusta este valor tantos grados como sea necesario. Para indicar 90 grados, es necesario introducir el valor 900 (adminte valores múltipos de 10 entre 0 y 2550). 
* lcd: Puede tomar valores 0 (desactivado) o 1 (activado). Tras hacer un save el tracker se reinicia y el display se apagará o encenderá en función de su valor.
* lcd_rows: número de filas del LCD display (valores admitidos 2 ó 4).
* lcd_addr: es la dirección I2C del LCD display. Sólo admite valores en sistema dedicmal (base 10). Para los valores hexadecimales típicos usad:
	- 0x20 --> 32
	- 0x27 --> 39
	- 0x3F --> 63
* start_track_dist: es la distancia a partir de la cual el tracker empieza a apuntar al aeromodelo (adminte valores entre 0 y 255).
* declination: es el valor de la declinación magnética. Visita [http://magnetic-declination.com/](http://magnetic-declination.com/), introduce tu ciudad y obtendrás el valor de la declinación magnética. Por ejemplo, 3° 2' Este, lo pasamos a formato grados.minutos *10 -> 3.2 * 10 = 32. Si no sabes el valor exacto déja esta parámetro a 0. (adminte valores entre 0 y 255).

---------------------
Para obtener más información visita el foro:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


