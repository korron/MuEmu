using System;
using System.ComponentModel;
using System.Data.OleDb;
using System.Drawing;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmBase : Form
	{
		private IContainer components;

		public static OleDbConnection Me_Conn;

		public static OleDbConnection Mu_Conn;

		static frmBase()
		{
			frmBase.Me_Conn = new OleDbConnection();
			frmBase.Mu_Conn = new OleDbConnection();
		}

		public frmBase()
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
			base.ClientSize = new System.Drawing.Size(284, 262);
			base.Name = "frmBase";
			this.Text = "frmBase";
			base.ResumeLayout(false);
		}

		protected bool Me_ExecuteSQL(string sql)
		{
			bool flag;
			try
			{
				(new OleDbCommand(sql, frmBase.Me_Conn)).ExecuteNonQuery();
				flag = true;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] strArrays = new string[] { "SQL：", sql, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(strArrays));
				return false;
			}
			return flag;
		}

		protected bool Mu_ExecuteSQL(string sql)
		{
			bool flag;
			try
			{
				(new OleDbCommand(sql, frmBase.Mu_Conn)).ExecuteNonQuery();
				flag = true;
			}
			catch (Exception exception1)
			{
				Exception exception = exception1;
				string[] strArrays = new string[] { "SQL：", sql, "\nError:", exception.Message, "\nSource:", exception.Source, "\nTrace:", exception.StackTrace };
				Utils.WarningMessage(string.Concat(strArrays));
				return false;
			}
			return flag;
		}
	}
}