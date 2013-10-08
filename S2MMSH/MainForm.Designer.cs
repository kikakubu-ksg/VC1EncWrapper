namespace S2MMSH
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_exec = new System.Windows.Forms.Button();
            this.button_ffmpegPathReffer = new System.Windows.Forms.Button();
            this.label_ffmpegPath = new System.Windows.Forms.Label();
            this.label_exPort = new System.Windows.Forms.Label();
            this.textBox_ffmpegPath = new System.Windows.Forms.TextBox();
            this.textBox_exPort = new System.Windows.Forms.TextBox();
            this.button_disconnect = new System.Windows.Forms.Button();
            this.textBox_inputstream = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_videorate = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_audiorate = new System.Windows.Forms.TextBox();
            this.textBox_log = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.radioButton_reencode_1 = new System.Windows.Forms.RadioButton();
            this.radioButton_reencode_2 = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupBox_reencode = new System.Windows.Forms.GroupBox();
            this.textBox_enc_framerate = new System.Windows.Forms.TextBox();
            this.label17 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.textBox_enc_bitrate_a = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox_enc_bitrate_v = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.textBox_enc_height = new System.Windows.Forms.TextBox();
            this.textBox_enc_width = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.groupBox_reencode.SuspendLayout();
            this.SuspendLayout();
            // 
            // button_exec
            // 
            this.button_exec.Location = new System.Drawing.Point(14, 261);
            this.button_exec.Name = "button_exec";
            this.button_exec.Size = new System.Drawing.Size(448, 23);
            this.button_exec.TabIndex = 15;
            this.button_exec.Text = "接続";
            this.button_exec.UseVisualStyleBackColor = true;
            this.button_exec.Click += new System.EventHandler(this.button_exec_Click);
            // 
            // button_ffmpegPathReffer
            // 
            this.button_ffmpegPathReffer.Location = new System.Drawing.Point(425, 2);
            this.button_ffmpegPathReffer.Name = "button_ffmpegPathReffer";
            this.button_ffmpegPathReffer.Size = new System.Drawing.Size(38, 23);
            this.button_ffmpegPathReffer.TabIndex = 2;
            this.button_ffmpegPathReffer.Text = "参照";
            this.button_ffmpegPathReffer.UseVisualStyleBackColor = true;
            this.button_ffmpegPathReffer.Click += new System.EventHandler(this.button_ffmpegPathReffer_Click);
            // 
            // label_ffmpegPath
            // 
            this.label_ffmpegPath.AutoSize = true;
            this.label_ffmpegPath.Location = new System.Drawing.Point(12, 9);
            this.label_ffmpegPath.Name = "label_ffmpegPath";
            this.label_ffmpegPath.Size = new System.Drawing.Size(59, 12);
            this.label_ffmpegPath.TabIndex = 2;
            this.label_ffmpegPath.Text = "ffmpegパス";
            // 
            // label_exPort
            // 
            this.label_exPort.AutoSize = true;
            this.label_exPort.Location = new System.Drawing.Point(12, 235);
            this.label_exPort.Name = "label_exPort";
            this.label_exPort.Size = new System.Drawing.Size(57, 12);
            this.label_exPort.TabIndex = 3;
            this.label_exPort.Text = "配信ポート";
            // 
            // textBox_ffmpegPath
            // 
            this.textBox_ffmpegPath.Location = new System.Drawing.Point(91, 6);
            this.textBox_ffmpegPath.Name = "textBox_ffmpegPath";
            this.textBox_ffmpegPath.Size = new System.Drawing.Size(328, 19);
            this.textBox_ffmpegPath.TabIndex = 1;
            // 
            // textBox_exPort
            // 
            this.textBox_exPort.Location = new System.Drawing.Point(77, 233);
            this.textBox_exPort.Name = "textBox_exPort";
            this.textBox_exPort.Size = new System.Drawing.Size(57, 19);
            this.textBox_exPort.TabIndex = 14;
            // 
            // button_disconnect
            // 
            this.button_disconnect.Location = new System.Drawing.Point(14, 290);
            this.button_disconnect.Name = "button_disconnect";
            this.button_disconnect.Size = new System.Drawing.Size(448, 23);
            this.button_disconnect.TabIndex = 16;
            this.button_disconnect.Text = "切断";
            this.button_disconnect.UseVisualStyleBackColor = true;
            this.button_disconnect.Click += new System.EventHandler(this.button_disconnect_Click);
            // 
            // textBox_inputstream
            // 
            this.textBox_inputstream.Location = new System.Drawing.Point(91, 31);
            this.textBox_inputstream.Name = "textBox_inputstream";
            this.textBox_inputstream.Size = new System.Drawing.Size(371, 19);
            this.textBox_inputstream.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "入力ストリーム";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 12);
            this.label2.TabIndex = 10;
            this.label2.Text = "平均ビットレート";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(141, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "映像";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(298, 64);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "音声";
            // 
            // textBox_videorate
            // 
            this.textBox_videorate.Location = new System.Drawing.Point(176, 61);
            this.textBox_videorate.Name = "textBox_videorate";
            this.textBox_videorate.Size = new System.Drawing.Size(60, 19);
            this.textBox_videorate.TabIndex = 4;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(243, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 14;
            this.label5.Text = "kbps";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(399, 64);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 15;
            this.label6.Text = "kbps";
            // 
            // textBox_audiorate
            // 
            this.textBox_audiorate.Location = new System.Drawing.Point(333, 61);
            this.textBox_audiorate.Name = "textBox_audiorate";
            this.textBox_audiorate.Size = new System.Drawing.Size(60, 19);
            this.textBox_audiorate.TabIndex = 5;
            // 
            // textBox_log
            // 
            this.textBox_log.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox_log.Location = new System.Drawing.Point(14, 341);
            this.textBox_log.Multiline = true;
            this.textBox_log.Name = "textBox_log";
            this.textBox_log.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_log.Size = new System.Drawing.Size(448, 81);
            this.textBox_log.TabIndex = 17;
            this.textBox_log.TextChanged += new System.EventHandler(this.textBox_log_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(14, 320);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(23, 12);
            this.label7.TabIndex = 18;
            this.label7.Text = "ログ";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(0, 7);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(62, 12);
            this.label8.TabIndex = 19;
            this.label8.Text = "再エンコード";
            // 
            // radioButton_reencode_1
            // 
            this.radioButton_reencode_1.AutoSize = true;
            this.radioButton_reencode_1.Location = new System.Drawing.Point(80, 5);
            this.radioButton_reencode_1.Name = "radioButton_reencode_1";
            this.radioButton_reencode_1.Size = new System.Drawing.Size(42, 16);
            this.radioButton_reencode_1.TabIndex = 6;
            this.radioButton_reencode_1.Text = "する";
            this.radioButton_reencode_1.UseVisualStyleBackColor = true;
            this.radioButton_reencode_1.CheckedChanged += new System.EventHandler(this.radioButton_reencode_1_CheckedChanged);
            // 
            // radioButton_reencode_2
            // 
            this.radioButton_reencode_2.AutoSize = true;
            this.radioButton_reencode_2.Checked = true;
            this.radioButton_reencode_2.Location = new System.Drawing.Point(128, 5);
            this.radioButton_reencode_2.Name = "radioButton_reencode_2";
            this.radioButton_reencode_2.Size = new System.Drawing.Size(52, 16);
            this.radioButton_reencode_2.TabIndex = 7;
            this.radioButton_reencode_2.TabStop = true;
            this.radioButton_reencode_2.Text = "しない";
            this.radioButton_reencode_2.UseVisualStyleBackColor = true;
            this.radioButton_reencode_2.CheckedChanged += new System.EventHandler(this.radioButton_reencode_2_CheckedChanged);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.radioButton_reencode_2);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.radioButton_reencode_1);
            this.panel1.Location = new System.Drawing.Point(12, 86);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 25);
            this.panel1.TabIndex = 22;
            // 
            // groupBox_reencode
            // 
            this.groupBox_reencode.Controls.Add(this.textBox_enc_framerate);
            this.groupBox_reencode.Controls.Add(this.label17);
            this.groupBox_reencode.Controls.Add(this.label16);
            this.groupBox_reencode.Controls.Add(this.textBox_enc_bitrate_a);
            this.groupBox_reencode.Controls.Add(this.label11);
            this.groupBox_reencode.Controls.Add(this.label12);
            this.groupBox_reencode.Controls.Add(this.textBox_enc_bitrate_v);
            this.groupBox_reencode.Controls.Add(this.label13);
            this.groupBox_reencode.Controls.Add(this.label14);
            this.groupBox_reencode.Controls.Add(this.label15);
            this.groupBox_reencode.Controls.Add(this.textBox_enc_height);
            this.groupBox_reencode.Controls.Add(this.textBox_enc_width);
            this.groupBox_reencode.Controls.Add(this.label10);
            this.groupBox_reencode.Controls.Add(this.label9);
            this.groupBox_reencode.Enabled = false;
            this.groupBox_reencode.Location = new System.Drawing.Point(12, 117);
            this.groupBox_reencode.Name = "groupBox_reencode";
            this.groupBox_reencode.Size = new System.Drawing.Size(449, 110);
            this.groupBox_reencode.TabIndex = 23;
            this.groupBox_reencode.TabStop = false;
            this.groupBox_reencode.Text = "エンコード設定";
            // 
            // textBox_enc_framerate
            // 
            this.textBox_enc_framerate.Location = new System.Drawing.Point(93, 78);
            this.textBox_enc_framerate.Name = "textBox_enc_framerate";
            this.textBox_enc_framerate.Size = new System.Drawing.Size(60, 19);
            this.textBox_enc_framerate.TabIndex = 13;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(159, 81);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(21, 12);
            this.label17.TabIndex = 25;
            this.label17.Text = "fps";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(16, 81);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(69, 12);
            this.label16.TabIndex = 24;
            this.label16.Text = "フレームレート";
            // 
            // textBox_enc_bitrate_a
            // 
            this.textBox_enc_bitrate_a.Location = new System.Drawing.Point(283, 46);
            this.textBox_enc_bitrate_a.Name = "textBox_enc_bitrate_a";
            this.textBox_enc_bitrate_a.Size = new System.Drawing.Size(60, 19);
            this.textBox_enc_bitrate_a.TabIndex = 12;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(349, 49);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(29, 12);
            this.label11.TabIndex = 22;
            this.label11.Text = "kbps";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(193, 49);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(29, 12);
            this.label12.TabIndex = 21;
            this.label12.Text = "kbps";
            // 
            // textBox_enc_bitrate_v
            // 
            this.textBox_enc_bitrate_v.Location = new System.Drawing.Point(126, 46);
            this.textBox_enc_bitrate_v.Name = "textBox_enc_bitrate_v";
            this.textBox_enc_bitrate_v.Size = new System.Drawing.Size(60, 19);
            this.textBox_enc_bitrate_v.TabIndex = 11;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(248, 49);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(29, 12);
            this.label13.TabIndex = 19;
            this.label13.Text = "音声";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(91, 49);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(29, 12);
            this.label14.TabIndex = 18;
            this.label14.Text = "映像";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(16, 49);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(55, 12);
            this.label15.TabIndex = 17;
            this.label15.Text = "ビットレート";
            // 
            // textBox_enc_height
            // 
            this.textBox_enc_height.Location = new System.Drawing.Point(158, 18);
            this.textBox_enc_height.Name = "textBox_enc_height";
            this.textBox_enc_height.Size = new System.Drawing.Size(42, 19);
            this.textBox_enc_height.TabIndex = 10;
            // 
            // textBox_enc_width
            // 
            this.textBox_enc_width.Location = new System.Drawing.Point(93, 18);
            this.textBox_enc_width.Name = "textBox_enc_width";
            this.textBox_enc_width.Size = new System.Drawing.Size(42, 19);
            this.textBox_enc_width.TabIndex = 9;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(141, 25);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(11, 12);
            this.label10.TabIndex = 1;
            this.label10.Text = "x";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(16, 21);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(58, 12);
            this.label9.TabIndex = 0;
            this.label9.Text = "画面サイズ";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(218, 93);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(136, 12);
            this.label18.TabIndex = 26;
            this.label18.Text = "※CODECはWMV2/WMA2";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(474, 434);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.groupBox_reencode);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox_log);
            this.Controls.Add(this.textBox_audiorate);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox_videorate);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_inputstream);
            this.Controls.Add(this.button_disconnect);
            this.Controls.Add(this.textBox_exPort);
            this.Controls.Add(this.textBox_ffmpegPath);
            this.Controls.Add(this.label_exPort);
            this.Controls.Add(this.label_ffmpegPath);
            this.Controls.Add(this.button_ffmpegPathReffer);
            this.Controls.Add(this.button_exec);
            this.Controls.Add(this.panel1);
            this.Name = "MainForm";
            this.Text = "Stream to MMSH";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.groupBox_reencode.ResumeLayout(false);
            this.groupBox_reencode.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_exec;
        private System.Windows.Forms.Button button_ffmpegPathReffer;
        private System.Windows.Forms.Label label_ffmpegPath;
        private System.Windows.Forms.Label label_exPort;
        private System.Windows.Forms.TextBox textBox_ffmpegPath;
        private System.Windows.Forms.TextBox textBox_exPort;
        private System.Windows.Forms.Button button_disconnect;
        private System.Windows.Forms.TextBox textBox_inputstream;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_videorate;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBox_audiorate;
        public System.Windows.Forms.TextBox textBox_log;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.RadioButton radioButton_reencode_1;
        private System.Windows.Forms.RadioButton radioButton_reencode_2;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.GroupBox groupBox_reencode;
        private System.Windows.Forms.TextBox textBox_enc_bitrate_a;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBox_enc_bitrate_v;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox textBox_enc_height;
        private System.Windows.Forms.TextBox textBox_enc_width;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox_enc_framerate;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label18;
    }
}

