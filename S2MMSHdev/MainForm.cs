using System;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Diagnostics;
using System.IO;
using Microsoft.DirectX.DirectSound;

namespace S2MMSH
{
    public partial class MainForm : Form
    {
        //private static Boolean serverstatus = true;
        //private Process process = null;
        //private Thread th_server = null;
        //private Thread th_ffmpeg = null;
        public LogoutputDelegate logoutputDelegate;

        public MainForm()
        {
            InitializeComponent();
        }
        private DevicesCollection myDevices = null;
        private void MainForm_Load(object sender, EventArgs e)
        {
            this.textBox_ffmpegPath.Text = Properties.Settings.Default.ffmpegpath;
            this.textBox_inputstream.Text = Properties.Settings.Default.inputstream;
            this.textBox_audiorate.Text = Properties.Settings.Default.audiorate;
            this.textBox_videorate.Text = Properties.Settings.Default.videorate;
            this.textBox_exPort.Text = Properties.Settings.Default.port;

            if (Properties.Settings.Default.reencode_flag)
            { // 再エンコあり
                radioButton_reencode_1.Checked = true;
                groupBox_reencode.Enabled = true;
            }
            else {
                radioButton_reencode_2.Checked = true;
                groupBox_reencode.Enabled = false;
            }

            this.textBox_enc_width.Text = Properties.Settings.Default.enc_width;
            this.textBox_enc_height.Text = Properties.Settings.Default.enc_height;
            this.textBox_enc_bitrate_v.Text = Properties.Settings.Default.enc_bitrate_v;
            this.textBox_enc_bitrate_a.Text = Properties.Settings.Default.enc_bitrate_a;
            this.textBox_enc_framerate.Text = Properties.Settings.Default.enc_framerate; 

            logoutputDelegate = new LogoutputDelegate(logoutput);
            this.button_disconnect.Enabled = false;
            this.textBox_log.AppendText("アプリケーションが開始しました。\r\n");

            // デバイスリストを取得してリストボックスに
            myDevices = new DevicesCollection();
            foreach (DeviceInformation dev in myDevices)
            {
                this.textBox_log.AppendText(dev.ToString());
            }
        }

        private void button_ffmpegPathReffer_Click(object sender, EventArgs e)
        {
            //OpenFileDialogクラスのインスタンスを作成
            OpenFileDialog ofd = new OpenFileDialog();

            ofd.FileName = "";
            ofd.InitialDirectory = @"C:\";
            ofd.Filter =
                "EXEファイル(*.exe)|*.exe|すべてのファイル(*.*)|*.*";
            ofd.FilterIndex = 1;
            ofd.Title = "ファイルを選択";
            //ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
            ofd.RestoreDirectory = true;
            ofd.CheckFileExists = true;
            ofd.CheckPathExists = true;

            //ダイアログを表示する
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                //OKボタンがクリックされたとき
                textBox_ffmpegPath.Text = ofd.FileName;
            }
        }

        // connection
        private void button_exec_Click(object sender, EventArgs e)
        {
            //this.textBox_log.AppendText("入力ストリームに接続します。\r\n");
            logoutputDelegate("入力ストリームに接続します。"); 

            ProcessManager pm = ProcessManager.Instance;

            // init
            this.button_exec.Enabled = false;

            // httpserver listening
            pm.th_server = new Thread(
                new ThreadStart(HttpThread)
            );
            pm.th_server.Start(); 

            // ffmpeg tcp stream receive process
            if (pm.process == null)
            {
                if (pm.th_ffmpeg == null)
                {
                    pm.th_ffmpeg = new Thread(new ThreadStart(delegate()
                    {
                        try
                        {
                            pm.process = new Process();
                            pm.process.SynchronizingObject = this;
                            //イベントハンドラの追加
                            pm.process.Exited += new EventHandler(p_Exited);
                            //pm.process.ErrorDataReceived += new DataReceivedEventHandler(NetErrorDataHandler);
                            //プロセスが終了したときに Exited イベントを発生させる
                            pm.process.EnableRaisingEvents = true;

                            // ffmpeg commandline
                            //string command = 
                            //     this.textBox_ffmpegPath.Text + 
                            // " -v quiet -i tcp://127.0.0.1:6665 -c copy -f asf_stream -";
                            ProcessStartInfo startInfo = new ProcessStartInfo();
                            startInfo.FileName = this.textBox_ffmpegPath.Text;

                            string url = this.textBox_inputstream.Text;
                            url = System.Text.RegularExpressions.Regex.Replace(
                                url,
                                @"^mms://",
                                "mmsh://");
                            url = System.Text.RegularExpressions.Regex.Replace(
                               url,
                               @"^http://",
                               "mmsh://");
                            if (this.radioButton_reencode_1.Checked == false)
                            {
                                startInfo.Arguments = String.Format(" -v quiet -i {0} -c copy -f asf_stream -", url);
                            }
                            else {
                                int width = 0;
                                int height = 0;
                                int bitrate_v = 0;
                                int bitrate_a = 0;
                                float framerate = 0;
                                try
                                {
                                    width = int.Parse(this.textBox_enc_width.Text);
                                    height = int.Parse(this.textBox_enc_height.Text);
                                    bitrate_v = int.Parse(this.textBox_enc_bitrate_v.Text) * 1000;
                                    bitrate_a = int.Parse(this.textBox_enc_bitrate_a.Text) * 1000;
                                    framerate = float.Parse(this.textBox_enc_framerate.Text);
                                }
                                catch (Exception)
                                {
                                    logoutput("エンコード設定が不正です。再エンコードしません。");
                                    startInfo.Arguments = String.Format(" -v quiet -i {0} -c copy -f asf_stream -", url);
                                }
                                string strsize = String.Format("{0}x{1}", width, height);
                                if (width == 0 || height == 0) strsize = "320x240";
                                if (bitrate_v == 0) bitrate_v = 256000;
                                if (bitrate_a == 0) bitrate_a = 128000;
                                if (framerate == 0) framerate = 15;

                                startInfo.Arguments = String.Format(
                                    " -v quiet -i {0} -acodec wmav2 -ab {1} -vcodec wmv2 -vb {2} -s {3} -r {4} -f asf_stream -", 
                                    url,
                                    bitrate_a,
                                    bitrate_v,
                                    strsize,
                                    framerate);
                            }
                            //startInfo.Arguments = " -v quiet -i tcp://127.0.0.1:6665 -c copy -f asf_stream -";
                            //startInfo.Arguments = " -v quiet -i rtsp://184.72.239.149/vod/mp4:BigBuckBunny_115k.mov -c copy -f asf_stream -";
                            //startInfo.Arguments = " -v quiet -i mmsh://win.global.playstream.com/showcase/mathtv/trig_4.5_350k.wmv -c copy -f asf_stream -";
                            //startInfo.Arguments = " -v quiet -i mmsh://218.228.167.141:8888 -c copy -f asf_stream -";
                            startInfo.CreateNoWindow = true; startInfo.CreateNoWindow = true;
                            startInfo.RedirectStandardOutput = true;
                            //startInfo.RedirectStandardError = true;
                            startInfo.UseShellExecute = false;

                            Console.WriteLine(startInfo.Arguments);

                            pm.process.StartInfo = startInfo;
                            pm.process.Start();

                            int c = 0;
                            const int nBytes = 65535;
                            byte[] buf = new byte[nBytes];
                            BinaryReader br = new BinaryReader(pm.process.StandardOutput.BaseStream);

                            // StandardOutputからの入力待ちがあるため、別スレッド上で動かす必要がある
                            Boolean flg = true;
                            AsfData asfData = AsfData.Instance;
                            while (flg)
                            {
                                if (br.Read(buf, 0, 4) == 4)
                                {
                                    if (buf[0] == '$')
                                    {
                                        c = buf[2] + (buf[3] << 8);
                                        if (br.Read(buf, 4, c) != c)
                                        {
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        break;
                                    }

                                    if (buf[1] == 'H')// header packet
                                    {
                                        //bitrate property
                                        int bitrate;
                                        int audiorate;
                                        try
                                        {
                                            bitrate = int.Parse(this.textBox_videorate.Text) * 1000;
                                            audiorate = int.Parse(this.textBox_audiorate.Text) * 1000;
                                        }
                                        catch (Exception ex)
                                        {
                                            //this.textBox_log.AppendText(ex.Message);
                                            //break;
                                            bitrate = 256000;
                                            audiorate = 128000;
                                        }
                                        if (bitrate == 0) bitrate = 256000;
                                        if (audiorate == 0) audiorate = 128000;

                                        byte[] bitrate_property =
                                            new byte[]{
        0xCE, 0x75, 0xF8, 0x7B, 0x8D, 0x46, 0xD1, 0x11,
        0x8D, 0x82, 0x00, 0x60, 0x97, 0xC9, 0xA2, 0xB2,
        0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, //Bitrate Records Count
        // video bitrate
        0x01, 0x00, 
        (byte)bitrate, 
        (byte)((bitrate >> 8) & 0xFF), 
        (byte)((bitrate >> 16) & 0xFF), 
        (byte)((bitrate >> 24) & 0xFF), 
        // audio bitrate 12800bit/sec
        0x02, 0x00, 
        (byte)audiorate, 
        (byte)((audiorate >> 8) & 0xFF), 
        (byte)((audiorate >> 16) & 0xFF), 
        (byte)((audiorate >> 24) & 0xFF)
                                    };

                                        // existence check
                                        int j, k;
                                        int y;
                                        Boolean pflg = true;
                                        for (j = 0; j < c; j++)
                                        {
                                            y = 0;
                                            for (k = 0; k < 16; k++)
                                            {
                                                if (bitrate_property[k] == buf[j + k])
                                                {
                                                    y++;
                                                }
                                                else { break; }
                                            }
                                            if (y == 16)
                                            {
                                                pflg = false;
                                                break;
                                            }
                                        }

                                        if (pflg)
                                        {
                                            byte[] data50 = new byte[50];
                                            int i;
                                            for (i = 0; i < 50; i++)
                                            {
                                                data50[i] = buf[c + 4 - 50 + i];
                                            }
                                            for (i = 0; i < 38; i++)
                                            {
                                                buf[c + 4 - 50 + i] = bitrate_property[i];
                                            }
                                            for (i = 0; i < 50; i++)
                                            {
                                                buf[c + 4 - 50 + 38 + i] = data50[i];
                                            }

                                            buf[2] = (byte)(c + 38);
                                            buf[3] = (byte)((c + 38) >> 8);
                                            buf[10] = buf[2];
                                            buf[11] = buf[3];
                                            buf[36] = (byte)(buf[36] + 1);
                                        }

                                        buf.CopyTo(asfData.asf_header, 0);
                                        Console.WriteLine("ASF header registered.");
                                        this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("ASFヘッダを登録しました。"); }), new object[] { "" });
                                        if (pm.serverstatus) this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("クライアント接続を受け付けます。"); }), new object[] { "" });
                                        asfData.asf_header_size = c + 4 + 38;
                                        //asfData.asf_header_size = c + 4;
                                        asfData.asf_status = ASF_STATUS.ASF_STATUS_SET_HEADER;

                                    }
                                    else
                                        if (buf[1] == 'D' && (
                                        asfData.mmsh_status == MMSH_STATUS.MMSH_STATUS_ASF_HEADER_SEND
                                        || asfData.mmsh_status == MMSH_STATUS.MMSH_STATUS_ASF_DATA_SENDING
                                        ))
                                        {
                                            try
                                            {
                                                if (asfData.mms_sock != null)
                                                {
                                                    int a = asfData.mms_sock.Available;
                                                    asfData.mms_sock.Send(buf, c + 4, SocketFlags.None);
                                                    //Console.WriteLine("ASF Data sent.");
                                                    asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_ASF_DATA_SENDING;
                                                    a = asfData.mms_sock.Available;
                                                }
                                            }
                                            catch (SocketException ex)
                                            {

                                                Console.WriteLine("{0} Error code: {1}.", ex.Message, ex.ErrorCode);
                                                this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput(ex.Message); }), new object[] { "" }); 
                                                asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_NULL;
                                            }
                                        }
                                        else
                                        {
                                            //Console.WriteLine("unknown header.");
                                        }
                                }
                                else {
                                    //EOF
                                    this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("入力がありません。配信を終了します。"); }), new object[] { "" });
                                        
                                    break; 
                                }
                            }
                            if (asfData.mms_sock != null)
                            {
                                asfData.mms_sock.Close();
                                asfData.mms_sock = null;

                            }
                        }
                        catch (Exception exx){
                            MessageBox.Show(exx.Message,
        "エラー",
        MessageBoxButtons.OK,
        MessageBoxIcon.Error);
                            
                        }
                        // todo 初期化

                    }));
                    pm.th_ffmpeg.Start();
                }
            }
            
            // closing
            this.button_disconnect.Enabled = true;
        }

        private void p_Exited(object sender, EventArgs e)
        {
            //プロセスが終了したときに実行される
            logoutput("ffmpegが終了しました。");
        }

        private static void NetErrorDataHandler(object sendingProcess,
           DataReceivedEventArgs errLine)
        {
            Console.WriteLine("エラーが書き込まれました。");
        }

        private void HttpThread() {
            // サーバーソケット初期化
            ProcessManager pm = ProcessManager.Instance;
            AsfData asfData = AsfData.Instance;
            this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("サーバを初期化します。"); }), new object[] { "" });
            //logoutputDelegate("サーバを初期化します。"); 
            pm.server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ip = IPAddress.Parse("127.0.0.1");
            IPEndPoint ipEndPoint = new IPEndPoint(ip, int.Parse(this.textBox_exPort.Text));

            pm.server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
            pm.server.Bind(ipEndPoint);
            pm.server.Listen(5);
            // 要求待ち（無限ループ）
            while (pm.serverstatus)
            {
                Socket sock = null;
                if (asfData.asf_status == ASF_STATUS.ASF_STATUS_SET_HEADER) this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("クライアント接続を受け付けます。"); }), new object[] { "" });
                try
                {
                    sock = pm.server.Accept();
                }
                catch 
                {
                    //this.BeginInvoke(new Action<String>(delegate(String str) { this.textBox_log.AppendText("ソケット接続エラー。\r\n"); }), new object[] { "" });
                    //throw ex;
                    break;
                }
                HttpServer response = new HttpServer(sock, this);
                response.Start();
            }

            // server dispose
            if (pm.server != null)
            {
                pm.server.Close();
            }
            this.BeginInvoke(new Action<String>(delegate(String str) { this.logoutput("サーバを終了します。"); }), new object[] { "" });

        }



        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // スレッド・プロセス終了
            ProcessManager pm = ProcessManager.Instance;
            if (pm.process != null)
            {
                if (!pm.process.HasExited)
                {
                    pm.process.CancelOutputRead();
                    pm.process.Kill();
                    pm.process.WaitForExit();
                }

                pm.process = null;
            }
            if (pm.th_server != null && pm.th_server.IsAlive)
            {
                
                pm.th_server.Abort();
                pm.th_server = null;
            }

            if (pm.th_ffmpeg != null && pm.th_ffmpeg.IsAlive)
            {
                pm.th_ffmpeg.Abort();
                pm.th_ffmpeg = null;
            }

            Properties.Settings.Default.ffmpegpath = this.textBox_ffmpegPath.Text;
            Properties.Settings.Default.inputstream = this.textBox_inputstream.Text;
            Properties.Settings.Default.audiorate = this.textBox_audiorate.Text;
            Properties.Settings.Default.videorate = this.textBox_videorate.Text;
            Properties.Settings.Default.port = this.textBox_exPort.Text;
            Properties.Settings.Default.reencode_flag = radioButton_reencode_1.Checked;
            Properties.Settings.Default.enc_width = this.textBox_enc_width.Text;
            Properties.Settings.Default.enc_height = this.textBox_enc_height.Text;
            Properties.Settings.Default.enc_bitrate_v = this.textBox_enc_bitrate_v.Text;
            Properties.Settings.Default.enc_bitrate_a = this.textBox_enc_bitrate_a.Text;
            Properties.Settings.Default.enc_framerate = this.textBox_enc_framerate.Text;

            Properties.Settings.Default.Save();
            
            base.OnClosing(e);
            Environment.Exit(0);
        }

        private void button_disconnect_Click(object sender, EventArgs e)
        {
            logoutput("接続を初期化します。"); 
            this.button_disconnect.Enabled = false;
            ProcessManager pm = ProcessManager.Instance;
            

            // スレッド・プロセス終了
            if (pm.process != null)
            {
                if (!pm.process.HasExited)
                {
                    try
                    {
                        pm.process.CancelOutputRead();
                    }
                    catch { }
                    pm.process.Kill();
                    pm.process.WaitForExit();
                }

                pm.process = null;
            }
            if (pm.th_server != null)
            {
                pm.server.Close();
                if(pm.th_server.IsAlive)
                pm.th_server.Abort();
                pm.th_server = null;
            }

            if (pm.th_ffmpeg != null)
            {
                if(pm.th_ffmpeg.IsAlive)
                pm.th_ffmpeg.Abort();
                pm.th_ffmpeg = null;
            }

            // 初期化
            AsfData asfData = AsfData.Instance;
            asfData.asf_status = ASF_STATUS.ASF_STATUS_NULL;
            asfData.asf_header_size = 0;
            asfData.asf_header = new byte[65535];
            asfData.mms_sock = null;
            asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_NULL;

            this.button_exec.Enabled = true;

            logoutput("接続を初期化しました。"); 
        }

        private void textBox_log_TextChanged(object sender, EventArgs e)
        {

        }

        public delegate void LogoutputDelegate(String str);
        public void logoutput(String str) {
            this.textBox_log.AppendText(DateTime.Now.ToString() + " " + str + "\r\n");
        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void radioButton_reencode_1_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = sender as RadioButton;

            if (radioButton.Checked)
            {
                Console.WriteLine(radioButton.Text + "が選択されました。");
                groupBox_reencode.Enabled = true;
            }
        }

        private void radioButton_reencode_2_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = sender as RadioButton;

            if (radioButton.Checked)
            {
                Console.WriteLine(radioButton.Text + "が選択されました。");
                groupBox_reencode.Enabled = false;
            }
        }

    }
}


//todo
//D&D対応
//ASFコメント追加
//EOF時の自動切断
//ffmpegコンソール直修
//バージョン管理
//プレイリストクラスの生成