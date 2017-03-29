using MuEditor.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MuEditor
{
	public class CharPanel : ucBase
	{
		public const int EquipNum = 12;

		private int index = -1;

		private int lastedIndex = -2;

		private bool isShowTip;

		private Rectangle[] positions = new Rectangle[] { new Rectangle(14, 73, 47, 72), new Rectangle(233, 73, 47, 72), new Rectangle(124, 11, 46, 46), new Rectangle(124, 73, 46, 72), new Rectangle(124, 161, 46, 45), new Rectangle(14, 161, 46, 46), new Rectangle(232, 161, 48, 46), new Rectangle(202, 11, 71, 46), new Rectangle(15, 12, 46, 46), new Rectangle(82, 34, 20, 20), new Rectangle(82, 184, 20, 20), new Rectangle(192, 184, 20, 20) };

		private DrawingUnit[] units = new DrawingUnit[12];

		private DrawingUnit curUnit = new DrawingUnit();

		private DrawingUnit selectedUnit;

		private int prof = -1;

		private EquipEditor editor;

		private IContainer components;

		private System.Windows.Forms.ContextMenuStrip popMenu;

		private ToolStripMenuItem 删除ToolStripMenuItem;

		private ToolStripMenuItem 属性ToolStripMenuItem;

		private ToolStripMenuItem 关闭ToolStripMenuItem;

		private ToolStripMenuItem 复制CToolStripMenuItem;

		private System.Windows.Forms.ContextMenuStrip muCopy;

		private ToolStripMenuItem 粘贴VToolStripMenuItem;

		private ToolTip ttInfo;

		private ToolStripMenuItem 复制全部AToolStripMenuItem;

		private ToolStripMenuItem 清空CToolStripMenuItem;

		private ToolStripMenuItem toolStripMenuItem2;

		private ToolStripMenuItem toolStripMenuItem1;

		public EquipEditor Editor
		{
			set
			{
				this.editor = value;
			}
		}

		public int Prof
		{
			get
			{
				return this.prof;
			}
			set
			{
				this.prof = value;
			}
		}

		public CharPanel()
		{
			this.InitializeComponent();
		}

		public CharPanel(EquipEditor editor)
		{
			this.InitializeComponent();
			this.editor = editor;
		}

		private bool addEditItem(int index)
		{
			if (this.curUnit == null || this.curUnit.Item == null || this.curUnit.Item.Img == null)
			{
				return false;
			}
			this.curUnit.X = index;
			this.curUnit.Y = 0;
			this.editor.updateData(this.curUnit.Item);
			if (this.canPutItem(this.curUnit) && this.putItem(this.curUnit, true, false))
			{
				return true;
			}
            Utils.WarningMessage(string.Concat("Item ", this.curUnit.Item.Name, " can not be placed in that position!"));
			return false;
		}

		public bool canPutItem(DrawingUnit unit)
		{
			EquipItem item = unit.Item;
			int x = unit.X;
			int y = unit.Y;
			if (x < 0 && x >= 12 && this.units[x] != null)
			{
				return false;
			}
			ushort itemSlot = EquipEditor.xItem[item.Type * 512 + item.Code].ItemSlot;
			switch (this.index)
			{
				case 0:
				{
					if (itemSlot != 0)
					{
						break;
					}
					return true;
				}
				case 1:
				{
					if (itemSlot != 0 && itemSlot != 1)
					{
						break;
					}
					return true;
				}
				case 2:
				{
					if (itemSlot != 2)
					{
						break;
					}
					return true;
				}
				case 3:
				{
					if (itemSlot != 3)
					{
						break;
					}
					return true;
				}
				case 4:
				{
					if (itemSlot != 4)
					{
						break;
					}
					return true;
				}
				case 5:
				{
					if (itemSlot != 5)
					{
						break;
					}
					return true;
				}
				case 6:
				{
					if (itemSlot != 6)
					{
						break;
					}
					return true;
				}
				case 7:
				{
					if (itemSlot != 7)
					{
						break;
					}
					return true;
				}
				case 8:
				{
					if (itemSlot != 8)
					{
						break;
					}
					return true;
				}
				case 9:
				{
					if (itemSlot != 9)
					{
						break;
					}
					return true;
				}
				case 10:
				{
					if (itemSlot != 10 && itemSlot != 11)
					{
						break;
					}
					return true;
				}
				case 11:
				{
					if (itemSlot != 10 && itemSlot != 11)
					{
						break;
					}
					return true;
				}
			}
			return false;
		}

		private void CharPanel_MouseClick(object sender, MouseEventArgs e)
		{
			this.index = this.findRectangle(e.X, e.Y);
			if (e.Button == System.Windows.Forms.MouseButtons.Right)
			{
				if (this.index < 0)
				{
					this.selectedUnit = null;
					return;
				}
				if (this.units[this.index] == null)
				{
					this.muCopy.Show(this, e.X, e.Y);
					this.selectedUnit = null;
					return;
				}
				this.selectedUnit = this.units[this.index];
				this.popMenu.Show(this, e.X, e.Y);
				return;
			}
			if (this.index < 0)
			{
				this.selectedUnit = null;
				return;
			}
			if (this.units[this.index] == null)
			{
				this.selectedUnit = null;
				return;
			}
			if ((int)base.Parent.Parent.Controls.Find("tabcInfo", false).Length > 0)
			{
				((TabControl)base.Parent.Parent.Controls.Find("tabcInfo", false)[0]).SelectedIndex = 2;
			}
			this.selectedUnit = this.units[this.index];
			this.editor.updateUI(this.selectedUnit.Item);
		}

		private void CharPanel_MouseDoubleClick(object sender, MouseEventArgs e)
		{
			this.index = this.findRectangle(e.X, e.Y);
			if (this.index < 0)
			{
				this.selectedUnit = null;
			}
			else if (this.units[this.index] == null)
			{
				this.addEditItem(this.index);
				return;
			}
		}

		private void CharPanel_MouseEnter(object sender, EventArgs e)
		{
			this.curUnit.Item = this.editor.EditItem;
		}

		private void CharPanel_MouseLeave(object sender, EventArgs e)
		{
			this.curUnit.Item = null;
			this.isShowTip = false;
			this.ttInfo.Hide(this);
			base.Invalidate();
		}

		private void CharPanel_MouseMove(object sender, MouseEventArgs e)
		{
			this.index = this.findRectangle(e.X, e.Y);
			if (this.lastedIndex != this.index)
			{
				this.isShowTip = false;
				this.ttInfo.Hide(this);
			}
			if (this.index < 0)
			{
				this.isShowTip = false;
				this.ttInfo.Hide(this);
			}
			else if (this.units[this.index] != null && !this.isShowTip)
			{
				this.isShowTip = true;
				this.lastedIndex = this.index;
				this.ttInfo.Show(Utils.GetEquipInfo(this.units[this.index].Item), this, e.X + 20, e.Y + 20);
			}
			base.Invalidate();
		}

		private void CharPanel_Paint(object sender, PaintEventArgs e)
		{
			Graphics graphics = e.Graphics;
			for (int i = 0; i < 12; i++)
			{
				if (this.units[i] != null)
				{
					this.drawUnit(graphics, this.units[i]);
				}
			}
			if (this.selectedUnit != null && this.selectedUnit.Item != null)
			{
				Brush solidBrush = new SolidBrush(Color.FromArgb(60, 128, 128, 128));
				graphics.FillRectangle(solidBrush, this.positions[this.selectedUnit.X]);
			}
		}

		public void clearData()
		{
			this.selectedUnit = null;
			for (int i = 0; i < 12; i++)
			{
				this.units[i] = null;
			}
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void drawUnit(Graphics g, DrawingUnit unit)
		{
			int x = unit.X;
			int y = unit.Y;
			EquipItem item = unit.Item;
			int num = Math.Max(this.positions[x].Width - item.Width * 26 >> 1, 0);
			int num1 = Math.Max(this.positions[x].Height - item.Height * 26 >> 1, 0);
			int num2 = Math.Min(item.Width * 26, this.positions[x].Width);
			int num3 = Math.Min(item.Height * 26, this.positions[x].Height);
			g.DrawImage(item.Img, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
			if (item.Level > 0)
			{
				g.DrawString(string.Format("+{0}", item.Level), new System.Drawing.Font("Arial", 8f), Brushes.White, (float)(this.positions[x].X + num), (float)(this.positions[x].Y + num1));
			}
			else if (item.IsNoDurability && item.Durability > 1)
			{
				g.DrawString(Convert.ToString(item.Durability), new System.Drawing.Font("Arial", 6f), Brushes.White, (float)(this.positions[x].X + num), (float)(this.positions[x].Y + num1));
			}
			if (item.SN < 0)
			{
				g.DrawRectangle(Pens.White, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length && item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length && item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length && item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length && item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length && item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Fuchsia, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if ((item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length || item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length || item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length || item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length || item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length || item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1) && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Violet, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length || item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length || item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length || item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length || item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length || item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1)
			{
				g.DrawRectangle(Pens.Pink, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.PlusLevel > 0 && item.SetVal > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.Aqua, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.SetVal > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6 || item.PlusLevel > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.Turquoise, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.LawnGreen, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.PlusLevel > 0 && item.SetVal > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Gold, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.PlusLevel > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6) || item.SetVal > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Yellow, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6)
			{
				g.DrawRectangle(Pens.YellowGreen, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.PlusLevel > 0)
			{
				g.DrawRectangle(Pens.SkyBlue, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
				return;
			}
			if (item.SetVal > 0)
			{
				g.DrawRectangle(Pens.Khaki, this.positions[x].X + num, this.positions[x].Y + num1, num2, num3);
			}
		}

		public int findRectangle(int x, int y)
		{
			for (int i = 0; i < 12; i++)
			{
				if (this.positions[i].Contains(x, y))
				{
					return i;
				}
			}
			return -1;
		}

		public string getEquipCodes()
		{
			StringBuilder stringBuilder = new StringBuilder();
			for (int i = 0; i < 12; i++)
			{
				if (this.units[i] == null || this.units[i].Item == null)
				{
                    stringBuilder.Append("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
				}
				else
				{
					stringBuilder.Append(this.units[i].Item.ToString());
				}
			}
			return stringBuilder.ToString();
		}

		private bool hasDataInClipboard()
		{
			IDataObject dataObject = Clipboard.GetDataObject();
			if (dataObject.GetDataPresent(DataFormats.Text))
			{
				string str = ((string)dataObject.GetData(DataFormats.Text)).Replace("&", "").Replace("0x", "");
				if (str.Length == 32 && Validator.HexString(str) && !str.StartsWith("FF"))
				{
					return true;
				}
			}
			return false;
		}

		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.popMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.关闭ToolStripMenuItem = new ToolStripMenuItem();
			this.复制CToolStripMenuItem = new ToolStripMenuItem();
			this.复制全部AToolStripMenuItem = new ToolStripMenuItem();
			this.属性ToolStripMenuItem = new ToolStripMenuItem();
			this.删除ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripMenuItem();
			this.muCopy = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.清空CToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem2 = new ToolStripMenuItem();
			this.粘贴VToolStripMenuItem = new ToolStripMenuItem();
			this.ttInfo = new ToolTip(this.components);
			this.popMenu.SuspendLayout();
			this.muCopy.SuspendLayout();
			base.SuspendLayout();
			ToolStripItemCollection items = this.popMenu.Items;
			ToolStripItem[] toolStripItemArray = new ToolStripItem[] { this.删除ToolStripMenuItem };
			items.AddRange(toolStripItemArray);
			this.popMenu.Name = "popMenu";
			this.popMenu.Size = new System.Drawing.Size(141, 136);
			this.关闭ToolStripMenuItem.Name = "关闭ToolStripMenuItem";
			this.关闭ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.关闭ToolStripMenuItem.Text = "Shear(&T)";
			this.关闭ToolStripMenuItem.Click += new EventHandler(this.关闭ToolStripMenuItem_Click);
			this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
			this.复制CToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.复制CToolStripMenuItem.Text = "Copy(&C)";
			this.复制CToolStripMenuItem.Click += new EventHandler(this.复制CToolStripMenuItem_Click);
			this.复制全部AToolStripMenuItem.Name = "复制全部AToolStripMenuItem";
			this.复制全部AToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.复制全部AToolStripMenuItem.Text = "Copy All(&A)";
			this.复制全部AToolStripMenuItem.Click += new EventHandler(this.复制全部AToolStripMenuItem_Click);
			this.属性ToolStripMenuItem.Name = "属性ToolStripMenuItem";
			this.属性ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.属性ToolStripMenuItem.Text = "Modify(&E)";
			this.属性ToolStripMenuItem.Click += new EventHandler(this.属性ToolStripMenuItem_Click);
			this.删除ToolStripMenuItem.Name = "删除ToolStripMenuItem";
			this.删除ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.删除ToolStripMenuItem.Text = "Delete Item";
			this.删除ToolStripMenuItem.Click += new EventHandler(this.删除ToolStripMenuItem_Click);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(140, 22);
            this.toolStripMenuItem1.Text = "Clear(&M)";
			this.toolStripMenuItem1.Click += new EventHandler(this.清空CToolStripMenuItem_Click);
			ToolStripItemCollection toolStripItemCollections = this.muCopy.Items;
            ToolStripItem[] toolStripItemArray1 = new ToolStripItem[] {};
			toolStripItemCollections.AddRange(toolStripItemArray1);
			this.muCopy.Name = "muCopy";
			this.muCopy.Size = new System.Drawing.Size(141, 70);
			this.muCopy.Opening += new CancelEventHandler(this.muCopy_Opening);
			this.清空CToolStripMenuItem.Name = "清空CToolStripMenuItem";
			this.清空CToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.清空CToolStripMenuItem.Text = "Clear(&C)";
			this.清空CToolStripMenuItem.Click += new EventHandler(this.清空CToolStripMenuItem_Click);
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(140, 22);
            this.toolStripMenuItem2.Text = "Copy All(&A)";
			this.toolStripMenuItem2.Click += new EventHandler(this.复制全部AToolStripMenuItem_Click);
			this.粘贴VToolStripMenuItem.Name = "粘贴VToolStripMenuItem";
			this.粘贴VToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.粘贴VToolStripMenuItem.Text = "Stick(&V)";
			this.粘贴VToolStripMenuItem.Click += new EventHandler(this.粘贴VToolStripMenuItem_Click);
			this.ttInfo.ToolTipIcon = ToolTipIcon.Info;
            this.ttInfo.ToolTipTitle = "Item Information";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackgroundImage = Resources.char_2;
			this.BackgroundImageLayout = ImageLayout.None;
			this.Cursor = Cursors.Default;
			this.DoubleBuffered = true;
			base.Margin = new System.Windows.Forms.Padding(0);
			base.Name = "CharPanel";
			base.Size = new System.Drawing.Size(295, 284);
			base.Paint += new PaintEventHandler(this.CharPanel_Paint);
			base.MouseClick += new MouseEventHandler(this.CharPanel_MouseClick);
			base.MouseDoubleClick += new MouseEventHandler(this.CharPanel_MouseDoubleClick);
			base.MouseEnter += new EventHandler(this.CharPanel_MouseEnter);
			base.MouseLeave += new EventHandler(this.CharPanel_MouseLeave);
			base.MouseMove += new MouseEventHandler(this.CharPanel_MouseMove);
			this.popMenu.ResumeLayout(false);
			this.muCopy.ResumeLayout(false);
			base.ResumeLayout(false);
		}

		public bool loadItemsByCodes(byte[] codes)
		{
			return this.loadItemsByCodes(codes, 0, (int)codes.Length);
		}

		public bool loadItemsByCodes(byte[] codes, int offset, int len)
		{
			if (offset < 0 || len < 192 || codes == null)
			{
				base.Invalidate();
				return false;
			}
			EquipItem equipItem = null;
			for (int i = 0; i < 12; i++)
			{
				EquipItem equipItem1 = EquipItem.createItem(codes, offset + i * 16, 16);
				equipItem = equipItem1;
				if (equipItem1 != null)
				{
					this.units[i] = new DrawingUnit(equipItem, i, 0);
				}
			}
			base.Invalidate();
			return true;
		}

		private void muCopy_Opening(object sender, CancelEventArgs e)
		{
			this.粘贴VToolStripMenuItem.Enabled = this.hasDataInClipboard();
		}

		public bool putItem(DrawingUnit unit, bool add, bool isCopy)
		{
			int x = unit.X;
			int y = unit.Y;
			if (!isCopy)
			{
				if (!add)
				{
					Utils.SN = Utils.SN - 1;
					unit.Item.SN = Utils.SN;
					this.units[x] = unit;
				}
				else
				{
					this.units[x] = new DrawingUnit(new EquipItem(), x, y);
					Utils.SN = Utils.SN - 1;
					unit.Item.SN = Utils.SN;
					this.units[x].Item.assign(unit.Item);
				}
				if (!Utils.ListPackage.Contains(unit.Item.ToString()))
				{
					Utils.ListPackage.Add(unit.Item.ToString());
				}
			}
			else
			{
				this.units[this.index] = new DrawingUnit(new EquipItem(), this.index, y);
				this.units[this.index].Item.assign(unit.Item);
			}
			return true;
		}

		public bool removeItem(DrawingUnit unit)
		{
			int x = unit.X;
			this.units[x] = null;
			return true;
		}

		private void setEquipProperty(DrawingUnit unit)
		{
			if (unit != null)
			{
				this.Cursor = Cursors.WaitCursor;
				EquipProperty equipProperty = new EquipProperty(unit.Item);
				equipProperty.ShowDialog();
				equipProperty.Dispose();
				this.Cursor = Cursors.Default;
			}
		}

		private void 关闭ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(this.selectedUnit.Item.ToString(), true);
			this.removeItem(this.selectedUnit);
			this.selectedUnit = null;
		}

		private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.removeItem(this.selectedUnit);
			Utils.ListPackage.Remove(this.selectedUnit.Item.ToString());
			this.selectedUnit = null;
		}

		private void 复制CToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(string.Concat("&", this.selectedUnit.Item.ToString()), true);
		}

		private void 复制全部AToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(string.Concat("&", this.getEquipCodes()), true);
		}

		private void 属性ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.setEquipProperty(this.selectedUnit);
		}

		private void 清空CToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.clearData();
			base.Invalidate();
		}

		private void 粘贴VToolStripMenuItem_Click(object sender, EventArgs e)
		{
			IDataObject dataObject = Clipboard.GetDataObject();
			if (dataObject.GetDataPresent(DataFormats.Text))
			{
				string str = ((string)dataObject.GetData(DataFormats.Text)).Replace("&", "").Replace("0x", "");
				if (str.Length == 32 && Validator.HexString(str) && !str.StartsWith("FF"))
				{
					EquipItem equipItem = EquipItem.createItem(str);
					DrawingUnit drawingUnit = new DrawingUnit(equipItem);
					if (equipItem != null && this.canPutItem(drawingUnit))
					{
						this.putItem(drawingUnit, false, true);
						return;
					}
                    Utils.WarningMessage(string.Concat("Item ", equipItem.Name, " can not be placed in that position!"));
				}
			}
		}
	}
}