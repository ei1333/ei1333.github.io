var str = '& < > ` " ' + "'";
var escapeHtml = (function (String) {
  var escapeMap = {
    '&': '&amp;',
    "'": '&#x27;',
    '`': '&#x60;',
    '"': '&quot;',
    '<': '&lt;',
    '>': '&gt;'
  };
  var escapeReg = '[';
  var reg;
  for (var p in escapeMap) {
    if (escapeMap.hasOwnProperty(p)) {
      escapeReg += p;
    }
  }
  escapeReg += ']';
  reg = new RegExp(escapeReg, 'g');
 
  return function escapeHtml (str) {
    str = (str === null || str === undefined) ? '' : '' + str;
    return str.replace(reg, function (match) {
      return escapeMap[match];
    });
  };
}(String));

$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
      $.get($(this).attr('src'), function(data)
      {
        $(this).text(data);
      });
    }
  });
  hljs.initHighlightingOnLoad();  
});
