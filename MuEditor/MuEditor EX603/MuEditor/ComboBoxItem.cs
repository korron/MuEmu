using System;

namespace MuEditor
{
	public class ComboBoxItem
	{
		private string _text = "";

		private string _value;

		public string Text
		{
			get
			{
				return this._text;
			}
			set
			{
				this._text = value;
			}
		}

		public string Value
		{
			get
			{
				return this._value;
			}
			set
			{
				this._value = value;
			}
		}

		public ComboBoxItem(string text, string value)
		{
			this._text = text;
			this._value = value;
		}

		public override string ToString()
		{
			return this._text;
		}
	}
}