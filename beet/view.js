var colors = {
  'atcoder': [
    {color:'#808080', min:   0, max: 399, title:'Gray' },
    {color:'#804000', min: 400, max: 799, title:'Brown' },
    {color:'#008000', min: 800, max:1199, title:'Green' },
    {color:'#00C0C0', min:1200, max:1599, title:'Cyan' },
    {color:'#0000FF', min:1600, max:1999, title:'Blue' },
    {color:'#C0C000', min:2000, max:2399, title:'Yellow' },
    {color:'#FF8000', min:2400, max:2799, title:'Orange' },
    {color:'#FF0000', min:2800, max:9999, ttile:'Red' }
  ],

  'codeforces':[
    {color:'#808080', min:   0, max:1199, title:'Newbie' },
    {color:'#008000', min:1200, max:1399, title:'Pupil' },
    {color:'#03A89E', min:1400, max:1599, title:'Specialist' },
    {color:'#0000FF', min:1600, max:1899, title:'Expert' },
    {color:'#AA00AA', min:1900, max:2199, title:'Candidate Master' },
    {color:'#AA00AA', min:2200, max:2299, title:'Master' },
    {color:'#FF8C00', min:2300, max:2399, title:'International Master'},
    {color:'#FF0000', min:2400, max:2599, title:'Grandmaster'},
    {color:'#FF0000', min:2600, max:2899, title:'International Grandmaster'},
    {color:'#FF0000', camelcolor: '#000000', min:2900, max:9999, title:'Legendary Grandmaster'}
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
  var url = "http://codeforces.com/api/user.rating?handle=ei1333";
  var xpath = '/html/body/pre';
  var query = "select * from json where url = '" + url + "'";
  var yql   = "https://query.yahooapis.com/v1/public/yql?format=json&q=" + encodeURIComponent(query);

  $.ajax(
  {
    type     : 'GET',
    url      : yql,
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                 data = data['query']['results']['json']['result'];
                 setRatingHtml('codeforces', "#now_cf", data[data.length-1 - 1]['newRating']);
                  console.log(data);
               },
  });

  $.ajax(
  {
    type     : 'GET',
    url      : "https://api.topcoder.com/v2/users/ei1333/statistics/data/srm",
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                  console.log(data);
                  setRatingHtml('topcoder', '#now_tc', data['rating']);
               },
  });


  var url = "https://atcoder.jp/user/ei1333";
  var xpath = '//*[@id="main-div"]/div/div/div[2]/script[2]';
  var query = "select * from html where url = '" + url + "' and xpath = '" + xpath + "'";
  var yql   = "https://query.yahooapis.com/v1/public/yql?format=json&q=" + encodeURIComponent(query);

  $.ajax(
  {
    type     : 'GET',
    url      : yql,
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                  data = JSON.parse(ConvertAtCoder(data['query']['results']['script']));
                  setRatingHtml("atcoder", "#now_ac", data[0][1]);
                  console.log(data);
               },
  });
});



// いい感じに parse してえいってする
function ConvertAtCoder(str)
{
  var first = str.indexOf('JSON.parse("');
  var last = str.indexOf('");', first);
  if(first != -1 && last != -1) {
	  return(str.slice(first + 12, last).replace(/\\/g, ""));
  }
  return(null);
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
  var line = getRatingLine(site, rating);
  $(component).css('color', line.color);
  $(component).text(rating + " (" + line.title + ")"); 
}

