using MuEditor.Properties;
using System;
using System.Collections;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace MuEditor
{
	public class EquipImageCache
	{
		private Hashtable cache = new Hashtable();

		public static EquipImageCache Instance
		{
			get
			{
				return EquipImageCache.Nested.instance;
			}
		}

		private EquipImageCache()
		{
		}

		public static byte[] BitmapToBytes(System.Drawing.Bitmap Bitmap)
		{
			byte[] array;
			MemoryStream memoryStream = null;
			try
			{
				try
				{
					memoryStream = new MemoryStream();
					Bitmap.Save(memoryStream, Bitmap.RawFormat);
                    byte[] numArray = new byte[memoryStream.Length];
					array = memoryStream.ToArray();
				}
				catch (ArgumentNullException argumentNullException)
				{
					throw argumentNullException;
				}
			}
			finally
			{
				memoryStream.Close();
			}
			return array;
		}

		private Image byteArrayToImage(byte[] Bytes)
		{
			Image image;
			using (MemoryStream memoryStream = new MemoryStream(Bytes))
			{
				image = Image.FromStream(memoryStream);
			}
			return image;
		}

		public static bool ExistsFile(string FilePath)
		{
			if (File.Exists(FilePath))
			{
				return true;
			}
			return false;
		}

		public EquipItem getItem(string name)
		{
			EquipItem itemFromDb = null;
			EquipItem item = (EquipItem)this.cache[name];
			itemFromDb = item;
			if (item == null)
			{
				lock (this.cache)
				{
					EquipItem equipItem = (EquipItem)this.cache[name];
					itemFromDb = equipItem;
					if (equipItem == null)
					{
						itemFromDb = this.getItemFromDb(name) ?? EquipItem.UnknownItem;
						this.cache[name] = itemFromDb;
						this.cache[itemFromDb.CodeType] = itemFromDb;
					}
				}
			}
			return itemFromDb;
		}

		public EquipItem getItemByCodeType(string codeType)
		{
			EquipItem itemFromDb = null;
			EquipItem item = (EquipItem)this.cache[codeType];
			itemFromDb = item;
			if (item == null)
			{
				lock (this.cache)
				{
					EquipItem equipItem = (EquipItem)this.cache[codeType];
					itemFromDb = equipItem;
					if (equipItem == null)
					{
						itemFromDb = this.getItemFromDb(EquipItem.getItemCode(codeType), EquipItem.getItemType(codeType)) ?? EquipItem.UnknownItem;
						this.cache[codeType] = itemFromDb;
						this.cache[itemFromDb.Name] = itemFromDb;
					}
				}
			}
			return itemFromDb;
		}

		protected EquipItem getItemFromDb(string ItemName)
		{
			byte[] numArray = null;
			EquipItem equipItem = null;
			try
			{
				int num = 0;
				while (num < (int)EquipEditor.xItem.Length)
				{
					if (EquipEditor.xItem[num] == null || !(frmMain.ByteToString(EquipEditor.xItem[num].Name, 30) == ItemName))
					{
						num++;
					}
					else
					{
						int wIZARD = EquipEditor.xItem[num].iClassNumber.WIZARD + EquipEditor.xItem[num].iClassNumber.KNIGHT << (1 + EquipEditor.xItem[num].iClassNumber.ELF & 31) << (2 + EquipEditor.xItem[num].iClassNumber.MAGUMSA & 31) << (3 + EquipEditor.xItem[num].iClassNumber.DARKLORD & 31) << 4;
						bool flag = (EquipEditor.xItem[num].iClassNumber.WIZARD != 0 ? true : EquipEditor.xItem[num].iClassNumber.SUMMONER != 0);
						equipItem = new EquipItem(EquipEditor.xItem[num].Index, frmMain.ByteToString(EquipEditor.xItem[num].Name, 30), EquipEditor.xItem[num].TwoHand, EquipEditor.xItem[num].Group, EquipEditor.xItem[num].X, EquipEditor.xItem[num].Y, wIZARD, flag);
						string str = string.Concat(Application.StartupPath, "\\Item\\{0}-{1}.jpg");
						str = string.Format(str, EquipEditor.xItem[num].Index, EquipEditor.xItem[num].Group);
						numArray = (!EquipImageCache.ExistsFile(str) ? EquipImageCache.BitmapToBytes(Resources.unknownItem) : this.imageToByteArray(str));
						equipItem.Img = this.byteArrayToImage(numArray);
						break;
					}
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "getItemFromDb：\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			return equipItem;
		}

		protected EquipItem getItemFromDb(ushort ItemIndex, ushort ItemType)
		{
			byte[] numArray = null;
			EquipItem equipItem = null;
			try
			{
				int itemType = ItemType * 512 + ItemIndex;
				if (EquipEditor.xItem[itemType] != null)
				{
					int wIZARD = EquipEditor.xItem[itemType].iClassNumber.WIZARD + EquipEditor.xItem[itemType].iClassNumber.KNIGHT << (1 + EquipEditor.xItem[itemType].iClassNumber.ELF & 31) << (2 + EquipEditor.xItem[itemType].iClassNumber.MAGUMSA & 31) << (3 + EquipEditor.xItem[itemType].iClassNumber.DARKLORD & 31) << 4;
					bool flag = (EquipEditor.xItem[itemType].iClassNumber.KNIGHT != 0 ? false : string.Concat(EquipEditor.xItem[itemType].iClassNumber.WIZARD.ToString(), EquipEditor.xItem[itemType].iClassNumber.SUMMONER.ToString()).Replace("0", "") != "");
					equipItem = new EquipItem(EquipEditor.xItem[itemType].Index, frmMain.ByteToString(EquipEditor.xItem[itemType].Name, 30), EquipEditor.xItem[itemType].TwoHand, EquipEditor.xItem[itemType].Group, EquipEditor.xItem[itemType].X, EquipEditor.xItem[itemType].Y, wIZARD, flag);
					string str = string.Concat(Application.StartupPath, "\\Item\\{0}-{1}.jpg");
					str = string.Format(str, EquipEditor.xItem[itemType].Index, EquipEditor.xItem[itemType].Group);
					numArray = (!EquipImageCache.ExistsFile(str) ? EquipImageCache.BitmapToBytes(Resources.unknownItem) : this.imageToByteArray(str));
					equipItem.Img = this.byteArrayToImage(numArray);
				}
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] message = new string[] { "getItemFromDb：\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(message));
			}
			return equipItem;
		}

		private byte[] imageToByteArray(string FilePath)
		{
			byte[] array;
			using (MemoryStream memoryStream = new MemoryStream())
			{
				using (Image image = Image.FromFile(FilePath))
				{
					using (Bitmap bitmap = new Bitmap(image))
					{
						bitmap.Save(memoryStream, image.RawFormat);
					}
				}
				array = memoryStream.ToArray();
			}
			return array;
		}

		private class Nested
		{
			internal readonly static EquipImageCache instance;

			static Nested()
			{
				EquipImageCache.Nested.instance = new EquipImageCache();
			}

			public Nested()
			{
			}
		}
	}
}