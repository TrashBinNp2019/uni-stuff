/** 
 * Given lottery ticket and a lower bound for winning, return 'Winner!' if the ticket is a winner, 'Loser!' otherwise.
 * Ticket follows the following format: each ticket is an array of pairs: a string and a number.
 * A pair is considered winning if and only if at least a single character in a string has the same charcode, as a number from the pair
 * Ticket is winning if and only if at least $win pairs are winning.
 * @param {{string, number}[]} ticket Lottery ticket.
 * @param {number} lowerBound Lower bound for winning.
 */
function bingo(ticket, win){
  function subarray(str, num) {
    for (let c of str) {
      if (c.charCodeAt(0) === num) return true;
    }
    return false;
  }
  console.log(ticket.reduce((sum, sub) => sum + subarray(sub[0], sub[1]), 0));
  return ticket.reduce((sum, sub) => sum + subarray(sub[0], sub[1]), 0) >= win? 'Winner!' : 'Loser!';
}