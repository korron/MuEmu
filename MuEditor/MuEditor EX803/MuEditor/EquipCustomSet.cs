using System;
using System.Collections;
using System.Text;

namespace MuEditor
{
	public class EquipCustomSet
	{
		public const int MAX_ITEM_NUM = 15;

		private string name;

		private byte classType;

		private byte membLvl;

		private EquipItem[] items = new EquipItem[15];

		public byte ClassType
		{
			get
			{
				return this.classType;
			}
			set
			{
				this.classType = value;
			}
		}

		public EquipItem[] Items
		{
			get
			{
				return this.items;
			}
		}

		public byte MembLvl
		{
			get
			{
				return this.membLvl;
			}
			set
			{
				this.membLvl = value;
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
				this.name = value;
			}
		}

		public EquipCustomSet()
		{
		}

		public string[] getItemsCodes()
		{
			string[] str = new string[15];
			for (int i = 0; i < 15; i++)
			{
				if (this.items[i] != null)
				{
					str[i] = this.items[i].ToString();
				}
				else
				{
					str[i] = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
				}
			}
			return str;
		}

		public string GetItemsCodes()
		{
			StringBuilder stringBuilder = new StringBuilder();
			for (int i = 0; i < 15; i++)
			{
				if (this.items[i] != null)
				{
					stringBuilder.Append(this.items[i].ToString());
				}
				else
				{
					stringBuilder.Append("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
				}
			}
			return stringBuilder.ToString();
		}

		public bool setItem(int pos, string scodes)
		{
			if (pos < 0 || pos >= 15)
			{
				return false;
			}
			this.items[pos] = EquipItem.createItem(scodes);
			return this.items[pos] != null;
		}

		public bool setItems(IList items)
		{
			for (int i = 0; i < items.Count; i++)
			{
				this.items[i] = (EquipItem)items[i];
			}
			return true;
		}

		public override string ToString()
		{
			return this.name;
		}
	}
}