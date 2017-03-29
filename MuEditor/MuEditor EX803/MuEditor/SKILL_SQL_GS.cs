using System;

namespace MuEditor
{
	public class SKILL_SQL_GS
	{
		private byte skillLv;

		private int gsSkillID;

		public int GSSkillID
		{
			get
			{
				return this.gsSkillID;
			}
			set
			{
				this.gsSkillID = value;
			}
		}

		public byte SKillLv
		{
			get
			{
				return this.skillLv;
			}
			set
			{
				this.skillLv = value;
			}
		}

		public SKILL_SQL_GS()
		{
		}
	}
}