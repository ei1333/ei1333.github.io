$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
     $(this).load("source_code/ " + $(this).attr('src'));
    }
  });
  hljs.initHighlightingOnLoad();  
});
