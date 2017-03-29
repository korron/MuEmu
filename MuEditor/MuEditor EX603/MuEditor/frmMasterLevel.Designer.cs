using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data.OleDb;
using System.Drawing;
using System.Resources;
using System.Text;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmMasterLevel : frmBase
	{
		private IContainer components;

		private MuEditor.TextBox txtPoint;

		private Label label32;

		private MuEditor.TextBox txtNextEXP;

		private Label label31;

		private MuEditor.TextBox txtEXP;

		private Label label30;

		private MuEditor.TextBox txtLevel;

		private Label label29;

		private Button btnOK;

		private Label label1;

		private Button button1;

		private MuEditor.TextBox txtCharacter;

		private Label label2;

		private RadioButton rbAll;

		private RadioButton rbKeep;

		private RadioButton rbClear;

		private GroupBox groupBox1;

		private string charName = "";

		private int classID;

		public frmMasterLevel(string charName)
		{
			this.InitializeComponent();
			this.charName = charName;
            string str = string.Format("SELECT MasterSkillTree.Name, MasterSkillTree.MasterLevel, MasterSkillTree.MasterExperience, MasterSkillTree.MasterPoint, Character.Class FROM Character INNER JOIN MasterSkillTree ON Character.Name = MasterSkillTree.Name COLLATE Chinese_PRC_CS_AS_KS_WS WHERE (MasterSkillTree.Name = '{0}')", charName);
			try
			{
				OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
				if (!oleDbDataReader.Read())
				{
                    Utils.WarningMessage(string.Concat("Sorry, no role", charName, "corresponding account information!"));
					this.btnOK.Enabled = false;
				}
				else
				{
					this.txtCharacter.Text = Convert.ToString(oleDbDataReader.GetValue(0));
                    this.txtLevel.Text = Convert.ToString(oleDbDataReader.GetValue(1));
                    this.txtEXP.Text = Convert.ToString(oleDbDataReader.GetValue(2));
                    
                    this.txtPoint.Text = Convert.ToString(oleDbDataReader.GetValue(3));
					if (oleDbDataReader.GetValue(4) != DBNull.Value)
					{
						this.classID = oleDbDataReader.GetByte(4);
					}
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

		private void btnOK_Click(object sender, EventArgs e)
		{
			string str = "";
			try
			{
				this.Cursor = Cursors.WaitCursor;
				short num = Convert.ToInt16(this.txtLevel.Text.Replace(" ", ""));
				long num1 = Convert.ToInt64(this.txtEXP.Text.Replace(" ", ""));
				
				short num2 = Convert.ToInt16(this.txtPoint.Text.Replace(" ", ""));
				object[] objArray = new object[] { num, num1, num2, this.charName };
                str = string.Format("UPDATE MasterSkillTree SET MasterLevel = {0}, MasterSkillTree.MasterExperience = {1}, MasterPoint = {2} WHERE (Name = '{3}')", objArray);
				base.Mu_ExecuteSQL(str);
				
                Utils.InfoMessage("Successful operation!");
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			this.Cursor = Cursors.Default;
		}

		private void button1_Click(object sender, EventArgs e)
		{
			base.Close();
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private string getJNSQL(bool isAll)
		{
			int j;
			StringBuilder stringBuilder;
			string str = string.Concat("UPDATE Character SET MagicList = {0} WHERE (Name = '", this.charName, "')");
			StringBuilder stringBuilder1 = new StringBuilder("0x");
			int num = 0;
			int num1 = 0;
			for (int i = 0; i < Utils.lstSSG.Count; i++)
			{
				SKILL_SQL_GS item = Utils.lstSSG[i];
				if (item.GSSkillID > 0 && item.GSSkillID < 255)
				{
					stringBuilder1.Append(Utils.SKILL_GS2SQL(item));
					num++;
				}
			}
			if (isAll)
			{
				num1 = 26;
				int num2 = this.classID;
				if (num2 > 35)
				{
					switch (num2)
					{
						case 48:
						case 50:
						{
							stringBuilder1.Append("FF2A18FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF29F4FF2968FF296DFF29F9FF29FEFF2936FF2A04FF2977FF2972FF297CFF29AEFF2940FF2945FF2959FF295EFF2981FF299A");
							for (j = num1 + num; j < 150; j++)
							{
								stringBuilder = stringBuilder1.Append("FF0000");
							}
							return string.Format(str, stringBuilder1.ToString());
						}
						case 49:
						{
							break;
						}
						default:
						{
							switch (num2)
							{
								case 64:
								case 66:
								{
									stringBuilder1.Append("FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF2A0EFF2968FF296DFF2A13FF2936FF2A09FF2977FF2972FF297CFF2990FF2995FF2940FF2945FF2959FF295EFF2981FF29A9FF299A");
									for (j = num1 + num; j < 150; j++)
									{
										stringBuilder = stringBuilder1.Append("FF0000");
									}
									return string.Format(str, stringBuilder1.ToString());
								}
								case 65:
								{
									break;
								}
								default:
								{
									switch (num2)
									{
										case 80:
										case 81:
										case 83:
										{
											num1 = num1 + 3;
											stringBuilder1.Append("FF2A2CFF2A22FF2A1DFF2A27FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF2A0EFF2968FF296DFF2A13FF2936FF2A09FF2977FF2972FF297CFF2940FF2945FF2959FF295EFF2981FF299AFF299FFF29A4");
											for (j = num1 + num; j < 150; j++)
											{
												stringBuilder = stringBuilder1.Append("FF0000");
											}
											return string.Format(str, stringBuilder1.ToString());
										}
									}
									break;
								}
							}
							break;
						}
					}
				}
				else
				{
					switch (num2)
					{
						case 0:
						case 1:
						case 3:
						{
							stringBuilder1.Append("FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF29BDFF2968FF296DFF29C2FF29C7FF2936FF29B8FF2977FF2972FF297CFF299FFF29A4FF2940FF2945FF2959FF295EFF2981FF299A");
							for (j = num1 + num; j < 150; j++)
							{
								stringBuilder = stringBuilder1.Append("FF0000");
							}
							return string.Format(str, stringBuilder1.ToString());
						}
						case 2:
						{
							break;
						}
						default:
						{
							switch (num2)
							{
								case 16:
								case 17:
								case 19:
								{
									stringBuilder1.Append("FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF29CCFF2968FF296DFF29D1FF29D6FF2936FF29DBFF2977FF2972FF297CFF2990FF2995FF2940FF2945FF2959FF295EFF2981FF299A");
									for (j = num1 + num; j < 150; j++)
									{
										stringBuilder = stringBuilder1.Append("FF0000");
									}
									return string.Format(str, stringBuilder1.ToString());
								}
								case 18:
								{
									break;
								}
								default:
								{
									switch (num2)
									{
										case 32:
										case 33:
										case 35:
										{
											stringBuilder1.Append("FF293BFF294AFF294FFF2954FF2963FF2986FF298BFF2931FF29E0FF2968FF296DFF29E5FF29EAFF2936FF29EFFF2977FF2972FF297CFF2990FF2995FF2940FF2945FF2959FF295EFF2981FF299A");
											for (j = num1 + num; j < 150; j++)
											{
												stringBuilder = stringBuilder1.Append("FF0000");
											}
											return string.Format(str, stringBuilder1.ToString());
										}
									}
									break;
								}
							}
							break;
						}
					}
				}
				num1 = 0;
			}
			for (j = num1 + num; j < 150; j++)
			{
				stringBuilder = stringBuilder1.Append("FF0000");
			}
			return string.Format(str, stringBuilder1.ToString());
		}

		private void InitializeComponent()
		{
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(frmMasterLevel));
			this.txtPoint = new MuEditor.TextBox();
			this.label32 = new Label();
			this.txtNextEXP = new MuEditor.TextBox();
			this.label31 = new Label();
			this.txtEXP = new MuEditor.TextBox();
			this.label30 = new Label();
			this.txtLevel = new MuEditor.TextBox();
			this.label29 = new Label();
			this.btnOK = new Button();
			this.label1 = new Label();
			this.button1 = new Button();
			this.txtCharacter = new MuEditor.TextBox();
			this.label2 = new Label();
            this.rbAll = new RadioButton();
            this.rbKeep = new RadioButton();
            this.rbClear = new RadioButton();
			this.groupBox1 = new GroupBox();
			this.groupBox1.SuspendLayout();
			base.SuspendLayout();
			this.txtPoint.IsOnlyNumber = true;
			this.txtPoint.Location = new Point(70, 124);
			this.txtPoint.Name = "txtPoint";
			this.txtPoint.Size = new System.Drawing.Size(144, 21);
			this.txtPoint.TabIndex = 59;
			this.label32.AutoSize = true;
			this.label32.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label32.Location = new Point(6, 128);
			this.label32.Name = "label32";
			this.label32.Size = new System.Drawing.Size(41, 12);
			this.label32.TabIndex = 58;
            this.label32.Text = "Left point:";
			this.txtNextEXP.IsOnlyNumber = true;
			this.txtNextEXP.Location = new Point(70, 97);
			this.txtNextEXP.Name = "txtNextEXP";
			this.txtNextEXP.Size = new System.Drawing.Size(144, 21);
			this.txtNextEXP.TabIndex = 57;
			this.label31.AutoSize = true;
			this.label31.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label31.Location = new Point(6, 101);
			this.label31.Name = "label31";
			this.label31.Size = new System.Drawing.Size(65, 12);
			this.label31.TabIndex = 56;
            
			this.txtEXP.IsOnlyNumber = true;
			this.txtEXP.Location = new Point(70, 70);
			this.txtEXP.Name = "txtEXP";
			this.txtEXP.Size = new System.Drawing.Size(144, 21);
			this.txtEXP.TabIndex = 55;
			this.label30.AutoSize = true;
			this.label30.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label30.Location = new Point(6, 74);
			this.label30.Name = "label30";
			this.label30.Size = new System.Drawing.Size(41, 12);
			this.label30.TabIndex = 54;
            this.label30.Text = "Experience:";
			this.txtLevel.IsOnlyNumber = true;
			this.txtLevel.Location = new Point(71, 43);
			this.txtLevel.Name = "txtLevel";
			this.txtLevel.Size = new System.Drawing.Size(144, 21);
			this.txtLevel.TabIndex = 53;
			this.txtLevel.TextChanged += new EventHandler(this.txtLevel_TextChanged);
			this.label29.AutoSize = true;
			this.label29.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label29.Location = new Point(6, 47);
			this.label29.Name = "label29";
			this.label29.Size = new System.Drawing.Size(41, 12);
			this.label29.TabIndex = 52;
            this.label29.Text = "Level:";
			this.btnOK.Location = new Point(41, 186);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(58, 23);
			this.btnOK.TabIndex = 60;
			this.btnOK.Text = "OK";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new EventHandler(this.btnOK_Click);
			this.label1.AutoSize = true;
			this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label1.Location = new Point(6, 20);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(41, 12);
			this.label1.TabIndex = 61;
            this.label1.Text = "Character:";
			this.button1.Location = new Point(118, 186);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(58, 23);
			this.button1.TabIndex = 63;
			this.button1.Text = "Close";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.button1_Click);
			this.txtCharacter.IsOnlyNumber = false;
			this.txtCharacter.Location = new Point(71, 16);
			this.txtCharacter.Name = "txtCharacter";
			this.txtCharacter.ReadOnly = true;
			this.txtCharacter.Size = new System.Drawing.Size(144, 21);
			this.txtCharacter.TabIndex = 64;
			this.label2.AutoSize = true;
			this.label2.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label2.Location = new Point(6, 156);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(65, 12);
			this.label2.TabIndex = 65;
            
			this.rbAll.AutoSize = true;
            this.rbAll.Visible = true;
			this.rbAll.Location = new Point(71, 156);
			this.rbAll.Name = "rbAll";
			this.rbAll.Size = new System.Drawing.Size(47, 16);
			this.rbAll.TabIndex = 66;
            
			this.rbAll.UseVisualStyleBackColor = true;
			this.rbKeep.AutoSize = true;
			
			this.rbKeep.Location = new Point(119, 156);
			this.rbKeep.Name = "rbKeep";
			this.rbKeep.Size = new System.Drawing.Size(47, 16);
			this.rbKeep.TabIndex = 67;
			this.rbKeep.TabStop = true;
            
			this.rbKeep.UseVisualStyleBackColor = true;
			this.rbClear.AutoSize = true;
			this.rbClear.Location = new Point(169, 156);
			this.rbClear.Name = "rbClear";
			this.rbClear.Size = new System.Drawing.Size(47, 16);
			this.rbClear.TabIndex = 68;
            
			this.rbClear.UseVisualStyleBackColor = true;
			this.groupBox1.Controls.Add(this.label1);		
			this.groupBox1.Controls.Add(this.label29);			
			this.groupBox1.Controls.Add(this.txtLevel);
			this.groupBox1.Controls.Add(this.label30);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.txtEXP);
			this.groupBox1.Controls.Add(this.txtCharacter);
			this.groupBox1.Controls.Add(this.label31);
			this.groupBox1.Controls.Add(this.button1);			
			this.groupBox1.Controls.Add(this.label32);
			this.groupBox1.Controls.Add(this.btnOK);
			this.groupBox1.Controls.Add(this.txtPoint);
			this.groupBox1.Location = new Point(6, 4);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(221, 218);
			this.groupBox1.TabIndex = 69;
			this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Modify master information";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(233, 227);
			base.Controls.Add(this.groupBox1);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.Icon = (System.Drawing.Icon)componentResourceManager.GetObject("$this.Icon");
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmMasterLevel";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterParent;
            this.Text = "Modify Masters";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			base.ResumeLayout(false);
		}

		private void txtLevel_TextChanged(object sender, EventArgs e)
		{
			if (int.Parse(this.txtLevel.Text) > 400)
			{
                Utils.WarningMessage("You can not be greater than 400!");
			}
		}
	}
}