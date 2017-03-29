using System;
using System.IO;

namespace MuEditor
{
	public class SkillClass
	{
		public CMagicDamage[] cMagic = new CMagicDamage[700];

		public SkillClass(string FileName)
		{
			byte[] numArray = new byte[] { 252, 207, 171 };
			int num = 96;
			FileInfo fileInfo = new FileInfo(FileName);
			long length = (fileInfo.Length - (long)4) / (long)num;
			FileStream fileStream = new FileStream(FileName, FileMode.Open);
			for (int i = 0; (long)i < length; i++)
			{
				int num1 = 0;
				CMagicDamage cMagicDamage = new CMagicDamage();
				byte[] numArray1 = new byte[num];
				fileStream.Read(numArray1, 0, num);
				for (int j = 0; j < num; j++)
				{
					numArray1[j] = (byte)(numArray1[j] ^ numArray[j % 3]);
				}
				cMagicDamage.m_Number = i;
				Array.Copy(numArray1, num1, cMagicDamage.Name, 0, 32);
				num1 = num1 + 32;
				cMagicDamage.饭骇 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.单固瘤 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.荤侩付唱樊 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.绢呼府萍 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.芭府 = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				cMagicDamage.Delay = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				cMagicDamage.Eng = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				cMagicDamage.Cha = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.加己 = numArray1[num1];
				num1++;
				cMagicDamage.SkilluseType = numArray1[num1];
				num1++;
				cMagicDamage.SkillBrand = BitConverter.ToInt32(numArray1, num1);
				num1 = num1 + 4;
				cMagicDamage.KillCout = numArray1[num1];
				num1++;
				cMagicDamage.iStatuNumber.stOne = numArray1[num1];
				num1++;
				cMagicDamage.iStatuNumber.stTwo = numArray1[num1];
				num1++;
				cMagicDamage.iStatuNumber.stThe = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.WIZARD = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.KNIGHT = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.ELF = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.MAGUMSA = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.DARKLORD = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.SUMMONER = numArray1[num1];
				num1++;
				cMagicDamage.iClassNumber.MONK = numArray1[num1];
				num1++;
				cMagicDamage.胶懦珐农 = numArray1[num1];
				num1++;
				cMagicDamage.酒捞能锅龋 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.胶懦鸥涝 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.鞘夸塞 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.家葛眉仿 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.家葛SD = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.鞘夸刮酶 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.公扁胶懦 = numArray1[num1];
				num1++;
				cMagicDamage.单固瘤备盒 = numArray1[num1];
				num1++;
				cMagicDamage.滚橇牢郸胶 = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				cMagicDamage.鸥百措惑 = numArray1[num1];
				num1++;
				cMagicDamage.鸥百康开 = numArray1[num1];
				num1++;
				cMagicDamage.荤芭府郴厘局拱 = numArray1[num1];
				num1++;
				cMagicDamage.鸥百卵扁 = numArray1[num1];
				num1++;
				cMagicDamage.呕巴眉农 = numArray1[num1];
				num1++;
				cMagicDamage.厘厚眉农 = numArray1[num1];
				num1++;
				cMagicDamage.UNK = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				this.cMagic[i] = cMagicDamage;
			}
		}
	}
}