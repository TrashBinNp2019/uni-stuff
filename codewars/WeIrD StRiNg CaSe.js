/**
 * Converts string to weird case: letter itterate between upper and lower case, beggining with upper case in each word.
 * - This is a test -> ThIs Is A TeSt.
 * @param {string} string String to convert. Should only contain letters and spaces.
 * @returns Given string in weird case.
 */
function toWeirdCase(string){
  return string.split(' ').map(str => [...str].map((val, ind) => {
    return ind % 2 === 0? val.toUpperCase() : val.toLowerCase();
  }).join('')).join(' ');
}