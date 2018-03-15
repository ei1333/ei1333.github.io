$(function()
{
  var canvas = $('#row');
  var ctx = $('#row')[0].getContext('2d');
  var fileReader = new FileReader();
  var base = new Image();
  base.src = "ushi.png";
  base.onload = function() {
    ctx.drawImage(base, 0, 0, 300, 200);
  };

  $('#id1').keyup(function(event)
  {
    updateId();
  });
  $('#id2').keyup(function(event)
  {
    updateId();
  });
  $('#id3').keyup(function(event)
  {
    updateId();
  });


  function updateId()
  {
    var strText1 = $('#id1').val();
    var str1 = Number(strText1) || 0;

    var strText2 = $('#id2').val();
    var str2 = Number(strText3) || 0;
    str2 *= 4;

    var strText3 = $('#id2').val();
    var str3 = Number(strText3) || 0;
    str3 *= 8;

    ctx.fillStyle="#FFFFFF";
    ctx.fillRect(195, 55, 77, 50);
    if(str.length != 0) {
      ctx.fillStyle="#000000";
      ctx.font = "10px _sans";
      ctx.fillText("("+(str1+str2+str3)+" MB)", 195, 55);
    }
    var img_png_src = $("#row")[0].toDataURL("image/png");
    $("#output").attr("src", img_png_src);
  };
});
