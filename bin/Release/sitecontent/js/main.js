function isFieldExsist(array, field)
{
	for(var i = 0; i < array.length; i++)
	{	
		if(array[i].name == field) return true;		
	}
	return false;
}

function setResultList(jsonData)
{
	var dataSet = [];	
	var respCnt = parseInt(jsonData.requestCnt);
	var allCnt = 0;	
	for(var i = 0; i < respCnt; i++)
	{
		var itemsCnt = jsonData[i].response.count;		
		for(var index in jsonData[i].response.items)
		{	
			var item = jsonData[i].response.items[index];
			dataSet.push(item);			
			allCnt++;				
		}		
	}		
	$("#taskStatus").text("Количество найденых записей: "+allCnt);
	$("#resultList").text(dataSet.join());		
}

function initTables()
{
	var tableCnt = $("input[name='tablesCnt']").val();	
	if(tableCnt > 0)
	{	
		for (var i = 1; i <= tableCnt; i++)
		{			
			var tableName = "Table"+(i).toString();
			var tmp = $("input[name='table"+(i).toString()+"Fields']").val();	
			if(tmp.length < 12) continue;			
			var tableFields = JSON.parse(tmp).array;	
									
			tmp = $("input[name='table"+(i).toString()+"Data']").val();	
			tmp = tmp.replace(/\r|\n/g, '');	
			if(tmp.length < 12) continue;				
			var tableData = JSON.parse(tmp).array;								
			
			tmp = $("input[name='table"+(i).toString()+"Func']").val();						
			var clickFunc = new Function("elem", tmp);
							
			$("#"+tableName).jsGrid({
				width: "90%",
				//height: $(window).height()*0.5,
 
				inserting: false,
				editing: false,
				sorting: true,
				paging: true,
				pageSize: 20,
								 
				data: tableData,
				fields: tableFields,
				
				rowDoubleClick : clickFunc
    		});
 		}
	}
}

function setDataGrid(jsonData)
{
	$("#resultList").hide();
	var dataSet = [];
	var vkFields = [{name: "id", type: "number"}];
	var respCnt = parseInt(jsonData.requestCnt);
	var allCnt = 0;	
	for(var i = 0; i < respCnt; i++)
	{
		var itemsCnt = jsonData[i].response.count;		
		for(var index in jsonData[i].response.items)
		{	
			var item = jsonData[i].response.items[index];
			for(var index in item)
			{
				if(!isFieldExsist(vkFields,index)) vkFields.push({name: index, type: "text"});   
			}				
			dataSet.push(item);			
			allCnt++;		
			if(allCnt > 500) break;
		}
		if(allCnt > 500) break;
	}			
	if(vkFields.length == 1)	
	{
		$("#jsGrid").hide();
		$("#resultList").show();
		setResultList(jsonData);		
		return;
	}
	$("#taskStatus").text("Количество найденых записей: "+jsonData.count);
		
	$("#jsGrid").jsGrid({
		width: "100%",
		height: $(window).height()*0.5,
 
		inserting: false,
		editing: false,
		sorting: true,
		paging: true,
		pageSize: 20,
 
		data: dataSet,
		fields: vkFields,
 			
		rowDoubleClick : function (elem) {
			var uri = "?page=user&id=" + elem.item.id;
			var newWindow = window.open(uri, "_blank");
			newWindow.focus();
     	}
    });
}

function saveToFile(fileName, data, mimeType) 
{
	var pageData = "data:"+mimeType+";charset=utf-8," + encodeURIComponent(data);
	document.href = pageData;
	document.target = "_blank";
	document.download = fileName;
	
}

function vkGetFrends(vkUserId)
{
	var comUrl = '?command=vkGetFrends';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&vkUserId='+vkUserId;
					
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView .frendsTaskHash").css("visibility","visible");
  		$('#taskIdFrends').attr("href", ("?page=task&hash="+msg));
  		$('#taskIdFrends').text(msg);  		
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});
}

function vkGetGroups(vkUserId)
{
	var comUrl = '?command=vkGetGroups';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&vkUserId='+vkUserId;
					
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView .groupTaskHash").css("visibility","visible");
  		$('#taskIdGroups').attr("href", ("?page=task&hash="+msg));
  		$('#taskIdGroups').text(msg);  		
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});
}

function vkGetPosts(ownerId)
{
	var comUrl = '?command=vkGetPosts';	
	var userId = $("input[name='user_id']").val();
	var postsCnt = $("input[name='postsCnt']").val();
	var sortMode = $("#postsSortMode").val();
	var postData = '&user_id='+userId+'&ownerId='+ownerId+"&postsCnt="+postsCnt+"&sortMode="+sortMode;
					
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView .groupTaskHash").css("visibility","visible");
  		$('#taskIdPosts').attr("href", ("?page=task&hash="+msg));
  		$('#taskIdPosts').text(msg);  		
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});
}

function vkCheckResult()
{
	var taskId = $('#taskId').val();
	var comUrl = '?command=vkGetSearchResult';	
	var userId = $("input[name='_id']").val();
	var postData = '&user_id='+userId+'&taskId='+taskId;
	var form = $('#vkSearchForm');
	var resultMode = $("input[name=resultMode]:checked").val();  
			
  	if(resultMode == "resJSON" || resultMode == "resCSV")
  	{
  		//saveToFile(taskId.toString()+".txt",msg, "application/json");
  		form.submit();
  		return;
  	}
	
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  	
  		if(msg == "Not ready")
  		{
  			$("#taskStatus").text("Запрос в обработке, попробуйте проверить результат через 30 секунд");
  			return msg;
  		}  		
  		var resultData = JSON.parse(msg);  		
  		$("#jsGrid").show();
  		setDataGrid(resultData);  		
  		
  		return '';	
  	},
	error: function () 
  	{
  		$("#taskStatus").text("Произошла ошибка во время выполнения запроса");
  		return '';
  	}
	});			

}

function vkUserSearch()
{		
	var q 			= $('#q').val();
	var city 		= $('#city').val();
	var sex 			= $('select#sex').val();
	var status 		= $('select#status').val();
	var sort 		= $('select#sort').val();
	var age_from 	= $('#age_from').val();
	var age_to 		= $('#age_to').val();
	var birth_year = $('#birth_year').val();
	var birth_month= $('#birth_month').val();
	var birth_day 	= $('#birth_day').val();
	var online 		= $('#online').is(':checked');
	var has_photo 	= $('#has_photo').is(':checked');
	var university = $('#university').val();
	var school 		= $('#school').val();
	var interests 	= $('#interests').val();
	var group_id 	= $('#group_id').val();
	var fields 		= $('#fields').val();
	var isNeedOnlyId 	= $('#isNeedOnlyId').is(':checked');

	var comUrl = '?command=vkUserSearch';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&q='+q+'&city='+city+'&sex='+sex+'&status='+status+'&sort='+sort;	
	postData += '&age_from='+age_from+'&age_to='+age_to+'&birth_year='+birth_year+'&birth_month='+birth_month;
	postData += '&birth_day='+birth_day+'&online='+online+'&has_photo='+has_photo+'&university='+university;
	postData += '&school='+school+'&interests='+interests+'&group_id='+group_id+'&fields='+fields+'&isNeedOnlyId='+isNeedOnlyId;
					
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView").css("visibility","visible");
  		$('#taskId').attr("href", ("?page=task&hash="+msg));
  		$('#taskId').text(msg);
  		//$('#taskId').val(msg);
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});	
}

function vkGroupSearch()
{		
	var q 			= $('#q').val();
	var city 		= $('#city').val();	
	var sort 		= $('select#sort').val();	
	var isNeedOnlyId 	= $('#isNeedOnlyId').is(':checked');

	var comUrl = '?command=vkGroupSearch';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&q='+q+'&city='+city+'&sort='+sort+'&isNeedOnlyId='+isNeedOnlyId;	

	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView").css("visibility","visible");
  		$('#taskId').attr("href", ("?page=task&hash="+msg));
  		$('#taskId').text(msg);  		
  		//$('#taskId').val(msg);
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});	
}
function vkPostSearch()
{		
	var q 				= $('#q').val();
	var ownerId 		= $('#ownerId').val();	
	var isNeedOnlyId 	= $('#isNeedOnlyId').is(':checked');

	var comUrl = '?command=vkPostSearch';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&q='+q+'&owner='+ownerId+'&isNeedOnlyId='+isNeedOnlyId;	

	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{    		
		$(".taskHashView").css("visibility","visible");
  		$('#taskId').attr("href", ("?page=task&hash="+msg));
  		$('#taskId').text(msg);  		
  		//$('#taskId').val(msg);
  		return msg;	
  	},
	error: function (msg) 
  	{  		
  		return '';
  	}
	});	
}

function vkAnalize()
{		
	var city 		= $('#city').val();	
	var sex 			= $('select#sex').val();
	var startAge 	= $('#startAge').val();
	var endAge 		= $('#endAge').val();
	var ids 			= $("#ids").text();

	var comUrl = '?command=vkAnalize';	
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id='+userId+'&sex='+sex+'&city='+city+'&startAge='+startAge+'&endAge='+endAge+'&ids='+ids;	

	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData, 
  	success: function(msg)
  	{  
  		$(".taskHashView").css("visibility","visible");
  		$('#taskId').attr("href", ("?page=analizeResult&taskId="+msg));
  		$('#taskId').text(msg); 
  		return msg;	
  	},
  		
	error: function (msg) 
  	{  		
  		return '';
  	}
	});	
}

function showVers(elem, mediaType)
{
	var selectedVerId = $(elem).val();
	var iframeElem = $('.page-viewer').first();
	var changeLogElem = $('#changeLog');	
	
	var comUrl = '?command=getversinfo';	
	var postData = "verid=" + selectedVerId;		
	var result = '';	
						
	$.ajax({
	type: 'POST',
  	url: comUrl,
  	data: postData,
  	async: false,
  	success: function(msg)
  	{
  		result = msg;
  		return msg;	
  	},
	error: function () 
  	{
  		return '';
  	}
	});	
		
	if(result.length > 0)
	{
		var delimPos  = result.indexOf("{CL:}", 0);
		if (delimPos == -1) return; 
		var pathToDoc = '/usercontent/'+String(mediaType)+'/' + result.substr(0, delimPos);
		var changeLogData = result.substr(delimPos + 5);
		alert(result);				
		$(changeLogElem).empty();
		$(changeLogElem).append(changeLogData);	
		$('input[name="urlToDoc"]').val(pathToDoc);	
		var url = 'http://docs.google.com/gview?url='+pathToDoc+'&embedded=true';		
		$(iframeElem).attr('src',url);
	}
}

var remouteDataMatcher = function(type) {
  return function findMatches(q, cb) {
    var matches, substringRegex;
    matches = [];
    
    var command = "";    
	 var value = "";
    if(type == "city") 
    {
    	command = '?command=getCities';
    	value = $('.cityBox .tt-input').val();
    }    
    if(type == "school") 
    {
    	var city = $('#city').val();
    	command = '?command=getSchools';
    	value = $('.schoolBox .tt-input').val() + '&city=' + city;
    }
    if(type == "university") 
    {
    	var city = $('#city').val();
    	command = '?command=getUniversities';
    	value = $('.uniBox .tt-input').val() + '&city=' + city;
    }

	 var strs = "";	 
    var queryStr = command + '&input=' + value;
    if(value.length > 2) strs = getInfo(queryStr);
       
    $.each(strs, function(i,str) {    
        matches.push(str);    
    });
       
    cb(matches);
  };
};

function getInfo(queryStr)
{
		var comUrl = queryStr;					
		var postData = '';		
		var result = '';	
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		async: false,
  		success: function(msg)
  		{
  			result = msg;
  			return msg;	
  		},
		error: function () 
  		{
  			return ' ';
  		}
		});		
		return result.split(',');	
}

function getTagsList()
{
		var comUrl = '?command=gettags';			
		var postData = '';		
		var result = '';	
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		async: false,
  		success: function(msg)
  		{
  			result = msg;
  			return msg;	
  		},
		error: function () 
  		{
  			return ' ';
  		}
		});		
		return result
}

function getGenresList()
{
		var comUrl = '?command=getgenres';			
		var postData = '';	
		var result = '';
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		async: false,
  		success: function(msg)
  		{   				
    		result = msg;
  			return msg;	
  		},
		error: function () 
  		{
  			return ' ';
  		}
		});	
		
		return result;	
}

function logout() 
{
	var comUrl = '?command=logout';			
	var userId = $("input[name='user_id']").val();
	var postData = '&user_id=' + userId;	
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{   				
    		location.reload();		
  		},
		error: function () 
  		{
  				
  		}
		});	
}

function answerClick(block, insertWhat, threadId)
{		
		var blockId = "#" + block;
		
		$("input[name='thread_id']").val(threadId);
		$("input[name='parent_id']").val(block);		
		$(insertWhat).insertAfter(blockId);
		
		$(".new_post_form").show();
		$(window).scrollTop($('.new_post_form').offset().top - 100);
}

function submitClick(elem)
{
		$("input[type='submit']").prop("disabled", true);
		elem.submit();
}

function newThreadFormHide()
{
	var status = $('.new_thread_form').css('display');
	
	if(status == 'none')
	{
		$('#new_thread_form_status').text('[Скрыть]');
		$('.new_thread_form').css({"display": "block"});
	}
	else
	if(status == 'block')
	{
		$('#new_thread_form_status').text('[Показать]');
		$('.new_thread_form').css({"display": "none"});
	}	
}

function hideClick(blockId, isHidden)
{
		//$(blockId).css({"display": "none"});
		var comUrl = '?command=hide';
		var metod  = 'add';
		if (isHidden) metod  = 'remove';	
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId +'&metod=' + metod + "&user_id=" + userId;		
		showWaitIco = true;
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
    		showWaitIco = false;
  		},
		error: function () 
  		{
  			showWaitIco = false;
  		}
		});
}

function delClick(blockId)
{
		var comUrl = '?command=del';
		var userId = $("input[name='user_id']").val();
		var id = 'id=' + blockId + "&user_id=" + userId;		
		showWaitIco = true;
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: id,
  		success: function(msg)
  		{  			
    		location.reload();
			showWaitIco = false;
  		},
  		error: function () 
  		{
  			showWaitIco = false;
  		}
		});
}

function delFiles(blockId)
{
		var comUrl = '?command=delfiles';			
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId + '&user_id=' + userId;	
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{   				
    		location.reload();		
  		},
		error: function () 
  		{
  				
  		}
		});		
}

function addToFavorite(blockId, isHidden)
{
		var comUrl = '?command=favorite';
		var metod  = 'add';
		if (isHidden) metod  = 'remove';	
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId +'&metod=' + metod + "&user_id=" + userId;		
		showWaitIco = true;
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
			showWaitIco = false;
  		},
  		error: function () 
  		{
  			showWaitIco = false;
  		}
		});		
}

function fixThread(blockId, isHidden)
{
		var comUrl = '?command=fix';
		var metod  = 'add';
		if (isHidden) metod  = 'remove';	
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId +'&metod=' + metod + "&user_id=" + userId;		
		showWaitIco = true;
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
			showWaitIco = false;
  		},
  		error: function () 
  		{
  			showWaitIco = false;
  		}
		});		
}

function fixToAll(blockId, isHidden)
{
		var comUrl = '?command=fixtoall';
		var metod  = 'add';
		if (isHidden) metod  = 'remove';	
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId +'&metod=' + metod + "&user_id=" + userId;		
		showWaitIco = true;
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
			showWaitIco = false;
  		},
  		error: function () 
  		{
  			showWaitIco = false;
  		}
		});		
}

function allowPremod(blockId)
{
		var comUrl = '?command=allowpremod';	
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId + "&user_id=" + userId;		
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
  		}
		});		
}

function complain(blockId)
{
		var comUrl = '?command=complain';	
		var metod  = 'add';		
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId + "&metod=" + metod + "&user_id=" + userId;		
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  		    		
    		hideClick(blockId);
  		}
		});		
}

function clearComplain(blockId)
{
		var comUrl = '?command=complain';	
		var metod  = 'remove';		
		var userId = $("input[name='user_id']").val();
		var postData = 'id=' + blockId + "&metod=" + metod + "&user_id=" + userId;		
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
  		}
		});		
}

function banUser(userId, roTime, closeAccess)
{
		var comUrl = '?command=ban';	
		var metod  = 'add';			
		var closeAccessStr = closeAccess;			
		var mid = $("input[name='user_id']").val();
		var postData = 'id=' + userId + "&metod=" + metod + "&rotime=" + (roTime*60*60*24) + "&closeaccess=" + closeAccessStr + "&user_id=" + mid;	
						
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();    		
  		}
		});		
}

function unbanUser(userId)
{
		var comUrl = '?command=ban';	
		var metod  = 'remove';				
		var mid = $("input[name='user_id']").val();
		var postData = 'id=' + userId + "&metod=" + metod + "&user_id=" + mid;			
		
		$.ajax({
		type: 'POST',
  		url: comUrl,
  		data: postData,
  		success: function(msg)
  		{  			
    		location.reload();
  		}
		});		
}

function insertBlockAfter(newBlock, prevBlock) 
{
	$(newBlock).insertAfter(prevBlock);
}

function gotoPage(pageURI)
{
		location.href = pageURI;
}

function checkFiles(element, isThreadFiles)
{
	var elementsNamePrefix = "pic"; 
	if(!isThreadFiles) elementsNamePrefix = "pic";
	var maxFileSize = 10;
	var extentionsArray = ["jpg", "jpeg", "gif", "png", "zip", "rar", "mp3", "wav", "mpeg","flac", "mpg","mp4","avi", "webm", "flv", "txt", "doc", "xls", "waw", "ogg", "wma", "wmv", "cpp", "h", "pdf", "djw"];
	var filesCnt  		= parseInt($("input[name='"+elementsNamePrefix+"_files_cnt']").val());	
	var currFileNum 	= parseInt(element.id.slice(-1));
	var statusElementId = "#"+elementsNamePrefix+"FileStatus" + currFileNum; 

   var val = $(element).val();
	var ext = val.substring(val.lastIndexOf('.') + 1).toLowerCase();
	if ($.inArray(ext, extentionsArray) == -1)
	{
		$(statusElementId).text("Тип данного файла не подходит");
		$(element).val("");
		return false;
	}

	var fileSize = ($(element)[0].files[0].size / 1024 / 1024); 
	if (fileSize > maxFileSize)
   {
		$(statusElementId).text("Файл должен быть меньше " + maxFileSize + "Мб");
		$(element).val("");
		return false;
   }
   
   $(statusElementId).text("Готово");
   if(filesCnt == currFileNum && filesCnt < 9)
   {
   	filesCnt++;
   	$("input[name='"+elementsNamePrefix+"_files_cnt']").val(filesCnt);
   	createFileInput(filesCnt, isThreadFiles);
	}
}

function createFileInput(currFilesCnt, isThreadFiles)
{
	var elementsNamePrefix = "pic"; 
	if(!isThreadFiles) elementsNamePrefix = "pic";
	
	var controlElementId 	= elementsNamePrefix+"FileDel" 	 + currFilesCnt; 
	var statusElementId 		= elementsNamePrefix+"FileStatus" + currFilesCnt; 
	var fileElementId   		= elementsNamePrefix+"FileUpload" + currFilesCnt; 	
	var fileElementName		= elementsNamePrefix+"file" 		 + currFilesCnt; 	
	var prevFileElementId   = ".new_"+elementsNamePrefix+"_form .file_separator:last"; 
	if(currFilesCnt == 0) prevFileElementId = "#"+elementsNamePrefix+"_files_cnt";
	
	var controlElemHtml = "<div class='file_control control_text'><span id='"+controlElementId+"' onclick='delFile(this, "+isThreadFiles+")'>[Очисить] </span></div>";	
	$(controlElemHtml).insertAfter(prevFileElementId);
	var inputElemHtml = 	"<div class='file_input'><input id='"+fileElementId+"' type='file' name='"+fileElementName+"' onchange='checkFiles(this, "+isThreadFiles+")' /></div>"
	$(inputElemHtml).insertAfter(".new_"+elementsNamePrefix+"_form .file_control:last");	
	var statusElemHtml = "<div class='file_status control_text'><span id="+statusElementId+"></span></div>";	
	$(statusElemHtml).insertAfter(".new_"+elementsNamePrefix+"_form .file_input:last");
	var separatorElemHtml = "<div class='file_separator'></div>";	
	$(separatorElemHtml).insertAfter(".new_"+elementsNamePrefix+"_form .file_status:last");

}

function delAllFiles(isThreadFiles)
{
	var elementsNamePrefix = "pic"; 
	if(!isThreadFiles) elementsNamePrefix = "pic";
	
	var postFormClass = ".new_"+elementsNamePrefix+"_form ";
		
	$(postFormClass + ".file_control").remove();
	$(postFormClass + ".file_input").remove();
	$(postFormClass + ".file_status").remove();	
	
	$("input[name='"+elementsNamePrefix+"_files_cnt']").val(0);
	
	createFileInput(0,isThreadFiles);
}

function delFile(elem, isThreadFiles)
{
	var elementsNamePrefix = "pic"; 
	if(!isThreadFiles) elementsNamePrefix = "pic";
	
	var currFileNum = parseInt(elem.id.slice(-1));
	$("input[name='"+elementsNamePrefix+"file"+currFileNum+"']").val("");
	$("#"+elementsNamePrefix+"FileStatus"+currFileNum).text("");
}

function fileClick(elem, filePath, filePrevPath, fileType, imgWidth, imgHeight, imgPrevWidth, imgPrevHeight)
{
	if(fileType == "image") 
	{
		if(imgWidth == 0 || imgHeight == 0 || imgPrevWidth == 0 || imgPrevHeight == 0 ) return;
		if(elem.width != imgPrevWidth && elem.height != imgPrevHeight)
		{
			elem.width  = imgPrevWidth;	
			elem.height = imgPrevHeight;	
			elem.src = filePrevPath;
		}
		else 
		{
			var clientWidth = document.documentElement.clientWidth * 0.92 - $(elem).offset().left;	
			if (clientWidth < imgPrevWidth) clientWidth = imgPrevWidth;
			
			if(imgWidth > clientWidth)
			{				
				var coeff =  (clientWidth) / imgWidth;
				imgWidth  = imgWidth  * coeff;
				imgHeight  = imgHeight  * coeff;
			}
			elem.width  = imgWidth;	
			elem.height = imgHeight;	
			elem.src = filePath;
		}
		
	}
	else 
	{
		gotoPage(filePath);
	}
}

////////////////////////////////////////////////////////////////

function setVisibility(block, isVisible)
{
	if(isVisible) block.show();
	else block.hide();
}

var substringMatcher = function(strs) {
  return function findMatches(q, cb) {
    var matches, substringRegex;

    // an array that will be populated with substring matches
    matches = [];

    // regex used to determine if a string contains the substring `q`
    substrRegex = new RegExp(q, 'i');

    // iterate through the pool of strings and for any string that
    // contains the substring `q`, add it to the `matches` array
    $.each(strs, function(i, str) {
      if (substrRegex.test(str)) {
        matches.push(str);
      }
    });	 
    cb(matches);
  };
};

function initVars() 
{
	 $('.spoiler-body').hide();
    $('.spoiler-head').click(function(){
        $(this).next().toggle();
    })
    
    initTables();
    $("#jsGrid").hide();
    $("#resultList").hide();
    $(".taskHashView").css("visibility","hidden");
    
    var fields = ["has_photo","photo_id","photo_100","photo_200", "photo_max",
    					"verified","online", "sex", "bdate", "city", "country", "home_town", "timezone",
    					"lists", "domain", "has_mobile", "contacts", "site", "education",
    					"universities", "schools", "status", "last_seen","followers_count", "common_count", "contacts", 
    					"nickname", "relatives", "relation", "personal", "connections", "exports", "wall_comments", "activities", 
    					"interests", "music", "movies", "tv", "books", "games", "about", "quotes", "can_post", 
    					"can_see_audio", "can_write_private_message", "can_send_friend_request", 
    					 "screen_name", "career", "military" ];
  
 
	$('.fieldsInput').tagsinput({		
  		trimValue: true, 
  		freeInput: false, 		
  		typeaheadjs:{
			  hint: true,
			  highlight: true,
			  minLength: 1,
			  name: 'fields',
			  source: substringMatcher(fields)
		}
	});		
	$('.fieldsInput').tagsinput('refresh');	
	
	$('.cityInput').tagsinput({		
  		trimValue: true, 
  		freeInput: false, 		
  		typeaheadjs:{
			  hint: true,
			  highlight: true,
			  minLength: 2,
			  name: 'cities',
			  source: remouteDataMatcher('city')			 
		}
	});		
	$('.cityInput').tagsinput('refresh');	
	
	$('.schoolInput').tagsinput({		
  		trimValue: true, 
  		freeInput: false, 		
  		typeaheadjs:{
			  hint: true,
			  highlight: true,
			  minLength: 2,
			  name: 'school',
			  source: remouteDataMatcher('school')			 
		}
	});		
	$('.schoolInput').tagsinput('refresh');	

	$('.uniInput').tagsinput({		
  		trimValue: true, 
  		freeInput: false, 		
  		typeaheadjs:{
			  hint: true,
			  highlight: true,
			  minLength: 2,			  
			  name: 'uni',
			  source: remouteDataMatcher('university')			
		}
	});		
	$('.uniInput').tagsinput('refresh');	
}

////////////////////////////////////////////////////////////////

String.prototype.insert = function(index, string) 
{
  if (index > 0)
    return this.substring(0, index) + string + this.substring(index, this.length);
  else
    return string + this;
};

function escapeRegExp(string) 
{
    return string.replace(/([.*+?^=!:${}()|\[\]\/\\])/g, "\\$1");
}

function replaceAll(string, find, replace) 
{
  return string.replace(new RegExp(escapeRegExp(find), 'g'), replace);
}

function parseMessage(messageElem)
{	
	var resultMessage = "";
   var textHTML = $(messageElem).html();   

	var ST_INIT 	 = 0;
	var ST_ITAL_BEG = 1;
	var ST_BOLD_BEG = 3;
	var ST_SPOILER_BEG = 5;
	var ST_QUOTE_BEG= 7;
	var ST_LINK_BEG = 9;
	var ST_CODE_BEG = 10;
	var ST_REPLAY_BEG = 11;

	var maxDeep = 5;

	var states = new Array();
	var startPos = new Array();
	states.push(ST_INIT);
	startPos.push(0);
	
	var state = ST_INIT;
	var stPos = 0;
	for(var pos = 0; pos < textHTML.length; ++pos)
   {
   	if(states.length > 0)
   	{
			state = states[states.length - 1];
			stPos = startPos[startPos.length - 1];
		}
		else 
		{
			var state = ST_INIT;
			var stPos = 0;
		}
        switch(textHTML.charAt(pos))
        {
        	case 'b':
        		if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_BOLD_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("b");
				}
			break;
			case 'i':
				if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_ITAL_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("i");
				}
			break;
			case 'l':
				if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_LINK_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("l");
				}
			break;
			case 'r':
				if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_REPLAY_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("r");
				}
			break;
			case 's':
				if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_SPOILER_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("s");
				}
			break;
			case 'q':
				if(textHTML.length - 1 > pos && textHTML.charAt(pos + 1) == '(')
				{
					if(states.length < maxDeep)
					{
						states.push(ST_QUOTE_BEG);
						startPos.push(resultMessage.length);
					}
					pos++;
				}
				else
				{
					resultMessage = resultMessage.concat("q");
				}
			break;
			
			case ')':
				if(state == ST_BOLD_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "<b>");
					resultMessage = resultMessage.concat("</b>");
					states.pop();
					startPos.pop();	
					continue;				
				}
				if(state == ST_ITAL_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "<i>");
					resultMessage = resultMessage.concat("</i>");
					states.pop();
					startPos.pop();	
					continue;					
				}		
				if(state == ST_SPOILER_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "<span class='spoiler'>");
					resultMessage = resultMessage.concat("</span>");					
					states.pop();
					startPos.pop();
					continue;	
				}
				if(state == ST_REPLAY_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "&gt;&gt;<span class='replyToLink'>");
					resultMessage = resultMessage.concat("</span>");					
					states.pop();
					startPos.pop();
					continue;	
				}
				if(state == ST_LINK_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "<a href='");
					resultMessage = resultMessage.concat("'>link</a>");					
					states.pop();
					startPos.pop();
					continue;	
				}
				if(state == ST_QUOTE_BEG)
				{
					resultMessage = resultMessage.insert(stPos, "&laquo;<span class='quote'>");
					resultMessage = resultMessage.concat("</span>&raquo;");					
					states.pop();
					startPos.pop();
					continue;	
				}
				resultMessage = resultMessage.concat(")");
			break;			
						
			default:
				resultMessage = resultMessage.concat(textHTML.charAt(pos));
			break;
        }
	}
	
	// YOUTUBE LINKS
	var startPos = 0;
	var endPos = 0;
	startPos = resultMessage.indexOf("https://www.youtube.com/watch?v=", startPos);
	if(startPos == -1) startPos = resultMessage.indexOf("http://www.youtube.com/watch?v=", startPos);
	endPos = resultMessage.indexOf("&nbsp", startPos);
	while (startPos != -1 && endPos != -1)
	{			
		resultMessage = resultMessage.insert(endPos, "' type='video/youtube'> </video></div>");
		resultMessage = resultMessage.insert(startPos, "<div class='youtube'><video width='360' height='240' controls> <source src='");
						
		startPos = resultMessage.indexOf("https://www.youtube.com/watch?v=", endPos + 70);
		if(startPos == -1) startPos = resultMessage.indexOf("http://www.youtube.com/watch?v=", endPos + 70);
		endPos = resultMessage.indexOf("&nbsp", startPos);
	}
	//
	
	resultMessage = replaceAll(resultMessage, "[div]", "<br>");
	resultMessage = replaceAll(resultMessage, "[/div]", "");

	//	REMOVE HTML CODE IN COMMENT
	startPos = 0;
	endPos = 0;
	startPos = resultMessage.indexOf("[", 0);
	endPos 	= resultMessage.indexOf("]", startPos);	
	while (startPos != -1 && endPos != -1 )
	{			
		resultMessage = resultMessage.substring(0, startPos).concat(resultMessage.substring(endPos+1, resultMessage.length));		
					
		startPos = resultMessage.indexOf("[", startPos-1);
		endPos = resultMessage.indexOf("]", startPos);		
	}
	//	

    $(messageElem).html(resultMessage);  
 }

function parseAllMessages()
{
	$(".user_text").each(function(indx){
  			parseMessage($(this));
	});
			
	$(".spoiler").each(function(indx){
		$(this).click(function(){
			$(this).toggleClass('selected');
		})			
	})					
}
	  
 //////////////////////////////////////////////////////////////////////////////////
 
 $.fn.center = function() 
 {
    this.css("position", "fixed");
    this.css("top", ($(window).height()/2 - this.height()/2) + "px");
    this.css("left", ($(window).width()/2 - this.width()/2) + "px");
    return this;
}


$(document).ready(
	function() 
	{		
		//nicEditors.allTextAreas();		
		//parseAllMessages();
		
		initVars();
	}
);