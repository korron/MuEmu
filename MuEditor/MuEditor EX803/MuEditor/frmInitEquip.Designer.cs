using MuEditor.Properties;
using System;
using System.ComponentModel;
using System.Data.OleDb;
using System.Drawing;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmInitEquip : frmBase
	{
		private static frmInitEquip form;

		private string[] strLoads = new string[7];

		private string[] strCodes = new string[7];

		private string strCode = "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

		private IContainer components;

		private Panel pnlPackage;

		private CharPanel charPanel;

		private EquipPanel packagePanel;

		private EquipPanel packagePanelLv1;

		private EquipPanel packagePanelLv2;

		private EquipPanel packagePanelLv3;

		private EquipPanel packagePanelLv4;

		private EquipPanel shopPanel;

        private PentagramPanel sBookPanel;

		private GroupBox groupBox2;

		private EquipEditor equipEditor;

		private ComboBox cbZhiye;

		private Label label1;

		private Button btnSave;

		private CheckBox chkAll;

		private Button btnClearChar;

		private Button btnCleanPackage;

		private Button btnClearPackage;

		static frmInitEquip()
		{
		}

		public frmInitEquip()
		{
			this.InitializeComponent();
			this.init();
		}

		private void btnCleanPackage_Click(object sender, EventArgs e)
		{
			this.packagePanel.DownItem();
			EquipItem[] equipItems = this.packagePanel.getEquipItems();
			this.packagePanel.clearData();
			this.packagePanel.putItems(equipItems, true);
			this.packagePanel.Invalidate();
			this.packagePanelLv1.DownItem();
			EquipItem[] equipItemArray = this.packagePanelLv1.getEquipItems();
			this.packagePanelLv1.clearData();
			this.packagePanelLv1.putItems(equipItemArray, true);
			this.packagePanelLv1.Invalidate();
			this.packagePanelLv2.DownItem();
			EquipItem[] equipItems1 = this.packagePanelLv2.getEquipItems();
			this.packagePanelLv2.clearData();
			this.packagePanelLv2.putItems(equipItems1, true);
			this.packagePanelLv2.Invalidate();
			this.packagePanelLv3.DownItem();
			EquipItem[] equipItemArray1 = this.packagePanelLv3.getEquipItems();
			this.packagePanelLv3.clearData();
			this.packagePanelLv3.putItems(equipItemArray1, true);
			this.packagePanelLv3.Invalidate();
			this.packagePanelLv4.DownItem();
			EquipItem[] equipItems2 = this.packagePanelLv4.getEquipItems();
			this.packagePanelLv4.clearData();
			this.packagePanelLv4.putItems(equipItems2, true);
			this.packagePanelLv4.Invalidate();
		}

		private void btnClearChar_Click(object sender, EventArgs e)
		{
			this.charPanel.clearData();
			this.charPanel.Invalidate();
            this.sBookPanel.clearData();
            this.sBookPanel.Invalidate();
		}

		private void btnClearPackage_Click(object sender, EventArgs e)
		{
			this.packagePanel.clearData();
			this.packagePanel.Invalidate();
			this.packagePanelLv1.clearData();
			this.packagePanelLv1.Invalidate();
			this.packagePanelLv2.clearData();
			this.packagePanelLv2.Invalidate();
			this.packagePanelLv3.clearData();
			this.packagePanelLv3.Invalidate();
			this.packagePanelLv4.clearData();
			this.packagePanelLv4.Invalidate();
		}

		private void btnSave_Click(object sender, EventArgs e)
		{
			string str = "IF EXISTS (SELECT NAME FROM SYSOBJECTS WHERE XTYPE = 'TR' AND NAME = 'T_HE_INSERT_Character_Inventory')\r\nDROP TRIGGER T_HE_INSERT_Character_Inventory";
			string str1 = "CREATE TRIGGER T_HE_INSERT_Character_Inventory\r\nON Character\r\nFOR INSERT\r\nAS\r\nBEGIN TRANSACTION\r\nDECLARE @Cls tinyint, @Lev smallint, @Name varchar\\(10\\)\r\nSELECT @Cls = Class, @Lev = cLevel, @Name = Name FROM INSERTED\r\nIF @Lev > 1\r\nIF @Cls = 0\r\nUPDATE Character SET Inventory = {0} WHERE (Name = @Name)\r\nELSE IF @Cls=16\r\nUPDATE Character SET Inventory = {1} WHERE (Name = @Name)\r\nelse if @Cls=32\r\nUPDATE Character SET Inventory = {2} WHERE (Name = @Name)\r\nELSE IF @Cls=48\r\nUPDATE Character SET Inventory = {3} WHERE (Name = @Name)\r\nELSE IF @Cls=64\r\nUPDATE Character SET Inventory = {4} WHERE (Name = @Name)\r\nELSE IF @Cls=80\r\nUPDATE Character SET Inventory = {5} WHERE (Name = @Name)\r\nELSE IF @Cls=96\r\nUPDATE Character SET Inventory = {6} WHERE (Name = @Name)\r\nELSE\r\nUPDATE Character SET Inventory = {0} WHERE (Name = @Name)\r\nCOMMIT TRANSACTION";
			try
			{
				if (this.chkAll.Checked)
				{
					string code = this.getCode();
					for (int i = 0; i < (int)this.strCodes.Length; i++)
					{
						this.strCodes[i] = code;
					}
				}
				str1 = string.Format(str1, this.strCodes);
				if (!base.Mu_ExecuteSQL(str) || !base.Mu_ExecuteSQL(str1))
				{
					Utils.WarningMessage("操作失败！");
				}
				else
				{
					for (int j = 0; j < (int)this.strCodes.Length; j++)
					{
						this.strLoads[j] = this.strCodes[j];
					}
					Utils.InfoMessage("操作成功！");
				}
			}
			catch (Exception exception)
			{
				Utils.WarningMessage(string.Concat("Error:", exception.Message));
			}
		}

		private void cbZhiye_SelectedIndexChanged(object sender, EventArgs e)
		{
			try
			{
				byte[] bytes = Utils.StringToBytes(this.strCodes[this.cbZhiye.SelectedIndex]);
				if (bytes != null)
				{
					this.charPanel.clearData();
					if (!this.charPanel.loadItemsByCodes(bytes, 0, 192))
					{
						Utils.WarningMessage("加载角色身上的装备失败，可能数据格式不正确！");
					}
					this.charPanel.Invalidate();
					this.packagePanel.clearData();
					int xNum = 192;
					if (!this.packagePanel.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色包裹里的装备失败，可能数据格式不正确！");
					}
					this.packagePanel.Invalidate();
					this.packagePanelLv1.clearData();
					xNum = xNum + this.packagePanel.XNum * this.packagePanel.YNum * 16;
					if (!this.packagePanelLv1.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色包裹Lv1里的装备失败，可能数据格式不正确！");
					}
					this.packagePanelLv1.Invalidate();
					this.packagePanelLv2.clearData();
					xNum = xNum + this.packagePanelLv1.XNum * this.packagePanelLv1.YNum * 16;
					if (!this.packagePanelLv2.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色包裹Lv2里的装备失败，可能数据格式不正确！");
					}
					this.packagePanelLv2.Invalidate();
					this.packagePanelLv3.clearData();
					xNum = xNum + this.packagePanelLv2.XNum * this.packagePanelLv2.YNum * 16;
					if (!this.packagePanelLv3.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色包裹Lv3里的装备失败，可能数据格式不正确！");
					}
					this.packagePanelLv3.Invalidate();
					this.packagePanelLv4.clearData();
					xNum = xNum + this.packagePanelLv3.XNum * this.packagePanelLv3.YNum * 16;
					if (!this.packagePanelLv4.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色包裹Lv4里的装备失败，可能数据格式不正确！");
					}
					this.packagePanelLv4.Invalidate();
					this.shopPanel.clearData();
					xNum = xNum + this.packagePanelLv4.XNum * this.packagePanelLv4.YNum * 16;
					if (!this.shopPanel.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
					{
						Utils.WarningMessage("加载角色商店里的装备失败，可能数据格式不正确！");
					}
					this.shopPanel.Invalidate();
                    this.sBookPanel.clearData();
                    xNum = xNum + this.shopPanel.XNum * this.shopPanel.YNum * 16;
                    if (!this.sBookPanel.loadItemsByCodes(bytes, xNum, (int)bytes.Length - xNum))
                    {
                        Utils.WarningMessage("加载角色技能书栏的装备失败，可能数据格式不正确！");
                    }
                    this.sBookPanel.Invalidate();
				}
			}
			catch (Exception exception)
			{
				Utils.WarningMessage(string.Concat("Error:", exception.Message));
			}
		}

		private void charPanel_MouseLeave(object sender, EventArgs e)
		{
			this.strCodes[this.cbZhiye.SelectedIndex] = this.getCode();
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void frmInitEquip_FormClosed(object sender, FormClosedEventArgs e)
		{
			frmInitEquip.form = null;
		}

		private void frmInitEquip_FormClosing(object sender, FormClosingEventArgs e)
		{
			bool flag = false;
			int num = 0;
			while (num < (int)this.strCodes.Length)
			{
				if (this.strLoads[num] == this.strCodes[num])
				{
					num++;
				}
				else
				{
					flag = true;
					break;
				}
			}
			if (flag && MessageBox.Show("是否保存当前设置？", "询问", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == System.Windows.Forms.DialogResult.Yes)
			{
				this.btnSave_Click(sender, e);
			}
		}

		private void frmInitEquip_Load(object sender, EventArgs e)
		{
			this.charPanel.Editor = this.equipEditor;
			this.packagePanel.setSize(8, 8);
			this.packagePanel.Editor = this.equipEditor;
			this.packagePanelLv1.setSize(8, 4);
			this.packagePanelLv1.Editor = this.equipEditor;
			this.packagePanelLv2.setSize(8, 4);
			this.packagePanelLv2.Editor = this.equipEditor;
			this.packagePanelLv3.setSize(8, 4);
			this.packagePanelLv3.Editor = this.equipEditor;
			this.packagePanelLv4.setSize(8, 4);
			this.packagePanelLv4.Editor = this.equipEditor;
			this.shopPanel.setSize(8, 4);
			this.shopPanel.Editor = this.equipEditor;
            this.sBookPanel.Editor = this.equipEditor;
			this.equipEditor.LoadData();
			this.cbZhiye.SelectedIndex = 0;
		}

		private string getCode()
		{
			string[] equipCodes = new string[] { "0x", this.charPanel.getEquipCodes(), this.packagePanel.getEquipCodes(), this.packagePanelLv1.getEquipCodes(), this.packagePanelLv2.getEquipCodes(), this.packagePanelLv3.getEquipCodes(), this.packagePanelLv4.getEquipCodes(), this.shopPanel.getEquipCodes(), this.sBookPanel.getEquipCodes() };
			return string.Concat(equipCodes);
		}

		public static frmInitEquip GetInstance()
		{
			if (frmInitEquip.form == null)
			{
				frmInitEquip.form = new frmInitEquip();
			}
			return frmInitEquip.form;
		}

		private void init()
		{
			string str = "SELECT text FROM sys.syscomments WHERE (id = OBJECT_ID('T_HE_INSERT_Character_Inventory'))";
			try
			{
				OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
				StringBuilder stringBuilder = new StringBuilder();
				while (oleDbDataReader.Read())
				{
					stringBuilder.Append(Convert.ToString(oleDbDataReader.GetValue(0)));
				}
				if (stringBuilder.ToString().Trim() == "")
				{
					for (int i = 0; i < (int)this.strCodes.Length; i++)
					{
						this.strCodes[i] = this.strCode;
						this.strLoads[i] = this.strCode;
					}
				}
				else
				{
					Match match = Regex.Match(stringBuilder.ToString(), "CREATE TRIGGER T_HE_INSERT_Character_Inventory\r\nON Character\r\nFOR INSERT\r\nAS\r\nBEGIN TRANSACTION\r\nDECLARE @Cls tinyint, @Lev smallint, @Name varchar\\(10\\)\r\nSELECT @Cls = Class, @Lev = cLevel, @Name = Name FROM INSERTED\r\nIF @Lev > 1\r\nIF @Cls = 0\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 16\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 32\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 48\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 64\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 80\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE IF @Cls = 96\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nELSE\r\nUPDATE Character SET Inventory = (0x[0-9A-F]{3776}) WHERE (Name = @Name)\r\nCOMMIT TRANSACTION", RegexOptions.IgnoreCase);
					if (!match.Success)
					{
						for (int j = 0; j < (int)this.strCodes.Length; j++)
						{
							this.strCodes[j] = this.strCode;
							this.strLoads[j] = this.strCode;
						}
					}
					else
					{
						for (int k = 0; k < (int)this.strCodes.Length; k++)
						{
							this.strCodes[k] = match.Groups[k + 1].Value;
							this.strLoads[k] = this.strCodes[k];
						}
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				Utils.WarningMessage(string.Concat("SQL：", str, "\nError:", exception.Message));
			}
		}

		private void InitializeComponent()
		{
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(frmInitEquip));
			this.pnlPackage = new Panel();
            this.sBookPanel = new PentagramPanel();
			this.btnClearChar = new Button();
			this.btnCleanPackage = new Button();
			this.btnClearPackage = new Button();
			this.chkAll = new CheckBox();
			this.btnSave = new Button();
			this.label1 = new Label();
			this.cbZhiye = new ComboBox();
			this.charPanel = new CharPanel();
			this.packagePanel = new EquipPanel();
			this.packagePanelLv1 = new EquipPanel();
			this.packagePanelLv2 = new EquipPanel();
			this.packagePanelLv3 = new EquipPanel();
			this.packagePanelLv4 = new EquipPanel();
			this.shopPanel = new EquipPanel();
			this.groupBox2 = new GroupBox();
			this.equipEditor = new EquipEditor();
			this.pnlPackage.SuspendLayout();
			this.groupBox2.SuspendLayout();
			base.SuspendLayout();
			this.pnlPackage.BackColor = Color.FromArgb(32, 27, 23);
			this.pnlPackage.BorderStyle = BorderStyle.Fixed3D;
            this.pnlPackage.Controls.Add(this.sBookPanel);
			this.pnlPackage.Controls.Add(this.btnClearChar);
			this.pnlPackage.Controls.Add(this.btnCleanPackage);
			this.pnlPackage.Controls.Add(this.btnClearPackage);
			this.pnlPackage.Controls.Add(this.chkAll);
			this.pnlPackage.Controls.Add(this.btnSave);
			this.pnlPackage.Controls.Add(this.label1);
			this.pnlPackage.Controls.Add(this.cbZhiye);
			this.pnlPackage.Controls.Add(this.charPanel);
			this.pnlPackage.Controls.Add(this.packagePanel);
			this.pnlPackage.Controls.Add(this.packagePanelLv1);
			this.pnlPackage.Controls.Add(this.packagePanelLv2);
			this.pnlPackage.Controls.Add(this.packagePanelLv3);
			this.pnlPackage.Controls.Add(this.packagePanelLv4);
			this.pnlPackage.Controls.Add(this.shopPanel);
			this.pnlPackage.Location = new Point(231, 4);
			this.pnlPackage.Name = "pnlPackage";
			this.pnlPackage.Size = new System.Drawing.Size(509, 497);
			this.pnlPackage.TabIndex = 21;
            this.sBookPanel.BackgroundImage = Resources.skillbook;
            this.sBookPanel.BackgroundImageLayout = ImageLayout.None;
            this.sBookPanel.Cursor = Cursors.Default;
            this.sBookPanel.Enabled = false;
            this.sBookPanel.Location = new Point(228, 217);
            this.sBookPanel.Margin = new System.Windows.Forms.Padding(0);
            this.sBookPanel.Name = "sBookPanel";
            this.sBookPanel.Prof = -1;
            this.sBookPanel.Size = new System.Drawing.Size(58, 58);
            this.sBookPanel.TabIndex = 89;
			this.btnClearChar.BackColor = Color.FromArgb(64, 64, 64);
			this.btnClearChar.FlatStyle = FlatStyle.Popup;
			this.btnClearChar.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			this.btnClearChar.ForeColor = Color.White;
			this.btnClearChar.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnClearChar.Location = new Point(311, 385);
			this.btnClearChar.Name = "btnClearChar";
			this.btnClearChar.Size = new System.Drawing.Size(65, 25);
			this.btnClearChar.TabIndex = 84;
			this.btnClearChar.Text = "清空人物";
			this.btnClearChar.UseVisualStyleBackColor = false;
			this.btnClearChar.Click += new EventHandler(this.btnClearChar_Click);
			this.btnCleanPackage.BackColor = Color.FromArgb(64, 64, 64);
			this.btnCleanPackage.FlatStyle = FlatStyle.Popup;
			this.btnCleanPackage.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			this.btnCleanPackage.ForeColor = Color.White;
			this.btnCleanPackage.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnCleanPackage.Location = new Point(453, 385);
			this.btnCleanPackage.Name = "btnCleanPackage";
			this.btnCleanPackage.Size = new System.Drawing.Size(42, 25);
			this.btnCleanPackage.TabIndex = 83;
			this.btnCleanPackage.Text = "整理";
			this.btnCleanPackage.UseVisualStyleBackColor = false;
			this.btnCleanPackage.Click += new EventHandler(this.btnCleanPackage_Click);
			this.btnClearPackage.BackColor = Color.FromArgb(64, 64, 64);
			this.btnClearPackage.FlatStyle = FlatStyle.Popup;
			this.btnClearPackage.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			this.btnClearPackage.ForeColor = Color.White;
			this.btnClearPackage.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnClearPackage.Location = new Point(382, 385);
			this.btnClearPackage.Name = "btnClearPackage";
			this.btnClearPackage.Size = new System.Drawing.Size(65, 25);
			this.btnClearPackage.TabIndex = 82;
			this.btnClearPackage.Text = "清空包裹";
			this.btnClearPackage.UseVisualStyleBackColor = false;
			this.btnClearPackage.Click += new EventHandler(this.btnClearPackage_Click);
			this.chkAll.AutoSize = true;
			this.chkAll.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.chkAll.ForeColor = Color.Yellow;
			this.chkAll.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.chkAll.Location = new Point(311, 441);
			this.chkAll.Name = "chkAll";
			this.chkAll.Size = new System.Drawing.Size(183, 21);
			this.chkAll.TabIndex = 81;
			this.chkAll.Text = "所有职业统一送当前所示装备";
			this.chkAll.UseVisualStyleBackColor = true;
			this.btnSave.BackColor = Color.FromArgb(64, 64, 64);
			this.btnSave.FlatStyle = FlatStyle.Popup;
			this.btnSave.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			this.btnSave.ForeColor = Color.White;
			this.btnSave.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnSave.Location = new Point(368, 465);
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size(73, 25);
			this.btnSave.TabIndex = 80;
			this.btnSave.TabStop = false;
			this.btnSave.Text = "保存设置";
			this.btnSave.UseVisualStyleBackColor = false;
			this.btnSave.Click += new EventHandler(this.btnSave_Click);
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("微软雅黑", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label1.ForeColor = Color.Yellow;
			this.label1.Location = new Point(308, 418);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(68, 17);
			this.label1.TabIndex = 79;
			this.label1.Text = "加载数据：";
			this.cbZhiye.DropDownHeight = 206;
			this.cbZhiye.DropDownStyle = ComboBoxStyle.DropDownList;
			this.cbZhiye.FormattingEnabled = true;
			this.cbZhiye.IntegralHeight = false;
			ComboBox.ObjectCollection items = this.cbZhiye.Items;
			object[] objArray = new object[] { "魔法师", "剑士", "弓箭手", "魔剑士", "圣导师", "召唤", "决斗士" };
			items.AddRange(objArray);
			this.cbZhiye.Location = new Point(378, 416);
			this.cbZhiye.Name = "cbZhiye";
			this.cbZhiye.Size = new System.Drawing.Size(69, 20);
			this.cbZhiye.TabIndex = 78;
			this.cbZhiye.TabStop = false;
			this.cbZhiye.SelectedIndexChanged += new EventHandler(this.cbZhiye_SelectedIndexChanged);
			this.charPanel.BackgroundImage = Resources.char_2;
			this.charPanel.BackgroundImageLayout = ImageLayout.None;
			this.charPanel.Cursor = Cursors.Default;
			this.charPanel.Location = new Point(0, -1);
			this.charPanel.Margin = new System.Windows.Forms.Padding(0);
			this.charPanel.Name = "charPanel";
			this.charPanel.Prof = -1;
			this.charPanel.Size = new System.Drawing.Size(295, 284);
			this.charPanel.TabIndex = 13;
			this.charPanel.MouseLeave += new EventHandler(this.charPanel_MouseLeave);
			this.packagePanel.BackgroundImage = Resources.warehouse_2;
			this.packagePanel.BackgroundImageLayout = ImageLayout.None;
			this.packagePanel.Cursor = Cursors.Default;
			this.packagePanel.Location = new Point(45, 283);
			this.packagePanel.Margin = new System.Windows.Forms.Padding(0);
			this.packagePanel.Name = "packagePanel";
			this.packagePanel.Size = new System.Drawing.Size(209, 209);
			this.packagePanel.TabIndex = 14;
			this.packagePanel.MouseLeave += new EventHandler(this.packagePanel_MouseLeave);
			this.packagePanelLv1.BackgroundImage = Resources.warehouse_2;
			this.packagePanelLv1.BackgroundImageLayout = ImageLayout.None;
			this.packagePanelLv1.Cursor = Cursors.Default;
			this.packagePanelLv1.Enabled = false;
			this.packagePanelLv1.Location = new Point(295, 0);
			this.packagePanelLv1.Margin = new System.Windows.Forms.Padding(0);
			this.packagePanelLv1.Name = "packagePanelLv1";
			this.packagePanelLv1.Size = new System.Drawing.Size(209, 105);
			this.packagePanelLv1.TabIndex = 85;
			this.packagePanelLv2.BackgroundImage = Resources.warehouse_2;
			this.packagePanelLv2.BackgroundImageLayout = ImageLayout.None;
			this.packagePanelLv2.Cursor = Cursors.Default;
			this.packagePanelLv2.Enabled = false;
			this.packagePanelLv2.Location = new Point(295, 107);
			this.packagePanelLv2.Margin = new System.Windows.Forms.Padding(0);
			this.packagePanelLv2.Name = "packagePanelLv2";
			this.packagePanelLv2.Size = new System.Drawing.Size(209, 105);
			this.packagePanelLv2.TabIndex = 86;
			this.packagePanelLv3.BackgroundImage = Resources.warehouse_2;
			this.packagePanelLv3.BackgroundImageLayout = ImageLayout.None;
			this.packagePanelLv3.Cursor = Cursors.Default;
			this.packagePanelLv3.Location = new Point(295, 214);
			this.packagePanelLv3.Margin = new System.Windows.Forms.Padding(0);
			this.packagePanelLv3.Name = "packagePanelLv3";
			this.packagePanelLv3.Size = new System.Drawing.Size(209, 105);
			this.packagePanelLv3.TabIndex = 87;
			this.packagePanelLv3.Visible = false;
			this.packagePanelLv4.BackgroundImage = Resources.warehouse_2;
			this.packagePanelLv4.BackgroundImageLayout = ImageLayout.None;
			this.packagePanelLv4.Cursor = Cursors.Default;
			this.packagePanelLv4.Enabled = false;
			this.packagePanelLv4.Location = new Point(295, 214);
			this.packagePanelLv4.Margin = new System.Windows.Forms.Padding(0);
			this.packagePanelLv4.Name = "packagePanelLv4";
			this.packagePanelLv4.Size = new System.Drawing.Size(209, 105);
			this.packagePanelLv4.TabIndex = 88;
			this.shopPanel.BackgroundImage = Resources.warehouse_2;
			this.shopPanel.BackgroundImageLayout = ImageLayout.None;
			this.shopPanel.Cursor = Cursors.Default;
			this.shopPanel.Location = new Point(295, 214);
			this.shopPanel.Margin = new System.Windows.Forms.Padding(0);
			this.shopPanel.Name = "shopPanel";
			this.shopPanel.Size = new System.Drawing.Size(209, 105);
			this.shopPanel.TabIndex = 58;
			this.shopPanel.Visible = false;
			this.groupBox2.Controls.Add(this.equipEditor);
			this.groupBox2.Location = new Point(2, 5);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(225, 496);
			this.groupBox2.TabIndex = 77;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "人物出生送装备设置";
			this.equipEditor.AllPart = false;
			this.equipEditor.DefaultDurability = 255;
			this.equipEditor.Location = new Point(4, 17);
			this.equipEditor.Margin = new System.Windows.Forms.Padding(0);
			this.equipEditor.Name = "equipEditor";
			this.equipEditor.Size = new System.Drawing.Size(216, 450);
			this.equipEditor.TabIndex = 1;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(739, 501);
			base.Controls.Add(this.groupBox2);
			base.Controls.Add(this.pnlPackage);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmInitEquip";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterParent;
			this.Text = "人物出生送装备设置";
			base.FormClosing += new FormClosingEventHandler(this.frmInitEquip_FormClosing);
			base.FormClosed += new FormClosedEventHandler(this.frmInitEquip_FormClosed);
			base.Load += new EventHandler(this.frmInitEquip_Load);
			this.pnlPackage.ResumeLayout(false);
			this.pnlPackage.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			base.ResumeLayout(false);
		}

		private void packagePanel_MouseLeave(object sender, EventArgs e)
		{
			this.packagePanel.DownItem();
			this.packagePanelLv1.DownItem();
			this.packagePanelLv2.DownItem();
			this.packagePanelLv3.DownItem();
			this.packagePanelLv4.DownItem();
			this.strCodes[this.cbZhiye.SelectedIndex] = this.getCode();
		}
	}
}