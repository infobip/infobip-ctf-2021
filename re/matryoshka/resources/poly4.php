$in="CCCCCCCCCC";$flag=base64_decode("DwZWQQVKCVcSRhhNElgPUh0MRh4BHENTXhpfClJGTg==");if (strlen($in)>=31){$res="";for($i=0;$i<strlen($flag);$i++){$res.=chr(ord($in[$i])^ord($flag[$i]));}echo $res;}
