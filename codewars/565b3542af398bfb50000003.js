/**
 * Create a function strCount (takes an object as argument) that will count all string values inside an object.
 * Do NOT copy: the code does NOT represent the best practices.
 * @param {*} obj Object to count strings in.
 * @returns Number of params within the object that are strings.
 */

function strCount(obj){
    console.log(obj);
    if(Array.isArray(obj)){
      return obj.reduce((ps, val) => ps + strCount(val), 0);
    } else if (obj !== null && obj !== undefined) {
      if (typeof(obj) === 'object') {
        return strCount(Object.entries(obj)) - Object.entries(obj).length;
      } else { 
        return typeof(obj) === 'string'? 1 : 0; 
      };
    } return 0;
  }