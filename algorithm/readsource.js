$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
      var poyo = $(this);
      $.get($(this).attr('src'), function(data)
      {
        poyo.text(data);
      });
    }
  });
  hljs.initHighlightingOnLoad();  
});
