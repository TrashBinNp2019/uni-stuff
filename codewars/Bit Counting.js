/**
 * Function that takes an integer as input, and returns the number of bits 
 * that are equal to one in the binary representation of that number. 
 * - Input is guaranteed non-negative.
 * @param {number} n Integer to count bits in.
 * @returns {number} Number of bits that are equal to one in the binary representation of that number.
 */
function countBits(n) {
  let res = 0;
  do {
    res += n % 2;
    n -= n % 2;
    n /= 2;
  } while (n > 0);
  return res;
};