/**
 * Zach McKee and Kevin Hance
 * CPSC 425-01
 * Project 2
 */
"use strict";

/** @type{WebGLRenderingContext} */
let gl;

let currentColor = vec4(0,0,0,1);
let drawingLines = true;
let mouseIsDown = false;
let points = [];
let startAndLength = [0];
let whatShape = [];
let colorAtPoint = [];
let curLength = 1;
let tempPoint;
let buttonRed;
let buttonBlue;
let buttonGreen;
let buttonBlack;
let buttonLines;
let buttonFilled;
let buffer;
let cBuffer;
// You will want to add additional variables to keep track of what needs
// to be drawn

let program;

window.addEventListener("load", function()
{
    //Getting all the buttons to add event listeners too
    buttonRed = document.getElementById("colorRed");
    buttonBlue = document.getElementById("colorBlue");
    buttonGreen = document.getElementById("colorGreen");
    buttonBlack = document.getElementById("colorBlack");
    buttonLines = document.getElementById("shapeLine");
    buttonFilled = document.getElementById("shapeFilled");
    //Giving all the buttons functionality
    buttonRed.addEventListener("click", function() {
        currentColor = vec4(1,0,0,1);
    });
    buttonBlue.addEventListener("click", function() {
        currentColor = vec4(0,0,1,1);
    });
    buttonGreen.addEventListener("click", function() {
        currentColor = vec4(0,1,0,1);
    });
    buttonBlack.addEventListener("click", function() {
        currentColor = vec4(0,0,0,1);
    });
    buttonLines.addEventListener("click", function() {
        drawingLines = true;
    });
    buttonFilled.addEventListener("click", function() {
        drawingLines = false;
    });

    let canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );

    //Code to be ran when someone clicks on the canvas
    canvas.addEventListener("mousedown", function(event) {
        //Getting the x and y of the mouse and normalizing it
        //to between -1 and 1 so it displays properly
        let normalizedX = 2 * event.clientX / canvas.width - 1;
        let normalizedY = 1 - 2 * event.clientY / canvas.height;
        tempPoint = vec2(normalizedX, normalizedY);
        points.push(tempPoint);
        mouseIsDown = true;
        //Determining what shape needs to be drawn and storing it
        //in the whatShape array
        if(drawingLines) {
            whatShape.push(0);
        } else {
            whatShape.push(1);
        }
        //Adding the color for the vertex into the
        //colorAtPoint array
        colorAtPoint.push(currentColor);
        //Adding the length of the current shape
        startAndLength[curLength] = 1
        //Checking to see if this is the first shape to be drawn,
        //If not, make the starting point to be drawn the previous shapes
        //starting point, plus its length
        if(startAndLength[curLength - 1] !== 0) {
            startAndLength[curLength - 1] = startAndLength[curLength-2] + startAndLength[curLength - 3] + 1;
        }

        //Send the data to the points and color buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
        gl.bufferData(gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, flatten(colorAtPoint), gl.STATIC_DRAW);
        render();
    });
    //Code to be ran while someone is hovering over the canvas
    canvas.addEventListener("mousemove", function(event) {
        let status = document.getElementById("status");
        status.innerHTML = event.clientX + ", " + event.clientY + " " + event.buttons;
        //Check to see if someone is clicking the mouse,
        //if they are, keep drawing using the same process as above
        if(mouseIsDown) {
            let normalizedX = 2 * event.clientX / canvas.width - 1;
            let normalizedY = 1 - 2 * event.clientY / canvas.height;
            tempPoint = vec2(normalizedX, normalizedY);
            points.push(tempPoint);
            colorAtPoint.push(currentColor);
            startAndLength[curLength]++;
            gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
            gl.bufferData(gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW);
            gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
            gl.bufferData(gl.ARRAY_BUFFER, flatten(colorAtPoint), gl.STATIC_DRAW);
            render();
        }
        
    });
    //Code to be ran when the mouse is pulled up
    canvas.addEventListener("mouseup", function(event) {
        //Set the boolean mouseIsDown to false
        //so the code knows to stop drawing while the 
        //mouse moves over the canvas
        mouseIsDown = false;
        //Subtract one from the current shape's
        //length to account for indexing by 0
        startAndLength[curLength] -= 1;
        //Move onto the next shape's spot
        //in the array
        curLength += 2;

    });
    
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );

    gl.clearColor( 0.8, 0.8, 0.8, 1.0 );

    program = initShaders( gl, "vertex-shader", "fragment-shader" );

    gl.useProgram( program );

    //Creating and initilizing the points buffer
    buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW);

    var vPos = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPos, 2, gl.FLOAT, false, 0,0);
    gl.enableVertexAttribArray(vPos);

    //Creating and initilizing the color buffer
    cBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(colorAtPoint), gl.STATIC_DRAW);

    var vColor = gl.getAttribLocation(program, "vColor");
    gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0,0);
    gl.enableVertexAttribArray(vColor);

    
    render();
    
});


function render() {
    gl.clear( gl.COLOR_BUFFER_BIT );
    
    var j = 0;
    //Loop through each shape and draw them according to what shape was selected.
    for(var i = 0; i < startAndLength.length; i += 2) {
        if(whatShape[j] === 0) {
            gl.drawArrays(gl.LINE_STRIP, startAndLength[i],startAndLength[i+1]);
        } else {
            gl.drawArrays(gl.TRIANGLE_FAN, startAndLength[i],startAndLength[i+1]);
        }
        j++;
    }
}
