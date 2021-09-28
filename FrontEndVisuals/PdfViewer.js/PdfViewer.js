var url = "http://192.168.2.84/owexpress/PDF/2021/2021-09-21/2021092149603785.pdf";

var MainSelector = $("#PDFView");

pdfjsLib.GlobalWorkerOptions.workerSrc = '//mozilla.github.io/pdf.js/build/pdf.worker.js';

//core della funzione rendering
function CoreRendering(page, pageNumber, pdfPath) {
    var NumOfPages = page["_transport"]["_numPages"];

    var scale = 1.5;
    var viewport = page.getViewport({ scale: scale });

    var canvas = document.getElementById('pdf');
    var context = canvas.getContext('2d');
    canvas.height = viewport.height;
    canvas.width = viewport.width;

    var renderContext = {
        canvasContext: context,
        viewport: viewport
    };
    var renderTask = page.render(renderContext);
    renderTask.promise.then(function () {

        var prev = $(".pdf_prev");
        var next = $(".pdf_next");
	
	if (NumOfPages > 1)
            switch (pageNumber) {

                case 1: //mostro solo il next
                    if (prev.hasClass("pdf_button")) prev.removeClass("pdf_button");
					if (prev.css("display") != "none") prev.hide();
					
					if(next.css("display") === "none") next.show();
                    next.addClass("pdf_button");

                    prev.off("click");
                    next.off("click");

                    next.on("click", function (e) {
                        WrapRendering(pdfPath, pageNumber + 1);
                        console.log("go to page " + (pageNumber + 1))
                    });
                    return;

                case NumOfPages: //mostro solo il prev
                    if (next.hasClass("pdf_button")) next.removeClass("pdf_button");
					if (next.css("display") != "none") next.hide();
					
					if(prev.css("display") === "none") prev.show();
                    prev.addClass("pdf_button");

                    prev.off("click");
                    next.off("click");

                    prev.on("click", function (e) {
                        WrapRendering(pdfPath, pageNumber - 1);
                        console.log("go to page " + (pageNumber - 1))
                    });
                    return;

                default:
					if(prev.css("display") === "none") prev.show();
					if(next.css("display") === "none") next.show();
				
                    prev.addClass("pdf_button");
                    next.addClass("pdf_button");

                    prev.off("click");
                    next.off("click");

                    prev.on("click", function (e) {
                        WrapRendering(pdfPath, pageNumber - 1);
                        console.log("go to page " + (pageNumber - 1))
                    });

                    next.on("click", function (e) {
                        WrapRendering(pdfPath, pageNumber + 1);
                        console.log("go to page " + (pageNumber + 1))
                    });

                    return;
            }
		else {
			prev.hide();
			next.hide();
		}
        
    });
}

//funzione wrapper del rendering
function WrapRendering(pdfPath, pageNumber) {
    var loadingTask = pdfjsLib.getDocument(pdfPath);

    loadingTask.promise.then(function (pdf) {

        pdf.getPage(pageNumber).then(function (page) {
            DestroyRendering();
            CoreRendering(page, pageNumber, pdfPath);
        });

    }, function (reason) {
        console.error(reason);
    });
}

//distruttore della canvas
function DestroyRendering() {
    $("#pdf").remove();
}

WrapRendering(url, 1);
