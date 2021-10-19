//Find the lenght of an ARRAY
function lenght(array) {
	var len = 0;
	array.forEach(function (item) {
		len++;
	})
	return len
}

//Format a string
function format(stringa, array_parametri) {
    var counter = 0;
    var stringa_out = stringa;

    array_parametri.forEach(function (item) {
        if (typeof (item) == "string") {
            var expr = "{" + counter + "}";
            if (stringa.includes(expr)) {
                stringa_out = stringa_out.replaceAll(expr, item);
            } else {
                return "errore";
            }
        } else {
            return "errore";
        }

        counter++;
    });

    return stringa_out;

}