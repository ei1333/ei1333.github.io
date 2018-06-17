var Point = function(x, y) {
    this.x = x;
    this.y = y;
};

function dist(a, b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

var Segment = function(begin, end) {
    this.begin = begin;
    this.end = end;
};

var Polygon = function(points) {
    this.points = points;
};

Point.prototype.draw = function(ctx) {
    ctx.save();
    ctx.beginPath();
    ctx.arc(this.x, this.y, 1, 0, Math.PI * 2, false);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
}
Segment.prototype.draw = function(ctx) {
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(this.begin.x, this.begin.y);
    ctx.lineTo(this.end.x, this.end.y);
    ctx.closePath();
    ctx.stroke();
    ctx.restore();
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

var PriorityQueue = function(compare) {
    this.heap = [null];
    this.compare = compare;
}

PriorityQueue.prototype.push = function(data) {
    var k = this.heap.length;
    this.heap.push(data);
    while(k > 1 && this.compare(this.heap[Math.floor(k / 2)], this.heap[k]) < 0) {
	var buf = this.heap[k];
	this.heap[k] = this.heap[Math.floor(k / 2)];
	this.heap[Math.floor(k / 2)] = buf;
	k = Math.floor(k / 2);
    }
}

PriorityQueue.prototype.modify = function(k) {
    var l = 2 * k;
    var r = 2 * k + 1;
    var largest = k;
    if(l < this.heap.length && this.compare(this.heap[k], this.heap[l]) < 0) {
	largest = l;
    }
    if(r < this.heap.length && this.compare(this.heap[largest], this.heap[r]) < 0) {
	largest = r;
    }
    
    if(largest != k) {
	var buf = this.heap[k];
	this.heap[k] = this.heap[largest];
	this.heap[largest] = buf;
	this.modify(largest);
    }
}
PriorityQueue.prototype.pop = function() {
    var top = this.heap[1];
    if(this.heap.length == 2) {
	this.heap.pop();
	return top;
    } else {
	
	this.heap[1] = this.heap.pop();
	this.modify(1);
	return top;
    }
}
PriorityQueue.prototype.size = function() {
    return this.heap.length - 1;
}
PriorityQueue.prototype.empty = function() {
    return this.heap.length <= 1;
}
    

var cv;
var c;
var timerID;

cv = document.getElementById('cv');
if(cv.getContext) {
    c = cv.getContext('2d');
 timerID = setInterval(draw, 30);
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

var points = get_random_points(500, field);
var que = new PriorityQueue(function(a, b) {
    return b[0] - a[0];
});

var edges = [];
var process = 0;

function draw() {
    c.clearRect(0, 0, cv.width, cv.height);
    
    points.forEach(function(point) {
	point.draw(c);
    });
    edges.forEach(function(edge) {
	edge.draw(c);
    });
    update();
}

var used = Array(points.length);
for(var i = 0; i < used.length; i++) {
    used[i] = false;
}

que.push([0, 0, -1]);

function update() {
    while(!que.empty()) {
	var p = que.pop();

	if(used[p[1]]) continue;
	used[p[1]] = true;
	if(p[2] != -1) edges.push(new Segment(points[p[1]], points[p[2]]));
	
	for(var i = 0; i < points.length; i++) {
	    que.push([dist(points[p[1]], points[i]), i, p[1]]);
	}
	break;
    }
}
