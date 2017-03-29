using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Data.Common;
using System.Data.OleDb;
using System.Drawing;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmUser : frmBase
	{
		private IContainer components;

		private MuEditor.TextBox txtAccount;

		private ComboBox cbChoise;

		private GroupBox groupBox1;

		private CheckBox cbEnvelop;

		private Button btnSearch;

		private CheckBox cbOnline;

		private DataGridView gvData;

		private GroupBox groupBox2;

		private Button btnXX;

		private Button btnJF;

		private Button btnFH;

		private Button btnCancel;

		private ComboBox cbField;

		private CheckBox cbGM;

		private CheckBox cbRed;

		private ComboBox cbFilter;

		private System.Windows.Forms.ContextMenuStrip ccmsMenu;

		private ToolStripMenuItem 批量封号AToolStripMenuItem;

		private ToolStripMenuItem 批量解封DToolStripMenuItem;

		private ToolStripMenuItem 批量下线OToolStripMenuItem;

		private static frmUser form;

		private frmMain frmM;

		private int cell;

		static frmUser()
		{
		}

		private frmUser(frmMain frm, string IP)
		{
			this.InitializeComponent();
			this.frmM = frm;
			this.cbChoise.SelectedIndex = (IP == "" ? 0 : 2);
			this.txtAccount.Text = IP;
			this.cbField.Items.Clear();
			this.cbField.Items.Add(new ComboBoxItem("", ""));
			if ((int)Utils.AccFieldNames.Length != (int)Utils.AccFieldValues.Length)
			{
                Utils.WarningMessage("Configuration file error! Node AccFieldNames and AccFieldValues number of inconsistencies!");
				return;
			}
			for (int i = 0; i < (int)Utils.AccFieldNames.Length; i++)
			{
				this.cbField.Items.Add(new ComboBoxItem(Utils.AccFieldNames[i], Utils.AccFieldValues[i]));
			}
		}

		private void bind()
		{
			string str = "SELECT DISTINCT {0} AS {0}, {1}[stat].[ConnectStat] AS [Status], {2} AS [{2}], [stat].[IP], [AC].[GameID1] AS [ID1], [AC].[GameID2] AS [ID2], [AC].[GameID3] AS [ID3], [AC].[GameID4] AS ID4], [AC].[GameID5] AS [ID5] FROM {3} {4} ORDER BY {0}";
			string str1 = "";
			try
			{
				string str2 = "[info].[memb___id]";
				string str3 = "[AC].[GameIDC] AS [GAMEIDC], ";
				string str4 = "[info].[bloc_code]";
                string[] mUSERVER = new string[] { " [MEMB_INFO] AS [info] LEFT JOIN [MEMB_STAT] AS [stat] ON [info].[memb___id] = [stat].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS LEFT JOIN [", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[AccountCharacter] AS [AC] ON [AC].[Id] = [stat].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS" };
				string str5 = string.Concat(mUSERVER);
				string str6 = "WHERE (1 = 1)";
				if (this.cbOnline.Checked)
				{
					str6 = string.Concat(str6, " AND ([stat].[ConnectStat] = 1)");
				}
				if (this.cbChoise.SelectedIndex == 0)
				{
					if (this.cbEnvelop.Checked)
					{
						str6 = string.Concat(str6, " AND ([info].[bloc_code] = 1)");
					}
					if (this.cbField.SelectedIndex > 0)
					{
						str6 = (this.cbFilter.SelectedIndex != this.cbFilter.Items.Count - 1 ? string.Concat(str6, string.Format(" AND {0} {1} '{2}'", ((ComboBoxItem)this.cbField.SelectedItem).Value, ((ComboBoxItem)this.cbFilter.SelectedItem).Value, this.txtAccount.Text.Trim().Replace("'", "''"))) : string.Concat(str6, string.Format(" AND {0} {1} '%{2}%'", ((ComboBoxItem)this.cbField.SelectedItem).Value, ((ComboBoxItem)this.cbFilter.SelectedItem).Value, this.txtAccount.Text.Trim().Replace("'", "''"))));
					}
					else if (this.txtAccount.Text.Trim() != "")
					{
						str6 = string.Concat(str6, string.Format(" AND [AC].[Id] LIKE '%{0}%'", this.txtAccount.Text.Trim().Replace("'", "''")));
					}
				}
				else if (this.cbChoise.SelectedIndex != 1)
				{
					if (this.cbEnvelop.Checked)
					{
						str6 = string.Concat(str6, " AND ([info].[bloc_code] = 1)");
					}
					if (this.txtAccount.Text.Trim() != "")
					{
						str6 = string.Concat(str6, string.Format(" AND [info].[IP] LIKE '%{0}%'", this.txtAccount.Text.Trim().Replace("'", "''")));
					}
				}
				else
				{
					str2 = "[CC].[AccountID]";
					str3 = "[CC].[Name] AS [Name], [CC].[cLevel] AS [Level], ";
					str4 = "[CC].[CtlCode]";
					string[] strArrays = new string[] { "[", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[Character] AS [CC] LEFT JOIN [", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[AccountCharacter] AS [AC] ON [AccountID] = [AC].[Id] COLLATE Chinese_PRC_CS_AS_KS_WS LEFT JOIN [MEMB_INFO] AS [info] ON [Id] = [info].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS LEFT JOIN [MEMB_STAT] AS [stat] ON [info].[memb___id] = [stat].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS" };
					str5 = string.Concat(strArrays);
					if (this.cbEnvelop.Checked)
					{
						str6 = string.Concat(str6, " AND ([CC].[CtlCode] = 1)");
					}
					if (this.cbRed.Checked)
					{
						str6 = string.Concat(str6, " AND ([CC].[PkLevel] > 3)");
					}
					if (this.cbGM.Checked)
					{
						str6 = string.Concat(str6, " AND ([CC].[CtlCode] > 1)");
					}
					if (this.cbField.SelectedIndex > 0)
					{
						str6 = (this.cbFilter.SelectedIndex != this.cbFilter.Items.Count - 1 ? string.Concat(str6, string.Format(" AND {0} {1} '{2}'", ((ComboBoxItem)this.cbField.SelectedItem).Value, ((ComboBoxItem)this.cbFilter.SelectedItem).Value, this.txtAccount.Text.Trim().Replace("'", "''"))) : string.Concat(str6, string.Format(" AND {0} {1} '%{2}%'", ((ComboBoxItem)this.cbField.SelectedItem).Value, ((ComboBoxItem)this.cbFilter.SelectedItem).Value, this.txtAccount.Text.Trim().Replace("'", "''"))));
					}
					else if (this.txtAccount.Text.Trim() != "")
					{
						str6 = string.Concat(str6, string.Format(" AND [info].[Name] LIKE '%{0}%'", this.txtAccount.Text.Trim().Replace("'", "''")));
					}
				}
				object[] objArray = new object[] { str2, str3, str4, str5, str6 };
				str1 = string.Format(str, objArray);
				OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(new OleDbCommand(str1, frmBase.Me_Conn));
				DataTable dataTable = new DataTable();
				oleDbDataAdapter.Fill(dataTable);
                this.gvData.DataSource = dataTable;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str1, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			base.Close();
		}

		private void btnFH_Click(object sender, EventArgs e)
		{
			if (this.getIDS(0) == "")
			{
				return;
			}
			this.Cursor = Cursors.WaitCursor;
			this.operate(false, 1);
			this.bind();
			this.Cursor = Cursors.Default;
		}

		private void btnJF_Click(object sender, EventArgs e)
		{
			if (this.getIDS(0) == "")
			{
				return;
			}
			this.Cursor = Cursors.WaitCursor;
			this.operate(false, 0);
			this.bind();
			this.Cursor = Cursors.Default;
		}

		private void btnSearch_Click(object sender, EventArgs e)
		{
			this.Cursor = Cursors.WaitCursor;
			this.bind();
			this.Cursor = Cursors.Default;
		}

		private void btnXX_Click(object sender, EventArgs e)
		{
			if (this.getIDS(0) == "")
			{
				return;
			}
			this.Cursor = Cursors.WaitCursor;
			this.operate(true, 0);
			this.bind();
			this.Cursor = Cursors.Default;
		}

		private void cbChoise_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.gvData.DataSource = null;
			this.cbFilter.Items.Clear();
			this.cbField.Items.Clear();
			this.cbField.Items.Add(new ComboBoxItem("", ""));
			if (this.cbChoise.SelectedIndex == 0)
			{
				if ((int)Utils.AccFieldNames.Length != (int)Utils.AccFieldValues.Length)
				{
                    Utils.WarningMessage("Configuration file error! Node AccFieldNames and AccFieldValues number of inconsistencies!");
					return;
				}
				for (int i = 0; i < (int)Utils.AccFieldNames.Length; i++)
				{
					this.cbField.Items.Add(new ComboBoxItem(Utils.AccFieldNames[i], Utils.AccFieldValues[i]));
				}
				return;
			}
			if (this.cbChoise.SelectedIndex == 1)
			{
				if ((int)Utils.ChaFieldNames.Length == (int)Utils.ChaFieldValues.Length)
				{
					for (int j = 0; j < (int)Utils.ChaFieldNames.Length; j++)
					{
						this.cbField.Items.Add(new ComboBoxItem(Utils.ChaFieldNames[j], Utils.ChaFieldValues[j]));
					}
					return;
				}
                Utils.WarningMessage("Configuration file error! Node ChaFieldNames and ChaFieldValues number of inconsistencies!");
			}
		}

		private void cbField_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.cbFilter.Items.Clear();
			if (this.cbField.SelectedIndex > 0)
			{
				for (int i = 0; i < (int)Utils.SearchNames.Length; i++)
				{
					this.cbFilter.Items.Add(new ComboBoxItem(Utils.SearchNames[i], Utils.SearchValues[i]));
				}
				this.cbFilter.SelectedIndex = 0;
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

		private void frmUser_FormClosed(object sender, FormClosedEventArgs e)
		{
			frmUser.form = null;
		}

		private string getIDS(int index)
		{
			string str = "''";
			int num = this.cell + index % 2;
			foreach (DataGridViewRow selectedRow in this.gvData.SelectedRows)
			{
				object obj = str;
				object[] value = new object[] { obj, ",'", selectedRow.Cells[num].Value, "'" };
				str = string.Concat(value);
			}
			if (str == "''" && this.gvData.CurrentRow != null)
			{
				object obj1 = str;
				object[] objArray = new object[] { obj1, ",'", this.gvData.CurrentRow.Cells[num].Value, "'" };
				str = string.Concat(objArray);
			}
			if (str == "''")
			{
                Utils.WarningMessage("Please select the line to be operated!");
				str = "";
			}
			return str;
		}

		public static frmUser GetInstance(frmMain frm, string IP)
		{
			if (frmUser.form == null)
			{
				frmUser.form = new frmUser(frm, IP);
			}
			return frmUser.form;
		}

		private void gvData_CellClick(object sender, DataGridViewCellEventArgs e)
		{
			if (e.RowIndex >= 0)
			{
				this.gvData.Rows[e.RowIndex].Selected = true;
			}
		}

		private void gvData_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
		{
			this.Cursor = Cursors.WaitCursor;
			if (e.RowIndex >= 0)
			{
				this.frmM.InputAccount(this.gvData.Rows[e.RowIndex].Cells[this.cell].Value.ToString());
				if (this.gvData.Rows[e.RowIndex].Cells[this.cell + 1].Value != null && this.gvData.Rows[e.RowIndex].Cells[this.cell + 1].Value.ToString() != "")
				{
					this.frmM.InputCharacter(this.gvData.Rows[e.RowIndex].Cells[this.cell + 1].Value.ToString());
				}
			}
			this.Cursor = Cursors.Default;
		}

		private void gvData_RowPostPaint(object sender, DataGridViewRowPostPaintEventArgs e)
		{
			int x = e.RowBounds.Location.X;
			int y = e.RowBounds.Location.Y;
			Rectangle rowBounds = e.RowBounds;
			Rectangle rectangle = new Rectangle(x, y, this.gvData.RowHeadersWidth - 4, rowBounds.Height);
			int rowIndex = e.RowIndex + 1;
			TextRenderer.DrawText(e.Graphics, rowIndex.ToString(), this.gvData.RowHeadersDefaultCellStyle.Font, rectangle, this.gvData.RowHeadersDefaultCellStyle.ForeColor, TextFormatFlags.Right | TextFormatFlags.VerticalCenter);
		}

		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.txtAccount = new MuEditor.TextBox();
			this.cbChoise = new ComboBox();
			this.groupBox1 = new GroupBox();
			this.cbGM = new CheckBox();
			this.cbRed = new CheckBox();
			this.cbFilter = new ComboBox();
			this.cbField = new ComboBox();
			this.btnSearch = new Button();
			this.cbOnline = new CheckBox();
			this.cbEnvelop = new CheckBox();
			this.gvData = new DataGridView();
			this.groupBox2 = new GroupBox();
			this.btnCancel = new Button();
			this.btnXX = new Button();
			this.btnJF = new Button();
			this.btnFH = new Button();
			this.ccmsMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.批量封号AToolStripMenuItem = new ToolStripMenuItem();
			this.批量解封DToolStripMenuItem = new ToolStripMenuItem();
			this.批量下线OToolStripMenuItem = new ToolStripMenuItem();
			this.groupBox1.SuspendLayout();
			((ISupportInitialize)this.gvData).BeginInit();
			this.groupBox2.SuspendLayout();
			this.ccmsMenu.SuspendLayout();
			base.SuspendLayout();
			this.txtAccount.IsOnlyNumber = false;
			this.txtAccount.Location = new Point(217, 15);
			this.txtAccount.MaxLength = 50;
			this.txtAccount.Name = "txtAccount";
			this.txtAccount.Size = new System.Drawing.Size(127, 21);
			this.txtAccount.TabIndex = 0;
			this.txtAccount.KeyPress += new KeyPressEventHandler(this.txtAccount_KeyPress);
			this.cbChoise.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbChoise.FormattingEnabled = true;
			this.cbChoise.Items.AddRange(new object[] { "Account", "Character", "IP" });
			this.cbChoise.Location = new Point(12, 15);
			this.cbChoise.Name = "cbChoise";
			this.cbChoise.Size = new System.Drawing.Size(52, 20);
			this.cbChoise.TabIndex = 1;
			this.cbChoise.SelectedIndexChanged += new EventHandler(this.cbChoise_SelectedIndexChanged);
			this.groupBox1.Controls.Add(this.cbGM);
			this.groupBox1.Controls.Add(this.cbRed);
			this.groupBox1.Controls.Add(this.cbFilter);
			this.groupBox1.Controls.Add(this.cbField);
			this.groupBox1.Controls.Add(this.btnSearch);
			this.groupBox1.Controls.Add(this.cbOnline);
			this.groupBox1.Controls.Add(this.cbEnvelop);
			this.groupBox1.Controls.Add(this.cbChoise);
			this.groupBox1.Controls.Add(this.txtAccount);
			this.groupBox1.Dock = DockStyle.Top;
			this.groupBox1.Location = new Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(604, 39);
			this.groupBox1.TabIndex = 4;
			this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Inquire";
			this.cbGM.AutoSize = true;
			this.cbGM.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.cbGM.Location = new Point(501, 17);
			this.cbGM.Name = "cbGM";
			this.cbGM.Size = new System.Drawing.Size(36, 16);
			this.cbGM.TabIndex = 12;
			this.cbGM.Text = "GM";
			this.cbGM.UseVisualStyleBackColor = true;
			this.cbRed.AutoSize = true;
			this.cbRed.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.cbRed.Location = new Point(450, 17);
			this.cbRed.Name = "cbRed";
			this.cbRed.Size = new System.Drawing.Size(48, 16);
			this.cbRed.TabIndex = 11;
            this.cbRed.Text = "Red name";
			this.cbRed.UseVisualStyleBackColor = true;
			this.cbFilter.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbFilter.FormattingEnabled = true;
            this.cbFilter.Items.AddRange(new object[] { "Account", "Character", "IP" });
			this.cbFilter.Location = new Point(167, 15);
			this.cbFilter.Name = "cbFilter";
			this.cbFilter.Size = new System.Drawing.Size(46, 20);
			this.cbFilter.TabIndex = 10;
			this.cbField.DropDownHeight = 306;
			this.cbField.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbField.FormattingEnabled = true;
			this.cbField.IntegralHeight = false;
			this.cbField.Items.AddRange(new object[] { "Account", "Character", "IP" });
			this.cbField.Location = new Point(69, 15);
			this.cbField.Name = "cbField";
			this.cbField.Size = new System.Drawing.Size(94, 20);
			this.cbField.TabIndex = 9;
			this.cbField.SelectedIndexChanged += new EventHandler(this.cbField_SelectedIndexChanged);
			this.btnSearch.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnSearch.Location = new Point(543, 13);
			this.btnSearch.Name = "btnSearch";
			this.btnSearch.Size = new System.Drawing.Size(50, 23);
			this.btnSearch.TabIndex = 8;
            this.btnSearch.Text = "Inquire";
			this.btnSearch.UseVisualStyleBackColor = true;
			this.btnSearch.Click += new EventHandler(this.btnSearch_Click);
			this.cbOnline.AutoSize = true;
			this.cbOnline.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.cbOnline.Location = new Point(399, 17);
			this.cbOnline.Name = "cbOnline";
			this.cbOnline.Size = new System.Drawing.Size(48, 16);
			this.cbOnline.TabIndex = 7;
            this.cbOnline.Text = "Online";
			this.cbOnline.UseVisualStyleBackColor = true;
			this.cbEnvelop.AutoSize = true;
			this.cbEnvelop.Location = new Point(349, 17);
			this.cbEnvelop.Name = "cbEnvelop";
			this.cbEnvelop.Size = new System.Drawing.Size(48, 16);
			this.cbEnvelop.TabIndex = 6;
            this.cbEnvelop.Text = "Blocked";
			this.cbEnvelop.UseVisualStyleBackColor = true;
			this.gvData.AllowUserToAddRows = false;
			this.gvData.AllowUserToDeleteRows = false;
			this.gvData.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.gvData.Location = new Point(0, 43);
			this.gvData.Name = "gvData";
			this.gvData.ReadOnly = true;
			this.gvData.RowHeadersWidth = 30;
			this.gvData.RowTemplate.Height = 23;
			this.gvData.Size = new System.Drawing.Size(604, 279);
			this.gvData.TabIndex = 6;
			this.gvData.CellClick += new DataGridViewCellEventHandler(this.gvData_CellClick);
			this.gvData.CellDoubleClick += new DataGridViewCellEventHandler(this.gvData_CellDoubleClick);
			this.gvData.RowPostPaint += new DataGridViewRowPostPaintEventHandler(this.gvData_RowPostPaint);
			this.groupBox2.Controls.Add(this.btnCancel);
			this.groupBox2.Controls.Add(this.btnXX);
			this.groupBox2.Controls.Add(this.btnJF);
			this.groupBox2.Controls.Add(this.btnFH);
			this.groupBox2.Dock = DockStyle.Bottom;
			this.groupBox2.Location = new Point(0, 328);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(604, 39);
			this.groupBox2.TabIndex = 7;
			this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Operating";
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new Point(402, 13);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(50, 23);
			this.btnCancel.TabIndex = 35;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new EventHandler(this.btnCancel_Click);
			this.btnXX.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnXX.Location = new Point(319, 13);
			this.btnXX.Name = "btnXX";
			this.btnXX.Size = new System.Drawing.Size(71, 23);
			this.btnXX.TabIndex = 11;
            this.btnXX.Text = "Batch offline";
			this.btnXX.UseVisualStyleBackColor = true;
			this.btnXX.Click += new EventHandler(this.btnXX_Click);
			this.btnJF.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnJF.Location = new Point(236, 13);
			this.btnJF.Name = "btnJF";
			this.btnJF.Size = new System.Drawing.Size(71, 23);
			this.btnJF.TabIndex = 10;
            this.btnJF.Text = "Batch unblocking";
			this.btnJF.UseVisualStyleBackColor = true;
			this.btnJF.Click += new EventHandler(this.btnJF_Click);
			this.btnFH.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnFH.Location = new Point(153, 13);
			this.btnFH.Name = "btnFH";
			this.btnFH.Size = new System.Drawing.Size(71, 23);
			this.btnFH.TabIndex = 9;
            this.btnFH.Text = "Bulk title";
			this.btnFH.UseVisualStyleBackColor = true;
			this.btnFH.Click += new EventHandler(this.btnFH_Click);
			ToolStripItemCollection items = this.ccmsMenu.Items;
			ToolStripItem[] toolStripItemArray = new ToolStripItem[] { this.批量封号AToolStripMenuItem, this.批量解封DToolStripMenuItem, this.批量下线OToolStripMenuItem };
			items.AddRange(toolStripItemArray);
			this.ccmsMenu.Name = "ccmsMenu";
			this.ccmsMenu.Size = new System.Drawing.Size(143, 70);
			this.批量封号AToolStripMenuItem.Name = "批量封号AToolStripMenuItem";
			this.批量封号AToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
			this.批量封号AToolStripMenuItem.Text = "批量封号(&B)";
			this.批量封号AToolStripMenuItem.Click += new EventHandler(this.btnFH_Click);
			this.批量解封DToolStripMenuItem.Name = "批量解封DToolStripMenuItem";
			this.批量解封DToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
			this.批量解封DToolStripMenuItem.Text = "批量解封(&D)";
			this.批量解封DToolStripMenuItem.Click += new EventHandler(this.btnJF_Click);
			this.批量下线OToolStripMenuItem.Name = "批量下线OToolStripMenuItem";
			this.批量下线OToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
			this.批量下线OToolStripMenuItem.Text = "批量下线(&O)";
			this.批量下线OToolStripMenuItem.Click += new EventHandler(this.btnXX_Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(604, 367);
			base.Controls.Add(this.groupBox2);
			base.Controls.Add(this.gvData);
			base.Controls.Add(this.groupBox1);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.IsMdiContainer = true;
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmUser";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
            this.Text = "People Management";
			base.FormClosed += new FormClosedEventHandler(this.frmUser_FormClosed);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((ISupportInitialize)this.gvData).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.ccmsMenu.ResumeLayout(false);
			base.ResumeLayout(false);
		}

		private void operate(bool isXX, int val)
		{
			string str = "UPDATE {0} SET {1} = {2} WHERE {3} IN ({4})";
			try
			{
				string str1 = "[MEMB_INFO]";
				string str2 = "[bloc_code]";
				string str3 = "[memb___id]";
				if (isXX)
				{
					str1 = "[MEMB_STAT]";
					str2 = "[ConnectStat]";
				}
				else if (this.cbChoise.SelectedIndex == 1)
				{
					str1 = "[Character]";
					str2 = "[CtlCode]";
					str3 = "[Name]";
				}
				object[] objArray = new object[] { str1, str2, val, str3, this.getIDS(this.cbChoise.SelectedIndex) };
				str = string.Format(str, objArray);
				if (!base.Me_ExecuteSQL(str))
				{
                    Utils.WarningMessage("operation failed!");
				}
				else
				{
                    Utils.InfoMessage("Successful operation!");
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void txtAccount_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == '\r')
			{
				this.btnSearch_Click(sender, e);
			}
		}
	}
}