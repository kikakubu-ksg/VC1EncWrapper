using System;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace S2MMSH
{

    // 応答クラス
    class HttpServer
    {
        private Socket mClient;
        private MainForm mForm;

        // コンストラクタ
        public HttpServer(Socket client, MainForm form)
        {
            mClient = client;
            mForm = form;
        }

        // 応答開始
        public void Start()
        {
            Thread thread = new Thread(Run);
            thread.Start();
        }

        // 応答実行
        public void Run()
        {
            try
            {
                // 要求受信
                byte[] buffer = new byte[4096];
                int recvLen = 0;
                try
                {
                    while (mClient.Available > 0)
                    {
                        recvLen += mClient.Receive(buffer);
                    }
                }
                catch (SocketException e)
                {
                    Console.WriteLine("{0} Error code: {1}.", e.Message, e.ErrorCode);
                    throw e;
                }
                String msg = "接続しました。";

                try
                {
                    msg = "接続しました。[" + mClient.RemoteEndPoint.ToString() + "]";
                }
                catch  {
                }

                mForm.BeginInvoke(new Action<String>(delegate(String str) { mForm.logoutput(msg); }), new object[] { "" });
                String message = Encoding.ASCII.GetString(buffer, 0, recvLen);
                Console.Write("httprequest:" + message);

                AsfData asfData = AsfData.Instance;

                //if (recvLen <= 0)  これ入れるとkagamiで成功しない。kagamiは何も送ってこない・・
                //    return;

                // HTTPヘッダー生成
                String httpHeader = null;
                byte[] httpHeaderBuffer = new byte[4096];

                if (asfData.asf_status == ASF_STATUS.ASF_STATUS_SET_HEADER && // asfヘッダ登録済み
                    asfData.mmsh_status != MMSH_STATUS.MMSH_STATUS_ASF_DATA_SENDING) // クライアントなし
                {
                    if (message.Contains("stream-switch"))
                    {
                        httpHeader = String.Format(
                            "HTTP/1.0 200 OK\r\n" +
                            "Server: Rex/12.0.7601.17514\r\n" +
                            "Cache-Control: no-cache\r\n" +
                            "Pragma: no-cache\r\n" +
                            "Pragma: client-id=2236067900\r\n" +
                            "Pragma: features=\"broadcast,playlist\"\n" +
                            "Content-Type: application/x-mms-framed\r\n" +
                            "Connection: Keep-Alive\r\n" +
                            "\r\n"
                        );

                        httpHeaderBuffer = Encoding.UTF8.GetBytes(httpHeader);
                        mClient.Send(httpHeaderBuffer);
                        if (message.Contains("Kagamin"))
                        {
                            mClient.Send(asfData.asf_header, asfData.asf_header_size, SocketFlags.None);
                            Console.WriteLine("ASF header sent.");
                        }
                        asfData.mms_sock = mClient; //早い者勝ち
                        asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_ASF_HEADER_SEND;
                    }
                    else if (message.Contains("NSPlayer"))
                    {
                        if (message.Contains("kagami"))
                        {
                            httpHeader = String.Format(
                                   "HTTP/1.0 200 OK\r\n" +
                                   "Server: Rex/12.0.7601.17514\r\n" +
                                   "Cache-Control: no-cache\r\n" +
                                   "Pragma: no-cache\r\n" +
                                   "Pragma: client-id=2236067900\r\n" +
                                   "Pragma: features=\"broadcast,playlist\"\r\n" +
                                   "Keep-Alive: timeout=1, max=0\r\n" +
                                   "Content-Type: application/vnd.ms.wms-hdr.asfv1\r\n" +
                                   "Connection: close\r\n" +
                                   "\r\n"
                               );
                        }
                        else {
                            httpHeader = String.Format(
                                       "HTTP/1.0 200 OK\r\n" +
                                   "Server: Rex/12.0.7601.17514\r\n" +
                                   "Cache-Control: no-cache\r\n" +
                                   "Pragma: no-cache\r\n" +
                                   "Pragma: client-id=2236067900\r\n" +
                                   "Pragma: features=\"broadcast,playlist\"\r\n" +
                                   "Keep-Alive: timeout=1, max=0\r\n" +
                                   "Content-Type: application/vnd.ms.wms-hdr.asfv1\r\n" +
                                   "Connection: close\r\n" +
                                   "\r\n"
                                  );
                        }
                        httpHeaderBuffer = Encoding.UTF8.GetBytes(httpHeader);
                        mClient.Send(httpHeaderBuffer);
                        mClient.Send(asfData.asf_header, asfData.asf_header_size, SocketFlags.None);
                        Console.WriteLine("ASF header sent.");
                        try
                        {
                            mForm.BeginInvoke(new Action<String>(delegate(String str) { mForm.logoutput("ASFヘッダを送信しました。[" + mClient.RemoteEndPoint.ToString() + "]"); }), new object[] { "" });

                        }
                        catch (Exception)
                        {
                        }    
                        //if (message.Contains("kagami"))
                        //if(true)
                        //{
                        asfData.mms_sock = mClient;
                        asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_ASF_HEADER_SEND;
                        //}
                        //else
                        //{
                        //    mForm.BeginInvoke(new Action<String>(delegate(String str) { mForm.logoutput("クライアントを切断します。[" + mClient.RemoteEndPoint.ToString() + "]"); }), new object[] { "" });
                        //    mClient.Close();
                        //}

                    } else {
                        mForm.BeginInvoke(new Action<String>(delegate(String str) { mForm.logoutput("クライアントを切断します。"); }), new object[] { "" });
                        mClient.Close();
                    }
                   
                }
                else {
                    mForm.BeginInvoke(new Action<String>(delegate(String str) { mForm.logoutput("MMSヘッダが未登録のため切断します。"); }), new object[] { "" });
                    httpHeader = String.Format(
                            "HTTP/1.0 503 Service Unavailable\r\n" +
                            "Server: Rex/12.0.7601.17514\r\n" +
                            "Cache-Control: no-cache\r\n" +
                            "\r\n"
                        );

                    mClient.Send(httpHeaderBuffer);
                    httpHeaderBuffer = Encoding.UTF8.GetBytes(httpHeader);

                    Console.WriteLine("503 sent.");
                    if (mClient != null)
                    {
                        mClient.Close();
                        asfData.mms_sock = null;
                    }
                    asfData.mmsh_status = MMSH_STATUS.MMSH_STATUS_NULL;
                }

            }
            catch (System.Net.Sockets.SocketException e)
            {
                Console.Write(e.Message);
            }
            catch (System.ObjectDisposedException e)
            {
                Console.Write(e.Message);
            }
            finally
            {
                // mClient.Close();
            }
        }
    }
}
