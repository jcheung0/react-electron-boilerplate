var addon = require('./build/Release/helloworld.node');


var obj = new addon.MyObject(10);
console.log(obj.plusOne());

console.warn(addon.register());
console.warn( addon.add(1,2));

console.warn(addon);
