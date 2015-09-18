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
* Settings on LOCAL GPS, LCD DISPLAY and BATTERY MONITORING, will not take effect in this release.

Please, be quite carefully using this feature, it is only for experimental use.
---------------------
# Instrucciones de Uso:

# Número de Versión

El número de versión 0.7, para que no haya confusión. Yo, de momento, me limitaría a subirla a la placa con los servos desconectados, por lo que pueda pasar.

Si habéis usado alguna vez el CLI de una Naze32 con Baseflight, veréis que me he inspirado ligeramente en su forma de proceder.

Aunque todos los parámetros son configurables, los relacionados con LCD, monitorización de la batería y gps local no tendrán efecto sobre el tracker, pues aún están por implementar. Los que sí tienen efecto los he dejado todos comentados en el config.h

# Primer Inicio

La primera vez que se inicia la controladora tras la carga del firmware, entrará automáticamente en modo CLI. El motivo es simple, los valores por defecto son cargados automáticamente y podría provocar que los servos se activen, sobre todo si no son los mismos con los que se diseñó el software, en especial el PAN, que se pondría poner a girar sin parar.

La consola espera nuestras órdenes, per oantes de nada recomiendo activar el retorno de carro y el line feed en la consola.

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
Al salvar la controladora hace un pseudo reinicio, realiza la carga de los parámetros, e inicia el LCD, los servos, etc... En este inicio ya no entramos en el modo CLI, dejándose de mostrar información por la consola.

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

* Mostrar el listado de características activadas (entre ellas: lcd, easing, gps local, monitor de batería y servotest.
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

# Efecto Easing en Servo Tilt
	
* set easing=1 para usar la función out- quart
* set easing=2 para usar la función out-circ
* set easing=0 para desactivarlo (o también feature easing) 
	
# Funcionamiento Verificado

En estos momentos se han verificado el funcionamiento correcto cuando configuramos cualquiera de las siguientes características/parámetros:

* servotest: tras activar la característica y salvar entra en este modo y se puede enviar comandos para mover los servos, etc...
* P,I,D: configurables y tienen efecto tras salvar.
* tilt0, tilt90: el cambio de los parámetros surte efecto tras salvar.
* easing, easing_steps, easing_min_angle, easing_milis: aparentemente se aplican bien.
* pan0: se aplica correctamente.
* min_pan_speed: funciona, aunque aún no acepta valores negativos (en algunos modelos de servos es necesario meter valores negativos para que funcione bien).
* offset: se aplica correctamente.
---------------------
Para obtener más información visita el foro:

[http://www.aeromodelismovirtual.com/showthread.php?t=34530](http://www.aeromodelismovirtual.com/showthread.php?t=34530)


