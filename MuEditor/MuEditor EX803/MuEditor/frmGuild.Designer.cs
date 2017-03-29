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
	public class frmGuild : frmBase
	{
		private IContainer components;

		private ComboBox cbGuild;

		private GroupBox groupBox1;

		private Button btnSearch;

		private MuEditor.TextBox txtName;

		private RadioButton rbMember;

		private RadioButton rbGuild;

		private ListBox lbMember;

		private MuEditor.TextBox txtNotice;

		private Button btnOK;

		private Label label3;

		private Label label1;

		private Label label2;

		private Label label4;

		private ListBox lstUnion;

		private ListBox lstRival;

		private Label label5;

		private Button btnAdd;

		private Button btnDel;

		private Label label6;

		private MuEditor.TextBox txtScore;

		private Button btnJS;

		public static string joinName;

		private static frmGuild form;

		private frmMain frmM;

		private DataView dv;

		static frmGuild()
		{
			frmGuild.joinName = "";
			frmGuild.form = null;
		}

		private frmGuild(frmMain frm)
		{
			this.InitializeComponent();
			this.frmM = frm;
			this.init();
			this.bind();
		}

		private void bind()
		{
			string str = "SELECT DISTINCT a.G_Name FROM Guild AS a INNER JOIN GuildMember AS b ON a.G_Name = b.G_Name COLLATE Chinese_PRC_CS_AS_KS_WS {0}";
			try
			{
				this.cbGuild.Items.Clear();
				this.lbMember.Items.Clear();
				this.lstUnion.Items.Clear();
				this.lstRival.Items.Clear();
				string str1 = "where 1=1";
				if (this.txtName.Text.Trim() != "")
				{
					str1 = (this.rbMember.Checked ? "Name" : "a.G_Name");
					str1 = string.Format("WHERE {0} LIKE '%{1}%'", str1, this.txtName.Text.Trim().Replace("'", "''"));
				}
				OleDbCommand oleDbCommand = new OleDbCommand(string.Format(str, str1), frmBase.Mu_Conn);
				OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(oleDbCommand);
				DataTable dataTable = new DataTable();
				oleDbDataAdapter.Fill(dataTable);
				foreach (DataRow row in dataTable.Rows)
				{
					this.cbGuild.Items.Add(row[0].ToString().Trim());
				}
				this.btnAdd.Enabled = this.cbGuild.Items.Count > 0;
				this.btnDel.Enabled = this.cbGuild.Items.Count > 0;
				this.btnJS.Enabled = this.cbGuild.Items.Count > 0;
				this.btnOK.Enabled = this.cbGuild.Items.Count > 0;
				if (this.cbGuild.Items.Count <= 0)
				{
					this.txtNotice.Text = "";
				}
				else
				{
					this.cbGuild.SelectedIndex = 0;
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void btnAdd_Click(object sender, EventArgs e)
		{
			string str = "INSERT INTO GuildMember (Name, G_Name, G_Level, G_Status) VALUES ('{0}', '{1}', 1, 0)";
			try
			{
				this.Cursor = Cursors.WaitCursor;
				frmGuild.joinName = "";
				(new frmGuildUser()).ShowDialog(this);
				if (frmGuild.joinName != "")
				{
					if (!(new OleDbCommand(string.Format("SELECT 1 FROM Character WHERE (Name = '{0}')", frmGuild.joinName), frmBase.Mu_Conn)).ExecuteReader().Read())
					{
                        Utils.WarningMessage("There is no role!");
					}
					else if (!base.Mu_ExecuteSQL(string.Format(str, frmGuild.joinName, this.cbGuild.SelectedItem.ToString().Replace("'", "''"))))
					{
                        Utils.WarningMessage("operation failed!");
					}
					else
					{
						string str1 = this.cbGuild.SelectedItem.ToString();
						this.init();
						this.bind();
						this.cbGuild.SelectedItem = str1;
                        Utils.InfoMessage("Successful operation!");
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		private void btnDel_Click(object sender, EventArgs e)
		{
			string str = "DELETE FROM GuildMember WHERE (Name = '{0}')";
			try
			{
				this.Cursor = Cursors.WaitCursor;
				if (this.lbMember.SelectedIndex != -1)
				{
					string str1 = this.lbMember.SelectedItem.ToString();
                    if (str1 != "[Leader]" && str1.EndsWith("[Leader]"))
					{
                        Utils.WarningMessage("You can not delete chief!");
						this.Cursor = Cursors.Default;
						return;
					}
                    else if (!base.Mu_ExecuteSQL(string.Format(str, str1.Replace("'", "''").Replace("[Deputy chief]", "").Replace("[Battle captain]", ""))))
					{
                        Utils.WarningMessage("operation failed!");
					}
					else
					{
						string str2 = this.cbGuild.SelectedItem.ToString();
						this.init();
						this.bind();
						this.cbGuild.SelectedItem = str2;
                        Utils.InfoMessage("Successful operation!");
					}
				}
				else
				{
                    Utils.WarningMessage("Please choose to delete a member!");
					this.Cursor = Cursors.Default;
					return;
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		private void btnJS_Click(object sender, EventArgs e)
		{
			string str = "DELETE FROM GuildMember WHERE (G_Name = '{0}');DELETE FROM Guild WHERE (G_Name = '{0}')";
			try
			{
				this.Cursor = Cursors.WaitCursor;
                if (MessageBox.Show(string.Concat("Are you sure you want to disband the current Zhanmeng", this.cbGuild.SelectedItem, "?"), "System Messages", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == System.Windows.Forms.DialogResult.Yes)
				{
					if (!base.Mu_ExecuteSQL(string.Format(str, this.cbGuild.SelectedItem.ToString().Replace("'", "''"))))
					{
                        Utils.WarningMessage("operation failed!");
					}
					else
					{
						this.init();
						this.bind();
                        Utils.InfoMessage("Successful operation!");
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			string str = "";
			try
			{
				this.Cursor = Cursors.WaitCursor;
				if (this.cbGuild.SelectedIndex != -1)
				{
					str = string.Format("UPDATE Guild SET G_Score = {0}, G_Notice = '{1}' WHERE (G_Name = '{2}')", this.txtScore.Text.Replace(" ", ""), this.txtNotice.Text.Replace("'", "''"), this.cbGuild.SelectedItem.ToString().Replace("'", "''"));
					if (!base.Mu_ExecuteSQL(str))
					{
						Utils.WarningMessage("操作失败！");
					}
					else
					{
						this.init();
						Utils.InfoMessage("操作成功！");
					}
				}
				else
				{
					return;
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		private void btnSearch_Click(object sender, EventArgs e)
		{
			this.Cursor = Cursors.WaitCursor;
			this.bind();
			this.Cursor = Cursors.Default;
		}

		private void cbGuild_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.Cursor = Cursors.WaitCursor;
			this.lbMember.Items.Clear();
			string str = string.Concat("SELECT Name, G_Status FROM GuildMember WHERE (G_Name = '", this.cbGuild.SelectedItem.ToString().Replace("'", "''"), "') ORDER BY G_Status DESC");
			try
			{
				OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(new OleDbCommand(str, frmBase.Mu_Conn));
				DataTable dataTable = new DataTable();
				oleDbDataAdapter.Fill(dataTable);
				foreach (DataRow row in dataTable.Rows)
				{
					int num = Convert.ToInt32(row[1]);
					if (num <= 0)
					{
						this.lbMember.Items.Add(row[0].ToString().Trim());
					}
					else
					{
						string str1 = "盟主";
						if (num == 32)
						{
							str1 = "战斗队长";
						}
						else if (num == 64)
						{
							str1 = "副盟主";
						}
						this.lbMember.Items.Add(string.Format("{0}[{1}]", row[0].ToString().Trim(), str1));
					}
				}
				this.dv.RowFilter = string.Concat("(G_Name = '", this.cbGuild.SelectedItem.ToString().Replace("'", "''"), "')");
				string str2 = "0";
				string str3 = "0";
				string str4 = "0";
				if (this.dv.Count > 0)
				{
					this.txtScore.Text = Convert.ToString(this.dv[0]["G_Score"]);
					this.txtScore.Text = (this.txtScore.Text == "" ? "0" : this.txtScore.Text);
					this.txtNotice.Text = Convert.ToString(this.dv[0]["G_Notice"]);
					str2 = Convert.ToString(this.dv[0]["G_Union"]);
					str3 = Convert.ToString(this.dv[0]["G_Rival"]);
					str4 = Convert.ToString(this.dv[0]["Number"]);
				}
				this.lstUnion.Items.Clear();
				this.dv.RowFilter = string.Format("(G_Union <> 0 AND G_Name <> '{0}' AND G_Union = {1}) OR (G_Name <> '{0}' AND G_Union = {2})", this.cbGuild.SelectedItem.ToString().Replace("'", "''"), str2, str4);
				for (int i = 0; i < this.dv.Count; i++)
				{
					this.lstUnion.Items.Add(Convert.ToString(this.dv[i]["G_Name"]));
				}
				this.lstRival.Items.Clear();
				this.dv.RowFilter = string.Format("(G_Rival <> 0 AND G_Name <> '{0}' AND G_Rival = {1}) OR (G_Name <> '{0}' AND G_Rival = {2})", this.cbGuild.SelectedItem.ToString().Replace("'", "''"), str3, str4);
				for (int j = 0; j < this.dv.Count; j++)
				{
					if (!this.lstUnion.Items.Contains(Convert.ToString(this.dv[j]["G_Name"])))
					{
						this.lstRival.Items.Add(Convert.ToString(this.dv[j]["G_Name"]));
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void frmGuild_FormClosed(object sender, FormClosedEventArgs e)
		{
			frmGuild.form = null;
		}

		public static frmGuild GetInstance(frmMain frm)
		{
			if (frmGuild.form == null)
			{
				frmGuild.form = new frmGuild(frm);
			}
			return frmGuild.form;
		}

		private void init()
		{
			string str = "SELECT Number, G_Name, G_Score, G_Notice, G_Rival, G_Union FROM Guild";
			try
			{
				OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter(new OleDbCommand(str, frmBase.Mu_Conn));
				DataTable dataTable = new DataTable();
				oleDbDataAdapter.Fill(dataTable);
				this.dv = dataTable.DefaultView;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}

		private void InitializeComponent()
		{
			this.cbGuild = new ComboBox();
			this.groupBox1 = new GroupBox();
			this.rbMember = new RadioButton();
			this.rbGuild = new RadioButton();
			this.btnSearch = new Button();
			this.txtName = new MuEditor.TextBox();
			this.lbMember = new ListBox();
			this.txtNotice = new MuEditor.TextBox();
			this.btnOK = new Button();
			this.label3 = new Label();
			this.label1 = new Label();
			this.label2 = new Label();
			this.label4 = new Label();
			this.lstUnion = new ListBox();
			this.lstRival = new ListBox();
			this.label5 = new Label();
			this.btnAdd = new Button();
			this.btnDel = new Button();
			this.label6 = new Label();
			this.txtScore = new MuEditor.TextBox();
			this.btnJS = new Button();
			this.groupBox1.SuspendLayout();
			base.SuspendLayout();
			this.cbGuild.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
			this.cbGuild.AutoCompleteSource = AutoCompleteSource.ListItems;
			this.cbGuild.DropDownHeight = 306;
			this.cbGuild.IntegralHeight = false;
			this.cbGuild.Location = new Point(6, 62);
			this.cbGuild.Name = "cbGuild";
			this.cbGuild.Size = new System.Drawing.Size(115, 20);
			this.cbGuild.TabIndex = 2;
			this.cbGuild.SelectedIndexChanged += new EventHandler(this.cbGuild_SelectedIndexChanged);
			this.groupBox1.Controls.Add(this.rbMember);
			this.groupBox1.Controls.Add(this.rbGuild);
			this.groupBox1.Controls.Add(this.btnSearch);
			this.groupBox1.Controls.Add(this.txtName);
			this.groupBox1.Dock = DockStyle.Top;
			this.groupBox1.Location = new Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(300, 39);
			this.groupBox1.TabIndex = 5;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "查询";
			this.rbMember.AutoSize = true;
			this.rbMember.Location = new Point(196, 17);
			this.rbMember.Name = "rbMember";
			this.rbMember.Size = new System.Drawing.Size(47, 16);
			this.rbMember.TabIndex = 10;
			this.rbMember.Text = "成员";
			this.rbMember.UseVisualStyleBackColor = true;
			this.rbGuild.AutoSize = true;
			this.rbGuild.Checked = true;
			this.rbGuild.Location = new Point(144, 18);
			this.rbGuild.Name = "rbGuild";
			this.rbGuild.Size = new System.Drawing.Size(47, 16);
			this.rbGuild.TabIndex = 9;
			this.rbGuild.TabStop = true;
			this.rbGuild.Text = "战盟";
			this.rbGuild.UseVisualStyleBackColor = true;
			this.btnSearch.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnSearch.Location = new Point(244, 13);
			this.btnSearch.Name = "btnSearch";
			this.btnSearch.Size = new System.Drawing.Size(50, 23);
			this.btnSearch.TabIndex = 8;
			this.btnSearch.Text = "查 询";
			this.btnSearch.UseVisualStyleBackColor = true;
			this.btnSearch.Click += new EventHandler(this.btnSearch_Click);
			this.txtName.IsOnlyNumber = false;
			this.txtName.Location = new Point(7, 15);
			this.txtName.MaxLength = 50;
			this.txtName.Name = "txtName";
			this.txtName.Size = new System.Drawing.Size(130, 21);
			this.txtName.TabIndex = 0;
			this.txtName.KeyPress += new KeyPressEventHandler(this.txtName_KeyPress);
			this.lbMember.FormattingEnabled = true;
			this.lbMember.ItemHeight = 12;
			this.lbMember.Location = new Point(126, 62);
			this.lbMember.Name = "lbMember";
			this.lbMember.Size = new System.Drawing.Size(167, 184);
			this.lbMember.TabIndex = 6;
			this.lbMember.MouseDoubleClick += new MouseEventHandler(this.lbMember_MouseDoubleClick);
			this.txtNotice.AcceptsReturn = true;
			this.txtNotice.IsOnlyNumber = false;
			this.txtNotice.Location = new Point(70, 282);
			this.txtNotice.MaxLength = 60;
			this.txtNotice.Name = "txtNotice";
			this.txtNotice.Size = new System.Drawing.Size(178, 21);
			this.txtNotice.TabIndex = 7;
			this.btnOK.Enabled = false;
			this.btnOK.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnOK.Location = new Point(254, 282);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(39, 23);
			this.btnOK.TabIndex = 9;
			this.btnOK.Text = "更新";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new EventHandler(this.btnOK_Click);
			this.label3.AutoSize = true;
			this.label3.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label3.Location = new Point(4, 288);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(65, 12);
			this.label3.TabIndex = 10;
			this.label3.Text = "战盟公告：";
			this.label1.AutoSize = true;
			this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label1.Location = new Point(124, 45);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(77, 12);
			this.label1.TabIndex = 11;
			this.label1.Text = "战盟成员列表";
			this.label2.AutoSize = true;
			this.label2.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label2.Location = new Point(5, 45);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(53, 12);
			this.label2.TabIndex = 12;
			this.label2.Text = "战盟列表";
			this.label4.AutoSize = true;
			this.label4.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label4.Location = new Point(5, 87);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(53, 12);
			this.label4.TabIndex = 13;
			this.label4.Text = "同盟战盟";
			this.lstUnion.FormattingEnabled = true;
			this.lstUnion.ItemHeight = 12;
			this.lstUnion.Location = new Point(6, 102);
			this.lstUnion.Name = "lstUnion";
			this.lstUnion.Size = new System.Drawing.Size(115, 64);
			this.lstUnion.TabIndex = 14;
			this.lstUnion.SelectedIndexChanged += new EventHandler(this.lstUnion_SelectedIndexChanged);
			this.lstRival.FormattingEnabled = true;
			this.lstRival.ItemHeight = 12;
			this.lstRival.Location = new Point(6, 185);
			this.lstRival.Name = "lstRival";
			this.lstRival.Size = new System.Drawing.Size(115, 64);
			this.lstRival.TabIndex = 15;
			this.lstRival.SelectedIndexChanged += new EventHandler(this.lstRival_SelectedIndexChanged);
			this.label5.AutoSize = true;
			this.label5.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label5.Location = new Point(5, 169);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(53, 12);
			this.label5.TabIndex = 16;
			this.label5.Text = "敌对战盟";
			this.btnAdd.Enabled = false;
			this.btnAdd.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnAdd.Location = new Point(125, 251);
			this.btnAdd.Name = "btnAdd";
			this.btnAdd.Size = new System.Drawing.Size(61, 23);
			this.btnAdd.TabIndex = 17;
			this.btnAdd.Text = "添加成员";
			this.btnAdd.UseVisualStyleBackColor = true;
			this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
			this.btnDel.Enabled = false;
			this.btnDel.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnDel.Location = new Point(190, 251);
			this.btnDel.Name = "btnDel";
			this.btnDel.Size = new System.Drawing.Size(61, 23);
			this.btnDel.TabIndex = 18;
			this.btnDel.Text = "删除成员";
			this.btnDel.UseVisualStyleBackColor = true;
			this.btnDel.Click += new EventHandler(this.btnDel_Click);
			this.label6.AutoSize = true;
			this.label6.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label6.Location = new Point(4, 260);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(65, 12);
			this.label6.TabIndex = 20;
			this.label6.Text = "战盟积分：";
			this.txtScore.IsOnlyNumber = true;
			this.txtScore.Location = new Point(70, 256);
			this.txtScore.Name = "txtScore";
			this.txtScore.Size = new System.Drawing.Size(43, 21);
			this.txtScore.TabIndex = 54;
			this.btnJS.Enabled = false;
			this.btnJS.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnJS.Location = new Point(254, 251);
			this.btnJS.Name = "btnJS";
			this.btnJS.Size = new System.Drawing.Size(39, 23);
			this.btnJS.TabIndex = 55;
			this.btnJS.Text = "解散";
			this.btnJS.UseVisualStyleBackColor = true;
			this.btnJS.Click += new EventHandler(this.btnJS_Click);
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(300, 308);
			base.Controls.Add(this.btnJS);
			base.Controls.Add(this.txtScore);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.btnDel);
			base.Controls.Add(this.btnAdd);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.lstRival);
			base.Controls.Add(this.lstUnion);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.btnOK);
			base.Controls.Add(this.txtNotice);
			base.Controls.Add(this.lbMember);
			base.Controls.Add(this.groupBox1);
			base.Controls.Add(this.cbGuild);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmGuild";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			this.Text = "战盟管理";
			base.TopMost = true;
			base.FormClosed += new FormClosedEventHandler(this.frmGuild_FormClosed);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		private void lbMember_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			this.Cursor = Cursors.WaitCursor;
			if (this.lbMember.SelectedItem != null)
			{
				frmMain _frmMain = this.frmM;
				string str = this.lbMember.SelectedItem.ToString();
				char[] chrArray = new char[] { '[' };
				_frmMain.InputCharacter(str.Split(chrArray)[0]);
			}
			this.Cursor = Cursors.Default;
		}

		private void lstRival_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.cbGuild.SelectedItem = this.lstRival.SelectedItem.ToString();
		}

		private void lstUnion_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.cbGuild.SelectedItem = this.lstUnion.SelectedItem.ToString();
		}

		private void txtName_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == '\r')
			{
				this.btnSearch_Click(sender, e);
			}
		}
	}
}