using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Library.Common
{
	public class IniClass
	{
		private string path;

		public IniClass(string INIPath)
		{
			this.path = INIPath;
		}

		[DllImport("kernel32", CharSet=CharSet.None, ExactSpelling=false)]
		private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

		public string IniReadValue(string Section, string Key)
		{
			StringBuilder stringBuilder = new StringBuilder(255);
			IniClass.GetPrivateProfileString(Section, Key, "", stringBuilder, 255, this.path);
			return stringBuilder.ToString();
		}

		public string IniReadValue(string Section, string Key, string DefValue)
		{
			StringBuilder stringBuilder = new StringBuilder(255);
			if (IniClass.GetPrivateProfileString(Section, Key, "", stringBuilder, 255, this.path) <= 0)
			{
				return DefValue;
			}
			return stringBuilder.ToString();
		}

		public void IniWriteValue(string Section, string Key, string Value)
		{
			IniClass.WritePrivateProfileString(Section, Key, Value, this.path);
		}

		public void IniWriteValue(string Section, string Key, string Value, string DefValue)
		{
			Value = (Value == null ? "" : Value);
			if ((Value == "" || Value == null) && DefValue != "" && DefValue != null)
			{
				Value = DefValue;
			}
			IniClass.WritePrivateProfileString(Section, Key, Value, this.path);
		}

		[DllImport("kernel32", CharSet=CharSet.None, ExactSpelling=false)]
		private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
	}
}