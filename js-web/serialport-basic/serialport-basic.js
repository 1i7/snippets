// https://github.com/EmergingTechnologyAdvisors/node-serialport#usage
var SerialPort = require('serialport');

port = new SerialPort("/dev/ttyUSB0", {
    // скорость
    baudRate: 9600,
    //baudRate: 115200,
    // получать данные по одной строке
    parser: SerialPort.parsers.readline('\n'),
    //parser: SerialPort.parsers.ReadLine,
    // не открывать порт сразу здесь
    autoOpen: false,
    lock: true
});

function writeData(data) {
    console.log("write: " + data);
    port.write(data,
        function(err) {
            if(!err) {
                // данные ушли ок
                console.log("write ok");
            } else {
                // ошибка записи в порт 
                // (например, порт открыт, но не хватает прав на запись)
                console.log("write error: " + err);
            }
        }
    );
    
    // после первого вызова повторять бесконечно в цикле
    //setTimeout(writeData, 1000);
}

// 
// События
// 

// порт открылся
port.on('open', function () {
    console.log("open");
    
    // теперь будем слать команду каждые 2 секунды
    setInterval(function() {writeData("ping");}, 2000);
});

// пришли данные
port.on('data', function(data) {
    console.log("data: " + data);
});

// отключили устройство (выдернули провод)
port.on('disconnect', function () {
    console.log("disconnect");
});

// 
// Действия
//

// открываем порт
port.open(function(err) {
    if(err) {
        // не получилось открыть порт
        console.log("Error opening: " + err);
    } else {
        console.log("Open OK");
        //setInterval(function() {writeData("ping");}, 1000);
    }
});

