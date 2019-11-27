//pm2018 macro
//downmenu.inc ver0.0.4
//input choice multiple Expansion
//---------------------------------------------------------------------------------------------------
//ver0.0.1:完成
//ver0.0.2:AbortFg=0 空を返すように修正
//ver0.0.3:標準関数使用に修正（Groupﾌｫﾙﾀﾞ未使用化）
//ver0.0.4:All以外の選択を反転処理化
//---------------------------------------------------------------------------------------------------

//input choice multiple Expansion
//pram  :Lst-Selection candidate list
//pram  :Msg-Dialog message
//pram  :AbortFg-Cancellation response ;0 - Return empty 1 - End
//return:OutLst-Selected string list
function Exec_DownMenu(string list Lst, string Msg, bool  AbortFg, output string list OutLst) {	
	$OutLst = {}

	//null check
	if size($Lst) < 1 {
		if $AbortFg==1 {
			macro abort
		} else {
			return
		}
	}

	//add All
	string allword = '** All **'
	string list tmpLst = $Lst
	int dmy = add_first($tmpLst, $allword)
	
	//user select
	int list idxs =  input choice multiple $tmpLst $Msg
	
	//null check
	if size(idxs) < 1 {
		if $AbortFg==1 {
			macro abort
		} else {
			return
		}
	}
	
	//to list
	foreach idx in $idxs {
		$dmy = add_last($OutLst, $tmpLst[$idx])
	}
	if $idxs[0] == 0 {
		$dmy = remove_first($OutLst)
		$OutLst = subtract($Lst, $OutLst)
	}
	return
}

//////////////////////////////
//ﾕﾆｯﾄﾃｽﾄ
function main() {
	string list paths =  extract(filter(folder('toolpath'), ''), 'Name') 
	string list re ={}
	call Exec_DownMenu($paths, 'hoge', 1, $re) 
}