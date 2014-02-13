using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace editor1
{
    /// <summary>
    /// BTreeItem.xaml 的交互逻辑
    /// </summary>
    public partial class BTreeItem : UserControl
    {
        public BTreeItem()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty contentProperty = DependencyProperty.Register("content", typeof(string), typeof(BTreeItem));

        public static readonly DependencyProperty colorProperty = DependencyProperty.Register("fillColor", typeof(Brush), typeof(BTreeItem));

        public Brush fillColor
        {
            get { return rect.Fill; }
            set { rect.Fill = value; }
        }

        public string content
        {
            get { return text.Text; }
            set { text.Text = value; }
        }
    }
}
