let CollisionDetect = {};

/**	intersectsWith
 *	@param	rectangle1	x, y, width, height
 *	@param	rectangle2	x, y, width, height
 *	@returns true if they intersect, false otherwise
 */
CollisionDetect.intersectsWith = function(rectangle1, rectangle2) {
	return !(rectangle2.x > rectangle1.x + rectangle1.width ||
			 rectangle2.x + rectangle2.width < rectangle1.x ||
			 rectangle2.y > rectangle1.y + rectangle1.height ||
			 rectangle2.y + rectangle2.height < rectangle1.y);
}