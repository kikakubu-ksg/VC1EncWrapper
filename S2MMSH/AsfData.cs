using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.Net;

namespace S2MMSH
{
    public enum ASF_STATUS
    {
        ASF_STATUS_NULL,               // 初期状態
        ASF_STATUS_SET_HEADER          // ASFヘッダ作成済み
    };

    public enum MMSH_STATUS
    {
        MMSH_STATUS_NULL,               // 初期状態
        MMSH_STATUS_CONNECTED,          // 
        MMSH_STATUS_HTTP_HEADER_SEND,
        MMSH_STATUS_ASF_HEADER_SEND,
        MMSH_STATUS_ASF_DATA_SENDING
    };

    public enum FFMPEG_STATUS
    {
        FFMPEG_STATUS_NULL,               // 初期状態
        FFMPEG_STATUS_INITIALIZED,        // 初期化済
        FFMPEG_STATUS_INITIALIZING,        // 初期化中
        FFMPEG_STATUS_PROCESS              // 処理中
    };

    public sealed class AsfData
    {
        private static AsfData m_Instance = new AsfData();
        public ASF_STATUS asf_status = ASF_STATUS.ASF_STATUS_NULL;
        public int asf_header_size = 0;
        public byte[] asf_header = new byte[65535];
        public Socket mms_sock = null;
        public MMSH_STATUS mmsh_status = MMSH_STATUS.MMSH_STATUS_NULL;

        private AsfData()
        {
            Console.WriteLine("Created instance.");
        }

        public static AsfData Instance
        {
            get
            {
                return m_Instance;
            }
        }

        public void DoSomething()
        {
            Console.WriteLine("DoSomething is called");
        }

    }

    public sealed class ProcessManager
    {
        private static ProcessManager m_Instance = new ProcessManager();
        public Process process =  null;
        public Thread th_server = null;
        public Thread th_ffmpeg = null;
        public Boolean serverstatus = true;
        public Socket server = null;
        public FFMPEG_STATUS ffmpegstatus = FFMPEG_STATUS.FFMPEG_STATUS_NULL;

        private ProcessManager()
        {
            Console.WriteLine("Created instance.");
        }

        public static ProcessManager Instance
        {
            get
            {
                return m_Instance;
            }
        }

        public void DoSomething()
        {
            Console.WriteLine("DoSomething is called");
        }
    }
}
