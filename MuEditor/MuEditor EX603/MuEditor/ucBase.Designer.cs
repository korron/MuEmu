using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace MuEditor
{
	public class ucBase : UserControl
	{
		private IContainer components;

		public ucBase()
		{
			this.InitializeComponent();
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
			base.SuspendLayout();
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.Name = "ucBase";
			base.ResumeLayout(false);
		}
	}
}