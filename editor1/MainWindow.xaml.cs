using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;

namespace editor1
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        /// <summary>
        /// 拖动的区域
        /// </summary>
        private FrameworkElement _dragScope;
        /// <summary>
        /// 用于显示鼠标跟随效果的装饰器
        /// </summary>
        private DragAdorner _adorner;
        /// <summary>
        /// 用于呈现DragAdorner的图画
        /// </summary>
        private AdornerLayer _layer;

        BehaveTree b;

        float x, y;

        ObservableCollection<BehaveTree> itemlist = new ObservableCollection<BehaveTree>();

        public MainWindow()
        {
            InitializeComponent();
            x = y = 10;
            canvas.DragOver += new DragEventHandler(canvas1_DragOver);
            canvas.Drop += new DragEventHandler(canvas1_Drop);
            b = new BehaveTree("test11.xml");      
            //canvas.Children.Add(BindThumb(b));
            //LoadXmlTest();
            itemlist.Add(b);
            TreeTest.ItemsSource = itemlist;
            BindRun();
        }

        void BindRun()
        {
            Binding b = new Binding();
            b.Source = BehaveTree.xmlData;
            b.Mode = BindingMode.OneWay;
            xmlRun.SetBinding(Run.TextProperty, b);
        }

        void LoadXmlTest()
        {
            string path = "test.xml";

            XmlDocument xml = new XmlDocument();
            xml.Load(path);

            XmlDataProvider xdp = new XmlDataProvider();
            xdp.Document = xml;
            xdp.XPath = @"/newObj/Node";

            TreeTest.DataContext = xdp;
            TreeTest.SetBinding(TreeView.ItemsSourceProperty, new Binding());
        }

        static string[] key = { "int", "string", "bool", "return"};

        static char[] keyWord = { '+', '-', '*', '/', '(', ')', ' ', '\t'};

        private void MyRTB_KeyUp(object sender, RoutedEventArgs e)
        {
            if (MyRTB.Document == null)
                return;

            MyRTB.TextChanged -= MyRTB_KeyUp;
            TextRange documentRange = new TextRange(MyRTB.Document.ContentStart, MyRTB.Document.ContentEnd);
            documentRange.ClearAllProperties();

            TextPointer StartofContent = MyRTB.Document.ContentStart;
            TextPointer currentPointer = MyRTB.Document.ContentStart;
            while (currentPointer.CompareTo(MyRTB.Document.ContentEnd) < 0)
            {
                if (currentPointer.GetPointerContext(LogicalDirection.Forward) == TextPointerContext.Text)
                {
                    string str = currentPointer.GetTextInRun(LogicalDirection.Forward);
                    //Console.WriteLine("str = \"" + str + "\"");
                    int index = Parse(str);
                    string token = str.Substring(0, index - 1);
                    if (key.Contains(token))
                    {
                        currentPointer = changeColor(Color.FromRgb(0, 255, 0), MyRTB, currentPointer, index);
                    }
                    else
                    {
                        currentPointer = changeColor(Color.FromRgb(254, 254, 254), MyRTB, currentPointer, index);
                    }
                }
                else
                    currentPointer = currentPointer.GetNextContextPosition(LogicalDirection.Forward);
            }
            MyRTB.TextChanged += MyRTB_KeyUp;
        }

        private TextPointer changeColor(Color l, RichTextBox rtb, TextPointer start, int length)
        {
            TextRange range = new TextRange(start, start.GetPositionAtOffset(length));

            range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(l));
            range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);

            
            return start.GetPositionAtOffset(length).GetNextContextPosition(LogicalDirection.Forward);
        }

        private int Parse(string str)
        {
            if (str == "")
            {
                return 1;
            }
            int i = 0;
            foreach (var c in str)
            {
                if (keyWord.Contains(c))
                {
                    i++;
                    break;
                }
                i++;
            }
            return i;
        }

        private void BtreeView(BehaveTree b)
        {
            canvas.Children.Add(BindThumb(b, x, y));
            foreach (BehaveTree t in b.next)
            {
                canvas.Children.Add(BindThumb(b, x, y));
            }
        }

        private MyThumb BindThumb(BehaveTree b, float x = 0, float y = 0)
        {
            MyThumb t = new MyThumb();
            Binding b1 = new Binding();
            b1.Source = b.name;
            t.SetBinding(MyThumb.contentProperty, b1);
            t.Style = (Style)FindResource("MyThumbStyle");
            t.rect.Fill = Brushes.White;
            Canvas.SetLeft(t, x);
            Canvas.SetTop(t, y);
            t.PreviewMouseMove += new MouseEventHandler(Mythumb_PreviewMouseMove);
            return t;
        }
        
        private void testDrop(object sender, DragEventArgs e)
        {
        }

        private void thumb1_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            ((Thumb)e.Source).Background = Brushes.Red;
            
        }

        private void thumb1_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            ((Thumb)e.Source).Background = Brushes.White;
        }

        private void thumb1_DragDelta(object sender, System.Windows.Controls.Primitives.DragDeltaEventArgs e)
        {
            //Console.WriteLine(Canvas.GetLeft(((Thumb)e.Source)));
            //Console.WriteLine(Canvas.GetTop(((Thumb)e.Source)));
            Canvas.SetLeft(((Thumb)e.Source), Canvas.GetLeft(((Thumb)e.Source)) + e.HorizontalChange);
            Canvas.SetTop(((Thumb)e.Source), Canvas.GetTop(((Thumb)e.Source)) + e.VerticalChange);
        }


        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            /*var layer = AdornerLayer.GetAdornerLayer(canvas);
            foreach (UIElement ui in canvas.Children)
            {
                if (ui is MyThumb)
                {
                    layer.Add(new MyCanvasAdorner(ui));
                }
            }*/
        }

        private void StartDrag(MouseEventArgs e)
        {
            MyThumb resource = e.Source as MyThumb;

            if (resource == null)
            {
                return;
            }

            this._dragScope = Application.Current.MainWindow.Content as FrameworkElement;


            Point p = e.GetPosition(this);
            
            this._dragScope.AllowDrop = true;

            DragEventHandler draghandler = new DragEventHandler(DragScope_PreviewDragOver);
            this._dragScope.PreviewDragOver += draghandler;

            this._adorner = new DragAdorner(this._dragScope, (UIElement)resource, 0.5);
            this._layer = AdornerLayer.GetAdornerLayer(this._dragScope as Visual);
            this._layer.Add(this._adorner);

            DataObject data = new DataObject(typeof(MyThumb), resource);
            DragDrop.DoDragDrop(resource, data, DragDropEffects.Move);

            AdornerLayer.GetAdornerLayer(this._dragScope).Remove(this._adorner);
            this._adorner = null;

            this._dragScope.PreviewDragOver -= draghandler;
        }

        void DragScope_PreviewDragOver(object sender, DragEventArgs args)
        {
            if (this._adorner != null)
            {
                this._adorner.LeftOffset = args.GetPosition(this._dragScope).X;
                this._adorner.TopOffset = args.GetPosition(this._dragScope).Y;
            }
        }

        void canvas1_Drop(object sender, DragEventArgs e)
        {
            IDataObject data = e.Data;
            Point p = grid.TranslatePoint(new Point(0, 0), canvas);
            if (data.GetDataPresent(typeof(MyThumb)))
            {
                MyThumb rect = data.GetData(typeof(MyThumb)) as MyThumb;
                Canvas.SetLeft(rect, _adorner.LeftOffset + p.X);
                Canvas.SetTop(rect, _adorner.TopOffset + p.Y);
            }
        }

        void canvas1_DragOver(object sender, DragEventArgs e)
        {
            if (!e.Data.GetDataPresent(typeof(MyThumb)))
            {
                e.Effects = DragDropEffects.None;
                e.Handled = true;
            }
        }

        void Mythumb_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                this.StartDrag(e);
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Console.WriteLine(BehaveTree.xmlData);
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            if (TreeTest.SelectedItem == null)
            {
                return;
            }
            BehaveTree node = (BehaveTree)TreeTest.SelectedItem;

            node.AddNode(new BehaveTree(node));
        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            if (TreeTest.SelectedItem == null)
            {
                return;
            }
            BehaveTree node = (BehaveTree)TreeTest.SelectedItem;
            BehaveTree father = node.parent;
            if (father == null)
            {
                return;
            }
            father.DelectNode(node);
        }

        private void MenuItem_Debug(object sender, RoutedEventArgs e)
        {
            Console.WriteLine(itemlist[0].ToString());
        }

        private void MenuItem_New_BehaveTree(object sender, RoutedEventArgs e)
        {
            itemlist[0].next.Clear();
            BehaveTree.filePath = "";
        }

        private void MenuItem_Save_BTree(object sender, RoutedEventArgs e)
        {
            if (BehaveTree.filePath == "")
            {
                MenuItem_Save_As_Btree(sender, e);
            }
            else
                itemlist[0].SaveToXml();
        }

        private void MenuItem_Save_As_Btree(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.SaveFileDialog saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            saveFileDialog.Title = "选择文件";
            saveFileDialog.Filter = "xml文件|*.xml";
            if (BehaveTree.filePath != "")
            {
                saveFileDialog.FileName = BehaveTree.filePath;
            }   
            saveFileDialog.RestoreDirectory = true;
            if (saveFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.Cancel)
            {
                return;
            }
            string filepath = saveFileDialog.FileName;
            itemlist[0].SaveToXml(filepath);
        }

        private void MenuItem_Open_BTree(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.OpenFileDialog openFileDialog = new System.Windows.Forms.OpenFileDialog();
            openFileDialog.Title = "选择文件";
            openFileDialog.Filter = "xml文件|*.xml";
            openFileDialog.FileName = string.Empty;
            openFileDialog.FilterIndex = 1;
            openFileDialog.RestoreDirectory = true;
            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.Cancel)
            {
                return;
            }
            string filepath = openFileDialog.FileName;
            itemlist[0].reloadXml(filepath);
            Console.WriteLine(filepath);
        }

        private void MenuItem_AS_Save(object sender, RoutedEventArgs e)
        {
            TextRange documentRange = new TextRange(MyRTB.Document.ContentStart, MyRTB.Document.ContentEnd);
            string str = documentRange.Text;
            BehaveTree b = (BehaveTree)TreeTest.SelectedItem;
            b.script = str;
        }
    }
}
