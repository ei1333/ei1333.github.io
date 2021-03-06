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
};


$(function()
{
  var rank = 1;
  var limit = 0;
  
  var call =  function(x) {
    var url = "https://atcoder.jp/ranking?p=" + x;
//*[@id="main-div"]/div/div/div/div[1]/table
    var xpath = '//*[@id="main-div"]/div/div/div/div[1]/table/tbody';
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
    var str = $.parseXML(data.query.results.result).documentElement;
    var $xml = $(str);
    var value = $xml.find("td");

    for(var i = 1; i < value.length; i +=6)
    {
      
      if(rank > 1000) return;
      var S =  value[i].innerHTML;
      if((""+S).includes("JP")) {
        $("#ranking").append("<tr id='rank" + rank + "'>");
        var now = "#rank" + rank;
        $(now).append("<td style='text-align: right;'>"+rank + "(" + value[i-1].innerHTML + ")</td>");
        $(now).append("<td><a href='https://beta.atcoder.jp/users/" + $(value[i]).find("span")[0].innerHTML + "' target='_blank'>"+$(value[i]).find("span")[0].innerHTML+"</td>");
        $(now).children().last().children("a").css("color", getRatingLine("atcoder",value[i+1].innerHTML).color).css("font-weight", "bold");
        $(now).append("<td style='text-align: center'>" + value[i+1].innerHTML + "</td>");
        $(now).append("<td style='text-align: center'>"+ value[i+2].innerHTML + "</td>");

        rank += 1;
      }
   }
   if(rank > 1000) return;
   call(x + 1);
  }).fail(function(data)
  {
  });
  }
  call(1); 
});


function getRatingLine(site, rating)
{
  for(var i = 0; i < colors[site].length; i++) {
    var line = colors[site][i];
    if(line.min <= rating && rating <= line.max) return(line);
  }
  return(null);
}

