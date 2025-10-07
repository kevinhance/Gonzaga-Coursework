"use strict";

/** @type{WebGLRenderingContext} */
let gl;

let currentColor = vec4(0,0,0,1);
let drawingLines = true;

// You will want to add additional variables to keep track of what needs
// to be drawn

let program;

window.addEventListener("load", function()
{
    let canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    canvas.addEventListener("mousedown", function(event) {
        
    });
    canvas.addEventListener("mousemove", function(event) {
        let status = document.getElementById("status");
        status.innerHTML = event.clientX + ", " + event.clientY + " " + event.buttons;
    });
    canvas.addEventListener("mouseup", function() {
    });
    
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );

    gl.clearColor( 0.8, 0.8, 0.8, 1.0 );

    program = initShaders( gl, "vertex-shader", "fragment-shader" );

    gl.useProgram( program );

    render();
});


function render() {
    gl.clear( gl.COLOR_BUFFER_BIT );
}
