S2MMSH
======

なんでも実況V　ストリーミング変換サーバ


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/kikakubu-ksg/s2mmsh/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

What is this  
ffmpegで認識可能なストリーミングデータについて、何実でライブ配信可能なmmsh形式に変換するツール  
入力元はFFMPEGランチャーやMMSストリームなど。  


How to use  
[入力にFFMPEGランチャーを使う場合]  
FFMPEGランチャーの出力にはtcp://IP:ポート?listenを使用。  
S2MMSHの入力ストリームにtcp://IP:ポートを指定し、平均ビットレートにはFFMPEGランチャーで指定した値を使用（おまじない）  

[入力にMMSソースを使う場合]  
プロトコルはmmsh://に書き換える。  

Issues  
たくさん。
