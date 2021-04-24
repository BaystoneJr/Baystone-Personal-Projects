'use strict';

(function () {
    let drawpad;
    let context;
    let picture;

    document.addEventListener('DOMContentLoaded', alusta);

    function alusta() {
        drawpad = document.getElementById('drawpad');
        context = drawpad.getContext('2d');
        picture = new Image();
        picture.src = 'pictures/poo.png';
        picture.onload=draw;
    }

    function draw () {
        context.clearRect(0,0,drawpad.width, drawpad.height);
        context.drawImage(picture, 0,0);
    }

})();