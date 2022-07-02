/**
 * Simple function to check if a number is prime.
 * - Not optimized.
 * @param {number} num Number to check 
 * @returns True if number is prime, false otherwise.
 */
function isPrime(num) {
  if (num <= 1) return false;
  if (num == 2 || num == 3) return true;
  if (num % 2 === 0) return false;
  
  for (let i = 3; i <= Math.ceil(Math.sqrt(num)); i += 2) {
    if (num % i === 0) return false
  }
  
  return true;
}