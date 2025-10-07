/**
 * Zach McKee and Kevin Hance
 * CPSC 425-01
 * Project 3
 */
"use strict";

let canvas;

/** @type {WebGLRenderingContext} */
let gl;

let program;

let rot1;
let rot2;
let rot3;
let scale1;
let tz;
let tx=0;
let ty=0;

let shapes = [];
var vertices = [
    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5, -0.5, -0.5, 1.0 )
];

var vertexColors = [
    [ 0.0, 0.0, 0.0, 1.0 ],  // black
    [ 1.0, 0.0, 0.0, 1.0 ],  // red
    [ 1.0, 1.0, 0.0, 1.0 ],  // yellow
    [ 0.0, 1.0, 0.0, 1.0 ],  // green
    [ 0.0, 0.0, 1.0, 1.0 ],  // blue
    [ 1.0, 0.0, 1.0, 1.0 ],  // magenta
    [ 0.0, 1.0, 1.0, 1.0 ],  // cyan
    [ 1.0, 1.0, 1.0, 1.0 ]   // white
];

let tVertices = [
    vec4(  0.0000,  0.0000, -1.0000, 1.0 ),
    vec4(  0.0000,  0.9428,  0.3333, 1.0 ),
    vec4( -0.8165, -0.4714,  0.3333, 1.0 ),
    vec4(  0.8165, -0.4714,  0.3333, 1.0 )
];

let sVertices = [
    vec4( 0.0, 0.0, -0.2, 1.0), //Front center (away from screen)
    vec4( 0.0, 0.0, 0.2, 1.0),  //Back center  (towards screen)
    vec4( 0.0, 0.55, 0.0, 1.0), //Top tip
    vec4( -0.15, 0.25, 0.0, 1.0), //Left/top
    vec4( -0.5, 0.25, 0.0, 1.0), //Left tip
    vec4( -0.25, 0.0, 0.0, 1.0),//Left/bottom
    vec4( -0.4, -.35, 0.0, 1.0), //Left/bottom tip
    vec4( 0.0, -0.18, 0.0, 1.0), //Bottom
    vec4( 0.4, -0.35, 0.0, 1.0), //Right/bottom tip
    vec4( 0.25, 0.0, 0.0, 1.0), //Right/Bottom
    vec4(0.5, 0.25, 0.0, 1.0),   //Right tip
    vec4(0.15, 0.25, 0.0, 1.0)    //Right/top
];

let dVertcies = [
    vec4(0.0, 0.65, 0.0, 1.0), //Top tip
    vec4(0.0, -0.65, 0.0, 1.0), //Bottom tip
    vec4(0.5, 0.0, 0.5, 1.0), //Back right
    vec4(-0.5, 0.0, 0.5, 1.0), //Back left
    vec4(-0.5, 0.0, -0.5, 1.0), //Front left
    vec4(0.5, 0.0, -0.5, 1.0), //Front right
]

let status;

// Represents a shape to be drawn to the screen, and maintains the relevant
// GPU buffers
class Shape {
    constructor() {
        if (!gl) {
            console.log("Shape constructor must be called after WebGL is initialized");
        }
        // Buffer for vertex positions
        this.vBuffer = gl.createBuffer();

        // Buffer for vertex colors
        this.cBuffer = gl.createBuffer();

        // Transformation matrix
        this.mat = mat4();

        // Number of vertices in this shape
        this.numVertices = 0;

        // What draw mode to use
        this.drawMode = gl.TRIANGLES;

    }

    // Render the shape to the screen
    draw() {
        // TODO
        let tempMat = gl.getUniformLocation(program, "mat",);
        gl.uniformMatrix4fv(tempMat, false, flatten(this.mat));
        
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vBuffer);
        var vPosition = gl.getAttribLocation(program, "vPosition");
        gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0,0);
        gl.enableVertexAttribArray(vPosition);

        gl.bindBuffer(gl.ARRAY_BUFFER, this.cBuffer);
        var vColor = gl.getAttribLocation(program, "vColor");
        gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0,0);
        gl.enableVertexAttribArray(vColor);

        gl.drawArrays(this.drawMode, 0, this.numVertices);
    }

    // Set the positions and colors to be used for this shape.  Both positions
    // and colors should be arrays of vec4s.
    setData(positions, colors) {
        if (positions.length != colors.length) {
            console.log("Positions and colors not the same length");
        }
        this.numVertices = positions.length;
        gl.bindBuffer(gl.ARRAY_BUFFER, this.vBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, flatten(positions), gl.STATIC_DRAW);
        var vPosition = gl.getAttribLocation(program, "vPosition");
        gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0,0);
        gl.enableVertexAttribArray(vPosition);

        gl.bindBuffer(gl.ARRAY_BUFFER, this.cBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW);
        var vColor = gl.getAttribLocation(program, "vColor");
        gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0,0);
        gl.enableVertexAttribArray(vColor);
    }

    // Set transformation matrix
    setMat(mat) {
        this.mat = mat;
    }
}

window.onload = function init()
{
    
    status = document.getElementById("status");
    rot1 = document.getElementById("rot1");
    rot2 = document.getElementById("rot2");
    rot3 = document.getElementById("rot3");
    scale1 = document.getElementById("scale1");
    tz = document.getElementById("tz");
    [rot1, rot2, rot3, scale1, tz].forEach(function(elem) {
        elem.initValue = elem.value;
        elem.addEventListener("input", render);
        elem.addEventListener("dblclick", function() {
            elem.value = elem.initValue;
            render();
        });
    });
    //Adding a cube
    let addCube = document.getElementById("addCube");
    // TODO: probably set up buttons here
    addCube.addEventListener("click", function(event) {
        [rot1, rot2, rot3, scale1, tz].forEach(function(elem) {
            elem.value = elem.initValue;
        });
        tx = 0;
        ty = 0;
        let newShape = new Shape();
        let points = [vertices[1], vertices[0], vertices[3], vertices[1], vertices[3], vertices[2],
                      vertices[2], vertices[3], vertices[7], vertices[2], vertices[7], vertices[6], 
                      vertices[3], vertices[0], vertices[4], vertices[3], vertices[4], vertices[7], 
                      vertices[6], vertices[5], vertices[1], vertices[6], vertices[1], vertices[2],
                      vertices[4], vertices[5], vertices[6], vertices[4], vertices[6], vertices[7],
                      vertices[5], vertices[4], vertices[0], vertices[5], vertices[0], vertices[1]];
        let colors = [vertexColors[1], vertexColors[1], vertexColors[1], vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[2], vertexColors[2], vertexColors[2], vertexColors[2], vertexColors[2], vertexColors[2],
                      vertexColors[3], vertexColors[3], vertexColors[3], vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[6], vertexColors[6], vertexColors[6], vertexColors[6], vertexColors[6], vertexColors[6],
                      vertexColors[4], vertexColors[4], vertexColors[4], vertexColors[4], vertexColors[4], vertexColors[4],
                      vertexColors[5], vertexColors[5], vertexColors[5], vertexColors[5], vertexColors[5], vertexColors[5]];
        newShape.setData(points, colors);
        shapes.push(newShape);
        render();
    });

    //Adding a tetrahedron
    let addTet = document.getElementById("addTet");
    addTet.addEventListener("click", function(event) {
        [rot1, rot2, rot3, scale1, tz].forEach(function(elem) {
            elem.value = elem.initValue;
        });
        tx = 0;
        ty = 0;
        let newShape = new Shape();
        let points = [tVertices[0], tVertices[2], tVertices[1],
                      tVertices[0], tVertices[2], tVertices[3],
                      tVertices[0], tVertices[1], tVertices[3],
                      tVertices[1], tVertices[2], tVertices[3]];
        let colors = [vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[4], vertexColors[4], vertexColors[4],
                      vertexColors[0], vertexColors[0], vertexColors[0]];
        newShape.setData(points, colors);
        shapes.push(newShape);
        render();
    });

    //Adding a star
    let addStar = document.getElementById("addShapeOne");
    addStar.addEventListener("click", function(event) {
        [rot1, rot2, rot3, scale1, tz].forEach(function(elem) {
            elem.value = elem.initValue;
        });
        tx = 0;
        ty = 0;
        let newShape = new Shape();
        let points = [sVertices[0], sVertices[2], sVertices[3],
                      sVertices[0], sVertices[3], sVertices[4],
                      sVertices[0], sVertices[4], sVertices[5],
                      sVertices[0], sVertices[5], sVertices[6],
                      sVertices[0], sVertices[6], sVertices[7],
                      sVertices[0], sVertices[7], sVertices[8],
                      sVertices[0], sVertices[8], sVertices[9],
                      sVertices[0], sVertices[9], sVertices[10],
                      sVertices[0], sVertices[10], sVertices[11],
                      sVertices[0], sVertices[11], sVertices[2],
                      sVertices[1], sVertices[2], sVertices[3],
                      sVertices[1], sVertices[3], sVertices[4],
                      sVertices[1], sVertices[4], sVertices[5],
                      sVertices[1], sVertices[5], sVertices[6],
                      sVertices[1], sVertices[6], sVertices[7],
                      sVertices[1], sVertices[7], sVertices[8],
                      sVertices[1], sVertices[8], sVertices[9],
                      sVertices[1], sVertices[9], sVertices[10],
                      sVertices[1], sVertices[10], sVertices[11],
                      sVertices[1], sVertices[11], sVertices[2]];
        let colors = [vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[1], vertexColors[1], vertexColors[1]];
        newShape.setData(points, colors);
        shapes.push(newShape);
        render();

    });

    //Adding a diamond
    let addDiamond = document.getElementById("addShapeTwo");
    addDiamond.addEventListener("click", function(event) {
        [rot1, rot2, rot3, scale1, tz].forEach(function(elem) {
            elem.value = elem.initValue;
        });
        tx = 0;
        ty = 0;
        let newShape = new Shape();
        let points = [dVertcies[0], dVertcies[2], dVertcies[3],
                      dVertcies[0], dVertcies[3], dVertcies[4],
                      dVertcies[0], dVertcies[4], dVertcies[5],
                      dVertcies[0], dVertcies[5], dVertcies[2],
                      dVertcies[1], dVertcies[2], dVertcies[3],
                      dVertcies[1], dVertcies[3], dVertcies[4],
                      dVertcies[1], dVertcies[4], dVertcies[5],
                      dVertcies[1], dVertcies[5], dVertcies[2]];
        let colors = [vertexColors[1], vertexColors[1], vertexColors[1],
                      vertexColors[2], vertexColors[2], vertexColors[2],
                      vertexColors[3], vertexColors[3], vertexColors[3],
                      vertexColors[4], vertexColors[4], vertexColors[4],
                      vertexColors[5], vertexColors[5], vertexColors[5],
                      vertexColors[6], vertexColors[6], vertexColors[6],
                      vertexColors[7], vertexColors[7], vertexColors[7],
                      vertexColors[0], vertexColors[0], vertexColors[0]];
        newShape.setData(points, colors);
        shapes.push(newShape);
        render();
                      
    });

    canvas = document.getElementById( "gl-canvas" );
    canvas.addEventListener("mousedown", function(event) {
        // TODO
    });
    canvas.addEventListener("mousemove", function() {
        if (event.buttons & 1 === 1) {
            let normalizedX = 2 * event.clientX / canvas.width - 1;
            let normalizedY = 1 - 2 * event.clientY / canvas.height;
            tx = normalizedX;
            ty = normalizedY;
            render();
        }
    });
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.8, 0.8, 0.8, 1.0 );

    gl.enable(gl.DEPTH_TEST);

    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    

    render();
};

function render()
{
    status.innerHTML = "Angles: " + (+rot1.value).toFixed()
        + ", " + (+rot2.value).toFixed()
        + ", " + (+rot3.value).toFixed()
        + ". Scale: " + (+scale1.value).toFixed(2)
        + ". Translation: " + (+tz.value).toFixed(2);
    
    let r1 = rotateX(rot1.value);
    let r2 = rotateY(rot2.value);
    let r3 = rotateZ(rot3.value);
    let s1 = scalem(scale1.value, scale1.value, scale1.value);
    let t1 = translate(tx, ty, tz.value);
    
    // TODO: set mat correctly
    let mat = r1;
    mat = mult(t1, mult(s1, mult(mult(r2,r3), r1)));
    
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    for (let i=0; i<shapes.length; i++) {
        if (i === shapes.length - 1) {
            shapes[i].setMat(mat);
        }
        shapes[i].draw();
    }
}
