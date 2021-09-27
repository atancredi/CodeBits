//Find the lenght of an ARRAY
function lenght(array) {
	var len = 0;
	array.forEach(function (item) {
		len++;
	})
	return len
}

//Test if an OBJECT/ARRAY and every other OBJECTs/ARRAYs inside are empty
function testArray(arr) {

	function arrayControl(arr) {
		if (typeof (arr) == "object" && Array.isArray(arr)) return true;
		else return false;
	}

	function objectControl(arr) {
		if (typeof (arr) == "object" && !(Array.isArray(arr))) return true;
		else return false;
	}

	var flag = true;

	function iteration(arr) {
		if (arrayControl(arr)) {

			for (var i = 0; i < lenght(arr); i++) {
				if (arrayControl(arr[i]) || objectControl(arr[i])) {
					iteration(arr[i]);
				}

				else {
					flag = false;
					break;
				}

			}

		} else if (objectControl(arr)) {

			var entries = Object.entries(arr);
			for (var i = 0; i < lenght(entries); i++) {

				if (arrayControl(entries[i][1]) || objectControl(entries[i][1])) {
					iteration(entries[i][1]);
				}

				else {
					flag = false;
					break;
				}
			}
		}

		else {
			flag = false;
		}

		return flag;

	}

	if (typeof (arr) === "object") {

		var result = iteration(arr);
	}

	return result;

}