$(function()
{
  var canvas = $('#row');
  var ctx = $('#row')[0].getContext('2d');
  var fileReader = new FileReader();
  var base = new Image();
  base.src = "ushi.png";
  base.onload = function() {
    ctx.drawImage(base, 0, 0, 400, 200);
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
    var str1 = eval($('#id1').val()) || 0;
    var str2 = eval($('#id2').val()) || 0;
    str2 *= 4;
    var str3 = eval($('#id3').val()) || 0;
    str3 *= 8;

    var str = (str1 + str2 + str3)/1024/1024;
    str = String(Math.floor((str * 100)) / 100);
    ctx.fillStyle="#FFFFFF";
    ctx.fillRect(215, 55, 150, 50);
    if(str[0] == "-") {
      str = "うくやめろ";
    } else if(str == "0") {
      str =  (str1 + str2 + str3)/1024;
      str = String(Math.floor((str * 100)) / 100);
      str = str.substring(0,4);
      str = str + " KiB";
    } else {
      if(str >= 100000) str = "うしー";
      else {
        str = str.substring(0,5);
        str = str + " MiB";
      }
    }

    if(str.length > 0) {
      ctx.fillStyle="#000000";
      ctx.font = "20px _sans";
      ctx.fillText(str, 230, 85);
    }
    var img_png_src = $("#row")[0].toDataURL("image/png");
    $("#output").attr("src", img_png_src);
  };

});
