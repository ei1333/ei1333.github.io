var Point = function(x, y) {
    this.x = x;
    this.y = y;
};

var Segment = function(begin, end) {
    this.begin = begin;
    this.end = end;
};


var Polygon = function(points) {
    this.points = points;
};

var Circle = function(center, radius) {
    this.center = center;
    this.radius = radius;
};

Point.prototype.draw = function(ctx) {
    ctx.save();
    ctx.beginPath();
    ctx.arc(this.x, this.y, 1, 0, Math.PI * 2, false);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}
Point.prototype.equal = function(p) {
    return p.x == this.x && p.y == this.y;
}
function cross(a, b) {
    return a.x * b.y - a.y * b.x;
}
function dot(a, b) {
    return a.x * b.x + a.y * b.y;
}

Segment.prototype.equal = function(p) {
    return ((p.begin == this.begin && p.end == this.end) ||
	    (p.begin == this.end && p.end == this.begin));
}

Polygon.prototype.draw = function(ctx) {
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(this.points[0].x, this.points[0].y);
    for(var i = 1; i < this.points.length; i++) {
	ctx.lineTo(this.points[i].x, this.points[i].y);
    }
    ctx.closePath();
    ctx.stroke();

    if(!this.color) {
	var color = {r:0, g:0, b:0};
	for(var i in color){
	    color[i] = Math.floor(Math.random() * 256);
	}
	this.color = "rgb(" + color.r + ", " + color.g + ", " + color.b + ")";
    }
    ctx.fillStyle = this.color;
    ctx.fill();
    ctx.restore();
}
Polygon.prototype.contains = function(point) {
    var isin = false;
    for(var i = 0 ; i < this.points.length; i++ ){
	var a = this.points[i];
	var b = this.points[(i + 1) % this.points.length];
	
	var latte = new Point(a.x - point.x, a.y - point.y);
	var malta = new Point(b.x - point.x, b.y - point.y);
	if(latte.y > malta.y) {
	    var beet = latte;
	    latte = malta;
	    malta = beet;
	}
	
	if(latte.y <= 0 && 0 < malta.y && cross(latte, malta) < 0) isin = !isin;
	if(cross(latte, malta) == 0 && dot(latte, malta) <= 0) return true;
    }
    return isin;
}
Polygon.prototype.get_circumcircle_from_triangle = function() {
    if(!this.circumcircle) {
	var p1 = this.points[0];
	var p2 = this.points[1];
	var p3 = this.points[2];

	var c = 2.0 * ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
	var latte = p2.x * p2.x - p1.x * p1.x + p2.y * p2.y - p1.y * p1.y;
	var malta = p3.x * p3.x - p1.x * p1.x + p3.y * p3.y - p1.y * p1.y;
	
	var x = ((p3.y - p1.y) * latte + (p1.y - p2.y) * malta) / c;
	var y = ((p1.x - p3.x) * latte + (p2.x - p1.x) * malta) / c;
	var r = Math.sqrt((p1.x - x) * (p1.x - x) + (p1.y - y) * (p1.y - y));
	this.circumcircle = new Circle(new Point(x, y), r);
    }
    return this.circumcircle;
};


Circle.prototype.draw = function(ctx) {
    ctx.save();
    ctx.beginPath();
    ctx.arc(this.center.x, this.center.y, this.radius, 0, Math.PI * 2, false);
    ctx.closePath();
    ctx.stroke();
    ctx.restore();
}
Circle.prototype.isin = function(point) {
    var x = point.x - this.center.x;
    var y = point.y - this.center.y;
    return x * x + y * y < this.radius * this.radius;
}

function get_random_points(num, field) {
    var points = [];
    var distx, disty;
    var x, y;

    distx = field.points[2].x - field.points[0].x;
    disty = field.points[2].y - field.points[0].y;
    for(var i = 0; i < num; i++) {
	x = Math.random() * distx + field.points[0].x;
	y = Math.random() * disty + field.points[0].y;
	points.push(new Point(x, y));
    }
    return points;
}


function get_circumcircle_from_stage(stage) {
    var rad = Math.sqrt((stage.w * stage.w) + (stage.h * stage.h)) * 0.5;
    var center = new Point(stage.x + stage.w * 0.5, stage.y + stage.h * 0.5);
    return new Circle(center, rad);
}

function get_circumtriangle_from_circle(circle) {
    return new Polygon([
	new Point(circle.center.x - Math.sqrt(3) * circle.radius, circle.center.y - circle.radius),
	new Point(circle.center.x + Math.sqrt(3) * circle.radius, circle.center.y - circle.radius),
	new Point(circle.center.x, circle.center.y + circle.radius * 2)
    ]);
}

var cv;
var c;
var timerID;

cv = document.getElementById('cv');
if(cv.getContext) {
    c = cv.getContext('2d');
    timerID = setInterval(draw, 150);
}

var stage = {
    x: 50,
    y: 50,
    w: 400,
    h: 400
};

var field  = new Polygon([
    new Point(stage.x, stage.y),
    new Point(stage.x, stage.y + stage.h),
    new Point(stage.x + stage.w, stage.y + stage.h),
    new Point(stage.x + stage.w, stage.y)
]);

var points = get_random_points(100, field);
var triangles = [get_circumtriangle_from_circle(get_circumcircle_from_stage(stage))];
var dame = triangles[0];

var process = 0;


function update(i) {
    if(i >= points.length) return;
    var p = points[i];

    var succeed = false;
    var new_triangles = [];
    triangles.forEach(function(triangle, j) {
	if(!succeed && triangle.contains(p)) {
	    for(var k = 0; k < triangle.points.length; k++) {
		var new_triangle = new Polygon([
		    triangle.points[k],
		    triangle.points[(k + 1) % triangle.points.length],
		    p
		]);
		new_triangles.push(new_triangle);
	    }
	    triangles.forEach(function(triangle2, k) {
		if(j != k) new_triangles.push(triangle2);
	    });
	    succeed = true;
	}
    });
    triangles = new_triangles;
    while(succeed) {
	succeed = false;
	for(var j = 0; j < triangles.length; j++) {
	    for(var k = 0; k < triangles.length; k++) {
		if(j == k) continue;
		for(var l = 0; l < 3; l++) {
		    for(var m = 0; m < 3; m++) {
			var s1 = new Segment(triangles[j].points[l], triangles[j].points[(l + 1) % 3]);
			var s2 = new Segment(triangles[k].points[m], triangles[k].points[(m + 1) % 3]);
			if(s1.equal(s2)) {
			    var circum = triangles[j].get_circumcircle_from_triangle();
			    if(circum.isin(triangles[k].points[(m + 2) % 3])) {
				var x = new Polygon([
				    triangles[j].points[l],
				    triangles[j].points[(l + 2) % 3],
				    triangles[k].points[(m + 2) % 3]]);
				var y = new Polygon([
				    triangles[j].points[(l + 1) % 3],
				    triangles[j].points[(l + 2) % 3],
				    triangles[k].points[(m + 2) % 3]]);
				
				triangles[j] = x;
				triangles[k] = y;

				succeed = true;
			    }
			    
			}
		    }
		}
	    }
	}
    }
}



function draw() {
    c.clearRect(0, 0, cv.width, cv.height);
   // field.draw(c);
    triangles.forEach(function(triangle) {
	var output = true;
	for(var i = 0; i < triangle.points.length; i++) {
	    
	    for(var j = 0; j < dame.points.length; j++) {
		if(dame.points[j].equal(triangle.points[i])) output = false;
		
	    }
	}
	if(output) triangle.draw(c);
    });
    points.forEach(function(point) {
	point.draw(c);
    });
    
    update(process);
    ++process;
    
}
