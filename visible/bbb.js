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

var UnionFind = function(sz) {
    this.data = new Array(sz);
    for(var i = 0; i < sz; i++) this.data[i] = -1;
};

UnionFind.prototype.find = function(k) {
    if(this.data[k] < 0) {
	return k;
    } else {
	this.data[k] = this.find(this.data[k]);
	return this.data[k];
    }
}
UnionFind.prototype.unite = function(x, y) {
    x = this.find(x);
    y = this.find(y);
    if(x == y) return;
    if(this.data[x] > this.data[y]) {
	var z = x;
	x = y;
	y = z;
    }
    this.data[x] += this.data[y];
    this.data[y] = x;
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
var uf = new UnionFind(points.length);
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

var init_edges = [];
for(var i = 0; i < points.length; i++) {
    for(var j = i + 1; j < points.length; j++) {
	init_edges.push([dist(points[i], points[j]), i, j]);
    }
}
init_edges.sort(function(a, b) {
    if(a[0] < b[0]) return -1;
    if(a[0] > b[0]) return 1;
    return 0;
});

function update() {
    for(var i = process; i < init_edges.length; i++) {
	var x = uf.find(init_edges[i][1]);
	var y = uf.find(init_edges[i][2]);
	if(x == y) continue;
	uf.unite(x, y);
	edges.push(new Segment(points[init_edges[i][1]], points[init_edges[i][2]]));;
	process = i + 1;
	break;
    }
}
