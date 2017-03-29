using System;
using System.Collections;

namespace MuEditor
{
	public class EquipItemType
	{
		private byte typeId;

		private string name;

		private IList itemNames;

		public IList ItemNames
		{
			get
			{
				return this.itemNames;
			}
			set
			{
				this.itemNames = value;
			}
		}

		public string Name
		{
			get
			{
				return this.name;
			}
		}

		public byte TypeId
		{
			get
			{
				return this.typeId;
			}
		}

		public EquipItemType()
		{
		}

		public EquipItemType(byte typeId, string name)
		{
			this.typeId = typeId;
			this.name = name;
		}

		public override string ToString()
		{
			return this.name;
		}
	}
}