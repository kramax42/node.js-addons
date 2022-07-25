let addon = require('bindings')('addon');

function printMessage(msg) {
  console.log(msg);
}

addon(printMessage);
