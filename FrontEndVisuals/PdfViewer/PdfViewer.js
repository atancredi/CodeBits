
var url = "http://192.168.2.84/owexpress/PDF/2021/2021-09-21/2021092149603785.pdf";

pdfjsLib.GlobalWorkerOptions.workerSrc = '//mozilla.github.io/pdf.js/build/pdf.worker.js';

//core della funzione rendering
function CoreRendering(page, pageNumber, pdfPath) {

    console.log(page["_transport"]["_numPages"]); //numero pagine

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

        switch (pageNumber) {

            case 1: //mostro solo il next
                next.addClass("pdf_button");
                break;

        }

        //Aggiungere qui gli handlers
        prev.on("click", function (e) {

        });

        next.on("click", function (e) {
            WrapRendering(pdfPath, pageNumber + 1)
        });

    });
}

//funzione wrapper del rendering
function WrapRendering(pdfPath, pageNumber) {
    var loadingTask = pdfjsLib.getDocument(pdfPath);

    loadingTask.promise.then(function (pdf) {

        pdf.getPage(pageNumber).then(function (page) { CoreRendering(page, pageNumber, pdfPath) });

    }, function (reason) {
        console.error(reason);
    });
}

//distruttore della canvas
function DestroyRendering() {

}

WrapRendering(url, 1);