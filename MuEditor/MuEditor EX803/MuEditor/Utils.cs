using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Configuration;
using System.Diagnostics;
using System.Management;
using System.Text;
using System.Web.Security;
using System.Windows.Forms;

namespace MuEditor
{
	public class Utils
	{
		public static List<SKILL_SQL_GS> lstSSG;

		public static string ErrorMsg;

		public static string[] YGS;

		public static string[] YSS;

		public static string[] strPlusA;

		public static string[] strPlusB;

		public static string[] strPlusC;

		public static string[] SearchNames;

		public static string[] SearchValues;

		public static int SN;

		public static List<string> ListWareHouse;

		public static List<string> ListPackage;

		public static string[] AccFieldNames
		{
			get
			{
				return ConfigurationManager.AppSettings["AccFieldNames"].Split(new char[] { '|' });
			}
		}

		public static string[] AccFieldValues
		{
			get
			{
				return ConfigurationManager.AppSettings["AccFieldValues"].Split(new char[] { '|' });
			}
		}

		public static int CDJExt
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CDJExt"]);
			}
		}

		public static int CDJLevel
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CDJLevel"]);
			}
		}

		public static int CDJSetVal
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CDJSetVal"]);
			}
		}

		public static bool CDJXY
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJXY"] == "true";
			}
		}

		public static bool CDJZY1
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY1"] == "true";
			}
		}

		public static bool CDJZY2
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY2"] == "true";
			}
		}

		public static bool CDJZY3
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY3"] == "true";
			}
		}

		public static bool CDJZY4
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY4"] == "true";
			}
		}

		public static bool CDJZY5
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY5"] == "true";
			}
		}

		public static bool CDJZY6
		{
			get
			{
				return ConfigurationManager.AppSettings["CDJZY6"] == "true";
			}
		}

		public static string[] ChaFieldNames
		{
			get
			{
				return ConfigurationManager.AppSettings["ChaFieldNames"].Split(new char[] { '|' });
			}
		}

		public static string[] ChaFieldValues
		{
			get
			{
				return ConfigurationManager.AppSettings["ChaFieldValues"].Split(new char[] { '|' });
			}
		}

		public static int CJPExt
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CJPExt"]);
			}
		}

		public static int CJPLevel
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CJPLevel"]);
			}
		}

		public static int CJPSetVal
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["CJPSetVal"]);
			}
		}

		public static bool CJPXY
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPXY"] == "true";
			}
		}

		public static bool CJPZY1
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY1"] == "true";
			}
		}

		public static bool CJPZY2
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY2"] == "true";
			}
		}

		public static bool CJPZY3
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY3"] == "true";
			}
		}

		public static bool CJPZY4
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY4"] == "true";
			}
		}

		public static bool CJPZY5
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY5"] == "true";
			}
		}

		public static bool CJPZY6
		{
			get
			{
				return ConfigurationManager.AppSettings["CJPZY6"] == "true";
			}
		}

		public static int DJExt
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["DJExt"]);
			}
		}

		public static bool DJJN
		{
			get
			{
				return ConfigurationManager.AppSettings["DJJN"] == "true";
			}
		}

		public static int DJLevel
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["DJLevel"]);
			}
		}

		public static bool DJXY
		{
			get
			{
				return ConfigurationManager.AppSettings["DJXY"] == "true";
			}
		}

		public static bool DJZY1
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY1"] == "true";
			}
		}

		public static bool DJZY2
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY2"] == "true";
			}
		}

		public static bool DJZY3
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY3"] == "true";
			}
		}

		public static bool DJZY4
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY4"] == "true";
			}
		}

		public static bool DJZY5
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY5"] == "true";
			}
		}

		public static bool DJZY6
		{
			get
			{
				return ConfigurationManager.AppSettings["DJZY6"] == "true";
			}
		}

		public static int JPExt
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["JPExt"]);
			}
		}

		public static bool JPJN
		{
			get
			{
				return ConfigurationManager.AppSettings["JPJN"] == "true";
			}
		}

		public static int JPLevel
		{
			get
			{
				return Convert.ToInt32(ConfigurationManager.AppSettings["JPLevel"]);
			}
		}

		public static bool JPXY
		{
			get
			{
				return ConfigurationManager.AppSettings["JPXY"] == "true";
			}
		}

		public static bool JPZY1
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY1"] == "true";
			}
		}

		public static bool JPZY2
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY2"] == "true";
			}
		}

		public static bool JPZY3
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY3"] == "true";
			}
		}

		public static bool JPZY4
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY4"] == "true";
			}
		}

		public static bool JPZY5
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY5"] == "true";
			}
		}

		public static bool JPZY6
		{
			get
			{
				return ConfigurationManager.AppSettings["JPZY6"] == "true";
			}
		}

		static Utils()
		{
			Utils.lstSSG = new List<SKILL_SQL_GS>(150);
            Utils.ErrorMsg = "Access denied.";
            string[] strArrays = new string[] { "Ignore", "Weapon damage + 11", "Weapon skill damage + 11", "Staff/magic damage + 5", "Staff skill damage + 11", "Defense rate + 24", "Maximum life + 29" };
			Utils.YGS = strArrays;
            string[] strArrays1 = new string[] { "Fire", "Water", "Earth", "Wind", "Darkness" };
			Utils.YSS = strArrays1;
            string[] strArrays2 = new string[] { " ---No--- ", "Minimum damage force upgrade", "Maximum damage force upgrade", "Lower power requirement", "Lower agility requirement", "Minimum/maximum damage force upgrade", "Attack damage force upgrade", "Skill damage force upgrade", "Damage Success Rate upgrade (PVP)", "Reduced SD Rate Upgrade", "Ignore SD damage upgrade" };
			Utils.strPlusA = strArrays2;
            string[] strArrays3 = new string[] { " ---No--- ", "Enhance defense", "Maximum AG increase", "Maximum HP increase", "HP regen rate increase", "Mana regen rate increase", "Defense success rate upgrade (PVP)", "Damage reduction upgrade", "SD ratio upgrade" };
			Utils.strPlusB = strArrays3;
            string[] strArrays4 = new string[] { " ---No--- ", "Increased mana", "Reduced strength requirement", "Reduced agility requirement", "Skill damage increase", "Attack damage upgrade", "SD damage reduction upgrade", "Damage rate increase upgrade (PVP)", "Ignore SD damage chance upgrade" };
			Utils.strPlusC = strArrays4;
			char[] chrArray = new char[] { '|' };
            Utils.SearchNames = "greater than|equal|less than|not containing|like".Split(chrArray);
			char[] chrArray1 = new char[] { '|' };
			Utils.SearchValues = ">|=|<|<>|like".Split(chrArray1);
			Utils.SN = 0;
			Utils.ListWareHouse = new List<string>();
			Utils.ListPackage = new List<string>();
		}

		public Utils()
		{
		}

		public static string EncodeEncrypt(string str)
		{
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "sha1");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "md5");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "sha1");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "md5");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "md5");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "sha1");
			str = FormsAuthentication.HashPasswordForStoringInConfigFile(str, "sha1");
			return str;
		}

		public static string FilterSQL(string strSql)
		{
			return strSql.Trim().Replace("'", "''");
		}

		public static bool Get380(EquipItem item)
		{
			ushort nLvl = EquipEditor.xItem[item.Type * 512 + item.Code].NLvl;
			Trace.WriteLine(string.Concat("NLvl : ", nLvl));
			return nLvl == 380;
		}

		public static string GetBoolenStr(bool val)
		{
			if (!val)
			{
				return "×";
			}
			return "√";
		}

		public static string GetEquipInfo(EquipItem item)
		{
			if (item == null)
			{
                return "Error: Equipment could not be read.";
			}
			string name = item.Name;
			string str = "";
			string str1 = "";
			if (item.Is380)
			{
                str = string.Concat("\r\n☆380 properties：", Utils.GetBoolenStr(true));
			}
			if (item.IsSet)
			{
                name = string.Concat(name, "〖Set〗");
			}
			if (!Utils.GetQX(item) && item.PlusType > 0 && item.PlusLevel > 0)
			{
                name = string.Concat(name, "〖Enhanced〗");
                str1 = string.Concat("\r\n★Enhanced：", Utils.GetPlusStr(item));
			}
			object[] objArray = new object[] { name, item.ToString(), item.Level, item.Durability, string.Concat(str, str1), Utils.GetBoolenStr(item.XY), Utils.GetBoolenStr(item.JN) };
            string str2 = string.Format("Name：{0}\r\nItem code：{1}\r\nItem level：+{2}\r\nDurability：{3}{4}\r\nLuck：{5}\r\nSkill：{6}\r\n", objArray);
            str2 = string.Concat(str2, "※Excellent : ", Utils.GetZY(item), "\r\n");
            str2 = string.Concat(str2, "Options : ", item.Ext * 4);
			if (Utils.GetQX(item))
			{
				byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
				byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
				byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
				if (itemKindA != 8)
				{
					if (item.XQ1 == 255)
					{
                        str2 = string.Concat(str2, "\r\n※Socket 1：Empty");
					}
					else if (item.XQ1 != 254)
					{
						int xQ1 = item.XQ1 % 50;
						int num = (item.XQ1 - xQ1) / 50;
						string str3 = str2;
                        string[] strArrays = new string[] { str3, "\r\n※Socket 1：", frmMain.ByteToString(EquipEditor.xSocket[xQ1].捞抚, 64), " +", EquipEditor.xSocket[xQ1].饭骇1[num].ToString() };
						str2 = string.Concat(strArrays);
					}
					else
					{
                        str2 = string.Concat(str2, "\r\n※Socket 1：Empty");
					}
					if (item.XQ2 == 255)
					{
                        str2 = string.Concat(str2, "\r\n※Socket 2：Empty");
					}
					else if (item.XQ2 != 254)
					{
						int xQ2 = item.XQ2 % 50;
						int xQ21 = (item.XQ2 - xQ2) / 50;
						string str4 = str2;
                        string[] strArrays1 = new string[] { str4, "\r\n※Socket 2：", frmMain.ByteToString(EquipEditor.xSocket[xQ2].捞抚, 64), " +", EquipEditor.xSocket[xQ2].饭骇1[xQ21].ToString() };
						str2 = string.Concat(strArrays1);
					}
					else
					{
						str2 = string.Concat(str2, "\r\n※Socket 2：Empty");
					}
					if (item.XQ3 == 255)
					{
                        str2 = string.Concat(str2, "\r\n※Socket 3：Empty");
					}
					else if (item.XQ3 != 254)
					{
						int xQ3 = item.XQ3 % 50;
						int xQ31 = (item.XQ3 - xQ3) / 50;
						string str5 = str2;
                        string[] strArrays2 = new string[] { str5, "\r\n※Socket 3：", frmMain.ByteToString(EquipEditor.xSocket[xQ3].捞抚, 64), " +", EquipEditor.xSocket[xQ3].饭骇1[xQ31].ToString() };
						str2 = string.Concat(strArrays2);
					}
					else
					{
                        str2 = string.Concat(str2, "\r\n※Socket 3：Empty");
					}
					if (item.XQ4 == 255)
					{
                        str2 = string.Concat(str2, "\r\n※Socket 4：Empty");
					}
					else if (item.XQ4 != 254)
					{
						int xQ4 = item.XQ4 % 50;
						int xQ41 = (item.XQ4 - xQ4) / 50;
						string str6 = str2;
                        string[] strArrays3 = new string[] { str6, "\r\n※Socket 4：", frmMain.ByteToString(EquipEditor.xSocket[xQ4].捞抚, 64), " +", EquipEditor.xSocket[xQ4].饭骇1[xQ41].ToString() };
						str2 = string.Concat(strArrays3);
					}
					else
					{
                        str2 = string.Concat(str2, "\r\n※Socket 4：Empty");
					}
					if (item.XQ5 == 255)
					{
                        str2 = string.Concat(str2, "\r\n※Socket 5：Empty");
					}
					else if (item.XQ5 != 254)
					{
						int xQ5 = item.XQ5 % 50;
						int xQ51 = (item.XQ5 - xQ5) / 50;
						string str7 = str2;
                        string[] strArrays4 = new string[] { str7, "\r\n※Socket 5：", frmMain.ByteToString(EquipEditor.xSocket[xQ5].捞抚, 64), " +", EquipEditor.xSocket[xQ5].饭骇1[xQ51].ToString() };
						str2 = string.Concat(strArrays4);
					}
					else
					{
                        str2 = string.Concat(str2, "\r\n※Socket 5：Empty");
					}
                    str2 = (item.YG < 0 || item.YG >= (int)Utils.YGS.Length - 1 ? string.Concat(str2, "\r\n※Socket element : ", Utils.YGS[0]) : string.Concat(str2, "\r\n※Socket element : ", Utils.YGS[item.YG + 1]));
				}
				else
				{
					if (itemKindB == 0)
					{
						if (item.XQ1 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element 1：Empty");
						}
						else if (item.XQ1 == 0)
						{
                            str2 = string.Concat(str2, "\r\n※Element 1：Empty");
						}
						if (item.XQ2 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element 2：Empty");
						}
						else if (item.XQ2 == 0)
						{
                            str2 = string.Concat(str2, "\r\n※Element 2：Empty");
						}
						if (item.XQ3 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element 3：Empty");
						}
						else if (item.XQ3 == 0)
						{
                            str2 = string.Concat(str2, "\r\n※Element 3：Empty");
						}
						if (item.XQ4 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element 4：Empty");
						}
						else if (item.XQ4 == 0)
						{
                            str2 = string.Concat(str2, "\r\n※Element 4：Empty");
						}
						if (item.XQ5 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element 5：Empty");
						}
						else if (item.XQ5 == 0)
						{
                            str2 = string.Concat(str2, "\r\n※Element 5：Empty");
						}
					}
					else if (itemKindB == 43)
					{
						if (item.XQ1 != 255)
						{
                            str2 = (item.XQ1 != 254 ? string.Concat(str2, "\r\n※Element 1：Element (Fire)") : string.Concat(str2, "\r\n※Element 1：Element"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element 1：No sockets");
						}
						if (item.XQ2 != 255)
						{
                            str2 = (item.XQ2 != 254 ? string.Concat(str2, "\r\n※Element 2：Element (Water") : string.Concat(str2, "\r\n※Element 2：Element"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element 2：No sockets");
						}
						if (item.XQ3 != 255)
						{
                            str2 = (item.XQ3 != 254 ? string.Concat(str2, "\r\n※Element 3：Element (Earth)") : string.Concat(str2, "\r\n※Element 3：Element"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element 3：No sockets");
						}
						if (item.XQ4 != 255)
						{
                            str2 = (item.XQ4 != 254 ? string.Concat(str2, "\r\n※Element 4：Element (Air)") : string.Concat(str2, "\r\n※Element 4：Element"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element 4：No sockets");
						}
						if (item.XQ5 != 255)
						{
                            str2 = (item.XQ5 != 254 ? string.Concat(str2, "\r\n※Element 5：Element (Darkness)") : string.Concat(str2, "\r\n※Element 5：Element"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element 5：No sockets");
						}
					}
					else if (itemKindB == 44)
					{
						if (item.XQ1 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：None");
						}
						else if (item.XQ1 == 17)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +1");
						}
						else if (item.XQ1 == 33)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +2");
						}
						else if (item.XQ1 == 49)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +3");
						}
						else if (item.XQ1 == 65)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +4");
						}
						else if (item.XQ1 == 81)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +5");
						}
						else if (item.XQ1 == 97)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +6");
						}
						else if (item.XQ1 == 113)
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +7");
						}
						else if (item.XQ1 != 129)
						{
                            str2 = (item.XQ1 != 145 ? string.Concat(str2, "\r\n※Element1：1st element +10") : string.Concat(str2, "\r\n※Element1：1st element +9"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element1：1st element +8");
						}
						if (item.XQ2 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：None");
						}
						else if (item.XQ2 == 17)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +1");
						}
						else if (item.XQ2 == 33)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +2");
						}
						else if (item.XQ2 == 49)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +3");
						}
						else if (item.XQ2 == 65)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +4");
						}
						else if (item.XQ2 == 81)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +5");
						}
						else if (item.XQ2 == 97)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +6");
						}
						else if (item.XQ2 == 113)
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +7");
						}
						else if (item.XQ2 != 129)
						{
                            str2 = (item.XQ2 != 145 ? string.Concat(str2, "\r\n※Element2：2nd element +10") : string.Concat(str2, "\r\n※Element2：2nd element +9"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element2：2nd element +8");
						}
						if (item.XQ3 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：None");
						}
						else if (item.XQ3 == 17)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +1");
						}
						else if (item.XQ3 == 33)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +2");
						}
						else if (item.XQ3 == 49)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +3");
						}
						else if (item.XQ3 == 65)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +4");
						}
						else if (item.XQ3 == 81)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +5");
						}
						else if (item.XQ3 == 97)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +6");
						}
						else if (item.XQ3 == 113)
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +7");
						}
						else if (item.XQ3 != 129)
						{
                            str2 = (item.XQ3 != 145 ? string.Concat(str2, "\r\n※Element3：3rd element +10") : string.Concat(str2, "\r\n※Element3：3rd element +9"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element3：3rd element +8");
						}
						if (item.XQ4 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：None");
						}
						else if (item.XQ4 == 17)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +1");
						}
						else if (item.XQ4 == 33)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +2");
						}
						else if (item.XQ4 == 49)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +3");
						}
						else if (item.XQ4 == 65)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +4");
						}
						else if (item.XQ4 == 81)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +5");
						}
						else if (item.XQ4 == 97)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +6");
						}
						else if (item.XQ4 == 113)
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +7");
						}
						else if (item.XQ4 != 129)
						{
                            str2 = (item.XQ4 != 145 ? string.Concat(str2, "\r\n※Element4：4th element +10") : string.Concat(str2, "\r\n※Element4：4th element +9"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element4：4th element +8");
						}
						if (item.XQ5 == 255)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：None");
						}
						else if (item.XQ5 == 17)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +1");
						}
						else if (item.XQ5 == 33)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +2");
						}
						else if (item.XQ5 == 49)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +3");
						}
						else if (item.XQ5 == 65)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +4");
						}
						else if (item.XQ5 == 81)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +5");
						}
						else if (item.XQ5 == 97)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +6");
						}
						else if (item.XQ5 == 113)
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +7");
						}
						else if (item.XQ5 != 129)
						{
                            str2 = (item.XQ5 != 145 ? string.Concat(str2, "\r\n※Element5：5th element +10") : string.Concat(str2, "\r\n※Element5：5th element +9"));
						}
						else
						{
                            str2 = string.Concat(str2, "\r\n※Element5：5th element +8");
						}
					}
                    str2 = (item.YG < 0 || item.YG - 17 >= (int)Utils.YSS.Length ? string.Concat(str2, "\r\n※Element：", Utils.YSS[0]) : string.Concat(str2, "\r\n※Element：", Utils.YSS[item.YG - 17]));
				}
			}
			str2 = string.Concat(str2, string.Format("", item.SN, Utils.GetSNStr(item.SN)));
			return str2;
		}

		public static string GetID()
		{
			string[] strArrays = Guid.NewGuid().ToString().Split(new char[] { '-' });
			return string.Concat(strArrays[3], strArrays[4]);
		}

		public static bool GetJN(EquipItem item)
		{
			ushort skillType = EquipEditor.xItem[item.Type * 512 + item.Code].SkillType;
			Trace.WriteLine(string.Concat("SkillType : ", skillType));
			return skillType != 0;
		}

		public static string GetMachineID()
		{
			string str;
			try
			{
				SelectQuery selectQuery = new SelectQuery("SELECT * FROM Win32_BaseBoard");
				ManagementObjectCollection.ManagementObjectEnumerator enumerator = (new ManagementObjectSearcher(selectQuery)).Get().GetEnumerator();
				enumerator.MoveNext();
				ManagementBaseObject current = enumerator.Current;
				StringBuilder stringBuilder = new StringBuilder();
				stringBuilder.Append(current.GetPropertyValue("SerialNumber").ToString());
				if (stringBuilder.ToString().Trim().Length < 5)
				{
					foreach (ManagementObject instance in (new ManagementClass("Win32_NetworkAdapterConfiguration")).GetInstances())
					{
						if ((bool)instance["IPEnabled"])
						{
							stringBuilder.Append(instance["MacAddress"].ToString());
						}
						instance.Dispose();
					}
				}
				str = string.Concat("S7", stringBuilder.ToString().Trim());
			}
			catch
			{
				str = "";
			}
			return str;
		}

		public static string GetPlusStr(EquipItem item)
		{
			if (item.Type >= 0 && item.Type <= 5)
			{
				return Utils.strPlusA[item.PlusType];
			}
			if (item.Type < 6 || item.Type > 11)
			{
				return Utils.GetBoolenStr(false);
			}
			return Utils.strPlusB[item.PlusType];
		}

		public static void GetPlusType(ComboBox cboPlusType, int plusType)
		{
			cboPlusType.Items.Clear();
			if (plusType == 1)
			{
				string[] strArrays = Utils.strPlusA;
				for (int i = 0; i < (int)strArrays.Length; i++)
				{
					string str = strArrays[i];
					cboPlusType.Items.Add(str);
				}
				return;
			}
			if (plusType == 2)
			{
				string[] strArrays1 = Utils.strPlusB;
				for (int j = 0; j < (int)strArrays1.Length; j++)
				{
					string str1 = strArrays1[j];
					cboPlusType.Items.Add(str1);
				}
				return;
			}
			if (plusType != 3)
			{
                cboPlusType.Items.Add(" ---No---");
				cboPlusType.SelectedIndex = 0;
				return;
			}
			string[] strArrays2 = Utils.strPlusC;
			for (int k = 0; k < (int)strArrays2.Length; k++)
			{
				string str2 = strArrays2[k];
				cboPlusType.Items.Add(str2);
			}
		}

		public static bool GetQX(EquipItem item)
		{
			byte itemKindA = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindA;
			Trace.WriteLine(string.Concat("ItemKind A : ", itemKindA));
			byte itemKindB = EquipEditor.xItem[item.Type * 512 + item.Code].ItemKindB;
			Trace.WriteLine(string.Concat("ItemKind B : ", itemKindB));
			byte itemCategory = EquipEditor.xItem[item.Type * 512 + item.Code].ItemCategory;
			Trace.WriteLine(string.Concat("ItemCategory : ", itemCategory));
			if (itemCategory == 2)
			{
				return true;
			}
			return itemKindA == 8;
		}

		public static string GetSNStr(int sn)
		{
			if (sn < 0)
			{
                return "GM items";
			}
			if (sn != 0)
			{
                return "Normal items";
			}
            return "Store items";
		}

		public static string GetZY(EquipItem item)
		{
			string str = "";
            string str1 = "Increase mana after kill/8 | Zen after kill+40%";
            string str2 = "Increase life after kill/8 | Defense Success Rate+10%";
            string str3 = "Speed + 7 | Reflect damage 5%";
            string str4 = "Increase damage +2% | Damage decrease 4%";
            string str5 = "Increase damage + level/20 | Increase MP 4%";
            string str6 = "Excellent damage rate + 10% | Increase HP +4%";
			switch (item.Type)
			{
				case 12:
				{
					if ((item.Code < 3 || item.Code > 6) && item.Code != 42)
					{
						if ((item.Code < 36 || item.Code > 40) && item.Code != 43)
						{
							break;
						}
                        str1 = "Ignore";
                        str2 = "Restore damage";
                        str3 = "Restore life";
                        str4 = "Restore mana";
						str5 = "Recovery";
                        str6 = "Recovery";
						break;
					}
					else
					{
                        str1 = "Add HP";
                        str2 = "Add MP";
                        str3 = "Ignore";
                        str4 = "Skill values";
                        str5 = "Speed";
                        str6 = "Recovery";
						break;
					}
				}
				case 13:
				{
					ushort code = item.Code;
					if (code == 30)
					{
                        str1 = "Add HP";
                        str2 = "Add MP";
                        str3 = "Ignore";
                        str4 = "Add VIP";
						break;
					}
					else if (code == 37)
					{
                        str1 = "Black Wolf";
                        str2 = "Green Wolf";
                        str3 = "Golden Wolf";
						break;
					}
					else
					{
						break;
					}
				}
			}
			str = string.Concat(str, (item.ZY1 ? string.Concat("\r\n\t", str1) : ""));
			str = string.Concat(str, (item.ZY2 ? string.Concat("\r\n\t", str2) : ""));
			str = string.Concat(str, (item.ZY3 ? string.Concat("\r\n\t", str3) : ""));
			str = string.Concat(str, (item.ZY4 ? string.Concat("\r\n\t", str4) : ""));
			str = string.Concat(str, (item.ZY5 ? string.Concat("\r\n\t", str5) : ""));
			str = string.Concat(str, (item.ZY6 ? string.Concat("\r\n\t", str6) : ""));
			if (str != "")
			{
				return str;
			}
			return Utils.GetBoolenStr(false);
		}

		public static string HexJN(byte[] bytes)
		{
			return string.Concat(bytes[0].ToString("X2"), bytes[1].ToString("X2"), bytes[2].ToString("X2"));
		}

		public static void InfoMessage(string msg)
		{
            MessageBox.Show(msg, "Note: ", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
		}

		public static bool IsRight()
		{
			return true;
		}

		public static string SKILL_GS2SQL(SKILL_SQL_GS ssg)
		{
			byte[] numArray = new byte[3];
			int num = 0;
			int gSSkillID = ssg.GSSkillID;
			int num1 = gSSkillID;
			byte sKillLv = ssg.SKillLv;
			int num2 = 0;
			if (gSSkillID > 765)
			{
				num = 3;
				num1 = 255;
				num2 = gSSkillID - num1 * num;
			}
			else if (gSSkillID > 510)
			{
				num = 2;
				num1 = 255;
				num2 = gSSkillID - num1 * num;
			}
			else if (gSSkillID <= 255)
			{
				num = 0;
			}
			else
			{
				num = 1;
				num1 = 255;
				num2 = gSSkillID - num1 * num;
			}
			numArray[0] = (byte)num1;
			numArray[1] = (byte)(sKillLv * 8 | num & 7);
			numArray[2] = (byte)num2;
			return string.Concat(numArray[0].ToString("X2"), numArray[1].ToString("X2"), numArray[2].ToString("X2"));
		}

		public static SKILL_SQL_GS SKILL_SQL2GS(byte[] szSQLSKILL)
		{
			int num = szSQLSKILL[0];
			bool flag = (szSQLSKILL[1] & 7) != 0;
			byte num1 = 0;
			if (flag)
			{
				num1 = (byte)(szSQLSKILL[1] / 8);
				num = num * (szSQLSKILL[1] & 7) + szSQLSKILL[2];
			}
			return new SKILL_SQL_GS()
			{
				SKillLv = num1,
				GSSkillID = num
			};
		}

		public static byte[] StringToBytes(string strCode)
		{
			strCode = strCode.Replace("0x", "");
			byte[] num = new byte[strCode.Length / 2];
			for (int i = 0; i < (int)num.Length; i++)
			{
				num[i] = Convert.ToByte(strCode.Substring(i * 2, 2), 16);
			}
			return num;
		}

		public static void WarningMessage(string msg)
		{
            MessageBox.Show(msg, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
		}
	}
}