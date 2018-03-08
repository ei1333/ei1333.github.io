$(function()
{
  $('pre code').each(function(i, block)
  {
    if(typeof $(this).attr('src') !== "undefined") {
      var poyo = $(this);
      $.get($(this).attr('src'), function(data)
      {
        poyo.text(data);
        hljs.highlightBlock(block);
      });
    }
  });

document.queryCommandSupported("copy")&&($("pre").before('<div class="div-sample-copy"><span class="btn-sample-copy">Copy</span></div>'),$(".btn-sample-copy").click(function(){window.getSelection().removeAllRanges();try{var e=document.createRange();e.selectNode($(this).parent().next("pre").get()[0]),window.getSelection().addRange(e),document.execCommand("copy");var t=this;}catch(o){console.log(o)}window.getSelection().removeAllRanges()}));

});
