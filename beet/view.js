$(function()
{
  $.ajax(
  {
    type     : 'GET',
    url      : '//codeforces.com/api/user.rating?handle=ei1333',
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                  console.log(data);
               },
  });

  $.ajax(
  {
    type     : 'GET',
    url      : "//api.topcoder.com/v2/users/ei1333/statistics/data/srm",
    dataType : 'json',
    timeout  : 10000,
    cache    : false,
    success  : function(data)
               {
                  console.log(data);
               },
  });


  var url = "//atcoder.jp/user/ei1333";
  var xpath = '//*[@id="main-div"]/div/div/div[2]/script[2]';
  var query = "select * from html where url = '" + url + "' and xpath = '" + xpath + "'";
  var yql   = "//query.yahooapis.com/v1/public/yql?format=json&q=" + encodeURIComponent(query);

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
