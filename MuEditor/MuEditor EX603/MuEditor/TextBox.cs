using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace MuEditor
{
	public class TextBox : System.Windows.Forms.TextBox
	{
		private bool isOnlyNumber;

		[Bindable(true)]
		[Category("Appearance")]
		[DefaultValue("false")]
		public bool IsOnlyNumber
		{
			get
			{
				return this.isOnlyNumber;
			}
			set
			{
				this.isOnlyNumber = value;
			}
		}

		public TextBox()
		{
			base.DoubleClick += new EventHandler(this.TextBox_DoubleClick);
			base.KeyUp += new KeyEventHandler(this.TextBox_KeyUp);
			base.KeyDown += new KeyEventHandler(this.TextBox_KeyDown);
			base.MouseClick += new MouseEventHandler(this.TextBox_MouseClick);
		}

		private void TextBox_DoubleClick(object sender, EventArgs e)
		{
			base.Focus();
			base.SelectAll();
		}

		private void TextBox_KeyDown(object sender, KeyEventArgs e)
		{
			if (this.isOnlyNumber && (e.KeyValue < 48 || e.KeyValue > 57) && (e.KeyValue < 96 || e.KeyValue > 105) && (e.KeyValue < 35 || e.KeyValue > 40) && e.KeyValue != 8 && e.KeyValue != 46)
			{
				e.SuppressKeyPress = true;
			}
		}

		private void TextBox_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.Control && e.KeyCode == Keys.A)
			{
				this.TextBox_DoubleClick(sender, e);
			}
		}

		private void TextBox_MouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == System.Windows.Forms.MouseButtons.Right)
			{
				this.TextBox_DoubleClick(sender, e);
			}
		}
	}
}