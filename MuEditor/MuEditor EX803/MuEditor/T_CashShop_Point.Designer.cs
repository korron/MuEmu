using System;
using System.ComponentModel;
using System.Data;
using System.Data.Common;
using System.Data.OleDb;
using System.Drawing;
using System.Resources;
using System.Windows.Forms;

namespace MuEditor
{
	public class T_CashShop_Point : frmBase
	{
		private IContainer components;

		private GroupBox groupBox1;

		private Label label1;

		private ComboBox txtAccount;

		private Label label2;

		private System.Windows.Forms.TextBox WCoinC;

		private MuEditor.TextBox WCoinC_Add;

		private Label label3;

		private Button btn_CashShop;

		private GroupBox groupBox2;

		private DataGridView CashLog;

		public T_CashShop_Point()
		{
			this.InitializeComponent();
		}

		private void btn_CashShop_Click(object sender, EventArgs e)
		{
			if (this.txtAccount.Text.Trim() == "" || this.WCoinC_Add.Text.Trim() == "0")
			{
				return;
			}
            string str = string.Format("UPDATE CashShopData SET WCoinP += {0} WHERE (AccountID = N'{1}')", this.WCoinC_Add.Text.Trim(), this.txtAccount.Text.Trim());
			try
			{
				if (!base.Me_ExecuteSQL(str))
				{
                    Utils.WarningMessage("Operation failed!");
				}
				else
				{
					str = string.Format("INSERT INTO CashLog (UserID, Amount) VALUES ('{0}', {1});", this.txtAccount.Text.Trim(), this.WCoinC_Add.Text.Trim());
					OleDbCommand oleDbCommand = new OleDbCommand(str.ToString(), frmBase.Mu_Conn);
					oleDbCommand.ExecuteNonQuery();
                    Utils.InfoMessage("Successful operation!");
					this.InputAccount(this.txtAccount.Text.Trim());
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "Error:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(T_CashShop_Point));
			this.groupBox1 = new GroupBox();
			this.btn_CashShop = new Button();
			this.WCoinC_Add = new MuEditor.TextBox();
			this.label3 = new Label();
			this.WCoinC = new System.Windows.Forms.TextBox();
			this.label2 = new Label();
			this.txtAccount = new ComboBox();
			this.label1 = new Label();
			this.groupBox2 = new GroupBox();
			this.CashLog = new DataGridView();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			((ISupportInitialize)this.CashLog).BeginInit();
			base.SuspendLayout();
			this.groupBox1.Controls.Add(this.btn_CashShop);
			this.groupBox1.Controls.Add(this.WCoinC_Add);
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.WCoinC);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.txtAccount);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new Point(8, 8);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(490, 82);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Points Management";
			this.btn_CashShop.Location = new Point(12, 52);
			this.btn_CashShop.Name = "btn_CashShop";
			this.btn_CashShop.Size = new System.Drawing.Size(466, 23);
			this.btn_CashShop.TabIndex = 6;
            this.btn_CashShop.Text = "OK";
			this.btn_CashShop.UseVisualStyleBackColor = true;
			this.btn_CashShop.Click += new EventHandler(this.btn_CashShop_Click);
			this.WCoinC_Add.IsOnlyNumber = false;
			this.WCoinC_Add.Location = new Point(378, 23);
			this.WCoinC_Add.Name = "WCoinC_Add";
			this.WCoinC_Add.Size = new System.Drawing.Size(100, 21);
			this.WCoinC_Add.TabIndex = 5;
			this.WCoinC_Add.Text = "0";
			this.WCoinC_Add.TextAlign = HorizontalAlignment.Center;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(349, 28);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(23, 12);
			this.label3.TabIndex = 4;
			this.label3.Text = "+/-";
			this.WCoinC.Location = new Point(241, 24);
			this.WCoinC.Name = "WCoinC";
			this.WCoinC.ReadOnly = true;
			this.WCoinC.Size = new System.Drawing.Size(100, 21);
			this.WCoinC.TabIndex = 3;
			this.WCoinC.Text = "0";
			this.WCoinC.TextAlign = HorizontalAlignment.Center;
			this.label2.AutoSize = true;
			this.label2.Location = new Point(191, 28);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(53, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "WCoinP：";
			this.txtAccount.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
			this.txtAccount.AutoCompleteSource = AutoCompleteSource.ListItems;
			this.txtAccount.FormattingEnabled = true;
			this.txtAccount.Location = new Point(62, 24);
			this.txtAccount.MaxLength = 10;
			this.txtAccount.Name = "txtAccount";
			this.txtAccount.Size = new System.Drawing.Size(121, 20);
			this.txtAccount.TabIndex = 1;
			this.txtAccount.SelectedIndexChanged += new EventHandler(this.txtAccount_SelectedIndexChanged);
			this.txtAccount.TextChanged += new EventHandler(this.txtAccount_TextChanged);
			this.txtAccount.KeyPress += new KeyPressEventHandler(this.txtAccount_KeyPress);
			this.label1.AutoSize = true;
			this.label1.Location = new Point(12, 28);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(53, 12);
			this.label1.TabIndex = 0;
            this.label1.Text = "Account：";
			this.groupBox2.Controls.Add(this.CashLog);
			this.groupBox2.Location = new Point(8, 96);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(490, 316);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Record";
			this.CashLog.AllowUserToAddRows = false;
			this.CashLog.AllowUserToDeleteRows = false;
			this.CashLog.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.CashLog.Location = new Point(12, 20);
			this.CashLog.Name = "CashLog";
			this.CashLog.ReadOnly = true;
			this.CashLog.RowTemplate.Height = 23;
			this.CashLog.Size = new System.Drawing.Size(466, 286);
			this.CashLog.TabIndex = 0;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(507, 419);
			base.Controls.Add(this.groupBox2);
			base.Controls.Add(this.groupBox1);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.Icon = (System.Drawing.Icon)componentResourceManager.GetObject("$this.Icon");
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "T_CashShop_Point";
			base.StartPosition = FormStartPosition.CenterScreen;
            this.Text = "WCoinP Editor";
			base.Load += new EventHandler(this.T_CashShop_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			((ISupportInitialize)this.CashLog).EndInit();
			base.ResumeLayout(false);
		}

		public void InputAccount(string account)
		{
			this.Cursor = Cursors.WaitCursor;
			this.showByAccount(account);
			this.Cursor = Cursors.Default;
		}

		private void showByAccount(string account)
		{
			if (account == "")
			{
				return;
			}
			if (frmBase.Me_Conn.State != ConnectionState.Open)
			{
				return;
			}
			string str = null;
			try
			{
                str = string.Format("SELECT [WCoinP] FROM [CashShopData] WHERE ([AccountID] = N'{0}')", account);
				OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
				if (!oleDbDataReader.Read())
				{
                    Utils.WarningMessage(string.Concat("Sorry, I did not find an account[", account, "]corresponding point information！"));
					this.WCoinC.Text = "0";
				}
				else
				{
					this.WCoinC.Text = Convert.ToString(oleDbDataReader.GetValue(0));
				}
				oleDbDataReader.Close();
				this.WCoinC_Add.Text = "0";
				this.showByCashLog(account);
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void showByCashLog(string UserID)
		{
			if (UserID == "")
			{
				return;
			}
			if (frmBase.Mu_Conn.State != ConnectionState.Open)
			{
				return;
			}
			string str = null;
			try
			{
				str = string.Format("SELECT [ID] AS [ID], [UserID] AS [Username], [Amount] AS [Amount], [SentDate] AS [Date] FROM [CashLog] WHERE ([UserID] = N'{0}') ORDER BY [ID] DESC", UserID);
				OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(new OleDbCommand(str, frmBase.Mu_Conn));
				DataTable dataTable = new DataTable();
				oleDbDataAdapter.Fill(dataTable);
				this.CashLog.DataSource = dataTable;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void T_CashShop_Load(object sender, EventArgs e)
		{
		}

		private void txtAccount_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == '\r')
			{
				this.InputAccount(this.txtAccount.Text.Trim());
			}
		}

		private void txtAccount_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.InputAccount(this.txtAccount.Text.Trim());
		}

		private void txtAccount_TextChanged(object sender, EventArgs e)
		{
			if (this.txtAccount.Items.Contains(this.txtAccount.Text) || this.txtAccount.Text == null)
			{
				return;
			}
			if (frmBase.Me_Conn.State != ConnectionState.Open)
			{
				return;
			}
			string str = null;
			try
			{
				str = string.Format("SELECT TOP 100 [memb___id] FROM [MEMB_INFO] WHERE [memb___id] LIKE '{0}%'", this.txtAccount.Text);
				OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
				object value = null;
				while (oleDbDataReader.Read())
				{
					value = oleDbDataReader.GetValue(0);
					if (this.txtAccount.Items.Contains(value))
					{
						continue;
					}
					this.txtAccount.Items.Add(value);
				}
				oleDbDataReader.Close();
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void txtAccountLoad()
		{
			if (frmBase.Me_Conn.State != ConnectionState.Open)
			{
				return;
			}
			string str = null;
			try
			{
				str = "SELECT TOP 100 [memb___id] FROM [MEMB_INFO]";
				OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
				this.txtAccount.Items.Clear();
				this.txtAccount.AutoCompleteCustomSource.Clear();
				this.txtAccount.Text = "";
				while (oleDbDataReader.Read())
				{
					this.txtAccount.Items.Add(oleDbDataReader.GetValue(0));
				}
				if (this.txtAccount.Items.Count > 0)
				{
					this.txtAccount.SelectedIndex = 0;
				}
				oleDbDataReader.Close();
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}
	}
}