yolo-ninja
==========

cgi for w3m to use weblio ej

Compile
---
'''sh
gcc -std=c99 dict.c -lcurl -loauth -o dict.cgi
'''
You can change output name by -o option

Dependencies
---
You need libcurl and liboauth

Usage
---
Copy dict.cgi to your w3m's local cgi-bin directory.

Then, you set 辞書引きをcgi経由で行う option to "yes" and 辞書引きコマンドのURL to file:///cgi-bin/dict.cgi
