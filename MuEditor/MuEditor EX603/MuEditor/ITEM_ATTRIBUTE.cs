using System;

namespace MuEditor
{
	public class ITEM_ATTRIBUTE
	{
		public int GID;

		public ushort Group;

		public ushort Index;

		public byte[] Model_Folder = new byte[260];

		public byte[] Model_Name = new byte[260];

		public byte[] Name = new byte[30];

		public byte ItemKindA;

		public byte ItemKindB;

		public byte ItemCategory;

		public bool TwoHand;

		public ushort Level;

		public ushort ItemSlot;

		public ushort SkillType;

		public byte X;

		public byte Y;

		public ushort DamMin;

		public ushort DamMax;

		public ushort MagDef;

		public int Defence;

		public ushort AtkSpeed;

		public ushort WalkSpeed;

		public ushort Dur;

		public ushort MagicDur;

		public ushort MagicPW;

		public ushort Str;

		public ushort Dex;

		public ushort Eng;

		public ushort Hea;

		public ushort Cha;

		public ushort NLvl;

		public ushort Value;

		public uint Zen;

		public byte 技飘加己;

		public ClassNumber iClassNumber = new ClassNumber();

		public MuEditor.Attribute iAttribute = new MuEditor.Attribute();

		public byte 滚府扁;

		public byte 芭贰;

		public byte 俺牢惑痢;

		public byte 芒绊焊包;

		public byte UNK_01;

		public byte UNK_02;

		public byte UNK_03;

		public byte UNK_04;

		public byte UNK_05;

		public ITEM_ATTRIBUTE()
		{
		}
	}
}