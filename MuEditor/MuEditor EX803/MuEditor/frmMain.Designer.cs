using Library.Common;
using MuEditor.Properties;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Net;
using System.Resources;
using System.Text;
using System.Windows.Forms;

namespace MuEditor
{
    public class frmMain : frmBase
    {
        private IContainer components;

        private MenuStrip menuStrip1;

        private ToolStripMenuItem SYSTEM_MenuItem;

        private ToolStripMenuItem CharacterManager;

        private ToolStripSeparator toolStripSeparator1;

        private ToolStripMenuItem ExitEditor;

        private CheckBox cbAll;

        private TabPage tabPage4;

        private Button btnMaster;

        private Label label29;

        private CheckedListBox clbCharacter;

        private Label label10;

        private TextBox txtLeaderShip;

        private Label laName;

        private TextBox txtChar;

        private ComboBox cboClass;

        private TextBox txtLevel;

        private TextBox txtPoint;

        private TextBox txtExp;

        private TextBox txtStrength;

        private TextBox txtDexterity;

        private TextBox txtEnergy;

        private TextBox txtVitality;

        private ComboBox cboPK;

        private ComboBox cboCode;

        private TextBox txtPosY;

        private TextBox txtPosX;

        private ComboBox cboMap;

        private Button btnUpdateChar;

        private Label label24;

        private Label label23;

        private Label label22;

        private Label label21;

        private Label label20;

        private Label label19;

        private Label label18;

        private Label label17;

        private Label label16;

        private Label label15;

        private Label label14;

        private GroupBox groupBox2;

        

        private Label label13;

        private Button btnAccount;

        private CheckBox chkState;

        private Label label9;

        private TextBox txtSNO;

        private Label label8;

        private TextBox txtAnswer;

        private Label label7;

        private TextBox txtQuestion;

        private TextBox txtEMail;

        private TextBox txtPassword;

        private TextBox txtAcc;

        private Label label6;

        private Label label5;

        private Label label4;

        private Label label3;

        private TabPage tabPage3;

        private EquipEditor equipEditor;

        private TabPage tabPage5;

        private TabControl tabcInfo;

        private GroupBox groupBox1;

        private Button btnChar;

        private Button btnWarehouse;

        private ComboBox txtAccount;

        private ComboBox cmbChar;

        private Label label2;

        private Label label1;

        private Button button2;

        private TextBox txtNick;

        private Label label32;

        private GroupBox groupBox3;

        private Label lblServer;

        private Label lblDisConnectTime;

        private Label lblConnectTime;

        private Label label36;

        private Label lblState;

        private Button btnSearchIP;

        private Label lblIP;

        private Label lblOnlineHours;

        private Label label35;

        private Label label34;

        private ToolStripMenuItem OnlineStat;

        private ToolStripMenuItem GuildManager;

        private ToolStripSeparator toolStripSeparator3;

        

        

        private Button btnExp;

        private ToolStripMenuItem HELP_MenuItem;

        private ToolStripMenuItem Help;

        private ToolStripMenuItem About;

        private ToolStripSeparator toolStripSeparator5;

        private CheckBox cbSaveJN;

        private ToolStripMenuItem AddAccountID;

        private Panel pnlPackage;

        private GroupBox packageExp;

        private RadioButton PackageExpLv2;

        private RadioButton PackageExpLv1;

        private CheckBox chkPackageExp;

        private Button btnUpdatePackage;

        private Button btnClearPackage;

        private Button btnClearChar;

        private Panel panel5;

        private EquipPanel shopPanel;

        private Panel panel4;

        private EquipPanel packagePanelLv4;

        private Panel panel3;

        private EquipPanel packagePanelLv3;

        private PentagramPanel sPentagramPanel;

        private Button btnCleanPackage;

        private Button btn1YMoney;

        private Button btnMaxMoney;

        private CharPanel charPanel;

        private Panel panel0;

        private TextBox txtMoney;

        private EquipPanel packagePanel;

        private Panel panel1;

        private EquipPanel packagePanelLv1;

        private Panel panel2;

        private EquipPanel packagePanelLv2;

        private Panel pnlWarehouse;

        private CheckBox WarehouseExp;

        private EquipPanel warehousePanelLv1;

        private Button btnClean;

        private Button btnWare1YMoney;

        private Button btnWareMaxMoney;

        private Label label33;

        private TextBox txtWareHousePwd;

        private Button btnClearWarehouse;

        private Label label26;

        private TextBox txtWareHouseMoney;

        private EquipPanel warehousePanel;

        private Label label11;

        private Button btnUpdateWarehouse;

        private ToolStripSeparator toolStripSeparator2;

        private ToolStripMenuItem CashShopPoint;

        private bool accountLogin;

        private bool charLogin;

        public static string ME_SERVER;

        public static string ME_DB;

        public static string MU_SERVER;

        public static string MU_DB;

        private string lastAccount = "";

        private string lastCharName = "";

        private string wareHouseCode = "";

        private string wareHouseLv1Code = "";

        private string charPanelCode = "";

        private string packagePanelCode = "";

        private string packagePanelLv1Code = "";

        private string packagePanelLv2Code = "";

        private string packagePanelLv3Code = "";

        private string packagePanelLv4Code = "";

        private string shopPanelCode = "";

        private string sPentagramPanelCode = "";

        private string ExtInventory = "";

        private bool MD5 = true;

        private frmUser FrmUser;

        private frmGuild FrmGuild;

        private frmInitEquip FrmEquip;

        private T_CashShop_Point T_CashShop;

        public static CMagicDamage[] xMagic;

        private int rightPanelFlag;

        public bool LoadedPackage
        {
            get
            {
                return (this.rightPanelFlag & 8) != 0;
            }
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag | 8;
                    return;
                }
                this.rightPanelFlag = this.rightPanelFlag & 247;
            }
        }

        public bool LoadedWarehouse
        {
            get
            {
                return (this.rightPanelFlag & 128) != 0;
            }
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag | 128;
                    return;
                }
                this.rightPanelFlag = this.rightPanelFlag & 127;
            }
        }

        public bool PackageReset
        {
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag & 240;
                }
            }
        }

        public bool ShownPackage
        {
            get
            {
                return (this.rightPanelFlag & 2) != 0;
            }
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag | 2;
                    return;
                }
                this.rightPanelFlag = this.rightPanelFlag & 253;
            }
        }

        public bool ShownWarehouse
        {
            get
            {
                return (this.rightPanelFlag & 32) != 0;
            }
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag | 32;
                    return;
                }
                this.rightPanelFlag = this.rightPanelFlag & 223;
            }
        }

        public bool WarehouseReset
        {
            set
            {
                if (value)
                {
                    this.rightPanelFlag = this.rightPanelFlag & 15;
                }
            }
        }

        static frmMain()
        {
            frmMain.ME_SERVER = "(local)";
            frmMain.ME_DB = "Me_MuOnline";
            frmMain.MU_SERVER = "(local)";
            frmMain.MU_DB = "MuOnline";
            frmMain.xMagic = null;
        }

        public frmMain()
        {
            this.InitializeComponent();
            string str = "Data\\Skill.bmd";
            if (!File.Exists(str))
             {
                 str = string.Concat("MuEdit\\bin\\Release\\", str);
             }
             frmMain.xMagic = (new SkillClass(str)).cMagic;
        }

        private void btn1YMoney_Click(object sender, EventArgs e)
        {
            this.txtMoney.Text = "100000000";
        }

        private void btnAccount_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            string str = this.txtAcc.Text.Trim();
            this.saveAccount(str);
            this.Cursor = Cursors.Default;
        }

        private void btnChar_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.showPackage(!this.ShownPackage);
            this.Cursor = Cursors.Default;
        }

        private void btnClean_Click(object sender, EventArgs e)
        {
            this.warehousePanel.DownItem();
            EquipItem[] equipItems = this.warehousePanel.getEquipItems();
            this.warehousePanel.clearData();
            this.warehousePanel.putItems(equipItems, true);
            this.warehousePanel.Invalidate();
        }

        private void btnCleanPackage_Click(object sender, EventArgs e)
        {
            this.packagePanel.DownItem();
            this.shopPanel.DownItem();
            EquipItem[] equipItems = this.packagePanel.getEquipItems();
            this.packagePanel.clearData();
            this.packagePanel.putItems(equipItems, true);
            this.packagePanel.Invalidate();
        }

        private void btnClearChar_Click(object sender, EventArgs e)
        {
            this.charPanel.clearData();
            this.charPanel.Invalidate();
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

        private void btnClearWarehouse_Click(object sender, EventArgs e)
        {
            this.warehousePanel.clearData();
            this.warehousePanel.Invalidate();
            this.warehousePanelLv1.clearData();
            this.warehousePanelLv1.Invalidate();
        }

        private void btnExp_Click(object sender, EventArgs e)
        {
            int num = Convert.ToInt32(this.txtLevel.Text.Trim());
            if (num <= 255)
            {
                this.txtExp.Text = string.Concat((num + 9) * num * num * 10);
                return;
            }
            if (num <= 255)
            {
                if (num > 400)
                {
                    this.txtExp.Text = "0";
                }
                return;
            }
            this.txtExp.Text = string.Concat((num - 255 + 9) * (num - 255) * (num - 255) * 1000 + (num + 9) * num * num * 10);
        }

        private void btnMaster_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            if (this.isCharOnline())
            {
                this.Cursor = Cursors.Default;
                Utils.WarningMessage(string.Format("This character is currently online and cannot be modified.", this.txtChar.Text.Trim()));
            }
            frmMasterLevel _frmMasterLevel = new frmMasterLevel(this.txtChar.Text.Trim());
            _frmMasterLevel.ShowDialog();
            this.Cursor = Cursors.Default;
        }

        private void btnMaxMoney_Click(object sender, EventArgs e)
        {
            this.txtMoney.Text = "2147483647";
        }

        private void btnSearchIP_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.FrmUser = frmUser.GetInstance(this, this.lblIP.Text);
            this.FrmUser.Visible = false;
            this.FrmUser.Show(this);
            this.setManagerFrm();
            this.Cursor = Cursors.Default;
        }

        private void btnUpdateChar_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            string str = this.txtChar.Text.Trim();
            this.saveCharacter(str);
            this.cmbChar_SelectedIndexChanged(sender, e);
            this.Cursor = Cursors.Default;
        }

        private void btnUpdatePackage_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            string str = this.txtChar.Text.Trim();
            if (!this.saveInventory(str))
            {
                Utils.WarningMessage("Inventory failed to save.");
            }
            else
            {
                Utils.InfoMessage("Inventory successfully updated！");
                this.charPanelCode = this.charPanel.getEquipCodes();
                this.packagePanelCode = this.packagePanel.getEquipCodes();
                this.packagePanelLv1Code = this.packagePanelLv1.getEquipCodes();
                this.packagePanelLv2Code = this.packagePanelLv2.getEquipCodes();
                this.packagePanelLv3Code = this.packagePanelLv3.getEquipCodes();
                this.packagePanelLv4Code = this.packagePanelLv4.getEquipCodes();
                this.shopPanelCode = this.shopPanel.getEquipCodes();
                this.sPentagramPanelCode = this.sPentagramPanel.getEquipCodes();
            }
            this.Cursor = Cursors.Default;
        }

        private void btnUpdateWarehouse_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            if (!this.saveWarehouse(this.txtAcc.Text.Trim()))
            {
                Utils.WarningMessage("Error: Warehouse update failed.");
            }
            else
            {
                Utils.InfoMessage("Warehouse successfully updated！");
                this.wareHouseCode = this.warehousePanel.getEquipCodes();
                this.wareHouseLv1Code = this.warehousePanelLv1.getEquipCodes();
            }
            this.Cursor = Cursors.Default;
        }

        private void btnWare1YMoney_Click(object sender, EventArgs e)
        {
            this.txtWareHouseMoney.Text = "100000000";
        }

        private void btnWarehouse_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.showWarehouse(!this.ShownWarehouse);
            this.Cursor = Cursors.Default;
        }

        private void btnWareMaxMoney_Click(object sender, EventArgs e)
        {
            this.txtWareHouseMoney.Text = "2147483647";
        }

        public static string ByteToString(byte[] Characters, int cLength)
        {
            return Encoding.GetEncoding("GB2312").GetString(Characters, 0, cLength).Replace("\0", " ").TrimEnd(new char[0]);
        }

        private void CashShopPoint_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.T_CashShop = new T_CashShop_Point()
            {
                Visible = false
            };
            this.T_CashShop.Show(this);
            this.Cursor = Cursors.Default;
        }

        private void cbAll_CheckedChanged(object sender, EventArgs e)
        {
            for (int i = 0; i < this.clbCharacter.Items.Count; i++)
            {
                this.clbCharacter.SetItemChecked(i, this.cbAll.Checked);
            }
        }

        private void cboClass_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.loadMagic(this.cboClass.SelectedIndex);
        }

        private bool CheckTable(OleDbConnection conn, string tableName)
        {
            if ((int)conn.GetSchema("Tables").Select(string.Format("TABLE_TYPE = 'TABLE' and TABLE_NAME = '{0}'", tableName)).Length > 0)
            {
                return true;
            }
            return false;
        }

        private void chkPackageExp_CheckedChanged(object sender, EventArgs e)
        {
            if (this.chkPackageExp.Checked)
            {
                this.PackageExpLv1.Enabled = true;
                this.PackageExpLv2.Enabled = true;
                return;
            }
            this.ExtInventory = "0";
            this.PackageExpLv1.Enabled = false;
            this.PackageExpLv2.Enabled = false;
            this.PackageExpLv1.Checked = false;
            this.PackageExpLv2.Checked = false;
        }

        private void clearGDI(bool isChar)
        {
            this.accountLogin = false;
            this.charLogin = false;
            this.btnUpdateChar.Enabled = false;
            this.btnUpdatePackage.Enabled = false;
            this.btnClearPackage.Enabled = false;
            this.charPanel.clearData();
            this.charPanel.Invalidate();
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
            this.shopPanel.clearData();
            this.shopPanel.Invalidate();
            this.sPentagramPanel.clearData();
            this.sPentagramPanel.Invalidate();
            this.charPanelCode = "";
            this.packagePanelCode = "";
            this.packagePanelLv1Code = "";
            this.packagePanelLv2Code = "";
            this.packagePanelLv3Code = "";
            this.packagePanelLv4Code = "";
            this.shopPanelCode = "";
            this.sPentagramPanelCode = "";
            if (!isChar)
            {
                this.btnUpdateWarehouse.Enabled = false;
                this.btnClearWarehouse.Enabled = false;
                this.warehousePanel.clearData();
                this.warehousePanel.Invalidate();
                this.wareHouseCode = "";
                this.warehousePanelLv1.clearData();
                this.warehousePanelLv1.Invalidate();
                this.wareHouseLv1Code = "";
            }
        }

        private void cmbChar_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '\r')
            {
                this.InputCharacter(this.cmbChar.Text.Trim());
            }
        }

        private void cmbChar_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.saveLast(true);
            this.showCharacter(this.cmbChar.Text);
            this.LoadedPackage = false;
            if (this.ShownPackage)
            {
                this.showPackage(true);
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

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                frmBase.Mu_Conn.Close();
                frmBase.Me_Conn.Close();
            }
            catch (Exception exception)
            {
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Console.WriteLine(frmMain.ByteToString(frmMain.xMagic[1].Name, 32));
            Console.WriteLine(frmMain.ByteToString(EquipEditor.xItem[1].Name, 30));
            Console.WriteLine(frmMain.ByteToString(EquipEditor.xSocket[1].捞抚, 64));
            IniClass iniClass = new IniClass(".\\config.ini");
            string str = "";
            try
            {
                string str1 = iniClass.IniReadValue("Me_MuOnline", "EnableTrusted", "1");
                frmMain.ME_SERVER = iniClass.IniReadValue("Me_MuOnline", "SERVER", "(local)");
                if (frmMain.ME_SERVER == "(local)" || frmMain.ME_SERVER == "localhost")
                {
                    frmMain.ME_SERVER = Dns.GetHostName().ToUpperInvariant();
                }
                string str2 = iniClass.IniReadValue("Me_MuOnline", "PORT", "1433");
                frmMain.ME_DB = iniClass.IniReadValue("Me_MuOnline", "ME_DB", "Me_MuOnline");
                string str3 = iniClass.IniReadValue("Me_MuOnline", "USER", "sa");
                string str4 = iniClass.IniReadValue("Me_MuOnline", "PASS", "sa");
                str = "";
                if (str1 != "1")
                {
                    object[] mESERVER = new object[] { frmMain.ME_SERVER, str2, frmMain.ME_DB, str3, str4 };
                    str = string.Format("Provider=SQLOLEDB.1;Data Source={0},{1};Initial Catalog={2};Uid={3};Pwd={4}", mESERVER);
                }
                else
                {
                    str = string.Format("Provider=SQLOLEDB.1;Data Source={0};Initial Catalog={1};Integrated Security=SSPI;", frmMain.ME_SERVER, frmMain.ME_DB);
                }
                frmBase.Me_Conn.ConnectionString = str;
                frmBase.Me_Conn.Open();
                str1 = iniClass.IniReadValue("MuOnline", "EnableTrusted", "1");
                frmMain.MU_SERVER = iniClass.IniReadValue("MuOnline", "SERVER", "(local)");
                if (frmMain.MU_SERVER == "(local)" || frmMain.MU_SERVER == "localhost")
                {
                    frmMain.MU_SERVER = Dns.GetHostName().ToUpperInvariant();
                }
                str2 = iniClass.IniReadValue("MuOnline", "PORT", "1433");
                frmMain.MU_DB = iniClass.IniReadValue("MuOnline", "MU_DB", "MuOnline");
                str3 = iniClass.IniReadValue("MuOnline", "USER", "sa");
                str4 = iniClass.IniReadValue("MuOnline", "PASS", "sa");
                str = "";
                if (str1 != "1")
                {
                    object[] mUSERVER = new object[] { frmMain.MU_SERVER, str2, frmMain.MU_DB, str3, str4 };
                    str = string.Format("Provider=SQLOLEDB.1;Data Source={0},{1};Initial Catalog={2};Uid={3};Pwd={4}", mUSERVER);
                }
                else
                {
                    str = string.Format("Provider=SQLOLEDB.1;Data Source={0};Initial Catalog={1};Integrated Security=SSPI;", frmMain.MU_SERVER, frmMain.MU_DB);
                }
                frmBase.Mu_Conn.ConnectionString = str;
                frmBase.Mu_Conn.Open();
                if (!this.CheckTable(frmBase.Mu_Conn, "ItemLog"))
                {
                    (new OleDbCommand("CREATE TABLE [dbo].[ItemLog] (\r\n\t[SEQ] [int] IDENTITY (1, 1) NOT NULL,\r\n\t[Acc] [varchar] (10) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[Name] [varchar] (10) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[ItemCode] [varbinary] (32) NULL,\r\n\t[SN] [int] NULL,\r\n\t[iName] [varchar] (50) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[iLvl] [varchar] (50) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[iSkill] [smallint] NULL,\r\n\t[iLuck] [smallint] NULL,\r\n\t[iExt] [varchar] (500) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[iSet] [smallint] NULL,\r\n\t[i380] [smallint] NULL,\r\n\t[iJh] [smallint] NULL,\r\n\t[SentDate] [smalldatetime] NULL \r\n) ON [PRIMARY]\r\nALTER TABLE [dbo].[ItemLog] ADD  DEFAULT (getdate()) FOR [SentDate]\r\n", frmBase.Mu_Conn)).ExecuteNonQuery();
                }
                if (!this.CheckTable(frmBase.Mu_Conn, "CashLog"))
                {
                    (new OleDbCommand("CREATE TABLE [dbo].[CashLog] (\r\n\t[ID] [int] IDENTITY (1, 1) NOT NULL,\r\n\t[UserID] [varchar] (16) COLLATE Chinese_PRC_CS_AS_KS_WS NULL,\r\n\t[Amount] [money] NULL,\r\n\t[SentDate] [smalldatetime] NULL \r\n) ON [PRIMARY]\r\nALTER TABLE [dbo].[CashLog] ADD  DEFAULT (getdate()) FOR [SentDate]\r\n", frmBase.Mu_Conn)).ExecuteNonQuery();
                }
                object obj = (new OleDbCommand("SELECT MIN(SN) AS SN FROM ItemLog", frmBase.Mu_Conn)).ExecuteScalar();
                Utils.SN = (obj == DBNull.Value ? 0 : Convert.ToInt32(obj));
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                Utils.WarningMessage(string.Concat("Database connection error，Error message：" + exception.Message + "\n using database connection：", str));
            }
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
            this.sPentagramPanel.Editor = this.equipEditor;
            this.warehousePanel.setSize(8, 15);
            this.warehousePanel.Editor = this.equipEditor;
            this.warehousePanelLv1.setSize(8, 15);
            this.warehousePanelLv1.Editor = this.equipEditor;
            this.equipEditor.LoadData();
            this.updateUI();
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.saveLast(false);
        }

        private void InitializeComponent()
        {
            ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(frmMain));
            this.menuStrip1 = new MenuStrip();
            this.SYSTEM_MenuItem = new ToolStripMenuItem();
            this.AddAccountID = new ToolStripMenuItem();
            this.CharacterManager = new ToolStripMenuItem();
            this.toolStripSeparator2 = new ToolStripSeparator();
            this.CashShopPoint = new ToolStripMenuItem();
            this.toolStripSeparator1 = new ToolStripSeparator();
            this.GuildManager = new ToolStripMenuItem();
            this.toolStripSeparator3 = new ToolStripSeparator();
            this.OnlineStat = new ToolStripMenuItem();
            this.toolStripSeparator5 = new ToolStripSeparator();
            this.ExitEditor = new ToolStripMenuItem();
            this.HELP_MenuItem = new ToolStripMenuItem();
            this.Help = new ToolStripMenuItem();
            this.About = new ToolStripMenuItem();
            this.cbAll = new CheckBox();
            this.tabPage4 = new TabPage();
            this.cbSaveJN = new CheckBox();
            this.btnExp = new Button();
            this.btnMaster = new Button();
            this.label29 = new Label();
            this.clbCharacter = new CheckedListBox();
            this.label10 = new Label();
            this.txtLeaderShip = new TextBox();
            this.laName = new Label();
            this.txtChar = new TextBox();
            this.cboClass = new ComboBox();
            this.txtLevel = new TextBox();
            this.txtPoint = new TextBox();
            this.txtExp = new TextBox();
            this.txtStrength = new TextBox();
            this.txtDexterity = new TextBox();
            this.txtEnergy = new TextBox();
            this.txtVitality = new TextBox();
            this.cboPK = new ComboBox();
            this.cboCode = new ComboBox();
            this.txtPosY = new TextBox();
            this.txtPosX = new TextBox();
            this.cboMap = new ComboBox();
            this.btnUpdateChar = new Button();
            this.label24 = new Label();
            this.label23 = new Label();
            this.label22 = new Label();
            this.label21 = new Label();
            this.label20 = new Label();
            this.label19 = new Label();
            this.label18 = new Label();
            this.label17 = new Label();
            this.label16 = new Label();
            this.label15 = new Label();
            this.label14 = new Label();
            this.groupBox2 = new GroupBox();
            
            
            this.txtNick = new TextBox();
            this.label32 = new Label();
            
            this.label13 = new Label();
            this.btnAccount = new Button();
            this.chkState = new CheckBox();
            this.label9 = new Label();
            this.txtSNO = new TextBox();
            this.label8 = new Label();
            this.txtAnswer = new TextBox();
            this.label7 = new Label();
            this.txtQuestion = new TextBox();
            this.txtEMail = new TextBox();
            this.txtPassword = new TextBox();
            this.txtAcc = new TextBox();
            this.label6 = new Label();
            this.label5 = new Label();
            this.label4 = new Label();
            this.label3 = new Label();
            this.tabPage3 = new TabPage();
            this.groupBox3 = new GroupBox();
            this.label35 = new Label();
            this.label34 = new Label();
            this.btnSearchIP = new Button();
            this.lblIP = new Label();
            this.lblOnlineHours = new Label();
            this.lblDisConnectTime = new Label();
            this.lblConnectTime = new Label();
            this.label36 = new Label();
            this.lblState = new Label();
            this.lblServer = new Label();
            this.tabPage5 = new TabPage();
            this.equipEditor = new EquipEditor();
            this.tabcInfo = new TabControl();
            this.groupBox1 = new GroupBox();
            this.btnChar = new Button();
            this.btnWarehouse = new Button();
            this.txtAccount = new ComboBox();
            this.cmbChar = new ComboBox();
            this.label2 = new Label();
            this.label1 = new Label();
            this.button2 = new Button();
            this.pnlPackage = new Panel();
            this.packageExp = new GroupBox();
            this.PackageExpLv2 = new RadioButton();
            this.PackageExpLv1 = new RadioButton();
            this.chkPackageExp = new CheckBox();
            this.btnUpdatePackage = new Button();
            this.btnClearPackage = new Button();
            this.btnClearChar = new Button();
            this.panel5 = new Panel();
            this.shopPanel = new EquipPanel();
            this.panel4 = new Panel();
            this.packagePanelLv4 = new EquipPanel();
            this.panel3 = new Panel();
            this.packagePanelLv3 = new EquipPanel();
            this.sPentagramPanel = new PentagramPanel();
            this.btnCleanPackage = new Button();
            this.btn1YMoney = new Button();
            this.btnMaxMoney = new Button();
            this.charPanel = new CharPanel();
            this.panel0 = new Panel();
            this.txtMoney = new TextBox();
            this.packagePanel = new EquipPanel();
            this.panel1 = new Panel();
            this.packagePanelLv1 = new EquipPanel();
            this.panel2 = new Panel();
            this.packagePanelLv2 = new EquipPanel();
            this.pnlWarehouse = new Panel();
            this.WarehouseExp = new CheckBox();
            this.warehousePanelLv1 = new EquipPanel();
            this.btnClean = new Button();
            this.btnWare1YMoney = new Button();
            this.btnWareMaxMoney = new Button();
            this.label33 = new Label();
            this.txtWareHousePwd = new TextBox();
            this.btnClearWarehouse = new Button();
            this.label26 = new Label();
            this.txtWareHouseMoney = new TextBox();
            this.warehousePanel = new EquipPanel();
            this.label11 = new Label();
            this.btnUpdateWarehouse = new Button();
            this.menuStrip1.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabcInfo.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.pnlPackage.SuspendLayout();
            this.packageExp.SuspendLayout();
            this.panel5.SuspendLayout();
            this.panel4.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel0.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.pnlWarehouse.SuspendLayout();
            base.SuspendLayout();
            this.menuStrip1.BackColor = SystemColors.ActiveBorder;
            this.menuStrip1.BackgroundImageLayout = ImageLayout.None;
            ToolStripItemCollection items = this.menuStrip1.Items;
            ToolStripItem[] sYSTEMMenuItem = new ToolStripItem[] { this.SYSTEM_MenuItem, this.HELP_MenuItem };
            items.AddRange(sYSTEMMenuItem);
            this.menuStrip1.Location = new Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new Size(1250, 25);
            this.menuStrip1.TabIndex = 14;
            this.menuStrip1.Text = "menuStrip1";
            ToolStripItemCollection dropDownItems = this.SYSTEM_MenuItem.DropDownItems;
            ToolStripItem[] addAccountID = new ToolStripItem[] { this.AddAccountID, this.toolStripSeparator2, this.CashShopPoint, this.toolStripSeparator3, this.OnlineStat, this.toolStripSeparator5, this.ExitEditor };
            dropDownItems.AddRange(addAccountID);
            this.SYSTEM_MenuItem.Name = "SYSTEM_MenuItem";
            this.SYSTEM_MenuItem.Size = new Size(59, 21);
            this.SYSTEM_MenuItem.Text = "File";
            this.AddAccountID.Name = "AddAccountID";
            this.AddAccountID.Size = new Size(142, 22);
            this.AddAccountID.Text = "Create account";
            this.AddAccountID.Click += new EventHandler(this.添加帐号NToolStripMenuItem_Click);
            this.CharacterManager.Name = "CharacterManager";
            this.CharacterManager.Size = new Size(142, 22);
            this.CharacterManager.Text = "Character manager";
            this.CharacterManager.Click += new EventHandler(this.人物查询toolStripMenuItem1_Click);
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new Size(139, 6);
            this.CashShopPoint.Name = "CashShopPoint";
            this.CashShopPoint.Size = new Size(142, 22);
            this.CashShopPoint.Text = "CashShop points";
            this.CashShopPoint.Click += new EventHandler(this.CashShopPoint_Click);
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new Size(139, 6);
            this.GuildManager.Name = "GuildManager";
            this.GuildManager.Size = new Size(142, 22);
            this.GuildManager.Text = "Guild Manager";
            this.GuildManager.Click += new EventHandler(this.战盟管理GToolStripMenuItem_Click);
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new Size(139, 6);
            this.OnlineStat.Name = "OnlineStat";
            this.OnlineStat.Size = new Size(142, 22);
            this.OnlineStat.Text = "Server Stats";
            this.OnlineStat.Click += new EventHandler(this.在线情况UToolStripMenuItem_Click);
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new Size(139, 6);
            this.ExitEditor.Name = "ExitEditor";
            this.ExitEditor.Size = new Size(142, 22);
            this.ExitEditor.Text = "Exit";
            this.ExitEditor.Click += new EventHandler(this.退出ToolStripMenuItem_Click);
            ToolStripItemCollection toolStripItemCollections = this.HELP_MenuItem.DropDownItems;
            ToolStripItem[] help = new ToolStripItem[] { this.About };
            toolStripItemCollections.AddRange(help);
            this.HELP_MenuItem.Name = "HELP_MenuItem";
            this.HELP_MenuItem.Size = new Size(61, 21);
            this.HELP_MenuItem.Text = "Help";
            this.Help.Name = "Help";
            this.Help.Size = new Size(191, 22);
            this.Help.Text = "Help";
            this.Help.Click += new EventHandler(this.如何使用HToolStripMenuItem_Click);
            this.About.Name = "About";
            this.About.Size = new Size(191, 22);
            this.About.Text = "About";
            this.About.Click += new EventHandler(this.关于AToolStripMenuItem_Click);
            this.cbAll.AutoSize = true;
            this.cbAll.ImeMode = ImeMode.NoControl;
            this.cbAll.Location = new Point(15, 211);
            this.cbAll.Name = "cbAll";
            this.cbAll.Size = new Size(48, 16);
            this.cbAll.TabIndex = 55;
            this.cbAll.Text = "Select all";
            this.cbAll.UseVisualStyleBackColor = true;
            this.cbAll.CheckedChanged += new EventHandler(this.cbAll_CheckedChanged);
            
            
            
            this.tabPage4.Controls.Add(this.btnMaster);
            this.tabPage4.Controls.Add(this.label29);
            
            this.tabPage4.Controls.Add(this.label10);
            this.tabPage4.Controls.Add(this.txtLeaderShip);
            this.tabPage4.Controls.Add(this.laName);
            this.tabPage4.Controls.Add(this.txtChar);
            this.tabPage4.Controls.Add(this.cboClass);
            this.tabPage4.Controls.Add(this.txtLevel);
            this.tabPage4.Controls.Add(this.txtPoint);
            
            this.tabPage4.Controls.Add(this.txtStrength);
            this.tabPage4.Controls.Add(this.txtDexterity);
            this.tabPage4.Controls.Add(this.txtEnergy);
            this.tabPage4.Controls.Add(this.txtVitality);
            this.tabPage4.Controls.Add(this.cboPK);
            this.tabPage4.Controls.Add(this.cboCode);
            this.tabPage4.Controls.Add(this.txtPosY);
            this.tabPage4.Controls.Add(this.txtPosX);
            this.tabPage4.Controls.Add(this.cboMap);
            this.tabPage4.Controls.Add(this.btnUpdateChar);
            this.tabPage4.Controls.Add(this.label24);
            this.tabPage4.Controls.Add(this.label23);
            this.tabPage4.Controls.Add(this.label22);
            this.tabPage4.Controls.Add(this.label21);
            this.tabPage4.Controls.Add(this.label20);
            this.tabPage4.Controls.Add(this.label19);
            this.tabPage4.Controls.Add(this.label18);
            this.tabPage4.Controls.Add(this.label17);
            this.tabPage4.Controls.Add(this.label16);
            this.tabPage4.Controls.Add(this.label15);
            
            this.tabPage4.Location = new Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new Padding(3);
            this.tabPage4.Size = new Size(216, 461);
            this.tabPage4.TabIndex = 1;
            this.tabPage4.Text = "Character info";
            this.tabPage4.UseVisualStyleBackColor = true;
            this.cbSaveJN.AutoSize = true;
            this.cbSaveJN.ImeMode = ImeMode.NoControl;
            this.cbSaveJN.Location = new Point(66, 391);
            this.cbSaveJN.Name = "cbSaveJN";
            this.cbSaveJN.Size = new Size(72, 16);
            this.cbSaveJN.TabIndex = 62;
            
            this.cbSaveJN.UseVisualStyleBackColor = true;
            this.btnExp.ImeMode = ImeMode.NoControl;
            this.btnExp.Location = new Point(171, 3);
            this.btnExp.Name = "btnExp";
            this.btnExp.Size = new Size(43, 23);
            this.btnExp.TabIndex = 60;
            this.btnExp.Text = "Exp";
            this.btnExp.UseVisualStyleBackColor = true;
            this.btnExp.Click += new EventHandler(this.btnExp_Click);
            this.btnMaster.ImeMode = ImeMode.NoControl;
            this.btnMaster.Location = new Point(32, 212);
            this.btnMaster.Name = "btnMaster";
            this.btnMaster.Size = new Size(73, 21);
            this.btnMaster.TabIndex = 54;
            this.btnMaster.Text = "Master levels";
            this.btnMaster.UseVisualStyleBackColor = true;
            this.btnMaster.Click += new EventHandler(this.btnMaster_Click);
            this.label29.AutoSize = true;
            this.label29.ImeMode = ImeMode.NoControl;
            this.label29.Location = new Point(7, 195);
            this.label29.Name = "label29";
            this.label29.Size = new Size(53, 12);
            this.label29.TabIndex = 53;
            
            this.clbCharacter.CheckOnClick = true;
            this.clbCharacter.FormattingEnabled = true;
            this.clbCharacter.Location = new Point(63, 188);
            this.clbCharacter.Name = "clbCharacter";
            this.clbCharacter.Size = new Size(146, 196);
            this.clbCharacter.TabIndex = 52;
            this.label10.AutoSize = true;
            this.label10.ImeMode = ImeMode.NoControl;
            this.label10.Location = new Point(108, 116);
            this.label10.Name = "label10";
            this.label10.Size = new Size(29, 12);
            this.label10.TabIndex = 34;
            this.label10.Text = "Com";
            this.txtLeaderShip.IsOnlyNumber = true;
            this.txtLeaderShip.Location = new Point(138, 109);
            this.txtLeaderShip.Name = "txtLeaderShip";
            this.txtLeaderShip.Size = new Size(71, 21);
            this.txtLeaderShip.TabIndex = 33;
            this.laName.AutoSize = true;
            this.laName.ImeMode = ImeMode.NoControl;
            this.laName.Location = new Point(7, 10);
            this.laName.Name = "laName";
            this.laName.Size = new Size(29, 12);
            this.laName.TabIndex = 32;
            
            this.txtChar.IsOnlyNumber = false;
            this.txtChar.Location = new Point(34, 5);
            this.txtChar.Name = "txtChar";
            this.txtChar.ReadOnly = true;
            this.txtChar.Size = new Size(68, 21);
            this.txtChar.TabIndex = 0;
            this.cboClass.DropDownHeight = 306;
            this.cboClass.DropDownStyle = ComboBoxStyle.DropDownList;
            this.cboClass.FormattingEnabled = true;
            this.cboClass.IntegralHeight = false;
            ComboBox.ObjectCollection objectCollections = this.cboClass.Items;
            object[] objArray = new object[] {
            "Dark Wizard",
            "Soul Master",
            "Grand Master",
            "Dark Knight",
            "Blade Knight",
            "Blade Master",
            "Elf",
            "Muse Elf",
            "High Elf",
            "Magic Gladiator",
            "Duel Master",
            "Dark Lord",
            "Lord Emperor",
            "Summoner",
            "Bloody Summoner",
            "Dimension Master",
            "Rage Fighter",
            "Fist Master"};
            objectCollections.AddRange(objArray);
            this.cboClass.Location = new Point(33, 32);
            this.cboClass.Name = "cboClass";
            this.cboClass.Size = new Size(69, 20);
            this.cboClass.TabIndex = 21;
            this.cboClass.SelectedIndexChanged += new EventHandler(this.cboClass_SelectedIndexChanged);
            this.txtLevel.IsOnlyNumber = true;
            this.txtLevel.Location = new Point(139, 4);
            this.txtLevel.Name = "txtLevel";
            this.txtLevel.Size = new Size(30, 21);
            this.txtLevel.TabIndex = 14;
            this.txtPoint.IsOnlyNumber = true;
            this.txtPoint.Location = new Point(33, 57);
            this.txtPoint.Name = "txtPoint";
            this.txtPoint.Size = new Size(69, 21);
            this.txtPoint.TabIndex = 16;
            this.txtExp.IsOnlyNumber = true;
            this.txtExp.Location = new Point(138, 31);
            this.txtExp.Name = "txtExp";
            this.txtExp.Size = new Size(71, 21);
            this.txtExp.TabIndex = 11;
            this.txtStrength.IsOnlyNumber = true;
            this.txtStrength.Location = new Point(138, 58);
            this.txtStrength.Name = "txtStrength";
            this.txtStrength.Size = new Size(71, 21);
            this.txtStrength.TabIndex = 12;
            this.txtDexterity.IsOnlyNumber = true;
            this.txtDexterity.Location = new Point(138, 84);
            this.txtDexterity.Name = "txtDexterity";
            this.txtDexterity.Size = new Size(71, 21);
            this.txtDexterity.TabIndex = 17;
            this.txtEnergy.IsOnlyNumber = true;
            this.txtEnergy.Location = new Point(33, 109);
            this.txtEnergy.Name = "txtEnergy";
            this.txtEnergy.Size = new Size(70, 21);
            this.txtEnergy.TabIndex = 18;
            this.txtVitality.IsOnlyNumber = true;
            this.txtVitality.Location = new Point(33, 84);
            this.txtVitality.Name = "txtVitality";
            this.txtVitality.Size = new Size(69, 21);
            this.txtVitality.TabIndex = 13;
            this.cboPK.FormattingEnabled = true;
            ComboBox.ObjectCollection items1 = this.cboPK.Items;
            object[] objArray1 = new object[] {
            "Warrior",
            "Hero",
            "2nd Stage Hero",
            "Commoner",
            "1st Stage Outlaw",
            "2nd Stage Outlaw",
            "3rd Stage Outlaw"};
            items1.AddRange(objArray1);
            this.cboPK.Location = new Point(33, 136);
            this.cboPK.Name = "cboPK";
            this.cboPK.Size = new Size(52, 20);
            this.cboPK.TabIndex = 22;
            this.cboCode.FormattingEnabled = true;
            ComboBox.ObjectCollection objectCollections1 = this.cboCode.Items;
            object[] objArray2 = new object[] {
            "Player",
            "Banned",
            "GM"};
            objectCollections1.AddRange(objArray2);
            this.cboCode.Location = new Point(138, 136);
            this.cboCode.Name = "cboCode";
            this.cboCode.Size = new Size(52, 20);
            this.cboCode.TabIndex = 23;
            this.txtPosY.IsOnlyNumber = true;
            this.txtPosY.Location = new Point(175, 162);
            this.txtPosY.Name = "txtPosY";
            this.txtPosY.Size = new Size(31, 21);
            this.txtPosY.TabIndex = 20;
            this.txtPosX.IsOnlyNumber = true;
            this.txtPosX.Location = new Point(138, 162);
            this.txtPosX.Name = "txtPosX";
            this.txtPosX.Size = new Size(31, 21);
            this.txtPosX.TabIndex = 15;
            this.cboMap.DropDownHeight = 306;
            this.cboMap.FormattingEnabled = true;
            this.cboMap.IntegralHeight = false;
            ComboBox.ObjectCollection items2 = this.cboMap.Items;
            object[] objArray3 = new object[] {
            "Lorencia",
            "Dungeon",
            "Devias",
            "Noria",
            "Elveland",
            "Elveland 2",
            "Arena",
            "Atlans",
            "Tarkan",
            "Devil Square 1, 2, 3 and 4",
            "Castle Siege",
            "Blood Castle 1",
            "Blood Castle 2",
            "Blood Castle 3",
            "Blood Castle 4",
            "Blood Castle 5",
            "Blood Castle 6",
            "Blood Castle 7",
            "Lost Tower 1",
            "Lost Tower 2",
            "Lost Tower 3",
            "Lost Tower 4",
            "Lost Tower 5",
            "Lost Tower 6",
            "Kalima 1",
            "Kalima 2",
            "Kalima 3",
            "Kalima 4",
            "Kalima 5",
            "Kalima 6",
            "Valley of Loren",
            "UNKNOWN",
            "Devil Square 5 & 6",
            "Swamp of Calmness",
            "Crywolf Fortress",
            "UNKNOWN - 35",
            "Kalima 7",
            "Kanturu Ruins",
            "Kanturu",
            "Refinery",
            "UNKNOWN - 40",
            "Balgass\' Barracks",
            "UNKNOWN",
            "UNKNOWN - 43",
            "UNKNOWN - 44",
            "Illusion Temple 1",
            "Illusion Temple 2",
            "Illusion Temple 3",
            "Illusion Temple 4",
            "Illusion Temple 5",
            "Illusion Temple 6",
            "UNKNOWN",
            "Blood Castle 8",
            "UNKNOWN 7",
            "Character select",
            "Select server",
            "Silent Map",
            "LaCleon",
            "Raklion Hatchery",
            "UNKNOWN - 59",
            "UNKNOWN - 60",
            "UNKNOWN - 61",
            "North Pole"};
            items2.AddRange(objArray3);
            this.cboMap.Location = new Point(33, 162);
            this.cboMap.Name = "cboMap";
            this.cboMap.Size = new Size(96, 20);
            this.cboMap.TabIndex = 24;
            this.btnUpdateChar.ImeMode = ImeMode.NoControl;
            this.btnUpdateChar.Location = new Point(116, 212);
            this.btnUpdateChar.Name = "btnUpdateChar";
            this.btnUpdateChar.Size = new Size(69, 21);
            this.btnUpdateChar.TabIndex = 25;
            this.btnUpdateChar.Text = "Update";
            this.btnUpdateChar.UseVisualStyleBackColor = true;
            this.btnUpdateChar.Click += new EventHandler(this.btnUpdateChar_Click);
            this.label24.AutoSize = true;
            this.label24.ImeMode = ImeMode.NoControl;
            this.label24.Location = new Point(108, 142);
            this.label24.Name = "label24";
            this.label24.Size = new Size(29, 12);
            this.label24.TabIndex = 10;
            this.label24.Text = "Type";
            this.label23.AutoSize = true;
            this.label23.ImeMode = ImeMode.NoControl;
            this.label23.Location = new Point(7, 168);
            this.label23.Name = "label23";
            this.label23.Size = new Size(29, 12);
            this.label23.TabIndex = 9;
            this.label23.Text = "Map";
            this.label22.AutoSize = true;
            this.label22.ImeMode = ImeMode.NoControl;
            this.label22.Location = new Point(7, 116);
            this.label22.Name = "label22";
            this.label22.Size = new Size(29, 12);
            this.label22.TabIndex = 8;
            this.label22.Text = "INT";
            this.label21.AutoSize = true;
            this.label21.ImeMode = ImeMode.NoControl;
            this.label21.Location = new Point(7, 142);
            this.label21.Name = "label21";
            this.label21.Size = new Size(29, 12);
            this.label21.TabIndex = 7;
            this.label21.Text = "PK";
            this.label20.AutoSize = true;
            this.label20.ImeMode = ImeMode.NoControl;
            this.label20.Location = new Point(108, 90);
            this.label20.Name = "label20";
            this.label20.Size = new Size(29, 12);
            this.label20.TabIndex = 6;
            this.label20.Text = "AGI";
            this.label19.AutoSize = true;
            this.label19.ImeMode = ImeMode.NoControl;
            this.label19.Location = new Point(7, 90);
            this.label19.Name = "label19";
            this.label19.Size = new Size(29, 12);
            this.label19.TabIndex = 5;
            this.label19.Text = "VIT";
            this.label18.AutoSize = true;
            this.label18.ImeMode = ImeMode.NoControl;
            this.label18.Location = new Point(7, 63);
            this.label18.Name = "label18";
            this.label18.Size = new Size(29, 12);
            this.label18.TabIndex = 4;
            this.label18.Text = "PT:";
            this.label17.AutoSize = true;
            this.label17.ImeMode = ImeMode.NoControl;
            this.label17.Location = new Point(108, 65);
            this.label17.Name = "label17";
            this.label17.Size = new Size(29, 12);
            this.label17.TabIndex = 3;
            this.label17.Text = "STR";
            this.label16.AutoSize = true;
            this.label16.ImeMode = ImeMode.NoControl;
            this.label16.Location = new Point(7, 37);
            this.label16.Name = "label16";
            this.label16.Size = new Size(29, 12);
            this.label16.TabIndex = 2;
            
            this.label15.AutoSize = true;
            this.label15.ImeMode = ImeMode.NoControl;
            this.label15.Location = new Point(107, 10);
            this.label15.Name = "label15";
            this.label15.Size = new Size(29, 12);
            this.label15.TabIndex = 1;
            this.label15.Text = "LVL:";
            this.label14.AutoSize = true;
            this.label14.ImeMode = ImeMode.NoControl;
            this.label14.Location = new Point(108, 37);
            this.label14.Name = "label14";
            this.label14.Size = new Size(29, 12);
            this.label14.TabIndex = 0;
            this.label14.Text = "EXP";
            
            
            this.groupBox2.Controls.Add(this.txtNick);
            this.groupBox2.Controls.Add(this.label32);
            
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.btnAccount);
            this.groupBox2.Controls.Add(this.chkState);
            this.groupBox2.Controls.Add(this.label9);
            
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.txtAnswer);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.txtQuestion);
            this.groupBox2.Controls.Add(this.txtEMail);
            this.groupBox2.Controls.Add(this.txtPassword);
            this.groupBox2.Controls.Add(this.txtAcc);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new Point(6, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new Size(202, 283);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Account information";
            
            
            this.txtNick.IsOnlyNumber = false;
            this.txtNick.Location = new Point(69, 68);
            this.txtNick.MaxLength = 10;
            this.txtNick.Name = "txtNick";
            this.txtNick.Size = new Size(110, 21);
            this.txtNick.TabIndex = 25;
            this.label32.AutoSize = true;
            this.label32.ImeMode = ImeMode.NoControl;
            this.label32.Location = new Point(13, 71);
            this.label32.Name = "label32";
            this.label32.Size = new Size(41, 12);
            this.label32.TabIndex = 24;
            this.label32.Text = "Nick：";

            this.label13.AutoSize = true;
            this.label13.ImeMode = ImeMode.NoControl;
            this.label13.Location = new Point(12, 225);
            this.label13.Name = "label13";
            this.label13.Size = new Size(41, 12);
            this.label13.TabIndex = 21;
            
            this.btnAccount.ImeMode = ImeMode.NoControl;
            this.btnAccount.Location = new Point(39, 225);
            this.btnAccount.Name = "btnAccount";
            this.btnAccount.Size = new Size(120, 46);
            this.btnAccount.TabIndex = 15;
            this.btnAccount.Text = "Update";
            this.btnAccount.UseVisualStyleBackColor = true;
            this.btnAccount.Click += new EventHandler(this.btnAccount_Click);
            this.chkState.AutoSize = true;
            this.chkState.ImeMode = ImeMode.NoControl;
            this.chkState.Location = new Point(99, 190);
            this.chkState.Name = "chkState";
            this.chkState.Size = new Size(48, 16);
            this.chkState.TabIndex = 14;
            this.chkState.Text = "Yes";
            this.chkState.UseVisualStyleBackColor = true;
            this.label9.AutoSize = true;
            this.label9.ImeMode = ImeMode.NoControl;
            this.label9.Location = new Point(40, 190);
            this.label9.Name = "label9";
            this.label9.Size = new Size(41, 12);
            this.label9.TabIndex = 13;
            this.label9.Text = "Blocked：";
            this.txtSNO.IsOnlyNumber = false;
            this.txtSNO.Location = new Point(69, 175);
            this.txtSNO.MaxLength = 18;
            this.txtSNO.Name = "txtSNO";
            this.txtSNO.Size = new Size(110, 21);
            this.txtSNO.TabIndex = 12;
            this.label8.AutoSize = true;
            this.label8.ImeMode = ImeMode.NoControl;
            this.label8.Location = new Point(13, 178);
            this.label8.Name = "label8";
            this.label8.Size = new Size(53, 12);
            this.label8.TabIndex = 11;
            
            this.txtAnswer.IsOnlyNumber = false;
            this.txtAnswer.Location = new Point(69, 148);
            this.txtAnswer.MaxLength = 50;
            this.txtAnswer.Name = "txtAnswer";
            this.txtAnswer.Size = new Size(110, 21);
            this.txtAnswer.TabIndex = 10;
            this.label7.AutoSize = true;
            this.label7.ImeMode = ImeMode.NoControl;
            this.label7.Location = new Point(13, 151);
            this.label7.Name = "label7";
            this.label7.Size = new Size(41, 12);
            this.label7.TabIndex = 9;
            this.label7.Text = "Answ：";
            this.txtQuestion.IsOnlyNumber = false;
            this.txtQuestion.Location = new Point(69, 121);
            this.txtQuestion.MaxLength = 50;
            this.txtQuestion.Name = "txtQuestion";
            this.txtQuestion.Size = new Size(110, 21);
            this.txtQuestion.TabIndex = 8;
            this.txtEMail.IsOnlyNumber = false;
            this.txtEMail.Location = new Point(69, 94);
            this.txtEMail.MaxLength = 50;
            this.txtEMail.Name = "txtEMail";
            this.txtEMail.Size = new Size(110, 21);
            this.txtEMail.TabIndex = 7;
            this.txtPassword.IsOnlyNumber = false;
            this.txtPassword.Location = new Point(69, 41);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.Size = new Size(110, 21);
            this.txtPassword.TabIndex = 6;
            this.txtAcc.IsOnlyNumber = false;
            this.txtAcc.Location = new Point(69, 14);
            this.txtAcc.Name = "txtAcc";
            this.txtAcc.ReadOnly = true;
            this.txtAcc.Size = new Size(110, 21);
            this.txtAcc.TabIndex = 5;
            this.label6.AutoSize = true;
            this.label6.ImeMode = ImeMode.NoControl;
            this.label6.Location = new Point(13, 124);
            this.label6.Name = "label6";
            this.label6.Size = new Size(41, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "Ques：";
            this.label5.AutoSize = true;
            this.label5.ImeMode = ImeMode.NoControl;
            this.label5.Location = new Point(13, 97);
            this.label5.Name = "label5";
            this.label5.Size = new Size(41, 12);
            this.label5.TabIndex = 3;
            this.label5.Text = "Mail：";
            this.label4.AutoSize = true;
            this.label4.ImeMode = ImeMode.NoControl;
            this.label4.Location = new Point(13, 44);
            this.label4.Name = "label4";
            this.label4.Size = new Size(41, 12);
            this.label4.TabIndex = 2;
            this.label4.Text = "Pass：";
            this.label3.AutoSize = true;
            this.label3.ImeMode = ImeMode.NoControl;
            this.label3.Location = new Point(13, 20);
            this.label3.Name = "label3";
            this.label3.Size = new Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "User：";
            this.tabPage3.Controls.Add(this.groupBox3);
            this.tabPage3.Controls.Add(this.groupBox2);
            this.tabPage3.Location = new Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new Padding(3);
            this.tabPage3.Size = new Size(216, 461);
            this.tabPage3.TabIndex = 0;
            this.tabPage3.Text = "Account details";
            this.tabPage3.UseVisualStyleBackColor = true;
            this.groupBox3.Controls.Add(this.label35);
            this.groupBox3.Controls.Add(this.label34);
            
            this.groupBox3.Controls.Add(this.lblIP);
            
            this.groupBox3.Controls.Add(this.lblDisConnectTime);
            this.groupBox3.Controls.Add(this.lblConnectTime);
            this.groupBox3.Controls.Add(this.label36);
            this.groupBox3.Controls.Add(this.lblState);
            this.groupBox3.Controls.Add(this.lblServer);
            this.groupBox3.Location = new Point(6, 295);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new Size(202, 159);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Server status";
            this.label35.AutoSize = true;
            this.label35.Font = new Font("Microsoft Sans Serif", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.label35.ImeMode = ImeMode.NoControl;
            this.label35.Location = new Point(3, 47);
            this.label35.Name = "label35";
            this.label35.Size = new Size(65, 12);
            this.label35.TabIndex = 19;
            this.label35.Text = "Status:";
            this.label34.AutoSize = true;
            this.label34.Font = new Font("Microsoft Sans Serif", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.label34.ImeMode = ImeMode.NoControl;
            this.label34.Location = new Point(3, 138);
            this.label34.Name = "label34";
            this.label34.Size = new Size(65, 12);
            this.label34.TabIndex = 18;
            
            this.btnSearchIP.ImeMode = ImeMode.NoControl;
            this.btnSearchIP.Location = new Point(154, 64);
            this.btnSearchIP.Name = "btnSearchIP";
            this.btnSearchIP.Size = new Size(43, 22);
            this.btnSearchIP.TabIndex = 17;
            this.btnSearchIP.Text = "Search IP";
            this.btnSearchIP.UseVisualStyleBackColor = true;
            this.btnSearchIP.Click += new EventHandler(this.btnSearchIP_Click);
            this.lblIP.BorderStyle = BorderStyle.FixedSingle;
            this.lblIP.ImeMode = ImeMode.NoControl;
            this.lblIP.Location = new Point(55, 66);
            this.lblIP.Name = "lblIP";
            this.lblIP.Size = new Size(95, 19);
            this.lblIP.TabIndex = 16;
            this.lblIP.Text = "0.0.0.0";
            this.lblIP.TextAlign = ContentAlignment.MiddleCenter;
            this.lblOnlineHours.AutoSize = true;
            this.lblOnlineHours.Font = new Font("Microsoft Sans Serif", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.lblOnlineHours.ImeMode = ImeMode.NoControl;
            this.lblOnlineHours.Location = new Point(67, 138);
            this.lblOnlineHours.Name = "lblOnlineHours";
            this.lblOnlineHours.Size = new Size(38, 12);
            this.lblOnlineHours.TabIndex = 15;
            this.lblOnlineHours.Text = "0 hours";
            this.lblDisConnectTime.AutoSize = true;
            this.lblDisConnectTime.ImeMode = ImeMode.NoControl;
            this.lblDisConnectTime.Location = new Point(3, 115);
            this.lblDisConnectTime.Name = "lblDisConnectTime";
            this.lblDisConnectTime.Size = new Size(65, 12);
            this.lblDisConnectTime.TabIndex = 14;
            this.lblDisConnectTime.Text = "Last offline：";
            this.lblConnectTime.AutoSize = true;
            this.lblConnectTime.ImeMode = ImeMode.NoControl;
            this.lblConnectTime.Location = new Point(3, 92);
            this.lblConnectTime.Name = "lblConnectTime";
            this.lblConnectTime.Size = new Size(65, 12);
            this.lblConnectTime.TabIndex = 13;
            this.lblConnectTime.Text = "Last online:";
            this.label36.AutoSize = true;
            this.label36.ImeMode = ImeMode.NoControl;
            this.label36.Location = new Point(3, 69);
            this.label36.Name = "label36";
            this.label36.Size = new Size(53, 12);
            this.label36.TabIndex = 12;
            this.label36.Text = "IP：";
            this.lblState.AutoSize = true;
            this.lblState.Font = new Font("Microsoft Sans Serif", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.lblState.ForeColor = Color.Green;
            this.lblState.ImeMode = ImeMode.NoControl;
            this.lblState.Location = new Point(74, 47);
            this.lblState.Name = "lblState";
            this.lblState.Size = new Size(44, 12);
            this.lblState.TabIndex = 11;
            this.lblState.Text = "IP:";
            this.lblServer.AutoSize = true;
            this.lblServer.ImeMode = ImeMode.NoControl;
            this.lblServer.Location = new Point(3, 23);
            this.lblServer.Name = "lblServer";
            this.lblServer.Size = new Size(53, 12);
            this.lblServer.TabIndex = 10;
            this.lblServer.Text = "Name:";
            this.tabPage5.Controls.Add(this.equipEditor);
            this.tabPage5.Location = new Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new Size(216, 461);
            this.tabPage5.TabIndex = 2;
            this.tabPage5.Text = "Item info";
            this.tabPage5.UseVisualStyleBackColor = true;
            this.equipEditor.AllPart = false;
            this.equipEditor.DefaultDurability = 255;
            this.equipEditor.Location = new Point(-1, 4);
            this.equipEditor.Margin = new Padding(0);
            this.equipEditor.Name = "equipEditor";
            this.equipEditor.Size = new Size(216, 457);
            this.equipEditor.TabIndex = 0;
            this.tabcInfo.Controls.Add(this.tabPage3);
            this.tabcInfo.Controls.Add(this.tabPage4);
            this.tabcInfo.Controls.Add(this.tabPage5);
            this.tabcInfo.Enabled = false;
            this.tabcInfo.Location = new Point(6, 87);
            this.tabcInfo.Name = "tabcInfo";
            this.tabcInfo.SelectedIndex = 0;
            this.tabcInfo.Size = new Size(224, 487);
            this.tabcInfo.TabIndex = 18;
            this.groupBox1.Controls.Add(this.btnChar);
            this.groupBox1.Controls.Add(this.btnWarehouse);
            this.groupBox1.Controls.Add(this.txtAccount);
            this.groupBox1.Controls.Add(this.cmbChar);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new Point(6, 20);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new Size(224, 64);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.btnChar.ImeMode = ImeMode.NoControl;
            this.btnChar.Location = new Point(156, 38);
            this.btnChar.Name = "btnChar";
            this.btnChar.Size = new Size(62, 21);
            this.btnChar.TabIndex = 5;
            this.btnChar.Text = "Inventory";
            this.btnChar.UseVisualStyleBackColor = true;
            this.btnChar.Click += new EventHandler(this.btnChar_Click);
            this.btnWarehouse.ImeMode = ImeMode.NoControl;
            this.btnWarehouse.Location = new Point(156, 14);
            this.btnWarehouse.Name = "btnWarehouse";
            this.btnWarehouse.Size = new Size(62, 21);
            this.btnWarehouse.TabIndex = 4;
            this.btnWarehouse.Text = "Valut";
            this.btnWarehouse.UseVisualStyleBackColor = true;
            this.btnWarehouse.Click += new EventHandler(this.btnWarehouse_Click);
            this.txtAccount.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            this.txtAccount.AutoCompleteSource = AutoCompleteSource.ListItems;
            this.txtAccount.FormattingEnabled = true;
            this.txtAccount.Location = new Point(46, 14);
            this.txtAccount.MaxLength = 10;
            this.txtAccount.Name = "txtAccount";
            this.txtAccount.Size = new Size(103, 20);
            this.txtAccount.TabIndex = 2;
            this.txtAccount.SelectedIndexChanged += new EventHandler(this.txtAccount_SelectedIndexChanged);
            this.txtAccount.TextChanged += new EventHandler(this.txtAccount_TextChanged);
            this.txtAccount.KeyPress += new KeyPressEventHandler(this.txtAccount_KeyPress);
            this.cmbChar.FormattingEnabled = true;
            this.cmbChar.Location = new Point(46, 39);
            this.cmbChar.MaxLength = 10;
            this.cmbChar.Name = "cmbChar";
            this.cmbChar.Size = new Size(103, 20);
            this.cmbChar.TabIndex = 3;
            this.cmbChar.SelectedIndexChanged += new EventHandler(this.cmbChar_SelectedIndexChanged);
            this.cmbChar.KeyPress += new KeyPressEventHandler(this.cmbChar_KeyPress);
            this.label2.AutoSize = true;
            this.label2.ImeMode = ImeMode.NoControl;
            this.label2.Location = new Point(10, 44);
            this.label2.Name = "label2";
            this.label2.Size = new Size(35, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "Char:";
            this.label1.AutoSize = true;
            this.label1.ImeMode = ImeMode.NoControl;
            this.label1.Location = new Point(10, 18);
            this.label1.Name = "label1";
            this.label1.Size = new Size(35, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Acc:";
            this.button2.ImeMode = ImeMode.NoControl;
            this.button2.Location = new Point(54, 400);
            this.button2.Name = "button2";
            this.button2.Size = new Size(86, 23);
            this.button2.TabIndex = 16;
            this.button2.Text = "Update";
            this.button2.UseVisualStyleBackColor = true;
            this.pnlPackage.BackColor = Color.FromArgb(32, 27, 23);
            this.pnlPackage.BorderStyle = BorderStyle.Fixed3D;
            this.pnlPackage.Controls.Add(this.packageExp);
            this.pnlPackage.Controls.Add(this.btnUpdatePackage);
            
            this.pnlPackage.Controls.Add(this.panel5);
            this.pnlPackage.Controls.Add(this.panel4);
            this.pnlPackage.Controls.Add(this.panel3);
            this.pnlPackage.Controls.Add(this.sPentagramPanel);
            
            
            this.pnlPackage.Controls.Add(this.btnMaxMoney);
            this.pnlPackage.Controls.Add(this.charPanel);
            this.pnlPackage.Controls.Add(this.panel0);
            this.pnlPackage.Controls.Add(this.panel1);
            this.pnlPackage.Controls.Add(this.panel2);
            this.pnlPackage.Location = new Point(656, 26);
            this.pnlPackage.Name = "pnlPackage";
            this.pnlPackage.Size = new Size(595, 548);
            this.pnlPackage.TabIndex = 23;
            this.pnlPackage.Visible = false;
            this.packageExp.Controls.Add(this.PackageExpLv2);
            this.packageExp.Controls.Add(this.PackageExpLv1);
            this.packageExp.Controls.Add(this.chkPackageExp);
            this.packageExp.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.packageExp.ForeColor = Color.Yellow;
            this.packageExp.Location = new Point(342, 404);
            this.packageExp.Name = "packageExp";
            this.packageExp.Size = new Size(200, 100);
            this.packageExp.TabIndex = 89;
            this.packageExp.TabStop = false;
            this.packageExp.Text = "Extended Inv.";
            this.PackageExpLv2.AutoSize = true;
            this.PackageExpLv2.Enabled = false;
            this.PackageExpLv2.Location = new Point(42, 68);
            this.PackageExpLv2.Name = "PackageExpLv2";
            this.PackageExpLv2.Size = new Size(69, 21);
            this.PackageExpLv2.TabIndex = 2;
            this.PackageExpLv2.TabStop = true;
            this.PackageExpLv2.Text = "Level 2";
            this.PackageExpLv2.UseVisualStyleBackColor = true;
            this.PackageExpLv2.CheckedChanged += new EventHandler(this.PackageExpLv2_CheckedChanged);
            this.PackageExpLv1.AutoSize = true;
            this.PackageExpLv1.Enabled = false;
            this.PackageExpLv1.Location = new Point(42, 46);
            this.PackageExpLv1.Name = "PackageExpLv1";
            this.PackageExpLv1.Size = new Size(69, 21);
            this.PackageExpLv1.TabIndex = 1;
            this.PackageExpLv1.TabStop = true;
            this.PackageExpLv1.Text = "Level 1";
            this.PackageExpLv1.UseVisualStyleBackColor = true;
            this.PackageExpLv1.CheckedChanged += new EventHandler(this.PackageExpLv1_CheckedChanged);
            this.chkPackageExp.AutoSize = true;
            this.chkPackageExp.ForeColor = Color.Red;
            this.chkPackageExp.Location = new Point(20, 24);
            this.chkPackageExp.Name = "chkPackageExp";
            this.chkPackageExp.Size = new Size(75, 21);
            this.chkPackageExp.TabIndex = 0;
            this.chkPackageExp.Text = "Extended Inv.";
            this.chkPackageExp.UseVisualStyleBackColor = true;
            this.chkPackageExp.CheckedChanged += new EventHandler(this.chkPackageExp_CheckedChanged);
            this.btnUpdatePackage.BackColor = Color.FromArgb(64, 64, 64);
            this.btnUpdatePackage.FlatStyle = FlatStyle.Popup;
            this.btnUpdatePackage.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnUpdatePackage.ForeColor = Color.White;
            this.btnUpdatePackage.ImeMode = ImeMode.NoControl;
            this.btnUpdatePackage.Location = new Point(370, 509);
            this.btnUpdatePackage.Name = "btnUpdatePackage";
            this.btnUpdatePackage.Size = new Size(130, 24);
            this.btnUpdatePackage.TabIndex = 83;
            this.btnUpdatePackage.Text = "Update Inventory";
            this.btnUpdatePackage.UseVisualStyleBackColor = false;
            this.btnUpdatePackage.Click += new EventHandler(this.btnUpdatePackage_Click);
            this.btnClearPackage.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            this.btnClearPackage.BackColor = Color.FromArgb(64, 64, 64);
            this.btnClearPackage.FlatStyle = FlatStyle.Popup;
            this.btnClearPackage.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnClearPackage.ForeColor = Color.White;
            this.btnClearPackage.ImeMode = ImeMode.NoControl;
            this.btnClearPackage.Location = new Point(380, 509);
            this.btnClearPackage.Name = "btnClearPackage";
            this.btnClearPackage.Size = new Size(66, 24);
            this.btnClearPackage.TabIndex = 85;
            this.btnClearPackage.Text = "Delete";
            this.btnClearPackage.UseVisualStyleBackColor = false;
            this.btnClearPackage.Click += new EventHandler(this.btnClearPackage_Click);
            this.btnClearChar.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            this.btnClearChar.BackColor = Color.FromArgb(64, 64, 64);
            this.btnClearChar.FlatStyle = FlatStyle.Popup;
            this.btnClearChar.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnClearChar.ForeColor = Color.White;
            this.btnClearChar.ImeMode = ImeMode.NoControl;
            this.btnClearChar.Location = new Point(312, 509);
            this.btnClearChar.Name = "btnClearChar";
            this.btnClearChar.Size = new Size(66, 24);
            this.btnClearChar.TabIndex = 84;
            this.btnClearChar.Text = "Delete";
            this.btnClearChar.UseVisualStyleBackColor = false;
            this.btnClearChar.Click += new EventHandler(this.btnClearChar_Click);
            this.panel5.BackgroundImage = Resources.shop;
            this.panel5.BackgroundImageLayout = ImageLayout.None;
            this.panel5.Controls.Add(this.shopPanel);
            this.panel5.Cursor = Cursors.Default;
            this.panel5.Location = new Point(295, 265);
            this.panel5.Margin = new Padding(0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new Size(295, 133);
            this.panel5.TabIndex = 80;
            this.shopPanel.BackgroundImage = Resources.warehouse_2;
            this.shopPanel.BackgroundImageLayout = ImageLayout.None;
            this.shopPanel.Cursor = Cursors.Default;
            this.shopPanel.Location = new Point(43, 15);
            this.shopPanel.Margin = new Padding(0);
            this.shopPanel.Name = "shopPanel";
            this.shopPanel.Size = new Size(209, 105);
            this.shopPanel.TabIndex = 59;
            this.panel4.BackgroundImage = Resources.package_exp_2;
            this.panel4.BackgroundImageLayout = ImageLayout.None;
            this.panel4.Controls.Add(this.packagePanelLv4);
            this.panel4.Cursor = Cursors.Default;
            this.panel4.Location = new Point(295, 265);
            this.panel4.Margin = new Padding(0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new Size(295, 133);
            this.panel4.TabIndex = 79;
            this.panel4.Visible = false;
            this.packagePanelLv4.BackgroundImage = Resources.warehouse_2;
            this.packagePanelLv4.BackgroundImageLayout = ImageLayout.None;
            this.packagePanelLv4.Cursor = Cursors.Default;
            this.packagePanelLv4.Enabled = false;
            this.packagePanelLv4.Location = new Point(43, 15);
            this.packagePanelLv4.Margin = new Padding(0);
            this.packagePanelLv4.Name = "packagePanelLv4";
            this.packagePanelLv4.Size = new Size(209, 105);
            this.packagePanelLv4.TabIndex = 67;
            this.panel3.BackgroundImage = Resources.package_exp_2;
            this.panel3.BackgroundImageLayout = ImageLayout.None;
            this.panel3.Controls.Add(this.packagePanelLv3);
            this.panel3.Cursor = Cursors.Default;
            this.panel3.Location = new Point(295, 266);
            this.panel3.Margin = new Padding(0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new Size(295, 133);
            this.panel3.TabIndex = 78;
            this.panel3.Visible = false;
            this.packagePanelLv3.BackgroundImage = Resources.warehouse_2;
            this.packagePanelLv3.BackgroundImageLayout = ImageLayout.None;
            this.packagePanelLv3.Cursor = Cursors.Default;
            this.packagePanelLv3.Enabled = false;
            this.packagePanelLv3.Location = new Point(43, 15);
            this.packagePanelLv3.Margin = new Padding(0);
            this.packagePanelLv3.Name = "packagePanelLv3";
            this.packagePanelLv3.Size = new Size(209, 105);
            this.packagePanelLv3.TabIndex = 66;
            this.sPentagramPanel.BackgroundImage = Resources.skillbook;
            this.sPentagramPanel.BackgroundImageLayout = ImageLayout.None;
            this.sPentagramPanel.Cursor = Cursors.Default;
            this.sPentagramPanel.Location = new Point(228, 198);
            this.sPentagramPanel.Margin = new Padding(0);
            this.sPentagramPanel.Name = "sPentagramPanel";
            this.sPentagramPanel.Prof = -1;
            this.sPentagramPanel.Size = new Size(58, 58);
            this.sPentagramPanel.TabIndex = 67;
            this.btnCleanPackage.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            this.btnCleanPackage.BackColor = Color.FromArgb(64, 64, 64);
            this.btnCleanPackage.FlatStyle = FlatStyle.Popup;
            this.btnCleanPackage.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnCleanPackage.ForeColor = Color.White;
            this.btnCleanPackage.ImeMode = ImeMode.NoControl;
            this.btnCleanPackage.Location = new Point(231, 509);
            this.btnCleanPackage.Name = "btnCleanPackage";
            this.btnCleanPackage.Size = new Size(44, 24);
            this.btnCleanPackage.TabIndex = 61;
            this.btnCleanPackage.Text = "Clear";
            this.btnCleanPackage.UseVisualStyleBackColor = false;
            this.btnCleanPackage.Click += new EventHandler(this.btnCleanPackage_Click);
            this.btn1YMoney.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            this.btn1YMoney.BackColor = Color.FromArgb(64, 64, 64);
            this.btn1YMoney.FlatStyle = FlatStyle.Popup;
            this.btn1YMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btn1YMoney.ForeColor = Color.White;
            this.btn1YMoney.ImeMode = ImeMode.NoControl;
            this.btn1YMoney.Location = new Point(191, 509);
            this.btn1YMoney.Name = "btn1YMoney";
            this.btn1YMoney.Size = new Size(37, 24);
            this.btn1YMoney.TabIndex = 57;
            this.btn1YMoney.Text = "100m";
            this.btn1YMoney.UseVisualStyleBackColor = false;
            this.btn1YMoney.Click += new EventHandler(this.btn1YMoney_Click);
            this.btnMaxMoney.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            this.btnMaxMoney.BackColor = Color.FromArgb(64, 64, 64);
            this.btnMaxMoney.FlatStyle = FlatStyle.Popup;
            this.btnMaxMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnMaxMoney.ForeColor = Color.White;
            this.btnMaxMoney.ImeMode = ImeMode.NoControl;
            this.btnMaxMoney.Location = new Point(143, 493);
            this.btnMaxMoney.Name = "btnMaxMoney";
            this.btnMaxMoney.Size = new Size(45, 24);
            this.btnMaxMoney.TabIndex = 56;
            this.btnMaxMoney.Text = "Max zen";
            this.btnMaxMoney.UseVisualStyleBackColor = false;
            this.btnMaxMoney.Click += new EventHandler(this.btnMaxMoney_Click);
            this.charPanel.BackgroundImage = Resources.char_2;
            this.charPanel.BackgroundImageLayout = ImageLayout.None;
            this.charPanel.Cursor = Cursors.Default;
            this.charPanel.Location = new Point(0, 0);
            this.charPanel.Margin = new Padding(0);
            this.charPanel.Name = "charPanel";
            this.charPanel.Prof = -1;
            this.charPanel.Size = new Size(295, 284);
            this.charPanel.TabIndex = 13;
            this.panel0.BackgroundImage = Resources.package;
            this.panel0.BackgroundImageLayout = ImageLayout.None;
            this.panel0.Controls.Add(this.txtMoney);
            this.panel0.Controls.Add(this.packagePanel);
            this.panel0.Cursor = Cursors.Default;
            this.panel0.Location = new Point(0, 284);
            this.panel0.Margin = new Padding(0);
            this.panel0.Name = "panel0";
            this.panel0.Size = new Size(295, 260);
            this.panel0.TabIndex = 68;
            this.txtMoney.BackColor = Color.FromArgb(16, 14, 14);
            this.txtMoney.BorderStyle = BorderStyle.FixedSingle;
            this.txtMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.txtMoney.ForeColor = Color.Red;
            this.txtMoney.IsOnlyNumber = true;
            this.txtMoney.Location = new Point(43, 210);
            this.txtMoney.Name = "txtMoney";
            this.txtMoney.Size = new Size(96, 23);
            this.txtMoney.TabIndex = 32;
            this.txtMoney.Text = "0";
            this.packagePanel.BackgroundImage = Resources.warehouse_2;
            this.packagePanel.BackgroundImageLayout = ImageLayout.None;
            this.packagePanel.Cursor = Cursors.Default;
            this.packagePanel.Location = new Point(43, 6);
            this.packagePanel.Margin = new Padding(0);
            this.packagePanel.Name = "packagePanel";
            this.packagePanel.Size = new Size(209, 209);
            this.packagePanel.TabIndex = 15;
            this.panel1.BackgroundImage = Resources.package_exp_1;
            this.panel1.BackgroundImageLayout = ImageLayout.None;
            this.panel1.Controls.Add(this.packagePanelLv1);
            this.panel1.Cursor = Cursors.Default;
            this.panel1.Location = new Point(295, 0);
            this.panel1.Margin = new Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new Size(295, 133);
            this.panel1.TabIndex = 69;
            this.packagePanelLv1.BackgroundImage = Resources.warehouse_2;
            this.packagePanelLv1.BackgroundImageLayout = ImageLayout.None;
            this.packagePanelLv1.Cursor = Cursors.Default;
            this.packagePanelLv1.Location = new Point(43, 15);
            this.packagePanelLv1.Margin = new Padding(0);
            this.packagePanelLv1.Name = "packagePanelLv1";
            this.packagePanelLv1.Size = new Size(209, 105);
            this.packagePanelLv1.TabIndex = 64;
            this.panel2.BackgroundImage = Resources.package_exp_2;
            this.panel2.BackgroundImageLayout = ImageLayout.None;
            this.panel2.Controls.Add(this.packagePanelLv2);
            this.panel2.Cursor = Cursors.Default;
            this.panel2.Location = new Point(295, 133);
            this.panel2.Margin = new Padding(0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new Size(295, 133);
            this.panel2.TabIndex = 70;
            this.packagePanelLv2.BackgroundImage = Resources.warehouse_2;
            this.packagePanelLv2.BackgroundImageLayout = ImageLayout.None;
            this.packagePanelLv2.Cursor = Cursors.Default;
            this.packagePanelLv2.Location = new Point(43, 15);
            this.packagePanelLv2.Margin = new Padding(0);
            this.packagePanelLv2.Name = "packagePanelLv2";
            this.packagePanelLv2.Size = new Size(209, 105);
            this.packagePanelLv2.TabIndex = 65;
            this.pnlWarehouse.BackColor = Color.FromArgb(32, 27, 23);
            this.pnlWarehouse.BorderStyle = BorderStyle.Fixed3D;
            this.pnlWarehouse.Controls.Add(this.WarehouseExp);
            this.pnlWarehouse.Controls.Add(this.warehousePanelLv1);
            
            
            this.pnlWarehouse.Controls.Add(this.btnWareMaxMoney);
            
            
            
            
            this.pnlWarehouse.Controls.Add(this.txtWareHouseMoney);
            this.pnlWarehouse.Controls.Add(this.warehousePanel);
            this.pnlWarehouse.Controls.Add(this.label11);
            this.pnlWarehouse.Controls.Add(this.btnUpdateWarehouse);
            this.pnlWarehouse.Location = new Point(233, 26);
            this.pnlWarehouse.Name = "pnlWarehouse";
            this.pnlWarehouse.Size = new Size(425, 548);
            this.pnlWarehouse.TabIndex = 22;
            this.pnlWarehouse.Visible = false;
            this.WarehouseExp.AutoSize = true;
            this.WarehouseExp.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.WarehouseExp.ForeColor = Color.Yellow;
            this.WarehouseExp.Location = new Point(146, 402);
            this.WarehouseExp.Name = "WarehouseExp";
            this.WarehouseExp.Size = new Size(75, 21);
            this.WarehouseExp.TabIndex = 62;
            this.WarehouseExp.Text = "Extended Ware";
            this.WarehouseExp.UseVisualStyleBackColor = true;
            this.warehousePanelLv1.BackgroundImage = Resources.warehouse_2;
            this.warehousePanelLv1.BackgroundImageLayout = ImageLayout.None;
            this.warehousePanelLv1.Cursor = Cursors.Default;
            this.warehousePanelLv1.Location = new Point(211, 0);
            this.warehousePanelLv1.Margin = new Padding(0);
            this.warehousePanelLv1.Name = "warehousePanelLv1";
            this.warehousePanelLv1.Size = new Size(209, 392);
            this.warehousePanelLv1.TabIndex = 61;
            this.btnClean.BackColor = Color.FromArgb(64, 64, 64);
            this.btnClean.FlatStyle = FlatStyle.Popup;
            this.btnClean.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnClean.ForeColor = Color.White;
            this.btnClean.ImeMode = ImeMode.NoControl;
            this.btnClean.Location = new Point(82, 457);
            this.btnClean.Name = "btnClean";
            this.btnClean.Size = new Size(48, 25);
            this.btnClean.TabIndex = 60;
            this.btnClean.Text = "Organize";
            this.btnClean.UseVisualStyleBackColor = false;
            this.btnClean.Click += new EventHandler(this.btnClean_Click);
            this.btnWare1YMoney.BackColor = Color.FromArgb(64, 64, 64);
            this.btnWare1YMoney.FlatStyle = FlatStyle.Popup;
            this.btnWare1YMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnWare1YMoney.ForeColor = Color.White;
            this.btnWare1YMoney.ImeMode = ImeMode.NoControl;
            this.btnWare1YMoney.Location = new Point(172, 425);
            this.btnWare1YMoney.Name = "btnWare1YMoney";
            this.btnWare1YMoney.Size = new Size(37, 25);
            this.btnWare1YMoney.TabIndex = 59;
            this.btnWare1YMoney.Text = "1m";
            this.btnWare1YMoney.UseVisualStyleBackColor = false;
            this.btnWare1YMoney.Click += new EventHandler(this.btnWare1YMoney_Click);
            this.btnWareMaxMoney.BackColor = Color.FromArgb(64, 64, 64);
            this.btnWareMaxMoney.FlatStyle = FlatStyle.Popup;
            this.btnWareMaxMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnWareMaxMoney.ForeColor = Color.White;
            this.btnWareMaxMoney.ImeMode = ImeMode.NoControl;
            this.btnWareMaxMoney.Location = new Point(234, 425);
            this.btnWareMaxMoney.Name = "btnWareMaxMoney";
            this.btnWareMaxMoney.Size = new Size(46, 25);
            this.btnWareMaxMoney.TabIndex = 58;
            this.btnWareMaxMoney.Text = "Max";
            this.btnWareMaxMoney.UseVisualStyleBackColor = false;
            this.btnWareMaxMoney.Click += new EventHandler(this.btnWareMaxMoney_Click);
            this.label33.Font = new Font("Verdana", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.label33.ForeColor = Color.Red;
            this.label33.ImeMode = ImeMode.NoControl;
            this.label33.Location = new Point(1, 499);
            this.label33.Name = "label33";
            this.label33.Size = new Size(200, 40);
            this.label33.TabIndex = 36;
            this.label33.Text = "Tip：Right-click on the item to modify\r\nCut and paste into different areas to spee" +
                "d up the process.";
            this.txtWareHousePwd.BackColor = Color.FromArgb(16, 14, 14);
            this.txtWareHousePwd.BorderStyle = BorderStyle.FixedSingle;
            this.txtWareHousePwd.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.txtWareHousePwd.ForeColor = Color.Red;
            this.txtWareHousePwd.IsOnlyNumber = true;
            this.txtWareHousePwd.Location = new Point(67, 399);
            this.txtWareHousePwd.Name = "txtWareHousePwd";
            this.txtWareHousePwd.Size = new Size(54, 23);
            this.txtWareHousePwd.TabIndex = 35;
            this.txtWareHousePwd.Text = "0";
            this.btnClearWarehouse.BackColor = Color.FromArgb(64, 64, 64);
            this.btnClearWarehouse.FlatStyle = FlatStyle.Popup;
            this.btnClearWarehouse.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnClearWarehouse.ForeColor = Color.White;
            this.btnClearWarehouse.ImeMode = ImeMode.NoControl;
            this.btnClearWarehouse.Location = new Point(4, 457);
            this.btnClearWarehouse.Name = "btnClearWarehouse";
            this.btnClearWarehouse.Size = new Size(72, 25);
            this.btnClearWarehouse.TabIndex = 17;
            this.btnClearWarehouse.Text = "Clear Vault";
            this.btnClearWarehouse.UseVisualStyleBackColor = false;
            this.btnClearWarehouse.Click += new EventHandler(this.btnClearWarehouse_Click);
            this.label26.AutoSize = true;
            this.label26.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.label26.ForeColor = Color.Yellow;
            this.label26.ImeMode = ImeMode.NoControl;
            this.label26.Location = new Point(3, 401);
            this.label26.Name = "label26";
            this.label26.Size = new Size(68, 17);
            this.label26.TabIndex = 34;
            this.label26.Text = "Pass:";
            this.txtWareHouseMoney.BackColor = Color.FromArgb(16, 14, 14);
            this.txtWareHouseMoney.BorderStyle = BorderStyle.FixedSingle;
            this.txtWareHouseMoney.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.txtWareHouseMoney.ForeColor = Color.Red;
            this.txtWareHouseMoney.IsOnlyNumber = true;
            this.txtWareHouseMoney.Location = new Point(150, 426);
            this.txtWareHouseMoney.Name = "txtWareHouseMoney";
            this.txtWareHouseMoney.Size = new Size(80, 23);
            this.txtWareHouseMoney.TabIndex = 33;
            this.txtWareHouseMoney.Text = "0";
            this.warehousePanel.BackgroundImage = Resources.warehouse_2;
            this.warehousePanel.BackgroundImageLayout = ImageLayout.None;
            this.warehousePanel.Cursor = Cursors.Default;
            this.warehousePanel.Location = new Point(0, 0);
            this.warehousePanel.Margin = new Padding(0);
            this.warehousePanel.Name = "warehousePanel";
            this.warehousePanel.Size = new Size(209, 392);
            this.warehousePanel.TabIndex = 11;
            this.label11.AutoSize = true;
            this.label11.Font = new Font("Microsoft YaHei", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
            this.label11.ForeColor = Color.Yellow;
            this.label11.ImeMode = ImeMode.NoControl;
            this.label11.Location = new Point(115, 428);
            this.label11.Name = "label11";
            this.label11.Size = new Size(44, 17);
            this.label11.TabIndex = 32;
            this.label11.Text = "Zen:";
            this.btnUpdateWarehouse.BackColor = Color.FromArgb(64, 64, 64);
            this.btnUpdateWarehouse.FlatStyle = FlatStyle.Popup;
            this.btnUpdateWarehouse.Font = new Font("Microsoft YaHei", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
            this.btnUpdateWarehouse.ForeColor = Color.White;
            this.btnUpdateWarehouse.ImeMode = ImeMode.NoControl;
            this.btnUpdateWarehouse.Location = new Point(136, 457);
            this.btnUpdateWarehouse.Name = "btnUpdateWarehouse";
            this.btnUpdateWarehouse.Size = new Size(130, 25);
            this.btnUpdateWarehouse.TabIndex = 10;
            this.btnUpdateWarehouse.Text = "Update Warehouse";
            this.btnUpdateWarehouse.UseVisualStyleBackColor = false;
            this.btnUpdateWarehouse.Click += new EventHandler(this.btnUpdateWarehouse_Click);
            base.AutoScaleDimensions = new SizeF(6f, 12f);
            base.AutoScaleMode = AutoScaleMode.Font;
            base.ClientSize = new Size(1250, 576);
            base.Controls.Add(this.pnlPackage);
            base.Controls.Add(this.pnlWarehouse);
            base.Controls.Add(this.menuStrip1);
            base.Controls.Add(this.tabcInfo);
            base.Controls.Add(this.groupBox1);
            base.Controls.Add(this.button2);
            base.FormBorderStyle = FormBorderStyle.FixedSingle;
            base.Icon = (Icon)componentResourceManager.GetObject("$this.Icon");
            base.MainMenuStrip = this.menuStrip1;
            base.MaximizeBox = false;
            base.Name = "frmMain";
            base.StartPosition = FormStartPosition.CenterScreen;
            this.Text = "MuEmu Editor S8";
            base.FormClosing += new FormClosingEventHandler(this.frmMain_FormClosing);
            base.FormClosed += new FormClosedEventHandler(this.Form1_FormClosed);
            base.Load += new EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.tabPage5.ResumeLayout(false);
            this.tabcInfo.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.pnlPackage.ResumeLayout(false);
            this.packageExp.ResumeLayout(false);
            this.packageExp.PerformLayout();
            this.panel5.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.panel3.ResumeLayout(false);
            this.panel0.ResumeLayout(false);
            this.panel0.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.pnlWarehouse.ResumeLayout(false);
            this.pnlWarehouse.PerformLayout();
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        public void InputAccount(string account)
        {
            this.Cursor = Cursors.WaitCursor;
            this.saveLast(false);
            this.showByAccount(account, "");
            this.updateUI();
            this.Cursor = Cursors.Default;
        }

        public void InputCharacter(string charName)
        {
            this.Cursor = Cursors.WaitCursor;
            this.saveLast(true);
            this.showByCharacter(charName);
            this.updateUI();
            this.Cursor = Cursors.Default;
        }

        private bool isCharOnline()
        {
            string str = "";
            bool flag = false;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                string[] mUSERVER = new string[] { "SELECT [MEMB_STAT].[ConnectStat] FROM [", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[AccountCharacter] AS [AC] INNER JOIN [dbo].[MEMB_STAT] ON [AC].[Id] = [MEMB_STAT].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS WHERE ([AC].[Id] = '{0}') AND ([AC].[GameIDC] = '{1}')" };
                str = string.Format(string.Concat(mUSERVER), this.txtAcc.Text.Trim(), this.txtChar.Text.Trim());
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
                if (oleDbDataReader.Read())
                {
                    flag = oleDbDataReader.GetValue(0).ToString() == "1";
                }
                oleDbDataReader.Close();
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
            return flag;
        }

        private bool isOnline()
        {
            string str = "";
            bool flag = false;
            try
            {
                this.Cursor = Cursors.WaitCursor;
                str = string.Concat("SELECT [ConnectStat] FROM [MEMB_STAT] WHERE ([memb___id] = '", this.txtAcc.Text.Trim(), "')");
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
                if (oleDbDataReader.Read())
                {
                    flag = oleDbDataReader.GetValue(0).ToString() == "1";
                }
                oleDbDataReader.Close();
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
            return flag;
        }

        

        protected byte[] loadInventory(string charName)
        {
            string str = null;
            if (charName == "")
            {
                return null;
            }
            byte[] value = null;
            try
            {
                str = string.Concat("SELECT [Inventory] FROM [Character] WHERE ([Name] = '", charName, "')");
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
                if (oleDbDataReader.Read() && oleDbDataReader.GetValue(0) != DBNull.Value)
                {
                    value = (byte[])oleDbDataReader.GetValue(0);
                }
                oleDbDataReader.Close();
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
            return value;
        }



        private void loadMagic(int type)
        {
            char[] chrArray;
            string[] strArrays;
            int k;
            this.clbCharacter.Items.Clear();
            type = (type < 0 ? 0 : type);
            try
            {
                string str = string.Format("SELECT [MagicList] FROM [Character] WHERE ([AccountID] = '{0}') AND ([Name] = '{1}')", this.txtAcc.Text.Trim(), this.txtChar.Text.Trim());
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
                byte[] value = null;
                byte[] numArray = new byte[3];
                string str1 = "";
                Utils.lstSSG.Clear();
                if (oleDbDataReader.Read() && oleDbDataReader.GetValue(0) != DBNull.Value)
                {
                    value = (byte[])oleDbDataReader.GetValue(0);
                    StringBuilder stringBuilder = new StringBuilder();
                    for (int i = 0; i < (int)value.Length; i++)
                    {
                        numArray[i % 3] = value[i];
                        if (i % 3 == 2)
                        {
                            SKILL_SQL_GS sKILLSQLG = Utils.SKILL_SQL2GS(numArray);
                            Utils.lstSSG.Add(sKILLSQLG);
                            if (this.cboClass.SelectedIndex > 15)
                            {
                                if (sKILLSQLG.GSSkillID > 0 && sKILLSQLG.GSSkillID < 255 || sKILLSQLG.GSSkillID > 258 && sKILLSQLG.GSSkillID < 269)
                                {
                                    stringBuilder.Append(string.Concat(",", Utils.SKILL_GS2SQL(sKILLSQLG)));
                                }
                            }
                            else if (sKILLSQLG.GSSkillID > 0 && sKILLSQLG.GSSkillID < 255)
                            {
                                stringBuilder.Append(string.Concat(",", Utils.SKILL_GS2SQL(sKILLSQLG)));
                            }
                        }
                    }
                    str1 = stringBuilder.ToString();
                }
                oleDbDataReader.Close();
                for (int j = 0; j < (int)frmMain.xMagic.Length; j++)
                {
                    if (frmMain.xMagic[j] != null && frmMain.xMagic[j].Name[0] != 0)
                    {
                        SKILL_SQL_GS sKILLSQLG1 = new SKILL_SQL_GS()
                        {
                            SKillLv = 0,
                            GSSkillID = frmMain.xMagic[j].m_Number
                        };
                        string str2 = Utils.SKILL_GS2SQL(sKILLSQLG1);
                        switch (type)
                        {
                            case 0:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.WIZARD != 1)
                                    {
                                        break;
                                    }
                                    bool flag = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str3 = strArrays[k];
                                        if (!(str3 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str3)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str3;
                                            flag = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag);
                                    break;
                                }
                            case 1:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.WIZARD == 0)
                                    {
                                        break;
                                    }
                                    bool flag1 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str4 = strArrays[k];
                                        if (!(str4 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str4)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str4;
                                            flag1 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag1);
                                    break;
                                }
                            case 2:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.WIZARD == 0)
                                    {
                                        break;
                                    }
                                    bool flag2 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str5 = strArrays[k];
                                        if (!(str5 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str5)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str5;
                                            flag2 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag2);
                                    break;
                                }
                            case 3:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.KNIGHT != 1)
                                    {
                                        break;
                                    }
                                    bool flag3 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str6 = strArrays[k];
                                        if (!(str6 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str6)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str6;
                                            flag3 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag3);
                                    break;
                                }
                            case 4:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.KNIGHT == 0)
                                    {
                                        break;
                                    }
                                    bool flag4 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str7 = strArrays[k];
                                        if (!(str7 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str7)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str7;
                                            flag4 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag4);
                                    break;
                                }
                            case 5:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.KNIGHT == 0)
                                    {
                                        break;
                                    }
                                    bool flag5 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str8 = strArrays[k];
                                        if (!(str8 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str8)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str8;
                                            flag5 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag5);
                                    break;
                                }
                            case 6:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.ELF != 1)
                                    {
                                        break;
                                    }
                                    bool flag6 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str9 = strArrays[k];
                                        if (!(str9 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str9)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str9;
                                            flag6 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag6);
                                    break;
                                }
                            case 7:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.ELF == 0)
                                    {
                                        break;
                                    }
                                    bool flag7 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str10 = strArrays[k];
                                        if (!(str10 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str10)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str10;
                                            flag7 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag7);
                                    break;
                                }
                            case 8:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.ELF == 0)
                                    {
                                        break;
                                    }
                                    bool flag8 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str11 = strArrays[k];
                                        if (!(str11 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str11)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str11;
                                            flag8 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag8);
                                    break;
                                }
                            case 9:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.MAGUMSA == 0)
                                    {
                                        break;
                                    }
                                    bool flag9 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str12 = strArrays[k];
                                        if (!(str12 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str12)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str12;
                                            flag9 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag9);
                                    break;
                                }
                            case 10:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.MAGUMSA == 0)
                                    {
                                        break;
                                    }
                                    bool flag10 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str13 = strArrays[k];
                                        if (!(str13 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str13)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str13;
                                            flag10 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag10);
                                    break;
                                }
                            case 11:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.DARKLORD == 0)
                                    {
                                        break;
                                    }
                                    bool flag11 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str14 = strArrays[k];
                                        if (!(str14 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str14)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str14;
                                            flag11 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag11);
                                    break;
                                }
                            case 12:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.DARKLORD == 0)
                                    {
                                        break;
                                    }
                                    bool flag12 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str15 = strArrays[k];
                                        if (!(str15 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str15)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str15;
                                            flag12 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag12);
                                    break;
                                }
                            case 13:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.SUMMONER == 0)
                                    {
                                        break;
                                    }
                                    bool flag13 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str16 = strArrays[k];
                                        if (!(str16 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str16)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str16;
                                            flag13 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag13);
                                    break;
                                }
                            case 14:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.SUMMONER == 0)
                                    {
                                        break;
                                    }
                                    bool flag14 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str17 = strArrays[k];
                                        if (!(str17 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str17)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str17;
                                            flag14 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag14);
                                    break;
                                }
                            case 15:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.SUMMONER == 0)
                                    {
                                        break;
                                    }
                                    bool flag15 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str18 = strArrays[k];
                                        if (!(str18 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str18)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str18;
                                            flag15 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag15);
                                    break;
                                }
                            case 16:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.MONK == 0)
                                    {
                                        break;
                                    }
                                    bool flag16 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str19 = strArrays[k];
                                        if (!(str19 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str19)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str19;
                                            flag16 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag16);
                                    break;
                                }
                            case 17:
                                {
                                    if (frmMain.xMagic[j].iClassNumber.MONK == 0)
                                    {
                                        break;
                                    }
                                    bool flag17 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str20 = strArrays[k];
                                        if (!(str20 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str20)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str20;
                                            flag17 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag17);
                                    break;
                                }
                            default:
                                {
                                    bool flag18 = false;
                                    chrArray = new char[] { ',' };
                                    strArrays = str1.Split(chrArray);
                                    for (k = 0; k < (int)strArrays.Length; k++)
                                    {
                                        string str21 = strArrays[k];
                                        if (!(str21 == "") && Utils.SKILL_SQL2GS(Utils.StringToBytes(str21)).GSSkillID == frmMain.xMagic[j].m_Number)
                                        {
                                            str2 = str21;
                                            flag18 = true;
                                        }
                                    }
                                    this.clbCharacter.Items.Add(new ComboBoxItem(frmMain.ByteToString(frmMain.xMagic[j].Name, 32), str2), flag18);
                                    break;
                                }
                        }
                    }
                }
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "loadMagic：\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
        }

        private void LoadSkillList()
        {
            throw new NotImplementedException();
        }

        protected byte[] loadWarehouse(string account)
        {
            string str = null;
            if (account == "")
            {
                return null;
            }
            byte[] value = null;
            try
            {
                str = string.Concat("SELECT [Items], [Money], [pw] FROM [warehouse] WHERE ([AccountID] = '", account, "')");
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
                if (!oleDbDataReader.Read() || oleDbDataReader.GetValue(0) == DBNull.Value)
                {
                    this.txtWareHouseMoney.Text = "0";
                    this.txtWareHousePwd.Text = "0";
                }
                else
                {
                    value = (byte[])oleDbDataReader.GetValue(0);
                    this.txtWareHouseMoney.Text = Convert.ToString(oleDbDataReader.GetValue(1));
                    this.txtWareHousePwd.Text = Convert.ToString(oleDbDataReader.GetValue(2));
                }
                oleDbDataReader.Close();
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
            return value;
        }

        private void PackageExpLv1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.PackageExpLv1.Checked)
            {
                this.ExtInventory = "1";
            }
        }

        private void PackageExpLv2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.PackageExpLv2.Checked)
            {
                this.ExtInventory = "2";
            }
        }

        private void resizeWindow()
        {
            if (!this.pnlWarehouse.Visible && !this.pnlPackage.Visible)
            {
                base.Width = 239;
                return;
            }
            if (this.pnlWarehouse.Visible && this.pnlPackage.Visible)
            {
                base.Width = 1256;
                this.pnlWarehouse.Left = 233;
                this.pnlPackage.Left = 656;
                return;
            }
            if (this.pnlPackage.Visible)
            {
                base.Width = 834;
                this.pnlPackage.Left = 233;
                return;
            }
            base.Width = 662;
            this.pnlWarehouse.Left = 233;
        }

        private bool saveAccount(string account)
        {
            bool flag;
            string str = null;
            try
            {
                account = (account == null ? "NULL" : string.Concat("'", account.Trim(), "'"));

                string str2 = (this.txtPassword.Text.Trim() == "NULL" ? "NULL" : string.Concat("'", this.txtPassword.Text.Trim(), "'"));
                string str4 = (this.txtEMail.Text.Trim() == "NULL" ? "NULL" : string.Concat("'", this.txtEMail.Text.Trim(), "'"));
                string str5 = (this.txtQuestion.Text.Trim() == "NULL" ? "NULL" : string.Concat("'", this.txtQuestion.Text.Trim(), "'"));
                string str6 = (this.txtAnswer.Text.Trim() == "NULL" ? "NULL" : string.Concat("'", this.txtAnswer.Text.Trim(), "'"));
                string str7 = (this.txtNick.Text.Trim() == "NULL" ? "NULL" : string.Concat("'", this.txtNick.Text.Trim(), "'"));
                string str8 = null;
                str7 = (!this.chkState.Checked ? "'0'" : "'1'");

                string[] strArrays1 = new string[] { "UPDATE [MEMB_INFO] SET [memb__pwd] = " + str2 + ", [memb_name] = " + str7 + ", [mail_addr] = " + str4 + ", [fpas_ques] = " + str5 + ", [fpas_answ] = " + str6 + ", [bloc_code] = " + str7 + " FROM [MEMB_INFO] WHERE ([memb___id] = " + account + ")" };
                str = string.Concat(strArrays1);
                (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteNonQuery();
                Utils.InfoMessage("Account saved successfully！");
                flag = true;
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
                return false;
            }
            return flag;
        }

        


        private bool saveCharacter(string charName)
        {
            bool flag;
            string str = null;
            charName = (charName == null ? "" : charName.Trim());
            if (charName == "")
            {
                return false;
            }
            if (this.isCharOnline())
            {
                Utils.WarningMessage(string.Format("Current character {0} is online！", this.txtChar.Text.Trim()));
                return false;
            }
            try
            {
                int num = Convert.ToInt32(this.txtLevel.Text.Replace(" ", ""));
                int num1 = Convert.ToInt32(this.txtPoint.Text.Replace(" ", ""));
                int num2 = 16;
                switch (this.cboClass.SelectedIndex)
                {
                    case 0:
                        {
                            num2 = 0;
                            break;
                        }
                    case 1:
                        {
                            num2 = 1;
                            break;
                        }
                    case 2:
                        {
                            num2 = 2;
                            break;
                        }
                    case 3:
                        {
                            num2 = 16;
                            break;
                        }
                    case 4:
                        {
                            num2 = 17;
                            break;
                        }
                    case 5:
                        {
                            num2 = 18;
                            break;
                        }
                    case 6:
                        {
                            num2 = 32;
                            break;
                        }
                    case 7:
                        {
                            num2 = 33;
                            break;
                        }
                    case 8:
                        {
                            num2 = 34;
                            break;
                        }
                    case 9:
                        {
                            num2 = 48;
                            break;
                        }
                    case 10:
                        {
                            num2 = 50;
                            break;
                        }
                    case 11:
                        {
                            num2 = 64;
                            break;
                        }
                    case 12:
                        {
                            num2 = 66;
                            break;
                        }
                    case 13:
                        {
                            num2 = 80;
                            break;
                        }
                    case 14:
                        {
                            num2 = 81;
                            break;
                        }
                    case 15:
                        {
                            num2 = 82;
                            break;
                        }
                    case 16:
                        {
                            num2 = 96;
                            break;
                        }
                    case 17:
                        {
                            num2 = 98;
                            break;
                        }
                    default:
                        {
                            num2 = 99;
                            break;
                        }
                }
                string str1 = "0";
                switch (this.cboCode.SelectedIndex)
                {
                    case 0:
                        {
                            str1 = "0";
                            break;
                        }
                    case 1:
                        {
                            str1 = "1";
                            break;
                        }
                    case 2:
                        {
                            str1 = "32";
                            break;
                        }                   
                }
                int num3 = Convert.ToInt32(this.txtExp.Text.Replace(" ", ""));
                int num4 = Convert.ToInt32(this.txtStrength.Text.Replace(" ", ""));
                int num5 = Convert.ToInt32(this.txtDexterity.Text.Replace(" ", ""));
                int num6 = Convert.ToInt32(this.txtVitality.Text.Replace(" ", ""));
                int num7 = Convert.ToInt32(this.txtEnergy.Text.Replace(" ", ""));
                int selectedIndex = this.cboMap.SelectedIndex;
                int num8 = Convert.ToInt32(this.txtPosX.Text.Replace(" ", ""));
                int num9 = Convert.ToInt32(this.txtPosY.Text.Replace(" ", ""));
                int selectedIndex1 = this.cboPK.SelectedIndex;
                int num10 = Convert.ToInt32(this.txtLeaderShip.Text.Replace(" ", ""));
                StringBuilder stringBuilder = new StringBuilder("0x");
                string str2 = "";
                if (this.cbSaveJN.Checked)
                {
                    int num11 = 0;
                    for (int i = 0; i < this.clbCharacter.CheckedItems.Count; i++)
                    {
                        ComboBoxItem item = (ComboBoxItem)this.clbCharacter.CheckedItems[i];
                        stringBuilder.Append(item.Value);
                    }
                    for (int j = 0; j < Utils.lstSSG.Count; j++)
                    {
                        SKILL_SQL_GS sKILLSQLG = Utils.lstSSG[j];
                        if (this.cboClass.SelectedIndex > 15)
                        {
                            if (!stringBuilder.ToString().Contains(Utils.SKILL_GS2SQL(sKILLSQLG)) && sKILLSQLG.GSSkillID > 269)
                            {
                                stringBuilder.Append(Utils.SKILL_GS2SQL(sKILLSQLG));
                                num11++;
                            }
                        }
                        else if (!stringBuilder.ToString().Contains(Utils.SKILL_GS2SQL(sKILLSQLG)) && sKILLSQLG.GSSkillID > 255)
                        {
                            stringBuilder.Append(Utils.SKILL_GS2SQL(sKILLSQLG));
                            num11++;
                        }
                    }
                    for (int k = this.clbCharacter.CheckedItems.Count + num11; k < 150; k++)
                    {
                        stringBuilder.Append("FF0000");
                    }
                    str2 = string.Concat(", [MagicList] = ", stringBuilder.ToString());
                }
                object[] objArray = new object[] { "UPDATE [Character] SET [cLevel] = ", num, ", [LevelUpPoint] = ", num1, ", [Class] = ", num2, ", [Experience] = ", num3, ", [Strength] = ", num4, ", [Dexterity] = ", num5, ", [Vitality] = ", num6, ", [Energy] = ", num7, str2, ", [MapNumber] = ", selectedIndex, ", [MapPosX] = ", num8, ", [MapPosY] = ", num9, ", [PkLevel] = ", selectedIndex1, ", [CtlCode] = ", str1, ", [Leadership] = ", num10, " WHERE ([Name] = '", charName, "')" };
                str = string.Concat(objArray);
                (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteNonQuery();
                Utils.InfoMessage("Character saved successfully！");
                flag = true;
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
                return false;
            }
            return flag;
        }

        public bool saveInventory(string charName)
        {
            bool flag;
            string str = "";
            try
            {
                if (charName == "" || !this.btnUpdatePackage.Enabled)
                {
                    flag = false;
                }
                else if (!this.isCharOnline())
                {
                    this.packagePanel.DownItem();
                    this.packagePanelLv1.DownItem();
                    this.packagePanelLv2.DownItem();
                    this.packagePanelLv3.DownItem();
                    this.packagePanelLv4.DownItem();
                    this.shopPanel.DownItem();
                    string[] equipCodes = new string[] { this.charPanel.getEquipCodes(), this.packagePanel.getEquipCodes(), this.packagePanelLv1.getEquipCodes(), this.packagePanelLv2.getEquipCodes(), this.packagePanelLv3.getEquipCodes(), this.packagePanelLv4.getEquipCodes(), this.shopPanel.getEquipCodes(), this.sPentagramPanel.getEquipCodes() };                                        
                    string str1 = string.Concat(equipCodes);
                    int num = Convert.ToInt32(this.txtMoney.Text.Replace(" ", ""));
                    this.saveItem(str1, true);
                    object[] ExtInventory = new object[] { str1, num, this.ExtInventory, charName };
                    str = string.Format("UPDATE [Character] SET [Inventory] = 0x{0}, [Money] = {1}, [ExtInventory] = {2} WHERE ([Name] = '{3}')", ExtInventory);
                    flag = base.Mu_ExecuteSQL(str);
                    
                }
                else
                {
                    Utils.WarningMessage(string.Format("Current character {0} is online！", this.txtChar.Text.Trim()));
                    flag = false;
                }
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
                return false;
            }
            return flag;
        }

        private void saveItem(string code, bool isChar)
        {
            string str = "INSERT INTO [ItemLog] ([Acc], [Name], [ItemCode], [SN], [iName], [iLvl], [iSkill], [iLuck], [iExt], [iSet], [i380], [iJh]) VALUES ('{0}', '{1}', 0x{2}, '{3}', '{4}', '{5}', '{6}', '{7}', '{8}', '{9}', '{10}', '{11}');";
            try
            {
                StringBuilder stringBuilder = new StringBuilder();
                bool flag = false;
                if (isChar)
                {
                    for (int i = 0; i < Utils.ListPackage.Count; i++)
                    {
                        string item = Utils.ListPackage[i];
                        if (item != "" && item != "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" && !stringBuilder.ToString().Contains(item))
                        {
                            EquipItem equipItem = EquipItem.createItem(item);
                            if (equipItem != null && equipItem.SN < 0)
                            {
                                StringBuilder stringBuilder1 = stringBuilder;
                                string str1 = str;
                                object[] name = new object[] { this.txtAcc.Text.Trim(), this.txtChar.Text.Trim(), item, equipItem.SN, equipItem.Name, null, null, null, null, null, null, null };
                                object[] level = new object[] { "+", equipItem.Level, "z", equipItem.Ext * 4 };
                                name[5] = string.Concat(level);
                                name[6] = (equipItem.JN ? 1 : 0);
                                name[7] = (equipItem.XY ? 1 : 0);
                                name[8] = equipItem.Name;
                                name[9] = (equipItem.SetVal > 0 ? 1 : 0);
                                name[10] = (equipItem.Is380 ? 1 : 0);
                                name[11] = 0;
                                stringBuilder1.Append(string.Format(str1, name));
                                Utils.ListPackage[i] = "";
                                flag = true;
                            }
                        }
                    }
                }
                for (int j = 0; j < Utils.ListWareHouse.Count; j++)
                {
                    string item1 = Utils.ListWareHouse[j];
                    if (item1 != "" && item1 != "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" && !stringBuilder.ToString().Contains(item1))
                    {
                        EquipItem equipItem1 = EquipItem.createItem(item1);
                        if (equipItem1 != null && equipItem1.SN < 0)
                        {
                            StringBuilder stringBuilder2 = stringBuilder;
                            string str2 = str;
                            object[] objArray = new object[] { this.txtAcc.Text.Trim(), this.txtChar.Text.Trim(), item1, equipItem1.SN, equipItem1.Name, null, null, null, null, null, null, null };
                            object[] level1 = new object[] { "+", equipItem1.Level, "z", equipItem1.Ext };
                            objArray[5] = string.Concat(level1);
                            objArray[6] = (equipItem1.JN ? 1 : 0);
                            objArray[7] = (equipItem1.XY ? 1 : 0);
                            objArray[8] = equipItem1.Name;
                            objArray[9] = (equipItem1.SetVal > 0 ? 1 : 0);
                            objArray[10] = (equipItem1.Is380 ? 1 : 0);
                            objArray[11] = 0;
                            stringBuilder2.Append(string.Format(str2, objArray));
                            Utils.ListWareHouse[j] = "";
                            flag = true;
                        }
                    }
                }
                if (flag)
                {
                    OleDbCommand oleDbCommand = new OleDbCommand(stringBuilder.ToString(), frmBase.Mu_Conn);
                    oleDbCommand.ExecuteNonQuery();
                }
            }
            catch (Exception exception1)
            {
                
            }
        }

        private void saveLast(bool isChar)
        {
            if (!isChar)
            {
                this.warehousePanel.DownItem();
                this.warehousePanelLv1.DownItem();
                this.packagePanel.DownItem();
                this.packagePanelLv1.DownItem();
                this.packagePanelLv2.DownItem();
                this.packagePanelLv3.DownItem();
                this.packagePanelLv4.DownItem();
                this.shopPanel.DownItem();
                if ((this.wareHouseCode != "" && this.wareHouseCode != this.warehousePanel.getEquipCodes() || this.wareHouseLv1Code != "" && this.wareHouseLv1Code != this.warehousePanelLv1.getEquipCodes() || this.packagePanelCode != "" && this.packagePanelCode != this.packagePanel.getEquipCodes() || this.packagePanelLv1Code != "" && this.packagePanelLv1Code != this.packagePanelLv1.getEquipCodes() || this.packagePanelLv2Code != "" && this.packagePanelLv2Code != this.packagePanelLv2.getEquipCodes() || this.packagePanelLv3Code != "" && this.packagePanelLv3Code != this.packagePanelLv3.getEquipCodes() || this.packagePanelLv4Code != "" && this.packagePanelLv4Code != this.packagePanelLv4.getEquipCodes() || this.charPanelCode != "" && this.charPanelCode != this.charPanel.getEquipCodes() || this.shopPanelCode != "" && this.shopPanelCode != this.shopPanel.getEquipCodes() || this.sPentagramPanelCode != "" && this.sPentagramPanelCode != this.sPentagramPanel.getEquipCodes()) && MessageBox.Show("The current warehouse, package or store has changed, do you want to save the changes?", "Error", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    this.saveInventory(this.lastCharName);
                    
                    this.saveWarehouse(this.lastAccount);
                }
            }
            else
            {
                this.packagePanel.DownItem();
                this.packagePanelLv1.DownItem();
                this.packagePanelLv2.DownItem();
                this.packagePanelLv3.DownItem();
                this.packagePanelLv4.DownItem();
                this.shopPanel.DownItem();
                if ((this.packagePanelCode != "" && this.packagePanelCode != this.packagePanel.getEquipCodes() || this.packagePanelLv1Code != "" && this.packagePanelLv1Code != this.packagePanelLv1.getEquipCodes() || this.packagePanelLv2Code != "" && this.packagePanelLv2Code != this.packagePanelLv2.getEquipCodes() || this.packagePanelLv3Code != "" && this.packagePanelLv3Code != this.packagePanelLv3.getEquipCodes() || this.packagePanelLv4Code != "" && this.packagePanelLv4Code != this.packagePanelLv4.getEquipCodes() || this.charPanelCode != "" && this.charPanelCode != this.charPanel.getEquipCodes() || this.shopPanelCode != "" && this.shopPanelCode != this.shopPanel.getEquipCodes() || this.sPentagramPanelCode != "" && this.sPentagramPanelCode != this.sPentagramPanel.getEquipCodes()) && MessageBox.Show("The current warehouse, package or store has changed, do you want to save the changes?", "Error", MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                {
                    this.saveInventory(this.lastCharName);
                    
                    return;
                }
            }
        }

        public bool saveWarehouse(string account)
        {
            bool flag;
            string str = "";
            try
            {
                if (account == "" || !this.btnUpdateWarehouse.Enabled)
                {
                    flag = false;
                }
                else
                {
                    int num = Convert.ToInt32(this.txtWareHouseMoney.Text.Replace(" ", ""));
                    int num1 = Convert.ToInt32(this.txtWareHousePwd.Text.Replace(" ", ""));
                    this.warehousePanel.DownItem();
                    this.warehousePanelLv1.DownItem();
                    string str1 = string.Concat(this.warehousePanel.getEquipCodes(), this.warehousePanelLv1.getEquipCodes());
                    this.saveItem(str1, false);
                    str = string.Concat("SELECT [Items] FROM [warehouse] WHERE ([AccountID] = '", account, "')");
                    OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
                    string str2 = null;
                    str2 = (!this.WarehouseExp.Checked ? "0" : "1");
                    str = string.Format("UPDATE [AccountCharacter] SET [ExtWarehouse] = {0} WHERE ([Id] = '{1}')", str2, account);
                    base.Mu_ExecuteSQL(str);
                    if (oleDbDataReader.Read())
                    {
                        if (this.isOnline())
                        {
                            byte[] value = null;
                            if (oleDbDataReader.GetValue(0) != DBNull.Value)
                            {
                                value = (byte[])oleDbDataReader.GetValue(0);
                            }
                            EquipPanel equipPanel = new EquipPanel();
                            equipPanel.setSize(8, 15);
                            equipPanel.loadItemsByCodes(value, 0, (int)value.Length);
                            EquipPanel equipPanel1 = new EquipPanel();
                            equipPanel1.setSize(8, 15);
                            equipPanel1.loadItemsByCodes(value, 3840, (int)value.Length);
                            if (this.wareHouseCode != equipPanel.getEquipCodes() || this.wareHouseLv1Code != equipPanel1.getEquipCodes())
                            {
                                if (MessageBox.Show("This vault is currently being accessed，do you want to continue updating？", "?", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                                {
                                    flag = false;
                                    return flag;
                                }
                                else
                                {
                                    object[] objArray = new object[] { str1, num, num1, account };
                                    str = string.Format("UPDATE [warehouse] SET [Items] = 0x{0}, [Money] = {1}, [pw] = {2} WHERE ([AccountID] = '{3}')", objArray);
                                    flag = base.Mu_ExecuteSQL(str);
                                    return flag;
                                }
                            }
                        }
                        object[] objArray1 = new object[] { str1, num, num1, account };
                        str = string.Format("UPDATE [warehouse] SET [Items] = 0x{0}, [Money] = {1}, [pw] = {2} WHERE ([AccountID] = '{3}')", objArray1);
                        flag = base.Mu_ExecuteSQL(str);
                    }
                    else
                    {
                        object[] objArray2 = new object[] { account, str1, num, 3, num1 };
                        str = string.Format("INSERT INTO [warehouse] ([AccountID], [Items], [Money], [DbVersion], [pw]) VALUES ('{0}', 0x{1}, {2}, {3}, {4})", objArray2);
                        flag = base.Mu_ExecuteSQL(str);
                    }
                }
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
                return false;
            }
            return flag;
        }

        private void setManagerFrm()
        {
            if (this.pnlWarehouse.Visible || this.pnlPackage.Visible)
            {
                if (this.FrmUser != null)
                {
                    this.FrmUser.Top = base.Top + base.Height / 2 - this.FrmUser.Height / 2;
                    this.FrmUser.Left = base.Left + base.Width / 2 - this.FrmUser.Width / 2;
                }
                if (this.FrmGuild != null)
                {
                    this.FrmGuild.Top = base.Top + base.Height / 2 - this.FrmGuild.Height / 2;
                    this.FrmGuild.Left = base.Left + base.Width / 2 - this.FrmGuild.Width / 2;
                }
                if (this.FrmEquip != null)
                {
                    this.FrmEquip.Top = base.Top + base.Height / 2 - this.FrmEquip.Height / 2;
                    this.FrmEquip.Left = base.Left + base.Width / 2 - this.FrmEquip.Width / 2;
                    return;
                }
            }
            else
            {
                if (this.FrmUser != null)
                {
                    this.FrmUser.Top = base.Top;
                    this.FrmUser.Left = base.Left + base.Width;
                }
                if (this.FrmGuild != null)
                {
                    this.FrmGuild.Top = base.Top;
                    this.FrmGuild.Left = base.Left + base.Width;
                }
                if (this.FrmEquip != null)
                {
                    this.FrmEquip.Top = base.Top;
                    this.FrmEquip.Left = base.Left + base.Width;
                }
            }
        }

        private void showByAccount(string account, string charName)
        {
            if (account == "")
            {
                return;
            }
            this.lastAccount = account;
            if (frmBase.Me_Conn.State != ConnectionState.Open)
            {
                return;
            }
            string str = null;
            try
            {
                str = string.Format("SELECT [a].[memb___id], [a].[memb__pwd], [a].[memb_name], [a].[sno__numb], [a].[mail_addr], [a].[fpas_ques], [a].[fpas_answ], [a].[bloc_code], [a].[post_code], [b].[ConnectStat], [b].[ServerName], [b].[IP], [b].[ConnectTM], [b].[DisConnectTM] FROM [MEMB_INFO] AS [a] LEFT OUTER JOIN [MEMB_STAT] AS [b] ON [a].[memb___id] = [b].[memb___id] COLLATE Chinese_PRC_CS_AS_KS_WS WHERE ([a].[memb___id] = '{0}')", account);
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
                if (!oleDbDataReader.Read())
                {
                    
                    this.txtAccount.SelectAll();
                    this.tabcInfo.Enabled = false;
                    this.pnlPackage.Enabled = false;
                    this.pnlWarehouse.Enabled = false;
                    this.clearGDI(false);
                }
                else
                {
                    foreach (DataRow row in oleDbDataReader.GetSchemaTable().Rows)
                    {
                        if (Convert.ToString(row["ColumnName"]) != "[memb__pwd]")
                        {
                            continue;
                        }
                        this.MD5 = Convert.ToString(row["DataType"]) == "System.Byte[]";
                        break;
                    }
                    ComboBox comboBox = this.txtAccount;
                    TextBox textBox = this.txtAcc;
                    string str1 = Convert.ToString(oleDbDataReader.GetValue(0));
                    string str2 = str1;
                    textBox.Text = str1;
                    comboBox.Text = str2;
                    this.txtPassword.Text = (Convert.ToString(oleDbDataReader.GetValue(2)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(1)));
                    
                    this.txtNick.Text = (Convert.ToString(oleDbDataReader.GetValue(2)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(2)));
                    this.txtSNO.Text = (Convert.ToString(oleDbDataReader.GetValue(3)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(3)));
                    this.txtEMail.Text = (Convert.ToString(oleDbDataReader.GetValue(4)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(4)));
                    this.txtQuestion.Text = (Convert.ToString(oleDbDataReader.GetValue(5)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(5)));
                    this.txtAnswer.Text = (Convert.ToString(oleDbDataReader.GetValue(6)) == "" ? "NULL" : Convert.ToString(oleDbDataReader.GetValue(6)));
                    string str3 = Convert.ToString(oleDbDataReader.GetValue(7));
                    this.chkState.Checked = str3 == "1";
                    
                    string str4 = (oleDbDataReader.GetValue(9).ToString() == "0" ? "Offline" : "Online");
                    this.lblState.Text = str4;
                    if (oleDbDataReader.GetValue(9).ToString() == "0" )
                    {
                        this.lblState.ForeColor = Color.Red;
                    }
                    else
                    {
                        this.lblState.ForeColor = Color.Green;
                    }          
                    
                    this.lblServer.Text = string.Format("Server: {0}", oleDbDataReader.GetValue(10));
                    this.lblIP.Text = string.Format("{0}", oleDbDataReader.GetValue(11));
                    this.lblConnectTime.Text = string.Format("Last online: {0:F}", oleDbDataReader.GetValue(12));
                    this.lblDisConnectTime.Text = string.Format("Last offline: {0:F}", oleDbDataReader.GetValue(13));
                    this.tabcInfo.Enabled = true;
                    this.pnlPackage.Enabled = true;
                    this.pnlWarehouse.Enabled = true;
                    this.showGDI(false);
                    oleDbDataReader.Close();
                    string[] mUSERVER = new string[] { "SELECT [AC].[GameIDC], [AC].[GameID1], [AC].[GameID2], [AC].[GameID3], [AC].[GameID4], [AC].[GameID5], [AC].[ExtWarehouse] FROM [dbo].[MEMB_INFO] LEFT OUTER JOIN [", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[AccountCharacter] AS [AC] ON [MEMB_INFO].[memb___id] = [AC].[Id] COLLATE Chinese_PRC_CS_AS_KS_WS WHERE ([AC].[Id] = '", account, "')" };
                    str = string.Concat(mUSERVER);
                    oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
                    this.cmbChar.Items.Clear();
                    this.cmbChar.Text = "";
                    if (!oleDbDataReader.Read())
                    {
                        
                        this.pnlPackage.Enabled = false;
                        this.clearGDI(true);
                    }
                    else
                    {
                        object value = oleDbDataReader.GetValue(0);
                        for (int i = 1; i <= 5; i++)
                        {
                            value = oleDbDataReader.GetValue(i);
                            if (value != null && value.ToString() != "")
                            {
                                this.cmbChar.Items.Add(value);
                            }
                        }
                        if (this.cmbChar.Items.Count > 0)
                        {
                            this.cmbChar.SelectedIndex = 0;
                        }
                        string str5 = Convert.ToString(oleDbDataReader.GetValue(6));
                        this.WarehouseExp.Checked = str5 == "1";
                        this.showGDI(false);
                    }
                    oleDbDataReader.Close();
                    str = string.Concat("SELECT [AccountCharacter].[Id], [AccountCharacter].[Number] FROM [MEMB_INFO] LEFT OUTER JOIN [AccountCharacter] ON [MEMB_INFO].[memb___id] = [AccountCharacter].[Id] COLLATE Chinese_PRC_CS_AS_KS_WS WHERE ([Id] = '", account, "')");
                    oleDbDataReader = (new OleDbCommand(str, frmBase.Me_Conn)).ExecuteReader();
                    
                    
                    oleDbDataReader.Close();
                    if (charName == "")
                    {
                        charName = this.cmbChar.Text;
                    }
                    this.showCharacter(charName);
                }
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
        }

        private void showByCharacter(string charName)
        {
            if (charName == "")
            {
                return;
            }
            if (frmBase.Mu_Conn.State != ConnectionState.Open)
            {
                return;
            }
            string str = null;
            string str1 = null;
            try
            {
                str = string.Concat("SELECT [AccountID] FROM [Character] WHERE ([Name] = '", charName, "')");
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str, frmBase.Mu_Conn)).ExecuteReader();
                if (!oleDbDataReader.Read())
                {
                    Utils.WarningMessage(string.Concat("Error: The character [" + charName + "] was not found."));
                    oleDbDataReader.Close();
                    this.clearGDI(true);
                    this.pnlPackage.Enabled = false;
                }
                else
                {
                    str1 = Convert.ToString(oleDbDataReader.GetValue(0));
                    this.pnlPackage.Enabled = true;
                    oleDbDataReader.Close();
                    this.showByAccount(str1, charName);
                }
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
        }

        private void showCharacter(string charName)
        {
            if (charName != "")
            {
                this.lastCharName = charName;
                if (frmBase.Mu_Conn.State == ConnectionState.Open)
                {
                    string cmdText = null;
                    try
                    {
                        cmdText = "SELECT [AccountID], [cLevel], [LevelUpPoint], [Class], [Experience], [Strength], [Dexterity], [Vitality], [Energy], [Money], [MapNumber], [MapPosX], [MapPosY], [PkCount], [PkLevel], [CtlCode], [Leadership], [ExtInventory] FROM [Character] WHERE ([Name] = '" + charName + "')";
                        OleDbDataReader reader = new OleDbCommand(cmdText, frmBase.Mu_Conn).ExecuteReader();
                        if (reader.Read())
                        {
                            Convert.ToString(reader.GetValue(0));
                            this.txtChar.Text = charName;
                            this.txtLevel.Text = Convert.ToString(reader.GetValue(1));
                            this.txtPoint.Text = Convert.ToString(reader.GetValue(2));
                            int @byte = 0;
                            if (reader.GetValue(3) != DBNull.Value)
                            {
                                @byte = reader.GetByte(3);
                            }
                            switch (@byte)
                            {
                                case 0:
                                    this.cboClass.SelectedIndex = 0;
                                    break;

                                case 1:
                                    this.cboClass.SelectedIndex = 1;
                                    break;

                                case 2:
                                    this.cboClass.SelectedIndex = 2;
                                    break;

                                case 16:
                                    this.cboClass.SelectedIndex = 3;
                                    break;

                                case 17:
                                    this.cboClass.SelectedIndex = 4;
                                    break;

                                case 18:
                                    this.cboClass.SelectedIndex = 5;
                                    break;

                                case 32:
                                    this.cboClass.SelectedIndex = 6;
                                    break;

                                case 33:
                                    this.cboClass.SelectedIndex = 7;
                                    break;

                                case 34:
                                    this.cboClass.SelectedIndex = 8;
                                    break;

                                case 48:
                                    this.cboClass.SelectedIndex = 9;
                                    break;

                                case 50:
                                    this.cboClass.SelectedIndex = 10;
                                    break;

                                case 64:
                                    this.cboClass.SelectedIndex = 11;
                                    break;

                                case 66:
                                    this.cboClass.SelectedIndex = 12;
                                    break;

                                case 80:
                                    this.cboClass.SelectedIndex = 13;
                                    break;

                                case 81:
                                    this.cboClass.SelectedIndex = 14;
                                    break;

                                case 82:
                                    this.cboClass.SelectedIndex = 15;
                                    break;

                                case 96:
                                    this.cboClass.SelectedIndex = 16;
                                    break;

                                case 98:
                                    this.cboClass.SelectedIndex = 17;
                                    break;

                                default:
                                    this.cboClass.SelectedIndex = 0x12;
                                    break;
                            }
                            this.txtExp.Text = Convert.ToInt32(reader.GetValue(4)).ToString();
                            this.txtStrength.Text = Convert.ToString(reader.GetValue(5));
                            this.txtDexterity.Text = Convert.ToString(reader.GetValue(6));
                            this.txtVitality.Text = Convert.ToString(reader.GetValue(7));
                            this.txtEnergy.Text = Convert.ToString(reader.GetValue(8));
                            this.txtMoney.Text = Convert.ToString(reader.GetValue(9));
                            int num2 = 0;
                            if (reader.GetValue(10) != DBNull.Value)
                            {
                                num2 = Convert.ToInt32(reader.GetValue(10));
                            }
                            if (num2 < this.cboMap.Items.Count)
                            {
                                this.cboMap.SelectedIndex = num2;
                            }
                            this.txtPosX.Text = Convert.ToString(reader.GetValue(11));
                            this.txtPosY.Text = Convert.ToString(reader.GetValue(12));
                            Convert.ToInt32(reader.GetValue(13));
                            int num3 = Convert.ToInt32(reader.GetValue(14));
                            this.cboPK.SelectedIndex = num3;
                            switch (reader.GetByte(15))
                            {
                                case 0:
                                    this.cboCode.SelectedIndex = 0;
                                    break;

                                case 1:
                                    this.cboCode.SelectedIndex = 1;
                                    break;

                                case 32:
                                    this.cboCode.SelectedIndex = 2;
                                    break;
                            }
                            this.txtLeaderShip.Text = Convert.ToString(reader.GetValue(0x10));
                            this.ExtInventory = Convert.ToString(reader.GetValue(0x11));
                            if (this.ExtInventory == "1")
                            {
                                this.chkPackageExp.Checked = true;
                                this.PackageExpLv1.Checked = true;
                                this.PackageExpLv2.Checked = false;
                            }
                            else if (this.ExtInventory == "2")
                            {
                                this.chkPackageExp.Checked = true;
                                this.PackageExpLv1.Checked = false;
                                this.PackageExpLv2.Checked = true;
                            }
                            else
                            {
                                this.chkPackageExp.Checked = false;
                                this.PackageExpLv1.Checked = false;
                                this.PackageExpLv2.Checked = false;
                            }
                            this.cmbChar.Text = charName;
                            this.loadMagic(this.cboClass.SelectedIndex);
                            this.pnlPackage.Enabled = true;
                            this.showGDI(true);
                        }
                        else
                        {
                            Utils.WarningMessage("Error: The character [" + charName + "] was not found.");
                            this.pnlPackage.Enabled = false;
                            this.clearGDI(true);
                        }
                        reader.Close();
                    }
                    catch (Exception exception)
                    {
                        Utils.WarningMessage("SQL：" + cmdText + "\nError:" + exception.Message + "\nSource:" + exception.Source + "\nTrace:" + exception.StackTrace);
                    }
                }
            }
        }

        private void showGDI(bool isChar)
        {
            this.accountLogin = true;
            this.charLogin = true;
            this.btnUpdateChar.Enabled = true;
            this.btnUpdatePackage.Enabled = true;
            this.btnUpdateWarehouse.Enabled = true;
            this.btnClearPackage.Enabled = true;
            this.btnClearWarehouse.Enabled = true;
            this.showPackageItems();
            if (!isChar)
            {
                this.showWarehouseItems();
                this.wareHouseCode = this.warehousePanel.getEquipCodes();
                this.wareHouseLv1Code = this.warehousePanelLv1.getEquipCodes();
            }
            this.charPanelCode = this.charPanel.getEquipCodes();
            this.packagePanelCode = this.packagePanel.getEquipCodes();
            this.packagePanelLv1Code = this.packagePanelLv1.getEquipCodes();
            this.packagePanelLv2Code = this.packagePanelLv2.getEquipCodes();
            this.packagePanelLv3Code = this.packagePanelLv3.getEquipCodes();
            this.packagePanelLv4Code = this.packagePanelLv4.getEquipCodes();
            this.shopPanelCode = this.shopPanel.getEquipCodes();
            this.sPentagramPanelCode = this.sPentagramPanel.getEquipCodes();
        }

        protected void showPackage(bool flag)
        {
            if (!flag)
            {
                this.tabcInfo.SelectedIndex = 1;
            }
            else
            {
                this.tabcInfo.SelectedIndex = 2;
                if (!this.LoadedPackage)
                {
                    this.showPackageItems();
                }
            }
            this.pnlPackage.Visible = flag;
            this.resizeWindow();
            this.ShownPackage = flag;
        }

        private void showPackageItems()
        {
            string str = this.txtChar.Text.Trim();
            if (str == "")
            {
                return;
            }
            byte[] numArray = this.loadInventory(str);
            
            if (numArray != null)
            {
                this.LoadedPackage = true;
                this.charPanel.clearData();
                int xNum = 192;
                if (!this.charPanel.loadItemsByCodes(numArray, 0, 192))
                {
                    Utils.WarningMessage(string.Format("Error: Role data for character [{0}] is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.packagePanel.clearData();
                if (!this.packagePanel.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Inventory data for character [{0}] is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.packagePanelLv1.clearData();
                xNum = xNum + this.packagePanel.XNum * this.packagePanel.YNum * 16;
                if (!this.packagePanelLv1.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Role data for [{0}] extension package 1 is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.packagePanelLv2.clearData();
                xNum = xNum + this.packagePanelLv1.XNum * this.packagePanelLv1.YNum * 16;
                if (!this.packagePanelLv2.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Role data for [{0}] extension package 2 is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.packagePanelLv3.clearData();
                xNum = xNum + this.packagePanelLv2.XNum * this.packagePanelLv2.YNum * 16;
                if (!this.packagePanelLv3.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Role data for [{0}] extension package 3 is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.packagePanelLv4.clearData();
                xNum = xNum + this.packagePanelLv3.XNum * this.packagePanelLv3.YNum * 16;
                if (!this.packagePanelLv4.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Role data for [{0}] extension package 4 is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                this.shopPanel.clearData();
                xNum = xNum + this.packagePanelLv4.XNum * this.packagePanelLv4.YNum * 16;
                if (!this.shopPanel.loadItemsByCodes(numArray, xNum, (int)numArray.Length - xNum))
                {
                    Utils.WarningMessage(string.Format("Error: Shop data for [{0}] is not in the correct format.", str));
                    this.LoadedPackage = false;
                }
                
                
            }
        }

        protected void showWarehouse(bool flag)
        {
            if (!flag)
            {
                this.tabcInfo.SelectedIndex = 0;
            }
            else
            {
                this.tabcInfo.SelectedIndex = 2;
                if (!this.LoadedWarehouse)
                {
                    this.showWarehouseItems();
                }
            }
            this.pnlWarehouse.Visible = flag;
            this.resizeWindow();
            this.ShownWarehouse = flag;
        }

        private void showWarehouseItems()
        {
            string str = this.txtAcc.Text.Trim();
            if (str == "")
            {
                return;
            }
            byte[] numArray = this.loadWarehouse(str);
            if (numArray == null)
            {
                this.LoadedWarehouse = true;
                this.warehousePanel.clearData();
                this.warehousePanel.loadItemsByCodes(numArray, 0, 0);
                this.warehousePanelLv1.clearData();
                this.warehousePanelLv1.loadItemsByCodes(numArray, 3840, 0);
            }
            else
            {
                this.LoadedWarehouse = true;
                this.warehousePanel.clearData();
                if (!this.warehousePanel.loadItemsByCodes(numArray, 0, (int)numArray.Length / 2))
                {
                    Utils.WarningMessage(string.Format("Error: Warehouse data for [{0}] is not in the correct format.", str));
                    this.LoadedWarehouse = false;
                }
                this.warehousePanelLv1.clearData();
                if (!this.warehousePanelLv1.loadItemsByCodes(numArray, (int)numArray.Length / 2, (int)numArray.Length / 2))
                {
                    Utils.WarningMessage(string.Format("Error: Warehouse extension 1 data for [{0}] is not in the correct format.", str));
                    this.LoadedWarehouse = false;
                    return;
                }
            }
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

        protected void updateUI()
        {
            this.btnWarehouse.Enabled = this.accountLogin;
            this.btnChar.Enabled = this.charLogin;
            this.btnMaster.Enabled = this.charLogin;
            if (this.ShownPackage)
            {
                this.showPackage(true);
            }
            if (this.ShownWarehouse)
            {
                this.showWarehouse(true);
            }
            if (this.ShownPackage || this.ShownWarehouse)
            {
                this.tabcInfo.SelectedIndex = 2;
            }
            if (this.charLogin)
            {
                this.charPanel.Prof = this.cboClass.SelectedIndex;
            }
            this.resizeWindow();
        }

        private void 人物查询toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.FrmUser = frmUser.GetInstance(this, "");
            this.FrmUser.Visible = false;
            this.FrmUser.Show(this);
            this.setManagerFrm();
            this.Cursor = Cursors.Default;
        }

        private void 关于AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            (new frmAbout()).ShowDialog(this);
        }

        private void 在线情况UToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string str = "No message query";
            string str1 = "";
            try
            {
                this.Cursor = Cursors.WaitCursor;
                string[] mUSERVER = new string[] { "SELECT TOP 1 (SELECT COUNT(1) FROM [MEMB_INFO]) AS [a], (SELECT COUNT(1) FROM [", frmMain.MU_SERVER, "].[", frmMain.MU_DB, "].[dbo].[Character]) AS [b], (SELECT COUNT(1) FROM [MEMB_STAT] WHERE ([ConnectStat] = 1)) AS [c] FROM [dbo].[MEMB_INFO]" };
                str1 = string.Concat(mUSERVER);
                OleDbDataReader oleDbDataReader = (new OleDbCommand(str1, frmBase.Me_Conn)).ExecuteReader();
                if (oleDbDataReader.Read())
                {
                    str = string.Format("Server statistics: \n\n Accounts: {0}\n Characters: {1} \n Online players: {2}", oleDbDataReader.GetValue(0), oleDbDataReader.GetValue(1), oleDbDataReader.GetValue(2));
                }
                oleDbDataReader.Close();
            }
            catch (Exception exception1)
            {
                Exception exception = exception1;
                string[] message = new string[] { "SQL：", str1, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
                Utils.WarningMessage(string.Concat(message));
            }
            this.Cursor = Cursors.Default;
            Utils.InfoMessage(str);
        }

        private void 如何使用HToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!File.Exists(string.Concat(Application.StartupPath, "\\使用说明.doc")))
            {
                Utils.WarningMessage("test wiadomosc");
                return;
            }
            Process.Start(string.Concat(Application.StartupPath, "\\使用说明.doc"));
        }

        private void 战盟管理GToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.FrmGuild = frmGuild.GetInstance(this);
            this.FrmGuild.Visible = false;
            this.FrmGuild.Show(this);
            this.setManagerFrm();
            this.Cursor = Cursors.Default;
        }

        private void 添加帐号NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            frmUserAdd.GetInstance().ShowDialog(this);
            this.Cursor = Cursors.Default;
        }

        private void 退出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            base.Close();
        }
    }
}