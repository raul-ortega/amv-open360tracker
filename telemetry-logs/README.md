# ¿Cómo utilizar los archivos .log?

Los archivos .log que encuentras en esta carpeta contienen capturas de datos de telemetría de los distintos protocolos. Estos archivos se pueden usar para hacer pruebas con nuestro tracker si no disponemos de la fuente de telemetría correspondiente al protocolo que queremos testear.

## ¿Qué necesitamos?

* Un adaptador USB-FTDI para conectar la controladora, en el caso de la crius se, o bien tener conectados el ordenador y el amv-open360tracker a través de bluetooth. En el caso de tener un Arduino sólo necesitamos su cable USB para conectarlo directamente al ordenador.
* En el archivo config.h del firmware del amv-open360tracker debemos definir los baudios a los que vayamos a transmitir, y el protocolo que queremos testear. Por ejemplo:

	`#define LTM`
	
	`#define BAUDS 9600`

* Un programa de comunicaciones serie que permita el envío de archivos, como por ejemplo [Hércules](http://new.hwg.cz/files/download/sw/version/hercules_3-2-8.exe).

## ¿Cómo enviar el archivo?

Los pasos a seguir son:

    1.- Enchufar el cable usb al ordenador, o conectamos los módulos bluetooth.
    2.- Suministrar alimentación al tracker.
    3.- Abrir hércules.
    4.- Hacer clic en la pestaña Serial.
    5.- Modificar los parámetros de comunicación:
		Name: 		COM8 (suponiendo que COM8 sea el puerto que se corresponde al adaptador UBS-FTDI / Bluetooth)
		Baud: 		9600 (suponiendo que en el confi.h se ha definido #define BAUD 9600)
		Data size:	8
		Parity: 	none
		Handshake: 	OFF
		Mode: 		Free
    6.- Hacer clic en el botón Open.
		Debería aparecer en verde "Serial COM8 opened".
	7.- Pulsamar las tecla CTROL + O (letra O, el símbolo + no se pulsa)
    8.- Seleccionamos el archivo que quermos enviar.
	9.- Hacer clic en el botón Abrir.

Aparecerá una pequeña ventana con el mensaje Sending file, la ruta completa del archivo que se está enviadno, los bytes enviados, y una barra de progreso.

Cuando termine se puede hacer clic en el botón Close para cerrar la conexión, o enviar el archivo nuevamente si se desea. 