

function nspClone(obj) {
  if (obj === null || typeof (obj) !== 'object')
    return obj;

  var temp = obj.constructor(); // changed

  for (var key in obj) {
    temp[key] = nspClone(obj[key]);
  }


  return temp;
}