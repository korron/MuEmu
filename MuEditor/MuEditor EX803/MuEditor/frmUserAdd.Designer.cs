using System;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Windows.Forms;

namespace MuEditor
{
	public class frmUserAdd : frmBase
	{
		private IContainer components;

		private Label label3;

		private MuEditor.TextBox txtAccount;

		private Label label1;

		private MuEditor.TextBox txtPwd;

		

		private Button btnOK;

		private Button btnClear;

		private Button btnClose;

		private GroupBox groupBox1;

		private Label label7;

	

		private Label label2;

		

		private static frmUserAdd form;

		static frmUserAdd()
		{
		}

		private frmUserAdd()
		{
			this.InitializeComponent();
		}

		private void btnClear_Click(object sender, EventArgs e)
		{
			this.txtAccount.Text = "";
			
			this.txtPwd.Text = "";
			
		}

		private void btnClose_Click(object sender, EventArgs e)
		{
			base.Close();
		}

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (frmBase.Me_Conn.State == ConnectionState.Open)
            {
                string format = "SELECT memb_guid FROM MEMB_INFO WHERE memb___id = '{0}'";
                try
                {
                    if (!Validator.UserName(this.txtAccount.Text.Trim()))
                    {
                        Utils.WarningMessage("Error: Account names must be between 4-10 characters, and only contain numbers, letters or underscores.");
                    }
                    else if (!Validator.PassWord(this.txtPwd.Text.Trim()))
                    {
                        Utils.WarningMessage("Error: Passwords must be between 4-10 characters.");
                    }
                    else
                    {
                        format = string.Format(format, this.txtAccount.Text.Trim());
                        OleDbDataReader reader = new OleDbCommand(format, frmBase.Me_Conn).ExecuteReader();
                        if (reader.Read())
                        {
                            Utils.WarningMessage("Error: The account [" + this.txtAccount.Text.Trim() + "] already exists.");
                            reader.Close();
                        }
                        else
                        {
                            reader.Close();
                            object[] args = new object[] { this.txtAccount.Text.Trim(), this.txtPwd.Text.Trim(), this.txtAccount.Text.Trim() + "@email.pl", 0, 1 };
                            format = string.Format("INSERT INTO dbo.MEMB_INFO(memb___id, memb__pwd, memb_name, mail_addr, fpas_ques, fpas_answ, sno__numb, post_code, bloc_code, ctl1_code) VALUES ('{0}', '{1}', 'EMU','{2}', 'question', 'answer', 0, '{4}', 0, 0)", args);
                            //format = string.Format("DECLARE @Result_Data tinyint; EXEC [dbo].[CreateAccount] @memb___id = N'{0}',@membwebid = N'{0}', @memb__pwd = N'{1}', @mail_addr = N'{2}', @Area_Code = {4}, @Result_Data = @Result_Data OUTPUT; SELECT @Result_Data as N'@Result_Data'", args);
                            if (base.Me_ExecuteSQL(format))
                            {
                                Utils.InfoMessage("Account created.");
                            }
                            else
                            {
                                Utils.WarningMessage("Error: Account creation failed.");
                            }
                        }
                    }
                }
                catch (Exception exception)
                {
                    Utils.WarningMessage("SQL：" + format + "\nError:" + exception.Message + "\nSource:" + exception.Source + "\nTrace:" + exception.StackTrace);
                }
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (this.components != null))
            {
                this.components.Dispose();
            }
            base.Dispose(disposing);
        }

		private void frmUserAdd_FormClosed(object sender, FormClosedEventArgs e)
		{
			frmUserAdd.form = null;
		}

		public static frmUserAdd GetInstance()
		{
			if (frmUserAdd.form == null)
			{
				frmUserAdd.form = new frmUserAdd();
			}
			return frmUserAdd.form;
		}

		private void InitializeComponent()
		{
			this.label3 = new Label();
			this.txtAccount = new MuEditor.TextBox();
			this.label1 = new Label();
			this.txtPwd = new MuEditor.TextBox();
			
			this.btnOK = new Button();
			this.btnClear = new Button();
			this.btnClose = new Button();
			this.groupBox1 = new GroupBox();
			this.label2 = new Label();
			
			this.label7 = new Label();
			
			this.groupBox1.SuspendLayout();
			base.SuspendLayout();
			this.label3.AutoSize = true;
			this.label3.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label3.Location = new Point(7, 19);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(41, 12);
			this.label3.TabIndex = 1;
            this.label3.Text = "Account:";
			this.txtAccount.IsOnlyNumber = false;
			this.txtAccount.Location = new Point(67, 15);
			this.txtAccount.MaxLength = 15;
			this.txtAccount.Name = "txtAccount";
			this.txtAccount.Size = new System.Drawing.Size(108, 21);
			this.txtAccount.TabIndex = 2;
			this.label1.AutoSize = true;
			this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label1.Location = new Point(7, 46);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(41, 12);
			this.label1.TabIndex = 3;
            this.label1.Text = "Password:";
			this.txtPwd.IsOnlyNumber = false;
			this.txtPwd.Location = new Point(67, 42);
			this.txtPwd.MaxLength = 10;
			this.txtPwd.Name = "txtPwd";
			this.txtPwd.Size = new System.Drawing.Size(108, 21);
			this.txtPwd.TabIndex = 4;
			
			this.btnOK.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnOK.Location = new Point(9, 143);
			this.btnOK.Name = "btnOK";
			this.btnOK.Size = new System.Drawing.Size(51, 21);
			this.btnOK.TabIndex = 10;
            this.btnOK.Text = "Create";
			this.btnOK.UseVisualStyleBackColor = true;
			this.btnOK.Click += new EventHandler(this.btnOK_Click);
			this.btnClear.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnClear.Location = new Point(67, 143);
			this.btnClear.Name = "btnClear";
			this.btnClear.Size = new System.Drawing.Size(51, 21);
			this.btnClear.TabIndex = 11;
			this.btnClear.Text = "Clear";
			this.btnClear.UseVisualStyleBackColor = true;
			this.btnClear.Click += new EventHandler(this.btnClear_Click);
			this.btnClose.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.btnClose.Location = new Point(124, 143);
			this.btnClose.Name = "btnClose";
			this.btnClose.Size = new System.Drawing.Size(51, 21);
			this.btnClose.TabIndex = 12;
			this.btnClose.Text = "Close";
			this.btnClose.UseVisualStyleBackColor = true;
			this.btnClose.Click += new EventHandler(this.btnClose_Click);
			this.groupBox1.Controls.Add(this.label2);
			
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.btnClose);
			this.groupBox1.Controls.Add(this.txtAccount);
			this.groupBox1.Controls.Add(this.btnClear);
			this.groupBox1.Controls.Add(this.txtPwd);
			
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.btnOK);
			this.groupBox1.Controls.Add(this.label7);
			
			this.groupBox1.Location = new Point(4, 4);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(182, 172);
			this.groupBox1.TabIndex = 67;
			this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Account details";
			this.label2.AutoSize = true;
			this.label2.ImeMode = System.Windows.Forms.ImeMode.NoControl;
			this.label2.Location = new Point(7, 97);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(41, 12);
			this.label2.TabIndex = 7;
            
			
		
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new System.Drawing.Size(192, 180);
			base.Controls.Add(this.groupBox1);
			base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "frmUserAdd";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			base.StartPosition = FormStartPosition.CenterParent;
			this.Text = "Create new account";
			base.FormClosed += new FormClosedEventHandler(this.frmUserAdd_FormClosed);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			base.ResumeLayout(false);
		}
	}
}