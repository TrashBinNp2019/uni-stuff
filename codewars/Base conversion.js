/**
 * This function implements a base converter, which converts positive integers between arbitrary bases/alphabets.
 * Do NOT copy: the code does NOT represent the best practices.
 * @param input Input string in source base/alphabet.
 * @param source Base/Alphabet to convert from.
 * @param target Base/Alphabet to conbvert to.
 * @returns String in target base/alphabet.
 */
function convert(input, source, target) {
    let val = 0;
    for (let deg = input.length - 1; deg >= 0; deg--) {
      val += source.indexOf(input[input.length - deg - 1]) * Math.pow(source.length, deg);
    }
     
    let res = "";
    let deg = val == 0? 0 : Math.floor(Math.log(val) / Math.log(target.length));
    for (deg; deg >= 0; deg--) {
      let buf = Math.floor(val / Math.pow(target.length, deg));
      res += target[buf];
      val -= buf * Math.pow(target.length, deg);
    }
    
    return res;
  }