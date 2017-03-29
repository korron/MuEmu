using System;
using System.IO;

namespace MuEditor
{
	public class ItemClass
	{
		public ITEM_ATTRIBUTE[] ItemAttribute = new ITEM_ATTRIBUTE[8192];

		public ItemClass(string FileName)
		{
			byte[] numArray = new byte[] { 252, 207, 171 };
			int num = 628;
			FileStream fileStream = new FileStream(FileName, FileMode.Open);
			byte[] numArray1 = new byte[4];
			fileStream.Read(numArray1, 0, 4);
			int num1 = BitConverter.ToInt32(numArray1, 0);
			for (int i = 0; i < num1; i++)
			{
				int num2 = 0;
				ITEM_ATTRIBUTE tEMATTRIBUTE = new ITEM_ATTRIBUTE();
				numArray1 = new byte[num];
				fileStream.Read(numArray1, 0, num);
				for (int j = 0; j < num; j++)
				{
					numArray1[j] = (byte)(numArray1[j] ^ numArray[j % 3]);
				}
				tEMATTRIBUTE.GID = BitConverter.ToInt32(numArray1, num2);
				num2 = num2 + 4;
				tEMATTRIBUTE.Group = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Index = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				Array.Copy(numArray1, num2, tEMATTRIBUTE.Model_Folder, 0, 260);
				num2 = num2 + 260;
				Array.Copy(numArray1, num2, tEMATTRIBUTE.Model_Name, 0, 260);
				num2 = num2 + 260;
				Array.Copy(numArray1, num2, tEMATTRIBUTE.Name, 0, 30);
				num2 = num2 + 30;
				tEMATTRIBUTE.ItemKindA = numArray1[num2];
				num2++;
				tEMATTRIBUTE.ItemKindB = numArray1[num2];
				num2++;
				tEMATTRIBUTE.ItemCategory = numArray1[num2];
				num2++;
				tEMATTRIBUTE.TwoHand = BitConverter.ToBoolean(numArray1, num2);
				num2++;
				tEMATTRIBUTE.Level = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.ItemSlot = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.SkillType = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.X = numArray1[num2];
				num2++;
				tEMATTRIBUTE.Y = numArray1[num2];
				num2++;
				tEMATTRIBUTE.DamMin = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.DamMax = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.MagDef = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Defence = BitConverter.ToInt32(numArray1, num2);
				num2 = num2 + 4;
				tEMATTRIBUTE.AtkSpeed = numArray1[num2];
				num2++;
				tEMATTRIBUTE.WalkSpeed = numArray1[num2];
				num2++;
				tEMATTRIBUTE.Dur = numArray1[num2];
				num2++;
				tEMATTRIBUTE.MagicDur = numArray1[num2];
				num2++;
				tEMATTRIBUTE.MagicPW = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Str = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Dex = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Eng = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Hea = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Cha = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.NLvl = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Value = BitConverter.ToUInt16(numArray1, num2);
				num2 = num2 + 2;
				tEMATTRIBUTE.Zen = BitConverter.ToUInt32(numArray1, num2);
				num2 = num2 + 4;
				tEMATTRIBUTE.技飘加己 = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.WIZARD = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.KNIGHT = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.ELF = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.MAGUMSA = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.DARKLORD = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.SUMMONER = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iClassNumber.MONK = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.ICE = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.POISON = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.LIGHTNING = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.FIRE = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.EARTH = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.WIND = numArray1[num2];
				num2++;
				tEMATTRIBUTE.iAttribute.WATER = numArray1[num2];
				num2++;
				this.ItemAttribute[tEMATTRIBUTE.GID] = tEMATTRIBUTE;
			}
		}
	}
}