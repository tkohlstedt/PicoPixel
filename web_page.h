#define index_page "<!doctype html>\n"\
"<html xmlns=http://www.w3.org/1999/xhtml>\n"\
"<head>\n"\
"<title>PicoPixel Controller</title>\n"\
"<meta content='text/html; charset=utf-8' http-equiv=Content-Type>\n"\
"<meta content=no-cache http-equiv=pragma>\n"\
"<meta content='no-cache, must-revalidate' http-equiv=content-type>\n"\
"<style>body{background-color:transparent}body,div,h3,p{margin:0;padding:0;font:normal 14px omnes-pro,Helvetica,Arial,sans-serif}#header{position:relative;margin:auto}#header a{margin-left:30px}#header h2{vertical-align:middle;font-size:42px;font-weight:700;text-decoration:none;color:#000;margin-left:30px;text-align:left}.usual{background:0 0;color:#111;padding:15px 20px;width:auto;margin:8px auto}.usual li{list-style:none;float:left}.usual ul a{display:block;padding:6px 10px;text-decoration:none!important;margin:1px;margin-left:0;font-weight:700;color:#fff;background:#aaa}.usual ul a:hover{color:#111;background:#eef3ff}.usual ul a.selected{margin-bottom:0;color:#000;background:#eef3ff;border-bottom:1px solid snow;cursor:default}.usual div{padding:10px 10px 8px 10px;clear:left;background:#eef3ff}.usual div a{color:#000;font-weight:700}.hide{display:none}.show{display:block}.mr5{margin-right:5px}.red{color:red}.usual div h3{margin-top:10px;margin-left:10px;font-size:24px;text-decoration:none;font-weight:700;color:#00f}.usual div p{margin-top:0;margin-bottom:10px}.ipt label{float:left;padding-top:3px;text-align:left;width:130px}.pwd label{float:left;margin-left:-5px;padding-top:3px;text-align:left;width:160px}.di-led{margin-top:2px;margin-right:10px;margin:5px auto;border:0 dashed #ccc;height:28px;width:28px;display:block}.di-on{background-image:url(img/di_on.png)}.dio-on{background-image:url(img/dio_on.png)}.di-off{background-image:url(img/di_off.png)}.d-no-use{background-image:url(img/notused.png)}.do-led{margin-top:2px;margin-right:20px;margin:5px auto;border:0 dashed #ccc;height:33px;width:96px;display:block}.do-on{background-image:url(img/do_on.png)}.do-off{background-image:url(img/do_off.png)}.io-dir{margin-top:5px;margin-bottom:5px;text-align:center;font-weight:700}.onboard-led{margin-top:2px;margin-right:10px;margin:5px auto;border:0 dashed #ccc;height:28px;width:28px;display:block}.led-on{background-image:url(img/di_on.png)}.led-off{background-image:url(img/di_off.png)}.div-analog{margin-left:30px;padding:0}.analog{margin-top:2px;margin-right:10px;border:1px solid #ccc;height:20px;width:500px;display:block}.io ul{margin-top:5px;margin-bottom:90px}.io li{margin-left:10px;margin-right:10px;list-style:none;float:left;text-align:center}.pointer{cursor:pointer}.ain{width:0%;height:100%;text-align:center;background:red;float:left;display:block}.conf-menu span{float:left}.conf-menu label{float:left;padding-top:3px;text-align:center;vertical-align:middle;width:70px}.conf-menu ul{margin-top:5px;margin-bottom:600px}.conf-menu li{padding-left:20px;padding-right:20px;list-style:none;float:left;text-align:center;font-weight:700;clear:both}.info label{float:left;text-align:left;width:100px}.info li{text-align:center;clear:both}.info span{vertical-align:middle;float:left;text-align:left;display:block;padding:0;border:0;margin:0}.info div{margin:0 auto;text-align:center;display:table-cell;vertical-align:middle;padding:0 15px 10px 0;background:#ffe4e1}a.tooltip{outline:0}a.tooltip strong{line-height:30px}a.tooltip:hover{text-decoration:none}a.tooltip span{z-index:10;display:none;padding:14px 20px;margin-top:-30px;margin-left:28px;width:150px;line-height:16px}a.tooltip:hover span{display:inline;position:absolute;color:#111;border:1px solid #dca;background:#fffaf0}.callout{z-index:20;position:absolute;top:30px;border:0;left:-12px}a.tooltip span{border-radius:4px;box-shadow:5px 5px 8px #ccc}.btn{background:#3498db;background-image:-webkit-linear-gradient(top,#3498db,#2980b9);background-image:-moz-linear-gradient(top,#3498db,#2980b9);background-image:-ms-linear-gradient(top,#3498db,#2980b9);background-image:-o-linear-gradient(top,#3498db,#2980b9);background-image:linear-gradient(to bottom,#3498db,#2980b9);-webkit-border-radius:28;-moz-border-radius:28;border-radius:28px;color:#fff;font-size:13px;padding:3px 10px 3px 10px;text-decoration:none}.btn:hover{background:#3cb0fd;background-image:-webkit-linear-gradient(top,#3cb0fd,#3498db);background-image:-moz-linear-gradient(top,#3cb0fd,#3498db);background-image:-ms-linear-gradient(top,#3cb0fd,#3498db);background-image:-o-linear-gradient(top,#3cb0fd,#3498db);background-image:linear-gradient(to bottom,#3cb0fd,#3498db);cursor:pointer;text-decoration:none}.width-onoff{width:60px;display:inline-block}.btn-on{background:#3498db}.btn-off{background:silver}</style>\n"\
"\n"\
"<script type='text/javascript' src='jscolor.js'></script> \n"\
"<script> \n"\
"// Here we can adjust defaults for all color pickers on page: \n"\
"jscolor.presets.default = { \n"\
"   palette: [ \n"\
"	    '#FF0000', '#00FF00', '#0000FF', '#ffffff' \n"\
"	], \n"\
"	paletteCols: 4, \n"\
"	hideOnPaletteClick: true, \n"\
"	//width: 271, \n"\
"	//height: 151, \n"\
"	position: 'right', \n"\
"	previewPosition: 'right', \n"\
"	backgroundColor: 'rgba(51,51,51,1)', controlBorderColor: 'rgba(153,153,153,1)', buttonColor: 'rgba(240,240,240,1)', \n"\
"	} \n"\
"</script> \n"\
"<script>\n"\
"var tabLinks=new Array(); \n"\
" var divContents=new Array(); \n"\
" var t_update;  \n"\
" var timer_is_on=0; \n"\
" var t_update_adc;\n"\
" var adctimer_is_on=0;\n"\
" var t_get_rs232; \n"\
" var rs232_timer_on=0;  \n"\
" var adc0_val = 1024;\n"\
" var tmp_adc0_val;\n"\
" \n"\
" function init() \n"\
" { \n"\
"	 var tabListItems=document.getElementById('tabs').childNodes; \n"\
"	 for(var i=0;i<tabListItems.length-1;i++) \n"\
"	 { \n"\
"	 	if(tabListItems[i].nodeName=='LI') \n"\
"		 { \n"\
"			 var tabLink=getFirstChildWithTagName(tabListItems[i],'A'); \n"\
"			 var id=getHash(tabLink.getAttribute('tabid')); \n"\
"			 tabLinks[id]=tabLink; \n"\
"			 divContents[id]=document.getElementById(id); \n"\
"		 } \n"\
"	 } \n"\
"	 var i=0; \n"\
"	 for(var id in tabLinks) \n"\
"	 { \n"\
"		 tabLinks[id].onclick=showTab; \n"\
"		 if(i==0){tabLinks[id].className='selected';} \n"\
"		 i++; \n"\
"	 } \n"\
" }; \n"\
" \n"\
" function showTab() \n"\
" { \n"\
"	 var selectedId=getHash(this.getAttribute('tabid')); \n"\
"	 for(var id in divContents) \n"\
"	 { \n"\
"	 	if(id==selectedId) \n"\
"		 { \n"\
"			 tabLinks[id].className='selected'; \n"\
"			 if(id)divContents[id].className='show'; \n"\
"			 if(selectedId=='tabs2'){updateOutputConfig();}else{;} \n"\
"//			 if(selectedId=='tabs2'){doUpdate();}else{stopUpdate();} \n"\
"//			 if(selectedId=='tabs3'){doADCUpdate();}else{stopADCUpdate();}\n"\
"//			 if(selectedId=='tabs4'){updatePortConfig();}else{;}			 \n"\
"//			 if(selectedId=='tabs5'){doGetRs232Data();}else{stopGetRs232Data();} \n"\
"		 } \n"\
"		 else \n"\
"		 { \n"\
"			 tabLinks[id].className=''; \n"\
"			 if(id)divContents[id].className='hide'; \n"\
"		 } \n"\
"	 } \n"\
"	 return false; \n"\
" }; \n"\
" \n"\
" function getFirstChildWithTagName(element,tagName) \n"\
" { \n"\
"	 for(var i=0; i<element.childNodes.length;i++) \n"\
"	 { \n"\
"		 if(element.childNodes[i].nodeName==tagName) return element.childNodes[i]; \n"\
"	 } \n"\
" }; \n"\
" \n"\
" function getHash(url) \n"\
" { \n"\
"	 var hashPos=url.lastIndexOf('#'); \n"\
"	 return url.substring(hashPos+1); \n"\
" }; \n"\
"\n"\
" function AJAX(url, callback)\n"\
" { \n"\
"	 var req = AJAX_init(); \n"\
"	 req.onreadystatechange = AJAX_processRequest; \n"\
"	 \n"\
"	 function AJAX_init() { \n"\
"		 if (window.XMLHttpRequest) { \n"\
"		 	return new XMLHttpRequest(); \n"\
"		 } else if (window.ActiveXObject) { \n"\
"		 	return new ActiveXObject('Microsoft.XMLHTTP'); \n"\
"		 } \n"\
"	 };\n"\
"	  \n"\
"	 function AJAX_processRequest() { \n"\
"		 if(req.readyState == 4) { \n"\
"		 	if(req.status == 200) { \n"\
"		 	if(callback) \n"\
"		 		callback(req.responseText); \n"\
"		 	} \n"\
"		 } \n"\
"	 }; \n"\
"	 \n"\
"	 this.doGet = function() { \n"\
"		 req.open('GET', url, true); \n"\
"		 req.send(null); \n"\
"	 };\n"\
"	  \n"\
"	 this.doPost = function(body) { \n"\
"		 req.open('POST', url, true); \n"\
"		 req.setRequestHeader('Content-Type', \n"\
"		 'application/x-www-form-urlencoded'); \n"\
"		 req.setRequestHeader('ISAJAX','yes'); \n"\
"		 req.send(body); \n"\
"	 }; \n"\
" }; \n"\
" \n"\
" function $(id){return document.getElementById(id);} \n"\
" \n"\
" function $$(id){return document.getElementsByName(id);} \n"\
" \n"\
" function $$_ie(tag, name){ \n"\
"	 if(!tag){tag='*';}	  \n"\
"	 var elems=document.getElementsByTagName(tag); \n"\
"	 var res=[]; \n"\
"	 for(var i=0;i<elems.length;i++){ \n"\
"		 att=elems[i].getAttribute('name'); \n"\
"		 if(att==name){ \n"\
"		 	res.push(elems[i]); \n"\
"		 } \n"\
"	 } \n"\
"	 return res; \n"\
" } \n"\
" \n"\
" function selset(id,val){\n"\
" 	var o=$(id);\n"\
" 	for(var i=0;i<o.options.length;i++){\n"\
" 		if(i==val){\n"\
" 			o.options[i].selected=true;\n"\
" 			break;\n"\
" 		}\n"\
" 	}\n"\
" }\n"\
" "\
" function selset_val(id,val){"\
" 	var o=$(id);"\
" 	for(var i=0;i<o.options.length;i++){"\
" 		if(o.options[i].value==val){"\
" 			o.options[i].selected=true;"\
" 			break;"\
" 		}"\
" 	}"\
" }"\
"  \n"\
" function selset_name(name, val){\n"\
" 	var o=$$(name);\n"\
" 	for(var i=0;i<o.options.length;i++){\n"\
" 		if(i==val){\n"\
" 			o.options[i].selected=true;\n"\
" 			break;\n"\
" 		}\n"\
" 	}\n"\
" }\n"\
" \n"\
" function BasicSettingCallback(o){ \n"\
"	 var obj;\n"\
"	 $('txtFwver').value=o.ver;\n"\
"	 $('txtDname').value=o.dname;\n"\
"	 $('txtPcode').value=o.pcode; \n"\
"	 $('txtMac').value=o.mac;\n"\
"	 $('txtLip').value=o.lip;	 \n"\
"	 $('txtGw').value=o.gw;\n"\
"	 $('txtSub').value=o.sub;\n"\
"	 $('txtDns').value=o.dns; 	 \n"\
"	 if(typeof(window.external)!='undefined'){\n"\
"	 	obj=$$_ie('input','dhcp');\n"\
"	 }else{\n"\
"	 	obj=$$('dhcp');\n"\
"	 }\n"\
"	 for(var i=0; i<obj.length;i++){\n"\
"	 	if(i==o.dhcp){\n"\
"	 		obj[i].checked=true;	 		\n"\
"	 		break;\n"\
"	 	}\n"\
"	 }	 \n"\
"	 netinfo_block(i);\n"\
"	 	 \n"\
"	 if(typeof(window.external)!='undefined'){\n"\
"	 	obj=$$_ie('input','smode');\n"\
"	 }else{\n"\
"	 	obj=$$('smode');\n"\
"	 }\n"\
"	 for(var i=0; i<obj.length;i++){\n"\
"	 	if(i==o.smode){\n"\
"	 		obj[i].checked=true;	 		\n"\
"	 		break;\n"\
"	 	}\n"\
"	 }	 \n"\
"	 $('txtUniverse').value=o.universe;\n"\
"	 $('txtUSize').value=o.usize;	 \n"\
" } \n"\
" \n"\
" function netinfo_block(o) {\n"\
" 	if(o == 1) { 	// Using DHCP setting, Netinfo inputbox blocked\n"\
"		$('txtLip').disabled=true;	 \n"\
"		$('txtGw').disabled=true;\n"\
"		$('txtSub').disabled=true;\n"\
"		$('txtDns').disabled=true;\n"\
" 	} else {			// Static setting, Netinfo inputbox unblocked\n"\
" 		$('txtLip').disabled=false;	 \n"\
"		$('txtGw').disabled=false;\n"\
"		$('txtSub').disabled=false;\n"\
"		$('txtDns').disabled=false;\n"\
" 	} 	\n"\
" }\n"\
" \n"\
" var dout; \n"\
" var dout_timer=false;\n"\
"\n"\
" function postdata(o){ \n"\
"	 var p=o.attributes['pin'].value; 	 \n"\
"	 var v = 0;	 \n"\
"	 if(o.className=='btn btn-on width-onoff'){v='1';}else{v='0';}	 \n"\
"	 dout_timer=setTimeout(function(){ \n"\
"		 if(dout && dout.abort){dout.abort();} \n"\
"		 dout=new AJAX('dout.cgi', function(t){ \n"\
"		 	try{\n"\
"		 		eval(t);		 		\n"\
"		 		if(t=='1'){		 			\n"\
"		 			o.setAttribute('class','btn btn-on width-onoff');\n"\
"		 		} else {		 			\n"\
"		 			o.setAttribute('class','btn btn-off width-onoff');\n"\
"		 		}		 		\n"\
"		 	}catch(e){alert(e);} \n"\
"		 }); \n"\
"		 dout.doPost('pin='+p+'&val='+v); \n"\
"	 },300); \n"\
" } \n"\
" \n"\
" function IoStatusCallback(o){ \n"\
"	 var i; \n"\
"	 var odout;	 \n"\
"	 var odin; \n"\
"	 var odir;\n"\
"	 var oled;\n"\
"	 var oledset;\n"\
"	 var odoutBtn;\n"\
"	 if(typeof(window.external)!='undefined'){ \n"\
"		 odout=$$_ie('span','dout');		  \n"\
"		 odin=$$_ie('span','din'); 	\n"\
"		 odir=$$_ie('span','iodir');\n"\
"		 oled=$$_ie('span','led');		 \n"\
"		 oledset=$$_ie('button','ledset-btn');\n"\
"		 odoutBtn=$$_ie('button','dout-btn');\n"\
"	 }else{\n"\
"		 odout=$$('dout');		 \n"\
"		 odin=$$('din');\n"\
"		 odir=$$('iodir');\n"\
"		 oled=$$('led');\n"\
"		 oledset=$$('ledset-btn');\n"\
"		 odoutBtn=$$('dout-btn');\n"\
"	 }\n"\
"	 \n"\
"	 // Configurable GPIOs\n"\
"	 for(i=0;i<odout.length;i++){ \n"\
"		 if (o['dout'][i]['v']=='2') { 	// IO direction: Output\n"\
"		 	odoutBtn[i].style.visibility='visible';\n"\
"		 	if(o['din'][i]['v']=='0') {		 		\n"\
"		 		odoutBtn[i].setAttribute('class','btn btn-off width-onoff');\n"\
"		 		odoutBtn[i].textContent='ON';\n"\
"		 	} else {		 		\n"\
"		 		odoutBtn[i].setAttribute('class','btn btn-on width-onoff');\n"\
"		 		odoutBtn[i].textContent='OFF';\n"\
"		 	}		 	\n"\
"		 	odir[i].textContent='Output'; //ok		 	\n"\
"		 } else if(o['dout'][i]['v']=='1') { // IO direction: Input, IO Setting button hide 		 	\n"\
"		 	odoutBtn[i].style.visibility='hidden';\n"\
"		 	odir[i].textContent='Input';\n"\
"		 } else { 							// IO direction: NotUsed, IO Setting button hide		 	\n"\
"		 	odoutBtn[i].style.visibility='hidden';\n"\
"		 	odir[i].textContent='NotUsed';\n"\
"		 } \n"\
"		 		 \n"\
"		 if(o['din'][i]['v']=='0') \n"\
"		 { \n"\
"		 	odin[i].className='di-led di-off'; 		// off\n"\
"		 }else{ 		 	\n"\
"		 	if (o['dout'][i]['v']=='2') {\n"\
"		 		odin[i].className='di-led dio-on'; // Dir-Output on: Blue led\n"\
"		 	} else {		 		\n"\
"		 		odin[i].className='di-led di-on'; // Dir-input on: Green led\n"\
"		 	}\n"\
"		 } \n"\
"	 }	 \n"\
"	 // On-board LED\n"\
"	 for(i=0;i<oled.length;i++){ \n"\
"		if (o['led'][i]['v']=='0') {\n"\
"			oled[i].className='onboard-led led-on';\n"\
"			oledset[i].setAttribute('class','btn btn-on width-onoff');\n"\
"			oledset[i].textContent='OFF';\n"\
"		} else {\n"\
"			oled[i].className='onboard-led led-off';\n"\
"			oledset[i].setAttribute('class','btn btn-off width-onoff');\n"\
"			oledset[i].textContent='ON';\n"\
"		}\n"\
"	 }  \n"\
" } \n"\
"  \n"\
" function updateIO(){ \n"\
"	 var oUpdate; \n"\
"	 setTimeout(function(){\n"\
"	 	oUpdate=new AJAX('io.cgi',function(t){\n"\
"	 		try{eval(t);}catch(e){location.href='/';}\n"\
"	 });	 	 \n"\
"	 oUpdate.doGet();},300);\n"\
"	 t_update=setTimeout('updateIO()',800); \n"\
" } \n"\
" \n"\
" function doUpdate(){ \n"\
"	 if(!timer_is_on) \n"\
"	 { \n"\
"		 timer_is_on=1; \n"\
"		 updateIO(); \n"\
"	 } \n"\
" } \n"\
" \n"\
" function stopUpdate(){ \n"\
"	 clearTimeout(t_update); \n"\
"	 timer_is_on=0; \n"\
" }\n"\
" \n"\
" function updateOutputConfig(){ 	 \n"\
"	 var oUpdate; \n"\
"	 setTimeout(function(){\n"\
"	 	oUpdate=new AJAX('outputconfig.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		});\n"\
"	 	oUpdate.doGet();\n"\
"	 },300);  \n"\
" }\n"\
" \n"\
"  function OutputConfigCallback(o){ \n"\
"	 var i; \n"\
"    for(i=0;i<8;i++){ \n"\
"       selset_val('selProto_p' + i,o['proto'][i]['p']); \n"\
"       selset_val('selIO_p' + i,o['pin'][i]['v']); \n"\
"	    $('txtStart_p' + i).value=o['start'][i]['s']; \n"\
"	    $('txtChannels_p' + i).value=o['channels'][i]['a']; \n"\
"    } \n"\
" }  \n"\
" \n"\
" function updatePortConfig(){ 	 \n"\
"	 var oUpdate; \n"\
"	 setTimeout(function(){\n"\
"	 	oUpdate=new AJAX('portconfig.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		});\n"\
"	 	oUpdate.doGet();\n"\
"	 },300);  \n"\
" }\n"\
" \n"\
"  function PortConfigCallback(o){ \n"\
"	 var i; \n"\
"	 var odstate; 	 \n"\
"	 var odir;\n"\
"	 var ostart;	 \n"\
"    var ochannels; \n"\
"	 if(typeof(window.external)!='undefined'){ \n"\
"		 odstate=$$_ie('span','dstate'); \n"\
"		 odir=$$_ie('select','dir'); 	\n"\
"	 	 ostart=$$_ie('input','start');	\n"\
"        ochannels=$$_ie('input','channels'); \n"\
"	 }else{\n"\
"		 odstate=$$('dstate');\n"\
"		 odir=$$('dir');\n"\
"		 ostart=$$('start');\n"\
"        ochannels=$$('channels');\n"\
"	 }	 \n"\
"	 \n"\
"	 for(i=0;i<odstate.length;i++){ 		 \n"\
"		if(o['dir'][i]['v']=='2') {			// IO Direction: Output \n"\
"			if(o['dstate'][i]['v']=='0') {\n"\
"				odstate[i].className='di-led di-off';// LED off\n"\
"			} else {\n"\
"				odstate[i].className='di-led dio-on'; // Out: Blue LED\n"\
"			}\n"\
"		} else if(o['dir'][i]['v']=='1') { 	// IO Direction: Input\n"\
"			if(o['dstate'][i]['v']=='0') {\n"\
"				odstate[i].className='di-led di-off';// LED off\n"\
"			} else {\n"\
"				odstate[i].className='di-led di-on'; // In: Green LED\n"\
"			}\n"\
"		} else {							// IO not used\n"\
"			odstate[i].className='di-led d-no-use';\n"\
"		}\n"\
"		 \n"\
"		for(var j=0;j<odir[i].options.length;j++){	// Select\n"\
"			if(j==o['dir'][i]['v']){\n"\
"				odir[i].options[j].selected=true;\n"\
"				break;\n"\
"			}\n"\
"		}			 \n"\
"		ostart[i].value = o['start'][i]['s'];	// start address \n"\
"       ochannels[i].value = o['channels'][i]['a']; // channel count \n"\
"	 }	\n"\
" }  \n"\
" \n"\
" function save_channel(o){ \n"\
"	 var p=o.attributes['pin'].value; 	 \n"\
"	 var str=$('txtStart_d'+p).value;	 \n"\
"    var strCh=$('txtChannels_d'+p).value; \n"\
"    var strPort=$('selDir_d'+p).value;   \n"\
"	 setTimeout(function(){ 		 \n"\
"		 dout=new AJAX('save_channel.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		 }); \n"\
"		 dout.doPost('pin='+p+'&Start='+str+'&Channels='+strCh+'&Port='+strPort); \n"\
"		 alert('Settings for D'+p+' changed.');\n"\
"	 },300); 	 	 \n"\
"	 setTimeout('updatePortConfig()',800*1);\n"\
" } \n"\
" \n"\
" function dir_change(o){\n"\
" 	 var p=o.attributes['pin'].value;\n"\
" 	 var v=o.value;\n"\
" 	 setTimeout(function(){ 		 \n"\
"		 dout=new AJAX('dir_change.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		 }); \n"\
"		 dout.doPost('pin='+p+'&dir='+v); 		 \n"\
"	 },300);\n"\
"	 setTimeout('updatePortConfig()',800*1);\n"\
" }\n"\
" \n"\
" function testmode_set(o){\n"\
" 	 setTimeout(function(){ 		 \n"\
"		 dout=new AJAX('set_testmode.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		 }); \n"\
"		 dout.doPost('testmode='+o); 		 \n"\
"	 },300);\n"\
" }\n"\
" \n"\
" function testtype_set(o){\n"\
" 	 var p=o.attributes['port'].value;\n"\
"    var ttype=$('selTmode_p'+p).value; \n"\
"	 var col=$('txtColor_p'+p).value;	 \n"\
" 	 setTimeout(function(){ 		 \n"\
"		 dout=new AJAX('set_testpattern.cgi', function(t){ \n"\
"		 	try{eval(t);}catch(e){alert(e);} \n"\
"		 }); \n"\
"		 dout.doPost('port='+p+'&testtype='+ttype+'&color='+col); 		 \n"\
"	 },300);\n"\
" }\n"\
" \n"\
" function io_status_factory_reset(){ \n"\
" 	var v=1;	 \n"\
"	if(confirm('Factory Reset: IO Direction / Status / Alias?'))\n"\
"	{\n"\
"		 setTimeout(function(){ 		 \n"\
"			 dout=new AJAX('set_default_io_status.cgi', function(t){ \n"\
"			 	try{eval(t);}catch(e){alert(e);} \n"\
"			 }); \n"\
"			 dout.doPost('io_reset='+v); 			 \n"\
"		 },300); 	 	 \n"\
"		 setTimeout('updatePortConfig()',1500*1);\n"\
"	}\n"\
" }\n"\
" \n"\
" function ADCStatusCallback(o){\n"\
" 	var i;\n"\
" 	var oAin;\n"\
" 	var oAinval; \n"\
"	if(typeof(window.external)!='undefined'){ 	\n"\
"		oAin=$$_ie('strong','ain');\n"\
"		oAinval=$$_ie('span','ainval');\n"\
"	}else{		 \n"\
"		oAin=$$('ain');\n"\
"		oAinval=$$('ainval');\n"\
"	}\n"\
"	\n"\
"	for(i=0;i<oAin.length;i++){ \n"\
"		oAin[i].style.width=o['ain'][i]['v']*500/5095+'px'; // 0~4095 + margin\n"\
"		oAinval[i].textContent = o['ain'][i]['v'];	\n"\
"	} \n"\
" }\n"\
" \n"\
" function updateADC(){ \n"\
"	 var oUpdate; \n"\
"	 setTimeout(function(){\n"\
"	 	oUpdate=new AJAX('adc.cgi',function(t){try{eval(t);\n"\
"	 	}catch(e){location.href='/';}\n"\
"	 });\n"\
"	 \n"\
"	 /*oUpdate.doPost('');},300);*/ \n"\
"	 oUpdate.doGet();},300);\n"\
"	 t_update_adc=setTimeout('updateADC()',500); \n"\
" } \n"\
" \n"\
" function doADCUpdate(){ \n"\
"	 if(!adctimer_is_on) \n"\
"	 { \n"\
"		 adctimer_is_on=1; \n"\
"		 updateADC(); \n"\
"	 } \n"\
" } \n"\
" \n"\
" function stopADCUpdate(){ \n"\
"	 clearTimeout(t_update_adc); \n"\
"	 adctimer_is_on=0; \n"\
" } \n"\
" \n"\
" function getRs232Data(){ \n"\
"	 var oUpdate; \n"\
"	 setTimeout(function(){\n"\
"	 	oUpdate=new AJAX('get_serial_data.cgi',function(t){try{eval(t);}catch(e){location.href='/';}}); \n"\
"	 	/*oUpdate.doPost('');*/\n"\
"	 	oUpdate.doGet();\n"\
"	 },300); \n"\
"	 \n"\
"	 t_get_rs232=setTimeout('getRs232Data()',1000); \n"\
" } \n"\
" \n"\
" function doGetRs232Data(){ \n"\
" 	if(!rs232_timer_on){\n"\
" 		rs232_timer_on=1;\n"\
" 		getRs232Data();\n"\
" 	} \n"\
" } \n"\
" \n"\
" function stopGetRs232Data(){ \n"\
" 	clearTimeout(t_get_rs232);\n"\
" 	rs232_timer_on=0; \n"\
" } \n"\
" \n"\
" function getRs232DataCallback(o){ \n"\
"	 var obj=$('txtRx'); \n"\
"	 if(obj) obj.value=obj.value+o.data; \n"\
" }\n"\
"  \n"\
" function clear_textarea(){ \n"\
"	 var obj=$('txtRx'); \n"\
"	 if(obj)obj.value=''; \n"\
" }\n"\
"  \n"\
" function send_to_rs232(){ \n"\
"	 var obj=$('txtTx'); \n"\
"	 var tx_data; \n"\
"	 var post_serial_data; \n"\
"	 if(obj){ \n"\
"		 tx_data=$('txtTx').value; \n"\
"		 var len=tx_data.length; \n"\
"		 if(len>0){ \n"\
"			 var post_timer=setTimeout(function(){ \n"\
"				 post_serial_data=new AJAX('tx_serial_data.cgi', function(t){ \n"\
"				 	try{eval(t);}catch(e){alert(e);} \n"\
"				 }); \n"\
"				 post_serial_data.doPost('data='+tx_data);  \n"\
"			 },300); \n"\
"		 } \n"\
"		 $('txtTx').value=''; // claer\n"\
"	 } \n"\
" } \n"\
" \n"\
" function len_chk(o) {\n"\
" 	var len = o.value.length;\n"\
" 	if(len > 24) {\n"\
" 		alert('Name/Alias up to 24 bytes can be entered'); 		\n"\
" 		o.value = o.value.substring(0, 24);  		\n"\
" 	}\n"\
" }\n"\
" \n"\
" function ip_chk(o) {\n"\
" 	var len = o.value.length;\n"\
" 	var pattern = /(^[0-9\.\b]+$)/; // Regular expression 	\n"\
" 	if(!pattern.test(o.value)) {\n"\
" 		alert('Allow only numbers and dot(.)'); 		\n"\
" 		o.value = o.value.substring(0, (o.value.length-1)); 			\n"\
" 	} 	\n"\
" 	if(len > 15) {\n"\
" 		o.value = o.value.substring(0, 15);  		\n"\
" 	}\n"\
" }\n"\
"</script>\n"\
"<link href=img/favicon.ico rel='shortcut icon' type=image/x-icon>\n"\
"</head>\n"\
"<body onload=init();>\n"\
"<div id=header>\n"\
"<h2>PicoPixel Configuration</h2>\n"\
"</div>\n"\
"<div class=usual>\n"\
"<ul id=tabs>\n"\
"<li><a href=#Settings accesskey=1 tabid=#tabs1>Device Settings</a></li>\n"\
"<li><a href=#OUTCONFIG accesskey=2 tabid=#tabs2>Output Configuration</a></li>\n"\
"<li><a href=#Test accesskey=3 tabid=#tabs3>Test Menu</a></li>\n"\
"<li><a href=#IOCONFIG accesskey=4 tabid=#tabs4>I/O Configuration</a></li>\n"\
"<li><a href=#Serial accesskey=5 tabid=#tabs5>Serial Data</a></li>\n"\
"</ul>\n"\
"<div class=show id=tabs1>\n"\
"<form action=config.cgi id=frmParam method=post>\n"\
"<h3>Device Information</h3>\n"\
"<div class=ipt>\n"\
"<p><label>Firmware version:</label><input id=txtFwver size=20 disabled></p>\n"\
"<p>\n"\
"<label for=txtDname>Device name:</label>\n"\
"<a href=# class=tooltip>\n"\
"<input id=txtDname size=20 name=devicename onkeyup=len_chk(this); maxlength=25>\n"\
"<span> Up to 24 bytes </span>\n"\
"</a>\n"\
"</p>\n"\
"<p><label>Product code: </label><input id=txtPcode size=20 disabled></p>\n"\
"<p><label>MAC address: </label><input id=txtMac size=20 disabled></p>\n"\
"</div>\n"\
"<h3>Network Configuration</h3>\n"\
"<div>\n"\
"<input id=rdStatic name=dhcp onclick=netinfo_block(this.value); type=radio value=0><label for=rdStatic>Static IP</label>\n"\
"<input id=rdDhcp name=dhcp onclick=netinfo_block(this.value); type=radio value=1><label for=rdDhcp>DHCP</label>\n"\
"</div>\n"\
"<div class=ipt>\n"\
"<p>\n"\
"<label for=txtSip>Device IP address:</label><input id=txtLip size=20 name=lip onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"<p>\n"\
"<label for=txtGw>Gateway:</label><input id=txtGw size=20 name=gw onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"<p>\n"\
"<label for=txtSub>Subnet mask:</label><input id=txtSub size=20 name=sub onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"<p>\n"\
"<label for=txtDns>DNS server:</label><input id=txtDns size=20 name=dns onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"</div>\n"\
"<h3>Server Mode</h3>\n"\
"<div>\n"\
"<p>\n"\
"<input id=rdZPP name=smode type=radio value=0><label for=rdZPP>ZPP</label>\n"\
"<input id=rdE131 name=smode type=radio value=1><label for=rdE131>E1.31</label>\n"\
"</p>\n"\
"<p>\n"\
"<label for=txtUniverse>Universe Start:</label><input id=txtUniverse size=6 name=Universe onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"<p>\n"\
"<label for=txtUSize>Universe Size:</label><input id=txtUSize size=6 name=USize onkeyup=ip_chk(this);>\n"\
"</p>\n"\
"</div>\n"\
"<div>\n"\
"<input type=submit value='Save Settings and Reboot' class=btn>\n"\
"</div>\n"\
"</form>\n"\
"</div>\n"\
"<div class=hide id=tabs2>\n"\
"<h3>Output Configuration</h3>\n"\
"<form action=set_portconfig.cgi id=frmOutputConfig method=post>\n"\
"<table>\n"\
"<thead><tr><th>Port</th><th>Protocol</th><th>IO Pin</th><th>Start address</th><th>Channel count</th></tr></thead>\n"\
"<tbody>\n"\
"<tr><td>P0</td>\n"\
"<td><select id=selProto_p0 name=Proto_p0>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p0 name=IO_p0>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p0 size=6 name=start_p0 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p0 size=6 name=channels_p0 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P1</td>\n"\
"<td><select id=selProto_p1 name=Proto_p1>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p1 name=IO_p1>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p1 size=6 name=start_p1 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p1 size=6 name=channels_p1 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P2</td>\n"\
"<td><select id=selProto_p2 name=Proto_p2>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p2 name=IO_p2>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p2 size=6 name=start_p2 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p2 size=6 name=channels_p2 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P3</td>\n"\
"<td><select id=selProto_p3 name=Proto_p3>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p3 name=IO_p3>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p3 size=6 name=start_p3 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p3 size=6 name=channels_p3 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P4</td>\n"\
"<td><select id=selProto_p4 name=Proto_p4>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p4 name=IO_p4>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p4 size=6 name=start_p4 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p4 size=6 name=channels_p4 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P5</td>\n"\
"<td><select id=selProto_p5 name=Proto_p5>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p5 name=IO_p5>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p5 size=6 name=start_p5 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p5 size=6 name=channels_p5 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P6</td>\n"\
"<td><select id=selProto_p6 name=Proto_p6>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p6 name=IO_p6>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p6 size=6 name=start_p6 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p6 size=6 name=channels_p6 maxlength=6></td>\n"\
"</tr>\n"\
"<tr><td>P7</td>\n"\
"<td><select id=selProto_p7 name=Proto_p7>\n"\
"<option value=0>Not Used</option>\n"\
"<option value=1>WS2812</option>\n"\
"<option value=8>DMX</option>\n"\
"</select></td>\n"\
"<td><select id=selIO_p7 name=IO_p7>\n"\
"<option value=0>DIO0</option>\n"\
"<option value=1>DIO1</option>\n"\
"<option value=2>DIO2</option>\n"\
"<option value=3>DIO3</option>\n"\
"<option value=4>DIO4</option>\n"\
"<option value=5>DIO5</option>\n"\
"<option value=6>DIO6</option>\n"\
"<option value=7>DIO7</option>\n"\
"<option value=8>DIO8</option>\n"\
"<option value=9>DIO9</option>\n"\
"<option value=10>DIO10</option>\n"\
"<option value=11>DIO11</option>\n"\
"<option value=12>DIO12</option>\n"\
"<option value=13>DIO13</option>\n"\
"<option value=14>DIO14</option>\n"\
"<option value=15>DIO15</option>\n"\
"</select></td>\n"\
"<td><input id=txtStart_p7 size=6 name=start_p7 onkeyup=len_chk(this); maxlength=6></td>\n"\
"<td><input id=txtChannels_p7 size=6 name=channels_p7 maxlength=6></td>\n"\
"</tr>\n"\
"</tbody></table>\n"\
"<div>\n"\
"<input type=submit value='Save Settings and Reboot' class=btn>\n"\
"</div>\n"\
"</form>\n"\
"</div>\n"\
\
"<div class=hide id=tabs3>\n"\
"<h3>Output Test Menu</h3>\n"\
"<p>\n"\
"<h4>Operating Mode</h4>\n"\
"<input id=rdRun name=tmode onclick=testmode_set(this.value); type=radio value=0 checked><label for=rdRun>Run</label>\n"\
"<input id=rdTest name=tmode onclick=testmode_set(this.value); type=radio value=1><label for=rdTest>Test</label>\n"\
"</p>\n"\
"<table>\n"\
"<thead><tr><th>Port</th><th>Test mode</th><th>Color</th></tr></thead>\n"\
"<tbody>\n"\
"<tr><td>P0</td>\n"\
"<td><select id=selTmode_p0 name=Tmode_p0 onchange=testtype_set(this); port=0>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p0 name=Color_p0 value='3399FF' onchange=testtype_set(this); port=0 data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P1</td>\n"\
"<td><select id=selTmode_p1 name=Tmode_p1>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p1 name=Color_p1 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P2</td>\n"\
"<td><select id=selTmode_p2 name=Tmode_p2>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p2 name=Color_p2 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P3</td>\n"\
"<td><select id=selTmode_p3 name=Tmode_p3>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p3 name=Color_p3 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P4</td>\n"\
"<td><select id=selTmode_p4 name=Tmode_p4>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p4 name=Color_p4 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P5</td>\n"\
"<td><select id=selTmode_p5 name=Tmode_p5>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p5 name=Color_p5 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P6</td>\n"\
"<td><select id=selTmode_p6 name=Tmode_p6>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p6 name=Color_p6 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"<tr><td>P7</td>\n"\
"<td><select id=selTmode_p7 name=Tmode_p7>\n"\
"<option value=0>Off</option>\n"\
"<option value=1>Solid</option>\n"\
"<option value=2>Chase</option>\n"\
"<option value=3>Color Wash</option>\n"\
"</select></td>\n"\
"<td><input id=txtColor_p7 name=Color_p7 value='3399FF' data-jscolor='{}'></td>\n"\
"</tr>\n"\
"</tbody></table>\n"\
"</div>\n"\
\
"<div class=hide id=tabs4>\n"\
"<h3>Port Configuration</h3>\n"\
"<div class=conf-menu>\n"\
"<div align=left>\n"\
"<input type=button value='IO Settings Factory Reset and Reboot' onclick=io_status_factory_reset(); class=btn>\n"\
"</div>\n"\
"<table style='font-weight:bold'><tr><td style='width:14ch'></td><td style='width:5ch'>Port</td><td style='width:10ch'>Channel</td><td style='width:10ch'>Start</td><td style='width:9ch'>Channels</td></tr></table>\n"\
"<ul>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D0</label>\n"\
"<select id=selDir_d0 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d0 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d0 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=0>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D1</label>\n"\
"<select id=selDir_d1 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d1 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d1 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=1>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D2</label>\n"\
"<select id=selDir_d2 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d2 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d2 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=2>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D3</label>\n"\
"<select id=selDir_d3 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d3 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d3 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=3>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D4</label>\n"\
"<select id=selDir_d4 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d4 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d4 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=4>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D5</label>\n"\
"<select id=selDir_d5 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d5 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d5 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=5>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D6</label>\n"\
"<select id=selDir_d6 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d6 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d6 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=6>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D7</label>\n"\
"<select id=selDir_d7 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d7 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d7 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=7>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D8</label>\n"\
"<select id=selDir_d8 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d8 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d8 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=8>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D9</label>\n"\
"<select id=selDir_d9 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d9 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d9 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=9>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D10</label>\n"\
"<select id=selDir_d10 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d10 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d10 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=10>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D11</label>\n"\
"<select id=selDir_d11 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d11 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d11 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=11>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D12</label>\n"\
"<select id=selDir_d12 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d12 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d12 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=12>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D13</label>\n"\
"<select id=selDir_d13 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d13 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d13 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=13>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D14</label>\n"\
"<select id=selDir_d14 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d14 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d14 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=14>\n"\
"</li>\n"\
"<li>\n"\
"<span class='di-led di-off' name=dstate></span>\n"\
"<label for=selDir>D15</label>\n"\
"<select id=selDir_d15 name=dir>\n"\
"<option value=0>NotUsed</option>\n"\
"<option value=1>Port 1</option>\n"\
"<option value=2>Port 2</option>\n"\
"<option value=3>Port 3</option>\n"\
"<option value=4>Port 4</option>\n"\
"<option value=5>Port 5</option>\n"\
"<option value=6>Port 6</option>\n"\
"<option value=7>Port 7</option>\n"\
"<option value=8>Port 8</option>\n"\
"</select>\n"\
"<input id=txtStart_d15 size=6 name=start onkeyup=len_chk(this); maxlength=6>\n"\
"<input id=txtChannels_d15 size=6 name=channels maxlength=6>\n"\
"<input type=button value='Save channel settings' onclick=save_channel(this); class=btn pin=15>\n"\
"</li>\n"\
"</ul>\n"\
"</div>\n"\
"</div>\n"\
"<div class=hide id=tabs5>\n"\
"<h3>Serial Data</h3>\n"\
"<div class=ipt>\n"\
"<p><label for=txtTx>Data to send:</label><input id=txtTx size=32 name=txdata><input type=button value=Send onclick=send_to_rs232(); class=btn></p>\n"\
"<p><label for=txtRx>Received data:</label><textarea cols=30 disabled id=txtRx name=rxdata rows=5></textarea><input type=button value=Clear onclick=clear_textarea(); class=btn></p>\n"\
"</div>\n"\
"</div>\n"\
"</div>\n"\
"<div style='margin:5px 5px;clear:both'>\n"\
"<center>\n"\
"©Copyright 2014 WIZnet Co., Ltd.\n"\
"</center>\n"\
"</div>\n"\
"<script src='widget.cgi'></script>\n"\
"</body>\n"\
"</html>\n"
