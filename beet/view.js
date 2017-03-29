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
                  console.log(data);
               },
  });
/*
  $.ajax(
  {
    type     : 'GET',
    url      : 'https://codeforces.com/api/user.rating?handle=ei1333',
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                  console.log(data);
               },
  });
*/

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
                  console.log(data);
               },
  });

});
