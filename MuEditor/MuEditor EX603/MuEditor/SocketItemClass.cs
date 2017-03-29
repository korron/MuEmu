using System;
using System.IO;

namespace MuEditor
{
	public class SocketItemClass
	{
		public ITEM_SOCKETITEM[] cSocket = new ITEM_SOCKETITEM[150];

		public SocketItemClass(string FileName)
		{
			byte[] numArray = new byte[] { 252, 207, 171 };
			int num = 108;
			long length = (new FileInfo(FileName)).Length / (long)num;
			FileStream fileStream = new FileStream(FileName, FileMode.Open);
			for (int i = 0; (long)i < length; i++)
			{
				int num1 = 0;
				ITEM_SOCKETITEM tEMSOCKETITEM = new ITEM_SOCKETITEM();
				byte[] numArray1 = new byte[num];
				fileStream.Read(numArray1, 0, num);
				for (int j = 0; j < num; j++)
				{
					numArray1[j] = (byte)(numArray1[j] ^ numArray[j % 3]);
				}
				tEMSOCKETITEM.绊蜡锅龋 = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.加己 = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇 = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				Array.Copy(numArray1, num1, tEMSOCKETITEM.捞抚, 0, 64);
				num1 = num1 + 64;
				tEMSOCKETITEM.荐摹鸥涝 = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇1[0] = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇1[1] = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇1[2] = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇1[3] = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.饭骇1[4] = BitConverter.ToUInt32(numArray1, num1);
				num1 = num1 + 4;
				tEMSOCKETITEM.阂 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.拱 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.倔澜 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.官恩 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.锅俺 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.顶 = numArray1[num1];
				num1++;
				tEMSOCKETITEM.NULL = BitConverter.ToUInt16(numArray1, num1);
				num1 = num1 + 2;
				this.cSocket[i] = tEMSOCKETITEM;
			}
		}
	}
}