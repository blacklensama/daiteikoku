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
    /// MyThumb.xaml 的交互逻辑
    /// </summary>
    public partial class MyThumb : UserControl
    {
        public MyThumb()
        {
            InitializeComponent();
        }

        public static readonly DependencyProperty contentProperty = DependencyProperty.Register("content", typeof(string), typeof(MyThumb));

        public static readonly DependencyProperty colorProperty = DependencyProperty.Register("fillColor", typeof(Brush), typeof(MyThumb));

        public Brush fillColor
        {
            get { return rect.Fill; }
            set { rect.Fill = fillColor; }
        }

        public string content
        {
            get { return myText.Text; }
            set { myText.Text = value; }
        }
    }
}
