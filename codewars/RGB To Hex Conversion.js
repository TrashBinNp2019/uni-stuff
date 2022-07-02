/**
 * Converts RGB color to a hex string.
 * @param {number} r Red value.
 * @param {number} g Green value. 
 * @param {number} b Blue value.
 * @returns {string} Corresponding hex string.
 */
function rgb(r, g, b){
  return convert(r) + convert(g) + convert(b);
}

/**
 * Given a number, converts it to hex string with 2 digits.
 * @param {number} val Number to convert.
 * @returns {string} Hex string.
 */
function convert(val) {
  if (val > 255) return ('FF');
  if (val < 0) return ('00');
  return val.toString(16).toUpperCase().padStart(2, '0');
}