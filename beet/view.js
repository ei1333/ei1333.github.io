var colors = {
  'atcoder': [
    {color:'#808080', min:   0, max: 399, title:'Gray' },
    {color:'#804000', min: 400, max: 799, title:'Brown' },
    {color:'#008000', min: 800, max:1199, title:'Green' },
    {color:'#00C0C0', min:1200, max:1599, title:'Cyan' },
    {color:'#0000FF', min:1600, max:1999, title:'Blue' },
    {color:'#C0C000', min:2000, max:2399, title:'Yellow' },
    {color:'#FF8000', min:2400, max:2799, title:'Orange' },
    {color:'#FF0000', min:2800, max:9999, title:'Red' }
  ],

  'codeforces':[
    {color:'#808080', min:   0, max:1199, title:'Newbie' },
    {color:'#008000', min:1200, max:1399, title:'Pupil' },
    {color:'#03A89E', min:1400, max:1599, title:'Specialist' },
    {color:'#0000FF', min:1600, max:1899, title:'Expert' },
    {color:'#AA00AA', min:1900, max:2099, title:'Candidate Master' },
    {color:'#FF8C00', min:2100, max:2299, title:'Master' },
    {color:'#FF8C00', min:2300, max:2399, title:'International Master'},
    {color:'#FF0000', min:2400, max:2599, title:'Grandmaster'},
    {color:'#FF0000', min:2600, max:2999, title:'International Grandmaster'},
    {color:'#FF0000', camelcolor: '#000000', min:3000, max:9999, title:'Legendary Grandmaster'}
  ],
    'topcoder':[
      { color:'#999999', min:   0, max: 899, title:'Gray'  },
      { color:'#00A900', min: 900, max:1199, title:'Green' },
      { color:'#6666FF', min:1200, max:1499, title:'Blue' },
      { color:'#DDCC00', min:1500, max:2199, title:'Yellow' },
      { color:'#EE0000', min:2200, max:2999, title:'Red' },
      { color:'#EE0000', camelcolor: '#000000', min:3000, max:9999, title:'Target' },
    ]
};



$(function()
{
  var handle = undefined;
  var match = location.search.match(/handle=(.*?)(&|$)/);
  if(match) {
    handle = decodeURIComponent(match[1]);
    $('#handle').val(handle);
  }
  if(handle === undefined) return;

  var beet = [];
  var Codeforces = function(handle) {
    var url = "http://codeforces.com/api/user.rating?handle=" + handle;
    var query = "select * from json where url = '" + url + "'";
    var yql   = "https://query.yahooapis.com/v1/public/yql?format=json&q=" + encodeURIComponent(query);

    $.ajax(
    {
      type     : 'GET',
      url      : yql,
      dataType : 'json',
      timeout  : 10000,
      cache    : false,
    }).done(function(data)
    {
      var rating = undefined;
      if(data['query']['results']['json']['status'] == "OK") {
        data = data['query']['results']['json']['result'];
        if(data != undefined) {
          if(data.length == undefined) {
            var buff = data;
            data = [];
            data.push(buff);
          }
          rating = data[data.length - 1]['newRating'];
        }

        var stocked = [];
        for(var i = 0; i < data.length; i++) {
          stocked.push({x: moment(new Date(data[i]['ratingUpdateTimeSeconds'] * 1000)), y: data[i]['newRating'], label: data[i]['contestName']});
        }

        createGraph("codeforces", "#canvas2", stocked, []); 
        setRatingHtml('codeforces', "#now_cf", rating);      
      }
    }).fail(function(data)
    {
      setRatingHtml('codeforces', "#now_cf", undefined);
    });
  };

  Codeforces(handle);

  $.ajax(
  {
    type     : 'GET',
    url      : "https://api.topcoder.com/v2/users/" + handle + "/statistics/data/srm",
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
  }).done(function(data)
  {
    var stocked = [];
    for(var i = 0; i < data['History'].length; i++) {
      stocked.push({x: moment(data['History'][i]['date'].replace(/\./g, '-')), y: data['History'][i]['rating'], label: data['History'][i]['challengeName']});
    }
    console.log(stocked);

    stocked.sort(function(a,b) {
      return (a['x'] < b['x'] ? 1 : -1);
    });

    createGraph("topcoder", "#canvas1", stocked, []);


    setRatingHtml('topcoder', '#now_tc', data['rating']);
  }).fail(function(data)
  {
    setRatingHtml('topcoder', '#now_tc', undefined);
  });


  var url = "https://atcoder.jp/user/" + handle;
  var xpath = '//*[@id="main-div"]/div/div/div/script';
  var query = "select * from htmlstring where url = '" + url + "' and xpath = '" + xpath + "'";
  var yql   = "https://query.yahooapis.com/v1/public/yql?format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&q=" + encodeURIComponent(query);

  $.ajax(
  {
    type     : 'GET',
    url      : yql,
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
  }).done(function(data)
  {
    var rating = undefined;
    data = JSON.parse(getAtcoderJSON(data.query.results.result));
    rating = data[0][1];
    var stocked = [];
    for(var i = 0; i < data.length; i++) {
      var update = new Date(data[i][0] * 1000);
      stocked.push({x: moment(update), y: data[i][1], label: data[i][3]});
    }
    createGraph("atcoder", "#canvas3", stocked, []);
    
    setRatingHtml("atcoder", "#now_ac", rating);
  }).fail(function(data)
  {
    setRatingHtml("atcoder", "#now_ac", undefined);
  });
});


function getAtcoderJSON(src) {
    //alert(src);
    var idxf = src.indexOf('JSON.parse("');
    var idxe = src.indexOf('");]]>', idxf);
    if (idxf != -1 && idxe != -1) {
	return src.slice(idxf + 12, idxe).replace(/\\/g, "");
    }
    return null;
}

// よくわからない
function getRatingLine(site, rating)
{
  for(var i = 0; i < colors[site].length; i++) {
    var line = colors[site][i];
    if(line.min <= rating && rating <= line.max) return(line);
  }
  return(null);
}

// 要素名 component に値 rating をセットする
function setRatingHtml(site, component, rating)
{
  if(rating == undefined) {
    $(component).text("?");
    return;
  }

  var line = getRatingLine(site, rating);
  $(component).css('color', line.color);
  $(component).text(rating + " (" + line.title + ")"); 
}


// いい感じにグラフを描画する
function createGraph(site, component, stocked1, stocked2)
{
  var ctx  = $(component);

  var each_point_color1 = [], each_point_color2 = [];

  for(var i = 0; i < stocked1.length; i++) {
    var line = getRatingLine(site, stocked1[i]['y']);
    each_point_color1.push(line.color);
  }
  for(var i = 0; i < stocked2.length; i++) {
    var line = getRatingLine(site, stocked2[i]['y']);
    each_point_color2.push(line.color);
  }

  var myLine = Chart.Line(ctx, {
    data: {
      datasets: [{
        tyle: 'line',
        data: stocked1,
        lineTension : 0,
        pointBackgroundColor: each_point_color1,
        pointRadius: 4,
        fill: false,
      },
      {
        tyle: 'line',
        data: stocked2,
        lineTension : 0,
        pointBackgroundColor: each_point_color2,
        pointRadius: 4,
        fill: false,

      }]
    },
    options: {
      legend: {
        display: false
      },
      title: {
        display: true,
        text: site
      },
      tooltips: {
        mode: 'label',
        callbacks: {
          title: function(tooltipItems, data) {
            return(stocked1[tooltipItems[0].index].label);
          }
        }
      },
      scales: {
        xAxes: [{
          type: 'time',
          position: 'bottom',
          unit: 'month',
          time: {
            displayFormats: {
              'millisecond': 'YY-MM',
              'second': 'YY-MM',
              'minute': 'YY-MM',
              'hour': 'YY-MM',
              'day': 'YY-MM',
              'week': 'YY-MM',
              'month': 'YY-MM',
              'quarter': 'YY-MM',
              'year': 'YY-MM',
            }
          }
        }]
      }
    },
  });

}
