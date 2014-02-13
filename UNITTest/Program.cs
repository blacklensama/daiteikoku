using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using editor1;


namespace UNITTest
{
    class Program
    {
        static void Main(string[] args)
        {
            BehaveTree b = new BehaveTree("test.xml");
            b.ToString();
        }
    }
}
