using System;
using System.Drawing;
using System.Reflection;
using System.Resources;
using System.Text;

namespace MuEditor
{
	public class EquipItem
	{
		public const string UNKNOW_ITEM = "unknownItem";

		public const int ITEM_SIZE = 16;

		private byte xnum = 1;

		private byte ynum = 1;

		private string name;

		private bool hand;

		private int profs;

		private byte[] codes = new byte[] { 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255 };

		private Image img;

		private bool isFZ;

		private static EquipItem unknownItem;

		public ushort Code
		{
			get
			{
				return (ushort)(this.codes[0] + (this.codes[7] & 128) * 2);
			}
			set
			{
				this.codes[0] = (byte)value;
				this.codes[7] = (byte)(value >> 1 & 128);
			}
		}

		public string CodeType
		{
			get
			{
				return EquipItem.getItemCodeType(this.codes);
			}
		}

		public byte Durability
		{
			get
			{
				return this.codes[2];
			}
			set
			{
				this.codes[2] = value;
			}
		}

		public int Ext
		{
			get
			{
				return ((this.codes[7] & 64) >> 4) + (this.codes[1] & 3);
			}
			set
			{
				this.modifyExt(value);
			}
		}

		public bool Hand
		{
			get
			{
				return this.hand;
			}
		}

		public byte Height
		{
			get
			{
				return this.ynum;
			}
		}

		public Image Img
		{
			get
			{
				return this.img;
			}
			set
			{
				if (this.img != value)
				{
					this.img = value;
				}
			}
		}

		public bool Is380
		{
			get
			{
				return (this.codes[9] & 15) != 0;
			}
			set
			{
				if (value)
				{
					this.codes[9] = (byte)(this.codes[9] | 8);
				}
			}
		}

		public bool IsFZ
		{
			get
			{
				return this.isFZ;
			}
		}

		public bool IsNoDurability
		{
			get
			{
				return this.codes[9] == 224;
			}
		}

		public bool IsSet
		{
			get
			{
				return (this.codes[8] & 12) != 0;
			}
			set
			{
				this.codes[8] = (byte)(this.codes[8] & 240);
			}
		}

		public bool JN
		{
			get
			{
				return (this.codes[1] & 128) != 0;
			}
			set
			{
				this.modifyJN(value);
			}
		}

		public byte Level
		{
			get
			{
				return (byte)((this.codes[1] & 120) >> 3);
			}
			set
			{
				this.modifyLevel((int)value);
			}
		}

		public string Name
		{
			get
			{
				return this.name;
			}
			set
			{
				if (this.name != value)
				{
					this.name = value;
				}
			}
		}

		public int PlusLevel
		{
			get
			{
				return this.codes[10] & 15;
			}
			set
			{
				this.modifyPlusLevel(value);
			}
		}

		public int PlusType
		{
			get
			{
				if (this.codes[10] == 255)
				{
					return 0;
				}
				return this.codes[10] >> 4;
			}
			set
			{
				this.modifyPlusType(value);
			}
		}

		public byte SetVal
		{
			get
			{
				if (this.codes[8] <= 15)
				{
					return this.codes[8];
				}
				return Convert.ToByte(string.Concat(this.codes[8].ToString().ToCharArray()[1]));
			}
			set
			{
				this.codes[8] = (byte)(Convert.ToByte(string.Concat(this.codes[8].ToString().ToCharArray()[0])) + value);
			}
		}

		public int SN
		{
			get
			{
				return Convert.ToInt32(this.ToString().Substring(6, 8), 16);
			}
			set
			{
				char[] charArray = value.ToString("X8").ToCharArray();
				this.codes[3] = (byte)Convert.ToInt32(string.Concat(charArray[0], charArray[1]), 16);
				this.codes[4] = (byte)Convert.ToInt32(string.Concat(charArray[2], charArray[3]), 16);
				this.codes[5] = (byte)Convert.ToInt32(string.Concat(charArray[4], charArray[5]), 16);
				this.codes[6] = (byte)Convert.ToInt32(string.Concat(charArray[6], charArray[7]), 16);
			}
		}

		public ushort Type
		{
			get
			{
				return (byte)(this.codes[9] >> 4);
			}
			set
			{
				this.codes[9] = (byte)(this.codes[9] & 15);
				this.codes[9] = (byte)(this.codes[9] | value << 4);
			}
		}

		public static EquipItem UnknownItem
		{
			get
			{
				return EquipItem.unknownItem;
			}
		}

		public byte Width
		{
			get
			{
				return this.xnum;
			}
		}

		public byte XQ1
		{
			get
			{
				return this.codes[11];
			}
			set
			{
				this.codes[11] = value;
			}
		}

		public byte XQ2
		{
			get
			{
				return this.codes[12];
			}
			set
			{
				this.codes[12] = value;
			}
		}

		public byte XQ3
		{
			get
			{
				return this.codes[13];
			}
			set
			{
				this.codes[13] = value;
			}
		}

		public byte XQ4
		{
			get
			{
				return this.codes[14];
			}
			set
			{
				this.codes[14] = value;
			}
		}

		public byte XQ5
		{
			get
			{
				return this.codes[15];
			}
			set
			{
				this.codes[15] = value;
			}
		}

		public bool XY
		{
			get
			{
				return (this.codes[1] & 4) != 0;
			}
			set
			{
				this.modifyXY(value);
			}
		}

		public byte YG
		{
			get
			{
				return this.codes[10];
			}
			set
			{
				this.codes[10] = value;
			}
		}

		public bool ZY1
		{
			get
			{
				return (this.codes[7] & 1) != 0;
			}
			set
			{
				this.modifyZY1(value);
			}
		}

		public bool ZY2
		{
			get
			{
				return (this.codes[7] & 2) != 0;
			}
			set
			{
				this.modifyZY2(value);
			}
		}

		public bool ZY3
		{
			get
			{
				return (this.codes[7] & 4) != 0;
			}
			set
			{
				this.modifyZY3(value);
			}
		}

		public bool ZY4
		{
			get
			{
				return (this.codes[7] & 8) != 0;
			}
			set
			{
				this.modifyZY4(value);
			}
		}

		public bool ZY5
		{
			get
			{
				return (this.codes[7] & 16) != 0;
			}
			set
			{
				this.modifyZY5(value);
			}
		}

		public bool ZY6
		{
			get
			{
				return (this.codes[7] & 32) != 0;
			}
			set
			{
				this.modifyZY6(value);
			}
		}

		static EquipItem()
		{
			EquipItem.unknownItem = EquipItem.createUnknownItem();
		}

		public EquipItem()
		{
		}

		public EquipItem(EquipItem baseItem)
		{
			this.xnum = baseItem.xnum;
			this.ynum = baseItem.ynum;
			this.name = baseItem.name;
			this.hand = baseItem.hand;
			this.profs = baseItem.profs;
			this.img = baseItem.img;
		}

		public EquipItem(ushort code, string name, bool hand, ushort type, byte xnum, byte ynum, int profs, bool isfz)
		{
			this.Code = code;
			this.Type = type;
			this.name = name;
			this.hand = hand;
			this.xnum = xnum;
			this.ynum = ynum;
			this.profs = profs;
			this.isFZ = isfz;
		}

		public EquipItem(EquipItem baseItem, byte[] codes)
		{
			this.xnum = baseItem.xnum;
			this.ynum = baseItem.ynum;
			this.name = baseItem.name;
			this.hand = baseItem.hand;
			this.profs = baseItem.profs;
			this.img = baseItem.img;
			codes.CopyTo(this.codes, 0);
		}

		public EquipItem(EquipItem baseItem, byte[] codes, int offset, int len)
		{
			this.xnum = baseItem.xnum;
			this.ynum = baseItem.ynum;
			this.name = baseItem.name;
			this.hand = baseItem.hand;
			this.profs = baseItem.profs;
			this.img = baseItem.img;
			Array.Copy(codes, offset, this.codes, 0, len);
		}

		public EquipItem assign(EquipItem other)
		{
			other.codes.CopyTo(this.codes, 0);
			this.xnum = other.xnum;
			this.ynum = other.ynum;
			this.name = other.name;
			this.hand = other.hand;
			this.profs = other.profs;
			this.img = other.img;
			return this;
		}

		public static EquipItem createItem(string scodes)
		{
			EquipItem equipItem;
			if (scodes.Length != 32)
			{
				return null;
			}
			scodes = scodes.ToUpper();
            if (scodes.StartsWith("FF"))
			{
				return null;
			}
			byte[] num = new byte[16];
			try
			{
				for (int i = 0; i < 16; i++)
				{
					num[i] = Convert.ToByte(scodes.Substring(i * 2, 2), 16);
				}
				return EquipItem.createItem(num);
			}
			catch (Exception exception)
			{
				equipItem = null;
			}
			return equipItem;
		}

		public static EquipItem createItem(byte[] codes)
		{
			return EquipItem.createItem(codes, 0, 16);
		}

		public static EquipItem createItem(byte[] codes, int offset, int len)
		{
			if (offset < 0 || len <= 0 || offset + len > (int)codes.Length || codes[offset] == 255)
			{
				return null;
			}
			string itemCodeType = EquipItem.getItemCodeType(codes, offset, len);
			EquipItem itemByCodeType = EquipImageCache.Instance.getItemByCodeType(itemCodeType);
			return new EquipItem(itemByCodeType, codes, offset, len);
		}

		public static EquipItem createItem(ushort code, ushort type)
		{
			string itemCodeType = EquipItem.getItemCodeType(code, type);
			return new EquipItem(EquipImageCache.Instance.getItemByCodeType(itemCodeType));
		}

		protected static EquipItem createUnknownItem()
		{
			EquipItem equipItem = new EquipItem()
			{
				Name = "unknownItem",
				hand = true,
				profs = 255
			};
			ResourceManager resourceManager = new ResourceManager("MuEditor.Properties.Resources", Assembly.GetExecutingAssembly());
			equipItem.Img = (Image)resourceManager.GetObject("unknownItem");
			return equipItem;
		}

		public byte[] getCodes()
		{
			return this.codes;
		}

		public static ushort getItemCode(string codeType)
		{
			if (codeType == null || codeType == null)
			{
				return (ushort)65535;
			}
			return Convert.ToUInt16(codeType.Substring(0, 4), 16);
		}

		public static string getItemCodeType(byte[] codes)
		{
			if ((int)codes.Length < 16)
			{
				return null;
			}
			return string.Format("{0:X2}{1:X2}{2:X2}", (codes[7] & 128) * 2 >> 8, codes[0], codes[9]);
		}

		public static string getItemCodeType(byte[] codes, int offset, int len)
		{
			if (offset < 0 || len <= 0 || offset + len > (int)codes.Length || len < 16)
			{
				return "unknownItem";
			}
			return string.Format("{0:X2}{1:X2}{2:X2}", (codes[offset + 7] & 128) * 2 >> 8, codes[offset], codes[offset + 9] >> 4);
		}

		public static string getItemCodeType(ushort code, ushort type)
		{
			return string.Format("{0:X2}{1:X2}{2:X2}", code >> 8, code & 255, type);
		}

		public static byte getItemType(string codeType)
		{
			if (codeType == null || codeType == null)
			{
				return (byte)255;
			}
			return Convert.ToByte(codeType.Substring(4, 2), 16);
		}

		public void modifyExt(int ext)
		{
			this.codes[1] = (byte)(this.codes[1] & 252);
			this.codes[7] = (byte)(this.codes[7] & 191);
			byte num = (byte)(4 & ext);
			this.codes[7] = (byte)(this.codes[7] | num << 4);
			ext = 3 & ext;
			this.codes[1] = (byte)(this.codes[1] | ext);
		}

		public void modifyJN(bool flag)
		{
			if (flag)
			{
				this.codes[1] = (byte)(this.codes[1] | 128);
				return;
			}
			this.codes[1] = (byte)(this.codes[1] & 127);
		}

		public void modifyLevel(int level)
		{
			this.codes[1] = (byte)(this.codes[1] & 135);
			this.codes[1] = (byte)(this.codes[1] | level << 3);
		}

		public void modifyPlusLevel(int level)
		{
			this.codes[10] = (byte)(this.codes[10] & 240);
			this.codes[10] = (byte)(this.codes[10] | level);
		}

		public void modifyPlusType(int type)
		{
			this.codes[10] = (byte)(this.codes[10] & 15);
			this.codes[10] = (byte)(this.codes[10] | type << 4);
		}

		public void modifyXY(bool flag)
		{
			if (flag)
			{
				this.codes[1] = (byte)(this.codes[1] | 4);
				return;
			}
			this.codes[1] = (byte)(this.codes[1] & 251);
		}

		public void modifyZY1(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 1);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 254);
		}

		public void modifyZY2(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 2);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 253);
		}

		public void modifyZY3(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 4);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 251);
		}

		public void modifyZY4(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 8);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 247);
		}

		public void modifyZY5(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 16);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 239);
		}

		public void modifyZY6(bool flag)
		{
			if (flag)
			{
				this.codes[7] = (byte)(this.codes[7] | 32);
				return;
			}
			this.codes[7] = (byte)(this.codes[7] & 223);
		}

		public static string toHex(byte[] codes, int offset, int len)
		{
			StringBuilder stringBuilder = new StringBuilder();
			for (int i = 0; i < len; i++)
			{
				stringBuilder.Append(codes[offset + i].ToString("X2"));
			}
			return stringBuilder.ToString();
		}

		public override string ToString()
		{
			StringBuilder stringBuilder = new StringBuilder();
			for (int i = 0; i < 16; i++)
			{
				stringBuilder.Append(this.codes[i].ToString("X2"));
			}
			return stringBuilder.ToString();
		}
	}
}