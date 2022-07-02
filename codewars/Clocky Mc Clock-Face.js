/**
 * Given angle of a clock hour hand, return current time.
 * @param {number} angle Angle in degrees 0-360.
 * @returns Current time, based on the angle of the hour hand.
 */
function whatTimeIsIt(angle) {
  let minutes = Math.floor(angle * 2);
  return `${Math.floor(minutes / 60).toString().padStart(2,'0')}:${(minutes % 60).toString().padStart(2,'0')}`.replace("00:", "12:");
}