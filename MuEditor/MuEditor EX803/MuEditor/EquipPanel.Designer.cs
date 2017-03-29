using MuEditor.Properties;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MuEditor
{
	public class EquipPanel : ucBase
	{
		public const int pixels = 26;

		private IContainer components;

		private System.Windows.Forms.ContextMenuStrip popMenu;

		private ToolStripMenuItem 删除ToolStripMenuItem;

		private ToolStripMenuItem 关闭ToolStripMenuItem;

		private ToolStripMenuItem toolStripMenuItem1;

		private ToolStripMenuItem 复制CToolStripMenuItem;

		private System.Windows.Forms.ContextMenuStrip muCopy;

		private ToolStripMenuItem 粘贴VToolStripMenuItem;

		private ToolStripMenuItem 复制全部AToolStripMenuItem;

		public ToolTip ttInfo;

		private ToolStripMenuItem 清空CToolStripMenuItem;

		private ToolStripMenuItem toolStripMenuItem2;

		private ToolStripMenuItem toolStripMenuItem3;

		private ToolStripMenuItem toolStripMenuItem4;

		private ToolStripMenuItem 整理ZToolStripMenuItem;

		private int xnum;

		private int ynum;

		private DrawingUnit[,] units;

		private bool[,] flags;

		private DrawingUnit curUnit = new DrawingUnit();

		private DrawingUnit activeUnit;

		private DrawingUnit selectedUnit;

		private DrawingUnit deleteUnit;

		private int lastedX;

		private int lastedY;

		private bool isShowTip;

		private int lastedTipX = -1;

		private int lastedTipY = -1;

		private EquipEditor editor;

		public EquipEditor Editor
		{
			set
			{
				this.editor = value;
			}
		}

		public IList Items
		{
			get
			{
				return this.getItems();
			}
		}

		public int XNum
		{
			get
			{
				return this.xnum;
			}
		}

		public int YNum
		{
			get
			{
				return this.ynum;
			}
		}

		public EquipPanel()
		{
			this.InitializeComponent();
		}

		public EquipPanel(int xnum, int ynum, EquipEditor editor)
		{
			this.InitializeComponent();
			this.setSize(xnum, ynum);
			this.editor = editor;
			this.curUnit.Item = editor.EditItem;
		}

		private bool addEditItem(int x, int y)
		{
			if (this.curUnit == null || this.curUnit.Item == null || this.curUnit.Item.Img == null)
			{
				return false;
			}
			this.curUnit.X = x;
			this.curUnit.Y = y;
			this.editor.updateData(this.curUnit.Item);
			if (this.canPutItem(this.curUnit) && this.putItem(this.curUnit, true))
			{
				return true;
			}
            Utils.WarningMessage(string.Concat("There is not enough space to put items[", this.curUnit.Item.Name, "]"));
			return false;
		}

		public bool canPutItem(EquipItem item, int x, int y, bool[,] flags)
		{
			if (item.Width + x > this.xnum || item.Height + y > this.ynum || x < 0 || y < 0)
			{
				return false;
			}
			if (flags[x, y])
			{
				return false;
			}
			for (int i = 0; i < item.Width; i++)
			{
				for (int j = 0; j < item.Height; j++)
				{
					if (flags[i + x, j + y])
					{
						return false;
					}
				}
			}
			return true;
		}

		public bool canPutItem(DrawingUnit unit)
		{
			EquipItem item = unit.Item;
			int x = unit.X;
			int y = unit.Y;
			if (item.Width + x > this.xnum || item.Height + y > this.ynum || x < 0 || y < 0)
			{
				return false;
			}
			if (this.flags[x, y])
			{
				return false;
			}
			for (int i = 0; i < item.Width; i++)
			{
				for (int j = 0; j < item.Height; j++)
				{
					if (this.flags[i + x, j + y])
					{
						return false;
					}
				}
			}
			return true;
		}

		public bool canPutItem(EquipItem item, int x, int y)
		{
			if (item.Width + x > this.xnum || item.Height + y > this.ynum || x < 0 || y < 0)
			{
				return false;
			}
			if (this.flags[x, y])
			{
				return false;
			}
			for (int i = 0; i < item.Width; i++)
			{
				for (int j = 0; j < item.Height; j++)
				{
					if (this.flags[i + x, j + y])
					{
						return false;
					}
				}
			}
			return true;
		}

		public bool canPutItems(EquipItem[] items)
		{
			bool[,] flagArray = (bool[,])this.flags.Clone();
			EquipItem[] equipItemArray = items;
			for (int i = 0; i < (int)equipItemArray.Length; i++)
			{
				EquipItem equipItem = equipItemArray[i];
				if (equipItem != null)
				{
					for (int j = 0; j < this.ynum; j++)
					{
						for (int k = 0; k < this.xnum; k++)
						{
							if (!flagArray[k, j] && this.canPutItem(equipItem, k, j, flagArray) && this.tryPutItem(equipItem, k, j, flagArray))
							{
                                continue;
							}
						}
					}
					return false;
				}
			}
			return true;
		}

		public void clearData()
		{
			this.activeUnit = null;
			this.selectedUnit = null;
			this.lastedX = 0;
			this.lastedY = 0;
			for (int i = 0; i < this.xnum; i++)
			{
				for (int j = 0; j < this.ynum; j++)
				{
					this.units[i, j] = null;
					this.flags[i, j] = false;
				}
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

		public void DownItem()
		{
			if (this.activeUnit != null)
			{
				this.activeUnit.X = this.lastedX;
				this.activeUnit.Y = this.lastedY;
				if (this.canPutItem(this.activeUnit) && this.putItem(this.activeUnit, false))
				{
					this.selectedUnit = null;
					this.activeUnit = null;
				}
			}
		}

		private void drawUnit(Graphics g, DrawingUnit unit)
		{
			int x = unit.X;
			int y = unit.Y;
			EquipItem item = unit.Item;
			g.DrawImage(item.Img, x * 26, y * 26, item.Width * 26, item.Height * 26);
			if (item.Level > 0)
			{
				g.DrawString(string.Format("+{0}", item.Level), new System.Drawing.Font("Arial", 8f), Brushes.White, (float)(x * 26), (float)(y * 26));
			}
			else if (item.IsNoDurability && item.Durability > 1)
			{
				g.DrawString(Convert.ToString(item.Durability), new System.Drawing.Font("Arial", 6f), Brushes.White, (float)(x * 26), (float)(y * 26));
			}
			if (item.SN < 0)
			{
				g.DrawRectangle(Pens.White, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length && item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length && item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length && item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length && item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length && item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Fuchsia, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if ((item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length || item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length || item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length || item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length || item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length || item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1) && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Violet, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.XQ1 > 0 && item.XQ1 < (int)EquipEditor.xSocket.Length || item.XQ2 > 0 && item.XQ2 < (int)EquipEditor.xSocket.Length || item.XQ3 > 0 && item.XQ3 < (int)EquipEditor.xSocket.Length || item.XQ4 > 0 && item.XQ4 < (int)EquipEditor.xSocket.Length || item.XQ5 > 0 && item.XQ5 < (int)EquipEditor.xSocket.Length || item.YG > 0 && item.YG < (int)Utils.YGS.Length - 1)
			{
				g.DrawRectangle(Pens.Pink, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.PlusLevel > 0 && item.SetVal > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.Aqua, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.SetVal > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6 || item.PlusLevel > 0 && item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.Turquoise, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.ZY1 && item.ZY2 && item.ZY3 && item.ZY4 && item.ZY5 && item.ZY6)
			{
				g.DrawRectangle(Pens.LawnGreen, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.PlusLevel > 0 && item.SetVal > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Gold, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.PlusLevel > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6) || item.SetVal > 0 && (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6))
			{
				g.DrawRectangle(Pens.Yellow, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.ZY1 || item.ZY2 || item.ZY3 || item.ZY4 || item.ZY5 || item.ZY6)
			{
				g.DrawRectangle(Pens.YellowGreen, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.PlusLevel > 0)
			{
				g.DrawRectangle(Pens.SkyBlue, x * 26, y * 26, item.Width * 26, item.Height * 26);
				return;
			}
			if (item.SetVal > 0)
			{
				g.DrawRectangle(Pens.Khaki, x * 26, y * 26, item.Width * 26, item.Height * 26);
			}
		}

		private void EquipPanel_MouseClick(object sender, MouseEventArgs e)
		{
			DrawingUnit drawingUnit = null;
			int x = e.X / 26;
			int y = e.Y / 26;
			if (e.Button == System.Windows.Forms.MouseButtons.Right)
			{
				if (this.activeUnit == null)
				{
					DrawingUnit drawingUnit1 = this.findUnit(x, y);
					drawingUnit = drawingUnit1;
					if (drawingUnit1 == null)
					{
						this.muCopy.Show(this, e.X, e.Y);
					}
					else
					{
						this.deleteUnit = drawingUnit;
						this.popMenu.Show(this, e.X, e.Y);
					}
				}
				else
				{
					this.activeUnit.X = this.lastedX;
					this.activeUnit.Y = this.lastedY;
					if (this.canPutItem(this.activeUnit) && this.putItem(this.activeUnit, false))
					{
						this.selectedUnit = null;
						this.activeUnit = null;
						DrawingUnit drawingUnit2 = this.findUnit(x, y);
						drawingUnit = drawingUnit2;
						if (drawingUnit2 == null)
						{
							this.muCopy.Show(this, e.X, e.Y);
						}
						else
						{
							this.deleteUnit = drawingUnit;
							this.popMenu.Show(this, e.X, e.Y);
						}
					}
				}
			}
			else if (this.activeUnit != null)
			{
				this.activeUnit.X = x;
				this.activeUnit.Y = y;
				if (!this.canPutItem(this.activeUnit) || !this.putItem(this.activeUnit, false))
				{
					this.activeUnit.X = this.lastedX;
					this.activeUnit.Y = this.lastedY;
					if (this.canPutItem(this.activeUnit) && this.putItem(this.activeUnit, false))
					{
						this.selectedUnit = null;
						this.activeUnit = null;
					}
					this.EquipPanel_MouseClick(sender, e);
				}
				else
				{
					this.selectedUnit = null;
					this.activeUnit = null;
				}
			}
			else
			{
				drawingUnit = this.findUnit(x, y);
				this.activeUnit = drawingUnit;
				if (this.activeUnit != null)
				{
					this.removeItem(this.activeUnit);
				}
				if (!this.flags[x, y] && this.selectedUnit != null)
				{
					this.removeItem(this.selectedUnit);
					this.activeUnit = this.selectedUnit;
					this.lastedX = this.selectedUnit.X;
					this.lastedY = this.selectedUnit.Y;
					this.selectedUnit = null;
				}
				if (drawingUnit != null)
				{
					if ((int)base.Parent.Parent.Controls.Find("tabcInfo", false).Length > 0)
					{
						((TabControl)base.Parent.Parent.Controls.Find("tabcInfo", false)[0]).SelectedIndex = 2;
					}
					this.selectedUnit = drawingUnit;
					this.lastedX = this.selectedUnit.X;
					this.lastedY = this.selectedUnit.Y;
					this.editor.updateUI(drawingUnit.Item);
				}
			}
			base.Invalidate();
		}

		private void EquipPanel_MouseDBClick(object sender, MouseEventArgs e)
		{
			int x = e.X / 26;
			int y = e.Y / 26;
			if (!this.flags[x, y] && this.selectedUnit == null)
			{
				if (!this.editor.AllPart)
				{
					this.putItems(this.editor.AddNum);
				}
				else
				{
					this.putItems();
					this.editor.AllPart = false;
				}
			}
			base.Invalidate();
		}

		private void EquipPanel_MouseEnter(object sender, EventArgs e)
		{
			this.curUnit.Item = this.editor.EditItem;
		}

		private void EquipPanel_MouseLeave(object sender, EventArgs e)
		{
			this.curUnit.Item = null;
			this.isShowTip = false;
			this.ttInfo.Hide(this);
			base.Invalidate();
		}

		private void EquipPanel_MouseMove(object sender, MouseEventArgs e)
		{
			try
			{
				int x = e.X / 26;
				int y = e.Y / 26;
				if (this.lastedTipX != x || this.lastedTipY != y)
				{
					this.isShowTip = false;
					this.ttInfo.Hide(this);
				}
				if (!this.flags[x, y])
				{
					if (this.activeUnit == null)
					{
						this.Cursor = Cursors.Default;
					}
					else
					{
						this.Cursor = Cursors.Hand;
					}
					this.isShowTip = false;
					this.ttInfo.Hide(this);
				}
				else
				{
					this.Cursor = Cursors.Default;
					if (this.findUnit(x, y) != null && !this.isShowTip)
					{
						this.isShowTip = true;
						this.lastedTipX = x;
						this.lastedTipY = y;
						this.ttInfo.Show(Utils.GetEquipInfo(this.findUnit(x, y).Item), this, e.X + 20, e.Y + 20);
					}
				}
			}
			catch
			{
			}
			base.Invalidate();
		}

		private void EquipPanel_Paint(object sender, PaintEventArgs e)
		{
			if (this.units == null)
			{
				return;
			}
			Graphics graphics = e.Graphics;
			DrawingUnit drawingUnit = null;
			EquipItem item = null;
			int x = 0;
			int y = 0;
			for (int i = 0; i < this.xnum; i++)
			{
				for (int j = 0; j < this.ynum; j++)
				{
					DrawingUnit drawingUnit1 = this.units[i, j];
					drawingUnit = drawingUnit1;
					if (drawingUnit1 != null && drawingUnit.Item != null)
					{
						this.drawUnit(graphics, this.units[i, j]);
					}
				}
			}
			if (this.activeUnit != null && this.activeUnit.Item != null)
			{
				item = this.activeUnit.Item;
				x = this.activeUnit.X;
				y = this.activeUnit.Y;
				graphics.DrawImage(item.Img, x * 26, y * 26, item.Width * 26, item.Height * 26);
				Brush solidBrush = new SolidBrush(Color.FromArgb(60, 128, 128, 128));
				graphics.FillRectangle(solidBrush, this.activeUnit.X * 26, this.activeUnit.Y * 26, this.activeUnit.Item.Width * 26, this.activeUnit.Item.Height * 26);
				graphics.DrawRectangle(Pens.Blue, x * 26, y * 26, item.Width * 26, item.Height * 26);
			}
		}

		protected DrawingUnit findUnit(int x, int y)
		{
			DrawingUnit drawingUnit = null;
			if (this.flags[x, y])
			{
				for (int i = 0; i < this.xnum; i++)
				{
					for (int j = 0; j < this.ynum; j++)
					{
						DrawingUnit drawingUnit1 = this.units[i, j];
						drawingUnit = drawingUnit1;
						if (drawingUnit1 != null && drawingUnit.contains(x, y))
						{
							return drawingUnit;
						}
					}
				}
			}
			return null;
		}

		public string getEquipCodes()
		{
			StringBuilder stringBuilder = new StringBuilder();
			for (int i = 0; i < this.ynum; i++)
			{
				for (int j = 0; j < this.xnum; j++)
				{
					if (this.units[j, i] == null || this.units[j, i].Item == null)
					{
						stringBuilder.Append("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
					}
					else
					{
						stringBuilder.Append(this.units[j, i].Item.ToString());
					}
				}
			}
			return stringBuilder.ToString();
		}

		public EquipItem[] getEquipItems()
		{
			IList items = this.getItems();
			EquipItem[] item = new EquipItem[items.Count];
			for (int i = 0; i < items.Count; i++)
			{
				item[i] = (EquipItem)items[i];
			}
			return item;
		}

		public IList getItems()
		{
			IList arrayLists = new ArrayList();
			for (int i = 0; i < this.ynum; i++)
			{
				for (int j = 0; j < this.xnum; j++)
				{
					if (this.units[j, i] != null && this.units[j, i].Item != null)
					{
						arrayLists.Add(this.units[j, i].Item);
					}
				}
			}
			return arrayLists;
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
				if (str.Length % 32 == 0 && Validator.HexString(str))
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
			this.toolStripMenuItem4 = new ToolStripMenuItem();
			this.toolStripMenuItem1 = new ToolStripMenuItem();
			this.删除ToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem3 = new ToolStripMenuItem();
			this.muCopy = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.清空CToolStripMenuItem = new ToolStripMenuItem();
			this.整理ZToolStripMenuItem = new ToolStripMenuItem();
			this.toolStripMenuItem2 = new ToolStripMenuItem();
			this.粘贴VToolStripMenuItem = new ToolStripMenuItem();
			this.ttInfo = new ToolTip(this.components);
			this.popMenu.SuspendLayout();
			this.muCopy.SuspendLayout();
			base.SuspendLayout();
			ToolStripItemCollection items = this.popMenu.Items;
			ToolStripItem[] toolStripItemArray = new ToolStripItem[] { this.删除ToolStripMenuItem, this.toolStripMenuItem3 };
			items.AddRange(toolStripItemArray);
			this.popMenu.Name = "popMenu";
			this.popMenu.Size = new System.Drawing.Size(137, 158);
			this.关闭ToolStripMenuItem.Name = "关闭ToolStripMenuItem";
			this.关闭ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.关闭ToolStripMenuItem.Text = "Shear";
			this.关闭ToolStripMenuItem.Click += new EventHandler(this.关闭ToolStripMenuItem_Click);
			this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
			this.复制CToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.复制CToolStripMenuItem.Text = "Copy";
			this.复制CToolStripMenuItem.Click += new EventHandler(this.复制CToolStripMenuItem_Click);
			this.复制全部AToolStripMenuItem.Name = "复制全部AToolStripMenuItem";
			this.复制全部AToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.复制全部AToolStripMenuItem.Text = "Copy All";
			this.复制全部AToolStripMenuItem.Click += new EventHandler(this.复制全部AToolStripMenuItem_Click);
			this.toolStripMenuItem4.Name = "toolStripMenuItem4";
			this.toolStripMenuItem4.Size = new System.Drawing.Size(136, 22);
            this.toolStripMenuItem4.Text = "Sort";
			this.toolStripMenuItem4.Click += new EventHandler(this.整理ZToolStripMenuItem_Click);
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(136, 22);
            this.toolStripMenuItem1.Text = "Modify";
			this.toolStripMenuItem1.Click += new EventHandler(this.toolStripMenuItem1_Click);
			this.删除ToolStripMenuItem.Name = "删除ToolStripMenuItem";
			this.删除ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.删除ToolStripMenuItem.Text = "Delete Item";
			this.删除ToolStripMenuItem.Click += new EventHandler(this.删除ToolStripMenuItem_Click);
			this.toolStripMenuItem3.Name = "toolStripMenuItem3";
			this.toolStripMenuItem3.Size = new System.Drawing.Size(136, 22);
            this.toolStripMenuItem3.Text = "Delete All";
			this.toolStripMenuItem3.Click += new EventHandler(this.清空CToolStripMenuItem_Click);
			ToolStripItemCollection toolStripItemCollections = this.muCopy.Items;
			ToolStripItem[] toolStripItemArray1 = new ToolStripItem[] { this.清空CToolStripMenuItem };
			toolStripItemCollections.AddRange(toolStripItemArray1);
			this.muCopy.Name = "muCopy";
			this.muCopy.Size = new System.Drawing.Size(153, 114);
			this.muCopy.Opening += new CancelEventHandler(this.muCopy_Opening);
			this.清空CToolStripMenuItem.Name = "清空CToolStripMenuItem";
			this.清空CToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.清空CToolStripMenuItem.Text = "Delete All";
			this.清空CToolStripMenuItem.Click += new EventHandler(this.清空CToolStripMenuItem_Click);
			this.整理ZToolStripMenuItem.Name = "整理ZToolStripMenuItem";
			this.整理ZToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.整理ZToolStripMenuItem.Text = "Sort";
			this.整理ZToolStripMenuItem.Click += new EventHandler(this.整理ZToolStripMenuItem_Click);
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(152, 22);
            this.toolStripMenuItem2.Text = "Copy All";
			this.toolStripMenuItem2.Click += new EventHandler(this.复制全部AToolStripMenuItem_Click);
			this.粘贴VToolStripMenuItem.Name = "粘贴VToolStripMenuItem";
			this.粘贴VToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.粘贴VToolStripMenuItem.Text = "Stick";
			this.粘贴VToolStripMenuItem.Click += new EventHandler(this.粘贴VToolStripMenuItem_Click);
			this.ttInfo.ToolTipIcon = ToolTipIcon.Info;
            this.ttInfo.ToolTipTitle = "Item Information";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackgroundImage = Resources.warehouse_2;
			this.BackgroundImageLayout = ImageLayout.None;
			this.Cursor = Cursors.Default;
			this.DoubleBuffered = true;
			base.Margin = new System.Windows.Forms.Padding(0);
			base.Name = "EquipPanel";
			base.Size = new System.Drawing.Size(209, 209);
			base.Paint += new PaintEventHandler(this.EquipPanel_Paint);
			base.MouseClick += new MouseEventHandler(this.EquipPanel_MouseClick);
			base.MouseDoubleClick += new MouseEventHandler(this.EquipPanel_MouseDBClick);
			base.MouseEnter += new EventHandler(this.EquipPanel_MouseEnter);
			base.MouseLeave += new EventHandler(this.EquipPanel_MouseLeave);
			base.MouseMove += new MouseEventHandler(this.EquipPanel_MouseMove);
			this.popMenu.ResumeLayout(false);
			this.muCopy.ResumeLayout(false);
			base.ResumeLayout(false);
		}

		public bool loadItemsByCodes(byte[] codes, int offset, int len)
		{
			if (offset < 0 || len < this.xnum * this.ynum * 16 || codes == null)
			{
				base.Invalidate();
				return false;
			}
			EquipItem equipItem = null;
			for (int i = 0; i < this.ynum; i++)
			{
				for (int j = 0; j < this.xnum; j++)
				{
					EquipItem equipItem1 = EquipItem.createItem(codes, offset + (i * this.xnum + j) * 16, 16);
					equipItem = equipItem1;
					if (equipItem1 != null)
					{
						this.units[j, i] = new DrawingUnit(equipItem, j, i);
						this.putItem(this.units[j, i], false);
					}
				}
			}
			base.Invalidate();
			return true;
		}

		public bool loadItemsByCodes(byte[] codes)
		{
			return this.loadItemsByCodes(codes, 0, (int)codes.Length);
		}

		public bool moveItem(DrawingUnit unit, int x, int y)
		{
			if (unit == null || unit.Item == null)
			{
				return false;
			}
			int num = unit.X;
			int num1 = unit.Y;
			this.removeItem(unit);
			unit.X = x;
			unit.Y = y;
			if (this.canPutItem(unit) && this.putItem(unit, false))
			{
				return true;
			}
			unit.X = num;
			unit.Y = num1;
			this.putItem(unit, false);
			return false;
		}

		private void muCopy_Opening(object sender, CancelEventArgs e)
		{
			this.粘贴VToolStripMenuItem.Enabled = this.hasDataInClipboard();
		}

		public bool putItem(EquipItem item, bool add, bool isCopy)
		{
			DrawingUnit drawingUnit = null;
			if (isCopy)
			{
				drawingUnit = new DrawingUnit(new EquipItem(), 0, 0);
				drawingUnit.Item.assign(item);
			}
			else if (!add)
			{
				drawingUnit = new DrawingUnit(item, 0, 0);
			}
			else
			{
				drawingUnit = new DrawingUnit(new EquipItem(), 0, 0);
				drawingUnit.Item.assign(item);
				Utils.SN = Utils.SN - 1;
				drawingUnit.Item.SN = Utils.SN;
				if (!Utils.ListWareHouse.Contains(drawingUnit.Item.ToString()))
				{
					Utils.ListWareHouse.Add(drawingUnit.Item.ToString());
				}
			}
			for (int i = 0; i < this.ynum; i++)
			{
				for (int j = 0; j < this.xnum; j++)
				{
					if (!this.flags[j, i])
					{
						drawingUnit.X = j;
						drawingUnit.Y = i;
						if (this.canPutItem(drawingUnit))
						{
							return this.putItem(drawingUnit, false);
						}
					}
				}
			}
			return false;
		}

		public bool putItem(DrawingUnit unit, bool add)
		{
			int x = unit.X;
			int y = unit.Y;
			if (!add)
			{
				this.units[x, y] = unit;
			}
			else
			{
				this.units[x, y] = new DrawingUnit(new EquipItem(), x, y);
				this.units[x, y].Item.assign(unit.Item);
				Utils.SN = Utils.SN - 1;
				this.units[x, y].Item.SN = Utils.SN;
			}
			for (int i = 0; i < unit.Item.Width; i++)
			{
				for (int j = 0; j < unit.Item.Height; j++)
				{
					this.flags[i + x, j + y] = true;
				}
			}
			return true;
		}

		public bool putItems(EquipItem[] items, bool isCopy)
		{
			bool flag = true;
			if (!this.canPutItems(items))
			{
				return false;
			}
			for (int i = 0; i < (int)items.Length; i++)
			{
				if (items[i] != null)
				{
					flag = (!flag ? false : this.putItem(items[i], true, isCopy));
				}
			}
			return flag;
		}

		public bool putItems(int nums)
		{
			bool flag = true;
			this.editor.updateData(this.curUnit.Item);
			for (int i = 0; i < nums; i++)
			{
				flag = (!flag ? false : this.putItem(this.curUnit.Item, true, false));
			}
			return flag;
		}

        public bool putItems()
        {
            bool flag = true;
            this.editor.updateData(this.curUnit.Item);
            EquipItem item = new EquipItem();
            string str = "7,8,9,10,11";
            string str2 = "0";
            switch (this.curUnit.Item.Code)
            {
                case 0x17:
                case 0x20:
                case 15:
                case 20:
                case 0x2f:
                case 0x30:
                case 0x25:
                case 0x47:
                    str2 = "7";
                    break;

                case 0x3b:
                case 60:
                case 0x3d:
                case 0x48:
                    str2 = "10";
                    break;
            }
            foreach (string str3 in str.Split(new char[] { ',' }))
            {
                if (!(str3 == str2) && (EquipEditor.xItem[(Convert.ToByte(str3) * 0x200) + this.curUnit.Item.Code] != null))
                {
                    item.assign(EquipItem.createItem(this.curUnit.Item.Code, Convert.ToByte(str3)));
                    item.Code = this.curUnit.Item.Code;
                    item.Type = Convert.ToByte(str3);
                    this.editor.updateData(item);
                    flag = flag && this.putItem(item, true, false);
                }
            }
            return flag;
        }

		public bool removeItem(DrawingUnit unit)
		{
			if (unit == null)
			{
				return true;
			}
			int x = unit.X;
			int y = unit.Y;
			this.units[x, y] = null;
			for (int i = 0; i < unit.Item.Width; i++)
			{
				for (int j = 0; j < unit.Item.Height; j++)
				{
					this.flags[i + x, j + y] = false;
				}
			}
			return true;
		}

		protected void resizePanel()
		{
			base.Width = this.xnum * 26;
			base.Height = this.ynum * 26;
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

		public void setSize(int xnum, int ynum)
		{
			this.xnum = xnum;
			this.ynum = ynum;
			this.resizePanel();
			this.units = new DrawingUnit[xnum, ynum];
			this.flags = new bool[xnum, ynum];
			for (int i = 0; i < xnum; i++)
			{
				for (int j = 0; j < ynum; j++)
				{
					this.units[i, j] = null;
					this.flags[i, j] = false;
				}
			}
		}

		private void toolStripMenuItem1_Click(object sender, EventArgs e)
		{
			this.setEquipProperty(this.deleteUnit);
			this.deleteUnit = null;
		}

		public bool tryPutItem(EquipItem item, int x, int y, bool[,] flags)
		{
			if (item.Width + x > this.xnum || item.Height + y > this.ynum || x < 0 || y < 0)
			{
				return false;
			}
			if (flags[x, y])
			{
				return false;
			}
			for (int i = 0; i < item.Width; i++)
			{
				for (int j = 0; j < item.Height; j++)
				{
					if (flags[i + x, j + y])
					{
						return false;
					}
					flags[i + x, j + y] = true;
				}
			}
			return true;
		}

		private void 关闭ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(this.deleteUnit.Item.ToString(), true);
			this.removeItem(this.deleteUnit);
			this.deleteUnit = null;
		}

		private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.removeItem(this.deleteUnit);
			Utils.ListWareHouse.Remove(this.deleteUnit.Item.ToString());
			this.deleteUnit = null;
		}

		private void 复制CToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(string.Concat("&", this.deleteUnit.Item.ToString()), true);
		}

		private void 复制全部AToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Clipboard.SetDataObject(string.Concat("&", this.getEquipCodes()), true);
		}

		private void 整理ZToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.DownItem();
			EquipItem[] equipItems = this.getEquipItems();
			this.clearData();
			this.putItems(equipItems, true);
			base.Invalidate();
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
					if (equipItem != null && this.putItem(equipItem, false, true))
					{
						return;
					}
				}
				else if (str.Length % 32 == 0 && Validator.HexString(str))
				{
					EquipItem[] equipItemArray = new EquipItem[str.Length / 32];
					for (int i = 0; i < str.Length / 32; i++)
					{
						string str1 = str.Substring(i * 32, 32);
						if (!str1.StartsWith("FF"))
						{
							equipItemArray[i] = EquipItem.createItem(str1);
						}
					}
					if (!this.putItems(equipItemArray, true))
					{
                        Utils.WarningMessage("There is not enough space for these items, please clean up enough space!");
					}
				}
			}
		}
	}
}