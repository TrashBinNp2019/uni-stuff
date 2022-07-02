/**
 * A function, that generates a bingo card.
 * @returns An array of 'Bingo style' numbers: ['B1', ..., 'I15', ..., 'N31', ..., 'G46', ..., 'O60', ...]
 */
function getCard() {
  /**
   * Function, generating a row of 'Bingo style' numbers.
   * @param {string} letter The letter of the row: 'B' or 'I' or 'N'....
   * @param {number} length The length of the row. Normally 4 for I and 5 for other letters.
   * @param {number} from Bottom boundry for random numbers in the row.
   * @param {number} to Top boundry for random numbers in the row.
   * @returns {string[]} A 'Bingo stryle' row of numbers.
   */
  function generateARow(letter, length, from, to) {
    let res = [];
    let val = 0;
    for (let i = 0; i < length; i++) {
      do {
        val = Math.floor(Math.random() * (to - from + 1) + from);
      } while (res.indexOf(val) !== -1)
    res = [...res, val];
    }
    return res.map(num => { return letter + num });
  }
  
  let B = generateARow('B', 5, 1, 15);
  let I = generateARow('I', 5, 16, 30);
  let N = generateARow('N', 4, 31, 45);
  let G = generateARow('G', 5, 46, 60);
  let O = generateARow('O', 5, 61, 75);
  return [...B, ...I, ...N, ...G, ...O];
}