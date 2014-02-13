using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Xml.Serialization;

namespace editor1
{
    public enum NodeKind
    {
        CompositeNode_SelectorNode,
        CompositeNode_SequenceNode,
        CompositeNode_ParallelNode,
        Decortaor_Node,
        Condition_Node,
        Action_Node
    }

    public enum RunStatus
    {
        Completed,
        Failure,
        Running
    }
    [XmlRoot("newObj")]
    public class NewObj
    {
        [XmlElement("Node")]
        public BehaveTree b;
    }
    [XmlRoot("Node")]
    public class BehaveTree : Object, INotifyPropertyChanged
    {
        public BehaveTree()
        {

        }
        public BehaveTree(BehaveTree b = null)
        {
            init();
            parent = b;
        }
        public void init()
        {
            next = new ObservableCollection<BehaveTree>();
            name = "未命名";
            script = "";
            scriptName = "";
        }
        public BehaveTree(string path)
        {
            init();
            loadFromXmlPath(path);
            filePath = path;
        }
        public void reloadXml(string path)
        {
            next.Clear();
            loadFromXmlPath(path);
            filePath = path;
        }

        public void SaveToXml()
        {
            SaveToXml(filePath);
        }

        public void SaveToXml(string file)
        {
            XmlWriterSettings setting = new XmlWriterSettings();
            setting.Indent = true;
            setting.Encoding = Encoding.GetEncoding("gb2312");
            setting.NewLineChars = Environment.NewLine;
            setting.OmitXmlDeclaration = true;
            XmlWriter wx = XmlWriter.Create(file, setting);
            XmlSerializer sz = new XmlSerializer(typeof(NewObj));
            XmlSerializerNamespaces _namespaces = new XmlSerializerNamespaces(
                    new XmlQualifiedName[] {
                        new XmlQualifiedName(string.Empty, "aa")  
                 });
            NewObj n = new NewObj();
            n.b = this;
            sz.Serialize(wx, n, _namespaces);
            //fs.Close();
        }
        public BehaveTree(XmlNode node, BehaveTree o)
        {
            init();
            loadFromXmlNode(node, o);
        }
        public void AddNode(BehaveTree b)
        {
            next.Add(b);
        }
        public void DelectNode(BehaveTree b)
        {
            next.Remove(b);
        }
        public BehaveTree loadFromXmlPath(string path)
        {
            XmlDocument doc = new XmlDocument();
            StreamReader sr = new StreamReader(path, Encoding.GetEncoding("gb2312"));
            xmlData = sr.ReadToEnd();
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            doc.Load(sr);
            
            XmlNode node = doc.FirstChild.FirstChild;
            BehaveTree b = loadFromXmlNode(node, null);
            sr.Close();
            return b;
        }
        public BehaveTree loadFromXmlNode(XmlNode node, BehaveTree o)
        {
            parent = o;
            name = node.Attributes["nodeName"].Value;
            string s = node.Attributes["nodeKind"].Value;
            kind = (NodeKind)Enum.Parse(typeof(NodeKind), s, true);
            s = node.Attributes["runStatus"].Value;
            status = (RunStatus)Enum.Parse(typeof(RunStatus), s, true);
            foreach (XmlNode n in node.ChildNodes)
            {
                next.Add(new BehaveTree(n, this));
            }
            if (node.Attributes["script"]!=null)
            {
                script = node.Attributes["script"].Value;
                scriptName = node.Attributes["scriptName"].Value;
            }
            return this;
        }
        [XmlElement("Node")]
        public ObservableCollection<BehaveTree> next
        {
            set;
            get;
        }
        [XmlIgnore]
        public BehaveTree parent
        {
            set;
            get;
        }
        [XmlAttribute("nodeName")]
        public string name
        {
            set;
            get;
        }
        [XmlAttribute("nodeKind")]
        public NodeKind kind
        {
            set;
            get;
        }
        [XmlAttribute("runStatus")]
        public RunStatus status
        {
            set;
            get;
        }
        [XmlAttribute("script")]
        public string script
        {
            set;
            get;
        }
        [XmlAttribute("scriptName")]
        public string scriptName
        {
            set;
            get;
        }
        public override string ToString()
        {
            
            return "test";
        }
        [XmlIgnore]
        public static string xmlData
        {
            set;
            get;
        }
        [XmlIgnore]
        public static string filePath
        {
            set;
            get;
        }
        public event PropertyChangedEventHandler PropertyChanged;

        void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }
    }
}
