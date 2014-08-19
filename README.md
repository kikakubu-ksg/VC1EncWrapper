S2MMSH
======

なんでも実況V　ストリーミング変換サーバ

##STORM (Stream to relayable MMSH)に変わる模様  
※reliableではない可能性が高い 

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/kikakubu-ksg/s2mmsh/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

##Update
2014/04/18 ASFの詳細タグを入れられるようにした。裏ではGUIDも自動挿入してます。  
2013/10/08 ffmpegのコマンドを直修できるようにした。  
2013/10/08 ffmpegのエラーをログに出力するようにした。  

##What is this  
ffmpegで認識可能なストリーミングデータについて、何実でライブ配信可能なmmsh形式に変換するツール  
入力元はFFMPEGランチャーやMMSストリームなど。  
注）現バージョンはKagamin2最新バージョンからのアクセスのみサポートしています。  
注）エンコード形式がH264の場合はWMPでは見れません。qasf.dllを使わない（不明。WMPだといろいろいじってもDirectShowのデコーダを使ってくれないぽい）独自コーデックなプレイヤーなら大丈夫。ここのコメントでMSの技術者が対応してねーよって明言してる→http://blogs.msdn.com/b/windows_multimedia_jp/archive/2009/09/18/win7.aspx  
注）ASFタグは元々のストリームに存在しなかった場合のみ有効です。勝手に他人の配信にタグ入れちゃうのはよろしくないと思うよ。  

##How to use  
[入力にFFMPEGランチャーを使う場合]  
FFMPEGランチャーの出力にはtcp://IP:ポート?listenを使用。  
S2MMSHの入力ストリームにtcp://IP:ポートを指定し、平均ビットレートにはFFMPEGランチャーで指定した値を使用（おまじない）  
コマンドをS2MMSHに直接貼り付ければFFMPEGランチャー起動する必要はないですぞ。  

[入力にMMSソースを使う場合]  
プロトコルはmmsh://に書き換える。 （http://とmms://は自動的に置き換えられる。）

[その他のソースを使う場合]  
RTSP、RTMP等、ffmpegが対応しているプロトコルについては変換可能。youtubeとかニコ生とかはURLさえ分かればだいたい変換可能？  
元ストリームのエンコード形式にかかわらずASFコンテナに突っ込むため、プレイヤーによって再生可否が大きく変動  
再生されやすさは、ffplay >>>>> VLC >>>>> GOM >>>WMPくらい  
再変換を行った場合はほぼ再生可能。  

[TIPS：ustreamをソースに使う場合]  
直修モードでこんな感じ。なんでこれでいけるのかは謎ですが（処理はrtmpdumpと同様っぽい）  
` -v error -i "rtmp://flash10.ustream.tv/ustreamVideo/11865965/ playpath=streams/live swfUrl=http://static-cdn1.ustream.tv/swf/live/viewer.rsl:96.swf swfVfy=1 live=1" -c copy -f asf_stream -  `

「rtmp://flash10.ustream.tv/ustreamVideo/11865965/」の部分だけamfファイルから拾ってくる。  

簡単な説明。詳細はググれ  
1. ustreamの配信urlのソースからcidを拾う  
2. http://cdngw.ustream.tv/Viewer/getStream/1/cid（←ここに入れる）.amfのファイルを取得  
3. amfファイルの中に「rtmp://flashXX.ustream.tv/ustreamVideo/（cid）」みたいなのがある  

※ケツにスラッシュいれないとダメぽいです。  
※ていうかユーストはこんなめんどいことしなくてもGOM用アドレスあったよなそういや  
  
[サンプルコマンド]  
S2MMSH単体で高品質エンコードする場合のサンプルとか。参考にしてください。  
`-v quiet -rtbufsize 10MB -r 60 -s 512x770 -f dshow -i video="SCFF DirectShow Filter":audio="ステレオ ミキサー (Realtek High Definit" -threads 4 -sws_flags lanczos -pix_fmt yuv420p -maxrate 512k -bufsize 256k -crf 23.0 -vcodec libx264 -preset medium -profile:v high -acodec libfdk_aac -ar 44100 -ab 64k -ac 2 -vol 256 -f asf_stream - `  

##Memo  
[簡易キャプチャー機構作成についてのメモ]  
コンセプト：既存のデスクトップキャプチャはデスクトップ領域の一部を切り出す方式。しかし一部の例外を除いてデスクトップに存在するものは全てウィンドウとして管理されているわけなので、ウィンドウのキャプチャをメモリ上で合成したものをビデオストリームのインプットとすることができるのではないか？  
利点：画面外（デスクトップ外）のウィンドウのキャプチャが可能。また最小化されてても背面にいても同様にキャプチャできるので、デスクトップの見た目と配信画像を完全に切り離すことができる。また、directshowfilterを経由しないキャプチャ方式という選択肢を持たせることができる。  
実装：PrintWindowで取得したウィンドウキャプチャイメージをBitbltでメモリデバイスコンテキスト上で合成加工したものをffmpegの標準入力に送り続けるだけ。サムネイルウィンドウをGUI上に作成して、各ウィンドウの配置とZを指定できる。  
問題：性能面を調査しないとよくわからない。現時点ではdirectshowfilterによるキャプチャよりも早くなるかもしれないし、遅くなるかもしれない。目標性能値はHDで60fpsくらいだろうか・・・ffmpegのrawimage処理性能によるかしらん。ちなみにバッファリングはffmpeg以降に任せる。  


##Issues  
PUSH対応  
鏡ツール化  
各鏡ツールとプレイヤーへの対応。（クライアントによって投げてくるhttpヘッダがまちまちなのよ）  
RTMPサーバ化  
$C（Change Notification）対応  ⇒鏡が対応してないので無理  
バックグラウンドストリーム（キャンバスストリーム）対応  
プレイリスト対応  
音声ストリーム追加（副音声追加）対応  
ピアキャスプロトコル対応  
統合エンコーダツールとして展開  
  
