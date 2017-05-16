var encode = function() {
	var plain = document.getElementById('plain').value;
	var code = [];
	var gap, ret = "";
	
	for(var i=0; i<plain.length; i++) {
		code[i] = plain.charCodeAt(i);
		gap = code[i] - ((i) ? code[i-1] : 0);
		var beet = [9, Math.floor((Math.abs(gap)/9)), Math.floor((Math.abs(gap)%9))];
		if(beet[1]!=0 && i>0) ret += "うぃーん";
		ret += adjust(beet, ((gap<0)?"うっくっく":"ひるど") );
	}
	
	document.getElementById('brain').value = ret;
};

var adjust = function(val, mark) {
	var ret = "";
	var s = [ "えいえいえtﾋﾞｰﾄﾋﾞｰﾄ", "うぃーんうっくっく(←いずらいt)ﾋﾞｰﾄﾋﾞｰﾄ", "らて。" ];
	var m = [ "ひるど", mark, mark ];
	for(var i= (val[1]==0) ? 2 : 0; i < 3; i++) {
		for(var j = 0; j<val[i]; j++) {
      ret += m[i];
    }
		ret += s[i];
	}
	return ret;
};
