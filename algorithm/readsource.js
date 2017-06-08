$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
     $(this).load($(this).attr('src'));
    }
  }
  hljs.initHighlightingOnLoad();  
});
