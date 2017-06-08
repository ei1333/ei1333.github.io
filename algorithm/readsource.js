$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
      $.get($(this).attr('src'), function(data)
      {
console.log(data);
        $(this).text(data);
      });
    }
  });
  hljs.initHighlightingOnLoad();  
});
