using System;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace MuEditor
{
	public class EquipEditor : ucBase
	{
		private const int CB_FINDSTRING = 332;

		private IContainer components;

		private ComboBox cboEquipLevel;

		private ComboBox cboEquipExt;

		private Label label31;

		private ComboBox cboEquipName;

		private ComboBox cboEquipType;

		private GroupBox groupBox3;

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

		private Label label29;

		private Label label28;

		private Label label1;

		private MuEditor.TextBox txtDurability;

		private CheckBox chk380;

		private ComboBox cboPlusType;

		private ComboBox cboPlusLevel;

		private Label eee;

		private Label label3;

		private Button button4;

		private Button button1;

		private Button button3;

		private MuEditor.TextBox AddNums;

		private Label label2;

		private CheckBox chkAllPart;

		private MuEditor.TextBox txtCode;

		private GroupBox gbXQ;

		private ComboBox cbInlay1b;

		private ComboBox cbInlay3b;

		private ComboBox cbInlay2b;

		private ComboBox cbInlay5b;

		private ComboBox cbInlay4b;

		private ComboBox cbZhiye;

		private Label label4;

		private Label label5;

		private ComboBox cbSetVal;

		private Label label11;

		private Label label10;

		private Label label9;

		private Label label8;

		private Label label7;

		private Label label6;

		private ComboBox cbInlay6b;

		private ArrayList itemTypes = new ArrayList();

		private EquipItem editItem;

		private byte defDurability = 255;

		public static ITEM_ATTRIBUTE[] xItem;

		public static ITEM_SOCKETITEM[] xSocket;

		public int AddNum
		{
			get
			{
				return Convert.ToInt32(this.AddNums.Text);
			}
		}

		public bool AllPart
		{
			get
			{
				switch (this.cboEquipType.SelectedIndex)
				{
					case 7:
					case 8:
					case 9:
					case 10:
					case 11:
					{
						return this.chkAllPart.Checked;
					}
				}
				return false;
			}
			set
			{
				this.chkAllPart.Checked = value;
			}
		}

		public byte DefaultDurability
		{
			get
			{
				return this.defDurability;
			}
			set
			{
				this.defDurability = value;
			}
		}

		public EquipItem EditItem
		{
			get
			{
				return this.editItem;
			}
		}

		static EquipEditor()
		{
		}

		public EquipEditor()
		{
			this.InitializeComponent();
			string str = "Data\\Item.bmd";
			if (!File.Exists(str))
			{
				str = string.Concat("MuEdit\\bin\\Release\\", str);
			}
			EquipEditor.xItem = (new ItemClass(str)).ItemAttribute;
			str = "Data\\SocketItem.bmd";
			if (!File.Exists(str))
			{
				str = string.Concat("MuEdit\\bin\\Release\\", str);
			}
			EquipEditor.xSocket = (new SocketItemClass(str)).cSocket;
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

		private void cboEquipName_KeyUp(object sender, KeyEventArgs e)
		{
			this.cboEquipName.DroppedDown = true;
		}

		private void cboEquipName_SelectedIndexChanged(object sender, EventArgs e)
		{
			string text = this.cboEquipName.Text;
			if (text == null || "" == text.Trim())
			{
				return;
			}
			EquipItem item = EquipImageCache.Instance.getItem(this.cboEquipName.Text);
			if (item != null)
			{
				if (this.editItem == null)
				{
					this.editItem = new EquipItem();
				}
				this.editItem.assign(item);
			}
			this.SetUIbyCob(item);
			this.cboPlusType.SelectedIndex = 0;
		}

		private void cboEquipType_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				EquipItemType selectedItem = (EquipItemType)this.cboEquipType.SelectedItem;
				selectedItem.ItemNames = new ArrayList();
				this.loadItemNamesByType(selectedItem.ItemNames, this.cboEquipType.SelectedIndex, this.cbZhiye.SelectedIndex);
				this.cboEquipName.Items.Clear();
				foreach (string itemName in selectedItem.ItemNames)
				{
					this.cboEquipName.Items.Add(itemName);
				}
				if ((this.cbZhiye.SelectedIndex != 4 || this.cboEquipType.SelectedIndex != 2) && (this.cbZhiye.SelectedIndex != 7 || this.cboEquipType.SelectedIndex != 5) && (this.cbZhiye.SelectedIndex != 7 || this.cboEquipType.SelectedIndex != 1))
				{
					this.cboEquipName.SelectedIndex = 0;
				}
				EquipItem item = EquipImageCache.Instance.getItem(this.cboEquipName.Text);
				if (item != null)
				{
					if (this.editItem == null)
					{
						this.editItem = new EquipItem();
					}
					this.editItem.assign(item);
				}
				this.SetUIbyCob(item);
				this.cboPlusType.SelectedIndex = 0;
				this.cboPlusLevel.SelectedIndex = 0;
			}
			catch (Exception exception1)
			{
				
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

		private void EquipEditor_Load(object sender, EventArgs e)
		{
			this.txtDurability.Text = Convert.ToString(this.defDurability);
		}

		private void Init_EquipEditor()
		{
			this.cbInlay1b.Items.Clear();
			this.cbInlay2b.Items.Clear();
			this.cbInlay3b.Items.Clear();
			this.cbInlay4b.Items.Clear();
			this.cbInlay5b.Items.Clear();
            this.cbInlay1b.Items.Add(new ComboBoxItem("No sockets", "255"));
            this.cbInlay1b.Items.Add(new ComboBoxItem("No element", "254"));
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
            this.cbInlay2b.Items.Add(new ComboBoxItem("No sockets", "255"));
            this.cbInlay2b.Items.Add(new ComboBoxItem("No element", "254"));
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
            this.cbInlay3b.Items.Add(new ComboBoxItem("No sockets", "255"));
            this.cbInlay3b.Items.Add(new ComboBoxItem("No element", "254"));
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
            this.cbInlay4b.Items.Add(new ComboBoxItem("No sockets", "255"));
            this.cbInlay4b.Items.Add(new ComboBoxItem("No element", "254"));
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
            this.cbInlay5b.Items.Add(new ComboBoxItem("No sockets", "255"));
            this.cbInlay5b.Items.Add(new ComboBoxItem("No element", "254"));
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
			this.cbSetVal.SelectedIndex = 0;
			this.cboPlusType.SelectedIndex = 0;
			this.cboPlusLevel.SelectedIndex = 0;
		}

		private void InitializeComponent()
		{
			this.cboEquipLevel = new ComboBox();
			this.cboEquipExt = new ComboBox();
			this.label31 = new Label();
			this.cboEquipName = new ComboBox();
			this.cboEquipType = new ComboBox();
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
			this.chk380 = new CheckBox();
			this.chkEquipXY = new CheckBox();
			this.chkEquipJN = new CheckBox();
			this.label30 = new Label();
			this.label29 = new Label();
			this.label28 = new Label();
			this.label1 = new Label();
			this.txtDurability = new MuEditor.TextBox();
			this.cboPlusType = new ComboBox();
			this.cboPlusLevel = new ComboBox();
			this.eee = new Label();
			this.label3 = new Label();
			this.chkAllPart = new CheckBox();
			this.AddNums = new MuEditor.TextBox();
			this.label2 = new Label();
			this.txtCode = new MuEditor.TextBox();
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
			this.cbZhiye = new ComboBox();
			this.label4 = new Label();
			this.label5 = new Label();
			this.cbSetVal = new ComboBox();
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
			this.cboEquipLevel.Location = new Point(25, 75);
			this.cboEquipLevel.Name = "cboEquipLevel";
			this.cboEquipLevel.Size = new System.Drawing.Size(46, 20);
			this.cboEquipLevel.TabIndex = 23;
			this.cboEquipExt.DropDownHeight = 206;
			this.cboEquipExt.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboEquipExt.FormattingEnabled = true;
			this.cboEquipExt.IntegralHeight = false;
			ComboBox.ObjectCollection objectCollections = this.cboEquipExt.Items;
			object[] objArray1 = new object[] { "0", "4", "8", "12", "16", "20", "24", "28" };
			objectCollections.AddRange(objArray1);
			this.cboEquipExt.Location = new Point(92, 75);
			this.cboEquipExt.Name = "cboEquipExt";
			this.cboEquipExt.Size = new System.Drawing.Size(50, 20);
			this.cboEquipExt.TabIndex = 22;
			this.label31.AutoSize = true;
			this.label31.Location = new Point(70, 79);
			this.label31.Name = "label31";
			this.label31.Size = new System.Drawing.Size(17, 12);
			this.label31.TabIndex = 21;
			this.label31.Text = "Opt";
			this.cboEquipName.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
			this.cboEquipName.AutoCompleteSource = AutoCompleteSource.ListItems;
			this.cboEquipName.DropDownHeight = 400;
			this.cboEquipName.FormattingEnabled = true;
			this.cboEquipName.IntegralHeight = false;
			this.cboEquipName.Location = new Point(40, 50);
			this.cboEquipName.Name = "cboEquipName";
			this.cboEquipName.Size = new System.Drawing.Size(115, 20);
			this.cboEquipName.TabIndex = 20;
			this.cboEquipName.SelectedIndexChanged += new EventHandler(this.cboEquipName_SelectedIndexChanged);
			this.cboEquipName.KeyUp += new KeyEventHandler(this.cboEquipName_KeyUp);
			this.cboEquipType.DropDownHeight = 206;
			this.cboEquipType.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboEquipType.FormattingEnabled = true;
			this.cboEquipType.IntegralHeight = false;
			this.cboEquipType.Location = new Point(40, 25);
			this.cboEquipType.Name = "cboEquipType";
			this.cboEquipType.Size = new System.Drawing.Size(115, 20);
			this.cboEquipType.TabIndex = 19;
			this.cboEquipType.SelectedIndexChanged += new EventHandler(this.cboEquipType_SelectedIndexChanged);
			
			this.groupBox3.Controls.Add(this.button3);
			this.groupBox3.Controls.Add(this.button2);
			this.groupBox3.Controls.Add(this.chkEquipZY6);
			this.groupBox3.Controls.Add(this.chkEquipZY4);
			this.groupBox3.Controls.Add(this.chkEquipZY2);
			this.groupBox3.Controls.Add(this.chkEquipZY5);
			this.groupBox3.Controls.Add(this.chkEquipZY3);
			this.groupBox3.Controls.Add(this.chkEquipZY1);
			this.groupBox3.Location = new Point(5, 149);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(207, 105);
			this.groupBox3.TabIndex = 18;
			this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Excellent options";
			this.button4.Location = new Point(156, 75);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(45, 22);
			this.button4.TabIndex = 13;
            this.button4.Text = "Sockets";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.button4_Click);
			this.button1.Location = new Point(107, 75);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(45, 22);
			this.button1.TabIndex = 12;
            this.button1.Text = "UNKNOWN";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.button1_Click);
			this.button3.Location = new Point(102, 75);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(50, 22);
			this.button3.TabIndex = 11;
            this.button3.Text = "unALL";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.button3_Click);
			this.button2.Location = new Point(53, 75);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(44, 22);
			this.button2.TabIndex = 10;
            this.button2.Text = "ALL";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.button2_Click);
			this.chkEquipZY6.AutoSize = true;
			this.chkEquipZY6.Location = new Point(111, 55);
			this.chkEquipZY6.Name = "chkEquipZY6";
			this.chkEquipZY6.Size = new System.Drawing.Size(48, 16);
			this.chkEquipZY6.TabIndex = 9;
            this.chkEquipZY6.Text = "Increase HP";
			this.chkEquipZY6.UseVisualStyleBackColor = true;
			this.chkEquipZY4.AutoSize = true;
			this.chkEquipZY4.Location = new Point(111, 35);
			this.chkEquipZY4.Name = "chkEquipZY4";
			this.chkEquipZY4.Size = new System.Drawing.Size(48, 16);
			this.chkEquipZY4.TabIndex = 8;
            this.chkEquipZY4.Text = "Increase HP";
			this.chkEquipZY4.UseVisualStyleBackColor = true;
			this.chkEquipZY2.AutoSize = true;
			this.chkEquipZY2.Location = new Point(111, 15);
			this.chkEquipZY2.Name = "chkEquipZY2";
			this.chkEquipZY2.Size = new System.Drawing.Size(48, 16);
			this.chkEquipZY2.TabIndex = 7;
            this.chkEquipZY2.Text = "DSR10%";
			this.chkEquipZY2.UseVisualStyleBackColor = true;
			this.chkEquipZY5.AutoSize = true;
			this.chkEquipZY5.Location = new Point(16, 55);
			this.chkEquipZY5.Name = "chkEquipZY5";
			this.chkEquipZY5.Size = new System.Drawing.Size(48, 16);
			this.chkEquipZY5.TabIndex = 6;
            this.chkEquipZY5.Text = "Increase MP";
			this.chkEquipZY5.UseVisualStyleBackColor = true;
			this.chkEquipZY3.AutoSize = true;
			this.chkEquipZY3.Location = new Point(16, 35);
			this.chkEquipZY3.Name = "chkEquipZY3";
			this.chkEquipZY3.Size = new System.Drawing.Size(48, 16);
			this.chkEquipZY3.TabIndex = 5;
            this.chkEquipZY3.Text = "REF";
			this.chkEquipZY3.UseVisualStyleBackColor = true;
			this.chkEquipZY1.AutoSize = true;
			this.chkEquipZY1.Location = new Point(16, 15);
			this.chkEquipZY1.Name = "chkEquipZY1";
			this.chkEquipZY1.Size = new System.Drawing.Size(72, 16);
			this.chkEquipZY1.TabIndex = 4;
            this.chkEquipZY1.Text = "Zen";
			this.chkEquipZY1.UseVisualStyleBackColor = true;
			this.chk380.AutoSize = true;
			this.chk380.Location = new Point(161, 52);
			this.chk380.Name = "chk380";
			this.chk380.Size = new System.Drawing.Size(54, 16);
			this.chk380.TabIndex = 29;
            this.chk380.Text = "380";
			this.chk380.UseVisualStyleBackColor = true;
			this.chkEquipXY.AutoSize = true;
			this.chkEquipXY.Location = new Point(69, 128);
			this.chkEquipXY.Name = "chkEquipXY";
			this.chkEquipXY.Size = new System.Drawing.Size(48, 16);
			this.chkEquipXY.TabIndex = 17;
            this.chkEquipXY.Text = "Luck";
			this.chkEquipXY.UseVisualStyleBackColor = true;
			this.chkEquipJN.AutoSize = true;
			this.chkEquipJN.Location = new Point(10, 128);
			this.chkEquipJN.Name = "chkEquipJN";
			this.chkEquipJN.Size = new System.Drawing.Size(48, 16);
			this.chkEquipJN.TabIndex = 16;
            this.chkEquipJN.Text = "Skill";
			this.chkEquipJN.UseVisualStyleBackColor = true;
			this.label30.AutoSize = true;
			this.label30.Location = new Point(4, 78);
			this.label30.Name = "label30";
			this.label30.Size = new System.Drawing.Size(17, 12);
			this.label30.TabIndex = 15;
            this.label30.Text = "lvl";
			this.label29.AutoSize = true;
			this.label29.Location = new Point(2, 54);
			this.label29.Name = "label29";
			this.label29.Size = new System.Drawing.Size(41, 12);
			this.label29.TabIndex = 14;
            this.label29.Text = "Title:";
			this.label28.AutoSize = true;
			this.label28.Location = new Point(3, 28);
			this.label28.Name = "label28";
			this.label28.Size = new System.Drawing.Size(41, 12);
			this.label28.TabIndex = 13;
            this.label28.Text = "Cat:";
			this.label1.AutoSize = true;
			this.label1.Location = new Point(147, 78);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(17, 12);
			this.label1.TabIndex = 24;
            this.label1.Text = "DB";
			this.txtDurability.IsOnlyNumber = true;
			this.txtDurability.Location = new Point(166, 75);
			this.txtDurability.Name = "txtDurability";
			this.txtDurability.Size = new System.Drawing.Size(39, 21);
			this.txtDurability.TabIndex = 25;
			this.txtDurability.Text = "255";
			this.txtDurability.TextAlign = HorizontalAlignment.Center;
			this.cboPlusType.DropDownHeight = 206;
			this.cboPlusType.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboPlusType.FormattingEnabled = true;
			this.cboPlusType.IntegralHeight = false;
			this.cboPlusType.Location = new Point(33, 101);
			this.cboPlusType.Name = "cboPlusType";
			this.cboPlusType.Size = new System.Drawing.Size(100, 20);
			this.cboPlusType.TabIndex = 30;
			this.cboPlusLevel.DropDownHeight = 206;
			this.cboPlusLevel.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cboPlusLevel.FormattingEnabled = true;
			this.cboPlusLevel.IntegralHeight = false;
			ComboBox.ObjectCollection items1 = this.cboPlusLevel.Items;
			object[] objArray2 = new object[] { "+ 0", "+ 1", "+ 2", "+ 3", "+ 4", "+ 5", "+ 6", "+ 7", "+ 8", "+ 9", "+10", "+11", "+12", "+13" };
			items1.AddRange(objArray2);
			this.cboPlusLevel.Location = new Point(164, 101);
			this.cboPlusLevel.Name = "cboPlusLevel";
			this.cboPlusLevel.Size = new System.Drawing.Size(42, 20);
			this.cboPlusLevel.TabIndex = 31;
			this.eee.AutoSize = true;
			this.eee.Location = new Point(3, 104);
			this.eee.Name = "eee";
			this.eee.Size = new System.Drawing.Size(29, 12);
			this.eee.TabIndex = 32;
            this.eee.Text = "Enh:";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(135, 104);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(29, 12);
			this.label3.TabIndex = 33;
            this.label3.Text = "GR:";
			this.chkAllPart.AutoSize = true;
			this.chkAllPart.Enabled = false;
			this.chkAllPart.Location = new Point(161, 29);
			this.chkAllPart.Name = "chkAllPart";
			this.chkAllPart.Size = new System.Drawing.Size(48, 16);
			this.chkAllPart.TabIndex = 35;
            this.chkAllPart.Text = "Match";
			this.chkAllPart.UseVisualStyleBackColor = true;
			this.AddNums.IsOnlyNumber = true;
			this.AddNums.Location = new Point(171, 0);
			this.AddNums.Name = "AddNums";
			this.AddNums.Size = new System.Drawing.Size(39, 21);
			this.AddNums.TabIndex = 38;
			this.AddNums.Text = "1";
			this.label2.AutoSize = true;
			this.label2.Location = new Point(135, 4);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(41, 12);
			this.label2.TabIndex = 37;
            this.label2.Text = "Qty:";
			this.txtCode.IsOnlyNumber = false;
			this.txtCode.Location = new Point(3, 425);
			this.txtCode.Name = "txtCode";
			this.txtCode.ReadOnly = true;
			this.txtCode.Size = new System.Drawing.Size(212, 21);
			this.txtCode.TabIndex = 37;
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
			this.gbXQ.Location = new Point(3, 259);
			this.gbXQ.Name = "gbXQ";
			this.gbXQ.Size = new System.Drawing.Size(210, 162);
			this.gbXQ.TabIndex = 38;
			this.gbXQ.TabStop = false;
            this.gbXQ.Text = "Socket options";
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
            this.label11.Text = "Element";
			this.label10.AutoSize = true;
			this.label10.Location = new Point(3, 118);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(23, 12);
			this.label10.TabIndex = 43;
            this.label10.Text = "S5";
			this.label9.AutoSize = true;
			this.label9.Location = new Point(3, 92);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(23, 12);
			this.label9.TabIndex = 42;
            this.label9.Text = "S4";
			this.label8.AutoSize = true;
			this.label8.Location = new Point(3, 68);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(23, 12);
			this.label8.TabIndex = 41;
            this.label8.Text = "S3";
			this.label7.AutoSize = true;
			this.label7.Location = new Point(3, 42);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(23, 12);
			this.label7.TabIndex = 40;
			this.label7.Text = "S2";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(3, 17);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(23, 12);
			this.label6.TabIndex = 39;
            this.label6.Text = "S1";
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
			this.cbZhiye.DropDownHeight = 206;
			this.cbZhiye.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbZhiye.FormattingEnabled = true;
			this.cbZhiye.IntegralHeight = false;
			ComboBox.ObjectCollection objectCollections1 = this.cbZhiye.Items;
            object[] objArray3 = new object[] { "All",
            "Wizard",
            "Dark Knight",
            "Elf",
            "Magic Gladiator",
            "Dark Lord",
            "Summoner",
            "Rage Fighter" };
			objectCollections1.AddRange(objArray3);
			this.cbZhiye.Location = new Point(62, 0);
			this.cbZhiye.Name = "cbZhiye";
			this.cbZhiye.Size = new System.Drawing.Size(67, 20);
			this.cbZhiye.TabIndex = 40;
			this.cbZhiye.SelectedIndexChanged += new EventHandler(this.cboEquipType_SelectedIndexChanged);
			this.label4.AutoSize = true;
			this.label4.Location = new Point(3, 3);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(65, 12);
			this.label4.TabIndex = 39;
            this.label4.Text = "Class:";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(125, 130);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(41, 12);
			this.label5.TabIndex = 42;
            this.label5.Text = "Value:";
			this.cbSetVal.DropDownHeight = 206;
			this.cbSetVal.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbSetVal.FormattingEnabled = true;
			this.cbSetVal.IntegralHeight = false;
			ComboBox.ObjectCollection items2 = this.cbSetVal.Items;
			object[] objArray4 = new object[] { "0", "5", "6", "9", "10" };
			items2.AddRange(objArray4);
			this.cbSetVal.Location = new Point(171, 126);
			this.cbSetVal.Name = "cbSetVal";
			this.cbSetVal.Size = new System.Drawing.Size(35, 20);
			this.cbSetVal.TabIndex = 43;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.Controls.Add(this.cbSetVal);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.cbZhiye);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.AddNums);
			
			base.Controls.Add(this.label2);
			
			base.Controls.Add(this.chkAllPart);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.eee);
			base.Controls.Add(this.cboPlusLevel);
			base.Controls.Add(this.cboPlusType);
			base.Controls.Add(this.txtDurability);
			base.Controls.Add(this.chk380);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.cboEquipLevel);
			base.Controls.Add(this.cboEquipExt);
			base.Controls.Add(this.label31);
			base.Controls.Add(this.cboEquipName);
			base.Controls.Add(this.cboEquipType);
			base.Controls.Add(this.groupBox3);
			base.Controls.Add(this.chkEquipXY);
			base.Controls.Add(this.chkEquipJN);
			base.Controls.Add(this.label30);
			base.Controls.Add(this.label29);
			base.Controls.Add(this.label28);
			base.Margin = new System.Windows.Forms.Padding(0);
			base.Name = "EquipEditor";
			base.Size = new System.Drawing.Size(217, 453);
			base.Load += new EventHandler(this.EquipEditor_Load);
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			this.gbXQ.ResumeLayout(false);
			this.gbXQ.PerformLayout();
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		public void LoadData()
		{
			try
			{
				this.loadItemTypes(this.itemTypes);
				this.cboEquipType.Items.Clear();
				foreach (EquipItemType itemType in this.itemTypes)
				{
					this.cboEquipType.Items.Add(itemType);
				}
				this.cboEquipType.SelectedIndex = 0;
				this.cboEquipLevel.SelectedIndex = 0;
				this.cboEquipExt.SelectedIndex = 0;
				this.cbZhiye.SelectedIndex = 0;
				this.cboPlusType.SelectedIndex = 0;
				this.cboPlusLevel.SelectedIndex = 0;
			}
			catch (Exception exception)
			{
                Utils.WarningMessage(string.Concat("Error: Database connection failed：", exception.Message));
			}
		}

		protected bool loadItemNamesByType(IList itemNames, int index, int type)
		{
			bool flag;
			this.itemTypes.Clear();
			this.cboEquipName.Items.Clear();
			try
			{
				for (int i = 0; i < (int)EquipEditor.xItem.Length; i++)
				{
					if (EquipEditor.xItem[i] != null && EquipEditor.xItem[i].Group == index)
					{
						switch (type)
						{
							case 1:
							{
								if (EquipEditor.xItem[i].iClassNumber.WIZARD == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 2:
							{
								if (EquipEditor.xItem[i].iClassNumber.KNIGHT == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 3:
							{
								if (EquipEditor.xItem[i].iClassNumber.ELF == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 4:
							{
								if (EquipEditor.xItem[i].iClassNumber.MAGUMSA == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 5:
							{
								if (EquipEditor.xItem[i].iClassNumber.DARKLORD == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 6:
							{
								if (EquipEditor.xItem[i].iClassNumber.SUMMONER == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							case 7:
							{
								if (EquipEditor.xItem[i].iClassNumber.MONK == 0)
								{
									break;
								}
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
							default:
							{
								itemNames.Add(frmMain.ByteToString(EquipEditor.xItem[i].Name, 30));
								break;
							}
						}
					}
				}
				flag = true;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "loadItemNamesByType：\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
				return false;
			}
			return flag;
		}

		protected bool loadItemTypes(IList itemTypes)
		{
			bool flag;
			itemTypes.Clear();
			try
			{
                itemTypes.Add(new EquipItemType(0, "Swords"));
                itemTypes.Add(new EquipItemType(1, "Axes"));
                itemTypes.Add(new EquipItemType(2, "Hammers/Maces"));
                itemTypes.Add(new EquipItemType(3, "Spears/Polearms"));
                itemTypes.Add(new EquipItemType(4, "Bows/Crossbows"));
                itemTypes.Add(new EquipItemType(5, "Staffs"));
                itemTypes.Add(new EquipItemType(6, "Shields"));
                itemTypes.Add(new EquipItemType(7, "Helms"));
                itemTypes.Add(new EquipItemType(8, "Armor"));
                itemTypes.Add(new EquipItemType(9, "Pants"));
                itemTypes.Add(new EquipItemType(10, "Gloves"));
                itemTypes.Add(new EquipItemType(11, "Boots"));
                itemTypes.Add(new EquipItemType(12, "Wings/Gems/Seals"));
                itemTypes.Add(new EquipItemType(13, "Amulets/Rings/Other"));
                itemTypes.Add(new EquipItemType(14, "Potions/Consumables"));
                itemTypes.Add(new EquipItemType(15, "Skills/Spells"));
				flag = true;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "itemTypes.Add：\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
				Application.Exit();
				return false;
			}
			return flag;
		}

		[DllImport("USER32.dll", CharSet=CharSet.None, EntryPoint="SendMessageA", ExactSpelling=false)]
		private static extern int SendMessage(IntPtr hwnd, int wMsg, IntPtr wParam, string lParam);

		public void SetUIbyCob(EquipItem item)
		{
			this.gbXQ.Enabled = Utils.GetQX(item);
			this.chkAllPart.Enabled = (item.Type < 7 ? false : item.Type <= 11);
			this.chkEquipXY.Enabled = (item.Type < 0 ? false : item.Type <= 11);
			this.cbSetVal.Enabled = this.chkEquipXY.Enabled;
			this.chk380.Enabled = Utils.Get380(item);
			this.chk380.Checked = this.chk380.Enabled;
			this.chkEquipJN.Enabled = Utils.GetJN(item);
			if (item.Type != 5)
			{
				this.txtDurability.Text = EquipEditor.xItem[item.Type * 512 + item.Code].Dur.ToString();
			}
			else
			{
				this.txtDurability.Text = EquipEditor.xItem[item.Type * 512 + item.Code].MagicDur.ToString();
			}
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
                            this.cbInlay1b.Items.Add(new ComboBoxItem("None", "0"));
							this.cbInlay2b.Items.Clear();
                            this.cbInlay2b.Items.Add(new ComboBoxItem("None", "0"));
							this.cbInlay3b.Items.Clear();
                            this.cbInlay3b.Items.Add(new ComboBoxItem("None", "0"));
							this.cbInlay4b.Items.Clear();
                            this.cbInlay4b.Items.Add(new ComboBoxItem("None", "0"));
							this.cbInlay5b.Items.Clear();
                            this.cbInlay5b.Items.Add(new ComboBoxItem("None", "0"));
						}
						else if (itemKindB == 43)
						{
							this.cbInlay1b.Items.Clear();
                            this.cbInlay1b.Items.Add(new ComboBoxItem("No sockets", "255"));
                            this.cbInlay1b.Items.Add(new ComboBoxItem("Element", "254"));
                            this.cbInlay1b.Items.Add(new ComboBoxItem("Element (Fire)", "0"));
							this.cbInlay2b.Items.Clear();
                            this.cbInlay2b.Items.Add(new ComboBoxItem("No sockets", "255"));
                            this.cbInlay2b.Items.Add(new ComboBoxItem("Element", "254"));
                            this.cbInlay2b.Items.Add(new ComboBoxItem("Element (Water)", "1"));
							this.cbInlay3b.Items.Clear();
                            this.cbInlay3b.Items.Add(new ComboBoxItem("No sockets", "255"));
                            this.cbInlay3b.Items.Add(new ComboBoxItem("Element", "254"));
                            this.cbInlay3b.Items.Add(new ComboBoxItem("Element (Earth)", "2"));
							this.cbInlay4b.Items.Clear();
                            this.cbInlay4b.Items.Add(new ComboBoxItem("No sockets", "255"));
                            this.cbInlay4b.Items.Add(new ComboBoxItem("Element", "254"));
                            this.cbInlay4b.Items.Add(new ComboBoxItem("Element (Wind)", "3"));
							this.cbInlay5b.Items.Clear();
                            this.cbInlay5b.Items.Add(new ComboBoxItem("No sockets", "255"));
                            this.cbInlay5b.Items.Add(new ComboBoxItem("Element", "254"));
                            this.cbInlay5b.Items.Add(new ComboBoxItem("Element (Darkness)", "4"));
						}
						else if (itemKindB == 44)
						{
							    this.cbInlay1b.Items.Clear();
                                this.cbInlay1b.Items.Add(new ComboBoxItem("None", "255"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +1", "17")); // Fallenfate - 1-order properties
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +2", "33"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +3", "49"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +4", "65"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +5", "81"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +6", "97"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +7", "113"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +8", "129"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +9", "145"));
                                this.cbInlay1b.Items.Add(new ComboBoxItem("Property 1 +10", "161"));
                                this.cbInlay2b.Items.Clear();
                                this.cbInlay2b.Items.Add(new ComboBoxItem("None", "255"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +1", "17"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +2", "33"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +3", "49"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +4", "65"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +5", "81"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +6", "97"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +7", "113"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +8", "129"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +9", "145"));
                                this.cbInlay2b.Items.Add(new ComboBoxItem("Property 2 +10", "161"));
                                this.cbInlay3b.Items.Clear();
                                this.cbInlay3b.Items.Add(new ComboBoxItem("None", "255"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +1", "17"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +2", "33"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +3", "49"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +4", "65"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +5", "81"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +6", "97"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +7", "113"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +8", "129"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +9", "145"));
                                this.cbInlay3b.Items.Add(new ComboBoxItem("Property 3 +10", "161"));
                                this.cbInlay4b.Items.Clear();
                                this.cbInlay4b.Items.Add(new ComboBoxItem("None", "255"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +1", "17"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +2", "33"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +3", "49"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +4", "65"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +5", "81"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +6", "97"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +7", "113"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +8", "129"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +9", "145"));
                                this.cbInlay4b.Items.Add(new ComboBoxItem("Property 4 +10", "161"));
                                this.cbInlay5b.Items.Clear();
                                this.cbInlay5b.Items.Add(new ComboBoxItem("None", "255"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +1", "17"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +2", "33"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +3", "49"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +4", "65"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +5", "81"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +6", "97"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +7", "113"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +8", "129"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +9", "145"));
                                this.cbInlay5b.Items.Add(new ComboBoxItem("Property 5 +10", "161"));
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
						if (itemKindA != 5 || itemKindB != 46 || item.Code != 37)
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
            this.chkEquipZY1.Enabled = this.chkEquipZY1.Text != "No";
            this.chkEquipZY2.Enabled = this.chkEquipZY2.Text != "No";
            this.chkEquipZY3.Enabled = this.chkEquipZY3.Text != "No";
            this.chkEquipZY4.Enabled = this.chkEquipZY4.Text != "No";
            this.chkEquipZY5.Enabled = this.chkEquipZY5.Text != "No";
            this.chkEquipZY6.Enabled = this.chkEquipZY6.Text != "No";
		}

		private void setZY(int type)
		{
			if (type == 0)
			{
				this.chkEquipZY1.Text = "No";
                this.chkEquipZY2.Text = "No";
                this.chkEquipZY3.Text = "No";
                this.chkEquipZY4.Text = "No";
                this.chkEquipZY5.Text = "No";
                this.chkEquipZY6.Text = "No";
				return;
			}
			if (type == 1)
			{
                this.chkEquipZY1.Text = "MANA /8";
                this.chkEquipZY2.Text = "LIFE /8";
                this.chkEquipZY3.Text = "Speed +7";
                this.chkEquipZY4.Text = "Damage +2%";
                this.chkEquipZY5.Text = "DMG level/20";
                this.chkEquipZY6.Text = "EDR + 10%";
				return;
			}
			if (type == 2)
			{
                this.chkEquipZY1.Text = "Zen + 40%";
                this.chkEquipZY2.Text = "DSR +10%";
                this.chkEquipZY3.Text = "REF 5%";
                this.chkEquipZY4.Text = "DD 4%";
                this.chkEquipZY5.Text = "MP +4%";
                this.chkEquipZY6.Text = "HP +4%";
				return;
			}
			if (type == 3)
			{
                this.chkEquipZY1.Text = "Withdraw";
                this.chkEquipZY2.Text = "Add mana";
                this.chkEquipZY3.Text = "Ignore"; 
                this.chkEquipZY4.Text = "Skill values";
                this.chkEquipZY5.Text = "Speed";
                this.chkEquipZY6.Text = "Recovery";
				return;
			}
			if (type == 4)
			{
                this.chkEquipZY1.Text = "Ignore";
                this.chkEquipZY2.Text = "Reflect damage";
                this.chkEquipZY3.Text = "Life regen";
                this.chkEquipZY4.Text = "Mana regen";
                this.chkEquipZY5.Text = "Recovery";
                this.chkEquipZY6.Text = "Recovery";
				return;
			}
			if (type == 5)
			{
                this.chkEquipZY1.Text = "Life +50";
                this.chkEquipZY2.Text = "Mana +50";
                this.chkEquipZY3.Text = "Ignore";
                this.chkEquipZY4.Text = "Add command";
                this.chkEquipZY5.Text = "No";
                this.chkEquipZY6.Text = "No";
				return;
			}
			if (type == 6)
			{
				this.chkEquipZY1.Text = "黑狼";
				this.chkEquipZY2.Text = "青狼";
				this.chkEquipZY3.Text = "金狼";
                this.chkEquipZY4.Text = "No";
                this.chkEquipZY5.Text = "No";
                this.chkEquipZY6.Text = "No";
			}
		}

        public void updateData(EquipItem item)
        {
            item.Level = (byte)this.cboEquipLevel.SelectedIndex;
            item.Ext = this.cboEquipExt.SelectedIndex;
            item.PlusType = (byte)this.cboPlusType.SelectedIndex;
            item.PlusLevel = (this.cboPlusType.SelectedIndex <= 0) ? ((byte)0) : ((byte)this.cboPlusLevel.SelectedIndex);
            item.JN = this.chkEquipJN.Checked && this.chkEquipJN.Enabled;
            item.XY = this.chkEquipXY.Checked && this.chkEquipXY.Enabled;
            item.ZY1 = this.chkEquipZY1.Checked && this.chkEquipZY1.Enabled;
            item.ZY2 = this.chkEquipZY2.Checked && this.chkEquipZY2.Enabled;
            item.ZY3 = this.chkEquipZY3.Checked && this.chkEquipZY3.Enabled;
            item.ZY4 = this.chkEquipZY4.Checked && this.chkEquipZY4.Enabled;
            item.ZY5 = this.chkEquipZY5.Checked && this.chkEquipZY5.Enabled;
            item.ZY6 = this.chkEquipZY6.Checked && this.chkEquipZY6.Enabled;
            item.IsSet = (this.cbSetVal.SelectedIndex > 0) && this.cbSetVal.Enabled;
            item.SetVal = this.cbSetVal.Enabled ? Convert.ToByte(this.cbSetVal.SelectedItem) : ((byte)0);
            item.Is380 = this.chk380.Checked && this.chk380.Enabled;
            item.Durability = Convert.ToByte(this.txtDurability.Text);
            if (this.gbXQ.Enabled)
            {
                item.PlusType = 0;
                item.PlusLevel = 0;
                byte itemKindA = xItem[(item.Type * 0x200) + item.Code].ItemKindA;
                byte itemKindB = xItem[(item.Type * 0x200) + item.Code].ItemKindB;
                byte itemCategory = xItem[(item.Type * 0x200) + item.Code].ItemCategory;
                if (itemKindA == 8)
                {
                    ComboBoxItem selectedItem = (ComboBoxItem)this.cbInlay1b.SelectedItem;
                    item.XQ1 = Convert.ToByte(selectedItem.Value);
                    ComboBoxItem item3 = (ComboBoxItem)this.cbInlay2b.SelectedItem;
                    item.XQ2 = Convert.ToByte(item3.Value);
                    ComboBoxItem item4 = (ComboBoxItem)this.cbInlay3b.SelectedItem;
                    item.XQ3 = Convert.ToByte(item4.Value);
                    ComboBoxItem item5 = (ComboBoxItem)this.cbInlay4b.SelectedItem;
                    item.XQ4 = Convert.ToByte(item5.Value);
                    ComboBoxItem item6 = (ComboBoxItem)this.cbInlay5b.SelectedItem;
                    item.XQ5 = Convert.ToByte(item6.Value);
                    item.YG = (byte)(this.cbInlay6b.SelectedIndex + 0x11);
                }
                else
                {
                    ComboBoxItem item7 = (ComboBoxItem)this.cbInlay1b.SelectedItem;
                    item.XQ1 = Convert.ToByte(item7.Value);
                    ComboBoxItem item8 = (ComboBoxItem)this.cbInlay2b.SelectedItem;
                    item.XQ2 = Convert.ToByte(item8.Value);
                    ComboBoxItem item9 = (ComboBoxItem)this.cbInlay3b.SelectedItem;
                    item.XQ3 = Convert.ToByte(item9.Value);
                    ComboBoxItem item10 = (ComboBoxItem)this.cbInlay4b.SelectedItem;
                    item.XQ4 = Convert.ToByte(item10.Value);
                    ComboBoxItem item11 = (ComboBoxItem)this.cbInlay5b.SelectedItem;
                    item.XQ5 = Convert.ToByte(item11.Value);
                    item.YG = (this.cbInlay6b.SelectedIndex > 0) ? ((byte)(this.cbInlay6b.SelectedIndex - 1)) : ((byte)0xff);
                }
            }
        }

		public void updateUI(EquipItem item)
		{
			try
			{
				this.cbZhiye.SelectedIndex = 0;
				this.cboEquipType.SelectedIndex = item.Type;
				this.cboEquipName.Text = item.Name;
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
				this.txtCode.Text = string.Concat("H:", item.ToString());
				if (this.gbXQ.Enabled)
				{
					this.cboPlusType.SelectedIndex = 0;
					this.cboPlusLevel.SelectedIndex = 0;
					byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
					byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
					byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
					if (itemKindA != 8)
					{
						if (item.XQ1 == 255)
						{
							this.cbInlay1b.SelectedIndex = 0;
						}
						else if (item.XQ1 != 254)
						{
							int xQ1 = item.XQ1 % 50;
							int num = (item.XQ1 - xQ1) / 50;
							string str = string.Concat(frmMain.ByteToString(EquipEditor.xSocket[xQ1].捞抚, 64), " +", EquipEditor.xSocket[xQ1].饭骇1[num].ToString());
							this.cbInlay1b.SelectedIndex = EquipEditor.SendMessage(this.cbInlay1b.Handle, 332, IntPtr.Zero, str);
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
							this.cbInlay2b.SelectedIndex = EquipEditor.SendMessage(this.cbInlay2b.Handle, 332, IntPtr.Zero, str1);
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
							this.cbInlay3b.SelectedIndex = EquipEditor.SendMessage(this.cbInlay3b.Handle, 332, IntPtr.Zero, str2);
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
							this.cbInlay4b.SelectedIndex = EquipEditor.SendMessage(this.cbInlay4b.Handle, 332, IntPtr.Zero, str3);
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
							this.cbInlay5b.SelectedIndex = EquipEditor.SendMessage(this.cbInlay5b.Handle, 332, IntPtr.Zero, str4);
						}
						else
						{
							this.cbInlay5b.SelectedIndex = 1;
						}
						if (item.YG < 0 || item.YG >= (int)Utils.YGS.Length - 1)
						{
							this.cbInlay6b.SelectedIndex = 0;
						}
						else
						{
							this.cbInlay6b.SelectedIndex = item.YG + 1;
						}
					}
					else
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
						}
						else
						{
							this.cbInlay6b.SelectedIndex = item.YG - 17;
						}
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "Error:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
		}
	}
}