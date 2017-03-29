using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmGuildUser : frmBase
	{
		private IContainer components;

		private Button btnSearch;

		private MuEditor.TextBox txtName;

		private GroupBox groupBox1;

		public frmGuildUser()
		{
			this.InitializeComponent();
		}

		private void btnSearch_Click(object sender, EventArgs e)
		{
			frmGuild.joinName = this.txtName.Text.Trim().Replace("'", "''");
			base.Close();
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
			this.btnSearch = new Button();
			this.txtName = new MuEditor.TextBox();
			this.groupBox1 = new GroupBox();
			this.groupBox1.SuspendLayout();
			base.SuspendLayout();
			this.btnSearch.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnSearch.Location = new Point(144, 20);
			this.btnSearch.Name = "btnSearch";
			this.btnSearch.Size = new System.Drawing.Size(50, 23);
			this.btnSearch.TabIndex = 10;
            this.btnSearch.Text = "Determined";
			this.btnSearch.UseVisualStyleBackColor = true;
			this.btnSearch.Click += new EventHandler(this.btnSearch_Click);
			this.txtName.IsOnlyNumber = false;
			this.txtName.Location = new Point(8, 21);
			this.txtName.MaxLength = 50;
			this.txtName.Name = "txtName";
			this.txtName.Size = new System.Drawing.Size(130, 21);
			this.txtName.TabIndex = 9;
			this.txtName.KeyPress += new KeyPressEventHandler(this.txtName_KeyPress);
			this.groupBox1.Controls.Add(this.btnSearch);
			this.groupBox1.Controls.Add(this.txtName);
			this.groupBox1.Location = new Point(8, 6);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(200, 60);
			this.groupBox1.TabIndex = 14;
			this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Please enter the role name";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(215, 74);
			base.Controls.Add(this.groupBox1);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmGuildUser";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterParent;
            this.Text = "Add member";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			base.ResumeLayout(false);
		}

		private void txtName_KeyPress(object sender, KeyPressEventArgs e)
		{
			if (e.KeyChar == '\r')
			{
				this.btnSearch_Click(sender, e);
			}
		}
	}
}