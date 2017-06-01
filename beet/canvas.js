$(function()
{
  var canvas = $('#row');
  var ctx = $('#row')[0].getContext('2d');
  var fileReader = new FileReader();
  var base = new Image();
  base.src = "sample.png";
  base.onload = function() {
    ctx.drawImage(base, 0, 0, canvas.width(), canvas.height());
  };
  $('#image').change(function()
  {
    if(!this.files.length) return;
    var getImage = $(this).siblings('img');
    fileReader.onload = function(event) {        
      var img = new Image();
      img.src = event.target.result;
      img.onload = function() {
        ctx.drawImage(base, 0, 0, canvas.width(), canvas.height());
        ctx.drawImage(img, 200, 140, 165, 165);
        updateId();
      };
    };

    fileReader.readAsDataURL(this.files[0]);
  });

  $('#id').keyup(function(event)
  {
    updateId();
  });

  function updateId()
  {
    var str = $('#id').val();
    ctx.fillStyle="#FFFFFF";
    ctx.fillRect(380, 140, 250, 170);
    if(str.length != 0) {
      ctx.fillStyle="#000000";
      ctx.font = "20px _sans";
      ctx.fillText("("+str+")", 380, 300);
    }
    var img_png_src = $("#row")[0].toDataURL("image/png");
    $("#output").attr("src", img_png_src);
  };
});
