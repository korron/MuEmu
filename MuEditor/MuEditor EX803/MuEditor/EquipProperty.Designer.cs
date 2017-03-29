using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Resources;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace MuEditor
{
	public class EquipProperty : frmBase
	{
		private const int CB_FINDSTRING = 332;

		private IContainer components;

		private ComboBox cboEquipLevel;

		private ComboBox cboEquipExt;

		private Label label31;

		private GroupBox groupBox3;

		private Button button3;

		private Button button2;

		private CheckBox chkEquipZY6;

		private CheckBox chkEquipZY4;

		private CheckBox chkEquipZY2;

		private CheckBox chkEquipZY5;

		private CheckBox chkEquipZY3;

		private CheckBox chkEquipZY1;

		private CheckBox chkEquipXY;

		private CheckBox chkEquipJN;

		private Label label30;

		private Label label1;

		private MuEditor.TextBox txtName;

		private Button btnOK;

		private Button btnCancel;

		private Label label2;

		private MuEditor.TextBox txtEquipCodes;

		private MuEditor.TextBox txtDurability;

		private Label label4;

		private ComboBox cbSetVal;

		private Label label5;

		private CheckBox chk380;

		private Label label3;

		private Label eee;

		private ComboBox cboPlusLevel;

		private ComboBox cboPlusType;

		private GroupBox gbXQ;

		private ComboBox cbInlay6b;

		private Label label11;

		private Label label10;

		private Label label9;

		private Label label8;

		private Label label7;

		private Label label6;

		private ComboBox cbInlay5b;

		private ComboBox cbInlay4b;

		private ComboBox cbInlay3b;

		private ComboBox cbInlay2b;

		private ComboBox cbInlay1b;

		private Label label12;

		private MuEditor.TextBox txtSN;

		private Button button4;

		private Button button1;

		private EquipItem item;

		public EquipProperty()
		{
			this.InitializeComponent();
		}

		public EquipProperty(EquipItem item)
		{
			this.InitializeComponent();
			this.item = item;
			this.updateUI(item);
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			this.item = null;
		}

		private void btnOK_Click(object sender, EventArgs e)
		{
			if (this.item != null)
			{
				this.updateData(this.item);
			}
			this.item = null;
			base.Close();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			this.chkEquipZY1.Checked = Utils.JPZY1;
			this.chkEquipZY2.Checked = Utils.JPZY2;
			this.chkEquipZY3.Checked = Utils.JPZY3;
			this.chkEquipZY4.Checked = Utils.JPZY4;
			this.chkEquipZY5.Checked = Utils.JPZY5;
			this.chkEquipZY6.Checked = Utils.JPZY6;
			this.cboEquipLevel.SelectedIndex = Utils.JPLevel;
			this.cboEquipExt.SelectedIndex = Utils.JPExt;
			this.chkEquipJN.Checked = Utils.JPJN;
			this.chkEquipXY.Checked = Utils.JPXY;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			this.chkEquipZY1.Checked = this.chkEquipZY1.Enabled;
			this.chkEquipZY2.Checked = this.chkEquipZY2.Enabled;
			this.chkEquipZY3.Checked = this.chkEquipZY3.Enabled;
			this.chkEquipZY4.Checked = this.chkEquipZY4.Enabled;
			this.chkEquipZY5.Checked = this.chkEquipZY5.Enabled;
			this.chkEquipZY6.Checked = this.chkEquipZY6.Enabled;
		}

		private void button3_Click(object sender, EventArgs e)
		{
			this.chkEquipZY1.Checked = false;
			this.chkEquipZY2.Checked = false;
			this.chkEquipZY3.Checked = false;
			this.chkEquipZY4.Checked = false;
			this.chkEquipZY5.Checked = false;
			this.chkEquipZY6.Checked = false;
		}

		private void button4_Click(object sender, EventArgs e)
		{
			this.chkEquipZY1.Checked = Utils.DJZY1;
			this.chkEquipZY2.Checked = Utils.DJZY2;
			this.chkEquipZY3.Checked = Utils.DJZY3;
			this.chkEquipZY4.Checked = Utils.DJZY4;
			this.chkEquipZY5.Checked = Utils.DJZY5;
			this.chkEquipZY6.Checked = Utils.DJZY6;
			this.cboEquipLevel.SelectedIndex = Utils.DJLevel;
			this.cboEquipExt.SelectedIndex = Utils.DJExt;
			this.chkEquipJN.Checked = Utils.DJJN;
			this.chkEquipXY.Checked = Utils.DJXY;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void Init_EquipEditor()
		{
			this.cbInlay1b.Items.Clear();
			this.cbInlay2b.Items.Clear();
			this.cbInlay3b.Items.Clear();
			this.cbInlay4b.Items.Clear();
			this.cbInlay5b.Items.Clear();
			this.cbInlay1b.Items.Add(new ComboBoxItem("未开孔", "255"));
			this.cbInlay1b.Items.Add(new ComboBoxItem("无属性", "254"));
			for (int i = 0; i < 50; i++)
			{
				if (EquipEditor.xSocket[i].捞抚[0] != 0)
				{
					for (int j = 0; j < 5; j++)
					{
						string str = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[i].捞抚, 64), " +", EquipEditor.xSocket[i].饭骇1[j].ToString());
						string str1 = (i + j * 50).ToString();
						this.cbInlay1b.Items.Add(new ComboBoxItem(str, str1));
					}
				}
			}
			this.cbInlay2b.Items.Add(new ComboBoxItem("未开孔", "255"));
			this.cbInlay2b.Items.Add(new ComboBoxItem("无属性", "254"));
			for (int k = 0; k < 50; k++)
			{
				if (EquipEditor.xSocket[k].捞抚[0] != 0)
				{
					for (int l = 0; l < 5; l++)
					{
						string str2 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[k].捞抚, 64), " +", EquipEditor.xSocket[k].饭骇1[l].ToString());
						string str3 = (k + l * 50).ToString();
						this.cbInlay2b.Items.Add(new ComboBoxItem(str2, str3));
					}
				}
			}
			this.cbInlay3b.Items.Add(new ComboBoxItem("未开孔", "255"));
			this.cbInlay3b.Items.Add(new ComboBoxItem("无属性", "254"));
			for (int m = 0; m < 50; m++)
			{
				if (EquipEditor.xSocket[m].捞抚[0] != 0)
				{
					for (int n = 0; n < 5; n++)
					{
						string str4 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[m].捞抚, 64), " +", EquipEditor.xSocket[m].饭骇1[n].ToString());
						string str5 = (m + n * 50).ToString();
						this.cbInlay3b.Items.Add(new ComboBoxItem(str4, str5));
					}
				}
			}
			this.cbInlay4b.Items.Add(new ComboBoxItem("未开孔", "255"));
			this.cbInlay4b.Items.Add(new ComboBoxItem("无属性", "254"));
			for (int o = 0; o < 50; o++)
			{
				if (EquipEditor.xSocket[o].捞抚[0] != 0)
				{
					for (int p = 0; p < 5; p++)
					{
						string str6 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[o].捞抚, 64), " +", EquipEditor.xSocket[o].饭骇1[p].ToString());
						string str7 = (o + p * 50).ToString();
						this.cbInlay4b.Items.Add(new ComboBoxItem(str6, str7));
					}
				}
			}
			this.cbInlay5b.Items.Add(new ComboBoxItem("未开孔", "255"));
			this.cbInlay5b.Items.Add(new ComboBoxItem("无属性", "254"));
			for (int q = 0; q < 50; q++)
			{
				if (EquipEditor.xSocket[q].捞抚[0] != 0)
				{
					for (int r = 0; r < 5; r++)
					{
						string str8 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[q].捞抚, 64), " +", EquipEditor.xSocket[q].饭骇1[r].ToString());
						string str9 = (q + r * 50).ToString();
						this.cbInlay5b.Items.Add(new ComboBoxItem(str8, str9));
					}
				}
			}
			this.cbInlay1b.SelectedIndex = 0;
			this.cbInlay2b.SelectedIndex = 0;
			this.cbInlay3b.SelectedIndex = 0;
			this.cbInlay4b.SelectedIndex = 0;
			this.cbInlay5b.SelectedIndex = 0;
			this.cbInlay6b.Items.Clear();
			for (int s = 0; s < (int)Utils.YGS.Length; s++)
			{
				this.cbInlay6b.Items.Add(new ComboBoxItem(Utils.YGS[s], s.ToString()));
			}
			this.cbInlay6b.SelectedIndex = 0;
		}

		private void InitializeComponent()
		{
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(EquipProperty));
			this.cboEquipLevel = new ComboBox();
			this.cboEquipExt = new ComboBox();
			this.label31 = new Label();
			this.groupBox3 = new GroupBox();
			this.button4 = new Button();
			this.button1 = new Button();
			this.button3 = new Button();
			this.button2 = new Button();
			this.chkEquipZY6 = new CheckBox();
			this.chkEquipZY4 = new CheckBox();
			this.chkEquipZY2 = new CheckBox();
			this.chkEquipZY5 = new CheckBox();
			this.chkEquipZY3 = new CheckBox();
			this.chkEquipZY1 = new CheckBox();
			this.chkEquipXY = new CheckBox();
			this.chkEquipJN = new CheckBox();
			this.label30 = new Label();
			this.label1 = new Label();
			this.txtName = new MuEditor.TextBox();
			this.btnOK = new Button();
			this.btnCancel = new Button();
			this.label2 = new Label();
			this.txtEquipCodes = new MuEditor.TextBox();
			this.txtDurability = new MuEditor.TextBox();
			this.label4 = new Label();
			this.cbSetVal = new ComboBox();
			this.label5 = new Label();
			this.chk380 = new CheckBox();
			this.label3 = new Label();
			this.eee = new Label();
			this.cboPlusLevel = new ComboBox();
			this.cboPlusType = new ComboBox();
			this.gbXQ = new GroupBox();
			this.cbInlay6b = new ComboBox();
			this.label11 = new Label();
			this.label10 = new Label();
			this.label9 = new Label();
			this.label8 = new Label();
			this.label7 = new Label();
			this.label6 = new Label();
			this.cbInlay5b = new ComboBox();
			this.cbInlay4b = new ComboBox();
			this.cbInlay3b = new ComboBox();
			this.cbInlay2b = new ComboBox();
			this.cbInlay1b = new ComboBox();
			this.label12 = new Label();
			this.txtSN = new MuEditor.TextBox();
			this.groupBox3.SuspendLayout();
			this.gbXQ.SuspendLayout();
			base.SuspendLayout();
			this.cboEquipLevel.DropDownHeight = 206;
			this.cboEquipLevel.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboEquipLevel.FormattingEnabled = true;
			this.cboEquipLevel.IntegralHeight = false;
			ComboBox.ObjectCollection items = this.cboEquipLevel.Items;
			object[] objArray = new object[] { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
			items.AddRange(objArray);
			this.cboEquipLevel.Location = new Point(21, 78);
			this.cboEquipLevel.Name = "cboEquipLevel";
			this.cboEquipLevel.Size = new System.Drawing.Size(48, 20);
			this.cboEquipLevel.TabIndex = 30;
			this.cboEquipExt.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboEquipExt.FormattingEnabled = true;
			ComboBox.ObjectCollection objectCollections = this.cboEquipExt.Items;
			object[] objArray1 = new object[] { "0", "4", "8", "12", "16", "20", "24", "28" };
			objectCollections.AddRange(objArray1);
			this.cboEquipExt.Location = new Point(99, 77);
			this.cboEquipExt.Name = "cboEquipExt";
			this.cboEquipExt.Size = new System.Drawing.Size(49, 20);
			this.cboEquipExt.TabIndex = 29;
			this.label31.AutoSize = true;
			this.label31.Location = new Point(76, 80);
			this.label31.Name = "label31";
			this.label31.Size = new System.Drawing.Size(17, 12);
			this.label31.TabIndex = 28;
			this.label31.Text = "追";
			this.groupBox3.Controls.Add(this.button4);
			this.groupBox3.Controls.Add(this.button1);
			this.groupBox3.Controls.Add(this.button3);
			this.groupBox3.Controls.Add(this.button2);
			this.groupBox3.Controls.Add(this.chkEquipZY6);
			this.groupBox3.Controls.Add(this.chkEquipZY4);
			this.groupBox3.Controls.Add(this.chkEquipZY2);
			this.groupBox3.Controls.Add(this.chkEquipZY5);
			this.groupBox3.Controls.Add(this.chkEquipZY3);
			this.groupBox3.Controls.Add(this.chkEquipZY1);
			this.groupBox3.Location = new Point(6, 145);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(210, 105);
			this.groupBox3.TabIndex = 27;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "卓越属性";
			this.button4.Location = new Point(156, 76);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(45, 22);
			this.button4.TabIndex = 15;
			this.button4.Text = "道 具";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.button4_Click);
			this.button1.Location = new Point(107, 76);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(45, 22);
			this.button1.TabIndex = 14;
			this.button1.Text = "极 品";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.button1_Click);
			this.button3.Location = new Point(58, 76);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(45, 22);
			this.button3.TabIndex = 11;
			this.button3.Text = "清 空";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.button3_Click);
			this.button2.Location = new Point(9, 76);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(45, 22);
			this.button2.TabIndex = 10;
			this.button2.Text = "全 选";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.button2_Click);
			this.chkEquipZY6.AutoSize = true;
			this.chkEquipZY6.Location = new Point(112, 55);
			this.chkEquipZY6.Name = "chkEquipZY6";
			this.chkEquipZY6.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY6.TabIndex = 9;
			this.chkEquipZY6.Text = "无";
			this.chkEquipZY6.UseVisualStyleBackColor = true;
			this.chkEquipZY4.AutoSize = true;
			this.chkEquipZY4.Location = new Point(112, 34);
			this.chkEquipZY4.Name = "chkEquipZY4";
			this.chkEquipZY4.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY4.TabIndex = 8;
			this.chkEquipZY4.Text = "无";
			this.chkEquipZY4.UseVisualStyleBackColor = true;
			this.chkEquipZY2.AutoSize = true;
			this.chkEquipZY2.Location = new Point(112, 14);
			this.chkEquipZY2.Name = "chkEquipZY2";
			this.chkEquipZY2.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY2.TabIndex = 7;
			this.chkEquipZY2.Text = "无";
			this.chkEquipZY2.UseVisualStyleBackColor = true;
			this.chkEquipZY5.AutoSize = true;
			this.chkEquipZY5.Location = new Point(21, 55);
			this.chkEquipZY5.Name = "chkEquipZY5";
			this.chkEquipZY5.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY5.TabIndex = 6;
			this.chkEquipZY5.Text = "无";
			this.chkEquipZY5.UseVisualStyleBackColor = true;
			this.chkEquipZY3.AutoSize = true;
			this.chkEquipZY3.Location = new Point(21, 34);
			this.chkEquipZY3.Name = "chkEquipZY3";
			this.chkEquipZY3.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY3.TabIndex = 5;
			this.chkEquipZY3.Text = "无";
			this.chkEquipZY3.UseVisualStyleBackColor = true;
			this.chkEquipZY1.AutoSize = true;
			this.chkEquipZY1.Location = new Point(21, 14);
			this.chkEquipZY1.Name = "chkEquipZY1";
			this.chkEquipZY1.Size = new System.Drawing.Size(36, 16);
			this.chkEquipZY1.TabIndex = 4;
			this.chkEquipZY1.Text = "无";
			this.chkEquipZY1.UseVisualStyleBackColor = true;
			this.chkEquipXY.AutoSize = true;
			this.chkEquipXY.Location = new Point(96, 102);
			this.chkEquipXY.Name = "chkEquipXY";
			this.chkEquipXY.Size = new System.Drawing.Size(48, 16);
			this.chkEquipXY.TabIndex = 26;
			this.chkEquipXY.Text = "幸运";
			this.chkEquipXY.UseVisualStyleBackColor = true;
			this.chkEquipJN.AutoSize = true;
			this.chkEquipJN.Location = new Point(47, 102);
			this.chkEquipJN.Name = "chkEquipJN";
			this.chkEquipJN.Size = new System.Drawing.Size(48, 16);
			this.chkEquipJN.TabIndex = 25;
			this.chkEquipJN.Text = "技能";
			this.chkEquipJN.UseVisualStyleBackColor = true;
			this.label30.AutoSize = true;
			this.label30.Location = new Point(5, 81);
			this.label30.Name = "label30";
			this.label30.Size = new System.Drawing.Size(17, 12);
			this.label30.TabIndex = 24;
			this.label30.Text = "加";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(4, 5);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(65, 12);
			this.label1.TabIndex = 31;
			this.label1.Text = "物品名称：";
			this.txtName.IsOnlyNumber = false;
			this.txtName.Location = new Point(70, 2);
			this.txtName.Name = "txtName";
			this.txtName.ReadOnly = true;
			this.txtName.Size = new System.Drawing.Size(146, 21);
			this.txtName.TabIndex = 32;
			this.btnOK.Location = new Point(21, 420);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(66, 25);
			this.btnOK.TabIndex = 33;
			this.btnOK.Text = "确  定";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new EventHandler(this.btnOK_Click);
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new Point(127, 420);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(69, 25);
			this.btnCancel.TabIndex = 34;
			this.btnCancel.Text = "取 消";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new EventHandler(this.btnCancel_Click);
			this.label2.AutoSize = true;
			this.label2.Location = new Point(4, 32);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(65, 12);
			this.label2.TabIndex = 35;
			this.label2.Text = "物品代码：";
			this.txtEquipCodes.IsOnlyNumber = false;
			this.txtEquipCodes.Location = new Point(70, 27);
			this.txtEquipCodes.Name = "txtEquipCodes";
			this.txtEquipCodes.ReadOnly = true;
			this.txtEquipCodes.Size = new System.Drawing.Size(146, 21);
			this.txtEquipCodes.TabIndex = 36;
			this.txtDurability.IsOnlyNumber = true;
			this.txtDurability.Location = new Point(180, 76);
			this.txtDurability.Name = "txtDurability";
			this.txtDurability.Size = new System.Drawing.Size(36, 21);
			this.txtDurability.TabIndex = 38;
			this.txtDurability.Text = "255";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(153, 81);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(29, 12);
			this.label4.TabIndex = 37;
			this.label4.Text = "耐：";
			this.cbSetVal.DropDownHeight = 206;
			this.cbSetVal.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbSetVal.FormattingEnabled = true;
			this.cbSetVal.IntegralHeight = false;
			ComboBox.ObjectCollection items1 = this.cbSetVal.Items;
			object[] objArray2 = new object[] { "0", "5", "6", "9", "10" };
			items1.AddRange(objArray2);
			this.cbSetVal.Location = new Point(182, 99);
			this.cbSetVal.Name = "cbSetVal";
			this.cbSetVal.Size = new System.Drawing.Size(35, 20);
			this.cbSetVal.TabIndex = 45;
			this.label5.AutoSize = true;
			this.label5.Location = new Point(141, 103);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(41, 12);
			this.label5.TabIndex = 44;
			this.label5.Text = "套装值";
			this.chk380.AutoSize = true;
			this.chk380.Location = new Point(5, 102);
			this.chk380.Name = "chk380";
			this.chk380.Size = new System.Drawing.Size(42, 16);
			this.chk380.TabIndex = 46;
			this.chk380.Text = "380";
			this.chk380.UseVisualStyleBackColor = true;
			this.label3.AutoSize = true;
			this.label3.Location = new Point(146, 125);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(29, 12);
			this.label3.TabIndex = 50;
			this.label3.Text = "等级";
			this.eee.AutoSize = true;
			this.eee.Location = new Point(3, 125);
			this.eee.Name = "eee";
			this.eee.Size = new System.Drawing.Size(29, 12);
			this.eee.TabIndex = 49;
			this.eee.Text = "强化";
			this.cboPlusLevel.DropDownHeight = 206;
			this.cboPlusLevel.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboPlusLevel.FormattingEnabled = true;
			this.cboPlusLevel.IntegralHeight = false;
			ComboBox.ObjectCollection objectCollections1 = this.cboPlusLevel.Items;
			object[] objArray3 = new object[] { "+ 0", "+ 1", "+ 2", "+ 3", "+ 4", "+ 5", "+ 6", "+ 7", "+ 8", "+ 9", "+10", "+11", "+12", "+13" };
			objectCollections1.AddRange(objArray3);
			this.cboPlusLevel.Location = new Point(175, 122);
			this.cboPlusLevel.Name = "cboPlusLevel";
			this.cboPlusLevel.Size = new System.Drawing.Size(42, 20);
			this.cboPlusLevel.TabIndex = 48;
			this.cboPlusType.DropDownHeight = 206;
			this.cboPlusType.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboPlusType.FormattingEnabled = true;
			this.cboPlusType.IntegralHeight = false;
			this.cboPlusType.Location = new Point(33, 122);
			this.cboPlusType.Name = "cboPlusType";
			this.cboPlusType.Size = new System.Drawing.Size(111, 20);
			this.cboPlusType.TabIndex = 47;
			this.gbXQ.Controls.Add(this.cbInlay6b);
			this.gbXQ.Controls.Add(this.label11);
			this.gbXQ.Controls.Add(this.label10);
			this.gbXQ.Controls.Add(this.label9);
			this.gbXQ.Controls.Add(this.label8);
			this.gbXQ.Controls.Add(this.label7);
			this.gbXQ.Controls.Add(this.label6);
			this.gbXQ.Controls.Add(this.cbInlay5b);
			this.gbXQ.Controls.Add(this.cbInlay4b);
			this.gbXQ.Controls.Add(this.cbInlay3b);
			this.gbXQ.Controls.Add(this.cbInlay2b);
			this.gbXQ.Controls.Add(this.cbInlay1b);
			this.gbXQ.Location = new Point(5, 253);
			this.gbXQ.Name = "gbXQ";
			this.gbXQ.Size = new System.Drawing.Size(210, 162);
			this.gbXQ.TabIndex = 51;
			this.gbXQ.TabStop = false;
			this.gbXQ.Text = "镶嵌属性";
			this.cbInlay6b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay6b.FormattingEnabled = true;
			this.cbInlay6b.Location = new Point(56, 137);
			this.cbInlay6b.Name = "cbInlay6b";
			this.cbInlay6b.Size = new System.Drawing.Size(150, 20);
			this.cbInlay6b.TabIndex = 45;
			this.label11.AutoSize = true;
			this.label11.Location = new Point(3, 142);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(53, 12);
			this.label11.TabIndex = 44;
			this.label11.Text = "荧光属性";
			this.label10.AutoSize = true;
			this.label10.Location = new Point(3, 118);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(23, 12);
			this.label10.TabIndex = 43;
			this.label10.Text = "孔5";
			this.label9.AutoSize = true;
			this.label9.Location = new Point(3, 92);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(23, 12);
			this.label9.TabIndex = 42;
			this.label9.Text = "孔4";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(3, 68);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(23, 12);
			this.label8.TabIndex = 41;
			this.label8.Text = "孔3";
			this.label7.AutoSize = true;
			this.label7.Location = new Point(3, 42);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(23, 12);
			this.label7.TabIndex = 40;
			this.label7.Text = "孔2";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(3, 17);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(23, 12);
			this.label6.TabIndex = 39;
			this.label6.Text = "孔1";
			this.cbInlay5b.DropDownHeight = 206;
			this.cbInlay5b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay5b.FormattingEnabled = true;
			this.cbInlay5b.IntegralHeight = false;
			this.cbInlay5b.Location = new Point(26, 113);
			this.cbInlay5b.Name = "cbInlay5b";
			this.cbInlay5b.Size = new System.Drawing.Size(180, 20);
			this.cbInlay5b.TabIndex = 38;
			this.cbInlay4b.DropDownHeight = 206;
			this.cbInlay4b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay4b.FormattingEnabled = true;
			this.cbInlay4b.IntegralHeight = false;
			this.cbInlay4b.Location = new Point(26, 88);
			this.cbInlay4b.Name = "cbInlay4b";
			this.cbInlay4b.Size = new System.Drawing.Size(180, 20);
			this.cbInlay4b.TabIndex = 37;
			this.cbInlay3b.DropDownHeight = 206;
			this.cbInlay3b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay3b.FormattingEnabled = true;
			this.cbInlay3b.IntegralHeight = false;
			this.cbInlay3b.Location = new Point(26, 63);
			this.cbInlay3b.Name = "cbInlay3b";
			this.cbInlay3b.Size = new System.Drawing.Size(180, 20);
			this.cbInlay3b.TabIndex = 36;
			this.cbInlay2b.DropDownHeight = 206;
			this.cbInlay2b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay2b.FormattingEnabled = true;
			this.cbInlay2b.IntegralHeight = false;
			this.cbInlay2b.Location = new Point(26, 38);
			this.cbInlay2b.Name = "cbInlay2b";
			this.cbInlay2b.Size = new System.Drawing.Size(180, 20);
			this.cbInlay2b.TabIndex = 34;
			this.cbInlay1b.DropDownHeight = 206;
			this.cbInlay1b.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbInlay1b.FormattingEnabled = true;
			this.cbInlay1b.IntegralHeight = false;
			this.cbInlay1b.Location = new Point(26, 13);
			this.cbInlay1b.Name = "cbInlay1b";
			this.cbInlay1b.Size = new System.Drawing.Size(180, 20);
			this.cbInlay1b.TabIndex = 32;
			this.label12.AutoSize = true;
			this.label12.Location = new Point(3, 58);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(53, 12);
			this.label12.TabIndex = 52;
			this.label12.Text = "系列号：";
			this.txtSN.IsOnlyNumber = false;
			this.txtSN.Location = new Point(70, 52);
			this.txtSN.Name = "txtSN";
			this.txtSN.Size = new System.Drawing.Size(146, 21);
			this.txtSN.TabIndex = 53;
			base.AcceptButton = this.btnOK;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.CancelButton = this.btnCancel;
			base.ClientSize = new System.Drawing.Size(222, 448);
			base.ControlBox = false;
			base.Controls.Add(this.txtSN);
			base.Controls.Add(this.label12);
			base.Controls.Add(this.gbXQ);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.eee);
			base.Controls.Add(this.cboPlusLevel);
			base.Controls.Add(this.cboPlusType);
			base.Controls.Add(this.chk380);
			base.Controls.Add(this.cbSetVal);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.txtDurability);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.txtEquipCodes);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.btnCancel);
			base.Controls.Add(this.btnOK);
			base.Controls.Add(this.txtName);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.cboEquipLevel);
			base.Controls.Add(this.cboEquipExt);
			base.Controls.Add(this.label31);
			base.Controls.Add(this.groupBox3);
			base.Controls.Add(this.chkEquipXY);
			base.Controls.Add(this.chkEquipJN);
			base.Controls.Add(this.label30);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.Icon = (System.Drawing.Icon)componentResourceManager.GetObject("$this.Icon");
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "EquipProperty";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterParent;
			this.Text = "装备属性";
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			this.gbXQ.ResumeLayout(false);
			this.gbXQ.PerformLayout();
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		[DllImport("USER32.dll", CharSet=CharSet.None, EntryPoint="SendMessageA", ExactSpelling=false)]
		private static extern int SendMessage(IntPtr hwnd, int wMsg, IntPtr wParam, string lParam);

		public void SetUIbyCob(EquipItem item)
		{
			this.gbXQ.Enabled = Utils.GetQX(item);
			this.chkEquipXY.Enabled = (item.Type < 0 ? false : item.Type <= 11);
			this.cbSetVal.Enabled = this.chkEquipXY.Enabled;
			this.chk380.Enabled = Utils.Get380(item);
			this.chk380.Checked = this.chk380.Enabled;
			this.chkEquipJN.Enabled = Utils.GetJN(item);
			if (item.Type >= 0 && item.Type <= 5)
			{
				this.setZY(1);
				if (!item.IsFZ)
				{
					Utils.GetPlusType(this.cboPlusType, 1);
				}
				else
				{
					Utils.GetPlusType(this.cboPlusType, 3);
				}
			}
			else if (item.Type < 6 || item.Type > 11)
			{
				Utils.GetPlusType(this.cboPlusType, 0);
			}
			else
			{
				this.setZY(2);
				Utils.GetPlusType(this.cboPlusType, 2);
			}
			this.Init_EquipEditor();
			byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
			byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
			byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
			switch (item.Type)
			{
				case 12:
				{
					this.cbInlay6b.Items.Clear();
					if (itemKindA != 8)
					{
						for (int i = 0; i < (int)Utils.YGS.Length; i++)
						{
							this.cbInlay6b.Items.Add(new ComboBoxItem(Utils.YGS[i], i.ToString()));
						}
					}
					else
					{
						if (itemKindB == 0)
						{
							this.cbInlay1b.Items.Clear();
							this.cbInlay1b.Items.Add(new ComboBoxItem("无属性", "0"));
							this.cbInlay2b.Items.Clear();
							this.cbInlay2b.Items.Add(new ComboBoxItem("无属性", "0"));
							this.cbInlay3b.Items.Clear();
							this.cbInlay3b.Items.Add(new ComboBoxItem("无属性", "0"));
							this.cbInlay4b.Items.Clear();
							this.cbInlay4b.Items.Add(new ComboBoxItem("无属性", "0"));
							this.cbInlay5b.Items.Clear();
							this.cbInlay5b.Items.Add(new ComboBoxItem("无属性", "0"));
						}
						else if (itemKindB == 43)
						{
							this.cbInlay1b.Items.Clear();
							this.cbInlay1b.Items.Add(new ComboBoxItem("未开孔", "255"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("愤怒的元素之魂", "254"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("愤怒的元素之魂(镶嵌)", "0"));
							this.cbInlay2b.Items.Clear();
							this.cbInlay2b.Items.Add(new ComboBoxItem("未开孔", "255"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("庇护的元素之魂", "254"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("庇护的元素之魂(镶嵌)", "1"));
							this.cbInlay3b.Items.Clear();
							this.cbInlay3b.Items.Add(new ComboBoxItem("未开孔", "255"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("高贵的元素之魂", "254"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("高贵的元素之魂(镶嵌)", "2"));
							this.cbInlay4b.Items.Clear();
							this.cbInlay4b.Items.Add(new ComboBoxItem("未开孔", "255"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("神圣的元素之魂", "254"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("神圣的元素之魂(镶嵌)", "3"));
							this.cbInlay5b.Items.Clear();
							this.cbInlay5b.Items.Add(new ComboBoxItem("未开孔", "255"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("狂喜的元素之魂", "254"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("狂喜的元素之魂(镶嵌)", "4"));
						}
						else if (itemKindB == 44)
						{
							this.cbInlay1b.Items.Clear();
							this.cbInlay1b.Items.Add(new ComboBoxItem("无属性", "255"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +1", "17"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +2", "33"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +3", "49"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +4", "65"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +5", "81"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +6", "97"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +7", "113"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +8", "129"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +9", "145"));
							this.cbInlay1b.Items.Add(new ComboBoxItem("1阶属性 +10", "161"));
							this.cbInlay2b.Items.Clear();
							this.cbInlay2b.Items.Add(new ComboBoxItem("无属性", "255"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +1", "17"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +2", "33"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +3", "49"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +4", "65"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +5", "81"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +6", "97"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +7", "113"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +8", "129"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +9", "145"));
							this.cbInlay2b.Items.Add(new ComboBoxItem("2阶属性 +10", "161"));
							this.cbInlay3b.Items.Clear();
							this.cbInlay3b.Items.Add(new ComboBoxItem("无属性", "255"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +1", "17"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +2", "33"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +3", "49"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +4", "65"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +5", "81"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +6", "97"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +7", "113"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +8", "129"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +9", "145"));
							this.cbInlay3b.Items.Add(new ComboBoxItem("3阶属性 +10", "161"));
							this.cbInlay4b.Items.Clear();
							this.cbInlay4b.Items.Add(new ComboBoxItem("无属性", "255"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +1", "17"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +2", "33"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +3", "49"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +4", "65"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +5", "81"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +6", "97"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +7", "113"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +8", "129"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +9", "145"));
							this.cbInlay4b.Items.Add(new ComboBoxItem("4阶属性 +10", "161"));
							this.cbInlay5b.Items.Clear();
							this.cbInlay5b.Items.Add(new ComboBoxItem("无属性", "255"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +1", "17"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +2", "33"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +3", "49"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +4", "65"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +5", "81"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +6", "97"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +7", "113"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +8", "129"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +9", "145"));
							this.cbInlay5b.Items.Add(new ComboBoxItem("5阶属性 +10", "161"));
						}
						this.cbInlay1b.SelectedIndex = 0;
						this.cbInlay2b.SelectedIndex = 0;
						this.cbInlay3b.SelectedIndex = 0;
						this.cbInlay4b.SelectedIndex = 0;
						this.cbInlay5b.SelectedIndex = 0;
						for (int j = 0; j < (int)Utils.YSS.Length; j++)
						{
							this.cbInlay6b.Items.Add(new ComboBoxItem(Utils.YSS[j], j.ToString()));
						}
					}
					this.cbInlay6b.SelectedIndex = 0;
					if (itemCategory != 1)
					{
						this.setZY(0);
						this.chkEquipXY.Enabled = false;
						break;
					}
					else if (itemKindB == 23)
					{
						this.setZY(0);
						this.chkEquipXY.Enabled = true;
						break;
					}
					else if (itemKindB == 24 || itemKindB == 27)
					{
						this.setZY(3);
						this.chkEquipXY.Enabled = true;
						break;
					}
					else if (itemKindB == 25 || itemKindB == 28 || itemKindB == 60)
					{
						this.setZY(4);
						this.chkEquipXY.Enabled = true;
						break;
					}
					else
					{
						this.setZY(0);
						this.chkEquipXY.Enabled = false;
						break;
					}
				}
				case 13:
				{
					if (itemCategory != 1)
					{
						if (item.Code != 37 || itemKindB != 46)
						{
							this.setZY(0);
							this.cbSetVal.Enabled = false;
							break;
						}
						else
						{
							this.setZY(6);
							this.chkEquipJN.Enabled = true;
							break;
						}
					}
					else if (itemKindB == 26)
					{
						this.setZY(5);
						this.chkEquipXY.Enabled = true;
						this.cbSetVal.Enabled = false;
						break;
					}
					else if (itemKindB == 29 || itemKindB == 30)
					{
						this.setZY(1);
						this.cbSetVal.Enabled = true;
						break;
					}
					else if (itemKindB != 31)
					{
						this.setZY(0);
						this.cbSetVal.Enabled = false;
						break;
					}
					else
					{
						this.setZY(2);
						this.cbSetVal.Enabled = true;
						break;
					}
				}
				case 14:
				case 15:
				{
					this.setZY(0);
					break;
				}
			}
			this.chkEquipZY1.Enabled = this.chkEquipZY1.Text != "无";
			this.chkEquipZY2.Enabled = this.chkEquipZY2.Text != "无";
			this.chkEquipZY3.Enabled = this.chkEquipZY3.Text != "无";
			this.chkEquipZY4.Enabled = this.chkEquipZY4.Text != "无";
			this.chkEquipZY5.Enabled = this.chkEquipZY5.Text != "无";
			this.chkEquipZY6.Enabled = this.chkEquipZY6.Text != "无";
		}

		private void setZY(int type)
		{
			if (type == 0)
			{
				this.chkEquipZY1.Text = "无";
				this.chkEquipZY2.Text = "无";
				this.chkEquipZY3.Text = "无";
				this.chkEquipZY4.Text = "无";
				this.chkEquipZY5.Text = "无";
				this.chkEquipZY6.Text = "无";
				return;
			}
			if (type == 1)
			{
				this.chkEquipZY1.Text = "+魔法值/8";
				this.chkEquipZY2.Text = "+生命值/8";
				this.chkEquipZY3.Text = "+速度+7";
				this.chkEquipZY4.Text = "+2%攻击";
				this.chkEquipZY5.Text = "等级/20攻击";
				this.chkEquipZY6.Text = "卓越一击";
				return;
			}
			if (type == 2)
			{
				this.chkEquipZY1.Text = "金钱 +30%";
				this.chkEquipZY2.Text = "防御 +10%";
				this.chkEquipZY3.Text = "反伤";
				this.chkEquipZY4.Text = "减伤";
				this.chkEquipZY5.Text = "魔法 +4%";
				this.chkEquipZY6.Text = "生命 +4%";
				return;
			}
			if (type == 3)
			{
				this.chkEquipZY1.Text = "加生";
				this.chkEquipZY2.Text = "加魔";
				this.chkEquipZY3.Text = "无视";
				this.chkEquipZY4.Text = "技能最大值";
				this.chkEquipZY5.Text = "加速";
				this.chkEquipZY6.Text = "追/回";
				return;
			}
			if (type == 4)
			{
				this.chkEquipZY1.Text = "无视";
				this.chkEquipZY2.Text = "反弹攻击";
				this.chkEquipZY3.Text = "恢复生命";
				this.chkEquipZY4.Text = "恢复魔法";
				this.chkEquipZY5.Text = "追/回";
				this.chkEquipZY6.Text = "追/回";
				return;
			}
			if (type == 5)
			{
				this.chkEquipZY1.Text = "生命 +50";
				this.chkEquipZY2.Text = "魔法 +50";
				this.chkEquipZY3.Text = "无视";
				this.chkEquipZY4.Text = "追加统率";
				this.chkEquipZY5.Text = "无";
				this.chkEquipZY6.Text = "无";
				return;
			}
			if (type == 6)
			{
				this.chkEquipZY1.Text = "黑狼";
				this.chkEquipZY2.Text = "青狼";
				this.chkEquipZY3.Text = "金狼";
				this.chkEquipZY4.Text = "无";
				this.chkEquipZY5.Text = "无";
				this.chkEquipZY6.Text = "无";
			}
		}

		public void updateData(EquipItem item)
		{
			object selectedIndex;
			byte num;
			byte selectedIndex1;
			item.SN = Convert.ToInt32(this.txtSN.Text.Replace(" ", ""));
			item.Level = (byte)this.cboEquipLevel.SelectedIndex;
			item.Ext = this.cboEquipExt.SelectedIndex;
			item.PlusType = (byte)this.cboPlusType.SelectedIndex;
			EquipItem equipItem = item;
			if (this.cboPlusType.SelectedIndex <= 0)
			{
				selectedIndex = null;
			}
			else
			{
				selectedIndex = this.cboPlusLevel.SelectedIndex;
			}
			equipItem.PlusLevel = (byte)selectedIndex;
			item.JN = (!this.chkEquipJN.Checked ? false : this.chkEquipJN.Enabled);
			item.XY = (!this.chkEquipXY.Checked ? false : this.chkEquipXY.Enabled);
			item.ZY1 = (!this.chkEquipZY1.Checked ? false : this.chkEquipZY1.Enabled);
			item.ZY2 = (!this.chkEquipZY2.Checked ? false : this.chkEquipZY2.Enabled);
			item.ZY3 = (!this.chkEquipZY3.Checked ? false : this.chkEquipZY3.Enabled);
			item.ZY4 = (!this.chkEquipZY4.Checked ? false : this.chkEquipZY4.Enabled);
			item.ZY5 = (!this.chkEquipZY5.Checked ? false : this.chkEquipZY5.Enabled);
			item.ZY6 = (!this.chkEquipZY6.Checked ? false : this.chkEquipZY6.Enabled);
			item.Is380 = (!this.chk380.Checked ? false : this.chk380.Enabled);
			item.IsSet = (this.cbSetVal.SelectedIndex <= 0 ? false : this.cbSetVal.Enabled);
			EquipItem equipItem1 = item;
			if (this.cbSetVal.Enabled)
			{
				num = Convert.ToByte(this.cbSetVal.SelectedItem);
			}
			else
			{
				num = 0;
			}
			equipItem1.SetVal = num;
			item.Durability = Convert.ToByte(this.txtDurability.Text.Replace(" ", ""));
			if (this.gbXQ.Enabled)
			{
				item.PlusType = 0;
				item.PlusLevel = 0;
				byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
				byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
				byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
				if (itemKindA == 8)
				{
					ComboBoxItem selectedItem = (ComboBoxItem)this.cbInlay1b.SelectedItem;
					item.XQ1 = Convert.ToByte(selectedItem.Value);
					ComboBoxItem comboBoxItem = (ComboBoxItem)this.cbInlay2b.SelectedItem;
					item.XQ2 = Convert.ToByte(comboBoxItem.Value);
					ComboBoxItem selectedItem1 = (ComboBoxItem)this.cbInlay3b.SelectedItem;
					item.XQ3 = Convert.ToByte(selectedItem1.Value);
					ComboBoxItem comboBoxItem1 = (ComboBoxItem)this.cbInlay4b.SelectedItem;
					item.XQ4 = Convert.ToByte(comboBoxItem1.Value);
					ComboBoxItem selectedItem2 = (ComboBoxItem)this.cbInlay5b.SelectedItem;
					item.XQ5 = Convert.ToByte(selectedItem2.Value);
					item.YG = (byte)(this.cbInlay6b.SelectedIndex + 17);
					return;
				}
				ComboBoxItem comboBoxItem2 = (ComboBoxItem)this.cbInlay1b.SelectedItem;
				item.XQ1 = Convert.ToByte(comboBoxItem2.Value);
				ComboBoxItem selectedItem3 = (ComboBoxItem)this.cbInlay2b.SelectedItem;
				item.XQ2 = Convert.ToByte(selectedItem3.Value);
				ComboBoxItem comboBoxItem3 = (ComboBoxItem)this.cbInlay3b.SelectedItem;
				item.XQ3 = Convert.ToByte(comboBoxItem3.Value);
				ComboBoxItem selectedItem4 = (ComboBoxItem)this.cbInlay4b.SelectedItem;
				item.XQ4 = Convert.ToByte(selectedItem4.Value);
				ComboBoxItem comboBoxItem4 = (ComboBoxItem)this.cbInlay5b.SelectedItem;
				item.XQ5 = Convert.ToByte(comboBoxItem4.Value);
				EquipItem equipItem2 = item;
				if (this.cbInlay6b.SelectedIndex > 0)
				{
					selectedIndex1 = (byte)(this.cbInlay6b.SelectedIndex - 1);
				}
				else
				{
					selectedIndex1 = 255;
				}
				equipItem2.YG = selectedIndex1;
			}
		}

		public void updateUI(EquipItem item)
		{
			this.SetUIbyCob(item);
			this.txtName.Text = item.Name;
			this.txtEquipCodes.Text = item.ToString();
			this.txtSN.Text = item.SN.ToString();
			this.cboEquipLevel.SelectedIndex = item.Level;
			this.cboEquipExt.SelectedIndex = item.Ext;
			if (item.PlusType < this.cboPlusType.Items.Count)
			{
				this.cboPlusType.SelectedIndex = item.PlusType;
			}
			if (item.PlusLevel < this.cboPlusLevel.Items.Count)
			{
				this.cboPlusLevel.SelectedIndex = item.PlusLevel;
			}
			this.chkEquipJN.Checked = item.JN;
			this.chkEquipXY.Checked = item.XY;
			this.chkEquipZY1.Checked = item.ZY1;
			this.chkEquipZY2.Checked = item.ZY2;
			this.chkEquipZY3.Checked = item.ZY3;
			this.chkEquipZY4.Checked = item.ZY4;
			this.chkEquipZY5.Checked = item.ZY5;
			this.chkEquipZY6.Checked = item.ZY6;
			this.cbSetVal.SelectedItem = string.Concat(item.SetVal);
			this.chk380.Checked = item.Is380;
			this.txtDurability.Text = Convert.ToString(item.Durability);
			if (this.gbXQ.Enabled)
			{
				this.cboPlusType.SelectedIndex = 0;
				this.cboPlusLevel.SelectedIndex = 0;
				byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
				byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
				byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
				if (itemKindA == 8)
				{
					if (itemKindB == 0)
					{
						if (item.XQ1 == 255)
						{
							this.cbInlay1b.SelectedIndex = 0;
						}
						else if (item.XQ1 == 0)
						{
							this.cbInlay1b.SelectedIndex = 0;
						}
						if (item.XQ2 == 255)
						{
							this.cbInlay2b.SelectedIndex = 0;
						}
						else if (item.XQ2 == 0)
						{
							this.cbInlay2b.SelectedIndex = 0;
						}
						if (item.XQ3 == 255)
						{
							this.cbInlay3b.SelectedIndex = 0;
						}
						else if (item.XQ3 == 0)
						{
							this.cbInlay3b.SelectedIndex = 0;
						}
						if (item.XQ4 == 255)
						{
							this.cbInlay4b.SelectedIndex = 0;
						}
						else if (item.XQ4 == 0)
						{
							this.cbInlay4b.SelectedIndex = 0;
						}
						if (item.XQ5 == 255)
						{
							this.cbInlay5b.SelectedIndex = 0;
						}
						else if (item.XQ5 == 0)
						{
							this.cbInlay5b.SelectedIndex = 0;
						}
					}
					else if (itemKindB == 43)
					{
						if (item.XQ1 == 255)
						{
							this.cbInlay1b.SelectedIndex = 0;
						}
						else if (item.XQ1 != 254)
						{
							this.cbInlay1b.SelectedIndex = 2;
						}
						else
						{
							this.cbInlay1b.SelectedIndex = 1;
						}
						if (item.XQ2 == 255)
						{
							this.cbInlay2b.SelectedIndex = 0;
						}
						else if (item.XQ2 != 254)
						{
							this.cbInlay2b.SelectedIndex = 2;
						}
						else
						{
							this.cbInlay2b.SelectedIndex = 1;
						}
						if (item.XQ3 == 255)
						{
							this.cbInlay3b.SelectedIndex = 0;
						}
						else if (item.XQ3 != 254)
						{
							this.cbInlay3b.SelectedIndex = 2;
						}
						else
						{
							this.cbInlay3b.SelectedIndex = 1;
						}
						if (item.XQ4 == 255)
						{
							this.cbInlay4b.SelectedIndex = 0;
						}
						else if (item.XQ4 != 254)
						{
							this.cbInlay4b.SelectedIndex = 2;
						}
						else
						{
							this.cbInlay4b.SelectedIndex = 1;
						}
						if (item.XQ5 == 255)
						{
							this.cbInlay5b.SelectedIndex = 0;
						}
						else if (item.XQ5 != 254)
						{
							this.cbInlay5b.SelectedIndex = 2;
						}
						else
						{
							this.cbInlay5b.SelectedIndex = 1;
						}
					}
					else if (itemKindB == 44)
					{
						if (item.XQ1 == 255)
						{
							this.cbInlay1b.SelectedIndex = 0;
						}
						else if (item.XQ1 == 17)
						{
							this.cbInlay1b.SelectedIndex = 1;
						}
						else if (item.XQ1 == 33)
						{
							this.cbInlay1b.SelectedIndex = 2;
						}
						else if (item.XQ1 == 49)
						{
							this.cbInlay1b.SelectedIndex = 3;
						}
						else if (item.XQ1 == 65)
						{
							this.cbInlay1b.SelectedIndex = 4;
						}
						else if (item.XQ1 == 81)
						{
							this.cbInlay1b.SelectedIndex = 5;
						}
						else if (item.XQ1 == 97)
						{
							this.cbInlay1b.SelectedIndex = 6;
						}
						else if (item.XQ1 == 113)
						{
							this.cbInlay1b.SelectedIndex = 7;
						}
						else if (item.XQ1 == 129)
						{
							this.cbInlay1b.SelectedIndex = 8;
						}
						else if (item.XQ1 != 145)
						{
							this.cbInlay1b.SelectedIndex = 10;
						}
						else
						{
							this.cbInlay1b.SelectedIndex = 9;
						}
						if (item.XQ2 == 255)
						{
							this.cbInlay2b.SelectedIndex = 0;
						}
						else if (item.XQ2 == 17)
						{
							this.cbInlay2b.SelectedIndex = 1;
						}
						else if (item.XQ2 == 33)
						{
							this.cbInlay2b.SelectedIndex = 2;
						}
						else if (item.XQ2 == 49)
						{
							this.cbInlay2b.SelectedIndex = 3;
						}
						else if (item.XQ2 == 65)
						{
							this.cbInlay2b.SelectedIndex = 4;
						}
						else if (item.XQ2 == 81)
						{
							this.cbInlay2b.SelectedIndex = 5;
						}
						else if (item.XQ2 == 97)
						{
							this.cbInlay2b.SelectedIndex = 6;
						}
						else if (item.XQ2 == 113)
						{
							this.cbInlay2b.SelectedIndex = 7;
						}
						else if (item.XQ2 == 129)
						{
							this.cbInlay2b.SelectedIndex = 8;
						}
						else if (item.XQ2 != 145)
						{
							this.cbInlay2b.SelectedIndex = 10;
						}
						else
						{
							this.cbInlay2b.SelectedIndex = 9;
						}
						if (item.XQ3 == 255)
						{
							this.cbInlay3b.SelectedIndex = 0;
						}
						else if (item.XQ3 == 17)
						{
							this.cbInlay3b.SelectedIndex = 1;
						}
						else if (item.XQ3 == 33)
						{
							this.cbInlay3b.SelectedIndex = 2;
						}
						else if (item.XQ3 == 49)
						{
							this.cbInlay3b.SelectedIndex = 3;
						}
						else if (item.XQ3 == 65)
						{
							this.cbInlay3b.SelectedIndex = 4;
						}
						else if (item.XQ3 == 81)
						{
							this.cbInlay3b.SelectedIndex = 5;
						}
						else if (item.XQ3 == 97)
						{
							this.cbInlay3b.SelectedIndex = 6;
						}
						else if (item.XQ3 == 113)
						{
							this.cbInlay3b.SelectedIndex = 7;
						}
						else if (item.XQ3 == 129)
						{
							this.cbInlay3b.SelectedIndex = 8;
						}
						else if (item.XQ3 != 145)
						{
							this.cbInlay3b.SelectedIndex = 10;
						}
						else
						{
							this.cbInlay3b.SelectedIndex = 9;
						}
						if (item.XQ4 == 255)
						{
							this.cbInlay4b.SelectedIndex = 0;
						}
						else if (item.XQ4 == 17)
						{
							this.cbInlay4b.SelectedIndex = 1;
						}
						else if (item.XQ4 == 33)
						{
							this.cbInlay4b.SelectedIndex = 2;
						}
						else if (item.XQ4 == 49)
						{
							this.cbInlay4b.SelectedIndex = 3;
						}
						else if (item.XQ4 == 65)
						{
							this.cbInlay4b.SelectedIndex = 4;
						}
						else if (item.XQ4 == 81)
						{
							this.cbInlay4b.SelectedIndex = 5;
						}
						else if (item.XQ4 == 97)
						{
							this.cbInlay4b.SelectedIndex = 6;
						}
						else if (item.XQ4 == 113)
						{
							this.cbInlay4b.SelectedIndex = 7;
						}
						else if (item.XQ4 == 129)
						{
							this.cbInlay4b.SelectedIndex = 8;
						}
						else if (item.XQ4 != 145)
						{
							this.cbInlay4b.SelectedIndex = 10;
						}
						else
						{
							this.cbInlay4b.SelectedIndex = 9;
						}
						if (item.XQ5 == 255)
						{
							this.cbInlay5b.SelectedIndex = 0;
						}
						else if (item.XQ5 == 17)
						{
							this.cbInlay5b.SelectedIndex = 1;
						}
						else if (item.XQ5 == 33)
						{
							this.cbInlay5b.SelectedIndex = 2;
						}
						else if (item.XQ5 == 49)
						{
							this.cbInlay5b.SelectedIndex = 3;
						}
						else if (item.XQ5 == 65)
						{
							this.cbInlay5b.SelectedIndex = 4;
						}
						else if (item.XQ5 == 81)
						{
							this.cbInlay5b.SelectedIndex = 5;
						}
						else if (item.XQ5 == 97)
						{
							this.cbInlay5b.SelectedIndex = 6;
						}
						else if (item.XQ5 == 113)
						{
							this.cbInlay5b.SelectedIndex = 7;
						}
						else if (item.XQ5 == 129)
						{
							this.cbInlay5b.SelectedIndex = 8;
						}
						else if (item.XQ5 != 145)
						{
							this.cbInlay5b.SelectedIndex = 10;
						}
						else
						{
							this.cbInlay5b.SelectedIndex = 9;
						}
					}
					Trace.WriteLine(string.Concat("item.YG : ", item.YG - 17));
					if (item.YG < 0 || item.YG - 17 >= (int)Utils.YSS.Length)
					{
						this.cbInlay6b.SelectedIndex = 0;
						return;
					}
					this.cbInlay6b.SelectedIndex = item.YG - 17;
					return;
				}
				if (item.XQ1 == 255)
				{
					this.cbInlay1b.SelectedIndex = 0;
				}
				else if (item.XQ1 != 254)
				{
					int xQ1 = item.XQ1 % 50;
					int num = (item.XQ1 - xQ1) / 50;
					string str = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ1].捞抚, 64), " +", EquipEditor.xSocket[xQ1].饭骇1[num].ToString());
					this.cbInlay1b.SelectedIndex = EquipProperty.SendMessage(this.cbInlay1b.Handle, 332, IntPtr.Zero, str);
				}
				else
				{
					this.cbInlay1b.SelectedIndex = 1;
				}
				if (item.XQ2 == 255)
				{
					this.cbInlay2b.SelectedIndex = 0;
				}
				else if (item.XQ2 != 254)
				{
					int xQ2 = item.XQ2 % 50;
					int xQ21 = (item.XQ2 - xQ2) / 50;
					string str1 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ2].捞抚, 64), " +", EquipEditor.xSocket[xQ2].饭骇1[xQ21].ToString());
					this.cbInlay2b.SelectedIndex = EquipProperty.SendMessage(this.cbInlay2b.Handle, 332, IntPtr.Zero, str1);
				}
				else
				{
					this.cbInlay2b.SelectedIndex = 1;
				}
				if (item.XQ3 == 255)
				{
					this.cbInlay3b.SelectedIndex = 0;
				}
				else if (item.XQ3 != 254)
				{
					int xQ3 = item.XQ3 % 50;
					int xQ31 = (item.XQ3 - xQ3) / 50;
					string str2 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ3].捞抚, 64), " +", EquipEditor.xSocket[xQ3].饭骇1[xQ31].ToString());
					this.cbInlay3b.SelectedIndex = EquipProperty.SendMessage(this.cbInlay3b.Handle, 332, IntPtr.Zero, str2);
				}
				else
				{
					this.cbInlay3b.SelectedIndex = 1;
				}
				if (item.XQ4 == 255)
				{
					this.cbInlay4b.SelectedIndex = 0;
				}
				else if (item.XQ4 != 254)
				{
					int xQ4 = item.XQ4 % 50;
					int xQ41 = (item.XQ4 - xQ4) / 50;
					string str3 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ4].捞抚, 64), " +", EquipEditor.xSocket[xQ4].饭骇1[xQ41].ToString());
					this.cbInlay4b.SelectedIndex = EquipProperty.SendMessage(this.cbInlay4b.Handle, 332, IntPtr.Zero, str3);
				}
				else
				{
					this.cbInlay4b.SelectedIndex = 1;
				}
				if (item.XQ5 == 255)
				{
					this.cbInlay5b.SelectedIndex = 0;
				}
				else if (item.XQ5 != 254)
				{
					int xQ5 = item.XQ5 % 50;
					int xQ51 = (item.XQ5 - xQ5) / 50;
					string str4 = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ5].捞抚, 64), " +", EquipEditor.xSocket[xQ5].饭骇1[xQ51].ToString());
					this.cbInlay5b.SelectedIndex = EquipProperty.SendMessage(this.cbInlay5b.Handle, 332, IntPtr.Zero, str4);
				}
				else
				{
					this.cbInlay5b.SelectedIndex = 1;
				}
				if (item.YG >= 0 && item.YG < (int)Utils.YGS.Length - 1)
				{
					this.cbInlay6b.SelectedIndex = item.YG + 1;
					return;
				}
				this.cbInlay6b.SelectedIndex = 0;
			}
		}
	}
}